#include "Base/ItemListWidget.h"

#include "Base/ItemWidget.h"
#include "Components/UniformGridPanel.h"


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

	if (ensure(ItemWidgetClass && ListPanel) )
	{
		for (int32 Column = 0; Column < NumberOfColumns; ++Column)
		{
			for (int32 Row = 0; Row < NumberOfRows; ++Row)
			{
				FName ItemWidgetName = *FString::Format(TEXT("ItemWidget_c{0}_r{1}"), {Column, Row});
				UItemWidget* NewItemWidgetObject = CreateWidget<UItemWidget>(this, ItemWidgetClass, ItemWidgetName);

				CachedItems.Add(NewItemWidgetObject);
				ListPanel->AddChildToUniformGrid(NewItemWidgetObject, Column, Row);
				NewItemWidgetObject->SetVisibility(ESlateVisibility::Hidden);
#if WITH_EDITOR
				// In editor, always make visible all items to ease design 
				if (IsDesignTime())
				{
					NewItemWidgetObject->SetVisibility(ESlateVisibility::Visible);
				}
#endif
			}
		}
	}

	return OriginalWidget;
}

void UItemListWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
