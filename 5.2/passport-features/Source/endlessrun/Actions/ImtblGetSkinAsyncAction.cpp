// Fill out your copyright notice in the Description page of Project Settings.


#include "ImtblGetSkinAsyncAction.h"
#include "endlessrun/API/ImmutableApi.h"
#include "Immutable/Misc/ImtblLogging.h"

UImtblGetSkinAsyncAction* UImtblGetSkinAsyncAction::GetSkin(UObject* WorldContextObject,
    const FString& WalletAddress, const FString& TokenAddress)
{
    UImtblGetSkinAsyncAction* GetSkinBlueprintNode = NewObject<UImtblGetSkinAsyncAction>();
    GetSkinBlueprintNode->WorldContextObject = WorldContextObject;
    GetSkinBlueprintNode->WalletAddress = WalletAddress;
    GetSkinBlueprintNode->TokenAddress = TokenAddress;
    return GetSkinBlueprintNode;
}


void UImtblGetSkinAsyncAction::Activate()
{
    if (!WorldContextObject || !WorldContextObject->GetWorld())
    {
        FString Err = "Get Skin failed due to missing world or world context object.";
        IMTBL_WARN("%s", *Err)
        Failed.Broadcast(Err);
        return;
    }
    UImtblGetSkinAsyncAction::DoGetSkin(nullptr);
}    


void UImtblGetSkinAsyncAction::DoGetSkin(TWeakObjectPtr<UImtblJSConnector> JSConnector)
{
    TWeakObjectPtr<UImmutableApi> ImtblApi = NewObject<UImmutableApi>();
    ImtblApi->GetSkin(TokenAddress, WalletAddress,
        UImmutableApi::FImtblApiResponseDelegate::CreateUObject(this, &UImtblGetSkinAsyncAction::OnGetSkinResponse));
}

void UImtblGetSkinAsyncAction::OnGetSkinResponse(const FImtblAPIResponse& Result)
{
    FString Msg = "";
    if (Result.ConnectedSuccessfully)
    {
        IMTBL_LOG("Get Skin Response: %s", *Result.Response->GetContentAsString())
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