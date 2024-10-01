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

#include "ImmutableTsSdkApi_V1TsSdkOrderbookPrepareOrderCancellationsPost200Response.h"

#include "ImmutableTsSdkApiModule.h"
#include "ImmutableTsSdkApi_Helpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableTsSdkApi
{

void ImmutableTsSdkApi_V1TsSdkOrderbookPrepareOrderCancellationsPost200Response::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	if (SignableAction.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("signableAction")); WriteJsonValue(Writer, SignableAction.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool ImmutableTsSdkApi_V1TsSdkOrderbookPrepareOrderCancellationsPost200Response::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("signableAction"), SignableAction);

	return ParseSuccess;
}

}