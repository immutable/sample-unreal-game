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

#include "OpenAPIMint.h"

#include "ImmutableOpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableOpenAPI
{

void OpenAPIMint::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("to")); WriteJsonValue(Writer, To);
	Writer->WriteIdentifierPrefix(TEXT("amount")); WriteJsonValue(Writer, Amount);
	Writer->WriteIdentifierPrefix(TEXT("asset")); WriteJsonValue(Writer, Asset);
	Writer->WriteObjectEnd();
}

bool OpenAPIMint::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("to"), To);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("amount"), Amount);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("asset"), Asset);

	return ParseSuccess;
}

}
