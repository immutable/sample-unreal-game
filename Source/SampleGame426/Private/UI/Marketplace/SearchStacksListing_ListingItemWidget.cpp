#include "Marketplace/SearchStacksListing_ListingItemWidget.h"

#include "Components/Button.h"


void USearchStacksListing_ListingItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (SelectButton)
	{
		SelectButton->OnClicked.AddUniqueDynamic(this, &USearchStacksListing_ListingItemWidget::OnSelectButtonClicked);
	}
}

void USearchStacksListing_ListingItemWidget::RegisterOnSelection(const FOnListingItemSelection& SelectionDelegate)
{
	OnListingItemSelection = SelectionDelegate; 
}

void USearchStacksListing_ListingItemWidget::SetListingId(const FString& Id)
{
	this->ListingId = Id;
}

const FString& USearchStacksListing_ListingItemWidget::GetListingId() const
{
	return ListingId;
}

void USearchStacksListing_ListingItemWidget::SetSelectionStatus(bool IsSelected)
{
	if (IsListingItemSelected == IsSelected)
	{
		return;	
	}
	
	IsListingItemSelected = IsSelected;
	OnListingItemSelection.ExecuteIfBound(IsListingItemSelected, this);
	BP_OnSelectStatusUpdate(IsSelected);
}

bool USearchStacksListing_ListingItemWidget::GetSelectionStatus() const
{
	return IsListingItemSelected;
}

void USearchStacksListing_ListingItemWidget::OnSelectButtonClicked()
{
	SetSelectionStatus(!IsListingItemSelected);
}
