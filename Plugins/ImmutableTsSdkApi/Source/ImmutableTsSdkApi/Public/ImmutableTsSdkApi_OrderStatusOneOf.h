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
 * ImmutableTsSdkApi_OrderStatusOneOf
 *
 * 
 */
class IMMUTABLETSSDKAPI_API ImmutableTsSdkApi_OrderStatusOneOf : public Model
{
public:
    virtual ~ImmutableTsSdkApi_OrderStatusOneOf() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	enum class NameEnum
	{
		Active,
  	};

	static FString EnumToString(const NameEnum& EnumValue);
	static bool EnumFromString(const FString& EnumAsString, NameEnum& EnumValue);
	/* The order status that indicates an order can be fulfilled. */
	TOptional<NameEnum> Name;
};

}
