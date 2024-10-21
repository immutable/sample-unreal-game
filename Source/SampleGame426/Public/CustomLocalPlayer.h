#pragma once

#include "OpenAPIOrderbookApi.h"
#include "Engine/LocalPlayer.h"
#include "Immutable/ImmutableDataTypes.h"
#include "Immutable/ImmutablePassport.h"

#include "CustomLocalPlayer.generated.h"

/*
 * 
 */
UCLASS(config=Game, transient)
class SAMPLEGAME426_API UCustomLocalPlayer : public ULocalPlayer
{
	GENERATED_BODY()

public:
	UCustomLocalPlayer();
	
	DECLARE_MULTICAST_DELEGATE_TwoParams(FPlayerControllerSetDelegate, UCustomLocalPlayer* LocalPlayer, APlayerController* PlayerController);
	DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerPassportInitializedDelegates, bool IsInitialized);
	DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerLoggedInDelegate, bool IsLoggedIn);
	DECLARE_MULTICAST_DELEGATE(FPlayerPassportDataObtained);
	
	/* Immutalbe related */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBalanceUpdatedDelegate, float, TokenBalance);

	FDelegateHandle CallAndRegister_OnPlayerControllerSet(FPlayerControllerSetDelegate::FDelegate Delegate);
	FDelegateHandle CallAndRegister_OnPassportInitialized(FPlayerPassportInitializedDelegates::FDelegate Delegate);
	FDelegateHandle CallAndRegister_OnPlayerLoggedIn(FPlayerLoggedInDelegate::FDelegate Delegate);
	FDelegateHandle CallAndRegister_OnPlayerPassportDataObtained(FPlayerPassportDataObtained::FDelegate Delegate);

	/* ULocalPlayer Interface */
	virtual void PlayerAdded(class UGameViewportClient* InViewportClient, int32 InControllerID) override;
	/* ULocalPlayer Interface */

	class UPrimaryGameLayout* GetRootUILayout() const;
	class UGameUIPolicy* GetGameUIPolicy() const;

	/* Immutalbe related */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void LoginPassport();
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void LogoutPassport();
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	bool IsPassportLoggedIn();
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	FString GetPassportWalletAddress();
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	float GetBalance();
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void UpdateBalance();

	void SignSubmitApproval(const FString& To, const FString& Data, TFunction<void(FString TransactionHash, FString Status)> Callback);
	void SignData(const FString& SingableMessageJson, TFunction<void(const FString& Signature)> Callback);

private:
	void InitializePassport();
	void OnPassportIsRunning(TWeakObjectPtr<class UImtblJSConnector> JSConnector);
	void OnPassportInitialized(FImmutablePassportResult Result);
	void OnPassportLoggedIn(FImmutablePassportResult Result);
	void OnPassportLoggedOut(FImmutablePassportResult Result);
	void OnBalanceUpdateResponse(const ImmutableTsSdkApi::OpenAPIOrderbookApi::TokenBalanceResponse& Response);

	void CollectPassportData();
	bool CheckAllPassportDataObtained();
	void NotifyIfAllPassportDataObtained();

public:
	UPROPERTY(BlueprintAssignable)
	FOnBalanceUpdatedDelegate OnBalanceUpdated;

	friend class ACustomPlayerController;

protected: 	
	/** Called when the local player is assigned a player controller */
	FPlayerControllerSetDelegate OnPlayerControllerSet;
	
	/** Called when the Immutable passport functionality is ready to be used */
	FPlayerPassportInitializedDelegates OnPlayerPassportInitialized;

	/** Called when the local player is logged into Immutable Passport */
	FPlayerLoggedInDelegate OnPlayerLoggedIn;

	/** Called when the local player's passport data is obtained */
	FPlayerPassportDataObtained OnPlayerPassportDataObtained;

private:
	TWeakObjectPtr<class UImmutablePassport> Passport;

	bool IsPassportInitialized = false;
	bool IsLocalPlayerLoggedIn = false;
	FString PassportWalletAddress;
	float PassportWalletBalance = 0.0f;

};