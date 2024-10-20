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

void UControlPanelButton::SetEnable(bool IsEnabled)
{
	if (bIsEnabled == IsEnabled)
	{
		return;
	}
	bIsEnabled = IsEnabled;
	BP_OnActivationStatusChanged(IsEnabled);
}

bool UControlPanelButton::IsEnabled()
{
	return bIsEnabled;
}

void UControlPanelButton::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UControlPanelButton::Show()
{
	SetVisibility(ESlateVisibility::Visible);
}

bool UControlPanelButton::Initialize()
{
	bool IsInitialized = Super::Initialize();

	if (IsInitialized)
	{
		ButtonTag = FGameplayTag::RequestGameplayTag(TEXT("UI.ControlPanel.Button.Empty"));
		Show();
		SetEnable(false);
	}
	
	return IsInitialized;
}

void UControlPanelButton::RegisterOnClick(const FOnControlPanelButtonClick& InOnControlPanelButtonClick)
{
	OnControlPanelButtonClickDelegate = InOnControlPanelButtonClick;
}

void UControlPanelButton::NativeDestruct()
{
	Super::NativeDestruct();
}

void UControlPanelButton::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	BP_OnHovered();
}

void UControlPanelButton::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	BP_OnUnhovered();
}

FReply UControlPanelButton::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	OnControlPanelButtonClickDelegate.ExecuteIfBound(ButtonTag);

	return Reply;
}

FReply UControlPanelButton::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
}

void UControlPanelButton::HandleButtonClicked()
{

}
