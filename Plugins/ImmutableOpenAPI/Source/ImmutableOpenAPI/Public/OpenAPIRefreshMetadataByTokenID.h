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
#include "OpenAPINFTMetadataAttribute.h"

namespace ImmutableOpenAPI
{

/*
 * OpenAPIRefreshMetadataByTokenID
 *
 * 
 */
class IMMUTABLEOPENAPI_API OpenAPIRefreshMetadataByTokenID : public Model
{
public:
    virtual ~OpenAPIRefreshMetadataByTokenID() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	/* The name of the NFT */
	TOptional<FString> Name;
	/* The description of the NFT */
	TOptional<FString> Description;
	/* The image url of the NFT */
	TOptional<FString> Image;
	/* The external link of the NFT */
	TOptional<FString> ExternalUrl;
	/* The animation url of the NFT */
	TOptional<FString> AnimationUrl;
	/* The youtube link of the NFT */
	TOptional<FString> YoutubeUrl;
	/* List of Metadata attributes */
	TOptional<TArray<OpenAPINFTMetadataAttribute>> Attributes;
	/* An `uint256` token id as string */
	FString TokenId;
};

}