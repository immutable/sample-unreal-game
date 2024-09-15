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

#include "OpenAPIQuotesForStacksResult.h"

#include "OpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace OpenAPI
{

void OpenAPIQuotesForStacksResult::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("result")); WriteJsonValue(Writer, Result);
	Writer->WriteIdentifierPrefix(TEXT("page")); WriteJsonValue(Writer, Page);
	Writer->WriteObjectEnd();
}

bool OpenAPIQuotesForStacksResult::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("result"), Result);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("page"), Page);

	return ParseSuccess;
}

}
