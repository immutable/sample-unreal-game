// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "HttpClient.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SAMPLEGAME426_API UHttpClient : public UObject
{
	GENERATED_BODY()

public:
	UHttpClient();
	~UHttpClient();

	UFUNCTION(BlueprintCallable, Category="HTTP")
	void MakeHttpRequest(const FString& Url, const FString& Method);

protected:
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
