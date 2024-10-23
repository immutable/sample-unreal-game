#include "Base/ActivatableWidget.h"

#include "LogSampleGame.h"

void UActivatableWidget::Reset()
{
	bIsActive = false;

	BP_OnWidgetActivated.Clear();
	BP_OnWidgetDeactivated.Clear();
}

bool UActivatableWidget::CanBeReleased() const
{
	return !bIsActive;
}

bool UActivatableWidget::IsActivated() const
{
	return bIsActive;
}

UWidget* UActivatableWidget::GetDesiredFocusTarget() const
{
	return NativeGetDesiredFocusTarget();
}

FSimpleMulticastDelegate& UActivatableWidget::OnActivated() const
{
	return OnActivatedEvent;
}

FSimpleMulticastDelegate& UActivatableWidget::OnDeactivated() const
{
	return OnDeactivatedEvent;
}

bool UActivatableWidget::SetsVisibilityOnActivated() const
{
	return bSetVisibilityOnActivated;
}

bool UActivatableWidget::SetsVisibilityOnDeactivated() const
{
	return bSetVisibilityOnDeactivated;
}

void UActivatableWidget::ActivateWidget()
{
	if (!bIsActive)
	{
		InternalProcessActivation();
	}
}

void UActivatableWidget::DeactivateWidget()
{
	if (bIsActive)
	{
		InternalProcessDeactivation();
	}
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

UWidget* UActivatableWidget::NativeGetDesiredFocusTarget() const
{
	return BP_GetDesiredFocusTarget();
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

void UActivatableWidget::InternalProcessActivation()
{
	UE_LOG(LogSampleGame, Verbose, TEXT("[%s] -> Activated"), *GetName());

	bIsActive = true;
	NativeOnActivated();
}

void UActivatableWidget::InternalProcessDeactivation()
{
	UE_LOG(LogSampleGame, Verbose, TEXT("[%s] -> Deactivated"), *GetName());

	bIsActive = false;
	NativeOnDeactivated();
}