#include "GameUIPolicy.h"

#include "GameUIManagerSubsystem.h"
#include "LogImmutableUI.h"


/* Static */ UGameUIPolicy* UGameUIPolicy::GetGameUIPolicy(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		if (UGameInstance* GameInstance = World->GetGameInstance())
		{
			if (UGameUIManagerSubsystem* UIManager = UGameInstance::GetSubsystem<UGameUIManagerSubsystem>(GameInstance))
			{
				return UIManager->GetCurrentUIPolicy();
			}
		}
	}

	return nullptr;
}

UGameUIManagerSubsystem* UGameUIPolicy::GetOwningUIManager() const
{
	return CastChecked<UGameUIManagerSubsystem>(GetOuter());
}

UWorld* UGameUIPolicy::GetWorld() const
{
	return GetOwningUIManager()->GetGameInstance()->GetWorld();
}

UPrimaryGameLayout* UGameUIPolicy::GetRootLayout(const ULocalPlayer* LocalPlayer) const
{
	return RootLayout;
}

void UGameUIPolicy::NotifyPlayerAdded(ULocalPlayer* LocalPlayer)
{
	if (APlayerController* PlayerController = LocalPlayer->GetPlayerController(GetWorld()))
	{
		TSubclassOf<UPrimaryGameLayout> LayoutWidgetClass = LayoutClass.LoadSynchronous();
		if (ensure(LayoutWidgetClass && !LayoutWidgetClass->HasAnyClassFlags(CLASS_Abstract)))
		{
			UPrimaryGameLayout* NewLayoutObject = CreateWidget<UPrimaryGameLayout>(PlayerController, LayoutWidgetClass);

			NewLayoutObject->SetPlayerContext(FLocalPlayerContext(LocalPlayer));
			NewLayoutObject->AddToPlayerScreen(1000);

			UE_LOG(LogImmutableUI, Log, TEXT("[%s] is adding s]'s root layout [%s] to the viewport"), *GetName(), *GetNameSafe(NewLayoutObject));

#if WITH_EDITOR
			if (GIsEditor)
			{
				// So our controller will work in PIE without needing to click in the viewport
				FSlateApplication::Get().SetUserFocusToGameViewport(0);
			}
#endif
		}
	}
}

void UGameUIPolicy::NotifyPlayerDestroyed(ULocalPlayer* LocalPlayer)
{
	RootLayout->RemoveFromParent();
	UE_LOG(LogImmutableUI, Log, TEXT("Removing root layout from the viewport"));
}
