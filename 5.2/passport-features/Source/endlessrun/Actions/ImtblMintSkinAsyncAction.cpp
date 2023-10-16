// Fill out your copyright notice in the Description page of Project Settings.


#include "ImtblMintSkinAsyncAction.h"
#include "endlessrun/API/ImmutableApi.h"
#include "Immutable/Misc/ImtblLogging.h"
#include "JsonObjectConverter.h"

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
    const TSharedRef<IHttpRequest> Request = HttpModule.CreateRequest();
    Request->SetVerb("POST");

	// We'll need to tell the server what type of content to expect in the POST data
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));

	FString RequestContent = TEXT("toUserWallet=") + WalletAddress;
	// Set the POST content
	Request->SetContentAsString(RequestContent);

    // Set the http URL
    Request->SetURL(MintServerBaseUrl + FString("/mint/skin"));

    // Set the callback, which will execute when the HTTP call is complete
    Request->OnProcessRequestComplete().BindUObject(this, &UImtblMintSkinAsyncAction::OnResponseReceived);

    // Submit the request for processing
    Request->ProcessRequest();
}

void UImtblMintSkinAsyncAction::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful)
    {
        IMTBL_LOG("Mint Skin Response: %s", *Response->GetContentAsString())
        Success.Broadcast("Mint Skin Success");
    }
    else
    {
        switch (Request->GetStatus())
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