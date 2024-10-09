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
#include "OpenAPIMarketPriceDetails.h"

namespace ImmutableIndexerSearchAPI
{

/*
 * OpenAPILastTrade
 *
 * Last trade
 */
class IMMUTABLEINDEXERSEARCHAPI_API OpenAPILastTrade : public Model
{
public:
    virtual ~OpenAPILastTrade() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	/* Trade ID */
	FGuid TradeId;
	/* Token id of the traded asset (uint256 as string) */
	FString TokenId;
	/* Price details, list of payments involved in this trade */
	TArray<OpenAPIMarketPriceDetails> PriceDetails;
	/* Amount of the trade (uint256 as string) */
	FString Amount;
	/* When the trade was created */
	FDateTime CreatedAt;
};

}