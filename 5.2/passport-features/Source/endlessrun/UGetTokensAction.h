#pragma once
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UGetTokensAction.generated.h"


USTRUCT(BlueprintType)
struct FTokenModel
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString token_id;
};

USTRUCT()
struct FGetFoxTokensResult
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FTokenModel> result;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetTokensOutputPin, const TArray<FTokenModel>&, Tokens, FString, Message);

UCLASS()
class ENDLESSRUN_API UGetTokensAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "EndlessRun")
	static UGetTokensAction* GetTokens(const FString& WalletAddress, const FString& TokenAddress);

	virtual void Activate() override;

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UPROPERTY(BlueprintAssignable)
	FGetTokensOutputPin GotTokens;
	UPROPERTY(BlueprintAssignable)
	FGetTokensOutputPin Failed;
private:
	FString Address;
	FString TokenContractAddress;
};
