#include "CustomGameInstance.h"

#include "CustomLocalPlayer.h"
#include "GameUIManagerSubsystem.h"
#include "LogSampleGameUI.h"

void UCustomGameInstance::SendSystemMessage(FGameplayTag MessageType, FText TitleText, FText BodyText)
{
	OnHandleSystemMessage.Broadcast(MessageType, TitleText, BodyText);
}

void UCustomGameInstance::HandleSystemMessage(FGameplayTag MessageType, FText Title, FText Message)
{
	UE_LOG(LogImmutableUI, Log, TEXT("HandleSystemMessage: Message  %s, %s, %s"), *MessageType.ToString(), *Title.ToString(), *Message.ToString());
	
	// ULocalPlayer* FirstPlayer = GetFirstGamePlayer();
	// // Forward severe ones to the error dialog for the first player
	// if (FirstPlayer && MessageType.MatchesTag(FCommonUserTags::SystemMessage_Error))
	// {
	// 	if (UCommonMessagingSubsystem* Messaging = FirstPlayer->GetSubsystem<UCommonMessagingSubsystem>())
	// 	{
	// 		Messaging->ShowError(UCommonGameDialogDescriptor::CreateConfirmationOk(Title, Message));
	// 	}
	// }
}

int32 UCustomGameInstance::AddLocalPlayer(ULocalPlayer* NewPlayer, FPlatformUserId UserId)
{
	int32 ReturnVal = Super::AddLocalPlayer(NewPlayer, UserId);
	if (ReturnVal != INDEX_NONE)
	{
		if (!PrimaryPlayer.IsValid())
		{
			UE_LOG(LogImmutableUI, Log, TEXT("AddLocalPlayer: Set %s to Player"), *NewPlayer->GetName());
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
		UE_LOG(LogImmutableUI, Log, TEXT("RemoveLocalPlayer: Unsetting Primary Player from %s"), *ExistingPlayer->GetName());
		GetSubsystem<UGameUIManagerSubsystem>()->NotifyPlayerDestroyed(ExistingPlayer);
	}

	return Super::RemoveLocalPlayer(ExistingPlayer);
}

void UCustomGameInstance::ReturnToMainMenu()
{
	Super::ReturnToMainMenu();
}
