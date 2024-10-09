/**
 * Indexer Marketplace APIs
 * This API implements endpoints to power data driven marketplace and game experiences
 *
 * OpenAPI spec version: 1.0
 * Contact: helpmebuild@immutable.com
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * https://github.com/OpenAPITools/openapi-generator
 * Do not edit the class manually.
 */

#include "OpenAPIPage.h"

#include "ImmutableIndexerSearchAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableIndexerSearchAPI
{

void OpenAPIPage::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	if (PreviousCursor.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("previous_cursor")); WriteJsonValue(Writer, PreviousCursor.GetValue());
	}
	if (NextCursor.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("next_cursor")); WriteJsonValue(Writer, NextCursor.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool OpenAPIPage::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("previous_cursor"), PreviousCursor);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("next_cursor"), NextCursor);

	return ParseSuccess;
}

}
