#pragma once

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "ImmutableApi.generated.h"

USTRUCT()
struct FImtblAPIResponse
{
	GENERATED_BODY()

	UPROPERTY()
	bool ConnectedSuccessfully = false;

	FHttpRequestPtr Request;
	FHttpResponsePtr Response;
};

/**
 *
 */
UCLASS()
class UImmutableApi : public UObject
{
	GENERATED_BODY()
public:

	DECLARE_DELEGATE_OneParam(FImtblApiResponseDelegate, const FImtblAPIResponse&);
	
	bool MintTokens(int Quantity, const FString& WalletAddress, const FImtblApiResponseDelegate& ResponseDelegate);
	bool MintSkin(const FString& WalletAddress, const FImtblApiResponseDelegate& ResponseDelegate);
	bool GetTokens(int Quantity, const FString& TokenAddress, const FString& WalletAddress, const FImtblApiResponseDelegate& ResponseDelegate);
	bool GetSkin(const FString& TokenAddress, const FString& WalletAddress, const FImtblApiResponseDelegate& ResponseDelegate);
	
protected:
	FHttpModule& HttpModule = FHttpModule::Get();
	FString MintServerBaseUrl = "http://localhost:6060";
	FString ImxApiBaseUrl = "https://api.sandbox.x.immutable.com";
	TMap<FString, FImtblApiResponseDelegate> ResponseDelegates;

	void SendResponse(FString RequestName, FHttpRequestPtr pRequest,
			FHttpResponsePtr pResponse,
			bool connectedSuccessfully);
public:
	const FString TOKEN_TOKEN_ADDRESS = "0x3765D19D5BC39b60718e43B4b12b30e87D383181";
	const FString SKIN_TOKEN_ADDRESS = "0x35bec1b2e8a30af9bfd138555a633245519b607c";
};
