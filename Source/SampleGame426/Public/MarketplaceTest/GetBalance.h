#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GetBalance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBalanceUpdated, float, Quantity);

/**
 * 
 */
UCLASS(Blueprintable)
class SAMPLEGAME426_API UGetBalance : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "MarketplaceTest")
	void GetTokenBalance(const FString& Address);

	UPROPERTY(BlueprintAssignable, Category = "MarketplaceTest")
	FOnBalanceUpdated OnBalanceUpdated;
};
