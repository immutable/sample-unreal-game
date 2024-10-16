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

#include "OpenAPIFailedOrderCancellation.h"

#include "ImmutableOpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableOpenAPI
{

inline FString ToString(const OpenAPIFailedOrderCancellation::ReasonCodeEnum& Value)
{
	switch (Value)
	{
	case OpenAPIFailedOrderCancellation::ReasonCodeEnum::Filled:
		return TEXT("FILLED");
	}

	UE_LOG(LogImmutableOpenAPI, Error, TEXT("Invalid OpenAPIFailedOrderCancellation::ReasonCodeEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString OpenAPIFailedOrderCancellation::EnumToString(const OpenAPIFailedOrderCancellation::ReasonCodeEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, OpenAPIFailedOrderCancellation::ReasonCodeEnum& Value)
{
	static TMap<FString, OpenAPIFailedOrderCancellation::ReasonCodeEnum> StringToEnum = { 
		{ TEXT("FILLED"), OpenAPIFailedOrderCancellation::ReasonCodeEnum::Filled }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool OpenAPIFailedOrderCancellation::EnumFromString(const FString& EnumAsString, OpenAPIFailedOrderCancellation::ReasonCodeEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const OpenAPIFailedOrderCancellation::ReasonCodeEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, OpenAPIFailedOrderCancellation::ReasonCodeEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void OpenAPIFailedOrderCancellation::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("order")); WriteJsonValue(Writer, Order);
	Writer->WriteIdentifierPrefix(TEXT("reason_code")); WriteJsonValue(Writer, ReasonCode);
	Writer->WriteObjectEnd();
}

bool OpenAPIFailedOrderCancellation::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("order"), Order);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("reason_code"), ReasonCode);

	return ParseSuccess;
}

}