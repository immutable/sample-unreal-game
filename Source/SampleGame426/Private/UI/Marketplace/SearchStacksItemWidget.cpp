#include "Marketplace/SearchStacksItemWidget.h"

#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "LogSampleGame.h"
#include "APIStackBundle.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Marketplace/MarketplacePolicy.h"
#include "Math/BigInt.h"
#include "Marketplace/SearchStacksListingWidget.h"
#include "UI/Utility/MathUtility.h"
#include "NFT/NFT_TableRowBase.h"


void USearchStacksItemWidget::ProcessModel(const ImmutablezkEVMAPI::Model& Data)
{
	StackBundle = MakeShareable(new ImmutablezkEVMAPI::APIStackBundle(static_cast<const ImmutablezkEVMAPI::APIStackBundle&>(Data)));
	
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

TSharedPtr<ImmutablezkEVMAPI::APIStackBundle> USearchStacksItemWidget::GetStackBundle() const
{
	return StackBundle;
}

void USearchStacksItemWidget::SetTextureNFT(TSoftObjectPtr<UTexture2D> Texture)
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

void USearchStacksItemWidget::SetName(const FString& Name)
{
	if (NFTName)
	{
		NFTName->SetText(FText::FromString(Name));
	}
}

void USearchStacksItemWidget::SetPrice(const ImmutablezkEVMAPI::APIMarketPriceDetails& PriceDetails)
{
	if (!NFTLowestPrice)
	{
		return;
	}

	if (const ImmutablezkEVMAPI::APIMarketPriceERC20Token* APIMarketPriceERC20Token = PriceDetails.Token.OneOf.TryGet<ImmutablezkEVMAPI::APIMarketPriceERC20Token>())
	{
		const TOptional<int32>& Decimals = APIMarketPriceERC20Token->Decimals;

		if (Decimals.IsSet())
		{
			FString Price = FMathUtility::ConvertWeiStringToFloatValueString(Decimals.GetValue(), PriceDetails.Amount);

			NFTLowestPrice->SetText(FText::FromString(Price));
		}

		const TOptional<FString>& Symbol = APIMarketPriceERC20Token->Symbol;

		if (Symbol.IsSet())
		{
			SetPriceTokenName(Symbol.GetValue());
		}
	}
}

void USearchStacksItemWidget::SetPriceTokenName(const FString& Name)
{
	if (NFTPriceTokenName)
	{
		NFTPriceTokenName->SetText(FText::FromString(Name));
	}
}

void USearchStacksItemWidget::SetListingCount(int32 Count)
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
