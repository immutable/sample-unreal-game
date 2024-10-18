#pragma once

#include "OpenAPIStackBundle.h"
#include "Base/ItemWidget.h"
#include "UI/Interfaces/IOpenAPIProcessorInterface.h"

#include "StackItemWidget.generated.h"


/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class SAMPLEGAME426_API UStackItemWidget : public UItemWidget, public IMarketplaceOpenAPIProcessorInterface
{
	GENERATED_BODY()

public:
	virtual void ProcessModel(const ImmutableOpenAPI::Model& Data) override;
	virtual void SetOriginalState() override;

	TSharedPtr<ImmutableOpenAPI::OpenAPIStackBundle> GetStackBundle() const;

protected:
	void SetListingCount(int32 Count);
	void SetTextureNFT(TSoftObjectPtr<UTexture2D> Texture);
	void SetName(const FString& Name);
	void SetPrice(const ImmutableOpenAPI::OpenAPIMarketPriceDetails& PriceDetails);
	void SetPriceTokenName(const FString& Name);

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

private:
	TSharedPtr<ImmutableOpenAPI::OpenAPIStackBundle> StackBundle;
	
};
