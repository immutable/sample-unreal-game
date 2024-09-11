#include "GameUIPolicy.h"

#include "CustomLocalPlayer.h"
#include "GameUIManagerSubsystem.h"
#include "LogSampleGame.h"
#include "LogSampleGame.h"


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

			// add login screen widget as an initial screen
			PushWidget(LoginScreenWidgetClass);

			UE_LOG(LogSampleGame, Log, TEXT("[%s] is adding s]'s root layout [%s] to the viewport"), *GetName(), *GetNameSafe(RootLayout));

	#if WITH_EDITOR
			if (GIsEditor)
			{
				// So our controller will work in PIE without needing to click in the viewport
				FSlateApplication::Get().SetUserFocusToGameViewport(0);
			}
	#endif
		}
	}));

	LocalPlayer->CallAndRegister_OnPlayerLoggedIn(UCustomLocalPlayer::FPlayerLoggedInDelegate::FDelegate::CreateWeakLambda(this, [this](bool IsLoggedIn)
	{
		if (IsLoggedIn)
		{
			PushWidget(FrontEndWidgetClass);
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
	UE_LOG(LogSampleGame, Log, TEXT("Removing root layout from the viewport"));
}

void UGameUIPolicy::PushWidget(TSoftClassPtr<UActivatableWidget> WidgetClassPtr)
{
	TSubclassOf<UActivatableWidget> LoadedClass = WidgetClassPtr.LoadSynchronous();
	
	if (ensure(LoadedClass && !LoadedClass->HasAnyClassFlags(CLASS_Abstract)))
	{
		RootLayout->PushWidgetToLayerStack(FGameplayTag::RequestGameplayTag(TEXT("UI.Layer.Menu")), LoadedClass);	
	}
	else
	{
		UE_LOG(LogSampleGame, Error, TEXT("Widget class is not assigned."));
	}
}
