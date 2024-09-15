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

namespace OpenAPI
{

/*
 * OpenAPIBasicAPIError
 *
 * 
 */
class OPENAPI_API OpenAPIBasicAPIError : public Model
{
public:
    virtual ~OpenAPIBasicAPIError() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	/* Error Message */
	FString Message;
	/* Link to IMX documentation that can help resolve this error */
	FString Link;
	/* Trace ID of the initial request */
	FString TraceId;
};

}
