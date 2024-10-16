#include "UI/Marketplace/MarketplacePolicy.h"

#include "CustomLocalPlayer.h"
#include "OpenAPIHelpers.h"
#include "OpenAPIStacksApiOperations.h"
#include "Dialog/DialogSubsystem.h"
#include "Engine/DataTable.h"


void UMarketplacePolicy::PostInitProperties()
{
	UObject::PostInitProperties();

	HttpRetryManager = MakeUnique<ImmutableOpenAPI::HttpRetryManager>(RetryLimitCount, RetryTimeoutRelativeSeconds);

	StacksAPI = MakeUnique<ImmutableOpenAPI::OpenAPIStacksApi>();
	StacksAPI->SetURL(ImmutableAPIURL);
	StacksAPI->AddHeaderParam(TEXT("Accept"), TEXT("application/json"));
	StacksAPI->SetHttpRetryManager(*HttpRetryManager);

	OrdersAPI = MakeUnique<ImmutableOpenAPI::OpenAPIOrdersApi>();
	OrdersAPI->SetURL(ImmutableAPIURL);
	OrdersAPI->AddHeaderParam(TEXT("Accept"), TEXT("application/json"));
	OrdersAPI->SetHttpRetryManager(*HttpRetryManager);
	
	TsSdkAPI = MakeUnique<ImmutableTsSdkApi::OpenAPIOrderbookApi>();
	TsSdkAPI->SetURL(TsSdkAPIURL);
}

UDataTable* UMarketplacePolicy::GetNFTDatatable()
{
	return NFT_Datatable;
}

ImmutableTsSdkApi::OpenAPIOrderbookApi* UMarketplacePolicy::GetTsSdkAPI()
{
	return TsSdkAPI.Get();
}

FString UMarketplacePolicy::GetBalanceContractAddress() const
{
	return BalanceContractAddress;
}

void UMarketplacePolicy::SetKeyword(const FString& Keyword)
{
	if (!Keyword.TrimStartAndEnd().IsEmpty())
	{
		SearchStacksKeyword = Keyword;
	}
	else
	{
		SearchStacksKeyword.Reset();
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

		SearchStacksTraits = "{" + TraitsJson + "}";
	}
	else
	{
		SearchStacksTraits.Reset();
	}
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