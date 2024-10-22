#pragma once

#include "CustomUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "SearchStacksListing_ListingItemWidget.h"

#include "SearchStacksListing_ListingsWidget.generated.h"


namespace ImmutableOpenAPI
{
	class OpenAPIListing;
}

/**
 * @class USearchStacksListing_ListingsWidget 
 * @ingroup Marketplace
 * @brief A widget class for displaying scrollable list of search stack marketed NFTs by user.
 */
UCLASS()
class USearchStacksListing_ListingsWidget : public UCustomUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE_OneParam(FOnSelectionStatusChange, bool /* IsSelected */)
	
	/**
	 * Adds an item to a scrollable list widget.
	 *
	 * @param Listing The Orderbook API listing to be added.
	 * @param IsIdEven A boolean indicating if the ID of the listing is even or odd, used for record color highlight/separation.
	 * @param InOnSelectionChangeDelegate The delegate to be called when the selection changes.
	 */
	void AddItem(const ImmutableOpenAPI::OpenAPIListing& Listing, bool IsIdEven, const UItemWidget::FOnSelectionChange& InOnSelectionChangeDelegate);
	/**
	 * Resets the state of this widget.
	 */
	void Reset();

protected:
	UPROPERTY(EditAnywhere, Category = "Marketplace")
	TSoftClassPtr<USearchStacksListing_ListingItemWidget> ItemWidgetClass;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UScrollBox* ScrollBoxListings = nullptr;
	
};
