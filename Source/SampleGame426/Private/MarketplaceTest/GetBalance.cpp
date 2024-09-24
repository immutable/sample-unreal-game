


#include "MarketplaceTest/GetBalance.h"

#include "JsonUtilities.h"
#include "LogSampleGame.h"
#include "MarketplaceTest/GetBalanceResponse.h"
#include "MarketplaceTest/HttpClient.h"

void UGetBalance::GetTokenBalance(const FString& Address)
{
	UE_LOG(LogSampleGame, Display, TEXT("Get Balance for Address: %s"), *Address);

	UHttpClient* HttpClient = NewObject<UHttpClient>();

	const FString Uri = FString::Printf(TEXT("http://localhost:6060/balance?address=%s"), *Address);

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
