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
#include "OpenAPICancelOrders200ResponseResultFailedCancellationsInner.h"

namespace ImmutableTsSdkApi
{

/*
 * OpenAPICancelOrders200ResponseResult
 *
 * 
 */
class IMMUTABLETSSDKAPI_API OpenAPICancelOrders200ResponseResult : public Model
{
public:
    virtual ~OpenAPICancelOrders200ResponseResult() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	/* Orders which failed to be cancelled */
	TOptional<TArray<OpenAPICancelOrders200ResponseResultFailedCancellationsInner>> FailedCancellations;
	/* Orders which are marked for cancellation but the cancellation cannot be guaranteed */
	TOptional<TArray<FString>> PendingCancellations;
	/* Orders which were successfully cancelled */
	TOptional<TArray<FString>> SuccessfulCancellations;
};

}