// Fill out your copyright notice in the Description page of Project Settings.


#include "MarketplaceTest/MarketplaceClient.h"

#include "JsonUtilities.h"
#include "LogSampleGame.h"
#include "MarketplaceTest/HttpClient.h"
#include "MarketplaceTest/MarketplaceClientTypes.h"

void UMarketplaceClient::GetUnsignedFulfillOrderTransactions(const FString& ListingId, const FString& TakerAddress)
{
	UE_LOG(LogSampleGame, Display, TEXT("GetUnsignedFulfillOrderTransactions: %s"), *ListingId);

	UHttpClient* HttpClient = NewObject<UHttpClient>();

	const FString Uri = FString::Printf(TEXT("http://localhost:8080/v1/ts-sdk/orderbook/fulfillOrder"));
	const FString Body = FString::Printf(
		TEXT("{\"listingId\": \"%s\",\"takerAddress\": \"%s\",\"takerFees\": []}"), *ListingId, *TakerAddress);

	HttpClient->MakeHttpPostRequest(Uri, Body, [this](FString ResponseString)
	{
		UE_LOG(LogSampleGame, Display, TEXT("MakeHttpPostRequest Callback"));

		FFulfillOrderResponse FulfillOrderResponse;
		FJsonObjectConverter::JsonObjectStringToUStruct<FFulfillOrderResponse>(ResponseString, &FulfillOrderResponse, 0, 0);
		
		for (int32 i = 0; i < FulfillOrderResponse.Actions.Num(); i++)
		{
			UE_LOG(LogSampleGame, Display, TEXT("PopulatedTransactions: %s"),
			       *FulfillOrderResponse.Actions[i].ToString());
		}
		
		OnFulfillOrderReturned.Broadcast(FulfillOrderResponse.Actions);
	});
}
