// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Immutable/Actions/ImtblBlueprintAsyncAction.h"
#include "endlessrun/API/ImmutableApi.h"
#include "ImtblGetSkinAsyncAction.generated.h"


/**
 * 
 */
UCLASS()
class UImtblGetSkinAsyncAction : public UImtblBlueprintAsyncAction
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FImmutableMintTokenOutputPin, FString, ErrorMessage);
    
    
public:
    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Game")
    static UImtblGetSkinAsyncAction* GetSkin(UObject* WorldContextObject,
        const FString& WalletAddress, const FString& TokenAddress);

    virtual void Activate() override;

private:

    void DoGetSkin(TWeakObjectPtr<class UImtblJSConnector> JSConnector);
    void OnGetSkinResponse(const FImtblAPIResponse& Result);

    FString WalletAddress;
    FString TokenAddress;
    
    UPROPERTY(BlueprintAssignable)
    FImmutableMintTokenOutputPin Success;
    UPROPERTY(BlueprintAssignable)
    FImmutableMintTokenOutputPin Failed;
};
