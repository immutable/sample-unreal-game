#pragma once

#include "Data/NFTMetadataAttributeDataAsset.h"

#include "MarketplacePolicy.generated.h"


namespace ImmutableQuery
{
	struct FMP_SearchStacksRequestTraitData;
	struct FMP_SearchStacksRequestData;
}

UCLASS(Abstract)
class UMarketplacePolicy : public UObject
{
	GENERATED_BODY()

public:
	/* UObject Interface */
	virtual void PostInitProperties() override;
	/* UObject Interface */

	void SetPageSize(int32 PageSize);
	void SetPageCursor(const FString& PageCursor);
	void SetAccount(const FString& Account);
	void SetKeyword(const FString& Keyword);
	void SetTraits(const TArray<ImmutableQuery::FMP_SearchStacksRequestTraitData>& Traits);
	void SetOnlyIncludeOwnerListings(bool OnlyIncludeOwnerListings);
	
	TSharedPtr<ImmutableQuery::FMP_SearchStacksRequestData> GetSearchData() const;
	
protected:
	// Online values:
	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Search NFT stacks")
	TArray<FString> ContractAddress;

	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Search NFT stacks")
	TSoftObjectPtr<UNFTMetadataAttributeDataAsset> SearchMetaAttributes;

	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Search NFT stacks")
	int32 NumberFractionalDigits = 4;

private:
	TSharedPtr<ImmutableQuery::FMP_SearchStacksRequestData> SearchData;
	
};
