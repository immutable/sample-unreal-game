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
#include "OpenAPIAssetCollectionItem.h"
#include "OpenAPIERC20Item.h"
#include "OpenAPIFee.h"
#include "OpenAPIProtocolData.h"

namespace ImmutableOpenAPI
{

/*
 * OpenAPICreateCollectionBidRequestBody
 *
 * 
 */
class IMMUTABLEOPENAPI_API OpenAPICreateCollectionBidRequestBody : public Model
{
public:
    virtual ~OpenAPICreateCollectionBidRequestBody() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	FString AccountAddress;
	FString OrderHash;
	/* Buy item for collection bid should either be ERC721 or ERC1155 collection item */
	TArray<OpenAPIAssetCollectionItem> Buy;
	/* Buy fees should only include maker marketplace fees and should be no more than two entries as more entires will incur more gas. It is best practice to have this as few as possible. */
	TArray<OpenAPIFee> Fees;
	/* Time after which the Order is considered expired */
	FDateTime EndAt;
	OpenAPIProtocolData ProtocolData;
	/* A random value added to the create Order request */
	FString Salt;
	/* Sell item for collection bid should be an ERC20 item */
	TArray<OpenAPIERC20Item> Sell;
	/* Digital signature generated by the user for the specific Order */
	FString Signature;
	/* Time after which Order is considered active */
	FDateTime StartAt;
};

}
