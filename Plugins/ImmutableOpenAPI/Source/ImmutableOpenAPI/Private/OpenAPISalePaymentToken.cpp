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

#include "OpenAPISalePaymentToken.h"

#include "ImmutableOpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableOpenAPI
{

void OpenAPISalePaymentToken::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	Writer->WriteIdentifierPrefix(TEXT("contract_type")); WriteJsonValue(Writer, ContractType);
	Writer->WriteIdentifierPrefix(TEXT("contract_address")); WriteJsonValue(Writer, ContractAddress);
	Writer->WriteIdentifierPrefix(TEXT("symbol")); WriteJsonValue(Writer, Symbol);
	Writer->WriteObjectEnd();
}

bool OpenAPISalePaymentToken::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("contract_type"), ContractType);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("contract_address"), ContractAddress);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("symbol"), Symbol);

	return ParseSuccess;
}

}
