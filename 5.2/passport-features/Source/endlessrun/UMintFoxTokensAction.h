#pragma once
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UMintFoxTokensAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMintFoxOutputPin, FString, Message);

UCLASS()
class ENDLESSRUN_API UMintFoxTokensAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "EndlessRun")
	static UMintFoxTokensAction* MintFoxes(const FString& ToAddress);

	virtual void Activate() override;

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UPROPERTY(BlueprintAssignable)
	FMintFoxOutputPin Minted;
	UPROPERTY(BlueprintAssignable)
	FMintFoxOutputPin Failed;
private:
	FString Address;
};

USTRUCT()
struct FMintData
{
	GENERATED_BODY()

	UPROPERTY()
	FString toUserWallet;
	UPROPERTY()
	int64 number;
};