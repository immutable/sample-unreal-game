
#include "Base/ActivatableWidget.h"

#include "LogSampleGame.h"


bool UActivatableWidget::CanBeReleased() const
{
	return !bIsActive;
}

void UActivatableWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ActivateWidget();
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
	UE_LOG(LogSampleGame, Verbose, TEXT("[%s] -> Activated"), *GetName());

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
	UE_LOG(LogSampleGame, Verbose, TEXT("[%s] -> Deactivated"), *GetName());

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
			UE_LOG(LogSampleGame, Verbose, TEXT("[%s] set visibility to [%s] on activation"), *GetName(), *StaticEnum<ESlateVisibility>()->GetDisplayValueAsText(ActivatedVisibility).ToString());
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
			UE_LOG(LogSampleGame, Verbose, TEXT("[%s] set visibility to [%d] on deactivation"), *GetName(), *StaticEnum<ESlateVisibility>()->GetDisplayValueAsText(DeactivatedVisibility).ToString());
		}

		BP_OnDeactivated();
		BP_OnWidgetDeactivated.Broadcast();
	}
}

void UActivatableWidget::Reset()
{
	bIsActive = false;

	BP_OnWidgetActivated.Clear();
	BP_OnWidgetDeactivated.Clear();
}

