// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "CoreMinimal.h"
#include "Immutable/Actions/ImtblBlueprintAsyncAction.h"
#include "ImtblGetSkinAsyncAction.generated.h"

USTRUCT(BlueprintType)
struct FSkinData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString token_id;
};

USTRUCT()
struct FGetSkins
{
    GENERATED_BODY()

    UPROPERTY()
    TArray<FSkinData> result;
};

/**
 * 
 */
UCLASS()
class UImtblGetSkinAsyncAction : public UImtblBlueprintAsyncAction
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FImmutableMintTokenOutputPin, const TArray<FSkinData>&, Skins, FString, ErrorMessage);
    
    
public:
    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Game")
    static UImtblGetSkinAsyncAction* GetSkin(UObject* WorldContextObject,
        const FString& WalletAddress, const FString& TokenAddress);

    virtual void Activate() override;

private:

    void DoGetSkin(TWeakObjectPtr<class UImtblJSConnector> JSConnector);
    void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

    FString WalletAddress;
    FString TokenAddress;
    
    FHttpModule& HttpModule = FHttpModule::Get();
    FString ImxApiBaseUrl = "https://api.sandbox.x.immutable.com";

    UPROPERTY(BlueprintAssignable)
    FImmutableMintTokenOutputPin Success;
    UPROPERTY(BlueprintAssignable)
    FImmutableMintTokenOutputPin Failed;
};
