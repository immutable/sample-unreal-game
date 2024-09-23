#include "Marketplace/MarketplaceStacksWidget.h"

#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "IContentBrowserSingleton.h"
#include "OpenAPISearchApiOperations.h"
#include "UI/Marketplace/MarketplacePolicy.h"
#include "Base/ItemWidget.h"


void UMarketplaceStacksWidget::RefreshItemList()
{
	if (!bInitialized)
	{
		return;
	}

	if (!ListPanel)
	{
		return;
	}

	UMarketplacePolicy* Policy = GetOwningCustomLocalPLayer()->GetGameUIPolicy()->GetMarketplacePolicy();

	if (!Policy)
	{
		return;
	}

	Policy->SetPageSize(ListPanel->GetNumberOfColumns() * ListPanel->GetNumberOfRows());
	Policy->GetOpenAPISearchApi()->SearchStacks(*Policy->GetSearchStacksRequest(), ImmutableOpenAPI::OpenAPISearchApi::FSearchStacksDelegate::CreateUObject(this, &UMarketplaceStacksWidget::OnSearchStacksResponse));
	
	// ImmutableQuery::ExecuteQuery<ImmutableQuery::FMP_SearchStacksRequestData>(RequestData, FOnImmutableQueryComplete::CreateLambda([this] (bool Success, TSharedPtr<OpenAPI::Model> Result) 
	// {
	// 	if (!Success)
	// 	{
	// 		// TODO handle system error
	// 		return;
	// 	}
	//
	// 	auto Data = StaticCastSharedPtr<OpenAPI::OpenAPISearchStacksResult>(Result);
	//
	// 	if (!Data.IsValid())
	// 	{
	// 		UE_LOG(LogTemp, Error, TEXT("Received stack json data cannot be converted to OpenAPISearchStacksResult"));
	// 		return;
	// 	}
	// 	
	// 	int32 NumberOfColumns = ListPanel->GetNumberOfColumns();
	// 	int32 NumberOfRows = ListPanel->GetNumberOfRows();
	// 	int32 NumberOfResults = Data->Result.Num();
	//
	// 	for (int32 ResultId = 0; ResultId < NumberOfResults; ResultId++)
	// 	{
	// 		int32 Row = ResultId / NumberOfColumns;
	// 		int32 Column = ResultId - Row * NumberOfColumns;
	// 		auto ItemWidget = ListPanel->GetItem(Column, Row);
	//
	// 		ItemWidget->ProcessModel(&Data->Result[ResultId]);
	// 	}
	// }));
}

void UMarketplaceStacksWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	RefreshItemList();
}

void UMarketplaceStacksWidget::OnSearchStacksResponse(const ImmutableOpenAPI::OpenAPISearchApi::SearchStacksResponse& Response)
{
	if (Response.IsSuccessful())
	{
		int32 NumberOfColumns = ListPanel->GetNumberOfColumns();
		int32 NumberOfRows = ListPanel->GetNumberOfRows();
		int32 NumberOfResults = Response.Content.Result.Num();

		for (int32 ResultId = 0; ResultId < NumberOfResults; ResultId++)
		{
			int32 Row = ResultId / NumberOfColumns;
			int32 Column = ResultId - Row * NumberOfColumns;
			auto ItemWidget = ListPanel->GetItem(Column, Row);

			ItemWidget->ProcessModel(Response.Content.Result[ResultId]);
		}
	}
}