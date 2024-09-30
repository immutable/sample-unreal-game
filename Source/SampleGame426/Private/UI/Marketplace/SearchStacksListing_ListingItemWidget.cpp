#include "Marketplace/SearchStacksListing_ListingItemWidget.h"


void USearchStacksListing_ListingItemWidget::RegisterOnSelection(FOnListingItemSelection OnListingItemSelection)
{
	this->OnListingItemSelection = OnListingItemSelection; 
}

void USearchStacksListing_ListingItemWidget::SetListingId(const FString& ListingId)
{
	this->ListingId = ListingId;
}

const FString& USearchStacksListing_ListingItemWidget::GetListingId() const
{
	return ListingId;
}

void USearchStacksListing_ListingItemWidget::Select()
{
	IsSelected = true;
	OnListingItemSelection.ExecuteIfBound(IsSelected, this);
}

void USearchStacksListing_ListingItemWidget::Deselect()
{
	IsSelected = false;
	OnListingItemSelection.ExecuteIfBound(IsSelected, this);
}
