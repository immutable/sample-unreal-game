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
#include "OpenAPINFT.h"

namespace ImmutableOpenAPI
{

/*
 * OpenAPIGetNFTResult
 *
 * Single NFT
 */
class IMMUTABLEOPENAPI_API OpenAPIGetNFTResult : public Model
{
public:
    virtual ~OpenAPIGetNFTResult() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	OpenAPINFT Result;
};

}
