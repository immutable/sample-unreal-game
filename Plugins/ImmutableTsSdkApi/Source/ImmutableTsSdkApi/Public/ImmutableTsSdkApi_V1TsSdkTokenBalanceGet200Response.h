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

namespace ImmutableTsSdkApi
{

/*
 * ImmutableTsSdkApi_V1TsSdkTokenBalanceGet200Response
 *
 * The response body returned from get balance endpoint
 */
class IMMUTABLETSSDKAPI_API ImmutableTsSdkApi_V1TsSdkTokenBalanceGet200Response : public Model
{
public:
    virtual ~ImmutableTsSdkApi_V1TsSdkTokenBalanceGet200Response() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	FString Quantity;
};

}
