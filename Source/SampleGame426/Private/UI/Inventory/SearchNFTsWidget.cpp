#include "Inventory/SearchNFTsWidget.h"

#include "CustomGameInstance.h"
#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "LogSampleGame.h"
#include "OpenAPIOrderbookApiOperations.h"
#include "OpenAPIOrdersApiOperations.h"
#include "OpenAPIStacksApiOperations.h"
#include "UIGameplayTags.h"
#include "Base/ItemWidget.h"
#include "Marketplace/MarketplacePolicy.h"
#include "Marketplace/SearchStacksListingWidget.h"
#include "UI/Interfaces/IOpenAPIProcessorInterface.h"
#include "UI/Utility/MathUtility.h"

#define LOCTEXT_NAMESPACE "ImmutableUI"

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

	if (!Policy.IsValid())
	{
		return;
	}

	ImmutableOpenAPI::OpenAPIStacksApi::SearchNFTsRequest SearchNFTsRequest;
	
	SearchNFTsRequest.ChainName = Policy->GetChainName();
	SearchNFTsRequest.PageSize = (ListPanel->GetNumberOfColumns() * ListPanel->GetNumberOfRows());
	SearchNFTsRequest.PageCursor = PageCursor;
	SearchNFTsRequest.AccountAddress = GetOwningCustomLocalPLayer()->GetPassportWalletAddress();
	SearchNFTsRequest.ContractAddress = Policy->GetContracts();
	SearchNFTsRequest.OnlyIncludeOwnerListings = true;
	
	Policy->GetStacksAPI()->SearchNFTs(SearchNFTsRequest, ImmutableOpenAPI::OpenAPIStacksApi::FSearchNFTsDelegate::CreateUObject(this, &USearchNfTsWidget::OnSearchNFTsResponse));
}

void USearchNfTsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	Policy = GetOwningCustomLocalPLayer()->GetGameUIPolicy()->GetMarketplacePolicy();
}

void USearchNfTsWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	RefreshItemList(TOptional<FString>());
}

void USearchNfTsWidget::SetupControlButtons(UAWStackWithControlPanels* HostPanel)
{
	Super::SetupControlButtons(HostPanel);

	SellButton = HostPanel->GetButton(FUIControlPanelButtons::Sell);
	CancelSellButton = HostPanel->GetButton(FUIControlPanelButtons::CancelSell);
	if (SellButton)
	{
		SellButton->OnPanelButtonClicked.AddUniqueDynamic(this, &USearchNfTsWidget::OnButtonClicked);	
	}
	if (CancelSellButton)
	{
		CancelSellButton->OnPanelButtonClicked.AddUniqueDynamic(this, &USearchNfTsWidget::OnButtonClicked);	
	}
}

void USearchNfTsWidget::OnSearchNFTsResponse(const ImmutableOpenAPI::OpenAPIStacksApi::SearchNFTsResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::ErrorFull, UDialogSubsystem::CreateErrorDescriptorWithErrorText(TEXT("Error"), TEXT("Failed to acquire search NFTs result"), Response.GetHttpResponse()->GetContentAsString()));
		
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
		auto Item = ListPanel->GetItem(Column, Row);

		auto ItemData = Response.Content.Result[ResultId];
		auto ItemWidget = Cast<USearchNFTsItemWidget>(Item);
		auto ItemInterface = Cast<IInventoryOpenAPIProcessorInterface>(Item);

		ItemInterface->ProcessModel(ItemData);
		ItemWidget->RegisterOnSelection(USearchNFTsItemWidget::FOnSearchNFTsItemWidgetSelection::CreateUObject(this, &USearchNfTsWidget::OnItemSelection));

		if (ItemData.Listings.Num())
		{
			ItemWidget->SetListForSellStatus(true);
		}
	}
}

void USearchNfTsWidget::OnItemSelection(bool IsSelected, USearchNFTsItemWidget* ItemWidget)
{
	if (SelectedItemWidget == ItemWidget)
	{
		SelectedItemWidget = nullptr;
		ItemWidget->SetSelectionStatus(false);
		
		if (SellButton)
		{
			SellButton->Disable();	
		}
	}
	else
	{
		if (SelectedItemWidget)
		{
			SelectedItemWidget->SetSelectionStatus(false);	
		}
		
		SelectedItemWidget = ItemWidget;

		if (SelectedItemWidget->IsListedForSell())
		{
			if (SellButton)
			{
				SellButton->Disable();	
			}
			if (CancelSellButton)
			{
				CancelSellButton->Enable();	
			}
			
		}
		else
		{
			if (SellButton)
			{
				SellButton->Enable();	
			}
			if (CancelSellButton)
			{
				CancelSellButton->Disable();	
			}
		}
	}
}

