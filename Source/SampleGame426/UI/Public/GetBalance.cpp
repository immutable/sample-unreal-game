// Fill out your copyright notice in the Description page of Project Settings.


#include "GetBalance.h"
#include "HttpClient.h"
#include "GetBalanceResponse.h"
#include "JsonUtilities.h" // Include JsonUtilities for JSON convers

void UGetBalance::GetTokenBalance(const FString& Address)
{
    // Create an instance of HttpClient
    UHttpClient* HttpClient = NewObject<UHttpClient>();

    // Specify the URL and method for the HTTP request
    FString Url = FString::Printf(TEXT("http://localhost:6060/balance?address=%s"), *Address);
    FString Method = "GET";

    // Make the HTTP request
    HttpClient->MakeHttpRequest(Url, Method, [this](FString ResponseString){
        FGetBalanceResponse GetBalanceResponse;
        FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &GetBalanceResponse, 0, 0);

        float Quantity = GetBalanceResponse.Quantity;

        OnBalanceUpdated.Broadcast(Quantity);
    });

    UE_LOG(LogTemp, Log, TEXT("GetTokenBalance Response: %s"), *HttpClient->ResponseContent);
}
