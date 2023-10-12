#include "UGetTokensAction.h"
#include "JsonObjectConverter.h"

UGetTokensAction* UGetTokensAction::GetTokens(const FString& WalletAddress, const FString& TokenAddress)
{
	UGetTokensAction* BlueprintNode = NewObject<UGetTokensAction>();
	BlueprintNode->Address = WalletAddress;
	BlueprintNode->TokenContractAddress = TokenAddress;
	return BlueprintNode;
}

void UGetTokensAction::Activate()
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> Request = httpModule.CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UGetTokensAction::OnResponseReceived);
	Request->SetURL("https://api.sandbox.immutable.com/v1/chains/imtbl-zkevm-testnet/accounts/" + Address + "/nfts?contract_address=" + TokenContractAddress);
	Request->SetVerb("GET");
	Request->ProcessRequest();
}

void UGetTokensAction::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
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
			FJsonObjectConverter::JsonObjectToUStruct(Wrapper.JsonObject.ToSharedRef(), &Result, 0, 0);
			GotTokens.Broadcast(Result.result, "");
		} else
		{
			Failed.Broadcast(EmptyArr, "Unable to mint tokens");
		}
	}
	else
	{
		Failed.Broadcast(EmptyArr, "Unable to mint tokens");
	}
}
