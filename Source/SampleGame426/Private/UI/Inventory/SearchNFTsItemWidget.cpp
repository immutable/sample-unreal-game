#include "Inventory/SearchNFTsItemWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"

#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "LogSampleGame.h"
#include "APINFTBundle.h"
#include "Marketplace/MarketplacePolicy.h"

void USearchNFTsItemWidget::ProcessModel(const ImmutablezkEVMAPI::Model& Data)
{
	NFTBundle = MakeShareable(new ImmutablezkEVMAPI::APINFTBundle(static_cast<const ImmutablezkEVMAPI::APINFTBundle&>(Data)));

	if (!NFTBundle.IsValid())
	{
		return;
	}

	auto Name = NFTBundle->NftWithStack.Name;

	if (!Name.IsSet())
	{
		UE_LOG(LogSampleGame, Error, TEXT("SearchNFTsItemWidget - Stack name was not set %s"), *(NFTBundle->NftWithStack.StackId.ToString()));

		return;
	}

	if (UMarketplacePolicy* Policy = GetOwningCustomLocalPLayer()->GetGameUIPolicy()->GetMarketplacePolicy())
	{
		FName RowName = FName(*Name->Replace(TEXT(" "),TEXT("_")));
		auto DatatableRow = Policy->FindNFTTextureRow(RowName);

		if (!DatatableRow)
		{
			UE_LOG(LogSampleGame, Error, TEXT("SearchNFTsItemWidget - No data row %s was not found"), *RowName.ToString());
			return;
		}

		SetTextureNFT(DatatableRow->Thumbnail);
		SetName(DatatableRow->Name);
	}

	int32 Balance = 0;

	if (NFTBundle->NftWithStack.Balance.IsSet())
	{
		Balance = NFTBundle->NftWithStack.Balance.GetValue();
	}

	SetID(NFTBundle->NftWithStack.TokenId);
	SetBalance(Balance);

	Show();
}

void USearchNFTsItemWidget::SetListForSellStatus(bool ListedStatus)
{
	if (bIsListed == ListedStatus)
	{
		return;
	}

	bIsListed = ListedStatus;
	BP_OnSetListForSellStatus(bIsListed);
}

bool USearchNFTsItemWidget::IsListedForSell() const
{
	return bIsListed;
}

FString USearchNFTsItemWidget::GetTokenId() const
{
	if (NFTBundle.IsValid())
	{
		return NFTBundle->NftWithStack.TokenId;
	}

	return TEXT("");
}

FString USearchNFTsItemWidget::GetContractAddress() const
{
	if (NFTBundle.IsValid())
	{
		return NFTBundle->NftWithStack.ContractAddress;
	}

	return TEXT("");
}

FString USearchNFTsItemWidget::GetListingId() const
{
	if (NFTBundle.IsValid() && NFTBundle->Listings.Num())
	{
		return NFTBundle->Listings[0].ListingId;
	}

	return TEXT("");
}

void USearchNFTsItemWidget::SetTextureNFT(TSoftObjectPtr<UTexture2D> Texture)
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

void USearchNFTsItemWidget::SetName(const FString& Name)
{
	if (NFTName)
	{
		NFTName->SetText(FText::FromString(Name));
	}
}

void USearchNFTsItemWidget::SetBalance(int32 Balance)
{
	if (NFTBalance)
	{
		NFTBalance->SetText(FText::AsNumber(Balance));
	}
}

void USearchNFTsItemWidget::SetID(const FString& ID)
{
	if (NFTID)
	{
		NFTID->SetText(FText::FromString(ID));
	}
}