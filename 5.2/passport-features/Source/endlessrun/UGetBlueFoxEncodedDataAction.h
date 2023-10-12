#pragma once
#include "HttpModule.h"
#include "UGetTokensAction.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UGetBlueFoxEncodedDataAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetBlueFoxEncodedDataOutputPin, const FString&, Data);

UCLASS()
class ENDLESSRUN_API UGetBlueFoxEncodedDataAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "EndlessRun")
	static UGetBlueFoxEncodedDataAction* EncodeBlueFoxData(const TArray<FString>& Tokens);

	virtual void Activate() override;

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UPROPERTY(BlueprintAssignable)
	FGetBlueFoxEncodedDataOutputPin Encoded;
	UPROPERTY(BlueprintAssignable)
	FGetBlueFoxEncodedDataOutputPin Failed;

private:
	TArray<FString> TokensToBurn;
};

USTRUCT()
struct FBlueFoxData
{
	GENERATED_BODY()

	UPROPERTY()
	FString tokenId1;
	UPROPERTY()
	FString tokenId2;
	UPROPERTY()
	FString tokenId3;
};