void USearchNfTsWidget::HandlePageData(const ImmutableOpenAPI::OpenAPIPage& PageData)
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

void USearchNfTsWidget::OnButtonClicked(FGameplayTag ButtonTag)
{
	if (ButtonTag.MatchesTagExact(FUIControlPanelButtons::Sell))
	{
		UDialog* SellDialog = UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::Sell, UDialogSubsystem::CreateSellDescriptor(TEXT(""), TEXT("Please enter price and confirm that you are ready to list your NFT")));

		if (SellDialog)
		{
			SellDialog->DialogResultDelegate.AddUniqueDynamic(this, &USearchNfTsWidget::OnPlayerConfirmedSell);	
		}
	}

	if (ButtonTag.MatchesTagExact(FUIControlPanelButtons::CancelSell))
	{
		UDialog* ConfirmationDialog = UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::Confirmation, UDialogSubsystem::CreateConfirmMessageDescriptor(TEXT(""), TEXT("Do you wish to cancel your listing")));

		if (ConfirmationDialog)
		{
			ConfirmationDialog->DialogResultDelegate.AddUniqueDynamic(this, &USearchNfTsWidget::OnPlayerConfirmedCancelSell);	
		}
	}
}

void USearchNfTsWidget::OnPlayerConfirmedSell(UDialog* DialogPtr, EDialogResult Result)
{
	auto Dialog = Cast<USellDialog>(DialogPtr);
	
	if (!Dialog || Result != EDialogResult::Confirmed)
	{
		return;
	}

	DialogPtr->KillDialog();

	UCustomLocalPlayer* LocalPlayer = Cast<UCustomLocalPlayer>(GetOwningLocalPlayer());
	ImmutableTsSdkApi::OpenAPIPrepareListingRequest RequestData;
	ImmutableTsSdkApi::OpenAPIOrderbookApi::PrepareListingRequest Request;
	ImmutableTsSdkApi::OpenAPIPrepareListingRequestBuy BuyData;
	ImmutableTsSdkApi::OpenAPIPrepareListingRequestSell SellData;

	BuyData.Amount = FMathUtility::ConvertFloatValueStringToWeiString(18, Dialog->GetPrice());
	BuyData.ContractAddress = Policy->GetBalanceContractAddress();
	BuyData.Type = ImmutableTsSdkApi::OpenAPIPrepareListingRequestBuy::TypeEnum::ERC20;

	SellData.ContractAddress = SelectedItemWidget->GetContractAddress();
	SellData.Type = ImmutableTsSdkApi::OpenAPIPrepareListingRequestSell::TypeEnum::ERC721;
	SellData.TokenId = SelectedItemWidget->GetTokenId();

	RequestData.MakerAddress = LocalPlayer->GetPassportWalletAddress();
	RequestData.Buy = BuyData;
	RequestData.Sell = SellData;

	Request.OpenAPIPrepareListingRequest = RequestData;

	ProcessingDialog = UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::Process, UDialogSubsystem::CreateProcessDescriptor(TEXT("Listing..."), TEXT("Started preparing listing..."), { EDialogResult::Cancelled, LOCTEXT("Cancel", "Cancel") }));
	ProcessingDialog->DialogResultDelegate.AddUniqueDynamic(this, &USearchNfTsWidget::OnProcessDialogAction);	
	Policy->GetTsSdkAPI()->PrepareListing(Request, ImmutableTsSdkApi::OpenAPIOrderbookApi::FPrepareListingDelegate::CreateUObject(this, &USearchNfTsWidget::OnPrepareListing));
}

void USearchNfTsWidget::OnPlayerConfirmedCancelSell(UDialog* DialogPtr, EDialogResult Result)
{
	if (!DialogPtr || Result != EDialogResult::Confirmed)
	{
		return;
	}

	DialogPtr->KillDialog();
	
	UCustomLocalPlayer* LocalPlayer = Cast<UCustomLocalPlayer>(GetOwningLocalPlayer());
	ImmutableTsSdkApi::OpenAPIOrderbookApi::CancelOrdersOnChainRequest Request;
	ImmutableTsSdkApi::OpenAPICancelOrdersOnChainRequest RequestData;

	RequestData.AccountAddress = LocalPlayer->GetPassportWalletAddress();
	RequestData.OrderIds.AddUnique(SelectedItemWidget->GetListingId());

	Request.OpenAPICancelOrdersOnChainRequest = RequestData;
	
	ProcessingDialog = UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::Process, UDialogSubsystem::CreateProcessDescriptor(TEXT("Canceling listing..."), TEXT("Started..."), { EDialogResult::Cancelled, LOCTEXT("Cancel", "Cancel") }));
	ProcessingDialog->DialogResultDelegate.AddUniqueDynamic(this, &USearchNfTsWidget::OnProcessDialogAction);	
	Policy->GetTsSdkAPI()->CancelOrdersOnChain(Request, ImmutableTsSdkApi::OpenAPIOrderbookApi::FCancelOrdersOnChainDelegate::CreateUObject(this, &USearchNfTsWidget::OnCancelOrdersOnChain));
}

