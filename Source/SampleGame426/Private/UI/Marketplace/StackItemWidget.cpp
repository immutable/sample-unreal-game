#include "Marketplace/StackItemWidget.h"

#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "LogSampleGame.h"
#include "OpenAPIStackBundle.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Marketplace/MarketplacePolicy.h"
#include "Math/BigInt.h"
#include "Marketplace/SearchStacksListingWidget.h"
#include "UI/Utility/MathUtility.h"
#include "NFT/NFT_TableRowBase.h"


void UStackItemWidget::ProcessModel(const ImmutableOpenAPI::Model& Data)
{
	StackBundle = MakeShareable(new ImmutableOpenAPI::OpenAPIStackBundle(static_cast<const ImmutableOpenAPI::OpenAPIStackBundle&>(Data)));
	
	if (!StackBundle.IsValid())
	{
		return;
	}

	auto Name = StackBundle->Stack.Name;

	if (!Name.IsSet())
	{
		UE_LOG(LogSampleGame, Error, TEXT("MarketplaceItemWidget - Stack name was not set %s"), *(StackBundle->Stack.StackId.ToString()));

		return;
	}

	if (UMarketplacePolicy* Policy = GetOwningCustomLocalPLayer()->GetGameUIPolicy()->GetMarketplacePolicy())
	{
		FName RowName = FName(*Name->Replace(TEXT(" "),TEXT("_")));
		auto DatatableRow = Policy->FindNFTTextureRow(RowName);
		
		if (!DatatableRow)
		{
			UE_LOG(LogSampleGame, Error, TEXT("MarketplaceItemWidget - No data row %s was not found"), *RowName.ToString());
			return;
		}

		SetTextureNFT(DatatableRow->Thumbnail);
		SetName(DatatableRow->Name);
	}

	int32 NumberOfListing = StackBundle->Listings.Num();
	
	SetListingCount(NumberOfListing);

	if (NumberOfListing)
	{
		SetPrice(StackBundle->Listings[0].PriceDetails);
	}
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

TSharedPtr<ImmutableOpenAPI::OpenAPIStackBundle> UStackItemWidget::GetStackBundle() const
{
	return StackBundle;
}

void UStackItemWidget::SetTextureNFT(TSoftObjectPtr<UTexture2D> Texture)
{
	if (NFTThumbnail)
	{
		UTexture2D* SourceTexturePtr = Texture.LoadSynchronous();

		if (SourceTexturePtr)
		{
			NFTThumbnail->SetBrushFromTexture(SourceTexturePtr);
		}	
	}
}

void UStackItemWidget::SetName(const FString& Name)
{
	if (NFTName)
	{
		NFTName->SetText(FText::FromString(Name));
	}
}

void UStackItemWidget::SetPrice(const ImmutableOpenAPI::OpenAPIMarketPriceDetails& PriceDetails)
{
	if (NFTLowestPrice && PriceDetails.Token.Decimals.IsSet())
	{
		FString Price = FMathUtility::ConvertWeiStringToFloatValueString(PriceDetails.Token.Decimals.GetValue(), PriceDetails.Amount.Value);  

		NFTLowestPrice->SetText(FText::FromString(Price));

		SetPriceTokenName(PriceDetails.Token.Symbol.GetValue());
	}
}

void UStackItemWidget::SetPriceTokenName(const FString& Name)
{
	if (NFTPriceTokenName)
	{
		NFTPriceTokenName->SetText(FText::FromString(Name));
	}
}

void UStackItemWidget::SetListingCount(int32 Count)
{
	if (NFTListingCount)
	{
		NFTListingCount->SetText(FText::AsNumber(Count));
	}
	else
	{
		NFTListingCount->SetVisibility(ESlateVisibility::Hidden);
	}
}
