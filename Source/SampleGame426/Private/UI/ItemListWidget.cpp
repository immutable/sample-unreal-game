#include "ItemListWidget.h"

#include "ItemWidget.h"
#include "Components/UniformGridPanel.h"


void UItemListWidget::RefreshItemList()
{
	FillGrid();
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
#if WITH_EDITOR
				// In editor, always make visible all items to ease design 
				if (!IsDesignTime())
				{
					NewItemWidgetObject->SetVisibility(ESlateVisibility::Visible);
				}
#else
				NewItemWidgetObject->SetVisibility(ESlateVisibility::Hidden);
#endif
			}
		}
	}

	return OriginalWidget;
}

void UItemListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FillGrid();
}

void UItemListWidget::FillGrid()
{
	if (!bInitialized)
	{
		return;
	}
	
	for (int32 Column = 0; Column < NumberOfColumns; ++Column)
	{
		for (int32 Row = 0; Row < NumberOfRows; ++Row)
		{
			auto ItemWidget = CachedItems[Column * NumberOfRows + Row];

			// ItemWidget->SetName();
			// ItemWidget->SetPrice();
			// ItemWidget->SetTextureNFT();
		}
	}
}