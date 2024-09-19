#include "Marketplace/MarketplaceItemFullWidget.h"

#include "OpenAPIListing.h"
#include "OpenAPIStackBundle.h"
#include "Marketplace/MarketplaceListingsWidget.h"

void UMarketplaceItemFullWidget::ProcessModel(const OpenAPI::Model* Data)
{
	auto StackBundle = static_cast<const OpenAPI::OpenAPIStackBundle*>(Data);

	if (!StackBundle)
	{
		return;
	}

	for (const auto& Listing : StackBundle->Listings)
	{
		Listings->AddItem(Listing);
	}
}
