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

#include "ImmutableTsSdkApi_V1TsSdkOrderbookFulfillOrderPost200Response.h"

#include "ImmutableTsSdkApiModule.h"
#include "ImmutableTsSdkApi_Helpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableTsSdkApi
{

void ImmutableTsSdkApi_V1TsSdkOrderbookFulfillOrderPost200Response::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	if (Actions.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("actions")); WriteJsonValue(Writer, Actions.GetValue());
	}
	if (Expiration.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("expiration")); WriteJsonValue(Writer, Expiration.GetValue());
	}
	if (Order.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("order")); WriteJsonValue(Writer, Order.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool ImmutableTsSdkApi_V1TsSdkOrderbookFulfillOrderPost200Response::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("actions"), Actions);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("expiration"), Expiration);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("order"), Order);

	return ParseSuccess;
}

}
