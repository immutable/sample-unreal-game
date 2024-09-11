#pragma once

#include "Engine/LocalPlayer.h"

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
	DECLARE_MULTICAST_DELEGATE(FPlayerPassportIsRunningDelegate);
	DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerLoggedInDelegate, bool IsLoggedIn);

	FDelegateHandle CallAndRegister_OnPlayerControllerSet(FPlayerControllerSetDelegate::FDelegate Delegate);
	FDelegateHandle CallAndRegister_OnPlayerLoggedIn(FPlayerLoggedInDelegate::FDelegate Delegate);
	FDelegateHandle CallAndRegister_OnPlayerPassportIsRunning(FPlayerPassportIsRunningDelegate::FDelegate Delegate);

	/* ULocalPlayer Interface */
	virtual void PlayerAdded(class UGameViewportClient* InViewportClient, int32 InControllerID) override;
	/* ULocalPlayer Interface */

	class UPrimaryGameLayout* GetRootUILayout() const;

	UFUNCTION(BlueprintCallable)
	void LoginPassport();

private:
	void InitializePassport();
	void OnPassportIsRunning(TWeakObjectPtr<class UImtblJSConnector> JSConnector);
	void OnPassportInitialized(struct FImmutablePassportResult Result);
	void OnPassportLoggedIn(struct FImmutablePassportResult Result);

public:
	/** Called when the Immutable passport functionality is ready to be used */
	FPlayerPassportIsRunningDelegate OnPlayerPassportIsRunning;

	friend class ACustomPlayerController;

protected: 	
	/** Called when the local player is assigned a player controller */
	FPlayerControllerSetDelegate OnPlayerControllerSet;

	/** Called when the local player is logged into Immutable Passport */
	FPlayerLoggedInDelegate OnPlayerLoggedIn;

private:
	TWeakObjectPtr<class UImmutablePassport> Passport;

};