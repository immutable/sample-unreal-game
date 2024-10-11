#include "Inventory/SearchNFTsWidget.h"

#include "CustomGameInstance.h"
#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "ImmutableTsSdkApi_DefaultApiOperations.h"
#include "ImmutableTsSdkApi_V1TsSdkOrderbookPrepareListingPostRequest.h"
#include "UIGameplayTags.h"
#include "Base/ItemWidget.h"
#include "ImmutableIndexerSearchAPI/Public/OpenAPIStacksApiOperations.h"
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

	if (Buttons.RemoveAndCopyValue(FUIControlPanelButtons::Sell, SellButton))
	{
		SellButton->OnPanelButtonClicked.AddUniqueDynamic(this, &USearchNfTsWidget::OnSellButtonClicked);
	}
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
		auto Item = ListPanel->GetItem(Column, Row);

		if (auto ItemInterface = Cast<IInventoryOpenAPIProcessorInterface>(Item))
		{
			ItemInterface->ProcessModel(Response.Content.Result[ResultId]);
		}

		if (auto ItemWidget = Cast<USearchNFTsItemWidget>(Item))
		{
			ItemWidget->RegisterOnSelection(USearchNFTsItemWidget::FOnSearchNFTsItemWidgetSelection::CreateUObject(this, &USearchNfTsWidget::OnItemSelection));
		}
	}
}

