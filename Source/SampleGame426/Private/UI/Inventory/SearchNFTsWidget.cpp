#include "Inventory/SearchNFTsWidget.h"

#include "CustomGameInstance.h"
#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "LogSampleGame.h"
#include "APIOrderbookApiOperations.h"
#include "APIOrdersApiOperations.h"
#include "APIMetadataSearchApiOperations.h"
#include "UIGameplayTags.h"
#include "Base/AWStackWithControlPanels.h"
#include "Base/ItemWidget.h"
#include "Marketplace/MarketplacePolicy.h"
#include "Marketplace/SearchStacksListingWidget.h"
#include "UI/Interfaces/IOpenAPIProcessorInterface.h"
#include "UI/Utility/MathUtility.h"

#define LOCTEXT_NAMESPACE "ImmutableUI"

void USearchNfTsWidget::RefreshItemList(TOptional<FString> PageCursor)
{
#if UE_5_1_OR_LATER
	if (!bWidgetInitialized)
#else
	if (!bInitialized)
#endif
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

	/**
	 * Step 1(Inventory display): In order to display items in the list panel of player's Inventory, we need to send a search request to the Immutable zkEVM API.
	 * Some request parameters are populated based on the current state of the UI Marketplace policy settings.
	 * @see UMarketplacePolicy
	 * 
	 * @param SearchNFTsRequest The request object to be passed to SearchNFTs method of the Immutable zkEVM API.
	 * Must-be parameters:
	 * - AccountAddress: The wallet address of the owning custom local player.
	 * - ContractAddress: The contract address of NFT we are searching for, retrieved from the policy.
	 * - ChainName: The name of the blockchain chain .
	 * - OnlyIncludeOwnerListings: A boolean flag to include only owner listings. Must be 'true' in order to list player's NFTs.
	 * Optional parameters:
	 * - PageSize: The number of items per page, calculated based on the number of columns and rows in the ListPanel.
	 * - PageCursor: The cursor for pagination.
	 * 
	 * The search request is sent using the ImmutablezkEVMAPI::APIStacksApi, and the response is bound to the USearchNfTsWidget::OnSearchNFTsResponse method.
	 */
	ImmutablezkEVMAPI::APIMetadataSearchApi::SearchNFTsRequest SearchNFTsRequest;
	
	SearchNFTsRequest.ChainName = Policy->GetChainName();
	SearchNFTsRequest.PageSize = (ListPanel->GetNumberOfColumns() * ListPanel->GetNumberOfRows());
	SearchNFTsRequest.PageCursor = PageCursor;
	SearchNFTsRequest.AccountAddress = GetOwningCustomLocalPLayer()->GetPassportWalletAddress();
	SearchNFTsRequest.ContractAddress = Policy->GetContracts();
	SearchNFTsRequest.OnlyIncludeOwnerListings = true;
	
	Policy->GetStacksAPI()->SearchNFTs(SearchNFTsRequest, ImmutablezkEVMAPI::APIMetadataSearchApi::FSearchNFTsDelegate::CreateUObject(this, &USearchNfTsWidget::OnSearchNFTsResponse));
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

	// if (SellButton)
	// {
	// 	SellButton->Show();
	// }
	// if (CancelSellButton)
	// {
	// 	CancelSellButton->Show();
	// }
}

void USearchNfTsWidget::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	// if (SellButton)
	// {
	// 	SellButton->Hide();
	// }
	// if (CancelSellButton)
	// {
	// 	CancelSellButton->Hide();
	// }
}

void USearchNfTsWidget::SetupControlButtons(UAWStackWithControlPanels* HostLayer)
{
	Super::SetupControlButtons(HostLayer);

	SellButton = HostLayer->AddButton(NativeUIGameplayTags.UI_ControlPanel_Button_Sell);
	CancelSellButton = HostLayer->AddButton(NativeUIGameplayTags.UI_ControlPanel_Button_CancelSell);

	if (SellButton)
	{
		SellButton->RegisterOnClick(UControlPanelButton::FOnControlPanelButtonClick::CreateUObject(this, &USearchNfTsWidget::OnButtonClicked));
		ControlPanelButtons.Add(NativeUIGameplayTags.UI_ControlPanel_Button_Sell, SellButton);
	}
	if (CancelSellButton)
	{
		CancelSellButton->RegisterOnClick(UControlPanelButton::FOnControlPanelButtonClick::CreateUObject(this, &USearchNfTsWidget::OnButtonClicked));
		ControlPanelButtons.Add(NativeUIGameplayTags.UI_ControlPanel_Button_CancelSell, CancelSellButton);
	}
}

