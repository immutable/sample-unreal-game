#pragma once

#include "Blueprint/UserWidget.h"
#include "SearchStacksListing_ListingItemWidget.h"

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
	DECLARE_DELEGATE_OneParam(FOnSelectionStatusChange, bool /* IsSelected */)
	
	void AddItem(const ImmutableOpenAPI::OpenAPIListing& Listing);
	USearchStacksListing_ListingItemWidget* GetSelectedItemWidget();
	void RegisterOnSelectionStatusChange(FOnSelectionStatusChange InDelegate);

protected:
	void OnItemSelection(bool IsSelected, USearchStacksListing_ListingItemWidget* ListingItemWidget);
	
protected:
	FOnSelectionStatusChange OnSelectionStatusChangeDelegate;
	UPROPERTY(EditAnywhere, Category = "Marketplace")
	TSoftClassPtr<USearchStacksListing_ListingItemWidget> ItemWidgetClass;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UScrollBox* ScrollBoxListings = nullptr;

private:
	USearchStacksListing_ListingItemWidget* SelectedItemWidget = nullptr;
};
