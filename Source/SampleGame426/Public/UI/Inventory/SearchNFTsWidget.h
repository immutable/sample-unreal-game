#pragma once

#include "Base/ActivatableWidgetWithControlPanels.h"
#include "UI/Interfaces/IItemListInterface.h"
#include "Marketplace/MarketplacePolicy.h"
#include "Base/ItemListWidget.h"
#include "Inventory/SearchNFTsItemWidget.h"
#include "APIMetadataSearchApi.h"
#include "APIOrderbookApi.h"
#include "APIOrdersApi.h"
#include "APIPage.h"

#include "SearchNFTsWidget.generated.h"

/**
 * @class USearchNfTsWidget
 * @ingroup Inventory
 * @brief A widget class for searching NFTs within the inventory UI.
 */
UCLASS(Abstract)
class SAMPLEGAME426_API USearchNfTsWidget : public UActivatableWidgetWithControlPanels, public IItemListInterface
{
	GENERATED_BODY()

public:
	/**
	 * Refreshes the list of NFTs owned by the currently logged-in Immutable Passport user and displays them in the inventory widget. This method overrides IItemListInterface::RefreshItemList.	 
	 *
	 * @param PageCursor An optional string representing the cursor for pagination. 
	 *                   If provided, the item list will be refreshed starting from the specified page cursor.
	 */
	virtual void RefreshItemList(TOptional<FString> PageCursor) override;

protected:
	/* UUserWidget interface  */
	virtual void NativeOnInitialized() override;
	/* UUserWidget interface */
	/* UActivatableWidget interface */
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	/* UActivatableWidget interface */

	/* UActivatableWidgetWithControlPanels interface */
	virtual void SetupControlButtons(class UAWStackWithControlPanels* HostLayer) override;
	/* UActivatableWidgetWithControlPanels interface */

	/**
	 * Handles the response from the SearchNFTs Immutable zkEVM API call.
	 * @see ImmutablezkEVMAPI::APIStacksApi::SearchNFTs
	 *
	 * @param Response The response object containing the results of the NFT search.
	 */
	void OnSearchNFTsResponse(const ImmutablezkEVMAPI::APIMetadataSearchApi::SearchNFTsResponse& Response);
	/**
	 * Handles the selection state of an item in the inventory.
	 *
	 * @param IsSelected A boolean indicating whether the item is selected.
	 * @param ItemWidget A pointer to the UItemWidget representing the item.
	 */
	void OnItemSelection(bool IsSelected, UItemWidget* ItemWidget);

private:
	/**
	 * Handles the pagination of inventory API query results.
	 *
	 * @param PageData The pagination data, represented by an ImmutablezkEVMAPI::APIPage object.
	 */
	void HandlePageData(const ImmutablezkEVMAPI::APIPage& PageData);
	/**
	 * Handles the event when the control panel button is clicked. For example Buy, Sell, etc.
	 *
	 * @param ButtonTag The gameplay tag associated with the clicked button.
	 */
	void OnButtonClicked(FGameplayTag ButtonTag);
	/**
	 * Handles the event when the player confirms the marketplace NFT listing action in the dialog.
	 *
	 * @param DialogPtr A pointer to the dialog where the sell action was confirmed.
	 * @param Result The result of the dialog interaction, indicating the player's choice.
	 */
	UFUNCTION()
	void OnPlayerConfirmedSell(UDialog* DialogPtr, EDialogResult Result);
	/**
	 * Called when the player confirms the cancellation of the marketplace NFT listing action.
	 *
	 * @param DialogPtr A pointer to the dialog that was used for the confirmation.
	 * @param Result The result of the dialog interaction.
	 */
	UFUNCTION()
	void OnPlayerConfirmedCancelSell(UDialog* DialogPtr, EDialogResult Result);
	/**
	 * Handles the preparation of the marketplace NFT listing based on the response from the OpenAPIOrderbookApi.
	 * @see https://docs.immutable.com/products/zkEVM/orderbook/create-listing#prepare-the-listing
	 *
	 * @param Response The response received from the PrepareListing API call.
	 */
	void OnPrepareListing(const ImmutableOrderbook::APIOrderbookApi::PrepareListingResponse& Response);
	/**
	 * Handles the creation of the marketplace NFT listing.
	 * @see https://docs.immutable.com/products/zkEVM/orderbook/create-listing#create-the-listing
	 *
	 * @param Response The response received from the CreateListing API call.
	 */
	void OnCreateListing(const ImmutableOrderbook::APIOrderbookApi::CreateListingResponse& Response);
	/**
	 * Handles the response for canceling the marketplace NFT listing.
	 * @see https://docs.immutable.com/products/zkEVM/orderbook/cancel
	 *
	 * @param Response The response object containing details about the canceled orders.
	 */
	void OnCancelOrdersOnChain(const ImmutableOrderbook::APIOrderbookApi::CancelOrdersOnChainResponse& Response);

	/**
	 * Handles the dialog callback action such as close, cancel, or confirm.
	 *
	 * @param DialogPtr A pointer to the dialog that is being processed.
	 * @param Result The result of the dialog action.
	 */
	UFUNCTION()
	void OnProcessDialogAction(UDialog* DialogPtr, EDialogResult Result);

	void ConfirmListing(const FString& ListingId);
	void OnGetListing(const ImmutablezkEVMAPI::APIOrdersApi::GetListingResponse& Response);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UItemListWidget* ListPanel = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* PreviousPageButton = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* NextPageButton = nullptr;

protected:
	TWeakObjectPtr<UMarketplacePolicy> Policy;

	ImmutablezkEVMAPI::APIPage PageCursors;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USearchNFTsItemWidget> SelectedItemWidget;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UControlPanelButton> SellButton;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UControlPanelButton> CancelSellButton;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDialog> ProcessingDialog;
};