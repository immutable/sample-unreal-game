#include "Marketplace/SearchStacksListing_ListingsWidget.h"

#include "IContentBrowserSingleton.h"
#include "OpenAPIListing.h"
#include "Components/ScrollBox.h"
#include "Marketplace/MarketplaceUtility.h"

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
