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

#include "OpenAPITransactionPurpose.h"

#include "ImmutableTsSdkApiModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableTsSdkApi
{

inline FString ToString(const OpenAPITransactionPurpose::Values& Value)
{
	switch (Value)
	{
	case OpenAPITransactionPurpose::Values::Approval:
		return TEXT("APPROVAL");
	case OpenAPITransactionPurpose::Values::FulfillOrder:
		return TEXT("FULFILL_ORDER");
	case OpenAPITransactionPurpose::Values::Cancel:
		return TEXT("CANCEL");
	}

	UE_LOG(LogImmutableTsSdkApi, Error, TEXT("Invalid OpenAPITransactionPurpose::Values Value (%d)"), (int)Value);
	return TEXT("");
}

FString OpenAPITransactionPurpose::EnumToString(const OpenAPITransactionPurpose::Values& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, OpenAPITransactionPurpose::Values& Value)
{
	static TMap<FString, OpenAPITransactionPurpose::Values> StringToEnum = { 
		{ TEXT("APPROVAL"), OpenAPITransactionPurpose::Values::Approval },
		{ TEXT("FULFILL_ORDER"), OpenAPITransactionPurpose::Values::FulfillOrder },
		{ TEXT("CANCEL"), OpenAPITransactionPurpose::Values::Cancel }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool OpenAPITransactionPurpose::EnumFromString(const FString& EnumAsString, OpenAPITransactionPurpose::Values& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const OpenAPITransactionPurpose::Values& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, OpenAPITransactionPurpose::Values& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void OpenAPITransactionPurpose::WriteJson(JsonWriter& Writer) const
{
	WriteJsonValue(Writer, Value);
}

bool OpenAPITransactionPurpose::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Value);
}

}
