#include "Marketplace/SearchStacksListingWidget.h"

#include "CustomGameInstance.h"
#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "LogSampleGame.h"
#include "OpenAPIListing.h"
#include "OpenAPIStackBundle.h"
#include "UIGameplayTags.h"
#include "Marketplace/MarketplacePolicy.h"
#include "Marketplace/SearchStacksListing_ListingsWidget.h"

#define MP_DESCRIPTION_DESCRIPTION TEXT("Description")
#define MP_DESCRIPTION_CREATED_AT TEXT("Created at")
#define MP_DESCRIPTION_UPDATED_AT TEXT("Updated at")


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

void USearchStacksListingWidget::FulfillOrder()
{
	UCustomLocalPlayer* LocalPlayer = Cast<UCustomLocalPlayer>(GetOwningLocalPlayer());
	UMarketplacePolicy* Policy = LocalPlayer->GetGameUIPolicy()->GetMarketplacePolicy();

	if (!Policy)
	{
		return;
	}
	
	if(Listings->GetSelectedItemWidget())
	{
		GetUnsignedFulfillOrderTransactionsRequest Request;

		Request.ListingId = Listings->GetSelectedItemWidget()->GetListingId();
		Request.TakerAddress = LocalPlayer->GetPassportWalletAddress();
		
		Policy->GetImmutableQuery()->GetUnsignedFulfillOrderTransactions(Request, ImmutableQuery::FGetUnsignedFulfillOrderTransactionsDelegate::CreateUObject(this, &USearchStacksListingWidget::OnGetUnsignedFulfillOrderTransaction));
	}
}

void USearchStacksListingWidget::OnGetUnsignedFulfillOrderTransaction(const GetUnsignedFulfillOrderTransactionsResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		UCustomGameInstance::SendSystemMessage(this, FUIErrors::Undefined, FText::FromString(TEXT("Error")), FText::FromString(Response.GetResponseString()));

		return;
	}

	UE_LOG(LogSampleGame, Log, TEXT("GetUnsignedFulfillOrderTransaction Expiration: %s"), *Response.Expiration);

	for (int32 i = 0; i < Response.Actions.Num(); i++)
	{
		UE_LOG(LogSampleGame, Log, TEXT("GetUnsignedFulfillOrderTransaction Actions: %s"), *Response.Actions[i].ToString());
	}
}

