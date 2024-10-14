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

#include "OpenAPISignCraftingResult.h"

#include "ImmutableOpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableOpenAPI
{

void OpenAPISignCraftingResult::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("signer_address")); WriteJsonValue(Writer, SignerAddress);
	Writer->WriteIdentifierPrefix(TEXT("signature")); WriteJsonValue(Writer, Signature);
	Writer->WriteObjectEnd();
}

bool OpenAPISignCraftingResult::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("signer_address"), SignerAddress);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("signature"), Signature);

	return ParseSuccess;
}

}
