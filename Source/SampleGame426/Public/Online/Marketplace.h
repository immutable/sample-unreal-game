#pragma once
#include "Interfaces/IHttpRequest.h"


DECLARE_DELEGATE_OneParam(FOnHttpRequestComplete, bool /*bWasSuccessful*/);

struct MarketplaceRequestTraitData
{
	FString TraitType;
	FString Value;
};

struct FMarketplaceRequestData
{
	TArray<FString> ContactAddress; // required
	FString AccountAddress;
	FString Keyword;
	bool OnlyIncludeOwnerListings;
	FString PageCursor;
	int32 PageSize;
	TArray<MarketplaceRequestTraitData> Trait;
};

struct FMarketplaceRequestQueryParameters
{
	static const FString ContactAddress; // required
	static const FString AccountAddress;
	static const FString Keyword;
	static const FString OnlyIncludeOwnerListings;
	static const FString PageCursor;
	static const FString PageSize;
	static const FString Trait;
};

class FMarketplace
{
public:
	static void QueryStacks(const FMarketplaceRequestData& RequestData, FOnHttpRequestComplete OnHttpRequestComplete);

private:
	static FString BuildGETContentString(const FMarketplaceRequestData& RequestData);
	
	static FString GetMarketplaceUrl();
	static void OnQueryStacksComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool IsSuccessful, FOnHttpRequestComplete OnHttpRequestComplete);
};
