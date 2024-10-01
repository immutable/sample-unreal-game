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
#include "OpenAPIFee.h"
#include "OpenAPIPaymentAmount.h"
#include "OpenAPIPriceDetailsToken.h"

namespace ImmutableOpenAPI
{

/*
 * OpenAPIPriceDetails
 *
 * Price details
 */
class IMMUTABLEOPENAPI_API OpenAPIPriceDetails : public Model
{
public:
    virtual ~OpenAPIPriceDetails() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	OpenAPIPriceDetailsToken Token;
	OpenAPIPaymentAmount Amount;
	OpenAPIPaymentAmount FeeInclusiveAmount;
	TArray<OpenAPIFee> Fees;
};

}