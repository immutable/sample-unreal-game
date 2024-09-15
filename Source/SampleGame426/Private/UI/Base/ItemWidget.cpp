#include "Base/ItemWidget.h"

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

void UItemWidget::SetName(const FString& Name)
{
	if (!NameNFT)
	{
		UE_LOG(LogSampleGame, Error, TEXT("NFT text widget is not assigned."));
		
		return;
	}
	
	NameNFT->SetText(FText::FromString(Name));
}

void UItemWidget::SetTotalCount(int32 Count)
{
	if (!TotalCount)
	{
		UE_LOG(LogSampleGame, Error, TEXT("NFT total count widget is not assigned."));
		
		return;
	}

	TotalCount->SetText(FText::AsNumber(Count));
}
