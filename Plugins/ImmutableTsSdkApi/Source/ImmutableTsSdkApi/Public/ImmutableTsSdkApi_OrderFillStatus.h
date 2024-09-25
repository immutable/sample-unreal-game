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
 * ImmutableTsSdkApi_OrderFillStatus
 *
 * 
 */
class IMMUTABLETSSDKAPI_API ImmutableTsSdkApi_OrderFillStatus : public Model
{
public:
    virtual ~ImmutableTsSdkApi_OrderFillStatus() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	TOptional<FString> Denominator;
	TOptional<FString> Numerator;
};

}
