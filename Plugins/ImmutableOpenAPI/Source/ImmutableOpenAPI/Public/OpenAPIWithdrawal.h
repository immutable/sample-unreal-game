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
 * OpenAPIWithdrawal
 *
 * The withdrawal activity details
 */
class IMMUTABLEOPENAPI_API OpenAPIWithdrawal : public Model
{
public:
    virtual ~OpenAPIWithdrawal() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	/* The account address the asset was withdrawn from */
	FString From;
	/* The amount of assets withdrawn */
	FString Amount;
	OpenAPIActivityAsset Asset;
};

}