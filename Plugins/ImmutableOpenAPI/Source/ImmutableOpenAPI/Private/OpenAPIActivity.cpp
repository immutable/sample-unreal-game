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

#include "OpenAPIActivity.h"

#include "ImmutableOpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableOpenAPI
{

void OpenAPIActivity::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("id")); WriteJsonValue(Writer, Id);
	Writer->WriteIdentifierPrefix(TEXT("chain")); WriteJsonValue(Writer, Chain);
	Writer->WriteIdentifierPrefix(TEXT("type")); WriteJsonValue(Writer, Type);
	Writer->WriteIdentifierPrefix(TEXT("details")); WriteJsonValue(Writer, Details);
	Writer->WriteIdentifierPrefix(TEXT("updated_at")); WriteJsonValue(Writer, UpdatedAt);
	Writer->WriteIdentifierPrefix(TEXT("indexed_at")); WriteJsonValue(Writer, IndexedAt);
	if (BlockchainMetadata.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("blockchain_metadata")); WriteJsonValue(Writer, BlockchainMetadata.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool OpenAPIActivity::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("id"), Id);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("chain"), Chain);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("type"), Type);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("details"), Details);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("updated_at"), UpdatedAt);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("indexed_at"), IndexedAt);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("blockchain_metadata"), BlockchainMetadata);

	return ParseSuccess;
}

}
