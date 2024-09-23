#pragma once

#include "Base/ItemWidget.h"
#include "UI/Interfaces/IOpenAPIProcessorInterface.h"
#include "NFT/NFT_TableRowBase.h"

#include "MarketplaceItemWidget.generated.h"


namespace ImmutableOpenAPI
{
	class OpenAPIStackBundle;
	class OpenAPIPriceDetails;
}

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class SAMPLEGAME426_API UMarketplaceItemWidget : public UItemWidget, public IOpenAPIProcessorInterface
{
	GENERATED_BODY()

public:
	virtual void ProcessModel(const ImmutableOpenAPI::Model& Data) override;

protected:
	/* UUserWidget */
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	/* UUserWidget */
	
	void SetListingCount(int32 Count);
	void SetTextureNFT(TSoftObjectPtr<UTexture2D> Texture);
	void SetName(const FString& Name);
	void SetPrice(const ImmutableOpenAPI::OpenAPIPriceDetails& PriceDetails);
	void SetPriceTokenName(const FString& Name);

private:
	FNFT_TableRowBase* FindTextureRow(FName RowName);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Marketplace", meta=(BindWidget))
	class UTextBlock* NFTName = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Marketplace", meta=(BindWidget))
	class UImage* NFTThumbnail  = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Marketplace", meta=(BindWidget))
	class UTextBlock* NFTListingCount  = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Marketplace", meta=(BindWidget))
	class UTextBlock* NFTLowestPrice = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Marketplace", meta=(BindWidget))
	class UTextBlock* NFTPriceTokenName  = nullptr;
	UPROPERTY(EditAnywhere, Category = "Marketplace")
	TSoftClassPtr<class UMarketplaceItemFullWidget> MarketplaceItemFullWidgetClass;
	UPROPERTY(EditAnywhere, Category = "Marketplace", meta = (RequiredAssetDataTags = "RowStructure=NFT_TableRowBase"))
	class UDataTable* NFT_DataSet;

private:
	TSharedPtr<ImmutableOpenAPI::OpenAPIStackBundle> StackBundle;
	
};
