#pragma once

#include "APIStackBundle.h"
#include "Base/ItemWidget.h"
#include "UI/Interfaces/IOpenAPIProcessorInterface.h"

#include "StackItemWidget.generated.h"


/**
 * @class UStackItemWidget
 * @ingroup Marketplace
 * @brief A widget class that represents an item in the search stack widget within the marketplace UI.
 * @see Blueprint that inherits from USearchStacksWidget. /Game/UI/Parts/Marketplace/WBP_SearchStackResults_Main
 */
UCLASS(Abstract, BlueprintType)
class SAMPLEGAME426_API UStackItemWidget : public UItemWidget, public IMarketplaceOpenAPIProcessorInterface
{
	GENERATED_BODY()

public:
	/* IMarketplaceOpenAPIProcessorInterface interface */
	virtual void ProcessModel(const ImmutablezkEVMAPI::Model& Data) override;
	/* IMarketplaceOpenAPIProcessorInterface interface */

	/**
	 * Retrieves the Immutable zkEVM API stack bundle associated with this NFT item.
	 *
	 * @return A shared pointer to an OpenAPIStackBundle object.
	 */
	TSharedPtr<ImmutablezkEVMAPI::APIStackBundle> GetStackBundle() const;

protected:
	/**
	 * Sets the listing count for the stack item widget.
	 *
	 * @param Count The number of listings to set.
	 */
	void SetListingCount(int32 Count);
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
	/**
	 * Sets the NFT price for the stack item widget.
	 *
	 * @param PriceDetails An object containing the market price details.
	 */
	void SetPrice(const ImmutablezkEVMAPI::APIMarketPriceDetails& PriceDetails);
	/**
	 * Sets the name of the cryptocurrency token used for the NFT price.
	 *
	 * @param Name The name of the price token to be set.
	 */
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
	TSharedPtr<ImmutablezkEVMAPI::APIStackBundle> StackBundle;
	
};
