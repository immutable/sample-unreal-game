#include "UI/Marketplace/MarketplacePolicy.h"

#include "CustomLocalPlayer.h"
#include "OpenAPIHelpers.h"
#include "OpenAPIStacksApiOperations.h"
#include "Dialog/DialogSubsystem.h"
#include "Engine/DataTable.h"


void UMarketplacePolicy::PostInitProperties()
{
	UObject::PostInitProperties();

	ImmutableOpenAPI = MakeUnique<ImmutableOpenAPI::OpenAPIStacksApi>();
	ImmutableOpenAPI_HttpRetryManager = MakeUnique<ImmutableOpenAPI::HttpRetryManager>(RetryLimitCount, RetryTimeoutRelativeSeconds);
	ImmutableOpenAPI->SetURL(MarketplaceAPIURL);
	ImmutableOpenAPI->AddHeaderParam(TEXT("Accept"), TEXT("application/json"));
	ImmutableOpenAPI->SetHttpRetryManager(*ImmutableOpenAPI_HttpRetryManager);
	
	TsSdkAPI = MakeUnique<ImmutableTsSdkApi::ImmutableTsSdkApi_DefaultApi>();
	TsSdkAPI->SetURL(TsSdkAPIURL);
	
	ImmutableOpenAPI_SearchStacksRequest = MakeShared<ImmutableOpenAPI::OpenAPIStacksApi::SearchStacksRequest>();
	ImmutableOpenAPI_SearchStacksRequest->ChainName = SearchAPIChainName;
	ImmutableOpenAPI_SearchNFTsRequest = MakeShared<ImmutableOpenAPI::OpenAPIStacksApi::SearchNFTsRequest>();
	ImmutableOpenAPI_SearchNFTsRequest->ChainName = SearchAPIChainName;
}

UDataTable* UMarketplacePolicy::GetNFTDatatable()
{
	return NFT_Datatable;
}

ImmutableOpenAPI::OpenAPIStacksApi* UMarketplacePolicy::GetImmutableOpenAPI()
{
	return ImmutableOpenAPI.Get();
}

TSharedPtr<ImmutableOpenAPI::OpenAPIStacksApi::SearchStacksRequest> UMarketplacePolicy::GetImmutableOpenAPI_SearchStacksRequest()
{
	ImmutableOpenAPI_SearchStacksRequest->ContractAddress = StackContractAddress;
	
	return ImmutableOpenAPI_SearchStacksRequest;
}

TSharedPtr<ImmutableOpenAPI::OpenAPIStacksApi::SearchNFTsRequest> UMarketplacePolicy::GetImmutableOpenAPI_SearchNfTsRequest()
{
	ImmutableOpenAPI_SearchNFTsRequest->ContractAddress = StackContractAddress;
	
	return ImmutableOpenAPI_SearchNFTsRequest;
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
	ImmutableOpenAPI_SearchStacksRequest->PageSize = PageSize;
	ImmutableOpenAPI_SearchNFTsRequest->PageSize = PageSize;
}

void UMarketplacePolicy::SetPageCursor(TOptional<FString> PageCursor)
{
	ImmutableOpenAPI_SearchStacksRequest->PageCursor = PageCursor;
	ImmutableOpenAPI_SearchNFTsRequest->PageCursor = PageCursor;
}

void UMarketplacePolicy::SetAccount(const FString& Account)
{
	if (Account.IsEmpty())
	{
        ImmutableOpenAPI_SearchStacksRequest->AccountAddress.Reset();
		ImmutableOpenAPI_SearchNFTsRequest->AccountAddress.Reset();
	}
	else
	{
		ImmutableOpenAPI_SearchStacksRequest->AccountAddress = Account;
		ImmutableOpenAPI_SearchNFTsRequest->AccountAddress = Account;
	}
}

void UMarketplacePolicy::SetKeyword(const FString& Keyword)
{
	if (!Keyword.TrimStartAndEnd().IsEmpty())
	{
		ImmutableOpenAPI_SearchStacksRequest->Keyword = Keyword;
	}
	else
	{
		ImmutableOpenAPI_SearchStacksRequest->Keyword.Reset();
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

		ImmutableOpenAPI_SearchStacksRequest->Trait = ImmutableOpenAPI::ToUrlString("{" + TraitsJson + "}");
	}
	else
	{
		ImmutableOpenAPI_SearchStacksRequest->Trait.Reset();
	}
}

void UMarketplacePolicy::SetOnlyIncludeOwnerListings(bool OnlyIncludeOwnerListings)
{
	ImmutableOpenAPI_SearchStacksRequest->OnlyIncludeOwnerListings = OnlyIncludeOwnerListings;
	ImmutableOpenAPI_SearchNFTsRequest->OnlyIncludeOwnerListings = OnlyIncludeOwnerListings;
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