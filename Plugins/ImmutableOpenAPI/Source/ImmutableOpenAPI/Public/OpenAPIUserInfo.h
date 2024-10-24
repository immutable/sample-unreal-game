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
 * OpenAPIUserInfo
 *
 * 
 */
class IMMUTABLEOPENAPI_API OpenAPIUserInfo : public Model
{
public:
    virtual ~OpenAPIUserInfo() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	/* The user's id */
	FString Sub;
	/* The user's email address */
	TOptional<FString> Email;
	/* The user's Passport address if it has been registered */
	TOptional<FString> PassportAddress;
	/* The user's list of linked addresses */
	TArray<FString> LinkedAddresses;
};

}