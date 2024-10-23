#pragma once

#include "Blueprint/UserWidgetPool.h"
#include "Components/Widget.h"

#include "Base/SAnimatedSwitcher.h"

#include "ActivatableWidgetContainer.generated.h"

/**
 * Base class with the functionality to manager N activatable widgets.
 */
UCLASS(Abstract)
class UActivatableWidgetContainer : public UWidget
{
	GENERATED_BODY()

public:
	DECLARE_EVENT_OneParam(UActivatableWidgetContainer, FOnDisplayedWidgetChanged, UActivatableWidget*);

	DECLARE_EVENT_TwoParams(UActivatableWidgetContainer, FTransitioningChanged, UActivatableWidgetContainer* /* Widget */, bool /* bIsTransitioning */);

public:
	UActivatableWidgetContainer(const FObjectInitializer& Initializer);

	/** UUserWidget: Interface Begin */
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif
	/** UUserWidget: Interface End */

	UFUNCTION(BlueprintPure, Category = "ActivatableWidgetStack")
	int32 GetNumWidgets() const;

	UFUNCTION(BlueprintPure, Category = "ActivatableWidgetStack")
	const TArray<UActivatableWidget*>& GetWidgetList() const;

	UFUNCTION(BlueprintCallable, Category = "ActivatableWidgetStack")
	UActivatableWidget* GetActiveWidget() const;

	FOnDisplayedWidgetChanged& OnDisplayedWidgetChanged() const;

	/** 
	 * Adds an activatable widget instance to the container. 
	 * This instance is not pooled in any way by the stack and responsibility for ownership lies with the original creator of the widget.
	 * 
	 * NOTE: In general, it is *strongly* recommended that you opt for the class-based AddWidget above. This one is mostly just here for legacy support.
	 */
	void AddWidgetInstance(UActivatableWidget& ActivatableWidget);

	void RemoveWidget(UActivatableWidget& WidgetToRemove);

	UFUNCTION(BlueprintCallable, Category = "ActivatableWidgetContainer")
	void ClearWidgets();

	/** Adds an activatable widget to the container. See BP_AddWidget for more info. */
	template <typename TActivatableWidget = UActivatableWidget>
	TActivatableWidget* AddWidget(TSubclassOf<UActivatableWidget> ActivatableWidgetClass);

	/** 
	 * Generates (either creates or pulls from the inactive pool) instance of the given widget class and adds it to the container.
	 * The provided lambda is called after the instance has been generated and before it is actually added to the container.
	 * So if you've got setup to do on the instance before it potentially activates, the lambda is the place to do it.
	 */
	template <typename TActivatableWidget = UActivatableWidget>
	TActivatableWidget* AddWidget(TSubclassOf<UActivatableWidget> ActivatableWidgetClass, TFunctionRef<void(TActivatableWidget&)> InstanceInitFunc);

protected:
	/** UVisual: Interface Begin */
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	/** UVisual: Interface End */

	/** UUserWidget: Interface Begin */
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void OnWidgetRebuilt() override;
	/** UUserWidget: Interface Begin */

	virtual void OnWidgetAddedToList(UActivatableWidget& AddedWidget);

	void SetSwitcherActiveWidget(UActivatableWidget& AddedWidget, bool bInstantTransition = false);
	void SetSwitcherIndex(int32 TargetIndex, bool bInstantTransition = false);

private:
	/** 
	 * Adds a widget of the given class to the container. 
	 * Note that all widgets added to the container are pooled, so the caller should not try to cache and re-use the created widget.
	 * 
	 * It is possible for multiple instances of the same class to be added to the container at once, so any instance created in the past
	 * is not guaranteed to be the one returned this time.
	 *
	 * So in practice, you should not trust that any prior state has been retained on the returned widget, and establish all appropriate properties every time.
	 */
	UFUNCTION(BlueprintCallable, Category = "ActivatableWidgetStack", Meta = (DeterminesOutputType = ActivatableWidgetClass, DisplayName = "Push Widget"))
	UActivatableWidget* BP_AddWidget(TSubclassOf<UActivatableWidget> ActivatableWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "ActivatableWidgetContainer")
	void RemoveWidget(UActivatableWidget* WidgetToRemove);

	UActivatableWidget* AddWidgetInternal(TSubclassOf<UActivatableWidget> ActivatableWidgetClass, TFunctionRef<void(UActivatableWidget&)> InitFunc);
	void RegisterInstanceInternal(UActivatableWidget& NewWidget);

