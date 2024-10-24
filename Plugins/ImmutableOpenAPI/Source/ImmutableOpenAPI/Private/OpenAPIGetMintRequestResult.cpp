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

#include "OpenAPIGetMintRequestResult.h"

#include "ImmutableOpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableOpenAPI
{

void OpenAPIGetMintRequestResult::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("chain")); WriteJsonValue(Writer, Chain);
	Writer->WriteIdentifierPrefix(TEXT("collection_address")); WriteJsonValue(Writer, CollectionAddress);
	Writer->WriteIdentifierPrefix(TEXT("reference_id")); WriteJsonValue(Writer, ReferenceId);
	Writer->WriteIdentifierPrefix(TEXT("owner_address")); WriteJsonValue(Writer, OwnerAddress);
	if (TokenId.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("token_id")); WriteJsonValue(Writer, TokenId.GetValue());
	}
	if (Amount.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("amount")); WriteJsonValue(Writer, Amount.GetValue());
	}
	if (ActivityId.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("activity_id")); WriteJsonValue(Writer, ActivityId.GetValue());
	}
	if (TransactionHash.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("transaction_hash")); WriteJsonValue(Writer, TransactionHash.GetValue());
	}
	Writer->WriteIdentifierPrefix(TEXT("created_at")); WriteJsonValue(Writer, CreatedAt);
	Writer->WriteIdentifierPrefix(TEXT("updated_at")); WriteJsonValue(Writer, UpdatedAt);
	if (Error.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("error")); WriteJsonValue(Writer, Error.GetValue());
	}
	Writer->WriteIdentifierPrefix(TEXT("status")); WriteJsonValue(Writer, Status);
	Writer->WriteObjectEnd();
}

bool OpenAPIGetMintRequestResult::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("chain"), Chain);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("collection_address"), CollectionAddress);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("reference_id"), ReferenceId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("owner_address"), OwnerAddress);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("token_id"), TokenId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("amount"), Amount);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("activity_id"), ActivityId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("transaction_hash"), TransactionHash);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("created_at"), CreatedAt);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("updated_at"), UpdatedAt);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("error"), Error);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("status"), Status);

	return ParseSuccess;
}

}