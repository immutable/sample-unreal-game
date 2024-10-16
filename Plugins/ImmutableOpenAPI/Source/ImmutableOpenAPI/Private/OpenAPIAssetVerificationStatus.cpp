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

#include "OpenAPIAssetVerificationStatus.h"

#include "ImmutableOpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableOpenAPI
{

inline FString ToString(const OpenAPIAssetVerificationStatus::Values& Value)
{
	switch (Value)
	{
	case OpenAPIAssetVerificationStatus::Values::Verified:
		return TEXT("verified");
	case OpenAPIAssetVerificationStatus::Values::Unverified:
		return TEXT("unverified");
	case OpenAPIAssetVerificationStatus::Values::Spam:
		return TEXT("spam");
	case OpenAPIAssetVerificationStatus::Values::Inactive:
		return TEXT("inactive");
	}

	UE_LOG(LogImmutableOpenAPI, Error, TEXT("Invalid OpenAPIAssetVerificationStatus::Values Value (%d)"), (int)Value);
	return TEXT("");
}

FString OpenAPIAssetVerificationStatus::EnumToString(const OpenAPIAssetVerificationStatus::Values& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, OpenAPIAssetVerificationStatus::Values& Value)
{
	static TMap<FString, OpenAPIAssetVerificationStatus::Values> StringToEnum = { 
		{ TEXT("verified"), OpenAPIAssetVerificationStatus::Values::Verified },
		{ TEXT("unverified"), OpenAPIAssetVerificationStatus::Values::Unverified },
		{ TEXT("spam"), OpenAPIAssetVerificationStatus::Values::Spam },
		{ TEXT("inactive"), OpenAPIAssetVerificationStatus::Values::Inactive }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool OpenAPIAssetVerificationStatus::EnumFromString(const FString& EnumAsString, OpenAPIAssetVerificationStatus::Values& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const OpenAPIAssetVerificationStatus::Values& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, OpenAPIAssetVerificationStatus::Values& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void OpenAPIAssetVerificationStatus::WriteJson(JsonWriter& Writer) const
{
	WriteJsonValue(Writer, Value);
}

bool OpenAPIAssetVerificationStatus::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Value);
}

}