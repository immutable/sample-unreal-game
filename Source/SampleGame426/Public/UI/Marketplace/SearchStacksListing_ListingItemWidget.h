#pragma once

#include "Base/ItemWidget.h"

#include "SearchStacksListing_ListingItemWidget.generated.h"


/**
 * @class USearchStacksListing_ListingItemWidget
 * @ingroup Marketplace
 * @brief A widget class of listed items in USearchStacksListing_ListingsWidget.
 */
UCLASS(Abstract, Blueprintable)
class SAMPLEGAME426_API USearchStacksListing_ListingItemWidget : public UItemWidget
{
	GENERATED_BODY()

public:
	/* UItemWidget interface */
	virtual void SetSelection(bool IsSelected) override;
	/* UItemWidget interface */
	
	/**
	 * Setter and getter of Immutable API stack listing ID used to perform purchase.
	 * @see ImmutableOpenAPI::OpenAPIListing in ImmutableOpenAPI plugin.
	 *
	 * @param Id The unique identifier for the listing parsed from Immutable API OpenAPIListing.
	 */
	void SetListingId(const FString& Id);
    const FString& GetListingId() const;

	/**
	 * Sets the display data for the listed item.
	 * @note This event is implemented by widget.	 
	 *
	 * @param TokenID The unique identifier for the NFT token.
	 * @param Amount The amount of listed NFTs. Usually one.
	 * @param FeeProtocol The protocol fee for the transaction.
	 * @param FeeRoyalty The royalty fee for the transaction.
	 * @param Price The price of the listed NFT.
	 * @param Currency The crypto currency in which the price is denominated.
	 * @param IsIdEven A boolean helps to choose color to hightlight record in the scrollable widget.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void SetData(const FString& TokenID, const FString& Amount, const FString& FeeProtocol, const FString& FeeRoyalty, const FString& Price, const FString& Currency, bool IsIdEven);

	/**
	 * Sets the ownership status of the listed NFT.
	 * @details This method is called when the ownership status of the listed NFT changes. If it is owned by the current user, the item will be highlighted.
	 *
	 * @param IsOwned A boolean value indicating whether the item is owned.
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void SetIsOwned(bool IsOwned);
	/**
	 * Blueprint-implementable event that is called to set the ownership status of the item.
	 * @note This event is implemented by widget.
	 *
	 * @param IsOwned A boolean value indicating whether the item is owned.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void BP_OnSetIsOwned(bool IsOwned);
	/**
	 * Checks if the item is owned.
	 *
	 * @return A boolean value indicating whether the item is owned.
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	bool IsOwned();

private:
	FString ListingId;
	bool bIsOwned = false;
};
