#include "Marketplace/SearchStacksWidget.h"

#include "CustomGameInstance.h"
#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "OpenAPIStacksApiOperations.h"
#include "UIGameplayTags.h"
#include "Base/AWStackWithControlPanels.h"
#include "UI/Marketplace/MarketplacePolicy.h"
#include "Base/ItemWidget.h"
#include "Dialog/DialogSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Marketplace/SearchStacksListingWidget.h"
#include "Marketplace/StackItemWidget.h"
#include "UI/Interfaces/IOpenAPIProcessorInterface.h"


void USearchStacksWidget::RefreshItemList(TOptional<FString> PageCursor)
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

	/**
	 * Step 1(Marketplace display): Constructs and sends a search stack request to the Immutable OpenAPI in order to obtain listed NFTs in the marketplace.
	 * In order to display items in the list panel of the marketplace, we need to send a search request to the Immutable OpenAPI.
	 * Some request parameters are populated based on the current state of the UI Marketplace policy settings.
	 * @see UMarketplacePolicy
	 * @details This function initializes a SearchStacksRequest object with various parameters
	 * such as page size, page cursor, account address, contract address, chain name,
	 * and active listings filter. It also handles sorting and optional keyword and trait
	 * filters. Finally, it sends the request to the Stacks API and binds the response
	 * to the OnSearchStacksResponse handler.
	 *
	 * @param SearchStacksRequest The request object to be passed to SearchStacks method of the Immutable OpenAPI.
	 * Must-be parameters:
	 * - AccountAddress: The wallet address of the owning custom local player.
	 * - ContractAddress: The contract address of NFT we are searching for, retrieved from the policy.
	 * - ChainName: The name of the blockchain chain .
	 * Optional parameters:
	 * - PageSize: The number of items per page, calculated based on the number of columns and rows in the ListPanel.
	 * - PageCursor: The cursor for pagination.
	 * - OnlyIfHasActiveListings: A boolean flag indicating if only active listings should be included.
	 * - SortBy: The sorting criteria, specified as an enumeration.
	 * - Keyword: The keyword for the search, if cached in the policy.
	 * - Trait: The traits or metadata criteria for the search, if cached in the policy.
	 *
	 * The search request is sent using the ImmutableOpenAPI::OpenAPIStacksApi, and the response is bound to the USearchStacksWidget::OnSearchStacksResponse method.
	 */
	ImmutableOpenAPI::OpenAPIStacksApi::SearchStacksRequest SearchStacksRequest;

	SearchStacksRequest.PageSize = ListPanel->GetNumberOfColumns() * ListPanel->GetNumberOfRows();
	SearchStacksRequest.PageCursor = PageCursor;
	SearchStacksRequest.AccountAddress = GetOwningCustomLocalPLayer()->GetPassportWalletAddress();
	SearchStacksRequest.ContractAddress = Policy->GetContracts();
	SearchStacksRequest.ChainName = Policy->GetChainName();
	SearchStacksRequest.OnlyIfHasActiveListings = true;

	HandleSorting(SearchStacksRequest.SortBy);
	
	if (!Policy->GetKeyword().IsEmpty())
	{
		SearchStacksRequest.Keyword = Policy->GetKeyword();	
	}
	if (!Policy->GetTraits().IsEmpty())
	{
		SearchStacksRequest.Trait = Policy->GetTraits();
	}
	
	Policy->GetStacksAPI()->SearchStacks(SearchStacksRequest, ImmutableOpenAPI::OpenAPIStacksApi::FSearchStacksDelegate::CreateUObject(this, &USearchStacksWidget::OnSearchStacksResponse));
}

void USearchStacksWidget::Refresh()
{
	Super::Refresh();

	RefreshItemList(TOptional<FString>());
}

void USearchStacksWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	RefreshItemList(TOptional<FString>());

	if (PreviousPageButton)
	{
		PreviousPageButton->Show();
	}
	
	if (NextPageButton)
	{
		NextPageButton->Show();
	}
	
	if (NFTInfoButton)
	{
		NFTInfoButton->Show();
	}
}

void USearchStacksWidget::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	if (PreviousPageButton)
	{
		PreviousPageButton->Hide();
	}
	
	if (NextPageButton)
	{
		NextPageButton->Hide();
	}
	
	if (NFTInfoButton)
	{
		NFTInfoButton->Hide();
	}
}

void USearchStacksWidget::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
}

