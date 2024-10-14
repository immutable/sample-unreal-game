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

namespace ImmutableOpenAPI
{

/*
 * OpenAPILinkWalletV2Request
 *
 * Link wallet V2 request
 */
class IMMUTABLEOPENAPI_API OpenAPILinkWalletV2Request : public Model
{
public:
    virtual ~OpenAPILinkWalletV2Request() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	/* This should be the EIP-6963 rdns value, if you're unable to get the rdns value you can provide \"External\". If using WalletConnect then provide \"WalletConnect\". */
	FString Type;
	/* The address of the external wallet being linked to Passport */
	FString WalletAddress;
	/* The EIP-712 signature */
	FString Signature;
	/* A unique identifier for the signature */
	FString Nonce;
};

}
