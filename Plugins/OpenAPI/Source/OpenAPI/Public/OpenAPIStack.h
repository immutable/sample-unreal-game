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
#include "OpenAPIChain.h"
#include "OpenAPINFTMetadataAttribute.h"

namespace OpenAPI
{

/*
 * OpenAPIStack
 *
 * Stack
 */
class OPENAPI_API OpenAPIStack : public Model
{
public:
    virtual ~OpenAPIStack() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	/* Stack ID */
	FGuid StackId;
	OpenAPIChain Chain;
	/* Contract address */
	FString ContractAddress;
	/* When the metadata was created */
	FDateTime CreatedAt;
	/* When the metadata was last updated */
	FDateTime UpdatedAt;
	/* The name of the NFT */
	TOptional<FString> Name;
	/* The description of the NFT */
	TOptional<FString> Description;
	/* The image url of the NFT */
	TOptional<FString> Image;
	/* The external website link of NFT */
	TOptional<FString> ExternalUrl;
	/* The animation url of the NFT */
	TOptional<FString> AnimationUrl;
	/* The youtube URL of NFT */
	TOptional<FString> YoutubeUrl;
	/* List of Metadata attributes */
	TOptional<TArray<OpenAPINFTMetadataAttribute>> Attributes;
	/* Total count of NFTs in the stack matching the filter params */
	int32 TotalCount = 0;
};

}