void USearchNfTsWidget::OnSearchNFTsResponse(const ImmutablezkEVMAPI::APIMetadataSearchApi::SearchNFTsResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		UCustomGameInstance::SendDialogMessage(this, NativeUIGameplayTags.UI_Dialog_ErrorFull, UDialogSubsystem::CreateErrorDescriptorWithErrorText(TEXT("Error"), TEXT("Failed to acquire search NFTs result"), Response.GetHttpResponse()->GetContentAsString()));
		
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
		auto Item = ListPanel->GetItemByRowColumn(Row, Column);

		auto ItemData = Response.Content.Result[ResultId];
		auto ItemWidget = Cast<USearchNFTsItemWidget>(Item);
		auto ItemInterface = Cast<IInventoryOpenAPIProcessorInterface>(Item);

		/**
		* Step 2(Inventory display): This function performs the second step in the process.
		* The Result array inside the Content of ImmutablezkEVMAPI::APIStacksApi::SearchNFTsResponse contains NFT data for the specified contract addresses owned by the player or Passport wallet address.
		* Register selection handler for the item widget to dynamically acquire data for performing Immutable zkEVM API Listing or Cancel Listing procedures.
		* Also, if Result's Listings array is not empty, highlight the item widget to be listed for sell.
		* @see Definition of USearchNFTsItemWidget::ProcessModel to understand how the data is processed and displayed in the Inventory panel.
		*/
		ItemInterface->ProcessModel(ItemData);
		ItemWidget->RegisterOnSelectionChange(UItemWidget::FOnSelectionChange::CreateUObject(this, &USearchNfTsWidget::OnItemSelection));

		if (ItemData.Listings.Num())
		{
			ItemWidget->SetListForSellStatus(true);
		}
	}
}

void USearchNfTsWidget::OnItemSelection(bool IsSelected, UItemWidget* ItemWidget)
{
	if (IsSelected && SelectedItemWidget != ItemWidget)
	{
		if (SelectedItemWidget)
		{
			SelectedItemWidget->SetSelection(false);
		}
		SelectedItemWidget = Cast<USearchNFTsItemWidget>(ItemWidget);

		bool IsListed = SelectedItemWidget->IsListedForSell();
		if (SellButton)
		{
			SellButton->SetEnable(!IsListed);	
		}
		if (CancelSellButton)
		{
			CancelSellButton->SetEnable(IsListed);	
		}
			
		return;
	}

	if (!IsSelected && SelectedItemWidget == ItemWidget)
	{
		SelectedItemWidget = nullptr;
		if (SellButton)
		{
			SellButton->SetEnable(false);
		}
		if (CancelSellButton)
		{
			CancelSellButton->SetEnable(false);	
		}
	}
}

