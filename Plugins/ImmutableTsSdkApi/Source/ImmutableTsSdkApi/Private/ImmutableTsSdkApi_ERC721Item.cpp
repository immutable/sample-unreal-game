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

#include "ImmutableTsSdkApi_ERC721Item.h"

#include "ImmutableTsSdkApiModule.h"
#include "ImmutableTsSdkApi_Helpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableTsSdkApi
{

inline FString ToString(const ImmutableTsSdkApi_ERC721Item::TypeEnum& Value)
{
	switch (Value)
	{
	case ImmutableTsSdkApi_ERC721Item::TypeEnum::ERC721:
		return TEXT("ERC721");
	}

	UE_LOG(LogImmutableTsSdkApi, Error, TEXT("Invalid ImmutableTsSdkApi_ERC721Item::TypeEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString ImmutableTsSdkApi_ERC721Item::EnumToString(const ImmutableTsSdkApi_ERC721Item::TypeEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, ImmutableTsSdkApi_ERC721Item::TypeEnum& Value)
{
	static TMap<FString, ImmutableTsSdkApi_ERC721Item::TypeEnum> StringToEnum = { 
		{ TEXT("ERC721"), ImmutableTsSdkApi_ERC721Item::TypeEnum::ERC721 }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool ImmutableTsSdkApi_ERC721Item::EnumFromString(const FString& EnumAsString, ImmutableTsSdkApi_ERC721Item::TypeEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const ImmutableTsSdkApi_ERC721Item::TypeEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, ImmutableTsSdkApi_ERC721Item::TypeEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void ImmutableTsSdkApi_ERC721Item::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("contractAddress")); WriteJsonValue(Writer, ContractAddress);
	Writer->WriteIdentifierPrefix(TEXT("tokenId")); WriteJsonValue(Writer, TokenId);
	Writer->WriteIdentifierPrefix(TEXT("type")); WriteJsonValue(Writer, Type);
	Writer->WriteObjectEnd();
}

bool ImmutableTsSdkApi_ERC721Item::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("contractAddress"), ContractAddress);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("tokenId"), TokenId);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("type"), Type);

	return ParseSuccess;
}

}