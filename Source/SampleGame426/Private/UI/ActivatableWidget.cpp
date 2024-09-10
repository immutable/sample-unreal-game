
#include "ActivatableWidget.h"

#include "LogImmutableUI.h"


void UActivatableWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// if (bIsBackHandler)
	// {
	// 	FBindUIActionArgs BindArgs(ICommonInputModule::GetSettings().GetDefaultBackAction(), FSimpleDelegate::CreateUObject(this, &UActivatableWidget::HandleBackAction));
	// 	BindArgs.bDisplayInActionBar = bIsBackActionDisplayedInActionBar;
	//
	// 	DefaultBackActionHandle = RegisterUIActionBinding(BindArgs);
	// }

	if (bAutoActivate)
	{
		UE_LOG(LogImmutableUI, Verbose, TEXT("[%s] auto-activated"), *GetName());
		ActivateWidget();
	}
}

void UActivatableWidget::NativeDestruct()
{
	if (UGameInstance* GameInstance = GetGameInstance<UGameInstance>())
	{
		// Deactivations might rely on members of the game instance to validly run.
		// If there's no game instance, any cleanup done in Deactivation will be irrelevant; we're shutting down the game
		DeactivateWidget();
	}
	Super::NativeDestruct();

	// if (DefaultBackActionHandle.IsValid())
	// {
	// 	DefaultBackActionHandle.Unregister();
	// }
}

UWidget* UActivatableWidget::GetDesiredFocusTarget() const
{
	return NativeGetDesiredFocusTarget();
}

UWidget* UActivatableWidget::NativeGetDesiredFocusTarget() const
{
	return BP_GetDesiredFocusTarget();
}

void UActivatableWidget::ActivateWidget()
{
	if (!bIsActive)
	{
		InternalProcessActivation();
	}
}

void UActivatableWidget::InternalProcessActivation()
{
	UE_LOG(LogImmutableUI, Verbose, TEXT("[%s] -> Activated"), *GetName());

	bIsActive = true;
	NativeOnActivated();
}

void UActivatableWidget::DeactivateWidget()
{
	if (bIsActive)
	{
		InternalProcessDeactivation();
	}
}

void UActivatableWidget::InternalProcessDeactivation()
{
	UE_LOG(LogImmutableUI, Verbose, TEXT("[%s] -> Deactivated"), *GetName());

	bIsActive = false;
	NativeOnDeactivated();
}

void UActivatableWidget::NativeOnActivated()
{
	if (ensureMsgf(bIsActive, TEXT("[%s] has called NativeOnActivated, but isn't actually activated! Never call this directly - call ActivateWidget()")))
	{
		if (bSetVisibilityOnActivated)
		{
			SetVisibility(ActivatedVisibility);
			UE_LOG(LogImmutableUI, Verbose, TEXT("[%s] set visibility to [%s] on activation"), *GetName(), *StaticEnum<ESlateVisibility>()->GetDisplayValueAsText(ActivatedVisibility).ToString());
		}

		BP_OnActivated();
		BP_OnWidgetActivated.Broadcast();
	}
}

void UActivatableWidget::NativeOnDeactivated()
{
	if (ensure(!bIsActive))
	{
		if (bSetVisibilityOnDeactivated)
		{
			SetVisibility(DeactivatedVisibility);
			UE_LOG(LogImmutableUI, Verbose, TEXT("[%s] set visibility to [%d] on deactivation"), *GetName(), *StaticEnum<ESlateVisibility>()->GetDisplayValueAsText(DeactivatedVisibility).ToString());
		}

		BP_OnDeactivated();
		BP_OnWidgetDeactivated.Broadcast();
	}
}

bool UActivatableWidget::NativeOnHandleBackAction()
{
	if (bIsBackHandler)
	{
		if (!BP_OnHandleBackAction())
		{
			// Default behavior is unconditional deactivation
			UE_LOG(LogImmutableUI, Verbose, TEXT("[%s] handled back with default implementation. Deactivating immediately."), *GetName());
			DeactivateWidget();
		}
		return true;
	}
	return false;
}

void UActivatableWidget::HandleBackAction()
{
	NativeOnHandleBackAction();
}

void UActivatableWidget::Reset()
{
	bIsActive = false;

	BP_OnWidgetActivated.Clear();
	BP_OnWidgetDeactivated.Clear();
}

