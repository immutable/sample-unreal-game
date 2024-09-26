#pragma once

#include "OpenAPISearchApi.h"
#include "Data/NFTMetadataAttributeDataAsset.h"

#include "MarketplacePolicy.generated.h"


namespace ImmutableQuery
{
	struct FMP_SearchStacksRequestTraitData;
	struct FMP_SearchStacksRequestData;
}

/*
 * 
 */
UCLASS(Abstract)
class UMarketplacePolicy : public UObject
{
	GENERATED_BODY()

public:
	UMarketplacePolicy();
	/* UObject Interface */
	virtual void PostInitProperties() override;
	/* UObject Interface */

	ImmutableOpenAPI::OpenAPISearchApi* GetOpenAPISearchApi();
	TSharedPtr<ImmutableOpenAPI::OpenAPISearchApi::SearchStacksRequest> GetSearchStacksRequest();

	void SetPageSize(int32 PageSize);
	void SetPageCursor(TOptional<FString> PageCursor);
	void SetAccount(const FString& Account);
	void SetKeyword(const FString& Keyword);
	void SetTraits(const TArray<FNFTMetadataAttribute_TraitType>& Traits);
	void SetOnlyIncludeOwnerListings(bool OnlyIncludeOwnerListings);
	
protected:
	// Online values:
	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Online")
	FString URL;

	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Online")
	FString SearchStacksChainName;

	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Online")
	uint32 RetryLimitCount = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Online")
	double RetryTimeoutRelativeSeconds = 1.0;
	
	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Search NFT stacks")
	TArray<FString> ContractAddress;

	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Search NFT stacks")
	int32 NumberFractionalDigits = 4;

private:
	TSharedPtr<ImmutableOpenAPI::OpenAPISearchApi::SearchStacksRequest> SearchStacksRequestData;
	TUniquePtr<ImmutableOpenAPI::OpenAPISearchApi> SearchAPI;
	TUniquePtr<ImmutableOpenAPI::HttpRetryManager> HttpRetryManager;
	
};
