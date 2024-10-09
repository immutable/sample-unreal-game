/**
 * Indexer Marketplace APIs
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
#include "OpenAPIListing.h"
#include "OpenAPIMarket.h"
#include "OpenAPINFTWithStack.h"

namespace ImmutableIndexerSearchAPI
{

/*
 * OpenAPINFTBundle
 *
 * NFT bundle includes NFT with stack, markets and listings
 */
class IMMUTABLEINDEXERSEARCHAPI_API OpenAPINFTBundle : public Model
{
public:
    virtual ~OpenAPINFTBundle() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	OpenAPINFTWithStack NftWithStack;
	TOptional<OpenAPIMarket> Market;
	/* List of open listings for the stack. */
	TArray<OpenAPIListing> Listings;
};

}
