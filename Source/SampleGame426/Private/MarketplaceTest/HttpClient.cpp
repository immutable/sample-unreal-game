#include "MarketplaceTest/HttpClient.h"

#include "HttpModule.h"
#include "LogSampleGame.h"
#include "Interfaces/IHttpResponse.h"
#include "Interfaces/IHttpRequest.h"

void UHttpClient::MakeHttpRequest(const FString& Uri, TFunction<void(const FString&)> Callback)
{
	UE_LOG(LogSampleGame, Log, TEXT("Make HTTP Request: %s"), *Uri);
	
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> const HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->SetURL(Uri);
	HttpRequest->SetVerb("GET");
	HttpRequest->SetHeader("Content-Type", TEXT("application/json"));

	HttpRequest->OnProcessRequestComplete().BindLambda(
		[this, Callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			UE_LOG(LogSampleGame, Log, TEXT("OnProcessRequestComplete"));
			if (bWasSuccessful && Response.IsValid())
			{
				const FString ResponseString = Response->GetContentAsString();
				UE_LOG(LogSampleGame, Log, TEXT("HTTP Response is: %s"), *ResponseString);
				Callback(ResponseString);
			}
			else
			{
				const FString RequestUrl = Request->GetURL();
				UE_LOG(LogSampleGame, Error, TEXT("HTTP Request could not be processed: %s"), *RequestUrl);
			}
		});

	HttpRequest->ProcessRequest();
}

void UHttpClient::MakeHttpPostRequest(const FString& Uri, const FString& Body, TFunction<void(const FString&)> Callback)
{
	UE_LOG(LogSampleGame, Log, TEXT("Make HTTP POST Request: %s"), *Uri);
	
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> const HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->SetURL(Uri);
	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader("Content-Type", TEXT("application/json"));
	HttpRequest->SetContentAsString(Body);
	
	HttpRequest->OnProcessRequestComplete().BindLambda(
		[this, Callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		UE_LOG(LogSampleGame, Log, TEXT("OnProcessRequestComplete"));
		if (bWasSuccessful && Response.IsValid())
		{
			const FString ResponseString = Response->GetContentAsString();
			UE_LOG(LogSampleGame, Log, TEXT("HTTP POST Response is: %s"), *ResponseString);
			Callback(ResponseString);
		}
		else
		{
			const FString RequestUrl = Request->GetURL();
			UE_LOG(LogSampleGame, Error, TEXT("HTTP POST Request could not be processed: %s"), *RequestUrl);
		}
	});

	HttpRequest->ProcessRequest();
}