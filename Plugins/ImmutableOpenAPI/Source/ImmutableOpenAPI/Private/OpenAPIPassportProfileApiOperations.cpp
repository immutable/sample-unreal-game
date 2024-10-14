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

#include "OpenAPIPassportProfileApiOperations.h"

#include "ImmutableOpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Dom/JsonObject.h"
#include "Templates/SharedPointer.h"
#include "HttpModule.h"
#include "PlatformHttp.h"

namespace ImmutableOpenAPI
{

FString OpenAPIPassportProfileApi::GetUserInfoRequest::ComputePath() const
{
	FString Path(TEXT("/passport-profile/v1/user/info"));
	return Path;
}

void OpenAPIPassportProfileApi::GetUserInfoRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("application/json") };

	HttpRequest->SetVerb(TEXT("GET"));

}

void OpenAPIPassportProfileApi::GetUserInfoResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetResponseString(TEXT("Passport user&#39;s info"));
		break;
	case 401:
		SetResponseString(TEXT("UnauthorizedError"));
		break;
	case 500:
		SetResponseString(TEXT("InternalServerError"));
		break;
	case 0:
	default:
		SetResponseString(TEXT("unexpected error"));
		break;
	}
}

bool OpenAPIPassportProfileApi::GetUserInfoResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString OpenAPIPassportProfileApi::LinkWalletV2Request::ComputePath() const
{
	FString Path(TEXT("/passport-profile/v2/linked-wallets"));
	return Path;
}

void OpenAPIPassportProfileApi::LinkWalletV2Request::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
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

		if (OpenAPILinkWalletV2Request.IsSet())
		{
			WriteJsonValue(Writer, OpenAPILinkWalletV2Request.GetValue());
		}
		Writer->Close();

		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
		HttpRequest->SetContentAsString(JsonBody);
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
		UE_LOG(LogImmutableOpenAPI, Error, TEXT("Body parameter (OpenAPILinkWalletV2Request) was ignored, not supported in multipart form"));
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
		UE_LOG(LogImmutableOpenAPI, Error, TEXT("Body parameter (OpenAPILinkWalletV2Request) was ignored, not supported in urlencoded requests"));
	}
	else
	{
		UE_LOG(LogImmutableOpenAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void OpenAPIPassportProfileApi::LinkWalletV2Response::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetResponseString(TEXT("OK"));
		break;
	case 400:
		SetResponseString(TEXT("BadRequestError"));
		break;
	case 401:
		SetResponseString(TEXT("UnauthorizedError"));
		break;
	case 403:
		SetResponseString(TEXT("ForbiddenError"));
		break;
	case 500:
		SetResponseString(TEXT("InternalServerError"));
		break;
	}
}

bool OpenAPIPassportProfileApi::LinkWalletV2Response::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

}
