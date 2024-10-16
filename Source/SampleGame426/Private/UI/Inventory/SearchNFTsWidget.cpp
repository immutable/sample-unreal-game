#include "Inventory/SearchNFTsWidget.h"

#include "CustomGameInstance.h"
#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "OpenAPIOrderbookApiOperations.h"
#include "OpenAPIOrdersApiOperations.h"
#include "OpenAPIStacksApiOperations.h"
#include "UIGameplayTags.h"
#include "Base/ItemWidget.h"
#include "Marketplace/MarketplacePolicy.h"
#include "Marketplace/SearchStacksListingWidget.h"
#include "UI/Interfaces/IOpenAPIProcessorInterface.h"
#include "UI/Utility/MathUtility.h"


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

		SellDialog->DialogResultDelegate.AddUniqueDynamic(this, &USearchNfTsWidget::OnPlayerConfirmedSell);	
	}

	if (ButtonTag.MatchesTagExact(FUIControlPanelButtons::CancelSell))
	{
		
	}
}

void USearchNfTsWidget::OnPlayerConfirmedSell(UDialog* DialogPtr, EDialogResult Result)
{
	auto Dialog = Cast<USellDialog>(DialogPtr);
	
	if (!Dialog || Result != EDialogResult::Confirmed)
	{
		return;
	}
	
	UCustomLocalPlayer* LocalPlayer = Cast<UCustomLocalPlayer>(GetOwningLocalPlayer());

	if (!Policy.IsValid())
	{
		return;
	}
	
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

	Policy->GetTsSdkAPI()->PrepareListing(Request, ImmutableTsSdkApi::OpenAPIOrderbookApi::FPrepareListingDelegate::CreateUObject(this, &USearchNfTsWidget::OnPrepareListing));
	DialogPtr->KillDialog();
}

void USearchNfTsWidget::OnPrepareListing(const ImmutableTsSdkApi::OpenAPIOrderbookApi::PrepareListingResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::ErrorFull, UDialogSubsystem::CreateErrorDescriptorWithErrorText(TEXT("Error"), TEXT("Failed to prepare listing"), Response.GetHttpResponse()->GetContentAsString()));
		
		return;
	}
	
	const auto* TransactionAction = Response.Content.Actions.FindByPredicate([this](const ImmutableTsSdkApi::OpenAPIAction& Action){ return Action.Type == ImmutableTsSdkApi::OpenAPIAction::TypeEnum::Transaction; });

	const auto* SignableAction = Response.Content.Actions.FindByPredicate([this](const ImmutableTsSdkApi::OpenAPIAction& Action){ return Action.Type == ImmutableTsSdkApi::OpenAPIAction::TypeEnum::Signable; });

	if (!TransactionAction || !SignableAction)
	{
		UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::ErrorSimple, UDialogSubsystem::CreateErrorSimpleDescriptor(TEXT("Error"), TEXT("Failed to find required actions in prepare listing response")));
		
		return;
	}

	if (!TransactionAction->PopulatedTransactions.IsSet())
	{
		UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::ErrorSimple, UDialogSubsystem::CreateErrorSimpleDescriptor(TEXT("Error"), TEXT("Failed to find TRANSACTION action's populated transactions in prepare listing response")));
		
		return;
	}

	if (!SignableAction->Message.IsSet())
	{
		UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::ErrorSimple, UDialogSubsystem::CreateErrorSimpleDescriptor(TEXT("Error"), TEXT("Failed to find SIGNABLE action's message in prepare listing response")));
		
		return;
	}

	FString PopulatedTransactionsTo = TransactionAction->PopulatedTransactions.GetValue().To.GetValue();
	FString PopulatedTransactionsData = TransactionAction->PopulatedTransactions.GetValue().Data.GetValue();

	GetOwningCustomLocalPLayer()->SignSubmitApproval(PopulatedTransactionsTo, PopulatedTransactionsData, [this, Content = Response.Content, Message = SignableAction->Message.GetValue()]()
	{
		UCustomGameInstance::SendDisplayMessage(this, "Signed and submitted transaction for listing");
		
		FString JsonText;
		TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonText);

		Message.WriteJson(JsonWriter);
		JsonWriter->Close();

		GetOwningCustomLocalPLayer()->SignData(JsonText, [this, Content](const FString& Signature)
		{
			UCustomGameInstance::SendDisplayMessage(this, "Signed typed data for listing");
			
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
	});
}

void USearchNfTsWidget::OnCreateListing(const ImmutableTsSdkApi::OpenAPIOrderbookApi::CreateListingResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::ErrorFull, UDialogSubsystem::CreateErrorDescriptorWithErrorText(TEXT("Error"), TEXT("Failed to create listing"), Response.GetHttpResponse()->GetContentAsString()));
		
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

				UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::Message, UDialogSubsystem::CreateMessageDescriptor(TEXT("Message"), *DisplayMessage));

				RefreshItemList(TOptional<FString>());
			}
		}
	}
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
