/**
 * Immutable zkEVM API
 * Immutable Multi Rollup API
 *
 * OpenAPI spec version: 1.0.0
 * Contact: support@immutable.com
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * https://github.com/OpenAPITools/openapi-generator
 * Do not edit the class manually.
 */

#include "OpenAPIActivitiesApiOperations.h"

#include "ImmutableOpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Dom/JsonObject.h"
#include "Templates/SharedPointer.h"
#include "HttpModule.h"
#include "PlatformHttp.h"

namespace ImmutableOpenAPI
{

FString OpenAPIActivitiesApi::GetActivityRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("chain_name"), FStringFormatArg(ToUrlString(ChainName)) },
	{ TEXT("activity_id"), FStringFormatArg(ToUrlString(ActivityId)) } };

	FString Path = FString::Format(TEXT("/v1/chains/{chain_name}/activities/{activity_id}"), PathParams);

	return Path;
}

void OpenAPIActivitiesApi::GetActivityRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

}

void OpenAPIActivitiesApi::GetActivityResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
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
	case 404:
		SetResponseString(TEXT("The specified resource was not found (404)"));
		break;
	case 500:
		SetResponseString(TEXT("Internal Server Error (500)"));
		break;
	}
}

bool OpenAPIActivitiesApi::GetActivityResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString OpenAPIActivitiesApi::ListActivitiesRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("chain_name"), FStringFormatArg(ToUrlString(ChainName)) } };

	FString Path = FString::Format(TEXT("/v1/chains/{chain_name}/activities"), PathParams);

	TArray<FString> QueryParams;
	if(ContractAddress.IsSet())
	{
		QueryParams.Add(FString(TEXT("contract_address=")) + ToUrlString(ContractAddress.GetValue()));
	}
	if(TokenId.IsSet())
	{
		QueryParams.Add(FString(TEXT("token_id=")) + ToUrlString(TokenId.GetValue()));
	}
	if(AccountAddress.IsSet())
	{
		QueryParams.Add(FString(TEXT("account_address=")) + ToUrlString(AccountAddress.GetValue()));
	}
	if(ActivityType.IsSet())
	{
		QueryParams.Add(FString(TEXT("activity_type=")) + ToUrlString(ActivityType.GetValue()));
	}
	if(TransactionHash.IsSet())
	{
		QueryParams.Add(FString(TEXT("transaction_hash=")) + ToUrlString(TransactionHash.GetValue()));
	}
	if(PageCursor.IsSet())
	{
		QueryParams.Add(FString(TEXT("page_cursor=")) + ToUrlString(PageCursor.GetValue()));
	}
	if(PageSize.IsSet())
	{
		QueryParams.Add(FString(TEXT("page_size=")) + ToUrlString(PageSize.GetValue()));
	}
	Path += TCHAR('?');
	Path += FString::Join(QueryParams, TEXT("&"));

	return Path;
}

void OpenAPIActivitiesApi::ListActivitiesRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

}

void OpenAPIActivitiesApi::ListActivitiesResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
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
	case 404:
		SetResponseString(TEXT("The specified resource was not found (404)"));
		break;
	case 500:
		SetResponseString(TEXT("Internal Server Error (500)"));
		break;
	}
}

bool OpenAPIActivitiesApi::ListActivitiesResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString OpenAPIActivitiesApi::ListActivityHistoryRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("chain_name"), FStringFormatArg(ToUrlString(ChainName)) } };

	FString Path = FString::Format(TEXT("/v1/chains/{chain_name}/activity-history"), PathParams);

	TArray<FString> QueryParams;
	QueryParams.Add(FString(TEXT("from_updated_at=")) + ToUrlString(FromUpdatedAt));
	if(ToUpdatedAt.IsSet())
	{
		QueryParams.Add(FString(TEXT("to_updated_at=")) + ToUrlString(ToUpdatedAt.GetValue()));
	}
	if(ContractAddress.IsSet())
	{
		QueryParams.Add(FString(TEXT("contract_address=")) + ToUrlString(ContractAddress.GetValue()));
	}
	if(ActivityType.IsSet())
	{
		QueryParams.Add(FString(TEXT("activity_type=")) + ToUrlString(ActivityType.GetValue()));
	}
	if(PageCursor.IsSet())
	{
		QueryParams.Add(FString(TEXT("page_cursor=")) + ToUrlString(PageCursor.GetValue()));
	}
	if(PageSize.IsSet())
	{
		QueryParams.Add(FString(TEXT("page_size=")) + ToUrlString(PageSize.GetValue()));
	}
	Path += TCHAR('?');
	Path += FString::Join(QueryParams, TEXT("&"));

	return Path;
}

void OpenAPIActivitiesApi::ListActivityHistoryRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

}

void OpenAPIActivitiesApi::ListActivityHistoryResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
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
	case 404:
		SetResponseString(TEXT("The specified resource was not found (404)"));
		break;
	case 500:
		SetResponseString(TEXT("Internal Server Error (500)"));
		break;
	}
}

bool OpenAPIActivitiesApi::ListActivityHistoryResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

}