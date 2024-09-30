#pragma once

#include "SearchStacksListing_ListingItemWidget.h"
#include "Blueprint/UserWidget.h"

#include "SearchStacksListing_ListingsWidget.generated.h"


namespace ImmutableOpenAPI
{
	class OpenAPIListing;
}

UCLASS()
class USearchStacksListing_ListingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void AddItem(const ImmutableOpenAPI::OpenAPIListing& Listing);
	void Buy();

protected:
	void OnItemSelection(bool IsSelected, USearchStacksListing_ListingItemWidget* ListingItemWidget);
	
private:
	void OnGetUnsignedFulfillOrderTransaction(const class GetUnsignedFulfillOrderTransactionsResponse& Response);

protected:
	UPROPERTY(EditAnywhere, Category = "Marketplace")
	TSoftClassPtr<USearchStacksListing_ListingItemWidget> ItemWidgetClass;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UScrollBox* ScrollBoxListings = nullptr;

private:
	USearchStacksListing_ListingItemWidget* SelectedItemWidget = nullptr;
};
