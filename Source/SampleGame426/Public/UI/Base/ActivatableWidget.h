#pragma once

#include "CustomUserWidget.h"

#include "ActivatableWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWidgetActivationChanged);

UCLASS(Meta = (DisableNativeTick))
class UActivatableWidget : public UCustomUserWidget
{
	GENERATED_BODY()

public:
	virtual void Reset();
	virtual bool CanBeReleased() const;

	UFUNCTION(BlueprintPure, Category = "ActivatableWidget")
	bool IsActivated() const;

	/** Returns the desired widget to focus when this Widget Activates. */
	UFUNCTION(BlueprintCallable, Category = "ActivatableWidget")
	UWidget* GetDesiredFocusTarget() const;

	FSimpleMulticastDelegate& OnActivated() const;
	FSimpleMulticastDelegate& OnDeactivated() const;

	bool SetsVisibilityOnActivated() const;
	bool SetsVisibilityOnDeactivated() const;

	UFUNCTION(BlueprintCallable, Category = "ActivatableWidget")
	void ActivateWidget();

	UFUNCTION(BlueprintCallable, Category = "ActivatableWidget")
	void DeactivateWidget();

protected:
	/** UUserWidget: Interface Begin */
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	/** UUserWidget: Interface End */

protected:
	/**
	 * Override to provide the desired widget that should receive focus when this becomes the primary active widget.
	 * If bAutoRestoreFocus is true, is only called when there is no valid cached restoration target (to provide the default/fallback)
	 */
	virtual UWidget* NativeGetDesiredFocusTarget() const;

	/** 
	 * Implement to provide the desired widget to focus if/when this activatable becomes the primary active widget.
	 * Note: This is a fallback used only if the native class parentage does not provide a target.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "ActivatableWidget", Meta = (DisplayName = "Get Desired Focus Target"))
	UWidget* BP_GetDesiredFocusTarget() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "ActivatableWidget", Meta = (DisplayName = "On Activated"))
	void BP_OnActivated();
	virtual void NativeOnActivated();

	UFUNCTION(BlueprintImplementableEvent, Category = "ActivatableWidget", Meta = (DisplayName = "On Deactivated"))
	void BP_OnDeactivated();
	virtual void NativeOnDeactivated();

	virtual void InternalProcessActivation();
	virtual void InternalProcessDeactivation();

protected:
	UPROPERTY(EditAnywhere, Category = "Activation", Meta = (InlineEditConditionToggle = "ActivatedVisibility"))
	bool bSetVisibilityOnActivated = false;

	UPROPERTY(EditAnywhere, Category = "Activation", Meta = (EditCondition = "bSetVisibilityOnActivated"))
	ESlateVisibility ActivatedVisibility = ESlateVisibility::SelfHitTestInvisible;

	UPROPERTY(EditAnywhere, Category = "Activation", Meta = (InlineEditConditionToggle = "DeactivatedVisibility"))
	bool bSetVisibilityOnDeactivated = false;

	UPROPERTY(EditAnywhere, Category = "Activation", Meta = (EditCondition = "bSetVisibilityOnDeactivated"))
	ESlateVisibility DeactivatedVisibility = ESlateVisibility::Collapsed;

private:
	/** Fires when the widget is activated. */
	UPROPERTY(BlueprintAssignable, Category = "Events", Meta = (AllowPrivateAccess = true, DisplayName = "On Widget Activated"))
	FOnWidgetActivationChanged BP_OnWidgetActivated;

	/** Fires when the widget is deactivated. */
	UPROPERTY(BlueprintAssignable, Category = "Events", Meta = (AllowPrivateAccess = true, DisplayName = "On Widget Deactivated"))
	FOnWidgetActivationChanged BP_OnWidgetDeactivated;

	UPROPERTY(BlueprintReadOnly, Category = "ActivatableWidget", Meta = (AllowPrivateAccess = true))
	bool bIsActive = false;

	/** Handle to default back action, if bound */
	mutable FSimpleMulticastDelegate OnActivatedEvent;
	mutable FSimpleMulticastDelegate OnDeactivatedEvent;
};