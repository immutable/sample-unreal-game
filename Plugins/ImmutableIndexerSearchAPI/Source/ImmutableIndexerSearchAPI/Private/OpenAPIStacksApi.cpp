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

#include "OpenAPIStacksApi.h"

#include "OpenAPIStacksApiOperations.h"
#include "ImmutableIndexerSearchAPIModule.h"

#include "HttpModule.h"
#include "Serialization/JsonSerializer.h"

namespace ImmutableIndexerSearchAPI
{

OpenAPIStacksApi::OpenAPIStacksApi()
: Url(TEXT("https://api.immutable.com"))
{
}

OpenAPIStacksApi::~OpenAPIStacksApi() {}

void OpenAPIStacksApi::SetURL(const FString& InUrl)
{
	Url = InUrl;
}

void OpenAPIStacksApi::AddHeaderParam(const FString& Key, const FString& Value)
{
	AdditionalHeaderParams.Add(Key, Value);
}

void OpenAPIStacksApi::ClearHeaderParams()
{
	AdditionalHeaderParams.Reset();
}

bool OpenAPIStacksApi::IsValid() const
{
	if (Url.IsEmpty())
	{
		UE_LOG(LogImmutableIndexerSearchAPI, Error, TEXT("OpenAPIStacksApi: Endpoint Url is not set, request cannot be performed"));
		return false;
	}

	return true;
}

void OpenAPIStacksApi::SetHttpRetryManager(FHttpRetrySystem::FManager& InRetryManager)
{
	if (RetryManager != &InRetryManager)
	{
		DefaultRetryManager.Reset();
		RetryManager = &InRetryManager;
	}
}

FHttpRetrySystem::FManager& OpenAPIStacksApi::GetHttpRetryManager()
{
	checkf(RetryManager, TEXT("OpenAPIStacksApi: RetryManager is null.  You may have meant to set it with SetHttpRetryManager first, or you may not be using a custom RetryManager at all."))
	return *RetryManager;
}

FHttpRequestRef OpenAPIStacksApi::CreateHttpRequest(const Request& Request) const
{
	if (!Request.GetRetryParams().IsSet())
	{
		return FHttpModule::Get().CreateRequest();
	}
	else
	{
		if (!RetryManager)
		{
			// Create default retry manager if none was specified
			DefaultRetryManager = MakeUnique<HttpRetryManager>(6, 60);
			RetryManager = DefaultRetryManager.Get();
		}

		const HttpRetryParams& Params = Request.GetRetryParams().GetValue();
		return RetryManager->CreateRequest(Params.RetryLimitCountOverride, Params.RetryTimeoutRelativeSecondsOverride, Params.RetryResponseCodes, Params.RetryVerbs, Params.RetryDomains);
	}
}

void OpenAPIStacksApi::HandleResponse(FHttpResponsePtr HttpResponse, bool bSucceeded, Response& InOutResponse) const
{
	InOutResponse.SetHttpResponse(HttpResponse);
	InOutResponse.SetSuccessful(bSucceeded);

	if (bSucceeded && HttpResponse.IsValid())
	{
		InOutResponse.SetHttpResponseCode((EHttpResponseCodes::Type)HttpResponse->GetResponseCode());
		FString ContentType = HttpResponse->GetContentType();
		FString Content;

		if (ContentType.IsEmpty())
		{
			return; // Nothing to parse
		}
		else if (ContentType.StartsWith(TEXT("application/json")) || ContentType.StartsWith("text/json"))
		{
			Content = HttpResponse->GetContentAsString();

			TSharedPtr<FJsonValue> JsonValue;
			auto Reader = TJsonReaderFactory<>::Create(Content);

			if (FJsonSerializer::Deserialize(Reader, JsonValue) && JsonValue.IsValid())
			{
				if (InOutResponse.FromJson(JsonValue))
					return; // Successfully parsed
			}
		}
		else if(ContentType.StartsWith(TEXT("text/plain")))
		{
			Content = HttpResponse->GetContentAsString();
			InOutResponse.SetResponseString(Content);
			return; // Successfully parsed
		}

		// Report the parse error but do not mark the request as unsuccessful. Data could be partial or malformed, but the request succeeded.
		UE_LOG(LogImmutableIndexerSearchAPI, Error, TEXT("Failed to deserialize Http response content (type:%s):\n%s"), *ContentType , *Content);
		return;
	}

	// By default, assume we failed to establish connection
	InOutResponse.SetHttpResponseCode(EHttpResponseCodes::RequestTimeout);
}

FHttpRequestPtr OpenAPIStacksApi::Backfill(const BackfillRequest& Request, const FBackfillDelegate& Delegate /*= FBackfillDelegate()*/) const
{
	if (!IsValid())
		return nullptr;

	FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
	HttpRequest->SetURL(*(Url + Request.ComputePath()));

	for(const auto& It : AdditionalHeaderParams)
	{
		HttpRequest->SetHeader(It.Key, It.Value);
	}

	Request.SetupHttpRequest(HttpRequest);

	HttpRequest->OnProcessRequestComplete().BindRaw(this, &OpenAPIStacksApi::OnBackfillResponse, Delegate);
	HttpRequest->ProcessRequest();
	return HttpRequest;
}

void OpenAPIStacksApi::OnBackfillResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FBackfillDelegate Delegate) const
{
	BackfillResponse Response;
	HandleResponse(HttpResponse, bSucceeded, Response);
	Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr OpenAPIStacksApi::SearchNFTs(const SearchNFTsRequest& Request, const FSearchNFTsDelegate& Delegate /*= FSearchNFTsDelegate()*/) const
{
	if (!IsValid())
		return nullptr;

	FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
	HttpRequest->SetURL(*(Url + Request.ComputePath()));

	for(const auto& It : AdditionalHeaderParams)
	{
		HttpRequest->SetHeader(It.Key, It.Value);
	}

	Request.SetupHttpRequest(HttpRequest);

	HttpRequest->OnProcessRequestComplete().BindRaw(this, &OpenAPIStacksApi::OnSearchNFTsResponse, Delegate);
	HttpRequest->ProcessRequest();
	return HttpRequest;
}

void OpenAPIStacksApi::OnSearchNFTsResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FSearchNFTsDelegate Delegate) const
{
	SearchNFTsResponse Response;
	HandleResponse(HttpResponse, bSucceeded, Response);
	Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr OpenAPIStacksApi::SearchStacks(const SearchStacksRequest& Request, const FSearchStacksDelegate& Delegate /*= FSearchStacksDelegate()*/) const
{
	if (!IsValid())
		return nullptr;

	FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
	HttpRequest->SetURL(*(Url + Request.ComputePath()));

	for(const auto& It : AdditionalHeaderParams)
	{
		HttpRequest->SetHeader(It.Key, It.Value);
	}

	Request.SetupHttpRequest(HttpRequest);

	HttpRequest->OnProcessRequestComplete().BindRaw(this, &OpenAPIStacksApi::OnSearchStacksResponse, Delegate);
	HttpRequest->ProcessRequest();
	return HttpRequest;
}

void OpenAPIStacksApi::OnSearchStacksResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FSearchStacksDelegate Delegate) const
{
	SearchStacksResponse Response;
	HandleResponse(HttpResponse, bSucceeded, Response);
	Delegate.ExecuteIfBound(Response);
}

}
