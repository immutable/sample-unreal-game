#include "UI/Marketplace/MarketplacePolicy.h"

#include "CustomLocalPlayer.h"
#include "OpenAPIHelpers.h"
#include "OpenAPISearchApiOperations.h"
#include "OpenAPIStacksApiOperations.h"
#include "Dialog/DialogSubsystem.h"
#include "Engine/DataTable.h"


void UMarketplacePolicy::PostInitProperties()
{
	UObject::PostInitProperties();

	SearchAPI = MakeUnique<ImmutableOpenAPI::OpenAPISearchApi>();
	SearchAPI_SearchStacksRequest = MakeShared<ImmutableOpenAPI::OpenAPISearchApi::SearchStacksRequest>();
	SearchAPI_HttpRetryManager = MakeUnique<ImmutableOpenAPI::HttpRetryManager>(RetryLimitCount, RetryTimeoutRelativeSeconds);
	
	SearchAPI->SetURL(MarketplaceAPIURL);
	SearchAPI->AddHeaderParam(TEXT("Accept"), TEXT("application/json"));
	SearchAPI->SetHttpRetryManager(*SearchAPI_HttpRetryManager);
	SearchAPI_SearchStacksRequest->ChainName = SearchAPIChainName;

	IndexerStacksAPI = MakeUnique<ImmutableIndexerSearchAPI::OpenAPIStacksApi>();
	IndexerStacksAPI_SearchNfTsRequest = MakeShared<ImmutableIndexerSearchAPI::OpenAPIStacksApi::SearchNFTsRequest>();
	IndexerStacksAPI_HttpRetryManager = MakeUnique<ImmutableIndexerSearchAPI::HttpRetryManager>(RetryLimitCount, RetryTimeoutRelativeSeconds);

	IndexerStacksAPI->SetURL(MarketplaceAPIURL);
	IndexerStacksAPI->AddHeaderParam(TEXT("Accept"), TEXT("application/json"));
	IndexerStacksAPI->SetHttpRetryManager(*IndexerStacksAPI_HttpRetryManager);
	IndexerStacksAPI_SearchNfTsRequest->ChainName = IndexerStacksAPIChainName;

	TsSdkAPI = MakeUnique<ImmutableTsSdkApi::ImmutableTsSdkApi_DefaultApi>();
	TsSdkAPI->SetURL(TsSdkAPIURL);
}

UDataTable* UMarketplacePolicy::GetNFTDatatable()
{
	return NFT_Datatable;
}

ImmutableOpenAPI::OpenAPISearchApi* UMarketplacePolicy::GetSearchAPI()
{
	return SearchAPI.Get();
}

TSharedPtr<ImmutableOpenAPI::OpenAPISearchApi::SearchStacksRequest> UMarketplacePolicy::GetSearchAPI_SearchStacksRequest()
{
	SearchAPI_SearchStacksRequest->ContractAddress = StackContractAddress;
	
	return SearchAPI_SearchStacksRequest;
}

ImmutableIndexerSearchAPI::OpenAPIStacksApi* UMarketplacePolicy::GetIndexerStacksAPI()
{
	return IndexerStacksAPI.Get();
}

TSharedPtr<ImmutableIndexerSearchAPI::OpenAPIStacksApi::SearchNFTsRequest> UMarketplacePolicy::GetIndexerStacksAPI_SearchNfTsRequest()
{
	IndexerStacksAPI_SearchNfTsRequest->OnlyIncludeOwnerListings = true;
	return IndexerStacksAPI_SearchNfTsRequest;
}

ImmutableTsSdkApi::ImmutableTsSdkApi_DefaultApi* UMarketplacePolicy::GetTsSdkAPI()
{
	return TsSdkAPI.Get();
}

FString UMarketplacePolicy::GetBalanceContractAddress() const
{
	return BalanceContractAddress;
}

void UMarketplacePolicy::SetPageSize(int32 PageSize)
{
	SearchAPI_SearchStacksRequest->PageSize = PageSize;
	IndexerStacksAPI_SearchNfTsRequest->PageSize = PageSize;
}

void UMarketplacePolicy::SetPageCursor(TOptional<FString> PageCursor)
{
	SearchAPI_SearchStacksRequest->PageCursor = PageCursor;
}

void UMarketplacePolicy::SetAccount(const FString& Account)
{
	if (Account.IsEmpty())
	{
		//SearchAPI_SearchStacksRequest->AccountAddress.Reset();
        IndexerStacksAPI_SearchNfTsRequest->AccountAddress.Reset();
	}
	else
	{
		//SearchAPI_SearchStacksRequest->AccountAddress = Account;
		IndexerStacksAPI_SearchNfTsRequest->AccountAddress = Account;
	}
}

void UMarketplacePolicy::SetKeyword(const FString& Keyword)
{
	if (!Keyword.TrimStartAndEnd().IsEmpty())
	{
		SearchAPI_SearchStacksRequest->Keyword = Keyword;	
	}
	else
	{
		SearchAPI_SearchStacksRequest->Keyword.Reset();
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

		SearchAPI_SearchStacksRequest->Trait = ImmutableOpenAPI::ToUrlString("{" + TraitsJson + "}");
	}
	else
	{
		SearchAPI_SearchStacksRequest->Trait.Reset();
	}
}

void UMarketplacePolicy::SetOnlyIncludeOwnerListings(bool OnlyIncludeOwnerListings)
{
	SearchAPI_SearchStacksRequest->OnlyIncludeOwnerListings = OnlyIncludeOwnerListings;
}

FNFT_TableRowBase* UMarketplacePolicy::FindNFTTextureRow(FName RowName)
{
	if (NFT_Datatable)
	{
		FString ContextString;

		return NFT_Datatable->FindRow<FNFT_TableRowBase>(RowName, ContextString, true);
	}
	
	return nullptr;
}