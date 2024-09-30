#pragma once

#include "HttpRetrySystem.h"
#include "ImmutableQueryDataTypes.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

struct SAMPLEGAME426_API ImmutableHttpRetryManager
	: public FHttpRetrySystem::FManager
#if ENGINE_MAJOR_VERSION <= 4
	, public FTickerObjectBase
#else
	, public FTSTickerObjectBase
#endif
{
	using FManager::FManager;

	virtual bool Tick(float DeltaTime) override final;
};

struct SAMPLEGAME426_API ImmutableHttpRetryParams
{
	ImmutableHttpRetryParams(
		const FHttpRetrySystem::FRetryLimitCountSetting& InRetryLimitCountOverride = FHttpRetrySystem::FRetryLimitCountSetting(),
		const FHttpRetrySystem::FRetryTimeoutRelativeSecondsSetting& InRetryTimeoutRelativeSecondsOverride = FHttpRetrySystem::FRetryTimeoutRelativeSecondsSetting(),
		const FHttpRetrySystem::FRetryResponseCodes& InRetryResponseCodes = FHttpRetrySystem::FRetryResponseCodes(),
		const FHttpRetrySystem::FRetryVerbs& InRetryVerbs = FHttpRetrySystem::FRetryVerbs(),
		const FHttpRetrySystem::FRetryDomainsPtr& InRetryDomains = FHttpRetrySystem::FRetryDomainsPtr()
	);

	FHttpRetrySystem::FRetryLimitCountSetting				RetryLimitCountOverride;
	FHttpRetrySystem::FRetryTimeoutRelativeSecondsSetting	RetryTimeoutRelativeSecondsOverride;
	FHttpRetrySystem::FRetryResponseCodes					RetryResponseCodes;
	FHttpRetrySystem::FRetryVerbs							RetryVerbs;
	FHttpRetrySystem::FRetryDomainsPtr						RetryDomains;
};

class SAMPLEGAME426_API ImmutableRequest
{
public:
	virtual ~ImmutableRequest() {}
	virtual void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const = 0;
	virtual FString ComputePath() const = 0;

	/* Enables retry and optionally sets a retry policy for this request */
	void SetShouldRetry(const ImmutableHttpRetryParams& Params = ImmutableHttpRetryParams()) { RetryParams = Params; }
	const TOptional<ImmutableHttpRetryParams>& GetRetryParams() const { return RetryParams; }

private:
	TOptional<ImmutableHttpRetryParams> RetryParams;
};

class SAMPLEGAME426_API ImmutableResponse
{
public:
	virtual ~ImmutableResponse() {}
	virtual bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) = 0;

	void SetSuccessful(bool InSuccessful) { Successful = InSuccessful; }
	bool IsSuccessful() const { return Successful; }

	virtual void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode);
	EHttpResponseCodes::Type GetHttpResponseCode() const { return ResponseCode; }

	void SetResponseString(const FString& InResponseString) { ResponseString = InResponseString; }
	const FString& GetResponseString() const { return ResponseString; }

	void SetHttpResponse(const FHttpResponsePtr& InHttpResponse) { HttpResponse = InHttpResponse; }
	const FHttpResponsePtr& GetHttpResponse() const { return HttpResponse; }

private:
	bool Successful;
	EHttpResponseCodes::Type ResponseCode;
	FString ResponseString;
	FHttpResponsePtr HttpResponse;
};

class SAMPLEGAME426_API GetBalanceRequest : public ImmutableRequest
{
public:
	virtual ~GetBalanceRequest() override {}
	virtual void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const override final;
	virtual FString ComputePath() const override final;

	FString Address;
};

class SAMPLEGAME426_API GetUnsignedFulfillOrderTransactionsRequest : public ImmutableRequest
{
public:
	virtual ~GetUnsignedFulfillOrderTransactionsRequest() override {}
	virtual void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const override final;
	virtual FString ComputePath() const override final;

	FString ListingId;
	FString TakerAddress;
};

class SAMPLEGAME426_API GetBalanceResponse : public ImmutableResponse
{
public:
	virtual ~GetBalanceResponse() override {}
	virtual void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) override final;
	virtual bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) override final;

	float Quantity;
};

class SAMPLEGAME426_API GetUnsignedFulfillOrderTransactionsResponse : public ImmutableResponse
{
public:
	virtual ~GetUnsignedFulfillOrderTransactionsResponse() override {}
	virtual void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) override final;
	virtual bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) override final;

	TArray<FAction> Actions;

	FString Expiration;

	FOrder Order;
};

class SAMPLEGAME426_API ImmutableQuery
{
public:
	ImmutableQuery();
	~ImmutableQuery();

	/* Sets the URL Endpoint.
	* Note: several fallback endpoints can be configured in request retry po, see Request::SetShouldRetry */
	void SetURL(const FString& InUrl);

	/* Adds global header params to all requests */
	void AddHeaderParam(const FString& Key, const FString& Value);
	void ClearHeaderParams();

	/* Sets the retry manager to the user-defined retry manager. User must manage the lifetime of the retry manager.
	* If no retry manager is specified and a request needs retries, a default retry manager will be used.
	* See also: Request::SetShouldRetry */
	void SetHttpRetryManager(FHttpRetrySystem::FManager& InRetryManager);
	FHttpRetrySystem::FManager& GetHttpRetryManager() const;

	DECLARE_DELEGATE_OneParam(FGetBalanceDelegate, const GetBalanceResponse&);
	DECLARE_DELEGATE_OneParam(FGetUnsignedFulfillOrderTransactionsDelegate, const GetUnsignedFulfillOrderTransactionsResponse&);

    FHttpRequestPtr GetBalance(const GetBalanceRequest& Request, const FGetBalanceDelegate& Delegate = FGetBalanceDelegate()) const;
    FHttpRequestPtr GetUnsignedFulfillOrderTransactions(const GetUnsignedFulfillOrderTransactionsRequest& Request, const FGetUnsignedFulfillOrderTransactionsDelegate& Delegate = FGetUnsignedFulfillOrderTransactionsDelegate()) const;
    
private:
    void OnGetBalance(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FGetBalanceDelegate Delegate) const;
    void OnGetUnsignedFulfillOrderTransactionsResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FGetUnsignedFulfillOrderTransactionsDelegate Delegate) const;
    
	FHttpRequestRef CreateHttpRequest(const ImmutableRequest& Request) const;
	bool IsValid() const;
	void HandleResponse(FHttpResponsePtr HttpResponse, bool bSucceeded, ImmutableResponse& InOutResponse) const;

	FString Url;
	TMap<FString,FString> AdditionalHeaderParams;
	mutable FHttpRetrySystem::FManager* RetryManager = nullptr;
	mutable TUniquePtr<ImmutableHttpRetryManager> DefaultRetryManager;
	
};
