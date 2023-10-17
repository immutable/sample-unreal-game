// Fill out your copyright notice in the Description page of Project Settings.


#include "ImtblMintTokensAsyncAction.h"
#include "Immutable/Misc/ImtblLogging.h"
#include "JsonObjectConverter.h"

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
    UImtblMintTokensAsyncAction::DoMintTokens();
}    


void UImtblMintTokensAsyncAction::DoMintTokens()
{
    const TSharedRef<IHttpRequest> Request = HttpModule.CreateRequest();
    Request->SetVerb("POST");

	// We'll need to tell the server what type of content to expect in the POST data
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));

	FString RequestContent = TEXT("toUserWallet=") + WalletAddress + TEXT("&number=") + FString::FromInt(Quantity);
	// Set the POST content
	Request->SetContentAsString(RequestContent);

    // Set the http URL
    Request->SetURL(MintServerBaseUrl + FString("/mint/token"));

    // Set the callback, which will execute when the HTTP call is complete
    Request->OnProcessRequestComplete().BindUObject(this, &UImtblMintTokensAsyncAction::OnResponseReceived);

    // Submit the request for processing
    Request->ProcessRequest();
}

void UImtblMintTokensAsyncAction::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
    if (bConnectedSuccessfully)
    {
        IMTBL_LOG("Mint Token Response: %s", *Response->GetContentAsString())
        Success.Broadcast("Mint Token Success");
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