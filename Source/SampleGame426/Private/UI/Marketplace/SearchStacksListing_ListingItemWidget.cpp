#include "Marketplace/SearchStacksListing_ListingItemWidget.h"


void USearchStacksListing_ListingItemWidget::RegisterOnSelection(const FOnListingItemSelection& SelectionDelegate)
{
	this->OnListingItemSelection = SelectionDelegate; 
}

void USearchStacksListing_ListingItemWidget::SetListingId(const FString& Id)
{
	this->ListingId = Id;
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
