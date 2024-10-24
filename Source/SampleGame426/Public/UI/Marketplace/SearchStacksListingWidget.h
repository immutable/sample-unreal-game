#pragma once

#include "APIOrderbookApi.h"
#include "Base/ActivatableWidgetWithControlPanels.h"
#include "Base/ItemWidget.h"
#include "UI/Interfaces/IOpenAPIProcessorInterface.h"

#include "SearchStacksListingWidget.generated.h"


/**
 * @class USearchStacksListingWidget
 * @ingroup Marketplace
 * @brief A widget class for displaying search stack NFT details and list of NFTs offered for purchase.
 * @details This widget is responsible for displaying the details of a selected NFT such as general information(name, NFT thumbnail, description and dates), metadata.
 * It also displays a list of NFTs offered for purchase by users.
 */
UCLASS(Abstract)
class SAMPLEGAME426_API USearchStacksListingWidget : public UActivatableWidgetWithControlPanels, public IMarketplaceOpenAPIProcessorInterface
{
	GENERATED_BODY()

public:
	/* UActivatableWidget interface */
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	/* UActivatableWidget interface */
	
	/* IMarketplaceOpenAPIProcessorInterface interface */
	virtual void ProcessModel(const ImmutablezkEVMAPI::Model& Data) override;
	/* IMarketplaceOpenAPIProcessorInterface interface */

	/* UActivatableWidgetWithControlPanels interface */
	virtual void SetupControlButtons(class UAWStackWithControlPanels* HostLayer) override;	
	virtual void Refresh() override;
	/* UActivatableWidgetWithControlPanels interface */
	
protected:
	/**
	 * Adds a NFT general information such as description, dates etc.
	 * @note This event is implemented by widget.
	 *
	 * @param Name The name of the description record.
	 * @param Value The value associated with the description record.
     * // Example usage:
     * AddDescriptionRecord(TEXT("Description"), TEXT("This item is awesome!"));
     */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void AddDescriptionRecord(const FString& Name, const FString& Value);

	/**
	 * Adds a metadata information.
	 * @note This event is implemented by widget.
	 *
	 * @param Name The name of the metadata attribute.
	 * @param Value The value of the metadata attribute.
	 * @example
     * // Example usage:
     * AddMetadataAttribute(TEXT("Rarity"), TEXT("Legendary"));
     */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void AddMetadataAttribute(const FString& Name, const FString& Value);

	/**
	 * Sets the thumbnail image for NFT.
	 * @note This event is implemented by widget.
	 *
	 * @param Thumbnail The UTexture2D object representing the thumbnail image to be set.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void SetThumbnail(UTexture2D* Thumbnail);

	/**
	 * Sets the name for NFT.
	 * @note This event is implemented by widget.
	 *
	 * @param Name NFT name.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void SetName(const FString& Name);

	/**
	 * Resets the search stacks listing widget to its default state.
	 *
	 * @note This event is implemented by widget.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void BP_Reset();

private:
	/**
	 * Handles the change in selection status of an item.
	 *
	 * @param IsItemSelected A boolean indicating whether the item is selected.
	 * @param ItemWidget A pointer to the UItemWidget representing the item whose selection status has changed.
	 */
	void OnItemSelectionStatusChange(bool IsItemSelected, UItemWidget* ItemWidget);
	/**
	 * Handles the fulfillment of an order that is recieved from Orderbook API.
	 * This method is called when an order is fulfilled and processes the response.
	 *
	 * @param Response The response received from the Orderbook API FulfillOrder call.
	 */
	void OnFulfillOrder(const ImmutableOrderbook::APIOrderbookApi::FulfillOrderResponse& Response);

	/**
	 * Handles the event when the buy button of the control panel is clicked.
	 *
	 * @param ButtonTag The gameplay tag associated with the button that was clicked.
	 * @see Source/SampleGame426/Public/UI/UIGameplayTags.h
	 */
	void OnBuyButtonClicked(FGameplayTag ButtonTag);

	/**
	 * Handles the dialog callback action such as close, cancel, or confirm.
	 *
	 * @param DialogPtr A pointer to the dialog that is being processed.
	 * @param Result The result of the dialog action.
	 */
	UFUNCTION()
	void OnProcessDialogAction(UDialog* DialogPtr, EDialogResult Result);
	
protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class USearchStacksListing_ListingsWidget* Listings = nullptr;

	UItemWidget* SelectedItem = nullptr;
	UControlPanelButton* BuyButton = nullptr;
	UDialog* ProcessingDialog = nullptr;
};
