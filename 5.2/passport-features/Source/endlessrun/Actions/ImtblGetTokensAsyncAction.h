// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Immutable/Actions/ImtblBlueprintAsyncAction.h"
#include "endlessrun/API/ImmutableApi.h"
#include "ImtblGetTokensAsyncAction.generated.h"

USTRUCT(BlueprintType)
struct FTokenData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString token_id;
};

USTRUCT()
struct FGetTokens
{
    GENERATED_BODY()

    UPROPERTY()
    TArray<FTokenData> result;
};

/**
 * 
 */
UCLASS()
class UImtblGetTokensAsyncAction : public UImtblBlueprintAsyncAction
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetTokensOutputPin, const TArray<FTokenData>&, Tokens, FString, ErrorMessage);
    
public:
    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Game")
    static UImtblGetTokensAsyncAction* GetTokens(UObject* WorldContextObject,
        const FString& WalletAddress, const FString& TokenAddress, const int Quantity);

    virtual void Activate() override;

    UPROPERTY(BlueprintAssignable)
    FGetTokensOutputPin Success;
    UPROPERTY(BlueprintAssignable)
    FGetTokensOutputPin Failed;

private:
    void DoGetTokens(TWeakObjectPtr<class UImtblJSConnector> JSConnector);
    void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

    FString WalletAddress;
    FString TokenAddress;
    int64 Quantity;
    
    FHttpModule& HttpModule = FHttpModule::Get();
    FString ImxApiBaseUrl = "https://api.sandbox.x.immutable.com";
};
