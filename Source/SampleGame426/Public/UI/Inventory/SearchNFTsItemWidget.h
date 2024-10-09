#pragma once

#include "Base/ItemWidget.h"
#include "UI/Interfaces/IOpenAPIProcessorInterface.h"

#include "SearchNFTsItemWidget.generated.h"


namespace ImmutableIndexerSearchAPI
{
	class OpenAPINFTBundle;
}

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class SAMPLEGAME426_API USearchNFTsItemWidget : public UItemWidget, public IInventoryOpenAPIProcessorInterface
{
	GENERATED_BODY()

public:
	virtual void ProcessModel(const ImmutableIndexerSearchAPI::Model& Data) override;

protected:
	void SetTextureNFT(TSoftObjectPtr<UTexture2D> Texture);
	void SetName(const FString& Name);
	void SetBalance(int32 Balance);

private:
	TSharedPtr<ImmutableIndexerSearchAPI::OpenAPINFTBundle> NFTBundle;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta=(BindWidget))
	class UTextBlock* NFTName = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta=(BindWidget))
	class UImage* NFTThumbnail  = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta=(BindWidget))
	class UTextBlock* NFTBalance  = nullptr;
	
};
