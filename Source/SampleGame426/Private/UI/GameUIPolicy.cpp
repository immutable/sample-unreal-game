#include "GameUIPolicy.h"

#include "CustomLocalPlayer.h"
#include "GameUIManagerSubsystem.h"
#include "LogSampleGameUI.h"


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

UPrimaryGameLayout* UGameUIPolicy::GetRootLayout() const
{
	return RootLayout;
}

void UGameUIPolicy::NotifyPlayerAdded(UCustomLocalPlayer* LocalPlayer)
{
	LocalPlayer->CallAndRegister_OnPlayerControllerSet(UCustomLocalPlayer::FPlayerControllerSetDelegate::FDelegate::CreateWeakLambda(this, [this](UCustomLocalPlayer* LocalPlayer, APlayerController* PlayerController)
	{
		TSubclassOf<UPrimaryGameLayout> LayoutWidgetClass = LayoutClass.LoadSynchronous();
	
		if (ensure(LayoutWidgetClass && !LayoutWidgetClass->HasAnyClassFlags(CLASS_Abstract)))
		{
			RootLayout = CreateWidget<UPrimaryGameLayout>(PlayerController, LayoutWidgetClass, TEXT("PrimaryGameLayout"));

			RootLayout->SetPlayerContext(FLocalPlayerContext(LocalPlayer));
			RootLayout->AddToPlayerScreen(1000);

			// add first front end widget
			AddFrontEndWidget();

			UE_LOG(LogImmutableUI, Log, TEXT("[%s] is adding s]'s root layout [%s] to the viewport"), *GetName(), *GetNameSafe(RootLayout));

	#if WITH_EDITOR
			if (GIsEditor)
			{
				// So our controller will work in PIE without needing to click in the viewport
				FSlateApplication::Get().SetUserFocusToGameViewport(0);
			}
	#endif
		}
	}));
}

void UGameUIPolicy::NotifyPlayerDestroyed(UCustomLocalPlayer* LocalPlayer)
{
	if (!RootLayout)
	{
		return;
	}
	
	RootLayout->RemoveFromParent();
	UE_LOG(LogImmutableUI, Log, TEXT("Removing root layout from the viewport"));
}

void UGameUIPolicy::AddFrontEndWidget()
{
	TSubclassOf<UActivatableWidget> LoadedClass = FrontEndWidgetClass.LoadSynchronous();
	
	if (ensure(LoadedClass && !LoadedClass->HasAnyClassFlags(CLASS_Abstract)))
	{
		RootLayout->PushWidgetToLayerStack(FGameplayTag::RequestGameplayTag(TEXT("UI.Layer.Menu")), LoadedClass);	
	}
}
