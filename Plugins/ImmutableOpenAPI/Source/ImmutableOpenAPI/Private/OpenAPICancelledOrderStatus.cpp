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

#include "OpenAPICancelledOrderStatus.h"

#include "ImmutableOpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableOpenAPI
{

inline FString ToString(const OpenAPICancelledOrderStatus::NameEnum& Value)
{
	switch (Value)
	{
	case OpenAPICancelledOrderStatus::NameEnum::Cancelled:
		return TEXT("CANCELLED");
	}

	UE_LOG(LogImmutableOpenAPI, Error, TEXT("Invalid OpenAPICancelledOrderStatus::NameEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString OpenAPICancelledOrderStatus::EnumToString(const OpenAPICancelledOrderStatus::NameEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, OpenAPICancelledOrderStatus::NameEnum& Value)
{
	static TMap<FString, OpenAPICancelledOrderStatus::NameEnum> StringToEnum = { 
		{ TEXT("CANCELLED"), OpenAPICancelledOrderStatus::NameEnum::Cancelled }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool OpenAPICancelledOrderStatus::EnumFromString(const FString& EnumAsString, OpenAPICancelledOrderStatus::NameEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const OpenAPICancelledOrderStatus::NameEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, OpenAPICancelledOrderStatus::NameEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

inline FString ToString(const OpenAPICancelledOrderStatus::CancellationTypeEnum& Value)
{
	switch (Value)
	{
	case OpenAPICancelledOrderStatus::CancellationTypeEnum::OnChain:
		return TEXT("ON_CHAIN");
	case OpenAPICancelledOrderStatus::CancellationTypeEnum::OffChain:
		return TEXT("OFF_CHAIN");
	case OpenAPICancelledOrderStatus::CancellationTypeEnum::Underfunded:
		return TEXT("UNDERFUNDED");
	}

	UE_LOG(LogImmutableOpenAPI, Error, TEXT("Invalid OpenAPICancelledOrderStatus::CancellationTypeEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString OpenAPICancelledOrderStatus::EnumToString(const OpenAPICancelledOrderStatus::CancellationTypeEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, OpenAPICancelledOrderStatus::CancellationTypeEnum& Value)
{
	static TMap<FString, OpenAPICancelledOrderStatus::CancellationTypeEnum> StringToEnum = { 
		{ TEXT("ON_CHAIN"), OpenAPICancelledOrderStatus::CancellationTypeEnum::OnChain },
		{ TEXT("OFF_CHAIN"), OpenAPICancelledOrderStatus::CancellationTypeEnum::OffChain },
		{ TEXT("UNDERFUNDED"), OpenAPICancelledOrderStatus::CancellationTypeEnum::Underfunded }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool OpenAPICancelledOrderStatus::EnumFromString(const FString& EnumAsString, OpenAPICancelledOrderStatus::CancellationTypeEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const OpenAPICancelledOrderStatus::CancellationTypeEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, OpenAPICancelledOrderStatus::CancellationTypeEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void OpenAPICancelledOrderStatus::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("name")); WriteJsonValue(Writer, Name);
	Writer->WriteIdentifierPrefix(TEXT("pending")); WriteJsonValue(Writer, Pending);
	Writer->WriteIdentifierPrefix(TEXT("cancellation_type")); WriteJsonValue(Writer, CancellationType);
	Writer->WriteObjectEnd();
}

bool OpenAPICancelledOrderStatus::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("name"), Name);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("pending"), Pending);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("cancellation_type"), CancellationType);

	return ParseSuccess;
}

}