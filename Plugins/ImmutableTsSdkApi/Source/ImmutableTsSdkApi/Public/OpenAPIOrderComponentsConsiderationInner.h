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
#include "OpenAPIItemType.h"

namespace ImmutableTsSdkApi
{

/*
 * OpenAPIOrderComponentsConsiderationInner
 *
 * 
 */
class IMMUTABLETSSDKAPI_API OpenAPIOrderComponentsConsiderationInner : public Model
{
public:
    virtual ~OpenAPIOrderComponentsConsiderationInner() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	FString EndAmount;
	FString IdentifierOrCriteria;
	OpenAPIItemType ItemType;
	FString Recipient;
	FString StartAmount;
	FString Token;
};

}