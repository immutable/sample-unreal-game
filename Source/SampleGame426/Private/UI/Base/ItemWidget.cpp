#include "Base/ItemWidget.h"

void UItemWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UItemWidget::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UItemWidget::SetOriginalState()
{
	Hide();

#if WITH_EDITOR
	// In editor, always make visible all items to ease design 
	if (IsDesignTime())
	{
		Show();
	}
#endif
}

void UItemWidget::SetSelection(bool IsSelected)
{
	bIsSelected = IsSelected;
	BP_OnSelectionChange(bIsSelected);
	OnSelectionChangeDelegate.Execute(bIsSelected, this);
}

void UItemWidget::RegisterOnSelectionChange(const FOnSelectionChange& InOnSelectionChangeDelegate)
{
	OnSelectionChangeDelegate = InOnSelectionChangeDelegate;
}

void UItemWidget::RegisterOnDoubleClick(const FOnDoubleClick& InOnDoubleClickDelegate)
{
	OnDoubleClickDelegate = InOnDoubleClickDelegate;
}

bool UItemWidget::Initialize()
{
	bool Result = Super::Initialize();

	if (!IsDesignTime())
	{
		SetOriginalState();
	}

	return Result;
}

FReply UItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	SetSelection(!bIsSelected);
	OnClick();

	return Reply;
}

FReply UItemWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	auto Reply = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);

	SetSelection(true);
	OnDoubleClick();
	OnDoubleClickDelegate.ExecuteIfBound(this);

	return Reply;
}
