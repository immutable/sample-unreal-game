// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"

#include "LogImmutableUI.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UItemWidget::SetTextureNFT(TSoftObjectPtr<UTexture2D> Texture)
{
	if (!TextureNFT)
	{
		UE_LOG(LogImmutableUI, Error, LOG_UI_ITEM_WIDGET_TEXTURE_WIDGET_NULL);
		
		return;	
	}
	
	UTexture2D* SourceTexturePtr = Texture.LoadSynchronous();

	if (SourceTexturePtr)
	{
		TextureNFT->SetBrushFromTexture(SourceTexturePtr);
	}
}

void UItemWidget::SetName(FName Name)
{
	if (!NameNFT)
	{
		UE_LOG(LogImmutableUI, Error, LOG_UI_ITEM_WIDGET_NAME_WIDGET_NULL);
		
		return;
	}
	
	NameNFT->SetText(FText::FromName(Name));
}

void UItemWidget::SetPrice(float Price)
{
	if (!PriceNFT)
	{
		UE_LOG(LogImmutableUI, Error, LOG_UI_ITEM_WIDGET_PRICE_WIDGET_NULL);
		
		return;
	}

	PriceNFT->SetText(FText::AsCurrency(Price));
}
