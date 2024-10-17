#include "Base/ControlPanelButton.h"

#include "Base/ActivatableWidgetWithControlPanels.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

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

void UControlPanelButton::SetName(const FText& InName)
{
	if (ButtonName)
	{
		ButtonName->SetText(InName);
	}
}

void UControlPanelButton::Enable()
{
	ButtonHitbox->SetIsEnabled(true);
	BP_OnActivationStatusChanged(true);
}

void UControlPanelButton::Disable()
{
	ButtonHitbox->SetIsEnabled(false);
	BP_OnActivationStatusChanged(false);
}

bool UControlPanelButton::IsEnabled()
{
	return ButtonHitbox->GetIsEnabled();
}

void UControlPanelButton::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UControlPanelButton::Show()
{
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

bool UControlPanelButton::IsButtonEnabled() const
{
	return ButtonHitbox->GetIsEnabled();
}

bool UControlPanelButton::Initialize()
{
	bool IsInitialized = Super::Initialize();

	if (IsInitialized)
	{
		ButtonTag = FGameplayTag::RequestGameplayTag(TEXT("UI.ControlPanel.Button.Empty"));
		ButtonHitbox->OnClicked.AddUniqueDynamic(this, &UControlPanelButton::HandleButtonClicked);
		Show();
		Disable();
	}
	
	return IsInitialized;
}

void UControlPanelButton::NativeDestruct()
{
	OnPanelButtonClicked.Clear();
	
	Super::NativeDestruct();
}

void UControlPanelButton::HandleButtonClicked()
{
	OnPanelButtonClicked.Broadcast(ButtonTag);
}
