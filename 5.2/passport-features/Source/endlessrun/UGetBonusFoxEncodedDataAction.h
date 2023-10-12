#pragma once
#include "HttpModule.h"
#include "UGetTokensAction.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UGetBonusFoxEncodedDataAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetBonusFoxEncodedDataOutputPin, const FString&, Data);

UCLASS()
class ENDLESSRUN_API UGetBonusFoxEncodedDataAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "EndlessRun")
	static UGetBonusFoxEncodedDataAction* EncodeBonusFoxData(const FString& Token);

	virtual void Activate() override;

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UPROPERTY(BlueprintAssignable)
	FGetBonusFoxEncodedDataOutputPin Encoded;
	UPROPERTY(BlueprintAssignable)
	FGetBonusFoxEncodedDataOutputPin Failed;

private:
	FString TokenToBurn;
};

USTRUCT()
struct FBonusFoxData
{
	GENERATED_BODY()

	UPROPERTY()
	FString tokenId;
};
