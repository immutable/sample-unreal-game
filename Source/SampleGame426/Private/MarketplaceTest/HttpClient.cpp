#include "MarketplaceTest/HttpClient.h"

#include "HttpModule.h"
#include "LogSampleGame.h"
#include "Interfaces/IHttpResponse.h"
#include "Interfaces/IHttpRequest.h"

void UHttpClient::MakeHttpRequest(const FString& Uri, const FString& Method, TFunction<void(const FString&)> Callback)
{
	UE_LOG(LogSampleGame, Log, TEXT("Make HTTP Request: %s"), *Uri);
	
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> const HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->SetURL(Uri);
	HttpRequest->SetVerb(Method);
	HttpRequest->SetContentAsString("application/json");

	HttpRequest->OnProcessRequestComplete().BindLambda([this, Callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{
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
}
