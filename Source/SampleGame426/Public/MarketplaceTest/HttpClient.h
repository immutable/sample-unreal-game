#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HttpClient.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SAMPLEGAME426_API UHttpClient : public UObject
{
	GENERATED_BODY()

public:
	FString ResponseContent;

	/**
	 * MakeHttpRequest
	 * @param Uri Request URI
	 * @param Method Request method
	 * @param Callback Request completed callback delegate
	 */
	void MakeHttpRequest(const FString& Uri, TFunction<void(const FString&)> Callback);

	/**
	 * MakeHttpPostRequest
	 * @param Uri Request URI
	 * @param Method Request method
	 * @param Body JSON string for the POST request body
	 * @param Callback Request completed callback delegate
	 */
	void MakeHttpPostRequest(const FString& Uri, const FString& Body, TFunction<void(const FString&)> Callback);
};
