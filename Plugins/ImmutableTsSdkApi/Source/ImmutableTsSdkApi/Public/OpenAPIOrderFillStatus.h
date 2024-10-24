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

namespace ImmutableTsSdkApi
{

/*
 * OpenAPIOrderFillStatus
 *
 * 
 */
class IMMUTABLETSSDKAPI_API OpenAPIOrderFillStatus : public Model
{
public:
    virtual ~OpenAPIOrderFillStatus() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	TOptional<FString> Denominator;
	TOptional<FString> Numerator;
};

}