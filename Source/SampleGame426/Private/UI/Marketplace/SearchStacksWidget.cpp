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

	// The request object containing the search parameters.
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
		
	
	// This function sends a search request to Immutable API and binds the response to OnSearchStacksResponse method
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
		UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::ErrorFull, UDialogSubsystem::CreateErrorDescriptorWithErrorText(TEXT("Error"), TEXT("Failed to acquire search stacks result"), Response.GetHttpResponse()->GetContentAsString()));
		
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
		if (auto ItemWidget = Cast<IMarketplaceOpenAPIProcessorInterface>(ListPanel->GetItem(Column, Row)))
		{
			ItemWidget->ProcessModel(Response.Content.Result[ResultId]);
		}

		// click and selection handlers
		if (auto ItemWidget = ListPanel->GetItem(Column, Row))
		{
			ItemWidget->RegisterOnSelectionChange(UItemWidget::FOnSelectionChange::CreateUObject(this, &USearchStacksWidget::OnItemSelectionChange));
			ItemWidget->RegisterOnDoubleClick(UItemWidget::FOnDoubleClick::CreateUObject(this, &USearchStacksWidget::OnItemDoubleClick));
		}
	}
}

void USearchStacksWidget::SetupControlButtons(UAWStackWithControlPanels* HostLayer)
{
	Super::SetupControlButtons(HostLayer);

	PreviousPageButton = HostLayer->AddButtonToRight(FUIControlPanelButtons::PreviousPage);
	NextPageButton = HostLayer->AddButtonToRight(FUIControlPanelButtons::NextPage);
	NFTInfoButton = HostLayer->AddButtonToRight(FUIControlPanelButtons::NFTInfo);

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
	if (ButtonTag.MatchesTagExact(FUIControlPanelButtons::PreviousPage))
	{
		RefreshItemList(PageCursors.PreviousCursor);
	}
	if (ButtonTag.MatchesTagExact(FUIControlPanelButtons::NextPage))
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
