#include "UGetBlueFoxEncodedDataAction.h"
#include "JsonObjectConverter.h"

UGetBlueFoxEncodedDataAction* UGetBlueFoxEncodedDataAction::EncodeBlueFoxData(const TArray<FString>& Tokens)
{
	UGetBlueFoxEncodedDataAction* BlueprintNode = NewObject<UGetBlueFoxEncodedDataAction>();
	BlueprintNode->TokensToBurn = Tokens;
	return BlueprintNode;
}

void UGetBlueFoxEncodedDataAction::Activate()
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> Request = httpModule.CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UGetBlueFoxEncodedDataAction::OnResponseReceived);
	Request->SetURL("http://localhost:6060/zk/token/craftskin/encodeddata");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	FString OutString;
	FJsonObjectConverter::UStructToJsonObjectString(FBlueFoxData{TokensToBurn[0], TokensToBurn[1], TokensToBurn[2]}, OutString, 0, 0, 0, nullptr, false);
	Request->SetContentAsString(OutString);
	Request->ProcessRequest();
}

void UGetBlueFoxEncodedDataAction::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
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
