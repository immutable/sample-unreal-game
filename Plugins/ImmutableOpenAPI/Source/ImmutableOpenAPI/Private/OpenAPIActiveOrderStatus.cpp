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

#include "OpenAPIActiveOrderStatus.h"

#include "ImmutableOpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableOpenAPI
{

inline FString ToString(const OpenAPIActiveOrderStatus::NameEnum& Value)
{
	switch (Value)
	{
	case OpenAPIActiveOrderStatus::NameEnum::Active:
		return TEXT("ACTIVE");
	}

	UE_LOG(LogImmutableOpenAPI, Error, TEXT("Invalid OpenAPIActiveOrderStatus::NameEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString OpenAPIActiveOrderStatus::EnumToString(const OpenAPIActiveOrderStatus::NameEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, OpenAPIActiveOrderStatus::NameEnum& Value)
{
	static TMap<FString, OpenAPIActiveOrderStatus::NameEnum> StringToEnum = { 
		{ TEXT("ACTIVE"), OpenAPIActiveOrderStatus::NameEnum::Active }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool OpenAPIActiveOrderStatus::EnumFromString(const FString& EnumAsString, OpenAPIActiveOrderStatus::NameEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const OpenAPIActiveOrderStatus::NameEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, OpenAPIActiveOrderStatus::NameEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void OpenAPIActiveOrderStatus::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("name")); WriteJsonValue(Writer, Name);
	Writer->WriteObjectEnd();
}

bool OpenAPIActiveOrderStatus::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("name"), Name);

	return ParseSuccess;
}

}
