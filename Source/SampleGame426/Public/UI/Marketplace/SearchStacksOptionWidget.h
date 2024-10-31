#pragma once

#include "APIStacksApiOperations.h"
#include "Base/ActivatableWidgetWithControlPanels.h"
#include "Data/NFTMetadataAttributeDataAsset.h"
#include "Interfaces/IItemListInterface.h"

#include "SearchStacksOptionWidget.generated.h"


/**
 * @class USearchStacksOptionWidget
 * @ingroup Marketplace
 * @brief A widget class for handling search stack options/filters in the marketplace UI.
 * @details This widget is responsible for managing filters widget which are created and added to scroll view/widget.
 * The filters are used to filter the search results based on the metadata attributes of NFTs.
 * In addtion, there is a keyword search bar which is used to filter the search results based on the keyword.
 */
UCLASS(Abstract)
class SAMPLEGAME426_API USearchStacksOptionWidget : public UActivatableWidgetWithControlPanels, public IItemListInterface
{
	GENERATED_BODY()

public:
	/* UActivatableWidgetWithControlPanels interface */
	virtual void Refresh() override;
	/* UActivatableWidgetWithControlPanels interface */

	/**
	 * Refreshes the filters in the marketplace search option widget. Overrides IItemListInterface::RefreshItemList.
	 *
	 * @param PageCursor An optional string representing the cursor for pagination. 
	 *                   If provided, the item list will be refreshed starting from the specified page cursor.
	 */
	virtual void RefreshItemList(TOptional<FString> PageCursor) override;
	
	/**
	 * Adds a NFT metadata filter to the search options widget.
	 *
	 * @note This event is implemented by widget.
	 * @param Name The name of NFT metadata.
	 * @param Values An array of values associated with NFT metadata.
	 */	
	UFUNCTION(BlueprintImplementableEvent)
	void AddMetadataFilter(const FString& Name, const TArray<FString>& Values);

	/**
	 * Sets the keyword for the search stack search.
	 *
	 * @param Keyword The keyword to be set.
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void SetKeyword(const FString& Keyword);

	/**
	 * Sets the traits for search stack search.
	 *
	 * @param Traits An array of FNFTMetadataAttribute_TraitType objects representing the traits to be set.
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void SetTraits(const TArray<FNFTMetadataAttribute_TraitType>& Traits);

	/** 
	 * Called when the search is initialized.
	 *
	 * @note This event is implemented by widget.
	 * @details This method is triggered to perform any necessary setup or initialization
	 * tasks when the search functionality is ready to be used.
	 */ 
	UFUNCTION(BlueprintImplementableEvent)
	void OnSearchInitilized();

protected:
	virtual void SetupControlButtons(class UAWStackWithControlPanels* HostLayer) override;
	void OnListFiltersResponse(const ImmutablezkEVMAPI::APIStacksApi::ListFiltersResponse& Response);

protected:
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Metadata")
	// TSoftObjectPtr<UNFTMetadataAttributeDataAsset> AttributeMetadata;

private:
	UPROPERTY(Transient)
	UControlPanelButton* SearchButton = nullptr;
	
};