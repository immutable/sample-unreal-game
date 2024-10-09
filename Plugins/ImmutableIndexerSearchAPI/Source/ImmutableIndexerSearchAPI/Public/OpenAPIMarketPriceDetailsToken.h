/**
 * Indexer Marketplace APIs
 * This API implements endpoints to power data driven marketplace and game experiences
 *
 * OpenAPI spec version: 1.0
 * Contact: helpmebuild@immutable.com
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * https://github.com/OpenAPITools/openapi-generator
 * Do not edit the class manually.
 */

#pragma once

#include "OpenAPIBaseModel.h"
#include "OpenAPIMarketPriceERC20Token.h"
#include "OpenAPIMarketPriceNativeToken.h"

namespace ImmutableIndexerSearchAPI
{

/*
 * OpenAPIMarketPriceDetailsToken
 *
 * Token details
 */
class IMMUTABLEINDEXERSEARCHAPI_API OpenAPIMarketPriceDetailsToken : public Model
{
public:
    virtual ~OpenAPIMarketPriceDetailsToken() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	enum class TypeEnum
	{
		Native,
		ERC20,
  	};

	static FString EnumToString(const TypeEnum& EnumValue);
	static bool EnumFromString(const FString& EnumAsString, TypeEnum& EnumValue);
	/* Token type user is offering, which in this case is the native IMX token */
	TypeEnum Type;
	/* The symbol of token */
	TOptional<FString> Symbol;
	/* Address of ERC20 token */
	FString ContractAddress;
	/* The decimals of token */
	TOptional<int32> Decimals;
};

}
