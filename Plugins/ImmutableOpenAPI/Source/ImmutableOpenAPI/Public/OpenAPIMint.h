/**
 * Immutable zkEVM API
 * Immutable Multi Rollup API
 *
 * OpenAPI spec version: 1.0.0
 * Contact: support@immutable.com
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * https://github.com/OpenAPITools/openapi-generator
 * Do not edit the class manually.
 */

#pragma once

#include "OpenAPIBaseModel.h"
#include "OpenAPIActivityAsset.h"

namespace ImmutableOpenAPI
{

/*
 * OpenAPIMint
 *
 * The mint activity details
 */
class IMMUTABLEOPENAPI_API OpenAPIMint : public Model
{
public:
    virtual ~OpenAPIMint() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	/* The account address the asset was minted to */
	FString To;
	/* The minted amount */
	FString Amount;
	OpenAPIActivityAsset Asset;
};

}
