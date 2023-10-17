// Fill out your copyright notice in the Description page of Project Settings.


#include "ImtblGetSkinAsyncAction.h"
#include "Immutable/Misc/ImtblLogging.h"
#include "JsonObjectConverter.h"

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
		TArray<FSkinData> EmptyArr;
        Failed.Broadcast(EmptyArr, Err);
        return;
    }
    UImtblGetSkinAsyncAction::DoGetSkin(nullptr);
}    


void UImtblGetSkinAsyncAction::DoGetSkin(TWeakObjectPtr<UImtblJSConnector> JSConnector)
{
    FHttpModule& httpModule = FHttpModule::Get();
    TSharedRef<IHttpRequest> Request = httpModule.CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &UImtblGetSkinAsyncAction::OnResponseReceived);

    Request->SetURL(ImxApiBaseUrl + "/v1/assets?collection=" + TokenAddress + "&user=" + WalletAddress);
    Request->SetVerb("GET");
    Request->ProcessRequest();
}

void UImtblGetSkinAsyncAction::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    TArray<FSkinData> EmptyArr;
    if (bWasSuccessful)
    {
        FString Content = Response->GetContentAsString();
        TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Content);
        FJsonObjectWrapper Wrapper;
        Wrapper.JsonObject = MakeShared<FJsonObject>();

        FGetSkins Result;
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
        Failed.Broadcast(EmptyArr, "Unable to encode data");
    }
}