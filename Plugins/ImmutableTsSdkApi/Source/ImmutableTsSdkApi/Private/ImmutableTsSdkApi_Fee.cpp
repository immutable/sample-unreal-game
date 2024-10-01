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

#include "ImmutableTsSdkApi_Fee.h"

#include "ImmutableTsSdkApiModule.h"
#include "ImmutableTsSdkApi_Helpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableTsSdkApi
{

void ImmutableTsSdkApi_Fee::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	if (Amount.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("amount")); WriteJsonValue(Writer, Amount.GetValue());
	}
	if (RecipientAddress.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("recipientAddress")); WriteJsonValue(Writer, RecipientAddress.GetValue());
	}
	if (Type.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("type")); WriteJsonValue(Writer, Type.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool ImmutableTsSdkApi_Fee::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("amount"), Amount);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("recipientAddress"), RecipientAddress);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("type"), Type);

	return ParseSuccess;
}

}