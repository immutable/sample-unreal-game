#include "Inventory/SearchNFTsItemWidget.h"

#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "LogSampleGame.h"
#include "OpenAPINFTBundle.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Marketplace/MarketplacePolicy.h"


void USearchNFTsItemWidget::ProcessModel(const ImmutableIndexerSearchAPI::Model& Data)
{
	NFTBundle = MakeShareable(new ImmutableIndexerSearchAPI::OpenAPINFTBundle(static_cast<const ImmutableIndexerSearchAPI::OpenAPINFTBundle&>(Data)));
	
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
	
	SetBalance(Balance);

	SetVisibility(ESlateVisibility::SelfHitTestInvisible);	
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