void USearchNfTsWidget::OnItemSelection(bool IsSelected, USearchNFTsItemWidget* ItemWidget)
{
	if (SelectedItemWidget == ItemWidget && !IsSelected)
	{
		SelectedItemWidget = nullptr;
		if (SellButton)
		{
			SellButton->Disable();	
		}

		return;
	}
	
	if (SelectedItemWidget != ItemWidget && IsSelected)
	{
		SelectedItemWidget = ItemWidget;

		if (SellButton)
		{
			SellButton->Enable();	
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

void USearchNfTsWidget::OnSellButtonClicked(FGameplayTag ButtonTag)
{
	if (!SelectedItemWidget)
	{
		return;
	}

	UDialog* SellDialog = UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::Sell, UDialogSubsystem::CreateSellDescriptor(TEXT(""), TEXT("Please enter price and confirm that you are ready to list your NFT")));

	SellDialog->DialogResultDelegate.AddUniqueDynamic(this, &USearchNfTsWidget::OnPlayerConfirmedSell);
}

void USearchNfTsWidget::OnPlayerConfirmedSell(UDialog* DialogPtr, EDialogResult Result)
{
	auto Dialog = Cast<USellDialog>(DialogPtr);
	
	if (!Dialog || Result != EDialogResult::Confirmed)
	{
		return;
	}
	
	UCustomLocalPlayer* LocalPlayer = Cast<UCustomLocalPlayer>(GetOwningLocalPlayer());
	UMarketplacePolicy* Policy = LocalPlayer->GetGameUIPolicy()->GetMarketplacePolicy();

	if (!Policy)
	{
		return;
	}
	
	ImmutableTsSdkApi::ImmutableTsSdkApi_V1TsSdkOrderbookPrepareListingPostRequest RequestData;
	ImmutableTsSdkApi::ImmutableTsSdkApi_DefaultApi::V1TsSdkOrderbookPrepareListingPostRequest Request;
	ImmutableTsSdkApi::ImmutableTsSdkApi_V1TsSdkOrderbookPrepareListingPostRequestBuy BuyData;
	ImmutableTsSdkApi::ImmutableTsSdkApi_V1TsSdkOrderbookPrepareListingPostRequestSell SellData;

	BuyData.Amount = FMathUtility::ConvertFloatValueStringToWeiString(18, Dialog->GetPrice());
	BuyData.ContractAddress = Policy->GetBalanceContractAddress();
	BuyData.Type = ImmutableTsSdkApi::ImmutableTsSdkApi_V1TsSdkOrderbookPrepareListingPostRequestBuy::TypeEnum::ERC20;

	SellData.ContractAddress = SelectedItemWidget->GetContractAddress();
	SellData.Type = ImmutableTsSdkApi::ImmutableTsSdkApi_V1TsSdkOrderbookPrepareListingPostRequestSell::TypeEnum::ERC721;
	SellData.TokenId = SelectedItemWidget->GetTokenId();

	RequestData.MakerAddress = LocalPlayer->GetPassportWalletAddress();
	RequestData.Buy = BuyData;
	RequestData.Sell = SellData;

	Request.ImmutableTsSdkApiV1TsSdkOrderbookPrepareListingPostRequest = RequestData;

	Policy->GetTsSdkAPI()->V1TsSdkOrderbookPrepareListingPost(Request, ImmutableTsSdkApi::ImmutableTsSdkApi_DefaultApi::FV1TsSdkOrderbookPrepareListingPostDelegate::CreateUObject(this, &USearchNfTsWidget::OnOrderbookPrepareListingPost));
	DialogPtr->KillDialog();
}

void USearchNfTsWidget::OnOrderbookPrepareListingPost(const ImmutableTsSdkApi::ImmutableTsSdkApi_DefaultApi::V1TsSdkOrderbookPrepareListingPostResponse& Response)
{
	for (auto Action : Response.Content.Actions)
	{
		if (!Action.Purpose.IsSet())
		{
			UCustomGameInstance::SendRunningLineMessage(this, TEXT("OnOrderbookPrepareListingPost: Purpose is not set!"));
			continue;
		}

		if (Action.Purpose.GetValue().Value != ImmutableTsSdkApi::ImmutableTsSdkApi_SignablePurpose::Values::CreateListing)
		{
			UCustomGameInstance::SendRunningLineMessage(this, TEXT("OnOrderbookPrepareListingPost: Purpose is not CREATE_LISTING!"));
			continue;
		}

		if (!Action.Message.IsSet())
		{
			UCustomGameInstance::SendRunningLineMessage(this, TEXT("OnOrderbookPrepareListingPost: Purpose message is not set!"));
			continue;
		}

		FString JsonText;
		TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonText);

		Action.Message->WriteJson(JsonWriter);
		JsonWriter->Close();

		GetOwningCustomLocalPLayer()->CreateListing(JsonText, [this, Content = Response.Content](const FString& Signature)
		{
			UMarketplacePolicy* Policy = GetOwningCustomLocalPLayer()->GetGameUIPolicy()->GetMarketplacePolicy();

			if (!Policy)
			{
				return;
			}
			ImmutableTsSdkApi::ImmutableTsSdkApi_DefaultApi::V1TsSdkOrderbookCreateListingPostRequest Request;
			ImmutableTsSdkApi::ImmutableTsSdkApi_V1TsSdkOrderbookCreateListingPostRequest RequestData;
			
			RequestData.OrderComponents = Content.OrderComponents;
			RequestData.OrderHash = Content.OrderHash;
			RequestData.OrderSignature = Signature;

			Request.ImmutableTsSdkApiV1TsSdkOrderbookCreateListingPostRequest = RequestData;

			FString JsonText;
			TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonText);
			Request.ImmutableTsSdkApiV1TsSdkOrderbookCreateListingPostRequest->WriteJson(JsonWriter);
			JsonWriter->Close();
			
			Policy->GetTsSdkAPI()->V1TsSdkOrderbookCreateListingPost(Request, ImmutableTsSdkApi::ImmutableTsSdkApi_DefaultApi::FV1TsSdkOrderbookCreateListingPostDelegate::CreateUObject(this, &USearchNfTsWidget::OnOrderbookCreateListingPost));
		});
	}
}

void USearchNfTsWidget::OnOrderbookCreateListingPost(const ImmutableTsSdkApi::ImmutableTsSdkApi_DefaultApi::V1TsSdkOrderbookCreateListingPostResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::ErrorFull, UDialogSubsystem::CreateErrorDescriptorWithErrorText(TEXT("Error"), TEXT("Failed to create listing"), Response.GetHttpResponse()->GetContentAsString()));
		
		return;
	}

	if (Response.GetHttpResponseCode() == EHttpResponseCodes::Type::Ok)
	{
		ImmutableTsSdkApi::ImmutableTsSdkApi_V1TsSdkOrderbookCreateListingPost200Response OkResponse;

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
