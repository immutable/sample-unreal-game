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

#include "OpenAPIAPIError401AllOf.h"

#include "ImmutableOpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableOpenAPI
{

inline FString ToString(const OpenAPIAPIError401AllOf::CodeEnum& Value)
{
	switch (Value)
	{
	case OpenAPIAPIError401AllOf::CodeEnum::UnauthorisedRequest:
		return TEXT("UNAUTHORISED_REQUEST");
	}

	UE_LOG(LogImmutableOpenAPI, Error, TEXT("Invalid OpenAPIAPIError401AllOf::CodeEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString OpenAPIAPIError401AllOf::EnumToString(const OpenAPIAPIError401AllOf::CodeEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, OpenAPIAPIError401AllOf::CodeEnum& Value)
{
	static TMap<FString, OpenAPIAPIError401AllOf::CodeEnum> StringToEnum = { 
		{ TEXT("UNAUTHORISED_REQUEST"), OpenAPIAPIError401AllOf::CodeEnum::UnauthorisedRequest }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool OpenAPIAPIError401AllOf::EnumFromString(const FString& EnumAsString, OpenAPIAPIError401AllOf::CodeEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const OpenAPIAPIError401AllOf::CodeEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, OpenAPIAPIError401AllOf::CodeEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void OpenAPIAPIError401AllOf::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("code")); WriteJsonValue(Writer, Code);
	if (Details.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("details")); WriteJsonValue(Writer, Details.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool OpenAPIAPIError401AllOf::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("code"), Code);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("details"), Details);

	return ParseSuccess;
}

}