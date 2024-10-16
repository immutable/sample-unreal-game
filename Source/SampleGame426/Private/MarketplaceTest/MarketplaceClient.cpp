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

	const FString Uri = FString::Printf(TEXT("https://api.sandbox.immutable.com/v1/ts-sdk/orderbook/fulfillOrder"));
	const FString Body = FString::Printf(
		TEXT("{\"listingId\": \"%s\",\"takerAddress\": \"%s\",\"takerFees\": []}"), *ListingId, *TakerAddress);

	HttpClient->MakeHttpPostRequest(Uri, Body, [this](FString ResponseString)
	{
		UE_LOG(LogSampleGame, Display, TEXT("MakeHttpPostRequest Callback"));

		FFulfillOrderResponse FulfillOrderResponse;
		FJsonObjectConverter::JsonObjectStringToUStruct<FFulfillOrderResponse>(ResponseString, &FulfillOrderResponse,
			0, 0);
		
		for (int32 i = 0; i < FulfillOrderResponse.Actions.Num(); i++)
		{
			UE_LOG(LogSampleGame, Display, TEXT("PopulatedTransactions: %s"),
			       *FulfillOrderResponse.Actions[i].ToString());
		}
		
		OnFulfillOrderReturned.Broadcast(FulfillOrderResponse.Actions);
	});
}

void UMarketplaceClient::PrepareListing(const FString& MakerAddress, const FBuy Buy, const FSell Sell)
{
	// TODO - Change from Warning to Display
	UE_LOG(LogSampleGame, Warning, TEXT("PrepareListing for token ID: %s from contract %s for %s amount (wei)"),
		*Sell.TokenId, *Sell.ContractAddress, *Buy.Amount);

	UHttpClient* HttpClient = NewObject<UHttpClient>();

	const FString Uri = FString::Printf(TEXT("https://api.sandbox.immutable.com/v1/ts-sdk/orderbook/prepareListing"));
	FPrepareListingRequest PrepareListingRequest;

	PrepareListingRequest.MakerAddress = *MakerAddress;
	PrepareListingRequest.Buy = Buy;
	PrepareListingRequest.Sell = Sell;

	FString RequestBodyString;
	
	FJsonObjectConverter::UStructToJsonObjectString<FPrepareListingRequest>(PrepareListingRequest, RequestBodyString);

	// TODO - Change from Warning to Display
	UE_LOG(LogSampleGame, Warning, TEXT("PrepareListing request body %s"), *RequestBodyString);

	HttpClient->MakeHttpPostRequest(Uri, RequestBodyString, [this](FString ResponseString)
	{
		// TODO - Change from Warning to Display
		UE_LOG(LogSampleGame, Warning, TEXT("Prepare Listing Callback: %s"), *ResponseString);

		FPrepareListingResponse PrepareListingResponse;
		FJsonObjectConverter::JsonObjectStringToUStruct<FPrepareListingResponse>(ResponseString, &PrepareListingResponse, 0, 0);

		// TODO - Change from Warning to Display
		UE_LOG(LogSampleGame, Warning, TEXT("Prepare listing order hash: %s"), *PrepareListingResponse.OrderHash);
		for (int32 i = 0; i < PrepareListingResponse.Actions.Num(); i++)
		{
			// TODO - Change from Warning to Display
			UE_LOG(LogSampleGame, Warning, TEXT("PopulatedTransactions: %s"),
				   *PrepareListingResponse.Actions[i].ToString());
		}

		OnPrepareListingReturned.Broadcast(PrepareListingResponse);
	});
}

void UMarketplaceClient::CreateListing(FOrderComponents OrderComponents, const FString& OrderHash, const FString& OrderSignature)
{
	// TODO - Change from Warning to Display
	UE_LOG(LogSampleGame, Warning, TEXT("Create listing"));
	UE_LOG(LogSampleGame, Warning, TEXT("Order hash: %s"), *OrderHash);
	UE_LOG(LogSampleGame, Warning, TEXT("Order signature: %s"), *OrderSignature);

	UHttpClient* HttpClient = NewObject<UHttpClient>();

	const FString Uri = FString::Printf(TEXT("https://api.sandbox.immutable.com/v1/ts-sdk/orderbook/createListing"));

	FCreateListingRequest CreateListingRequest;

	CreateListingRequest.MakerFees = {};
	CreateListingRequest.OrderComponents = OrderComponents;
	CreateListingRequest.OrderHash = *OrderHash;
	CreateListingRequest.OrderSignature = *OrderSignature;

	FString RequestBodyString;
	FJsonObjectConverter::UStructToJsonObjectString<FCreateListingRequest>(CreateListingRequest, RequestBodyString);

	HttpClient->MakeHttpPostRequest(Uri, RequestBodyString, [this](FString ResponseString)
	{
		// TODO - Change from Warning to Display
		UE_LOG(LogSampleGame, Warning, TEXT("Create listing response body %s"), *ResponseString);

		FCreateListingResponse CreateListingResponse;
		FJsonObjectConverter::JsonObjectStringToUStruct<FCreateListingResponse>(ResponseString, &CreateListingResponse, 0, 0);

		// TODO - Change from Warning to Display
		UE_LOG(LogSampleGame, Warning, TEXT("Listing ID: %s"), *CreateListingResponse.Result.Id);
		
		OnCreateListingReturned.Broadcast(CreateListingResponse);
	});
}

void UMarketplaceClient::CancelListing(const FString& ListingId, const FString& AccountAddress)
{
	// TODO - Change from Warning to Display
	UE_LOG(LogSampleGame, Warning, TEXT("Cancel listing"));
	UE_LOG(LogSampleGame, Warning, TEXT("Cancel listing ID: %s"), *ListingId);
	UE_LOG(LogSampleGame, Warning, TEXT("Cancel listing account address: %s"), *AccountAddress);

	UHttpClient* HttpClient = NewObject<UHttpClient>();

	const FString Uri = FString::Printf(TEXT("https://api.sandbox.immutable.com/v1/ts-sdk/orderbook/cancelOrdersOnChain"));
	
	FCancelListingRequest CancelListingRequest;

	CancelListingRequest.OrderIds.Add(ListingId);
	CancelListingRequest.AccountAddress = *AccountAddress;
	
	FString RequestBodyString;
	FJsonObjectConverter::UStructToJsonObjectString<FCancelListingRequest>(CancelListingRequest, RequestBodyString);

	HttpClient->MakeHttpPostRequest(Uri, RequestBodyString, [this](FString ResponseString)
	{
		// TODO - Change from Warning to Display
		UE_LOG(LogSampleGame, Warning, TEXT("Cancel listing response body %s"), *ResponseString);

		FCancelListingResponse CancelListingResponse;
		FJsonObjectConverter::JsonObjectStringToUStruct<FCancelListingResponse>(ResponseString, &CancelListingResponse, 0, 0);
		
		// TODO - Change from Warning to Display
		UE_LOG(LogSampleGame, Warning, TEXT("Cancel listing transaction to: %s"), *CancelListingResponse.CancellationAction.PopulatedTransactions.To);
		UE_LOG(LogSampleGame, Warning, TEXT("Cancel listing transaction data: %s"), *CancelListingResponse.CancellationAction.PopulatedTransactions.Data);
				
		OnCancelListingReturned.Broadcast(CancelListingResponse);
	});
}
