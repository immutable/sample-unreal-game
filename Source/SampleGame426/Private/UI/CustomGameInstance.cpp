#include "CustomGameInstance.h"

#include "CustomLocalPlayer.h"
#include "GameUIManagerSubsystem.h"
#include "LogSampleGame.h"
#include "Dialog/DialogSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UCustomGameInstance::SendSystemMessage(const UObject* WorldContextObject, FGameplayTag MessageType, FText TitleText, FText BodyText)
{
	auto GameInstance = Cast<UCustomGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));

	if (!GameInstance)
	{
		UE_LOG(LogSampleGame, Error, TEXT("Failed to SendSystemMessage for %s"), *WorldContextObject->GetName());
		return;
	}
	
	if (UDialogSubsystem* DialogSubsystem = GameInstance->GetFirstGamePlayer()->GetSubsystem<UDialogSubsystem>())
	{
		DialogSubsystem->ShowError(UDialogSubsystem::CreateErrorDescriptor(TitleText, BodyText));
	}
}

int32 UCustomGameInstance::AddLocalPlayer(ULocalPlayer* NewPlayer, FPlatformUserId UserId)
{
	int32 ReturnVal = Super::AddLocalPlayer(NewPlayer, UserId);
	if (ReturnVal != INDEX_NONE)
	{
		if (!PrimaryPlayer.IsValid())
		{
			UE_LOG(LogSampleGame, Log, TEXT("AddLocalPlayer: Set %s to Player"), *NewPlayer->GetName());
			PrimaryPlayer = NewPlayer;
		}
		
		GetSubsystem<UGameUIManagerSubsystem>()->NotifyPlayerAdded(Cast<UCustomLocalPlayer>(NewPlayer));
	}
	
	return ReturnVal;
}

bool UCustomGameInstance::RemoveLocalPlayer(ULocalPlayer* ExistingPlayer)
{
	if (PrimaryPlayer == ExistingPlayer)
	{
		PrimaryPlayer.Reset();
		UE_LOG(LogSampleGame, Log, TEXT("RemoveLocalPlayer: Unsetting Primary Player from %s"), *ExistingPlayer->GetName());
		GetSubsystem<UGameUIManagerSubsystem>()->NotifyPlayerDestroyed(ExistingPlayer);
	}

	return Super::RemoveLocalPlayer(ExistingPlayer);
}

void UCustomGameInstance::ReturnToMainMenu()
{
	Super::ReturnToMainMenu();
}
