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
 * OpenAPICreateMintRequestResult
 *
 * 
 */
class IMMUTABLEOPENAPI_API OpenAPICreateMintRequestResult : public Model
{
public:
    virtual ~OpenAPICreateMintRequestResult() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	FString ImxMintRequestsLimit;
	FString ImxMintRequestsLimitReset;
	FString ImxRemainingMintRequests;
	FString ImxMintRequestsRetryAfter;
};

}