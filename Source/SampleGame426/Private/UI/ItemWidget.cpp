// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"

#include "LogSampleGame.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UItemWidget::SetTextureNFT(TSoftObjectPtr<UTexture2D> Texture)
{
	if (!TextureNFT)
	{
		UE_LOG(LogSampleGame, Error, TEXT("NFT texture widget is not assigned."));
		
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
		UE_LOG(LogSampleGame, Error, TEXT("NFT text widget is not assigned."));
		
		return;
	}
	
	NameNFT->SetText(FText::FromName(Name));
}

void UItemWidget::SetPrice(float Price)
{
	if (!PriceNFT)
	{
		UE_LOG(LogSampleGame, Error, TEXT("NFT price widget is not assigned."));
		
		return;
	}

	PriceNFT->SetText(FText::AsCurrency(Price));
}