void USearchNfTsWidget::OnPrepareListing(const ImmutableTsSdkApi::OpenAPIOrderbookApi::PrepareListingResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		UE_LOG(LogSampleGame, Error, TEXT("OnPrepareListing error: %s"), *Response.GetHttpResponse()->GetContentAsString());

		ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Prepare listing error!"), TEXT("Failed to prepare listing order"), { EDialogResult::Closed, LOCTEXT("Close", "Close") }, false));
		
		return;
	}
	
	const auto* TransactionAction = Response.Content.Actions.FindByPredicate([this](const ImmutableTsSdkApi::OpenAPIAction& Action){ return Action.Type == ImmutableTsSdkApi::OpenAPIAction::TypeEnum::Transaction; });

	const auto* SignableAction = Response.Content.Actions.FindByPredicate([this](const ImmutableTsSdkApi::OpenAPIAction& Action){ return Action.Type == ImmutableTsSdkApi::OpenAPIAction::TypeEnum::Signable; });

	if (!TransactionAction && !SignableAction)
	{
		ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Prepare listing error!"), TEXT("Failed to find required actions in prepare listing response"), { EDialogResult::Closed, LOCTEXT("Close", "Close") }, false));
		
		return;
	}

	auto SignDataLambda = [this, Content = Response.Content, Message = SignableAction->Message.GetValue()]()
	{
		FString JsonText;
		TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonText);

		Message.WriteJson(JsonWriter);
		JsonWriter->Close();
		
		GetOwningCustomLocalPLayer()->SignData(JsonText, [this, Content](const FString& Signature)
		{
			ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Listing..."), TEXT("Signed typed data for listing..."), { EDialogResult::Cancelled, LOCTEXT("Cancel", "Cancel") }));
			
			UMarketplacePolicy* Policy = GetOwningCustomLocalPLayer()->GetGameUIPolicy()->GetMarketplacePolicy();

			if (!Policy)
			{
				return;
			}
			ImmutableTsSdkApi::OpenAPIOrderbookApi::CreateListingRequest Request;
			ImmutableTsSdkApi::OpenAPICreateListingRequest RequestData;

			RequestData.OrderComponents = Content.OrderComponents;
			RequestData.OrderHash = Content.OrderHash;
			RequestData.OrderSignature = Signature;
			Request.OpenAPICreateListingRequest = RequestData;
			
			Policy->GetTsSdkAPI()->CreateListing(Request, ImmutableTsSdkApi::OpenAPIOrderbookApi::FCreateListingDelegate::CreateUObject(this, &USearchNfTsWidget::OnCreateListing));
		});
	};

	if (TransactionAction)
	{
		FString PopulatedTransactionsTo = TransactionAction->PopulatedTransactions.GetValue().To.GetValue();
		FString PopulatedTransactionsData = TransactionAction->PopulatedTransactions.GetValue().Data.GetValue();

		GetOwningCustomLocalPLayer()->SignSubmitApproval(PopulatedTransactionsTo, PopulatedTransactionsData, [this, SignDataLambda](FString TransactionHash, FString Status)
		{
			ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Listing..."), TEXT("Signed and submitted transaction for listing..."), { EDialogResult::Cancelled, LOCTEXT("Cancel", "Cancel") }));

			SignDataLambda();
		});
	}
	else
	{
		SignDataLambda();
	}
}