void USearchStacksWidget::OnSearchStacksResponse(const ImmutableOpenAPI::OpenAPIStacksApi::SearchStacksResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		UCustomGameInstance::SendDialogMessage(this, NativeUIGameplayTags.UI_Dialog_ErrorFull, UDialogSubsystem::CreateErrorDescriptorWithErrorText(TEXT("Error"), TEXT("Failed to acquire search stacks result"), Response.GetHttpResponse()->GetContentAsString()));
		
		return;
	}

	int32 NumberOfColumns = ListPanel->GetNumberOfColumns();
	int32 NumberOfResults = Response.Content.Result.Num();

	HandlePageData(Response.Content.Page);
	// Assign the results data to the list panel's items
	for (int32 ResultId = 0; ResultId < NumberOfResults; ResultId++)
	{
		int32 Row = ResultId / NumberOfColumns;
		int32 Column = ResultId - Row * NumberOfColumns;
		
		// Assign via processing a signle stack bundle data received from Immutable API
		if (auto ItemWidget = Cast<IMarketplaceOpenAPIProcessorInterface>(ListPanel->GetItemByRowColumn(Row, Column)))
		{
			/**
			 * Step 2(Marketplace display): This function performs the second step in the process.
			 * The Result array inside the Content of ImmutableOpenAPI::OpenAPIStacksApi::SearchStacksResponse contains NFT data for the specified contract addresses owned by the player or Passport wallet address.
			 * @see Definition of UStackItemWidget::ProcessModel to understand how the data is processed and displayed in the list panel.
			 */
			ItemWidget->ProcessModel(Response.Content.Result[ResultId]);
		}

		// click and selection handlers
		if (auto ItemWidget = ListPanel->GetItemByRowColumn(Row, Column))
		{
			
			// Register click and selection handlers for the item widget			
			ItemWidget->RegisterOnSelectionChange(UItemWidget::FOnSelectionChange::CreateUObject(this, &USearchStacksWidget::OnItemSelectionChange));
			ItemWidget->RegisterOnDoubleClick(UItemWidget::FOnDoubleClick::CreateUObject(this, &USearchStacksWidget::OnItemDoubleClick));
		}
	}
}

void USearchStacksWidget::SetupControlButtons(UAWStackWithControlPanels* HostLayer)
{
	Super::SetupControlButtons(HostLayer);

	PreviousPageButton = HostLayer->AddButtonToRight(NativeUIGameplayTags.UI_ControlPanel_Button_PreviousPage);
	NextPageButton = HostLayer->AddButtonToRight(NativeUIGameplayTags.UI_ControlPanel_Button_NextPage);
	NFTInfoButton = HostLayer->AddButtonToRight(NativeUIGameplayTags.UI_ControlPanel_Button_NFTInfo);

	if (PreviousPageButton)
	{
		PreviousPageButton->RegisterOnClick(UControlPanelButton::FOnControlPanelButtonClick::CreateUObject(this, &USearchStacksWidget::OnControlButtonClicked));
	}
	if (NextPageButton)
	{
		NextPageButton->RegisterOnClick(UControlPanelButton::FOnControlPanelButtonClick::CreateUObject(this, &USearchStacksWidget::OnControlButtonClicked));
	}
	if (NFTInfoButton)
	{
		NFTInfoButton->RegisterOnClick(UControlPanelButton::FOnControlPanelButtonClick::CreateWeakLambda(this, [HostLayer](FGameplayTag ButtonTag)
		{
			HostLayer->MoveToNextWidgetInGroup();
		}));
	}
}

void USearchStacksWidget::HandlePageData(const ImmutableOpenAPI::OpenAPIPage& PageData)
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

void USearchStacksWidget::HandleSorting(TOptional<ImmutableOpenAPI::OpenAPIStacksApi::SearchStacksRequest::SortByEnum>& Sorting)
{
	switch (GetSortCategory())
	{
	case ESearchStacks_SortCategories::Price:
		if (GetSortOrder())
		{
			Sorting = ImmutableOpenAPI::OpenAPIStacksApi::SearchStacksRequest::SortByEnum::CheapestFirst;	
		}
		else
		{
			Sorting.Reset();
		}
		break;
	default:
		Sorting.Reset();		
	}
}

void USearchStacksWidget::ItemSelectionChange(bool IsSelected, UItemWidget* ItemWidget)
{
	if (IsSelected && SelectedItemWidget != ItemWidget)
	{
		if (SelectedItemWidget)
		{
			SelectedItemWidget->SetSelection(false);
		}
		SelectedItemWidget = ItemWidget;
		if (NFTInfoButton)
		{
			NFTInfoButton->SetEnable();	
		}
			
		return;
	}

	if (!IsSelected && SelectedItemWidget == ItemWidget)
	{
		SelectedItemWidget = nullptr;
		if (NFTInfoButton)
		{
			NFTInfoButton->SetEnable(false);
		}
	}
}

void USearchStacksWidget::OnControlButtonClicked(FGameplayTag ButtonTag)
{
	if (ButtonTag.MatchesTagExact(NativeUIGameplayTags.UI_ControlPanel_Button_PreviousPage))
	{
		RefreshItemList(PageCursors.PreviousCursor);
	}
	if (ButtonTag.MatchesTagExact(NativeUIGameplayTags.UI_ControlPanel_Button_NextPage))
	{
		RefreshItemList(PageCursors.NextCursor);
	}
}

void USearchStacksWidget::OnItemSelectionChange(bool IsSelected, UItemWidget* ItemWidget)
{
	ItemSelectionChange(IsSelected, ItemWidget);
}

void USearchStacksWidget::OnItemDoubleClick(UItemWidget* InItemWidget)
{
	ItemSelectionChange(true, InItemWidget);
}
