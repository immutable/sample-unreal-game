#include "CustomGameInstance.h"

#include "CustomLocalPlayer.h"
#include "GameUIManagerSubsystem.h"
#include "LogSampleGame.h"
#include "UIGameplayTags.h"
#include "Kismet/GameplayStatics.h"


void UCustomGameInstance::SendDialogMessage(const UObject* WorldContextObject, FGameplayTag DialogType, const UDialogDescriptor* Descriptor)
{
	auto GameInstance = Cast<UCustomGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));

	if (!GameInstance)
	{
		UE_LOG(LogSampleGame, Error, TEXT("Failed to SendSystemMessage for %s"), *WorldContextObject->GetName());
		return;
	}
	
	if (UDialogSubsystem* DialogSubsystem = GameInstance->GetFirstGamePlayer()->GetSubsystem<UDialogSubsystem>())
	{
		DialogSubsystem->ShowDialog(DialogType, Descriptor);
	}
}

void UCustomGameInstance::SendRunningLineMessage(const UObject* WorldContextObject, const FString& Message)
{
	UE_LOG(LogSampleGame, Log, TEXT("%s"), *Message);
}

//
// void UCustomGameInstance::SendErrorMessage(const UObject* WorldContextObject, FGameplayTag MessageType, const FString& Title, const FString& Body, const FString& Error)
// {
// 	auto GameInstance = Cast<UCustomGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
//
// 	if (!GameInstance)
// 	{
// 		UE_LOG(LogSampleGame, Error, TEXT("Failed to SendSystemMessage for %s"), *WorldContextObject->GetName());
// 		return;
// 	}
// 	
// 	if (UDialogSubsystem* DialogSubsystem = GameInstance->GetFirstGamePlayer()->GetSubsystem<UDialogSubsystem>())
// 	{
// 		if (Error.IsEmpty())
// 		{
// 			DialogSubsystem->ShowError(FUIDialogTypes::ErrorFull, UDialogSubsystem::CreateErrorDescriptorWithErrorText(Title, Body, Error));	
// 		}
// 		else
// 		{
// 			DialogSubsystem->ShowError(FUIDialogTypes::ErrorFull, UDialogSubsystem::CreateErrorDescriptorWithErrorText(Title, Body, Error));
// 		}
// 	}
// }

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
