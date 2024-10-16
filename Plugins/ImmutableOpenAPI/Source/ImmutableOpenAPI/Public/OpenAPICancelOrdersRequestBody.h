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
 * OpenAPICancelOrdersRequestBody
 *
 * 
 */
class IMMUTABLEOPENAPI_API OpenAPICancelOrdersRequestBody : public Model
{
public:
    virtual ~OpenAPICancelOrdersRequestBody() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	/* Address of the user initiating the cancel request */
	FString AccountAddress;
	/* List of order ids proposed for cancellation */
	TArray<FGuid> Orders;
	/* Signature generated by the user for the specific cancellation request */
	FString Signature;
};

}