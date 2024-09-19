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

	void MakeHttpRequest(const FString& Uri, const FString& Method, TFunction<void(const FString&)> Callback);
};
