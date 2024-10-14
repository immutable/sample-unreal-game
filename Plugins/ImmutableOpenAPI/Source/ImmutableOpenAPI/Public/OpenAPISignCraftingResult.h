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

namespace ImmutableOpenAPI
{

/*
 * OpenAPISignCraftingResult
 *
 * 
 */
class IMMUTABLEOPENAPI_API OpenAPISignCraftingResult : public Model
{
public:
    virtual ~OpenAPISignCraftingResult() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	/* An Ethereum address */
	FString SignerAddress;
	/* The signature of the request */
	FString Signature;
};

}
