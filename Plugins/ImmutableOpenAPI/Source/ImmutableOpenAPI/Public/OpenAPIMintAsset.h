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
#include "OpenAPINFTMetadataRequest.h"

namespace ImmutableOpenAPI
{

/*
 * OpenAPIMintAsset
 *
 * 
 */
class IMMUTABLEOPENAPI_API OpenAPIMintAsset : public Model
{
public:
    virtual ~OpenAPIMintAsset() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	/* The id of this asset in the system that originates the mint request */
	FString ReferenceId;
	/* The address of the receiver */
	FString OwnerAddress;
	/* An optional `uint256` token id as string. Required for ERC1155 collections. */
	TOptional<FString> TokenId;
	/* Optional mount of tokens to mint. Required for ERC1155 collections. ERC712 collections can omit this field or set it to 1 */
	TOptional<FString> Amount;
	TOptional<OpenAPINFTMetadataRequest> Metadata;
};

}