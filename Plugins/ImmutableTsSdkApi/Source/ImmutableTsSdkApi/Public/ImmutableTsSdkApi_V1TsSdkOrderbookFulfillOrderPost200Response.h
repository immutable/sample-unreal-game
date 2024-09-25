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

#include "ImmutableTsSdkApi_BaseModel.h"
#include "ImmutableTsSdkApi_Order.h"
#include "ImmutableTsSdkApi_TransactionAction.h"

namespace ImmutableTsSdkApi
{

/*
 * ImmutableTsSdkApi_V1TsSdkOrderbookFulfillOrderPost200Response
 *
 * Response schema for the fulfillOrder endpoint
 */
class IMMUTABLETSSDKAPI_API ImmutableTsSdkApi_V1TsSdkOrderbookFulfillOrderPost200Response : public Model
{
public:
    virtual ~ImmutableTsSdkApi_V1TsSdkOrderbookFulfillOrderPost200Response() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	TOptional<TArray<ImmutableTsSdkApi_TransactionAction>> Actions;
	/* User MUST submit the fulfillment transaction before the expiration Submitting after the expiration will result in a on chain revert */
	TOptional<FString> Expiration;
	TOptional<ImmutableTsSdkApi_Order> Order;
};

}
