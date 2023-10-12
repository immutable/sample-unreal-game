// Fill out your copyright notice in the Description page of Project Settings.


#include "ImtblMintSkinAsyncAction.h"
#include "endlessrun/API/ImmutableApi.h"
#include "Immutable/Misc/ImtblLogging.h"

UImtblMintSkinAsyncAction* UImtblMintSkinAsyncAction::MintSkin(UObject* WorldContextObject,
    const FString& WalletAddress)
{
    UImtblMintSkinAsyncAction* MintSkinBlueprintNode = NewObject<UImtblMintSkinAsyncAction>();
    MintSkinBlueprintNode->WorldContextObject = WorldContextObject;
    MintSkinBlueprintNode->WalletAddress = WalletAddress;
    return MintSkinBlueprintNode;
}


void UImtblMintSkinAsyncAction::Activate()
{
    if (!WorldContextObject || !WorldContextObject->GetWorld())
    {
        FString Err = "Mint Skin failed due to missing world or world context object.";
        IMTBL_WARN("%s", *Err)
        Failed.Broadcast(Err);
        return;
    }
    UImtblMintSkinAsyncAction::DoMintSkin(nullptr);
}    


void UImtblMintSkinAsyncAction::DoMintSkin(TWeakObjectPtr<UImtblJSConnector> JSConnector)
{
    TWeakObjectPtr<UImmutableApi> ImtblApi = NewObject<UImmutableApi>();
    ImtblApi->MintSkin(WalletAddress,
        UImmutableApi::FImtblApiResponseDelegate::CreateUObject(this, &UImtblMintSkinAsyncAction::OnMintSkinResponse));
}

void UImtblMintSkinAsyncAction::OnMintSkinResponse(const FImtblAPIResponse& Result)
{
    FString Msg = "";
    if (Result.ConnectedSuccessfully)
    {
        IMTBL_LOG("Mint Skin Response: %s", *Result.Response->GetContentAsString())
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