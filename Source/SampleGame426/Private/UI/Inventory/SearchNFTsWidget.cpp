#include "Inventory/SearchNFTsWidget.h"

#include "CustomGameInstance.h"
#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "UIGameplayTags.h"
#include "Base/ItemWidget.h"
#include "ImmutableIndexerSearchAPI/Public/OpenAPIStacksApiOperations.h"
#include "Marketplace/MarketplacePolicy.h"
#include "UI/Interfaces/IOpenAPIProcessorInterface.h"


void USearchNfTsWidget::RefreshItemList(TOptional<FString> PageCursor)
{
	if (!bInitialized)
	{
		return;
	}

	if (!ListPanel)
	{
		return;
	}
	
	ListPanel->ResetPanelItems();

	UMarketplacePolicy* Policy = GetOwningCustomLocalPLayer()->GetGameUIPolicy()->GetMarketplacePolicy();

	if (!Policy)
	{
		return;
	}

	Policy->SetPageSize(ListPanel->GetNumberOfColumns() * ListPanel->GetNumberOfRows());
	Policy->SetPageCursor(PageCursor);
	Policy->SetAccount(GetOwningCustomLocalPLayer()->GetPassportWalletAddress());
	Policy->GetIndexerStacksAPI()->SearchNFTs(*Policy->GetIndexerStacksAPI_SearchNfTsRequest(), ImmutableIndexerSearchAPI::OpenAPIStacksApi::FSearchNFTsDelegate::CreateUObject(this, &USearchNfTsWidget::OnSearchNFTsResponse));
}

void USearchNfTsWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	RefreshItemList(TOptional<FString>());
}

void USearchNfTsWidget::SetupControlButtons(TMap<FGameplayTag, UControlPanelButton*>& Buttons)
{
	Super::SetupControlButtons(Buttons);
}

void USearchNfTsWidget::OnSearchNFTsResponse(const ImmutableIndexerSearchAPI::OpenAPIStacksApi::SearchNFTsResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::ErrorFull, UDialogSubsystem::CreateErrorDescriptorWithErrorText(TEXT("Error"), TEXT("Failed to acquire search NFTs result"), Response.GetResponseString()));
		
		return;
	}

	int32 NumberOfColumns = ListPanel->GetNumberOfColumns();
	// int32 NumberOfRows = ListPanel->GetNumberOfRows();
	int32 NumberOfResults = Response.Content.Result.Num();

	HandlePageData(Response.Content.Page);
	for (int32 ResultId = 0; ResultId < NumberOfResults; ResultId++)
	{
		int32 Row = ResultId / NumberOfColumns;
		int32 Column = ResultId - Row * NumberOfColumns;
		if (auto ItemWidget = Cast<IInventoryOpenAPIProcessorInterface>(ListPanel->GetItem(Column, Row)))
		{
			ItemWidget->ProcessModel(Response.Content.Result[ResultId]);	
		}
	}
}

void USearchNfTsWidget::HandlePageData(const ImmutableIndexerSearchAPI::OpenAPIPage& PageData)
{
	PageCursors = PageData;

	if (NextPageButton)
	{
		PageCursors.NextCursor.IsSet() ? NextPageButton->Show() : NextPageButton->Hide();	
	}
	if (PreviousPageButton)
	{
		PageCursors.PreviousCursor.IsSet() ? PreviousPageButton->Show() : PreviousPageButton->Hide();
	}
}
