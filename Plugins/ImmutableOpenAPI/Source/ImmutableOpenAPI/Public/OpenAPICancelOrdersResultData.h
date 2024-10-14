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
#include "OpenAPIFailedOrderCancellation.h"

namespace ImmutableOpenAPI
{

/*
 * OpenAPICancelOrdersResultData
 *
 * 
 */
class IMMUTABLEOPENAPI_API OpenAPICancelOrdersResultData : public Model
{
public:
    virtual ~OpenAPICancelOrdersResultData() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	/* Orders which were successfully cancelled */
	TArray<FString> SuccessfulCancellations;
	/* Orders which are marked for cancellation but the cancellation cannot be guaranteed */
	TArray<FString> PendingCancellations;
	/* Orders which failed to be cancelled */
	TArray<OpenAPIFailedOrderCancellation> FailedCancellations;
};

}
