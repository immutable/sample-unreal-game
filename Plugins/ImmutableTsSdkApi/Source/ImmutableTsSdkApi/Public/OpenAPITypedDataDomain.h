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
 * OpenAPITypedDataDomain
 *
 * 
 */
class IMMUTABLETSSDKAPI_API OpenAPITypedDataDomain : public Model
{
public:
    virtual ~OpenAPITypedDataDomain() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	TOptional<FString> ChainId;
	TOptional<FString> Name;
	TOptional<FString> Salt;
	TOptional<FString> VerifyingContract;
	TOptional<FString> Version;
};

}