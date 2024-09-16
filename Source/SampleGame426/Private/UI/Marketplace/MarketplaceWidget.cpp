#include "Marketplace/MarketplaceWidget.h"

#include "IContentBrowserSingleton.h"
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

	if (!ListPanel)
	{
		return;
	}
	
	ImmutableQuery::ExecuteQuery<ImmutableQuery::FMP_SearchStacksRequestData>(BuildRequestData(TEXT("")), FOnImmutableQueryComplete::CreateLambda([this] (bool Success, TSharedPtr<OpenAPI::Model> Result) 
	{
		if (!Success)
		{
			// TODO handle system error
			return;
		}

		auto Data = StaticCastSharedPtr<OpenAPI::OpenAPISearchStacksResult>(Result);

		if (!Data.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("Received stack json data cannot be converted to OpenAPISearchStacksResult"));
			return;
		}
		
		int32 NumberOfColumns = ListPanel->GetNumberOfColumns();
		int32 NumberOfRows = ListPanel->GetNumberOfRows();
		int32 NumberOfResults = Data->Result.Num();

		for (int32 ResultId = 0; ResultId < NumberOfResults; ResultId++)
		{
			int32 Row = ResultId / NumberOfColumns;
			int32 Column = ResultId - Row * NumberOfColumns;
			auto ItemWidget = ListPanel->GetItem(Column, Row);

			ItemWidget->ProcessModel(&Data->Result[ResultId]);
			
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
