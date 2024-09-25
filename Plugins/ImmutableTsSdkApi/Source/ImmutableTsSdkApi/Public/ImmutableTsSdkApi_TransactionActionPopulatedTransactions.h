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

#pragma once

#include "ImmutableTsSdkApi_BaseModel.h"
#include "ImmutableTsSdkApi_TransactionActionPopulatedTransactionsAccessListInner.h"

namespace ImmutableTsSdkApi
{

/*
 * ImmutableTsSdkApi_TransactionActionPopulatedTransactions
 *
 * 
 */
class IMMUTABLETSSDKAPI_API ImmutableTsSdkApi_TransactionActionPopulatedTransactions : public Model
{
public:
    virtual ~ImmutableTsSdkApi_TransactionActionPopulatedTransactions() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	TOptional<FString> To;
	TOptional<FString> From;
	TOptional<double> Nonce;
	TOptional<FString> GasLimit;
	TOptional<FString> GasPrice;
	TOptional<FString> Data;
	TOptional<FString> Value;
	TOptional<double> ChainId;
	TOptional<double> Type;
	TOptional<TArray<ImmutableTsSdkApi_TransactionActionPopulatedTransactionsAccessListInner>> AccessList;
	TOptional<FString> MaxFeePerGas;
	TOptional<FString> MaxPriorityFeePerGas;
	TOptional<TMap<FString, TSharedPtr<FJsonValue>>> CustomData;
	TOptional<bool> CcipReadEnabled;
};

}
