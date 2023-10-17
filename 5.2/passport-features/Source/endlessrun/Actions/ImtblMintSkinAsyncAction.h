// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "CoreMinimal.h"
#include "Immutable/Actions/ImtblBlueprintAsyncAction.h"
#include "ImtblMintSkinAsyncAction.generated.h"


/**
 * 
 */
UCLASS()
class UImtblMintSkinAsyncAction : public UImtblBlueprintAsyncAction
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FImmutableMintSkinOutputPin, const FString, ErrorMessage);
    
public:
    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Game")
    static UImtblMintSkinAsyncAction* MintSkin(UObject* WorldContextObject, const FString& WalletAddress);

    virtual void Activate() override;

private:
    void DoMintSkin(TWeakObjectPtr<class UImtblJSConnector> JSConnector);
    void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

    FString WalletAddress;

    FHttpModule& HttpModule = FHttpModule::Get();
    FString MintServerBaseUrl = "http://localhost:6060";

    UPROPERTY(BlueprintAssignable)
    FImmutableMintSkinOutputPin Success;
    UPROPERTY(BlueprintAssignable)
    FImmutableMintSkinOutputPin Failed;
};