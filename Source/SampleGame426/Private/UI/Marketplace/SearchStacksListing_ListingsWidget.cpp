#include "Marketplace/SearchStacksListing_ListingsWidget.h"

#include "CustomGameInstance.h"
#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "IContentBrowserSingleton.h"
#include "LogSampleGame.h"
#include "OpenAPIListing.h"
#include "UIGameplayTags.h"
#include "Components/ScrollBox.h"
#include "Marketplace/MarketplacePolicy.h"
#include "Marketplace/MarketplaceUtility.h"
#include "Online/ImmutableQuery.h"

void USearchStacksListing_ListingsWidget::AddItem(const ImmutableOpenAPI::OpenAPIListing& Listing)
{
	if (ScrollBoxListings)
	{
		USearchStacksListing_ListingItemWidget* ListingsItemWidget = CreateWidget<USearchStacksListing_ListingItemWidget>(ScrollBoxListings, ItemWidgetClass.LoadSynchronous());
		UPanelSlot* ScrollBoxSlot = ScrollBoxListings->AddChild(ListingsItemWidget);
		
		if (ScrollBoxSlot)
		{
			auto Decimals = Listing.PriceDetails.Token.Decimals;
			
			if (Decimals.IsSet())
			{
				FString Price = FMarketplaceUtility::ConvertMarketplaceTokenValue(Decimals.GetValue(), Listing.PriceDetails.Amount.Value);
				FString FeeProtocol, FeeRoyalty;

				for (const auto& Fee : Listing.PriceDetails.Fees)
				{
					switch(Fee.Type)
					{
					case ImmutableOpenAPI::OpenAPIFee::TypeEnum::Protocol:
						FeeProtocol = FMarketplaceUtility::ConvertMarketplaceTokenValue(Decimals.GetValue(), Fee.Amount);	
					break;
					case ImmutableOpenAPI::OpenAPIFee::TypeEnum::Royalty:
						FeeRoyalty = FMarketplaceUtility::ConvertMarketplaceTokenValue(Decimals.GetValue(), Fee.Amount);
					break;
					default:;
					}
				}
				
				ListingsItemWidget->RegisterOnSelection(USearchStacksListing_ListingItemWidget::FOnListingItemSelection::CreateUObject(this, &USearchStacksListing_ListingsWidget::OnItemSelection));
				ListingsItemWidget->SetListingId(Listing.ListingId);
				ListingsItemWidget->SetData(Listing.TokenId,
					Listing.Amount,
					FeeProtocol,
					FeeRoyalty,
					Price,
					Listing.PriceDetails.Token.Symbol.GetValue());
			}
		}
	}
}

void USearchStacksListing_ListingsWidget::Buy()
{
	UCustomLocalPlayer* LocalPlayer = Cast<UCustomLocalPlayer>(GetOwningLocalPlayer());
	UMarketplacePolicy* Policy = LocalPlayer->GetGameUIPolicy()->GetMarketplacePolicy();

	if (!Policy)
	{
		return;
	}
	
	if(SelectedItemWidget)
	{
		GetUnsignedFulfillOrderTransactionsRequest Request;

		Request.ListingId = SelectedItemWidget->GetListingId();
		Request.TakerAddress = LocalPlayer->GetPassportWalletAddress();
		
		Policy->GetImmutableQuery()->GetUnsignedFulfillOrderTransactions(Request, ImmutableQuery::FGetUnsignedFulfillOrderTransactionsDelegate::CreateUObject(this, &USearchStacksListing_ListingsWidget::OnGetUnsignedFulfillOrderTransaction));
	}
}

void USearchStacksListing_ListingsWidget::OnItemSelection(bool IsSelected, USearchStacksListing_ListingItemWidget* ListingItemWidget)
{
	if (SelectedItemWidget == ListingItemWidget && !IsSelected)
	{
		SelectedItemWidget = nullptr;
		return;
	}
	
	if (SelectedItemWidget != ListingItemWidget && IsSelected)
	{
		SelectedItemWidget->Deselect();
		SelectedItemWidget = ListingItemWidget;
	}
}

void USearchStacksListing_ListingsWidget::OnGetUnsignedFulfillOrderTransaction(const GetUnsignedFulfillOrderTransactionsResponse& Response)
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
