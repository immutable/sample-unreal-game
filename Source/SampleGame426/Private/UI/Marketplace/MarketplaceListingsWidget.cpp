#include "Marketplace/MarketplaceListingsWidget.h"

#include "OpenAPIListing.h"
#include "Components/ScrollBox.h"
#include "Marketplace/MarketplaceUtility.h"

void UMarketplaceListingsWidget::AddItem(const OpenAPI::OpenAPIListing& Listing)
{
	if (ScrollBoxListings)
	{
		UMarketplaceListingsItemWidget* ListingsItemWidget = CreateWidget<UMarketplaceListingsItemWidget>(ScrollBoxListings, ItemWidgetClass.LoadSynchronous());		
		
		if (ScrollBoxListings->AddChild(ListingsItemWidget))
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
					case OpenAPI::OpenAPIFee::TypeEnum::Protocol:
						FeeProtocol = FMarketplaceUtility::ConvertMarketplaceTokenValue(Decimals.GetValue(), Fee.Amount);	
					break;
					case OpenAPI::OpenAPIFee::TypeEnum::Royalty:
						FeeRoyalty = FMarketplaceUtility::ConvertMarketplaceTokenValue(Decimals.GetValue(), Fee.Amount);
					break;
					default:;
					}
				}
			
				ListingsItemWidget->OnProcessPrice(Listing.TokenId,
					Listing.Amount,
					FeeProtocol,
					FeeRoyalty,
					Price,
					Listing.PriceDetails.Token.Symbol.GetValue());
			}
		}
	}
}
