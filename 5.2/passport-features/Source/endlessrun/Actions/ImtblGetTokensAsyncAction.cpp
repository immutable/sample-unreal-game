// Fill out your copyright notice in the Description page of Project Settings.


#include "ImtblGetTokensAsyncAction.h"
#include "Immutable/Misc/ImtblLogging.h"
#include "JsonObjectConverter.h"

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
        TArray<FTokenData> EmptyArr;
        Failed.Broadcast(EmptyArr, Err);
        return;
    }
    UImtblGetTokensAsyncAction::DoGetTokens(nullptr);
}    


void UImtblGetTokensAsyncAction::DoGetTokens(TWeakObjectPtr<UImtblJSConnector> JSConnector)
{
    FHttpModule& httpModule = FHttpModule::Get();
    TSharedRef<IHttpRequest> Request = httpModule.CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &UImtblGetTokensAsyncAction::OnResponseReceived);

    Request->SetURL(ImxApiBaseUrl + "/v1/assets?collection=" + TokenAddress + "&page_size=" + FString::FromInt(Quantity) + "&user=" + WalletAddress);
    Request->SetVerb("GET");
    Request->ProcessRequest();
}

void UImtblGetTokensAsyncAction::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    TArray<FTokenData> EmptyArr;
    if (bWasSuccessful)
    {
        FString Content = Response->GetContentAsString();
        IMTBL_LOG("Get Tokens Response0: %s", *Content);
        const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Content);
        FJsonObjectWrapper Wrapper;
        Wrapper.JsonObject = MakeShared<FJsonObject>();

        FGetTokens Result;
        if (!FJsonSerializer::Deserialize(JsonReader, Wrapper.JsonObject) || !Wrapper.JsonObject.IsValid())
        {
            IMTBL_ERR("Could not parse response from JavaScript -- invalid JSON: %s", *Content)
            Failed.Broadcast(EmptyArr, "Unable to get tokens");
        }
        else if(!FJsonObjectConverter::JsonObjectToUStruct(Wrapper.JsonObject.ToSharedRef(), &Result, 0, 0))
        {
            IMTBL_ERR("Could not parse response from JavaScript into the expected response object format: %s", *Content)
            Failed.Broadcast(EmptyArr, "Unable to get tokens");
        }
        else
        {
            Success.Broadcast(Result.result, "");
        }            
    }
    else
    {
        Failed.Broadcast(EmptyArr, "Unable to get tokens");
    }
}