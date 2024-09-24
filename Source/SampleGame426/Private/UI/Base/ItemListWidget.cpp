#include "Base/ItemListWidget.h"

#include "Base/ItemWidget.h"
#include "Components/UniformGridPanel.h"


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

int32 UItemListWidget::GetNumberOfColumns() const
{
	return NumberOfColumns;
}

int32 UItemListWidget::GetNumberOfRows() const
{
	return NumberOfRows;
}

class UItemWidget* UItemListWidget::GetItem(int32 id)
{
	return CachedItems[id];
}

UItemWidget* UItemListWidget::GetItem(int32 Column, int32 Row)
{
	return CachedItems[Row * NumberOfColumns + Column];
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
				ListPanel->AddChildToUniformGrid(NewItemWidgetObject, Row, Column);
			}
		}
	}

	return OriginalWidget;
}

void UItemListWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
