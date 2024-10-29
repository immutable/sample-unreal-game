#include "GameFramework/CustomGameMode.h"

#include "GameUIManagerSubsystem.h"

void ACustomGameMode::InitializeHUDForPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::InitializeHUDForPlayer_Implementation(NewPlayer);

	if (UGameUIManagerSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UGameUIManagerSubsystem>())
	{
		TSoftClassPtr<UGameUIPolicy> UIPolicyClassToUse;

		if (UWorld* World = GetWorld())
		{
			if (ACustomGameMode* CustomGameMode = Cast<ACustomGameMode>(World->GetAuthGameMode()))
			{
				UIPolicyClassToUse = CustomGameMode->UIPolicyClass;
			}
		}

		if (UIPolicyClassToUse.IsNull())
		{
			if (!Subsystem->GetCurrentUIPolicy() && !Subsystem->GetDefaultUIPolicyClass().IsNull())
			{
				UIPolicyClassToUse = Subsystem->GetDefaultUIPolicyClass();
			}
		}

		if (ensureAlways(!UIPolicyClassToUse.IsNull()))
		{
			TSubclassOf<UGameUIPolicy> PolicyClass = UIPolicyClassToUse.LoadSynchronous();
			Subsystem->SwitchToPolicy(PolicyClass);
		}
	}
}
