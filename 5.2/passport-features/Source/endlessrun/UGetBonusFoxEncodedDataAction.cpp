#include "UGetBonusFoxEncodedDataAction.h"
#include "JsonObjectConverter.h"

UGetBonusFoxEncodedDataAction* UGetBonusFoxEncodedDataAction::EncodeBonusFoxData(const FString& Token)
{
	UGetBonusFoxEncodedDataAction* BlueprintNode = NewObject<UGetBonusFoxEncodedDataAction>();
	BlueprintNode->TokenToBurn = Token;
	return BlueprintNode;
}

void UGetBonusFoxEncodedDataAction::Activate()
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> Request = httpModule.CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UGetBonusFoxEncodedDataAction::OnResponseReceived);
	Request->SetURL("http://localhost:6060/zk/skin/craftskin/encodeddata");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	FString OutString;
	FJsonObjectConverter::UStructToJsonObjectString(FBonusFoxData{TokenToBurn}, OutString, 0, 0, 0, nullptr, false);
	Request->SetContentAsString(OutString);
	Request->ProcessRequest();
}

void UGetBonusFoxEncodedDataAction::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TArray<FTokenModel> EmptyArr;
	if (bWasSuccessful)
	{
		FString Content = Response->GetContentAsString();
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Content);
		FJsonObjectWrapper Wrapper;
		Wrapper.JsonObject = MakeShared<FJsonObject>();

		FGetFoxTokensResult Result;
		if (FJsonSerializer::Deserialize(JsonReader, Wrapper.JsonObject))
		{
			Encoded.Broadcast(Wrapper.JsonObject->GetStringField("data"));
		} else
		{
			Failed.Broadcast("Unable to encode data");
		}
	}
	else
	{
		Failed.Broadcast("Unable to encode data");
	}
}
