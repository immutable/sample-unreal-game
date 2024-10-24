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

#include "OpenAPIPrepareListingRequestBuy.h"

#include "ImmutableTsSdkApiModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableTsSdkApi
{

inline FString ToString(const OpenAPIPrepareListingRequestBuy::TypeEnum& Value)
{
	switch (Value)
	{
	case OpenAPIPrepareListingRequestBuy::TypeEnum::ERC20:
		return TEXT("ERC20");
	case OpenAPIPrepareListingRequestBuy::TypeEnum::Native:
		return TEXT("NATIVE");
	}

	UE_LOG(LogImmutableTsSdkApi, Error, TEXT("Invalid OpenAPIPrepareListingRequestBuy::TypeEnum Value (%d)"), (int)Value);
	return TEXT("");
}

FString OpenAPIPrepareListingRequestBuy::EnumToString(const OpenAPIPrepareListingRequestBuy::TypeEnum& EnumValue)
{
	return ToString(EnumValue);
}

inline bool FromString(const FString& EnumAsString, OpenAPIPrepareListingRequestBuy::TypeEnum& Value)
{
	static TMap<FString, OpenAPIPrepareListingRequestBuy::TypeEnum> StringToEnum = { 
		{ TEXT("ERC20"), OpenAPIPrepareListingRequestBuy::TypeEnum::ERC20 },
		{ TEXT("NATIVE"), OpenAPIPrepareListingRequestBuy::TypeEnum::Native }, };

	const auto Found = StringToEnum.Find(EnumAsString);
	if(Found)
		Value = *Found;

	return Found != nullptr;
}

bool OpenAPIPrepareListingRequestBuy::EnumFromString(const FString& EnumAsString, OpenAPIPrepareListingRequestBuy::TypeEnum& EnumValue)
{
	return FromString(EnumAsString, EnumValue);
}

inline void WriteJsonValue(JsonWriter& Writer, const OpenAPIPrepareListingRequestBuy::TypeEnum& Value)
{
	WriteJsonValue(Writer, ToString(Value));
}

inline bool TryGetJsonValue(const TSharedPtr<FJsonValue>& JsonValue, OpenAPIPrepareListingRequestBuy::TypeEnum& Value)
{
	FString TmpValue;
	if (JsonValue->TryGetString(TmpValue))
	{
		if(FromString(TmpValue, Value))
			return true;
	}
	return false;
}

void OpenAPIPrepareListingRequestBuy::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("amount")); WriteJsonValue(Writer, Amount);
	Writer->WriteIdentifierPrefix(TEXT("contractAddress")); WriteJsonValue(Writer, ContractAddress);
	Writer->WriteIdentifierPrefix(TEXT("type")); WriteJsonValue(Writer, Type);
	Writer->WriteObjectEnd();
}

bool OpenAPIPrepareListingRequestBuy::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("amount"), Amount);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("contractAddress"), ContractAddress);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("type"), Type);

	return ParseSuccess;
}

}