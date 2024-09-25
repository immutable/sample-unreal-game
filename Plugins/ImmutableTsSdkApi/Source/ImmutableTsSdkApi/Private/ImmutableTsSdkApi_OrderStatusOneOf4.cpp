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

#include "ImmutableTsSdkApi_OrderStatusOneOf4.h"

#include "ImmutableTsSdkApiModule.h"
#include "ImmutableTsSdkApi_Helpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableTsSdkApi
{

inline FString ToString(const ImmutableTsSdkApi_OrderStatusOneOf4::NameEnum& Value)
{
	switch (Value)
	{
	case ImmutableTsSdkApi_OrderStatusOneOf4::NameEnum::Inactive:
		return TEXT("INACTIVE");
	}

	UE_LOG(LogImmutableTsSdkApi, Error, TEXT("Invalid ImmutableTsSdkApi_OrderStatusOneOf4::NameEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString ImmutableTsSdkApi_OrderStatusOneOf4::EnumToString(const ImmutableTsSdkApi_OrderStatusOneOf4::NameEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, ImmutableTsSdkApi_OrderStatusOneOf4::NameEnum& Value)
{
	static TMap<FString, ImmutableTsSdkApi_OrderStatusOneOf4::NameEnum> StringToEnum = { 
		{ TEXT("INACTIVE"), ImmutableTsSdkApi_OrderStatusOneOf4::NameEnum::Inactive }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool ImmutableTsSdkApi_OrderStatusOneOf4::EnumFromString(const FString& EnumAsString, ImmutableTsSdkApi_OrderStatusOneOf4::NameEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const ImmutableTsSdkApi_OrderStatusOneOf4::NameEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, ImmutableTsSdkApi_OrderStatusOneOf4::NameEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void ImmutableTsSdkApi_OrderStatusOneOf4::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	if (Name.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("name")); WriteJsonValue(Writer, Name.GetValue());
	}
	if (SufficientApprovals.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("sufficient_approvals")); WriteJsonValue(Writer, SufficientApprovals.GetValue());
	}
	if (SufficientBalances.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("sufficient_balances")); WriteJsonValue(Writer, SufficientBalances.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool ImmutableTsSdkApi_OrderStatusOneOf4::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("name"), Name);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("sufficient_approvals"), SufficientApprovals);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("sufficient_balances"), SufficientBalances);

	return ParseSuccess;
}

}