void USearchNfTsWidget::HandlePageData(const ImmutablezkEVMAPI::APIPage& PageData)
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
	if (ButtonTag.MatchesTagExact(NativeUIGameplayTags.UI_ControlPanel_Button_Sell))
	{
		UDialog* SellDialog = UCustomGameInstance::SendDialogMessage(this, NativeUIGameplayTags.UI_Dialog_Sell, UDialogSubsystem::CreateSellDescriptor(TEXT(""), TEXT("Please enter price and confirm that you are ready to list your NFT")));

		if (SellDialog)
		{
			SellDialog->DialogResultDelegate.AddUniqueDynamic(this, &USearchNfTsWidget::OnPlayerConfirmedSell);	
		}
	}

	if (ButtonTag.MatchesTagExact(NativeUIGameplayTags.UI_ControlPanel_Button_CancelSell))
	{
		UDialog* ConfirmationDialog = UCustomGameInstance::SendDialogMessage(this, NativeUIGameplayTags.UI_Dialog_Confirmation, UDialogSubsystem::CreateConfirmMessageDescriptor(TEXT(""), TEXT("Do you wish to cancel your listing")));

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

	ProcessingDialog = UCustomGameInstance::SendDialogMessage(this, NativeUIGameplayTags.UI_Dialog_Process, UDialogSubsystem::CreateProcessDescriptor(TEXT("Listing..."), TEXT("Started preparing listing..."), {EDialogResult::Cancelled, LOCTEXT("Cancel", "Cancel")}));
	ProcessingDialog->DialogResultDelegate.AddUniqueDynamic(this, &USearchNfTsWidget::OnProcessDialogAction);	

	UCustomLocalPlayer* LocalPlayer = Cast<UCustomLocalPlayer>(GetOwningLocalPlayer());
	
	/**
	 * Step 1(Listing): Prepares a listing request for the Immutable Orderbook API.
	 *
	 * This function sets up the necessary data for a listing request, including the buy and sell details,
	 * and then sends the request using PrepareListing method of Immutable Orderbook API.
	 *
	 * The buy data includes the amount (converted to Wei string), contract address, and type (ERC20).
	 * The sell data includes the contract address, type (ERC721), and token ID obtained from the selected item widget.
	 * The maker address is set to the local player's wallet address.
	 *
	 * @param RequestData The data for the prepare listing request.
	 * @param Request The request object for the prepare listing.
	 * @param BuyData The data for the buy side of the listing.
	 * @param SellData The data for the sell side of the listing.
	 */
	ImmutableOrderbook::APIPrepareListingRequest RequestData;
	ImmutableOrderbook::APIOrderbookApi::PrepareListingRequest Request;
	ImmutableOrderbook::APIPrepareListingRequestBuy BuyData;
	ImmutableOrderbook::APIPrepareListingRequestSell SellData;

	BuyData.Amount = FMathUtility::ConvertFloatValueStringToWeiString(18, Dialog->GetPrice());
	BuyData.ContractAddress = Policy->GetBalanceContractAddress();
	BuyData.Type = ImmutableOrderbook::APIPrepareListingRequestBuy::TypeEnum::ERC20;

	SellData.ContractAddress = SelectedItemWidget->GetContractAddress();
	SellData.Type = ImmutableOrderbook::APIPrepareListingRequestSell::TypeEnum::ERC721;
	SellData.TokenId = SelectedItemWidget->GetTokenId();

	RequestData.MakerAddress = LocalPlayer->GetPassportWalletAddress();
	RequestData.Buy = BuyData;
	RequestData.Sell = SellData;

	Request.APIPrepareListingRequest = RequestData;
	Policy->GetTsSdkAPI()->PrepareListing(Request, ImmutableOrderbook::APIOrderbookApi::FPrepareListingDelegate::CreateUObject(this, &USearchNfTsWidget::OnPrepareListing));
}

void USearchNfTsWidget::OnPlayerConfirmedCancelSell(UDialog* DialogPtr, EDialogResult Result)
{
	if (!DialogPtr || Result != EDialogResult::Confirmed)
	{
		return;
	}

	DialogPtr->KillDialog();

	ProcessingDialog = UCustomGameInstance::SendDialogMessage(this, NativeUIGameplayTags.UI_Dialog_Process, UDialogSubsystem::CreateProcessDescriptor(TEXT("Canceling listing..."), TEXT("Started..."), {EDialogResult::Cancelled, LOCTEXT("Cancel", "Cancel")}));
	ProcessingDialog->DialogResultDelegate.AddUniqueDynamic(this, &USearchNfTsWidget::OnProcessDialogAction);	
	
	UCustomLocalPlayer* LocalPlayer = Cast<UCustomLocalPlayer>(GetOwningLocalPlayer());

	/**
	 * Step 1(Cancel Listing): Prepares a cancel listing request for the Immutable Orderbook API.
	 *
	 * This function sets up the necessary data for a cancel listing request, including the account address and order IDs,
	 * and then sends the request using CancelOrdersOnChain method of Immutable Orderbook API.
	 *
	 * The account address is set to the local player's wallet address.
	 * The order ID is obtained from the selected item widget.
	 *
	 * @param RequestData The data for the cancel listing request.
	 * @param Request The request object for the cancel listing.
	 */
	ImmutableOrderbook::APIOrderbookApi::CancelOrdersOnChainRequest Request;
	ImmutableOrderbook::APICancelOrdersOnChainRequest RequestData;

	RequestData.AccountAddress = LocalPlayer->GetPassportWalletAddress();
	RequestData.OrderIds.AddUnique(SelectedItemWidget->GetListingId());

	Request.APICancelOrdersOnChainRequest = RequestData;
	Policy->GetTsSdkAPI()->CancelOrdersOnChain(Request, ImmutableOrderbook::APIOrderbookApi::FCancelOrdersOnChainDelegate::CreateUObject(this, &USearchNfTsWidget::OnCancelOrdersOnChain));
}

