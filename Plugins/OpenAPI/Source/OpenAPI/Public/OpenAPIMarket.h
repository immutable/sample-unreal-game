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
#include "OpenAPILastTrade.h"
#include "OpenAPIListing.h"

namespace OpenAPI
{

/*
 * OpenAPIMarket
 *
 * Market data
 */
class OPENAPI_API OpenAPIMarket : public Model
{
public:
    virtual ~OpenAPIMarket() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	TOptional<OpenAPIListing> FloorListing;
	TOptional<OpenAPILastTrade> LastTrade;
};

}
