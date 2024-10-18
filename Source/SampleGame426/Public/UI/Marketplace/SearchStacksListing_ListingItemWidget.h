#pragma once

#include "Base/ItemWidget.h"

#include "SearchStacksListing_ListingItemWidget.generated.h"


UCLASS(Abstract, Blueprintable)
class SAMPLEGAME426_API USearchStacksListing_ListingItemWidget : public UItemWidget
{
	GENERATED_BODY()

public:
	/* UItemWidget interface */
	virtual void SetSelection(bool IsSelected) override;
	/* UItemWidget interface */
	
	void SetListingId(const FString& Id);
    const FString& GetListingId() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void SetData(const FString& TokenID, const FString& Amount, const FString& FeeProtocol, const FString& FeeRoyalty, const FString& Price, const FString& Currency, bool IsIdEven);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void SetIsOwned(bool IsOwned);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void BP_OnSetIsOwned(bool IsOwned);
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	bool IsOwned();

private:
	FString ListingId;
	bool bIsOwned = false;
};
