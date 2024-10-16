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
#include "OpenAPIMarketPriceDetailsToken.h"
#include "OpenAPIMarketPriceFees.h"
#include "OpenAPIPaymentAmount.h"

namespace ImmutableOpenAPI
{

/*
 * OpenAPIMarketPriceDetails
 *
 * Market Price details
 */
class IMMUTABLEOPENAPI_API OpenAPIMarketPriceDetails : public Model
{
public:
    virtual ~OpenAPIMarketPriceDetails() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	OpenAPIMarketPriceDetailsToken Token;
	OpenAPIPaymentAmount Amount;
	OpenAPIPaymentAmount FeeInclusiveAmount;
	TArray<OpenAPIMarketPriceFees> Fees;
};

}