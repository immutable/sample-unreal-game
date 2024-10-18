#pragma once

#include "Base/ItemWidget.h"
#include "UI/Interfaces/IOpenAPIProcessorInterface.h"

#include "SearchNFTsItemWidget.generated.h"


namespace ImmutableOpenAPI
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
	/* IInventoryOpenAPIProcessorInterface interface */
	virtual void ProcessModel(const ImmutableOpenAPI::Model& Data) override;
	/* IInventoryOpenAPIProcessorInterface interface */

	void SetListForSellStatus(bool ListedStatus);
	bool IsListedForSell() const;
	FString GetTokenId() const;
	FString GetContractAddress() const;
	FString GetListingId() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void BP_OnSetListForSellStatus(bool IsItemListed);

protected:
	void SetTextureNFT(TSoftObjectPtr<UTexture2D> Texture);
	void SetName(const FString& Name);
	void SetBalance(int32 Balance);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta=(BindWidget))
	class UTextBlock* NFTName = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta=(BindWidget))
	class UImage* NFTThumbnail  = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta=(BindWidget))
	class UTextBlock* NFTBalance  = nullptr;
	
private:
	TSharedPtr<ImmutableOpenAPI::OpenAPINFTBundle> NFTBundle;
	bool bIsListed = false;
	
};
