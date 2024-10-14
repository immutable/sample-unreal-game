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

#include "OpenAPINftsApiOperations.h"

#include "ImmutableOpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Dom/JsonObject.h"
#include "Templates/SharedPointer.h"
#include "HttpModule.h"
#include "PlatformHttp.h"

namespace ImmutableOpenAPI
{

FString OpenAPINftsApi::CreateMintRequestRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("contract_address"), FStringFormatArg(ToUrlString(ContractAddress)) },
	{ TEXT("chain_name"), FStringFormatArg(ToUrlString(ChainName)) } };

	FString Path = FString::Format(TEXT("/v1/chains/{chain_name}/collections/{contract_address}/nfts/mint-requests"), PathParams);

	return Path;
}

void OpenAPINftsApi::CreateMintRequestRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = { TEXT("application/json") };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("POST"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
		// Body parameters
		FString JsonBody;
		JsonWriter Writer = TJsonWriterFactory<>::Create(&JsonBody);

		WriteJsonValue(Writer, OpenAPICreateMintRequestRequest);
		Writer->Close();

		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
		HttpRequest->SetContentAsString(JsonBody);
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
		UE_LOG(LogImmutableOpenAPI, Error, TEXT("Body parameter (OpenAPICreateMintRequestRequest) was ignored, not supported in multipart form"));
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
		UE_LOG(LogImmutableOpenAPI, Error, TEXT("Body parameter (OpenAPICreateMintRequestRequest) was ignored, not supported in urlencoded requests"));
	}
	else
	{
		UE_LOG(LogImmutableOpenAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void OpenAPINftsApi::CreateMintRequestResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 202:
		SetResponseString(TEXT("Accepted"));
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
	case 409:
		SetResponseString(TEXT("Conflict (409)"));
		break;
	case 429:
		SetResponseString(TEXT("Too Many mint requests (429)"));
		break;
	case 500:
		SetResponseString(TEXT("Internal Server Error (500)"));
		break;
	}
}

bool OpenAPINftsApi::CreateMintRequestResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString OpenAPINftsApi::GetMintRequestRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("contract_address"), FStringFormatArg(ToUrlString(ContractAddress)) },
	{ TEXT("chain_name"), FStringFormatArg(ToUrlString(ChainName)) },
	{ TEXT("reference_id"), FStringFormatArg(ToUrlString(ReferenceId)) } };

	FString Path = FString::Format(TEXT("/v1/chains/{chain_name}/collections/{contract_address}/nfts/mint-requests/{reference_id}"), PathParams);

	return Path;
}

void OpenAPINftsApi::GetMintRequestRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

}

void OpenAPINftsApi::GetMintRequestResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
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
	case 500:
		SetResponseString(TEXT("Internal Server Error (500)"));
		break;
	}
}

bool OpenAPINftsApi::GetMintRequestResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString OpenAPINftsApi::GetNFTRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("contract_address"), FStringFormatArg(ToUrlString(ContractAddress)) },
	{ TEXT("token_id"), FStringFormatArg(ToUrlString(TokenId)) },
	{ TEXT("chain_name"), FStringFormatArg(ToUrlString(ChainName)) } };

	FString Path = FString::Format(TEXT("/v1/chains/{chain_name}/collections/{contract_address}/nfts/{token_id}"), PathParams);

	return Path;
}

void OpenAPINftsApi::GetNFTRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

}

void OpenAPINftsApi::GetNFTResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
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

bool OpenAPINftsApi::GetNFTResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString OpenAPINftsApi::ListAllNFTsRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("chain_name"), FStringFormatArg(ToUrlString(ChainName)) } };

	FString Path = FString::Format(TEXT("/v1/chains/{chain_name}/nfts"), PathParams);

	TArray<FString> QueryParams;
	if(FromUpdatedAt.IsSet())
	{
		QueryParams.Add(FString(TEXT("from_updated_at=")) + ToUrlString(FromUpdatedAt.GetValue()));
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

void OpenAPINftsApi::ListAllNFTsRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

}

void OpenAPINftsApi::ListAllNFTsResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
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

bool OpenAPINftsApi::ListAllNFTsResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString OpenAPINftsApi::ListMintRequestsRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("contract_address"), FStringFormatArg(ToUrlString(ContractAddress)) },
	{ TEXT("chain_name"), FStringFormatArg(ToUrlString(ChainName)) } };

	FString Path = FString::Format(TEXT("/v1/chains/{chain_name}/collections/{contract_address}/nfts/mint-requests"), PathParams);

	TArray<FString> QueryParams;
	if(PageCursor.IsSet())
	{
		QueryParams.Add(FString(TEXT("page_cursor=")) + ToUrlString(PageCursor.GetValue()));
	}
	if(PageSize.IsSet())
	{
		QueryParams.Add(FString(TEXT("page_size=")) + ToUrlString(PageSize.GetValue()));
	}
	if(Status.IsSet())
	{
		QueryParams.Add(FString(TEXT("status=")) + ToUrlString(Status.GetValue()));
	}
	Path += TCHAR('?');
	Path += FString::Join(QueryParams, TEXT("&"));

	return Path;
}

void OpenAPINftsApi::ListMintRequestsRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

}

void OpenAPINftsApi::ListMintRequestsResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
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
	case 500:
		SetResponseString(TEXT("Internal Server Error (500)"));
		break;
	}
}

bool OpenAPINftsApi::ListMintRequestsResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString OpenAPINftsApi::ListNFTsRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("contract_address"), FStringFormatArg(ToUrlString(ContractAddress)) },
	{ TEXT("chain_name"), FStringFormatArg(ToUrlString(ChainName)) } };

	FString Path = FString::Format(TEXT("/v1/chains/{chain_name}/collections/{contract_address}/nfts"), PathParams);

	TArray<FString> QueryParams;
	if(TokenId.IsSet())
	{
		QueryParams.Add(CollectionToUrlString_multi(TokenId.GetValue(), TEXT("token_id")));
	}
	if(FromUpdatedAt.IsSet())
	{
		QueryParams.Add(FString(TEXT("from_updated_at=")) + ToUrlString(FromUpdatedAt.GetValue()));
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

void OpenAPINftsApi::ListNFTsRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

}

void OpenAPINftsApi::ListNFTsResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
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

bool OpenAPINftsApi::ListNFTsResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString OpenAPINftsApi::ListNFTsByAccountAddressRequest::ComputePath() const
{
	TMap<FString, FStringFormatArg> PathParams = { 
	{ TEXT("account_address"), FStringFormatArg(ToUrlString(AccountAddress)) },
	{ TEXT("chain_name"), FStringFormatArg(ToUrlString(ChainName)) } };

	FString Path = FString::Format(TEXT("/v1/chains/{chain_name}/accounts/{account_address}/nfts"), PathParams);

	TArray<FString> QueryParams;
	if(ContractAddress.IsSet())
	{
		QueryParams.Add(FString(TEXT("contract_address=")) + ToUrlString(ContractAddress.GetValue()));
	}
	if(TokenId.IsSet())
	{
		QueryParams.Add(CollectionToUrlString_multi(TokenId.GetValue(), TEXT("token_id")));
	}
	if(FromUpdatedAt.IsSet())
	{
		QueryParams.Add(FString(TEXT("from_updated_at=")) + ToUrlString(FromUpdatedAt.GetValue()));
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

void OpenAPINftsApi::ListNFTsByAccountAddressRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

}

void OpenAPINftsApi::ListNFTsByAccountAddressResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
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

bool OpenAPINftsApi::ListNFTsByAccountAddressResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

}
