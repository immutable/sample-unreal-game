#include "Base/ItemListWidget.h"

#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/UniformGridPanel.h"

#include "UI/Base/ItemWidget.h"

int32 UItemListWidget::GetNumberOfColumns() const
{
	return NumberOfColumns;
}

int32 UItemListWidget::GetNumberOfRows() const
{
	return NumberOfRows;
}

class UItemWidget* UItemListWidget::GetItemById(int32 Id)
{
	return CachedItems[Id];
}

UItemWidget* UItemListWidget::GetItemByRowColumn(int32 Row, int32 Column)
{
	return CachedItems[Row * NumberOfColumns + Column];
}

UItemWidget* UItemListWidget::GetSelectedItem() const
{
	return nullptr;
}

void UItemListWidget::ResetPanelItems()
{
	int32 Number = ListPanel->GetChildrenCount();

	for (int32 i = 0; i < Number; ++i)
	{
		if (auto Item = Cast<UItemWidget>(ListPanel->GetChildAt(i)))
		{
			Item->SetOriginalState();
		}
	}
}

TSharedRef<SWidget> UItemListWidget::RebuildWidget()
{
	CachedItems.Reset(NumberOfColumns * NumberOfRows);

	auto OriginalWidget = Super::RebuildWidget();

	TSubclassOf<UItemWidget> ItemWidgetClass = ItemClass.LoadSynchronous();

	if (ItemWidgetClass && ListPanel)
	{
		for (int32 Row = 0; Row < NumberOfRows; ++Row)
		{
			for (int32 Column = 0; Column < NumberOfColumns; ++Column)
			{
				FName ItemWidgetName = *FString::Format(TEXT("ItemWidget_c{0}_r{1}"), {Column, Row});
				UItemWidget* NewItemWidgetObject = CreateWidget<UItemWidget>(this, ItemWidgetClass, ItemWidgetName);

				CachedItems.Add(NewItemWidgetObject);

				//auto UniformGridSlot = ListPanel->AddChildToUniformGrid(NewItemWidgetObject, Row, Column);
				auto GridSlot = ListPanel->AddChildToGrid(NewItemWidgetObject, Row, Column);

				GridSlot->SetPadding(ItemPadding);
				GridSlot->SetHorizontalAlignment(HAlign_Fill);
				GridSlot->SetVerticalAlignment(VAlign_Fill);
			}
		}
	}

	return OriginalWidget;
}