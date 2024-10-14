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
#include "OpenAPIChain.h"
#include "OpenAPIFee.h"
#include "OpenAPIItem.h"
#include "OpenAPITradeBlockchainMetadata.h"

namespace ImmutableOpenAPI
{

/*
 * OpenAPITrade
 *
 * 
 */
class IMMUTABLEOPENAPI_API OpenAPITrade : public Model
{
public:
    virtual ~OpenAPITrade() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	/* Buy items are transferred from the taker to the maker. */
	TArray<OpenAPIItem> Buy;
	/* Deprecated. Use maker and taker addresses instead of buyer and seller addresses. */
	FString BuyerAddress;
	/* Deprecated. Use fees instead. The taker always pays the fees. */
	TArray<OpenAPIFee> BuyerFees;
	TArray<OpenAPIFee> Fees;
	OpenAPIChain Chain;
	FString OrderId;
	TOptional<OpenAPITradeBlockchainMetadata> BlockchainMetadata;
	/* Time the on-chain trade event is indexed by the order book system */
	FDateTime IndexedAt;
	/* Global Trade identifier */
	FString Id;
	/* Sell items are transferred from the maker to the taker. */
	TArray<OpenAPIItem> Sell;
	/* Deprecated. Use maker and taker addresses instead of buyer and seller addresses. */
	FString SellerAddress;
	FString MakerAddress;
	FString TakerAddress;
};

}
