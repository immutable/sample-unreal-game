#include "Marketplace/MarketplaceWidget.h"

#include "LogSampleGame.h"
#include "OpenAPISearchStacksResult.h"
#include "Online/ImmutableQuery.h"
#include "Base/ItemWidget.h"


void UMarketplaceWidget::RefreshItemList()
{
	if (!bInitialized)
	{
		return;
	}

	ImmutableQuery::ExecuteQuery(BuildRequestData(TEXT("")), FOnImmutableQueryComplete::CreateLambda([this] (bool Success, TSharedPtr<OpenAPI::Model> Result) 
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

TSharedPtr<ImmutableQuery::FMP_SearchStacksRequestData> UMarketplaceWidget::BuildRequestData(const FString& PageCursor)
{
	TSharedPtr<ImmutableQuery::FMP_SearchStacksRequestData> Data = MakeShareable(new ImmutableQuery::FMP_SearchStacksRequestData());

	//Data.AccountAddress = TEXT("0x8c864b96826f3b897cc125a23bc93ab3ebb173ab");
	Data->ContactAddress = { TEXT("0xcdbee7935e1b0eaabdee64219182602df0d8d094") };
	Data->PageSize = PageSize;
	Data->PageCursor = PageCursor;

	return Data;
}

void UMarketplaceWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	int32 TotalNumberItems = ListPanel->GetNumberOfColumns() * ListPanel->GetNumberOfRows();

	PageSize = TotalNumberItems;// + (10 - TotalNumberItems % 10); 
	
	RefreshItemList();
}
