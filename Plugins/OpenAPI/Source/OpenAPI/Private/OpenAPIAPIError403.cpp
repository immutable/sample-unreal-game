/**
 * Indexer Search API
 * This API implements endpoints to power data driven marketplace and game experiences
 *
 * OpenAPI spec version: 1.0
 * Contact: helpmebuild@immutable.com
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * https://github.com/OpenAPITools/openapi-generator
 * Do not edit the class manually.
 */

#include "OpenAPIAPIError403.h"

#include "OpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace OpenAPI
{

inline FString ToString(const OpenAPIAPIError403::CodeEnum& Value)
{
	switch (Value)
	{
	case OpenAPIAPIError403::CodeEnum::AuthenticationError:
		return TEXT("AUTHENTICATION_ERROR");
	}

	UE_LOG(LogOpenAPI, Error, TEXT("Invalid OpenAPIAPIError403::CodeEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString OpenAPIAPIError403::EnumToString(const OpenAPIAPIError403::CodeEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, OpenAPIAPIError403::CodeEnum& Value)
{
	static TMap<FString, OpenAPIAPIError403::CodeEnum> StringToEnum = { 
		{ TEXT("AUTHENTICATION_ERROR"), OpenAPIAPIError403::CodeEnum::AuthenticationError }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool OpenAPIAPIError403::EnumFromString(const FString& EnumAsString, OpenAPIAPIError403::CodeEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const OpenAPIAPIError403::CodeEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, OpenAPIAPIError403::CodeEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void OpenAPIAPIError403::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("message")); WriteJsonValue(Writer, Message);
	Writer->WriteIdentifierPrefix(TEXT("link")); WriteJsonValue(Writer, Link);
	Writer->WriteIdentifierPrefix(TEXT("trace_id")); WriteJsonValue(Writer, TraceId);
	Writer->WriteIdentifierPrefix(TEXT("code")); WriteJsonValue(Writer, Code);
	if (Details.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("details")); WriteJsonValue(Writer, Details.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool OpenAPIAPIError403::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("message"), Message);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("link"), Link);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("trace_id"), TraceId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("code"), Code);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("details"), Details);

	return ParseSuccess;
}

}
