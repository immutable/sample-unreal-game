/**
 * TS SDK API
 * running ts sdk as an api
 *
 * OpenAPI spec version: 1.0.0
 * Contact: contact@immutable.com
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * https://github.com/OpenAPITools/openapi-generator
 * Do not edit the class manually.
 */

#include "ImmutableTsSdkApi_V1TsSdkOrderbookCancelOrdersOnChainPostRequest.h"

#include "ImmutableTsSdkApiModule.h"
#include "ImmutableTsSdkApi_Helpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableTsSdkApi
{

void ImmutableTsSdkApi_V1TsSdkOrderbookCancelOrdersOnChainPostRequest::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("orderIds")); WriteJsonValue(Writer, OrderIds);
	Writer->WriteIdentifierPrefix(TEXT("accountAddress")); WriteJsonValue(Writer, AccountAddress);
	Writer->WriteObjectEnd();
}

bool ImmutableTsSdkApi_V1TsSdkOrderbookCancelOrdersOnChainPostRequest::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("orderIds"), OrderIds);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("accountAddress"), AccountAddress);

	return ParseSuccess;
}

}
