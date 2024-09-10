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

	FDelegateHandle CallAndRegister_OnPlayerControllerSet(FPlayerControllerSetDelegate::FDelegate Delegate);

protected: 	
	/** Called when the local player is assigned a player controller */
	FPlayerControllerSetDelegate OnPlayerControllerSet;

public:
	class UPrimaryGameLayout* GetRootUILayout() const;

	friend class ACustomPlayerController;

};