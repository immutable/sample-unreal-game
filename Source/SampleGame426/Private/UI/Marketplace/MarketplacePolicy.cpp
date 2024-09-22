#include "UI/Marketplace/MarketplacePolicy.h"

#include "Online/ImmutableQuery.h"


void UMarketplacePolicy::PostInitProperties()
{
	UObject::PostInitProperties();

	SearchData = MakeShareable(new ImmutableQuery::FMP_SearchStacksRequestData());
}

void UMarketplacePolicy::SetPageSize(int32 PageSize)
{
	SearchData->PageSize = PageSize;
}

void UMarketplacePolicy::SetPageCursor(const FString& PageCursor)
{
	SearchData->PageCursor = PageCursor;
}

void UMarketplacePolicy::SetAccount(const FString& Account)
{
	SearchData->AccountAddress = Account;
}

void UMarketplacePolicy::SetKeyword(const FString& Keyword)
{
	SearchData->Keyword = Keyword;
}

void UMarketplacePolicy::SetTraits(const TArray<ImmutableQuery::FMP_SearchStacksRequestTraitData>& Traits)
{
	SearchData->Trait = Traits;
}

void UMarketplacePolicy::SetOnlyIncludeOwnerListings(bool OnlyIncludeOwnerListings)
{
	SearchData->OnlyIncludeOwnerListings = OnlyIncludeOwnerListings;
}

TSharedPtr<ImmutableQuery::FMP_SearchStacksRequestData> UMarketplacePolicy::GetSearchData() const
{
	SearchData->ContactAddress = ContractAddress;

	return SearchData;
}
