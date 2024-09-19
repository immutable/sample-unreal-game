#include "Marketplace/MarketplaceWidget.h"

#include "IContentBrowserSingleton.h"
#include "LogSampleGame.h"
#include "OpenAPISearchStacksResult.h"
#include "Online/ImmutableQuery.h"
#include "Base/ItemWidget.h"
#include "Settings/SampleGameSettings.h"


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

	auto RequestData = BuildRequestData(TEXT(""), TEXT(""));
	
	ImmutableQuery::ExecuteQuery<ImmutableQuery::FMP_SearchStacksRequestData>(RequestData, FOnImmutableQueryComplete::CreateLambda([this] (bool Success, TSharedPtr<OpenAPI::Model> Result) 
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

TSharedPtr<ImmutableQuery::FMP_SearchStacksRequestData> UMarketplaceWidget::BuildRequestData(const FString& PageCursor, const FString& Account) const
{
	auto Settings = GetDefault<USampleGameSettings>();

	if (!Settings->ContractAddress.Num())
	{
		UE_LOG(LogSampleGame, Error, TEXT("Immutable Settings: List of contact addresses are empty"));

		return nullptr;
	}

	TSharedPtr<ImmutableQuery::FMP_SearchStacksRequestData> Data = MakeShareable(new ImmutableQuery::FMP_SearchStacksRequestData());

	if (!Account.IsEmpty())
	{
		Data->AccountAddress = Account;	
	}
	
	Data->ContactAddress = Settings->ContractAddress;
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
