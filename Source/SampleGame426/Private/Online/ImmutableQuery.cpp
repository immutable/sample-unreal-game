#include "ImmutableQuery.h"

#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "LogSampleGame.h"


bool ImmutableHttpRetryManager::Tick(float DeltaTime)
{
	FManager::Update();
	return true;
}

ImmutableHttpRetryParams::ImmutableHttpRetryParams(const FHttpRetrySystem::FRetryLimitCountSetting& InRetryLimitCountOverride, const FHttpRetrySystem::FRetryTimeoutRelativeSecondsSetting& InRetryTimeoutRelativeSecondsOverride, const FHttpRetrySystem::FRetryResponseCodes& InRetryResponseCodes, const FHttpRetrySystem::FRetryVerbs& InRetryVerbs, const FHttpRetrySystem::FRetryDomainsPtr& InRetryDomains)
	: RetryLimitCountOverride(InRetryLimitCountOverride)
	, RetryTimeoutRelativeSecondsOverride(InRetryTimeoutRelativeSecondsOverride)
	, RetryResponseCodes(InRetryResponseCodes)
	, RetryVerbs(InRetryVerbs)
	, RetryDomains(InRetryDomains)
{
}

void ImmutableResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	ResponseCode = InHttpResponseCode;
	SetSuccessful(EHttpResponseCodes::IsOk(InHttpResponseCode));
	if(InHttpResponseCode == EHttpResponseCodes::RequestTimeout)
	{
		SetResponseString(TEXT("Request Timeout"));
	}
}

void GetBalanceRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
}

FString GetBalanceRequest::ComputePath() const
{
	return  FString::Printf(TEXT("/balance?address=%s"), *Address);	
}

void GetUnsignedFulfillOrderTransactionsRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	const FString Body = FString::Printf(TEXT("{\"listingId\": \"%s\",\"takerAddress\": \"%s\",\"takerFees\": []}"), *ListingId, *TakerAddress);

	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader("Content-Type", TEXT("application/json"));
	HttpRequest->SetContentAsString(Body);
}

FString GetUnsignedFulfillOrderTransactionsRequest::ComputePath() const
{
	return FString::Printf(TEXT("/v1/ts-sdk/orderbook/fulfillOrder"));
}

void GetBalanceResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	ImmutableResponse::SetHttpResponseCode(InHttpResponseCode);
}

bool GetBalanceResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	GetBalanceResponse Response;
	
	//FJsonObjectConverter::JsonObjectStringToUStruct<GetBalanceResponse>(ResponseString, &GetBalanceResponse, 0, 0);
	//return TryGetJsonValue(JsonValue, Content);

	return true;
}

void GetUnsignedFulfillOrderTransactionsResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	ImmutableResponse::SetHttpResponseCode(InHttpResponseCode);
}

bool GetUnsignedFulfillOrderTransactionsResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return true;
}

ImmutableQuery::ImmutableQuery()
{
	Url = TEXT("http://localhost:3000");
}

ImmutableQuery::~ImmutableQuery()
{
}

void ImmutableQuery::SetURL(const FString& InUrl)
{
	Url = InUrl;
}

void ImmutableQuery::AddHeaderParam(const FString& Key, const FString& Value)
{
	AdditionalHeaderParams.Add(Key, Value);
}

void ImmutableQuery::ClearHeaderParams()
{
	AdditionalHeaderParams.Reset();
}

void ImmutableQuery::SetHttpRetryManager(FHttpRetrySystem::FManager& InRetryManager)
{
	if (RetryManager != &InRetryManager)
	{
		DefaultRetryManager.Reset();
		RetryManager = &InRetryManager;
	}
}

FHttpRetrySystem::FManager& ImmutableQuery::GetHttpRetryManager() const
{
	// checkf(RetryManager, TEXT("OpenAPISearchApi: RetryManager is null.  You may have meant to set it with SetHttpRetryManager first, or you may not be using a custom RetryManager at all."))
	return *RetryManager;
}

FHttpRequestPtr ImmutableQuery::GetBalance(const GetBalanceRequest& Request, const FGetBalanceDelegate& Delegate) const
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

	HttpRequest->OnProcessRequestComplete().BindRaw(this, &ImmutableQuery::OnGetBalance, Delegate);
	HttpRequest->ProcessRequest();
	
	return HttpRequest;
}

FHttpRequestPtr ImmutableQuery::GetUnsignedFulfillOrderTransactions(const GetUnsignedFulfillOrderTransactionsRequest& Request, const FGetUnsignedFulfillOrderTransactionsDelegate& Delegate) const
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

	HttpRequest->OnProcessRequestComplete().BindRaw(this, &ImmutableQuery::OnGetUnsignedFulfillOrderTransactionsResponse, Delegate);
	HttpRequest->ProcessRequest();
	
	return HttpRequest;
}

void ImmutableQuery::OnGetUnsignedFulfillOrderTransactionsResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FGetUnsignedFulfillOrderTransactionsDelegate Delegate) const
{
	GetUnsignedFulfillOrderTransactionsResponse Response;
	
	HandleResponse(HttpResponse, bSucceeded, Response);
	Delegate.ExecuteIfBound(Response);
}

void ImmutableQuery::OnGetBalance(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FGetBalanceDelegate Delegate) const
{
	GetBalanceResponse Response;
	
	HandleResponse(HttpResponse, bSucceeded, Response);
	Delegate.ExecuteIfBound(Response);
}

FHttpRequestRef ImmutableQuery::CreateHttpRequest(const ImmutableRequest& Request) const
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
			DefaultRetryManager = MakeUnique<ImmutableHttpRetryManager>(6, 60);
			RetryManager = DefaultRetryManager.Get();
		}

		const ImmutableHttpRetryParams& Params = Request.GetRetryParams().GetValue();
		return RetryManager->CreateRequest(Params.RetryLimitCountOverride, Params.RetryTimeoutRelativeSecondsOverride, Params.RetryResponseCodes, Params.RetryVerbs, Params.RetryDomains);
	}
}

bool ImmutableQuery::IsValid() const
{
	if (Url.IsEmpty())
	{
		UE_LOG(LogSampleGame, Error, TEXT("Endpoint Url is not set, request cannot be performed"));
		return false;
	}

	return true;
}

void ImmutableQuery::HandleResponse(FHttpResponsePtr HttpResponse, bool bSucceeded, ImmutableResponse& InOutResponse) const
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
		UE_LOG(LogSampleGame, Error, TEXT("Failed to deserialize Http response content (type:%s):\n%s"), *ContentType , *Content);
		return;
	}

	// By default, assume we failed to establish connection
	InOutResponse.SetHttpResponseCode(EHttpResponseCodes::RequestTimeout);
}
