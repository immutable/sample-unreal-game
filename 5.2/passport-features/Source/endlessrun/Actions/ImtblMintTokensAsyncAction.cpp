// Fill out your copyright notice in the Description page of Project Settings.


#include "ImtblMintTokensAsyncAction.h"
#include "endlessrun/API/ImmutableApi.h"
#include "Immutable/Misc/ImtblLogging.h"

UImtblMintTokensAsyncAction* UImtblMintTokensAsyncAction::MintTokens(UObject* WorldContextObject,
    const FString& WalletAddress, const int Quantity)
{
    UImtblMintTokensAsyncAction* MintTokenBlueprintNode = NewObject<UImtblMintTokensAsyncAction>();
    MintTokenBlueprintNode->WorldContextObject = WorldContextObject;
    MintTokenBlueprintNode->WalletAddress = WalletAddress;
    MintTokenBlueprintNode->Quantity = Quantity;
    return MintTokenBlueprintNode;
}


void UImtblMintTokensAsyncAction::Activate()
{
    if (!WorldContextObject || !WorldContextObject->GetWorld())
    {
        FString Err = "Mint Tokens failed due to missing world or world context object.";
        IMTBL_WARN("%s", *Err)
        Failed.Broadcast(Err);
        return;
    }
    UImtblMintTokensAsyncAction::DoMintTokens(nullptr);
}    


void UImtblMintTokensAsyncAction::DoMintTokens(TWeakObjectPtr<UImtblJSConnector> JSConnector)
{
    TWeakObjectPtr<UImmutableApi> ImtblApi = NewObject<UImmutableApi>();
    ImtblApi->MintTokens(Quantity, WalletAddress,
        UImmutableApi::FImtblApiResponseDelegate::CreateUObject(this, &UImtblMintTokensAsyncAction::OnMintTokensResponse));
}

void UImtblMintTokensAsyncAction::OnMintTokensResponse(const FImtblAPIResponse& Result)
{
    FString Msg = "";
    if (Result.ConnectedSuccessfully)
    {
        IMTBL_LOG("Mint Token Response: %s", *Result.Response->GetContentAsString())
        Success.Broadcast(Msg);
    }
    else
    {
        switch (Result.Request->GetStatus())
        {
        case EHttpRequestStatus::Failed_ConnectionError:
            {
                Failed.Broadcast("Connection failed");
                break;
            }
        default:
            {
                Failed.Broadcast("Request failed");
            }
        }
    }
}