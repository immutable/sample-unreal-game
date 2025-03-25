#include "Marketplace/SearchStacksContractSelectItemWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"

void USearchStacksContractSelectItemWidget::SetTextureNFT(TSoftObjectPtr<UTexture2D> Texture)
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

void USearchStacksContractSelectItemWidget::SetName(const FString& Name)
{
	if (NFTName)
	{
		NFTName->SetText(FText::FromString(Name));
	}
}