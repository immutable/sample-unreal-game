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
#include "OpenAPILastTrade.h"

namespace ImmutableIndexerSearchAPI
{

/*
 * OpenAPIMarketNft
 *
 * NFT market data
 */
class IMMUTABLEINDEXERSEARCHAPI_API OpenAPIMarketNft : public Model
{
public:
    virtual ~OpenAPIMarketNft() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	TOptional<OpenAPILastTrade> LastTrade;
};

}
