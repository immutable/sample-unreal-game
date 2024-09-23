/**
 * Indexer Search API
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
#include "OpenAPINFTMetadataAttributeValue.h"

namespace ImmutableOpenAPI
{

/*
 * OpenAPINFTMetadataAttribute
 *
 * 
 */
class IMMUTABLEOPENAPI_API OpenAPINFTMetadataAttribute : public Model
{
public:
    virtual ~OpenAPINFTMetadataAttribute() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	enum class DisplayTypeEnum
	{
		Number,
		BoostPercentage,
		BoostNumber,
		Date,
  	};

	static FString EnumToString(const DisplayTypeEnum& EnumValue);
	static bool EnumFromString(const FString& EnumAsString, DisplayTypeEnum& EnumValue);
	/* Display type for this attribute */
	TOptional<DisplayTypeEnum> DisplayType;
	/* The metadata trait type */
	FString TraitType;
	FString Value;
};

}
