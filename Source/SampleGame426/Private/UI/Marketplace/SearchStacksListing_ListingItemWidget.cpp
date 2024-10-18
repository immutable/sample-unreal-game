#include "Marketplace/SearchStacksListing_ListingItemWidget.h"

#include "Components/Button.h"


void USearchStacksListing_ListingItemWidget::SetSelection(bool IsSelected)
{
	if (!bIsOwned)
	{
		Super::SetSelection(IsSelected);
	}
}

void USearchStacksListing_ListingItemWidget::SetListingId(const FString& Id)
{
	this->ListingId = Id;
}

const FString& USearchStacksListing_ListingItemWidget::GetListingId() const
{
	return ListingId;
}

void USearchStacksListing_ListingItemWidget::SetIsOwned(bool IsOwned)
{
	bIsOwned = IsOwned;
	BP_OnSetIsOwned(IsOwned);
}

bool USearchStacksListing_ListingItemWidget::IsOwned()
{
	return bIsOwned;
}
