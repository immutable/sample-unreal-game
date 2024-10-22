#pragma once

#include "Base/ItemWidget.h"
#include "UI/Interfaces/IOpenAPIProcessorInterface.h"

#include "SearchNFTsItemWidget.generated.h"


namespace ImmutableOpenAPI
{
	class OpenAPINFTBundle;
}

/**
 * @class USearchNFTsItemWidget
 * @ingroup Inventory
 * @brief A widget class representing a single item or card of a searched NFT in the inventory.
 */
UCLASS(Abstract, BlueprintType)
class SAMPLEGAME426_API USearchNFTsItemWidget : public UItemWidget, public IInventoryOpenAPIProcessorInterface
{
	GENERATED_BODY()

public:
	/* IInventoryOpenAPIProcessorInterface interface */
	virtual void ProcessModel(const ImmutableOpenAPI::Model& Data) override;
	/* IInventoryOpenAPIProcessorInterface interface */

	/**
	 * Sets the list status for selling items.
	 *
	 * @param ListedStatus A boolean value indicating whether the item is listed for sale (true) or not (false).
	 */
	void SetListForSellStatus(bool ListedStatus);
	/**
	 * @brief Checks if the item is listed for sale.
	 *
	 * @return A boolean value indicating whether the item is listed for sale.
	 */
	bool IsListedForSell() const;
	/**
	 * @brief Retrieves the token ID associated with the displayed NFT in the inventory.
	 * @see ImmutableOpenAPI::OpenAPINFTWithStack in ImmutableOpenAPI plugin.
	 *
	 * @return A string representing the token ID.
	 */
	FString GetTokenId() const;
	/**
	 * @brief Retrieves the NFT contract address associated with the displayed NFT in the inventory.
	 * @see ImmutableOpenAPI::OpenAPINFTWithStack in ImmutableOpenAPI plugin.
	 *
	 * @return A string representing the contract address.
	 */
	FString GetContractAddress() const;
	/**
	 * @brief Retrieves the listing ID from the ImmutableOpenAPI, which is used to cancel the marketplace NFT listing.
	 * @see ImmutableOpenAPI::OpenAPIListing in ImmutableOpenAPI plugin.
	 *
	 * @param Id The unique identifier for the listing parsed from Immutable API OpenAPIListing.
	 */
	FString GetListingId() const;

	/**
	 * Called to update the list status of an item for selling.
	 *
	 * @note This event is implemented by widget.	 
	 * @param IsItemListed A boolean indicating whether the item is listed for sale.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void BP_OnSetListForSellStatus(bool IsItemListed);

protected:
	/**
	 * Sets the texture for the NFT card.
	 *
	 * @param Texture A soft object pointer to the UTexture2D asset representing the NFT texture.
	 */
	void SetTextureNFT(TSoftObjectPtr<UTexture2D> Texture);
	/**
	 * Sets the name of the NFT item.
	 *
	 * @param Name The name to set for the NFT item.
	 */
	void SetName(const FString& Name);
	/**
	 * Sets the balance of the NFT item owned by the current user.
	 *
	 * @param Balance The new balance to be set.
	 */
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
