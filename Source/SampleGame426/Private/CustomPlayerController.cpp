#include "CustomPlayerController.h"

#include "CustomLocalPlayer.h"

void ACustomPlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();

	if (UCustomLocalPlayer* LocalPlayer = Cast<UCustomLocalPlayer>(Player))
	{
		LocalPlayer->OnPlayerControllerSet.Broadcast(LocalPlayer, this);
	}
}