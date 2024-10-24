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
#include "OpenAPIOperatorAllowlistStatus.h"
#include "OpenAPIOperatorAllowlistStatusDetails.h"

namespace ImmutableOpenAPI
{

/*
 * OpenAPIOperatorAllowlistContractStatus
 *
 * 
 */
class IMMUTABLEOPENAPI_API OpenAPIOperatorAllowlistContractStatus : public Model
{
public:
    virtual ~OpenAPIOperatorAllowlistContractStatus() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	OpenAPIChain Chain;
	/* The address of the contract */
	FString ContractAddress;
	OpenAPIOperatorAllowlistStatus Status;
	OpenAPIOperatorAllowlistStatusDetails Details;
	/* When the contract status was created */
	FDateTime CreatedAt;
	/* Who created the status */
	FString CreatedBy;
};

}