void USearchNfTsWidget::OnCreateListing(const ImmutableTsSdkApi::OpenAPIOrderbookApi::CreateListingResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		UE_LOG(LogSampleGame, Error, TEXT("OnCreateListing error: %s"), *Response.GetHttpResponse()->GetContentAsString());
		ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Creating listing error!"), TEXT("Failed to create listing"), { EDialogResult::Closed, LOCTEXT("Close", "Close") }, false));
		
		return;
	}

	if (Response.GetHttpResponseCode() == EHttpResponseCodes::Type::Ok)
	{
		ImmutableTsSdkApi::OpenAPICreateListing200Response OkResponse;

		TSharedPtr<FJsonValue> JsonValue;
		auto Reader = TJsonReaderFactory<>::Create(Response.GetHttpResponse()->GetContentAsString());

		if (FJsonSerializer::Deserialize(Reader, JsonValue) && JsonValue.IsValid())
		{
			if (OkResponse.FromJson(JsonValue) && OkResponse.Result.IsSet())
			{
				auto Result = OkResponse.Result.GetValue();
				FString DisplayMessage = FString::Format(TEXT("Your listing starts at: {0} with ID: {1}"), { Result.StartAt, Result.Id });

				UCustomGameInstance::SendDisplayMessage(this, DisplayMessage);
				ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Created listing successfully!"), TEXT("Your item is listed"), { EDialogResult::Closed, LOCTEXT("Close", "Close") }, false));

				SelectedItemWidget->SetListForSellStatus(true);
			}
		}
	}
}

void USearchNfTsWidget::OnCancelOrdersOnChain(const ImmutableTsSdkApi::OpenAPIOrderbookApi::CancelOrdersOnChainResponse& Response)
{
	if (!Response.IsSuccessful() || Response.GetHttpResponseCode() != EHttpResponseCodes::Type::Ok)
	{
		ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Canceling listing error!"), TEXT("Failed to cancel order"), { EDialogResult::Closed, LOCTEXT("Close", "Close") }, false));
		
		return;
	}

	ImmutableTsSdkApi::OpenAPICancelOrdersOnChain200Response OkResponse;
	TSharedPtr<FJsonValue> JsonValue;

	FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Response.GetHttpResponse()->GetContentAsString()), JsonValue);

	if (!JsonValue.IsValid() || !OkResponse.FromJson(JsonValue) || !OkResponse.CancellationAction.IsSet() || !OkResponse.CancellationAction.GetValue().PopulatedTransactions.IsSet())
	{
		ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Canceling listing error!"), TEXT("Failed to cancel order due to missing data"), { EDialogResult::Closed, LOCTEXT("Close", "Close") }, false));

		return;
	}

	auto Action = OkResponse.CancellationAction.GetValue();
	
	if (Action.Purpose.GetValue().Value != ImmutableTsSdkApi::OpenAPITransactionPurpose::Values::Cancel)
	{
		ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Canceling listing error!"), TEXT("Failed to cancel order due to wrong transaction purpose"), { EDialogResult::Closed, LOCTEXT("Close", "Close") }, false));
		
		return;
	}

	FString PopulatedTransactionsTo = Action.PopulatedTransactions.GetValue().To.GetValue();
	FString PopulatedTransactionsData = Action.PopulatedTransactions.GetValue().Data.GetValue();

	GetOwningCustomLocalPLayer()->SignSubmitApproval(PopulatedTransactionsTo, PopulatedTransactionsData, [this](FString TransactionHash, FString Status)
	{
		FString DisplayMessage = FString::Format(TEXT("Your listing was canceled with transaction hash: {0} and status: {1}"), { TransactionHash, Status });

		UCustomGameInstance::SendDisplayMessage(this, *DisplayMessage);
		ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Canceling listing success!"), TEXT("Your listing is canceled"), { EDialogResult::Closed, LOCTEXT("Close", "Close") }, false));
		SelectedItemWidget->SetListForSellStatus(false);
	});
}

void USearchNfTsWidget::OnProcessDialogAction(UDialog* DialogPtr, EDialogResult Result)
{
	if (Result == EDialogResult::Closed || Result == EDialogResult::Cancelled)
	{
		DialogPtr->KillDialog();
		return;
	}

	// if (DialogPtr->GetDialogTag().MatchesTagExact(FUIDialogTypes::Process))
	// {
	// 	
	// }
}

void USearchNfTsWidget::ConfirmListing(const FString& ListingId)
{
	ImmutableOpenAPI::OpenAPIOrdersApi::GetListingRequest ListingRequest;

	ListingRequest.ChainName = Policy->GetChainName();
	ListingRequest.ChainName = ListingId;

	Policy->GetOrdersAPI()->GetListing(ListingRequest, ImmutableOpenAPI::OpenAPIOrdersApi::FGetListingDelegate::CreateUObject(this, &USearchNfTsWidget::OnGetListing));
}

void USearchNfTsWidget::OnGetListing(const ImmutableOpenAPI::OpenAPIOrdersApi::GetListingResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		return;
	}
}
