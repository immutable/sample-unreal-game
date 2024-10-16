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

#include "OpenAPINFTContractType.h"

#include "ImmutableOpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableOpenAPI
{

inline FString ToString(const OpenAPINFTContractType::Values& Value)
{
	switch (Value)
	{
	case OpenAPINFTContractType::Values::ERC721:
		return TEXT("ERC721");
	case OpenAPINFTContractType::Values::ERC1155:
		return TEXT("ERC1155");
	}

	UE_LOG(LogImmutableOpenAPI, Error, TEXT("Invalid OpenAPINFTContractType::Values Value (%d)"), (int)Value);
	return TEXT("");
}

FString OpenAPINFTContractType::EnumToString(const OpenAPINFTContractType::Values& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, OpenAPINFTContractType::Values& Value)
{
	static TMap<FString, OpenAPINFTContractType::Values> StringToEnum = { 
		{ TEXT("ERC721"), OpenAPINFTContractType::Values::ERC721 },
		{ TEXT("ERC1155"), OpenAPINFTContractType::Values::ERC1155 }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool OpenAPINFTContractType::EnumFromString(const FString& EnumAsString, OpenAPINFTContractType::Values& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const OpenAPINFTContractType::Values& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, OpenAPINFTContractType::Values& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void OpenAPINFTContractType::WriteJson(JsonWriter& Writer) const
{
	WriteJsonValue(Writer, Value);
}

bool OpenAPINFTContractType::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Value);
}

}