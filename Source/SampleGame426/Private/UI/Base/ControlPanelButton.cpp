#include "Base/ControlPanelButton.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Base/ActivatableWidgetWithControlPanels.h"

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

bool UControlPanelButton::IsEnabled() const
{
	return bIsEnabled;
}

void UControlPanelButton::SetEnable(bool bNewIsEnabled)
{
	if (bIsEnabled == bNewIsEnabled)
	{
		return;
	}
	bIsEnabled = bNewIsEnabled;
	BP_OnActivationStatusChanged(bNewIsEnabled);
}

void UControlPanelButton::SetIcon(const FSlateBrush& NewIcon)
{
	if (Icon)
	{
		Icon->SetBrush(NewIcon);
	}
}

void UControlPanelButton::SetButtonTag(FGameplayTag& NewButtonTag)
{
	ButtonTag = NewButtonTag;
}

void UControlPanelButton::SetName(const FText& NewName)
{
	if (ButtonName)
	{
		ButtonName->SetText(NewName);
	}
}

void UControlPanelButton::Show()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UControlPanelButton::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UControlPanelButton::RegisterOnClick(const FOnControlPanelButtonClick& InOnControlPanelButtonClick)
{
	OnControlPanelButtonClickDelegate = InOnControlPanelButtonClick;
}

FReply UControlPanelButton::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (bIsEnabled)
	{
		OnControlPanelButtonClickDelegate.ExecuteIfBound(ButtonTag);
	}

	return Reply;
}

void UControlPanelButton::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (bIsEnabled)
	{
		BP_OnHovered();
	}
}

void UControlPanelButton::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if (bIsEnabled)
	{
		BP_OnUnhovered();
	}
}