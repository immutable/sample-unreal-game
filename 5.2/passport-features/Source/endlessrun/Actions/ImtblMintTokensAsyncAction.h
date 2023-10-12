// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Immutable/Actions/ImtblBlueprintAsyncAction.h"
#include "endlessrun/API/ImmutableApi.h"
#include "ImtblMintTokensAsyncAction.generated.h"


/**
 * 
 */
UCLASS()
class UImtblMintTokensAsyncAction : public UImtblBlueprintAsyncAction
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FImmutableMintTokenOutputPin, FString, Message);
    
    
public:
    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Game")
    static UImtblMintTokensAsyncAction* MintTokens(UObject* WorldContextObject, const FString& WalletAddress,
        const int Quantity);

    virtual void Activate() override;

private:

    void DoMintTokens();
    void OnMintTokensResponse(FHttpRequestPtr pRequest, FHttpResponsePtr pResponse, bool connectedSuccessfully);

    FString WalletAddress;
    int Quantity;
    FHttpModule& HttpModule = FHttpModule::Get();
    FString MintServerBaseUrl = "http://localhost:6060";
    FString ImxApiBaseUrl = "https://api.sandbox.x.immutable.com";
    
    UPROPERTY(BlueprintAssignable)
    FImmutableMintTokenOutputPin Success;
    UPROPERTY(BlueprintAssignable)
    FImmutableMintTokenOutputPin Failed;
};
