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
#include "OpenAPIStack.h"

namespace ImmutableIndexerSearchAPI
{

/*
 * OpenAPIStackBundle
 *
 * Stack bundle includes stacks, markets and listings
 */
class IMMUTABLEINDEXERSEARCHAPI_API OpenAPIStackBundle : public Model
{
public:
    virtual ~OpenAPIStackBundle() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	OpenAPIStack Stack;
	/* Total count of NFTs in the stack matching the filter params */
	int32 StackCount = 0;
	TOptional<OpenAPIMarket> Market;
	/* List of open listings for the stack. */
	TArray<OpenAPIListing> Listings;
};

}