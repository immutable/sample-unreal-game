// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpClient.h"
#include "Http.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"

UHttpClient::UHttpClient()
{
}

UHttpClient::~UHttpClient()
{
}

void UHttpClient::MakeHttpRequest(const FString& Url, const FString& Method, TFunction<void(FString)> CallbackFunction)
{
	UE_LOG(LogTemp, Log, TEXT("Make HTTP Request: %s"), *Url)

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->SetURL(Url);
	HttpRequest->SetVerb(Method);

    HttpRequest->OnProcessRequestComplete().BindLambda([this, CallbackFunction](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
        if (bWasSuccessful && Response.IsValid())
        {
            FString ResponseString = Response->GetContentAsString();
            UE_LOG(LogTemp, Log, TEXT("HTTP Request Completed: %s"), *ResponseString);
            // Handle the successful response
            CallbackFunction(ResponseString);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("HTTP Request failed"));
        }
    });

	HttpRequest->ProcessRequest();

}

// Old method for binding on HttpRequest->OnProcessRequestComplete()
// void UHttpClient::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
// {
//     if (bWasSuccessful && Response.IsValid())
//     {
//         // Handle the successful response
//         ResponseContent = Response->GetContentAsString();
//         UE_LOG(LogTemp, Log, TEXT("Response: %s"), *ResponseContent);
//     }
//     else
//     {
//         // Handle the error
//         UE_LOG(LogTemp, Error, TEXT("HTTP Request failed"));
//     }
// }
