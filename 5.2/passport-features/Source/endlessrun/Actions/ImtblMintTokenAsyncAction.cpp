// Fill out your copyright notice in the Description page of Project Settings.


#include "Immutable/Actions/ImtblMintTokenAsyncAction.h"
#include "../API/ImmutableApi.h"
#include "Immutable/Misc/ImtblLogging.h"


UImtblMintTokenAsyncAction* UImtblMintTokenAsyncAction::MintToken(UObject* WorldContextObject)
{
    UImtblMintTokenAsyncAction* MintTokenBlueprintNode = NewObject<UImtblMintTokenAsyncAction>();
    MintTokenBlueprintNode->WorldContextObject = WorldContextObject;
    return MintTokenBlueprintNode;
}


void UImtblMintTokenAsyncAction::Activate()
{
    if (!WorldContextObject || !WorldContextObject->GetWorld())
    {
        FString Err = "Mint Tokens failed due to missing world or world context object.";
        IMTBL_WARN("%s", *Err)
        Failed.Broadcast(Err);
        return;
    }

    UImmutableApi *Api = new UImmutableApi();
    if (Api->MintTokens(1, Api->TOKEN_TOKEN_ADDRESS))
    {
        Success.Broadcast(TEXT(""));
    }
    else
    {
        Failed.Broadcast(TEXT("Failed to mint token."));
    }
}

