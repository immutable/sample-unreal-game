#include "Base/ControlPanelButton.h"

#include "Base/ActivatableWidgetWithControls.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UControlPanelButton::SetIcon(const FSlateBrush& InBrush)
{
	if (Icon)
	{
		Icon->SetBrush(InBrush);
	}
}

void UControlPanelButton::SetButtonTag(FGameplayTag& InTag)
{
	ButtonTag = InTag;
}

void UControlPanelButton::Enable()
{
}

void UControlPanelButton::Disable()
{
}

bool UControlPanelButton::Initialize()
{
	bool IsInitialized = Super::Initialize();

	if (IsInitialized)
	{
		ButtonTag = FGameplayTag::RequestGameplayTag(TEXT("UI.ControlPanel.Button.Empty"));
		ButtonHitbox->OnClicked.AddUniqueDynamic(this, &UControlPanelButton::HandleButtonClicked);
	}
	
	return IsInitialized;
}

void UControlPanelButton::HandleButtonClicked()
{
	if (UActivatableWidgetWithControls* ControlPanel = Cast<UActivatableWidgetWithControls>(GetOuter()->GetOuter()))
	{
		ControlPanel->OnControlButtonClicked(ButtonTag);
	}
}