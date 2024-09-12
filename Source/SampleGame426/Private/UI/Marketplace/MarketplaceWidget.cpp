#include "Marketplace/MarketplaceWidget.h"

#include "Marketplace.h"
#include "Base/ItemWidget.h"


void UMarketplaceWidget::RefreshItemList()
{
	if (!bInitialized)
	{
		return;
	}

	FMarketplaceRequestData Data;

	Data.AccountAddress = TEXT("0x8c864b96826f3b897cc125a23bc93ab3ebb173ab");
	Data.ContactAddress = { TEXT("0xcdbee7935e1b0eaabdee64219182602df0d8d094") };
	Data.PageSize = 10;

	FMarketplace::QueryStacks(Data, FOnHttpRequestComplete::CreateLambda([this](bool Success)
	{
		if (Success && ListPanel)
		{
			auto NumberOfColumns = ListPanel->GetNumberOfColumns();
			auto NumberOfRows = ListPanel->GetNumberOfRows();
			
			for (int32 Column = 0; Column < NumberOfColumns; ++Column)
			{
				for (int32 Row = 0; Row < NumberOfRows; ++Row)
				{
					auto ItemWidget = ListPanel->GetItem(Column, Row);

					// ItemWidget->SetName();
					// ItemWidget->SetPrice();
					// ItemWidget->SetTextureNFT();
				}
			}
		}
	}));
}

void UMarketplaceWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	RefreshItemList();
}
