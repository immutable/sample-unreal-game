#include "ImmutableQuery.h"

#include "HttpModule.h"
#include "LogSampleGame.h"
#include "OpenAPISearchStacksResult.h"
#include "Interfaces/IHttpResponse.h"


#define CHANI_NAME			TEXT("imtbl-zkevm-devnet")
#define SEARCH_BASE_URL		TEXT("https://api.dev.immutable.com/experimental/chains/{0}/search/stacks")

// GET https://api.immutable.com/experimental/chains/{{chain_name}}/search/stacks?
// 	contract_address={{$placeholder}}&
// 	account_address={{$placeholder}}&
// 	only_include_owner_listings={{$placeholder}}&
// 	trait={{$placeholder}}&
// 	keyword={{$placeholder}}&
// 	page_size={{$placeholder}}&
// 	page_cursor={{$placeholder}}

namespace ImmutableQuery
{
	FString GetMarketplaceUrl()
	{
		const FString MARKETPLACE_URL = FString::Format(SEARCH_BASE_URL, { CHANI_NAME });

		return MARKETPLACE_URL;
	}

	FString BuildGETContentString(TSharedPtr<ImmutableQuery::FMP_SearchStacksRequestData> RequestData)
	{
		const FString ContactAddress = TEXT("contract_address");
		const FString AccountAddress = TEXT("account_address");
		const FString Keyword = TEXT("keyword");
		const FString PageCursor = TEXT("page_cursor");
		const FString PageSize = TEXT("page_size");
		const FString Trait = TEXT("trait");
		const FString OnlyIncludeOwnerListings = TEXT("only_include_owner_listings");
	
		FString Content;

		for (auto Address : RequestData->ContactAddress)
		{
			Content += TEXT("&") + ContactAddress + TEXT("=") + Address;	
		}

		if (!RequestData->AccountAddress.IsEmpty())
		{
			Content += TEXT("&") + AccountAddress + TEXT("=") + RequestData->AccountAddress;	
		}

		if (!RequestData->Keyword.IsEmpty())
		{
			Content += TEXT("&") + Keyword + TEXT("=") + RequestData->Keyword;	
		}

		if (!RequestData->PageCursor.IsEmpty())
		{
			Content += TEXT("&") + PageCursor + TEXT("=") + RequestData->PageCursor;
		}

		if (RequestData->PageSize > 0)
		{
			Content += TEXT("&") + PageSize + TEXT("=") + FString::FromInt(RequestData->PageSize);
		}

		Content += TEXT("&") + OnlyIncludeOwnerListings + TEXT("=") + (RequestData->OnlyIncludeOwnerListings ? TEXT("true") : TEXT("false"));
	
		Content.RemoveAt(0);
	
		return Content;
	}

	// template<> void ExecuteQuery(TSharedPtr<FMP_SearchStacksRequestData> Data, const FOnImmutableQueryComplete& OnMarketplaceQueryComplete)
	// {
	// 	const FString URL = GetMarketplaceUrl() + "?" + BuildGETContentString(Data);
	// 	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	//
	// 	UE_LOG(LogSampleGame, Log, TEXT("GET Marketplace stacks from URL: %s"), *URL)
	//
	// 	HttpRequest->SetURL(URL);
	// 	HttpRequest->SetVerb(TEXT("GET"));
	// 	HttpRequest->SetHeader(TEXT("Accept"), TEXT("application/json"));
	// 	HttpRequest->OnProcessRequestComplete().BindLambda([OnMarketplaceQueryComplete](FHttpRequestPtr Request, FHttpResponsePtr Response, bool IsSuccessful)
	// 	{
	// 		if (IsSuccessful)
	// 		{
	// 			TSharedPtr<FJsonValue> JsonValue;
	// 			const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	// 		
	// 			if (!FJsonSerializer::Deserialize(JsonReader, JsonValue))
	// 			{
	// 				UE_LOG(LogSampleGame, Log, TEXT("Marketplace - Search NFT stacks: Failed to deserialize json value"));
	// 			}
	// 		
	// 			TSharedPtr<OpenAPI::OpenAPISearchStacksResult> SearchStacksResult = MakeShareable(new OpenAPI::OpenAPISearchStacksResult());
	// 		
	// 			if (SearchStacksResult->FromJson(JsonValue))
	// 			{
	// 				UE_LOG(LogSampleGame, Log, TEXT("Marketplace - Search NFT stacks: Failed to parse SearchStacksResult from json value"));
	// 			}
	//
	// 			OnMarketplaceQueryComplete.Execute(true, SearchStacksResult);
	// 		}
	// 	});
	// 	HttpRequest->ProcessRequest();
	// }

}