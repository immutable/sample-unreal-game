#pragma once

#include "Base/ItemWidget.h"
#include "NFT/NFT_TableRowBase.h"

#include "MarketplaceItemWidget.generated.h"

namespace OpenAPI
{
	class OpenAPIPriceDetails;
}

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class SAMPLEGAME426_API UMarketplaceItemWidget : public UItemWidget
{
	GENERATED_BODY()

public:
	virtual void ProcessModel(const OpenAPI::Model* Data) override;

protected:
	void SetListingCount(int32 Count);
	void SetTextureNFT(TSoftObjectPtr<UTexture2D> Texture);
	void SetName(const FString& Name);
	void SetPrice(const OpenAPI::OpenAPIPriceDetails& PriceDetails);
	void SetPriceTokenName(const FString& Name);

private:
	FNFT_TableRowBase* FindTextureRow(FName RowName);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* NFTName = nullptr;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UImage* NFTThumbnail  = nullptr;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* NFTListingCount  = nullptr;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* NFTLowestPrice = nullptr;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* NFTPriceTokenName  = nullptr;
	UPROPERTY(EditAnywhere, Category = NFT, meta = (RequiredAssetDataTags = "RowStructure=NFT_TableRowBase"))
	class UDataTable* NFT_DataSet;

};
