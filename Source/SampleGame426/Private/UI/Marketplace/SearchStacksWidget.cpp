#include "Marketplace/SearchStacksWidget.h"

#include "CustomGameInstance.h"
#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "OpenAPIStacksApiOperations.h"
#include "UIGameplayTags.h"
#include "UI/Marketplace/MarketplacePolicy.h"
#include "Base/ItemWidget.h"
#include "Dialog/DialogSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"
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

	ImmutableOpenAPI::OpenAPIStacksApi::SearchStacksRequest SearchStacksRequest;

	SearchStacksRequest.PageSize = ListPanel->GetNumberOfColumns() * ListPanel->GetNumberOfRows();
	SearchStacksRequest.PageCursor = PageCursor;
	SearchStacksRequest.AccountAddress = GetOwningCustomLocalPLayer()->GetPassportWalletAddress();
	SearchStacksRequest.ContractAddress = Policy->GetContracts();
	SearchStacksRequest.ChainName = Policy->GetChainName();
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

void USearchStacksWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	RefreshItemList(TOptional<FString>());
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
	// int32 NumberOfRows = ListPanel->GetNumberOfRows();
	int32 NumberOfResults = Response.Content.Result.Num();

	HandlePageData(Response.Content.Page);
	for (int32 ResultId = 0; ResultId < NumberOfResults; ResultId++)
	{
		int32 Row = ResultId / NumberOfColumns;
		int32 Column = ResultId - Row * NumberOfColumns;
		
		if (auto ItemWidget = Cast<IMarketplaceOpenAPIProcessorInterface>(ListPanel->GetItem(Column, Row)))
		{
			ItemWidget->ProcessModel(Response.Content.Result[ResultId]);	
		}
	}
}

void USearchStacksWidget::SetupControlButtons(UAWStackWithControlPanels* HostPanel)
{
	Super::SetupControlButtons(HostPanel);

	PreviousPageButton = HostPanel->GetButton(FUIControlPanelButtons::PreviousPage);
	NextPageButton = HostPanel->GetButton(FUIControlPanelButtons::NextPage);

	if (PreviousPageButton)
	{
		PreviousPageButton->OnPanelButtonClicked.AddUniqueDynamic(this, &USearchStacksWidget::OnPageDirectionButtonClicked);
	}
	if (NextPageButton)
	{
		NextPageButton->OnPanelButtonClicked.AddUniqueDynamic(this, &USearchStacksWidget::OnPageDirectionButtonClicked);	
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

void USearchStacksWidget::OnPageDirectionButtonClicked(FGameplayTag ButtonTag)
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
