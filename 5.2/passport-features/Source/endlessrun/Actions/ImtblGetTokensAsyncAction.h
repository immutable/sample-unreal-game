// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Immutable/Actions/ImtblBlueprintAsyncAction.h"
#include "endlessrun/API/ImmutableApi.h"
#include "ImtblGetTokensAsyncAction.generated.h"


/**
 * 
 */
UCLASS()
class UImtblGetTokensAsyncAction : public UImtblBlueprintAsyncAction
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FImmutableMintTokenOutputPin, FString, ErrorMessage);
    
    
public:
    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Game")
    static UImtblGetTokensAsyncAction* GetTokens(UObject* WorldContextObject,
        const FString& WalletAddress, const FString& TokenAddress, const int Quantity);

    virtual void Activate() override;

private:

    void DoGetTokens(TWeakObjectPtr<class UImtblJSConnector> JSConnector);
    void OnGetTokensResponse(const FImtblAPIResponse& Result);

    FString WalletAddress;
    FString TokenAddress;
    int Quantity;
    
    UPROPERTY(BlueprintAssignable)
    FImmutableMintTokenOutputPin Success;
    UPROPERTY(BlueprintAssignable)
    FImmutableMintTokenOutputPin Failed;
};
