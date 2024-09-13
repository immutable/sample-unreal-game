// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

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
	UFUNCTION(BlueprintCallable, Category="Sample Game")
	void GetTokenBalance(const FString& Address);

	UPROPERTY(BlueprintAssignable)
	FOnBalanceUpdated OnBalanceUpdated;
};