void USearchNfTsWidget::OnPrepareListing(const ImmutableOrderbook::APIOrderbookApi::PrepareListingResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		UE_LOG(LogSampleGame, Error, TEXT("OnPrepareListing error: %s"), *Response.GetHttpResponse()->GetContentAsString());

		ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Prepare listing error!"), TEXT("Failed to prepare listing order"), { EDialogResult::Closed, LOCTEXT("Close", "Close") }, false));
		
		return;
	}

	/**
	 * Step 2(Listing): Processes the response from the PrepareListing Orderbook API call and handles the required actions.
	 * 
	 * This function searches for specific actions (Transaction and Signable) in the response content.
	 * If the player has never conducted the PrepareListing operation before, the Transaction action must be present in the response.
	 * Subsequently, only the Signable action is required to sign the data and create a listing.
	 * 
	 * If the Transaction action is present, the function signs and submits the transaction to the blockchain via Immutable SDK ZkEvmSendTransactionWithConfirmation.
	 * @see https://docs.immutable.com/sdks/zkEVM/unreal#zkevm-send-transaction. It is implemented in UCustomLocalPlayer::SignSubmitApproval.
	 * If the Signable action is present, the function signs the data using Immutable SDK ZkEvmSignTypedDataV4 and creates a listing via the Immutable Orderbook API's CreateListing method.
	 */

	const auto* TransactionAction = Response.Content.Actions.FindByPredicate([this](const ImmutableOrderbook::APIAction& Action){ return Action.Type == ImmutableOrderbook::APIAction::TypeEnum::Transaction; });
	const auto* SignableAction = Response.Content.Actions.FindByPredicate([this](const ImmutableOrderbook::APIAction& Action){ return Action.Type == ImmutableOrderbook::APIAction::TypeEnum::Signable; });

	if (!TransactionAction && !SignableAction)
	{
		ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Prepare listing error!"), TEXT("Failed to find required actions in prepare listing response"), { EDialogResult::Closed, LOCTEXT("Close", "Close") }, false));
		
		return;
	}

	// defining lambda to avoid duplicate code
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

			/**
			* Step 2 Continued(Listing): This function continues the process of handling the Listing operation.
			* 
			* After succeful callback from ZkEvmSignTypedDataV4, the function sends a request to create a listing using the Immutable Orderbook API's CreateListing method.
			* The request includes the order components, order hash, and the signature obtained from the signed data.
			* The CreateListing method will send a callback to the delegate method USearchNfTsWidget::OnCreateListing, which will inform us whether the listing was successfully created or not.
			* @see USearchNfTsWidget::OnCreateListing
			* 
			* @param Request The request object for creating the listing.
			* @param RequestData The data for the create listing request.
			*/
			ImmutableOrderbook::APIOrderbookApi::CreateListingRequest Request;
			ImmutableOrderbook::APICreateListingRequest RequestData;

			RequestData.OrderComponents = Content.OrderComponents;
			RequestData.OrderHash = Content.OrderHash;
			RequestData.OrderSignature = Signature;
			Request.APICreateListingRequest = RequestData;
			
			Policy->GetTsSdkAPI()->CreateListing(Request, ImmutableOrderbook::APIOrderbookApi::FCreateListingDelegate::CreateUObject(this, &USearchNfTsWidget::OnCreateListing));
		});
	};

	if (TransactionAction)
	{
		FString PopulatedTransactionsTo = TransactionAction->PopulatedTransactions.GetValue().To.GetValue();
		FString PopulatedTransactionsData = TransactionAction->PopulatedTransactions.GetValue().Data.GetValue();

		// find explanation for this part in Step 2(Listing) comment
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

void USearchNfTsWidget::OnCreateListing(const ImmutableOrderbook::APIOrderbookApi::CreateListingResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		UE_LOG(LogSampleGame, Error, TEXT("OnCreateListing error: %s"), *Response.GetHttpResponse()->GetContentAsString());
		ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Creating listing error!"), TEXT("Failed to create listing"), { EDialogResult::Closed, LOCTEXT("Close", "Close") }, false));
		
		return;
	}

	if (Response.GetHttpResponseCode() == EHttpResponseCodes::Type::Ok)
	{
		ImmutableOrderbook::APICreateListing200Response OkResponse;

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

void USearchNfTsWidget::OnCancelOrdersOnChain(const ImmutableOrderbook::APIOrderbookApi::CancelOrdersOnChainResponse& Response)
{
	if (!Response.IsSuccessful() || Response.GetHttpResponseCode() != EHttpResponseCodes::Type::Ok)
	{
		ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Canceling listing error!"), TEXT("Failed to cancel order"), { EDialogResult::Closed, LOCTEXT("Close", "Close") }, false));
		
		return;
	}

	ImmutableOrderbook::APICancelOrdersOnChain200Response OkResponse;
	TSharedPtr<FJsonValue> JsonValue;

	FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Response.GetHttpResponse()->GetContentAsString()), JsonValue);

	if (!JsonValue.IsValid() || !OkResponse.FromJson(JsonValue) || !OkResponse.CancellationAction.IsSet() || !OkResponse.CancellationAction.GetValue().PopulatedTransactions.IsSet())
	{
		ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Canceling listing error!"), TEXT("Failed to cancel order due to missing data"), { EDialogResult::Closed, LOCTEXT("Close", "Close") }, false));

		return;
	}

	auto Action = OkResponse.CancellationAction.GetValue();
	
	if (Action.Purpose.GetValue().Value != ImmutableOrderbook::APITransactionPurpose::Values::Cancel)
	{
		ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Canceling listing error!"), TEXT("Failed to cancel order due to wrong transaction purpose"), { EDialogResult::Closed, LOCTEXT("Close", "Close") }, false));
		
		return;
	}

	/**
	 * Step 2(Cancel Listing):If response from CancelOrdersOnChain of Orderbook API is successful, we have to approve this transaction by using ZkEvmSendTransactionWithConfirmation.
	 *
	 * This function retrieves the populated transaction details from the Action object,
	 * then calls the SignSubmitApproval(ZkEvmSendTransactionWithConfirmation) method on the owning custom local player.
	 * Upon completion, it can format and display a message with the transaction hash and status,
	 * updates the processing dialog to indicate success, and sets the selected item widget's
	 * list-for-sell status to false.
	 * @see UCustomLocalPlayer::SignSubmitApproval
	 */
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

	// if (DialogPtr->GetDialogTag().MatchesTagExact(NativeUIGameplayTags.UI_Dialog_Process))
	// {
	// 	
	// }
}

void USearchNfTsWidget::ConfirmListing(const FString& ListingId)
{
	ImmutablezkEVMAPI::APIOrdersApi::GetListingRequest ListingRequest;

	ListingRequest.ChainName = Policy->GetChainName();
	ListingRequest.ChainName = ListingId;

	Policy->GetOrdersAPI()->GetListing(ListingRequest, ImmutablezkEVMAPI::APIOrdersApi::FGetListingDelegate::CreateUObject(this, &USearchNfTsWidget::OnGetListing));
}

void USearchNfTsWidget::OnGetListing(const ImmutablezkEVMAPI::APIOrdersApi::GetListingResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		return;
	}
}
