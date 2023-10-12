#include "UMintFoxTokensAction.h"
#include "JsonObjectConverter.h"

UMintFoxTokensAction* UMintFoxTokensAction::MintFoxes(const FString& ToAddress)
{
	UMintFoxTokensAction* BlueprintNode = NewObject<UMintFoxTokensAction>();
	BlueprintNode->Address = ToAddress;
	return BlueprintNode;
}

void UMintFoxTokensAction::Activate()
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> Request = httpModule.CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UMintFoxTokensAction::OnResponseReceived);
	Request->SetURL("http://localhost:6060/zkmint/token");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	FString OutString;
	FJsonObjectConverter::UStructToJsonObjectString(FMintData{Address, 3}, OutString, 0, 0, 0, nullptr, false);
	Request->SetContentAsString(OutString);
	Request->ProcessRequest();
}

void UMintFoxTokensAction::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		Minted.Broadcast("");
	}
	else
	{
		Failed.Broadcast("Unable to mint tokens");
	}
}
