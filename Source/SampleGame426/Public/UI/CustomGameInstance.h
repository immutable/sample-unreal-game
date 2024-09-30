#pragma once

#include "GameplayTagContainer.h"
#include "Engine/GameInstance.h"

#include "CustomGameInstance.generated.h"


UCLASS(Config = Game)
class UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	/** Delegate when a system error message is sent, the game can choose to display it to the user using the type tag */
	// DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCustomHandleSystemMessageDelegate, FGameplayTag, MessageType, FText, TitleText, FText, BodyText);
	
	// UPROPERTY(BlueprintAssignable, Category = CommonUser)
	// FCustomHandleSystemMessageDelegate OnHandleSystemMessage;

	/** Send a system message via OnHandleSystemMessage */
	UFUNCTION(BlueprintCallable, Category = CommonUser)
	static void SendSystemMessage(const UObject* WorldContextObject, FGameplayTag MessageType, FText TitleText, FText BodyText);

	virtual int32 AddLocalPlayer(ULocalPlayer* NewPlayer, FPlatformUserId UserId) override;
	virtual bool RemoveLocalPlayer(ULocalPlayer* ExistingPlayer) override;
	virtual void ReturnToMainMenu() override;

private:
	/** This is the primary player*/
	TWeakObjectPtr<ULocalPlayer> PrimaryPlayer;
};