#pragma once

#include "Blueprint/UserWidget.h"

#include "SearchStacksListing_ListingItemWidget.generated.h"


UCLASS(Abstract, Blueprintable)
class SAMPLEGAME426_API USearchStacksListing_ListingItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	
	DECLARE_DELEGATE_TwoParams(FOnListingItemSelection, bool /* IsSelected */, USearchStacksListing_ListingItemWidget* /* ListingItemWidget */)
	
	void RegisterOnSelection(const FOnListingItemSelection& SelectionDelegate);
	
	void SetListingId(const FString& Id);
    const FString& GetListingId() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void SetData(const FString& TokenID, const FString& Amount, const FString& FeeProtocol, const FString& FeeRoyalty, const FString& Price, const FString& Currency, bool IsToBuy = true);

	void SetSelectionStatus(bool IsSelected);
	bool GetSelectionStatus() const;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void BP_OnSelectStatusUpdate(bool IsSelected);

private:
	UFUNCTION()
	void OnSelectButtonClicked();

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UButton* SelectButton = nullptr;

private:
	FString ListingId;
	FOnListingItemSelection OnListingItemSelection;
	bool IsListingItemSelected = false;
};
