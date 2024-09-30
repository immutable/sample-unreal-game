#include "Base/ControlPanelButton.h"

#include "Base/ActivatableWidgetWithControlPanels.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UControlPanelButton::SetIcon(const FSlateBrush& InBrush)
{
	if (Icon)
	{
		Icon->SetBrush(InBrush);
	}
}

void UControlPanelButton::SetIconColor(const FLinearColor& InColor)
{
	if (Icon)
	{
		Icon->SetBrushTintColor(InColor);
	}
}

void UControlPanelButton::SetButtonTag(FGameplayTag& InTag)
{
	ButtonTag = InTag;
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

void UControlPanelButton::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UControlPanelButton::Show()
{
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
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
