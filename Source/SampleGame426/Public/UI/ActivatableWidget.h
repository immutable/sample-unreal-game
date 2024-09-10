 #pragma once

#include "Blueprint/UserWidget.h"

#include "ActivatableWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWidgetActivationChanged);


UCLASS(meta = (DisableNativeTick))
class UActivatableWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = ActivatableWidget)
	bool IsActivated() const { return bIsActive; }

	UFUNCTION(BlueprintCallable, Category = ActivatableWidget)
	void ActivateWidget();

	UFUNCTION(BlueprintCallable, Category = ActivatableWidget)
	void DeactivateWidget();
	
	/** Returns the desired widget to focus when this Widget Activates. */
	UFUNCTION(BlueprintCallable, Category = ActivatableWidget)
	UWidget* GetDesiredFocusTarget() const;

	FSimpleMulticastDelegate& OnActivated() const { return OnActivatedEvent; }
	FSimpleMulticastDelegate& OnDeactivated() const { return OnDeactivatedEvent; }

public:
	
	bool IsModal() const { return bIsModal; }
	bool SetsVisibilityOnActivated() const { return bSetVisibilityOnActivated; }
	bool SetsVisibilityOnDeactivated() const { return bSetVisibilityOnDeactivated; }

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	/**
	 * Override to provide the desired widget that should receive focus when this becomes the primary active widget.
	 * If bAutoRestoreFocus is true, is only called when there is no valid cached restoration target (to provide the default/fallback)
	 */
	virtual UWidget* NativeGetDesiredFocusTarget() const;
	
	/** 
	 * Implement to provide the desired widget to focus if/when this activatable becomes the primary active widget.
	 * Note: This is a fallback used only if the native class parentage does not provide a target.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = ActivatableWidget, meta = (DisplayName = "Get Desired Focus Target"))
	UWidget* BP_GetDesiredFocusTarget() const;

	UFUNCTION(BlueprintImplementableEvent, Category = ActivatableWidget, meta = (DisplayName = "On Activated"))
	void BP_OnActivated();
	virtual void NativeOnActivated();

	UFUNCTION(BlueprintImplementableEvent, Category = ActivatableWidget, meta = (DisplayName = "On Deactivated"))
	void BP_OnDeactivated();
	virtual void NativeOnDeactivated();

	/** 
	 * Override in BP implementations to provide custom behavior when receiving a back action 
	 * Note: Only called if native code in the base class hasn't handled it in NativeOnHandleBackAction 
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = ActivatableWidget, meta = (DisplayName = "On Handle Back Action"))
	bool BP_OnHandleBackAction();
	virtual bool NativeOnHandleBackAction();

	void HandleBackAction();

	/** True to receive "Back" actions automatically. Custom back handler behavior can be provided, default is to deactivate. */
	UPROPERTY(EditAnywhere, Category = Back)
	bool bIsBackHandler = false;

	/** True to receive "Back" actions automatically. Custom back handler behavior can be provided, default is to deactivate. */
	UPROPERTY(EditAnywhere, Category = Back)
	bool bIsBackActionDisplayedInActionBar = false;

	/** True to automatically activate upon construction */
	UPROPERTY(EditAnywhere, Category = Activation)
	bool bAutoActivate = false;

	/** 
	 * True to have this widget be treated as a root node for input routing, regardless of its actual parentage.
	 * Should seldom be needed, but useful in cases where a child widget should prevent all action processing by parents, even though they remain active (ex: modal popup menu).
	 */
	UPROPERTY(EditAnywhere, Category = Activation, meta = (EditCondition = bSupportsActivationFocus))
	bool bIsModal = false;

private:
	/** Fires when the widget is activated. */
	UPROPERTY(BlueprintAssignable, Category = Events, meta = (AllowPrivateAccess = true, DisplayName = "On Widget Activated"))
	FOnWidgetActivationChanged BP_OnWidgetActivated;
	
	/** Fires when the widget is deactivated. */
	UPROPERTY(BlueprintAssignable, Category = Events, meta = (AllowPrivateAccess = true, DisplayName = "On Widget Deactivated"))
	FOnWidgetActivationChanged BP_OnWidgetDeactivated;
	
	UPROPERTY(BlueprintReadOnly, Category = ActivatableWidget, meta = (AllowPrivateAccess = true))
	bool bIsActive = false;

	/** True if we should switch to activated visibility only when all bound widgets are active */
	bool bAllActive = true;

	/** Handle to default back action, if bound */
	// FUIActionBindingHandle DefaultBackActionHandle;
	mutable FSimpleMulticastDelegate OnActivatedEvent;
	mutable FSimpleMulticastDelegate OnDeactivatedEvent;

protected:
	
	UPROPERTY(EditAnywhere, Category = Activation, meta = (InlineEditConditionToggle = "ActivatedVisibility"))
	bool bSetVisibilityOnActivated = false;

	UPROPERTY(EditAnywhere, Category = Activation, meta = (EditCondition = "bSetVisibilityOnActivated"))
	ESlateVisibility ActivatedVisibility = ESlateVisibility::SelfHitTestInvisible;

	UPROPERTY(EditAnywhere, Category = Activation, meta = (InlineEditConditionToggle = "DeactivatedVisibility"))
	bool bSetVisibilityOnDeactivated = false;

	UPROPERTY(EditAnywhere, Category = Activation, meta = (EditCondition = "bSetVisibilityOnDeactivated"))
	ESlateVisibility DeactivatedVisibility = ESlateVisibility::Collapsed;
	
	virtual void InternalProcessActivation();
	virtual void InternalProcessDeactivation();
	void Reset();
};