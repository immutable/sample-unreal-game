/**
 * TS SDK API
 * running ts sdk as an api
 *
 * OpenAPI spec version: 1.0.0
 * Contact: contact@immutable.com
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * https://github.com/OpenAPITools/openapi-generator
 * Do not edit the class manually.
 */

#pragma once

#include "OpenAPIBaseModel.h"
#include "OpenAPIOrderbookApi.h"

#include "OpenAPICancelOrders200Response.h"
#include "OpenAPICancelOrdersOnChain200Response.h"
#include "OpenAPICancelOrdersOnChainRequest.h"
#include "OpenAPICancelOrdersRequest.h"
#include "OpenAPICreateListing200Response.h"
#include "OpenAPICreateListingRequest.h"
#include "OpenAPIFulfillOrder200Response.h"
#include "OpenAPIFulfillOrderRequest.h"
#include "OpenAPIPrepareListing200Response.h"
#include "OpenAPIPrepareListingRequest.h"
#include "OpenAPIPrepareOrderCancellations200Response.h"
#include "OpenAPIPrepareOrderCancellationsRequest.h"
#include "OpenAPITokenBalance200Response.h"

namespace ImmutableTsSdkApi
{

/* 

*/
class IMMUTABLETSSDKAPI_API OpenAPIOrderbookApi::CancelOrdersRequest : public Request
{
public:
    virtual ~CancelOrdersRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	TOptional<OpenAPICancelOrdersRequest> OpenAPICancelOrdersRequest;
};

class IMMUTABLETSSDKAPI_API OpenAPIOrderbookApi::CancelOrdersResponse : public Response
{
public:
    virtual ~CancelOrdersResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    OpenAPICancelOrders200Response Content;
};

/* 

*/
class IMMUTABLETSSDKAPI_API OpenAPIOrderbookApi::CancelOrdersOnChainRequest : public Request
{
public:
    virtual ~CancelOrdersOnChainRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	TOptional<OpenAPICancelOrdersOnChainRequest> OpenAPICancelOrdersOnChainRequest;
};

class IMMUTABLETSSDKAPI_API OpenAPIOrderbookApi::CancelOrdersOnChainResponse : public Response
{
public:
    virtual ~CancelOrdersOnChainResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    OpenAPICancelOrdersOnChain200Response Content;
};

/* 

*/
class IMMUTABLETSSDKAPI_API OpenAPIOrderbookApi::CreateListingRequest : public Request
{
public:
    virtual ~CreateListingRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	TOptional<OpenAPICreateListingRequest> OpenAPICreateListingRequest;
};

class IMMUTABLETSSDKAPI_API OpenAPIOrderbookApi::CreateListingResponse : public Response
{
public:
    virtual ~CreateListingResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    OpenAPICreateListing200Response Content;
};

/* 

*/
class IMMUTABLETSSDKAPI_API OpenAPIOrderbookApi::FulfillOrderRequest : public Request
{
public:
    virtual ~FulfillOrderRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	TOptional<OpenAPIFulfillOrderRequest> OpenAPIFulfillOrderRequest;
};

class IMMUTABLETSSDKAPI_API OpenAPIOrderbookApi::FulfillOrderResponse : public Response
{
public:
    virtual ~FulfillOrderResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    OpenAPIFulfillOrder200Response Content;
};

/* 

*/
class IMMUTABLETSSDKAPI_API OpenAPIOrderbookApi::PrepareListingRequest : public Request
{
public:
    virtual ~PrepareListingRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	TOptional<OpenAPIPrepareListingRequest> OpenAPIPrepareListingRequest;
};

class IMMUTABLETSSDKAPI_API OpenAPIOrderbookApi::PrepareListingResponse : public Response
{
public:
    virtual ~PrepareListingResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    OpenAPIPrepareListing200Response Content;
};

/* 

*/
class IMMUTABLETSSDKAPI_API OpenAPIOrderbookApi::PrepareOrderCancellationsRequest : public Request
{
public:
    virtual ~PrepareOrderCancellationsRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	TOptional<OpenAPIPrepareOrderCancellationsRequest> OpenAPIPrepareOrderCancellationsRequest;
};

class IMMUTABLETSSDKAPI_API OpenAPIOrderbookApi::PrepareOrderCancellationsResponse : public Response
{
public:
    virtual ~PrepareOrderCancellationsResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    OpenAPIPrepareOrderCancellations200Response Content;
};

/* 

*/
class IMMUTABLETSSDKAPI_API OpenAPIOrderbookApi::TokenBalanceRequest : public Request
{
public:
    virtual ~TokenBalanceRequest() {}
	void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const final;
	FString ComputePath() const final;

	FString WalletAddress;
	FString ContractAddress;
};

class IMMUTABLETSSDKAPI_API OpenAPIOrderbookApi::TokenBalanceResponse : public Response
{
public:
    virtual ~TokenBalanceResponse() {}
	void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode) final;
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;

    OpenAPITokenBalance200Response Content;
};

}