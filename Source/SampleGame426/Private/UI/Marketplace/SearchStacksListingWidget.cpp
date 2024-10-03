#include "Marketplace/SearchStacksListingWidget.h"

#include "CustomGameInstance.h"
#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "ImmutableTsSdkApi_DefaultApiOperations.h"
#include "ImmutableTsSdkApi_V1TsSdkOrderbookFulfillOrderPostRequest.h"
#include "LogSampleGame.h"
#include "OpenAPIListing.h"
#include "OpenAPIStackBundle.h"
#include "UIGameplayTags.h"
#include "Marketplace/MarketplacePolicy.h"
#include "Marketplace/SearchStacksListing_ListingsWidget.h"

#define MP_DESCRIPTION_DESCRIPTION TEXT("Description")
#define MP_DESCRIPTION_CREATED_AT TEXT("Created at")
#define MP_DESCRIPTION_UPDATED_AT TEXT("Updated at")


void USearchStacksListingWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (Listings)
	{
		Listings->RegisterOnSelectionStatusChange(USearchStacksListing_ListingsWidget::FOnSelectionStatusChange::CreateUObject(this, &USearchStacksListingWidget::OnSelectionStatusChange));		
	}
}

void USearchStacksListingWidget::SetupControlButtons(TMap<FGameplayTag, UControlPanelButton*>& Buttons)
{
	Super::SetupControlButtons(Buttons);

	if (Buttons.RemoveAndCopyValue(FUIControlPanelButtons::Buy, BuyButton))
	{
		BuyButton->OnPanelButtonClicked.AddUniqueDynamic(this, &USearchStacksListingWidget::OnBuyButtonClicked);
	}
}

void USearchStacksListingWidget::ProcessModel(const ImmutableOpenAPI::Model& Data)
{
	auto StackBundle = static_cast<const ImmutableOpenAPI::OpenAPIStackBundle&>(Data);

	FString StackName = StackBundle.Stack.Name.GetValue();

	// set name and thumbnail
	if (UMarketplacePolicy* Policy = GetOwningCustomLocalPLayer()->GetGameUIPolicy()->GetMarketplacePolicy())
	{
		FName RowName = FName(*StackName.Replace(TEXT(" "),TEXT("_")));
		auto DatatableRow = Policy->FindNFTTextureRow(RowName);
		
		if (!DatatableRow)
		{
			UE_LOG(LogSampleGame, Error, TEXT("MarketplaceItemWidget - No data row %s was not found"), *RowName.ToString());
			return;
		}
		
		UTexture2D* SourceTexturePtr = DatatableRow->Thumbnail.LoadSynchronous();

		if (SourceTexturePtr)
		{
			SetThumbnail(SourceTexturePtr);
		}	
		SetName(DatatableRow->Name);
	}

	// set nft info
	FString Description = StackBundle.Stack.Description.IsSet() ? StackBundle.Stack.Description.GetValue() : TEXT("");
	
	AddDescriptionRecord(MP_DESCRIPTION_DESCRIPTION, Description);
	AddDescriptionRecord(MP_DESCRIPTION_CREATED_AT, StackBundle.Stack.CreatedAt.ToString());
	AddDescriptionRecord(MP_DESCRIPTION_UPDATED_AT, StackBundle.Stack.UpdatedAt.ToString());

	if (StackBundle.Stack.Attributes.IsSet())
	{
		for (auto Attribute : StackBundle.Stack.Attributes.GetValue())
		{
			TSharedPtr<FJsonValue> Value;

			AddMetadataAttribute(Attribute.TraitType, Attribute.Value);
		}
	}

	for (const auto& Listing : StackBundle.Listings)
	{
		Listings->AddItem(Listing);
	}
}

void USearchStacksListingWidget::OnSelectionStatusChange(bool IsAnyItemSelected)
{
	if (BuyButton)
	{
		IsAnyItemSelected ? BuyButton->Enable() : BuyButton->Disable();
	}
}

void USearchStacksListingWidget::OnBuyButtonClicked(FGameplayTag ButtonTag)
{
	UCustomLocalPlayer* LocalPlayer = Cast<UCustomLocalPlayer>(GetOwningLocalPlayer());
	UMarketplacePolicy* Policy = LocalPlayer->GetGameUIPolicy()->GetMarketplacePolicy();

	if (!Policy)
	{
		return;
	}
	
	if(Listings->GetSelectedItemWidget())
	{
		ImmutableTsSdkApi::ImmutableTsSdkApi_V1TsSdkOrderbookFulfillOrderPostRequest RequestData;
		ImmutableTsSdkApi::ImmutableTsSdkApi_DefaultApi::V1TsSdkOrderbookFulfillOrderPostRequest Request;

		RequestData.ListingId = Listings->GetSelectedItemWidget()->GetListingId();
		RequestData.TakerAddress = LocalPlayer->GetPassportWalletAddress();
		Request.ImmutableTsSdkApiV1TsSdkOrderbookFulfillOrderPostRequest = RequestData;
		
		
		Policy->GetTsSdkAPI()->V1TsSdkOrderbookFulfillOrderPost(Request, ImmutableTsSdkApi::ImmutableTsSdkApi_DefaultApi::FV1TsSdkOrderbookFulfillOrderPostDelegate::CreateUObject(this, &USearchStacksListingWidget::OnOrderbookFulfillOrder));
	}
}

void USearchStacksListingWidget::OnOrderbookFulfillOrder(const ImmutableTsSdkApi::ImmutableTsSdkApi_DefaultApi::V1TsSdkOrderbookFulfillOrderPostResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		UCustomGameInstance::SendSystemMessage(this, FUIErrors::Undefined, FText::FromString(TEXT("Error")), FText::FromString(Response.GetResponseString()));

		return;
	}

	if (Response.Content.Expiration.IsSet())
	{
		UE_LOG(LogSampleGame, Log, TEXT("GetUnsignedFulfillOrderTransaction Expiration: %s"), *Response.Content.Expiration.GetValue());	
	}

	if (Response.Content.Actions.IsSet())
	{
		auto Actions = Response.Content.Actions.GetValue();
		for (int32 i = 0; i < Actions.Num(); i++)
		{
			if (Actions[i].Purpose.IsSet())
			{
				auto Purpose = Actions[i].Purpose.GetValue();
				
				UE_LOG(LogSampleGame, Log, TEXT("GetUnsignedFulfillOrderTransaction Actions: %s"), *Purpose.EnumToString(Purpose.Value));	
			}
		}
	}
}

