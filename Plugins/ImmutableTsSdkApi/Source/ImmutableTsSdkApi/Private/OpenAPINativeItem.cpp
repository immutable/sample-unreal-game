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

#include "OpenAPINativeItem.h"

#include "ImmutableTsSdkApiModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableTsSdkApi
{

inline FString ToString(const OpenAPINativeItem::TypeEnum& Value)
{
	switch (Value)
	{
	case OpenAPINativeItem::TypeEnum::Native:
		return TEXT("NATIVE");
	}

	UE_LOG(LogImmutableTsSdkApi, Error, TEXT("Invalid OpenAPINativeItem::TypeEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString OpenAPINativeItem::EnumToString(const OpenAPINativeItem::TypeEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, OpenAPINativeItem::TypeEnum& Value)
{
	static TMap<FString, OpenAPINativeItem::TypeEnum> StringToEnum = { 
		{ TEXT("NATIVE"), OpenAPINativeItem::TypeEnum::Native }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool OpenAPINativeItem::EnumFromString(const FString& EnumAsString, OpenAPINativeItem::TypeEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const OpenAPINativeItem::TypeEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, OpenAPINativeItem::TypeEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void OpenAPINativeItem::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("amount")); WriteJsonValue(Writer, Amount);
	Writer->WriteIdentifierPrefix(TEXT("type")); WriteJsonValue(Writer, Type);
	Writer->WriteObjectEnd();
}

bool OpenAPINativeItem::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("amount"), Amount);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("type"), Type);

	return ParseSuccess;
}

}