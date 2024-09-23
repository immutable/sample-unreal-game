#include "Marketplace/SearchStacksWidget.h"

#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "IContentBrowserSingleton.h"
#include "OpenAPISearchApiOperations.h"
#include "UI/Marketplace/MarketplacePolicy.h"
#include "Base/ItemWidget.h"


void USearchStacksWidget::RefreshItemList()
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
	Policy->GetOpenAPISearchApi()->SearchStacks(*Policy->GetSearchStacksRequest(), ImmutableOpenAPI::OpenAPISearchApi::FSearchStacksDelegate::CreateUObject(this, &USearchStacksWidget::OnSearchStacksResponse));
}

void USearchStacksWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	RefreshItemList();
}

void USearchStacksWidget::OnSearchStacksResponse(const ImmutableOpenAPI::OpenAPISearchApi::SearchStacksResponse& Response)
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