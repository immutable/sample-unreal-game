// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "ImtblMintTokenAsyncAction.generated.h"


/**
 * 
 */
UCLASS()
class UImtblMintTokenAsyncAction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FImmutableMintTokenOutputPin, FString, ErrorMessage);
    
public:
    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Game")
    static UImtblMintTokenAsyncAction* MintToken(UObject* WorldContextObject);

    virtual void Activate() override;

private:
    
    UPROPERTY(BlueprintAssignable)
    FImmutableMintTokenOutputPin Success;
    UPROPERTY(BlueprintAssignable)
    FImmutableMintTokenOutputPin Failed;
};