	void HandleSwitcherIsTransitioningChanged(bool bIsTransitioning);
	void HandleActiveIndexChanged(int32 ActiveWidgetIndex);
	void HandleActiveWidgetDeactivated(UActivatableWidget* DeactivatedWidget);

	/**
	 * This is a bit hairy and very edge-casey, but a necessary measure to ensure expected Slate interaction behavior.
	 *
	 * Since we immediately remove slots from our switcher in response to changes to the active index of the switcher, we can
	 * wind up confusing the HittestGrid for that frame. The grid (correctly) thinks the widget at the previously displayed index is what it
	 * should interact with, but it skips it because we've already released all references and destroyed it. This causes pointer
	 * input (most importantly the synthetic mouse move) to fall through our container for that frame, potentially triggering interactions
	 * with elements that, as far as any user can tell, were never actually visible!
	 *
	 * So, when we remove a slot, we hold a reference to the SWidget in that slot for a single frame, to ensure hittest grid integrity.
	 * This does delay destruction of the removed SObjectWidget by one frame, but that does not present any discernable issue,
	 * as it's no different from any other inactive widget within a switcher.
	 */
	void ReleaseWidget(const TSharedRef<SWidget>& WidgetToRelease);

public:
	FTransitioningChanged OnTransitioningChanged;

protected:
	/** The type of transition to play between widgets */
	UPROPERTY(EditAnywhere, Category = "Transition")
	ECommonSwitcherTransition TransitionType;

	/** The curve function type to apply to the transition animation */
	UPROPERTY(EditAnywhere, Category = "Transition")
	ETransitionCurve TransitionCurveType;

	/** The total duration of a single transition between widgets */
	UPROPERTY(EditAnywhere, Category = "Transition")
	float TransitionDuration = 0.4f;

	UPROPERTY(Transient)
	TArray<UActivatableWidget*> WidgetList;

	UPROPERTY(Transient)
	UActivatableWidget* DisplayedWidget;

	UPROPERTY(Transient)
	FUserWidgetPool GeneratedWidgetsPool;

	TSharedPtr<SOverlay> MyOverlay;
	TSharedPtr<SAnimatedSwitcher> MySwitcher;

private:
	TArray<TSharedPtr<SWidget>> ReleasedWidgets;

	//@todo DanH: This is pretty clunky - revisit for something smoother
	bool bRemoveDisplayedWidgetPostTransition = false;

	mutable FOnDisplayedWidgetChanged OnDisplayedWidgetChangedEvent;
};

template <typename ActivatableWidgetT>
ActivatableWidgetT* UActivatableWidgetContainer::AddWidget(TSubclassOf<UActivatableWidget> ActivatableWidgetClass)
{
	// Don't actually add the widget if the cast will fail
	if (ActivatableWidgetClass && ActivatableWidgetClass->IsChildOf<ActivatableWidgetT>())
	{
		return Cast<ActivatableWidgetT>(AddWidgetInternal(ActivatableWidgetClass, [](UActivatableWidget&)
		{
		}));
	}
	return nullptr;
}

template <typename ActivatableWidgetT>
ActivatableWidgetT* UActivatableWidgetContainer::AddWidget(TSubclassOf<UActivatableWidget> ActivatableWidgetClass, TFunctionRef<void(ActivatableWidgetT&)> InstanceInitFunc)
{
	// Don't actually add the widget if the cast will fail
	if (ActivatableWidgetClass && ActivatableWidgetClass->IsChildOf<ActivatableWidgetT>())
	{
		return Cast<ActivatableWidgetT>(AddWidgetInternal(ActivatableWidgetClass, [&InstanceInitFunc](UActivatableWidget& WidgetInstance)
		{
			InstanceInitFunc(*CastChecked<ActivatableWidgetT>(&WidgetInstance));
		}));
	}
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
// UActivatableWidgetStack
//////////////////////////////////////////////////////////////////////////

/** 
 */
UCLASS()
class UActivatableWidgetStack : public UActivatableWidgetContainer
{
	GENERATED_BODY()

protected:
	/** UActivatableWidgetContainer: Interface Begin */
	virtual void OnWidgetAddedToList(UActivatableWidget& AddedWidget) override;
	/** UActivatableWidgetContainer: Interface End */
};