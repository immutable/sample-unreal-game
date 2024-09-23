#include "UI/Marketplace/MarketplacePolicy.h"

#include "OpenAPIHelpers.h"
#include "OpenAPISearchApiOperations.h"


UMarketplacePolicy::UMarketplacePolicy()
{
}

void UMarketplacePolicy::PostInitProperties()
{
	UObject::PostInitProperties();

	SearchAPI = MakeUnique<ImmutableOpenAPI::OpenAPISearchApi>();
	SearchStacksRequestData = MakeShared<ImmutableOpenAPI::OpenAPISearchApi::SearchStacksRequest>();
	HttpRetryManager = MakeUnique<ImmutableOpenAPI::HttpRetryManager>(RetryLimitCount, RetryTimeoutRelativeSeconds);
	
	SearchAPI->SetURL(URL);
	SearchAPI->SetHttpRetryManager(*HttpRetryManager);
	SearchStacksRequestData->ChainName = SearchStacksChainName;
}

ImmutableOpenAPI::OpenAPISearchApi* UMarketplacePolicy::GetOpenAPISearchApi()
{
	return SearchAPI.Get();
}

TSharedPtr<ImmutableOpenAPI::OpenAPISearchApi::SearchStacksRequest> UMarketplacePolicy::GetSearchStacksRequest()
{
	SearchStacksRequestData->ContractAddress = ContractAddress;
	
	return SearchStacksRequestData;
}

void UMarketplacePolicy::SetPageSize(int32 PageSize)
{
	SearchStacksRequestData->PageSize = PageSize;
}

void UMarketplacePolicy::SetPageCursor(const FString& PageCursor)
{
	SearchStacksRequestData->PageCursor = PageCursor;
}

void UMarketplacePolicy::SetAccount(const FString& Account)
{
	if (Account.IsEmpty())
	{
		SearchStacksRequestData->AccountAddress = Account;	
	}
	else
	{
		SearchStacksRequestData->AccountAddress.Reset();
	}
	
}

void UMarketplacePolicy::SetKeyword(const FString& Keyword)
{
	if (!Keyword.TrimStartAndEnd().IsEmpty())
	{
		SearchStacksRequestData->Keyword = Keyword;	
	}
	else
	{
		SearchStacksRequestData->Keyword.Reset();
	}
	
}

void UMarketplacePolicy::SetTraits(const TArray<FNFTMetadataAttribute_TraitType>& Traits)
{
	if (Traits.Num())
	{
		FString TraitsJson;

		for (auto Trait : Traits)
		{
			FString ValuesJson;

			for (auto Value : Trait.Values)
			{
				if (!ValuesJson.IsEmpty())
				{
					ValuesJson.AppendChar(TEXT(','));
				}
				ValuesJson += "\"" + Value + "\"";
			}
			if (!TraitsJson.IsEmpty())
			{
				TraitsJson.AppendChar(TEXT(','));
			}
			TraitsJson += "\"" + Trait.Name + "\": {\"values\": [" + ValuesJson + "], \"condition\": \"eq\"}";
		}

		SearchStacksRequestData->Trait = ImmutableOpenAPI::ToUrlString("{" + TraitsJson + "}");
	}
	else
	{
		SearchStacksRequestData->Trait.Reset();
	}
}

void UMarketplacePolicy::SetOnlyIncludeOwnerListings(bool OnlyIncludeOwnerListings)
{
	SearchStacksRequestData->OnlyIncludeOwnerListings = OnlyIncludeOwnerListings;
}
