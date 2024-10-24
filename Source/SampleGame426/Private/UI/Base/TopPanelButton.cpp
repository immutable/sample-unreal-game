#include "Base/TopPanelButton.h"

void UTopPanelButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Hide();
}

int32 UTopPanelButton::GetIndex() const
{
	return ButtonIndex;
}

void UTopPanelButton::SetIndex(int32 NewIndex)
{
	ButtonIndex = NewIndex;
}

void UTopPanelButton::Show()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UTopPanelButton::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

FReply UTopPanelButton::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	BP_OnClick();
	OnClickDelegate.ExecuteIfBound(this);

	return Reply;
}

void UTopPanelButton::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	BP_OnHovered();
}

void UTopPanelButton::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	BP_OnUnhovered();
}