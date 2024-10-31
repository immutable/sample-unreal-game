#pragma once

#include "Base/ItemWidget.h"

#include "SearchStacksContractSelectItemWidget.generated.h"


class UTextBlock;
class UImage;

/**
 * @class USearchStacksContractSelectItemWidget
 * @ingroup Marketplace
 * @brief A widget class that represents an item in the search stacks contract select widget within the marketplace UI.
 * @see Blueprint that inherits from USearchStacksWidget. /Game/UI/Parts/Marketplace/WBP_SearchStacksContractSelect_Main
 */
UCLASS(Abstract, BlueprintType)
class SAMPLEGAME426_API USearchStacksContractSelectItemWidget : public UItemWidget
{
	GENERATED_BODY()

public:
	void SetContractAddress(const FString& InContractAddress) { ContractAddress = InContractAddress; }
	FString GetContractAddress() { return ContractAddress; }

	/**
	 * Sets the thumbnail texture for the NFT.
	 *
	 * @param Texture A soft object pointer to the UTexture2D asset to be set as the texture for the NFT.
	 */
	void SetTextureNFT(TSoftObjectPtr<UTexture2D> Texture);
	/**
	 * Sets the NFT name of the stack item widget.
	 *
	 * @param Name The new name to set for the stack item widget.
	 */
	void SetName(const FString& Name);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Marketplace", meta=(BindWidget))
	UTextBlock* NFTName = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Marketplace", meta=(BindWidget))
	UImage* NFTThumbnail  = nullptr;

private:
	FString ContractAddress;
	
};
