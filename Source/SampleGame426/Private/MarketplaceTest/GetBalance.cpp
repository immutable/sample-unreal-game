


#include "MarketplaceTest/GetBalance.h"

#include "JsonUtilities.h"
#include "LogSampleGame.h"
#include "MarketplaceTest/GetBalanceResponse.h"
#include "MarketplaceTest/HttpClient.h"

void UGetBalance::GetTokenBalance(const FString& Address)
{
	UE_LOG(LogSampleGame, Display, TEXT("Get Balance for Address: %s"), *Address);

	UHttpClient* HttpClient = NewObject<UHttpClient>();

	const FString ContractAddress = "0x328766302e7617d0de5901f8da139dca49f3ec75";

	const FString Uri = FString::Printf(TEXT("https://api.dev.immutable.com/v1/ts-sdk/token/balance?wallet_address=%s&contract_address=%s"), *Address, *ContractAddress);

	// Make HTTP request
	HttpClient->MakeHttpRequest(Uri, [this](FString ResponseString)
	{
		UE_LOG(LogSampleGame, Display, TEXT("HttpClient->MakeHttpRequest()"));
		FGetBalanceResponse GetBalanceResponse;
		FJsonObjectConverter::JsonObjectStringToUStruct<FGetBalanceResponse>(ResponseString, &GetBalanceResponse, 0, 0);

		const float Quantity = GetBalanceResponse.Quantity;

		UE_LOG(LogSampleGame, Display, TEXT("Balance Quantity: %f"), Quantity);
		
		OnBalanceUpdated.Broadcast(Quantity);
	});
}
