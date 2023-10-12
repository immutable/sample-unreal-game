// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Immutable/Actions/ImtblBlueprintAsyncAction.h"
#include "endlessrun/API/ImmutableApi.h"
#include "ImtblMintSkinAsyncAction.generated.h"


/**
 * 
 */
UCLASS()
class UImtblMintSkinAsyncAction : public UImtblBlueprintAsyncAction
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FImmutableMintSkinOutputPin, FString, ErrorMessage);
    
    
public:
    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Game")
    static UImtblMintSkinAsyncAction* MintSkin(UObject* WorldContextObject, const FString& WalletAddress);

    virtual void Activate() override;

private:

    void DoMintSkin(TWeakObjectPtr<class UImtblJSConnector> JSConnector);
    void OnMintSkinResponse(const FImtblAPIResponse& Result);

    FString WalletAddress;
    
    UPROPERTY(BlueprintAssignable)
    FImmutableMintSkinOutputPin Success;
    UPROPERTY(BlueprintAssignable)
    FImmutableMintSkinOutputPin Failed;
};
