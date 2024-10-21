#pragma once

#include "CustomUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "SearchStacksListing_ListingItemWidget.h"

#include "SearchStacksListing_ListingsWidget.generated.h"


namespace ImmutableOpenAPI
{
	class OpenAPIListing;
}

UCLASS()
class USearchStacksListing_ListingsWidget : public UCustomUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE_OneParam(FOnSelectionStatusChange, bool /* IsSelected */)
	
	void AddItem(const ImmutableOpenAPI::OpenAPIListing& Listing, bool IsIdEven, const UItemWidget::FOnSelectionChange& InOnSelectionChangeDelegate);
	void Reset();

protected:
	UPROPERTY(EditAnywhere, Category = "Marketplace")
	TSoftClassPtr<USearchStacksListing_ListingItemWidget> ItemWidgetClass;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UScrollBox* ScrollBoxListings = nullptr;
	
};
