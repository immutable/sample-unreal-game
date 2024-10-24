#pragma once

#include "APIPage.h"
#include "APIStacksApi.h"
#include "APIStacksApiOperations.h"
#include "Base/ActivatableWidgetWithControlPanels.h"
#include "Base/ItemListWidget.h"
#include "UI/Interfaces/IItemListInterface.h"

#include "SearchStacksWidget.generated.h"

UENUM()
enum class ESearchStacks_SortCategories : uint8
{
	Price
};


/**
 * @class USearchStacksWidget
 * @ingroup Marketplace
 * @brief A widget class that represents the search stacks results in the marketplace UI.
 * @details This widget is responsible for displaying item cards of NFT, with data parsed from search stacks JSON data received from the Immutable API.
 * The displayed items can be purchased or studied using NFT information displayed on the item card or the item card info widget USearchStacksListingWidget.
 * It also handles the selection, double-click, and sorting of item cards based on the selected sort category.
 */
UCLASS(Abstract)
class SAMPLEGAME426_API USearchStacksWidget : public UActivatableWidgetWithControlPanels, public IItemListInterface
{
	GENERATED_BODY()

public:
	/**
	 * Refreshes the item list in the marketplace search stacks widget. Overrides IItemListInterface::RefreshItemList.
	 *
	 * @param PageCursor An optional string representing the cursor for pagination. 
	 *                   If provided, the item list will be refreshed starting from the specified page cursor.
	 */
	virtual void RefreshItemList(TOptional<FString> PageCursor) override;
	
	virtual void Refresh() override;	
	
	// Get the currently selected item widget
	UItemWidget* GetSelectedItem() const { return SelectedItemWidget; }

	// Widget Item sort helpers
	UFUNCTION(BlueprintImplementableEvent, BlueprintPure)
	ESearchStacks_SortCategories GetSortCategory();
	UFUNCTION(BlueprintImplementableEvent, BlueprintPure)
	bool GetSortOrder();

protected:
	/* UActivatableWidget interface */
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	virtual void OnWidgetRebuilt() override;
	/* UActivatableWidget interface */

	/**
	 * Handles the response from the Search Stacks API.
	 *
	 * @param Response The response object from the Search Stacks API.
	 */
	void OnSearchStacksResponse(const ImmutablezkEVMAPI::APIStacksApi::SearchStacksResponse& Response);

	/* UActivatableWidgetWithControlPanels interface */
	virtual void SetupControlButtons(class UAWStackWithControlPanels* HostLayer) override;
	/* UActivatableWidgetWithControlPanels interface */

private:
	// Pagination handler
	void HandlePageData(const ImmutablezkEVMAPI::APIPage& PageData);
	// Sorting handler
	void HandleSorting(TOptional<ImmutablezkEVMAPI::APIStacksApi::SearchStacksRequest::SortByEnum>& Sorting);
	// Item selection handler
	void ItemSelectionChange(bool IsSelected, UItemWidget* ItemWidget);
	// Control panel button handler such Buy, Sell, etc.
	void OnControlButtonClicked(FGameplayTag ButtonTag);
	// Item selection handler
	void OnItemSelectionChange(bool IsSelected, UItemWidget* ItemWidget);
	// Item double click handler
	void OnItemDoubleClick(UItemWidget* InItemWidget);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UItemListWidget* ListPanel = nullptr;
	UPROPERTY(EditAnywhere, Category = "Marketplace")
	TSoftClassPtr<class USearchStacksListingWidget> SearchStacksListingWidgetClass;

private:
	ImmutablezkEVMAPI::APIPage PageCursors;
	UItemWidget* SelectedItemWidget = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* PreviousPageButton = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* NextPageButton = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* NFTInfoButton = nullptr;
	
};
