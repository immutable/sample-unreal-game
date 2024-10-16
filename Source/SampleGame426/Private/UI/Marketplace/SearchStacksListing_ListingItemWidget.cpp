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

void USearchStacksListing_ListingItemWidget::OnSelectButtonClicked()
{
	IsListingItemSelected = !IsListingItemSelected;
	OnListingItemSelection.ExecuteIfBound(IsListingItemSelected, this);
	BP_OnSelectButtonClick(IsListingItemSelected);
}
