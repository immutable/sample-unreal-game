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
#include "OpenAPIActivity.h"

namespace ImmutableOpenAPI
{

/*
 * OpenAPIGetActivityResult
 *
 * Single activity
 */
class IMMUTABLEOPENAPI_API OpenAPIGetActivityResult : public Model
{
public:
    virtual ~OpenAPIGetActivityResult() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	OpenAPIActivity Result;
};

}