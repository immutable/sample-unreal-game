#pragma once

#include "APIOrderbookApi.h"
#include "Engine/LocalPlayer.h"

#include "APIOrderbookApi.h"

#include "Immutable/ImmutableDataTypes.h"

#include "CustomLocalPlayer.generated.h"

class UImmutablePassport;

class ACustomPlayerController;
class UGameUIPolicy;
class UPrimaryGameLayout;

UCLASS(Config = "Game", Transient)
class SAMPLEGAME426_API UCustomLocalPlayer : public ULocalPlayer
{
	GENERATED_BODY()

	friend ACustomPlayerController;

public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FPlayerControllerSetDelegate, UCustomLocalPlayer* LocalPlayer, APlayerController* PlayerController);
	DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerPassportInitializedDelegates, bool bIsInitialized);
	DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerLoggedInDelegate, bool bIsLoggedIn);
	DECLARE_MULTICAST_DELEGATE(FPlayerPassportDataObtained);

	/* Immutalbe related */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBalanceUpdatedDelegate, float, TokenBalance);

public:
	UCustomLocalPlayer();

	/** ULocalPlayer: Interface Begin */
	virtual void PlayerAdded(UGameViewportClient* InViewportClient, int32 InControllerID) override;
	virtual void PlayerAdded(UGameViewportClient* InViewportClient, FPlatformUserId InUserId) override;
	/** ULocalPlayer: Interface End */

	FDelegateHandle CallAndRegister_OnPlayerControllerSet(FPlayerControllerSetDelegate::FDelegate Delegate);
	FDelegateHandle CallAndRegister_OnPassportInitialized(FPlayerPassportInitializedDelegates::FDelegate Delegate);
	FDelegateHandle CallAndRegister_OnPlayerLoggedIn(FPlayerLoggedInDelegate::FDelegate Delegate);
	FDelegateHandle CallAndRegister_OnPlayerPassportDataObtained(FPlayerPassportDataObtained::FDelegate Delegate);

	UPrimaryGameLayout* GetRootUILayout() const;
	UGameUIPolicy* GetGameUIPolicy() const;

	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	bool IsPassportLoggedIn();

	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	FString GetPassportWalletAddress();

	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	float GetBalance();

	/* Immutalbe related */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void LoginPassport();

	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void LogoutPassport();

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
	void OnBalanceUpdateResponse(const ImmutableOrderbook::APIOrderbookApi::TokenBalanceResponse& Response);

	void CollectPassportData();
	bool CheckAllPassportDataObtained();
	void NotifyIfAllPassportDataObtained();

public:
	UPROPERTY(BlueprintAssignable)
	FOnBalanceUpdatedDelegate OnBalanceUpdated;

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
	TWeakObjectPtr<UImmutablePassport> Passport;

	bool IsPassportInitialized = false;
	bool IsLocalPlayerLoggedIn = false;
	FString PassportWalletAddress;
	float PassportWalletBalance = 0.0f;
};