#pragma once

#include "MarketplaceItemWIdget.h"
#include "MarketplaceListingsItemWidget.h"
#include "Blueprint/UserWidget.h"

#include "MarketplaceListingsWidget.generated.h"


namespace OpenAPI
{
	class OpenAPIListing;
}

UCLASS()
class UMarketplaceListingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void AddItem(const OpenAPI::OpenAPIListing& Listing);

protected:
	UPROPERTY(EditAnywhere, Category = "Marketplace")
	TSoftClassPtr<UMarketplaceListingsItemWidget> ItemWidgetClass;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UScrollBox* ScrollBoxListings = nullptr;
};
