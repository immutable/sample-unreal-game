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

#include "OpenAPIProtocolData.h"

#include "ImmutableOpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableOpenAPI
{

inline FString ToString(const OpenAPIProtocolData::OrderTypeEnum& Value)
{
	switch (Value)
	{
	case OpenAPIProtocolData::OrderTypeEnum::FullRestricted:
		return TEXT("FULL_RESTRICTED");
	case OpenAPIProtocolData::OrderTypeEnum::PartialRestricted:
		return TEXT("PARTIAL_RESTRICTED");
	}

	UE_LOG(LogImmutableOpenAPI, Error, TEXT("Invalid OpenAPIProtocolData::OrderTypeEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString OpenAPIProtocolData::EnumToString(const OpenAPIProtocolData::OrderTypeEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, OpenAPIProtocolData::OrderTypeEnum& Value)
{
	static TMap<FString, OpenAPIProtocolData::OrderTypeEnum> StringToEnum = { 
		{ TEXT("FULL_RESTRICTED"), OpenAPIProtocolData::OrderTypeEnum::FullRestricted },
		{ TEXT("PARTIAL_RESTRICTED"), OpenAPIProtocolData::OrderTypeEnum::PartialRestricted }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool OpenAPIProtocolData::EnumFromString(const FString& EnumAsString, OpenAPIProtocolData::OrderTypeEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const OpenAPIProtocolData::OrderTypeEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, OpenAPIProtocolData::OrderTypeEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void OpenAPIProtocolData::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("order_type")); WriteJsonValue(Writer, OrderType);
	Writer->WriteIdentifierPrefix(TEXT("counter")); WriteJsonValue(Writer, Counter);
	Writer->WriteIdentifierPrefix(TEXT("zone_address")); WriteJsonValue(Writer, ZoneAddress);
	Writer->WriteIdentifierPrefix(TEXT("seaport_address")); WriteJsonValue(Writer, SeaportAddress);
	Writer->WriteIdentifierPrefix(TEXT("seaport_version")); WriteJsonValue(Writer, SeaportVersion);
	Writer->WriteObjectEnd();
}

bool OpenAPIProtocolData::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("order_type"), OrderType);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("counter"), Counter);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("zone_address"), ZoneAddress);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("seaport_address"), SeaportAddress);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("seaport_version"), SeaportVersion);

	return ParseSuccess;
}

}
