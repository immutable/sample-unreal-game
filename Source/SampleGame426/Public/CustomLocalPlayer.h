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
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBalanceUpdatedFloatDelegate, float, TokenBalance);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBalanceUpdatedFStringDelegate, const FString&, TokenBalance);

public:
	UCustomLocalPlayer();

	/** ULocalPlayer: Interface Begin */
#if (ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 1)
	virtual void PlayerAdded(UGameViewportClient* InViewportClient, FPlatformUserId InUserId) override;
#else
	virtual void PlayerAdded(UGameViewportClient* InViewportClient, int32 InControllerID) override;
#endif
	/** ULocalPlayer: Interface End */

	FDelegateHandle CallAndRegister_OnPlayerControllerSet(FPlayerControllerSetDelegate::FDelegate Delegate);
	FDelegateHandle CallAndRegister_OnPassportInitialized(FPlayerPassportInitializedDelegates::FDelegate Delegate);
	FDelegateHandle CallAndRegister_OnPlayerLoggedIn(FPlayerLoggedInDelegate::FDelegate Delegate);
	FDelegateHandle CallAndRegister_OnPlayerPassportDataObtained(FPlayerPassportDataObtained::FDelegate Delegate);

	UPrimaryGameLayout* GetRootUILayout() const;
	UGameUIPolicy* GetGameUIPolicy() const;

	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	bool IsPassportLoggedIn();

	UFUNCTION(BlueprintPure)
	FString GetPassportWalletAddress();

	UFUNCTION(BlueprintPure)
	FString GetPassportEmail();

	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	float GetIMRBalance();

	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	float GetIMXBalance();

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
	void OnIMRBalanceUpdateResponse(const ImmutableOrderbook::APIOrderbookApi::TokenBalanceResponse& Response);
	void OnIMXBalanceUpdateResponse(FImmutablePassportResult Result);
	void OnUSDCBalanceUpdateResponse(const ImmutableOrderbook::APIOrderbookApi::TokenBalanceResponse& Response);

	void CollectPassportData();
	bool CheckAllPassportDataObtained();
	void NotifyIfAllPassportDataObtained();

public:
	UPROPERTY(BlueprintAssignable)
	FOnBalanceUpdatedFloatDelegate OnIMRBalanceUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnBalanceUpdatedFStringDelegate OnIMXBalanceUpdated;
	
	UPROPERTY(BlueprintAssignable)
	FOnBalanceUpdatedFloatDelegate OnUSDCBalanceUpdated;

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
	FString PassportEmail;
	float PassportWalletBalanceIMR = 0.0f;
	float PassportWalletBalanceIMX = 0.0f;
	float PassportWalletBalanceUSDC = 0.0f;
};
