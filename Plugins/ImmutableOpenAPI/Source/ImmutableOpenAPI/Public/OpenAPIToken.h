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
#include "OpenAPIAssetVerificationStatus.h"
#include "OpenAPIChain.h"

namespace ImmutableOpenAPI
{

/*
 * OpenAPIToken
 *
 * 
 */
class IMMUTABLEOPENAPI_API OpenAPIToken : public Model
{
public:
    virtual ~OpenAPIToken() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	OpenAPIChain Chain;
	/* The address of token contract */
	FString ContractAddress;
	/* The address of root token contract */
	TOptional<FString> RootContractAddress;
	/* The id of the root chain for a bridged token */
	TOptional<FString> RootChainId;
	/* The name of the bridge, for bridged tokens only */
	TOptional<FString> BridgeUsed;
	/* The symbol of token */
	TOptional<FString> Symbol;
	/* The decimals of token */
	TOptional<int32> Decimals;
	/* The image url of token */
	TOptional<FString> ImageUrl;
	/* The name of token */
	TOptional<FString> Name;
	OpenAPIAssetVerificationStatus VerificationStatus;
	/* When the collection was last updated */
	FDateTime UpdatedAt;
	/* Indicates whether the token is canonical or not */
	bool IsCanonical = false;
};

}
