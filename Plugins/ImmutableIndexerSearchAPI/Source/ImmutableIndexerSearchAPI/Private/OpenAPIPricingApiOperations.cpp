/**
 * Indexer Marketplace APIs
 * This API implements endpoints to power data driven marketplace and game experiences
 *
 * OpenAPI spec version: 1.0
 * Contact: helpmebuild@immutable.com
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * https://github.com/OpenAPITools/openapi-generator
 * Do not edit the class manually.
 */

#include "OpenAPIPricingApiOperations.h"

#include "ImmutableIndexerSearchAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Dom/JsonObject.h"
#include "Templates/SharedPointer.h"
#include "HttpModule.h"
#include "PlatformHttp.h"

namespace ImmutableIndexerSearchAPI
{

FString OpenAPIPricingApi::QuotesForNFTsRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("chain_name"), FStringFormatArg(ToUrlString(ChainName)) },
	{ TEXT("contract_address"), FStringFormatArg(ToUrlString(ContractAddress)) } };

	FString Path = FString::Format(TEXT("/experimental/chains/{chain_name}/quotes/{contract_address}/nfts"), PathParams);

	TArray<FString> QueryParams;
	QueryParams.Add(CollectionToUrlString_multi(TokenId, TEXT("token_id")));
	if(PageCursor.IsSet())
	{
		QueryParams.Add(FString(TEXT("page_cursor=")) + ToUrlString(PageCursor.GetValue()));
	}
	Path += TCHAR('?');
	Path += FString::Join(QueryParams, TEXT("&"));

	return Path;
}

void OpenAPIPricingApi::QuotesForNFTsRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

}

void OpenAPIPricingApi::QuotesForNFTsResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetResponseString(TEXT("200 response"));
		break;
	case 400:
		SetResponseString(TEXT("Bad Request (400)"));
		break;
	case 401:
		SetResponseString(TEXT("Unauthorised Request (401)"));
		break;
	case 403:
		SetResponseString(TEXT("Forbidden Request (403)"));
		break;
	case 404:
		SetResponseString(TEXT("The specified resource was not found (404)"));
		break;
	case 429:
		SetResponseString(TEXT("Too Many Requests (429)"));
		break;
	case 500:
		SetResponseString(TEXT("Internal Server Error (500)"));
		break;
	}
}

bool OpenAPIPricingApi::QuotesForNFTsResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString OpenAPIPricingApi::QuotesForStacksRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("chain_name"), FStringFormatArg(ToUrlString(ChainName)) },
	{ TEXT("contract_address"), FStringFormatArg(ToUrlString(ContractAddress)) } };

	FString Path = FString::Format(TEXT("/experimental/chains/{chain_name}/quotes/{contract_address}/stacks"), PathParams);

	TArray<FString> QueryParams;
	QueryParams.Add(CollectionToUrlString_multi(StackId, TEXT("stack_id")));
	if(PageCursor.IsSet())
	{
		QueryParams.Add(FString(TEXT("page_cursor=")) + ToUrlString(PageCursor.GetValue()));
	}
	Path += TCHAR('?');
	Path += FString::Join(QueryParams, TEXT("&"));

	return Path;
}

void OpenAPIPricingApi::QuotesForStacksRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

}

void OpenAPIPricingApi::QuotesForStacksResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetResponseString(TEXT("200 response"));
		break;
	case 400:
		SetResponseString(TEXT("Bad Request (400)"));
		break;
	case 401:
		SetResponseString(TEXT("Unauthorised Request (401)"));
		break;
	case 403:
		SetResponseString(TEXT("Forbidden Request (403)"));
		break;
	case 404:
		SetResponseString(TEXT("The specified resource was not found (404)"));
		break;
	case 429:
		SetResponseString(TEXT("Too Many Requests (429)"));
		break;
	case 500:
		SetResponseString(TEXT("Internal Server Error (500)"));
		break;
	}
}

bool OpenAPIPricingApi::QuotesForStacksResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

}
