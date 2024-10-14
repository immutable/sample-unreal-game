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
 * OpenAPIAPIError403
 *
 * 
 */
class IMMUTABLEOPENAPI_API OpenAPIAPIError403 : public Model
{
public:
    virtual ~OpenAPIAPIError403() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	/* Error Message */
	FString Message;
	/* Link to IMX documentation that can help resolve this error */
	FString Link;
	/* Trace ID of the initial request */
	FString TraceId;
	enum class CodeEnum
	{
		AuthenticationError,
  	};

	static FString EnumToString(const CodeEnum& EnumValue);
	static bool EnumFromString(const FString& EnumAsString, CodeEnum& EnumValue);
	/* Error Code */
	CodeEnum Code;
	/* Additional details to help resolve the error */
	TOptional<TSharedPtr<FJsonObject>> Details;
};

}
