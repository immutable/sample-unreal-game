// Fill out your copyright notice in the Description page of Project Settings.


#include "ImtblGetTokensAsyncAction.h"
#include "endlessrun/API/ImmutableApi.h"
#include "Immutable/Misc/ImtblLogging.h"

UImtblGetTokensAsyncAction* UImtblGetTokensAsyncAction::GetTokens(UObject* WorldContextObject,
    const FString& WalletAddress, const FString& TokenAddress, const int Quantity)
{
    UImtblGetTokensAsyncAction* GetTokensBlueprintNode = NewObject<UImtblGetTokensAsyncAction>();
    GetTokensBlueprintNode->WorldContextObject = WorldContextObject;
    GetTokensBlueprintNode->WalletAddress = WalletAddress;
    GetTokensBlueprintNode->TokenAddress = TokenAddress;
    GetTokensBlueprintNode->Quantity = Quantity;
    return GetTokensBlueprintNode;
}


void UImtblGetTokensAsyncAction::Activate()
{
    if (!WorldContextObject || !WorldContextObject->GetWorld())
    {
        FString Err = "Get Tokens failed due to missing world or world context object.";
        IMTBL_WARN("%s", *Err)
        Failed.Broadcast(Err);
        return;
    }
    UImtblGetTokensAsyncAction::DoGetTokens(nullptr);
}    


void UImtblGetTokensAsyncAction::DoGetTokens(TWeakObjectPtr<UImtblJSConnector> JSConnector)
{
    TWeakObjectPtr<UImmutableApi> ImtblApi = NewObject<UImmutableApi>();
    ImtblApi->GetTokens(Quantity, TokenAddress, WalletAddress,
        UImmutableApi::FImtblApiResponseDelegate::CreateUObject(this, &UImtblGetTokensAsyncAction::OnGetTokensResponse));
}

void UImtblGetTokensAsyncAction::OnGetTokensResponse(const FImtblAPIResponse& Result)
{
    FString Msg = "";
    if (Result.ConnectedSuccessfully)
    {
        IMTBL_LOG("Get Tokens Response: %s", *Result.Response->GetContentAsString())
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