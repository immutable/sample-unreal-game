﻿#include "Marketplace/MarketplaceItemWIdget.h"

#include "CustomLocalPlayer.h"
#include "GameUIManagerSubsystem.h"
#include "LogSampleGame.h"
#include "OpenAPIStackBundle.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/DataTable.h"
#include "Math/BigInt.h"
#include "NFT/NFT_TableRowBase.h"
#include "Marketplace/MarketplaceItemFullWidget.h"
#include "Marketplace/MarketplaceUtility.h"


void UMarketplaceItemWidget::ProcessModel(const OpenAPI::Model* Data)
{
	StackBundle = MakeShareable(new OpenAPI::OpenAPIStackBundle(*(static_cast<const OpenAPI::OpenAPIStackBundle*>(Data))));

	if (!StackBundle.IsValid() || !NFT_DataSet)
	{
		return;
	}

	auto Name = StackBundle->Stack.Name;

	if (!Name.IsSet())
	{
		UE_LOG(LogSampleGame, Error, TEXT("MarketplaceItemWidget - Stack name was not set %s"), *(StackBundle->Stack.StackId.ToString()));

		return;
	}

	FName RowName = FName(*Name->Replace(TEXT(" "),TEXT("_")));
	auto DatatableRow = FindTextureRow(RowName);
		
	if (!DatatableRow)
	{
		UE_LOG(LogSampleGame, Error, TEXT("MarketplaceItemWidget - No data row was not found in %s"), *(NFT_DataSet->GetName()));
		return;
	}

	SetTextureNFT(DatatableRow->Thumbnail);
	SetName(DatatableRow->Name);


	int32 NumberOfListing = StackBundle->Listings.Num();
	
	SetListingCount(NumberOfListing);

	if (NumberOfListing)
	{
		SetPrice(StackBundle->Listings[0].PriceDetails);
	}

	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

FReply UMarketplaceItemWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDoubleClick(InGeometry,InMouseEvent);

	if (auto Widget = Cast<UMarketplaceItemFullWidget>(UGameUIManagerSubsystem::PushWidgetToLayer(GetOwningCustomLocalPLayer(), FGameplayTag::RequestGameplayTag(TEXT("UI.Layer.Menu")), MarketplaceItemFullWidgetClass.LoadSynchronous())))
	{
		Widget->ProcessModel(StackBundle.Get());
	}
	
	return Reply; 
}

void UMarketplaceItemWidget::SetTextureNFT(TSoftObjectPtr<UTexture2D> Texture)
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

void UMarketplaceItemWidget::SetName(const FString& Name)
{
	if (NFTName)
	{
		NFTName->SetText(FText::FromString(Name));
	}
}

void UMarketplaceItemWidget::SetPrice(const OpenAPI::OpenAPIPriceDetails& PriceDetails)
{
	if (NFTLowestPrice && PriceDetails.Token.Decimals.IsSet())
	{
		FString Price = FMarketplaceUtility::ConvertMarketplaceTokenValue(PriceDetails.Token.Decimals.GetValue(), PriceDetails.Amount.Value);  

		NFTLowestPrice->SetText(FText::FromString(Price));

		SetPriceTokenName(PriceDetails.Token.Symbol.GetValue());
	}
}

void UMarketplaceItemWidget::SetPriceTokenName(const FString& Name)
{
	if (NFTPriceTokenName)
	{
		NFTPriceTokenName->SetText(FText::FromString(Name));
	}
}

void UMarketplaceItemWidget::SetListingCount(int32 Count)
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

FNFT_TableRowBase* UMarketplaceItemWidget::FindTextureRow(FName RowName)
{
	if (NFT_DataSet)
	{
		FString ContextString;

		return NFT_DataSet->FindRow<FNFT_TableRowBase>(RowName, ContextString, true);
	}
	
	return nullptr;
}