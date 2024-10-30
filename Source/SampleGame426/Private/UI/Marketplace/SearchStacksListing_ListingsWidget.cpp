﻿#include "Marketplace/SearchStacksListing_ListingsWidget.h"

#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "APIFee.h"
#include "Components/ScrollBox.h"
#include "ImmutablezkEVMAPI/Public/APIFee.h"
#include "UI/Utility/MathUtility.h"


void USearchStacksListing_ListingsWidget::AddItem(const ImmutablezkEVMAPI::APIListing& Listing, bool IsIdEven, const UItemWidget::FOnSelectionChange& InOnSelectionChangeDelegate)
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
				FString Price = FMathUtility::ConvertWeiStringToFloatValueString(Decimals.GetValue(), Listing.PriceDetails.Amount);
				FString FeeProtocol, FeeRoyalty;

				for (const auto& Fee : Listing.PriceDetails.Fees)
				{
					switch(static_cast<ImmutablezkEVMAPI::APIFee::TypeEnum>(Fee.Type))
					{
					case ImmutablezkEVMAPI::APIFee::TypeEnum::Protocol:
						FeeProtocol = FMathUtility::ConvertWeiStringToFloatValueString(Decimals.GetValue(), Fee.Amount);	
					break;
					case ImmutablezkEVMAPI::APIFee::TypeEnum::Royalty:
						FeeRoyalty = FMathUtility::ConvertWeiStringToFloatValueString(Decimals.GetValue(), Fee.Amount);
					break;
					default:;
					}
				}

				ListingsItemWidget->RegisterOnSelectionChange(InOnSelectionChangeDelegate);
				ListingsItemWidget->SetIsOwned(Listing.Creator.Equals(GetOwningCustomLocalPLayer()->GetPassportWalletAddress()));
				ListingsItemWidget->SetListingId(Listing.ListingId);
				ListingsItemWidget->SetData(Listing.TokenId,
					Listing.Amount,
					FeeProtocol,
					FeeRoyalty,
					Price,
					Listing.PriceDetails.Token.Symbol.GetValue(),
					IsIdEven);
				ListingsItemWidget->Show();
			}
		}
	}
}

void USearchStacksListing_ListingsWidget::Reset()
{
	if (ScrollBoxListings)
	{
		ScrollBoxListings->ClearChildren();
	}
}
