#include "GameUIPolicy.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

#include "CustomLocalPlayer.h"
#include "LogSampleGame.h"
#include "UI/GameUIManagerSubsystem.h"
#include "UI/Interfaces/IPassportListnerInterface.h"
#include "UI/UIGameplayTags.h"

UGameUIPolicy* UGameUIPolicy::GetGameUIPolicy(const UObject* WorldContextObject)
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

UWorld* UGameUIPolicy::GetWorld() const
{
	return GetOwningUIManager()->GetGameInstance()->GetWorld();
}

UGameUIManagerSubsystem* UGameUIPolicy::GetOwningUIManager() const
{
	return CastChecked<UGameUIManagerSubsystem>(GetOuter());
}

UPrimaryGameLayout* UGameUIPolicy::GetRootLayout() const
{
	return RootLayout;
}

UMarketplacePolicy* UGameUIPolicy::GetMarketplacePolicy() const
{
	return MarketplacePolicy;
}

const FDialogType* UGameUIPolicy::GetDialogType(FGameplayTag DialogTag) const
{
	UDialogTypeDataAsset* Data = DialogTypeDataAsset.LoadSynchronous();

	if (!Data)
	{
		return nullptr;
	}

	return Data->Dialogs.Find(DialogTag);
}

void UGameUIPolicy::ShowThrobber()
{
	if (!ThrobberScreenWidgetClass.IsNull())
	{
		ThrobberScreenWidget = PushWidget(ThrobberScreenWidgetClass, NativeUIGameplayTags.UI_Layer_Modal);
	}
}

void UGameUIPolicy::HideThrobber()
{
	if (ThrobberScreenWidget && ThrobberScreenWidget->IsActivated())
	{
		ThrobberScreenWidget->DeactivateWidget();
	}
}

void UGameUIPolicy::NotifyPlayerAdded(UCustomLocalPlayer* LocalPlayer)
{
	LocalPlayer->CallAndRegister_OnPlayerControllerSet(UCustomLocalPlayer::FPlayerControllerSetDelegate::FDelegate::CreateWeakLambda(this, [this](UCustomLocalPlayer* LocalPlayer, APlayerController* PlayerController)
	{
		TSubclassOf<UPrimaryGameLayout> LayoutWidgetClass = LayoutClass.LoadSynchronous();

		if (ensure(LayoutWidgetClass && !LayoutWidgetClass->HasAnyClassFlags(CLASS_Abstract)))
		{
			RootLayout = CreateWidget<UPrimaryGameLayout>(PlayerController, LayoutWidgetClass);
			RootLayout->SetPlayerContext(FLocalPlayerContext(LocalPlayer));
			RootLayout->AddToPlayerScreen(1000);

			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController);
			PlayerController->SetShowMouseCursor(true);

			UE_LOG(LogSampleGame, Log, TEXT("[%s] is adding s]'s root layout [%s] to the viewport"), *GetName(), *GetNameSafe(RootLayout));

			// add login screen widget as an initial screen
			if (!LoginScreenWidgetClass.IsNull())
			{
				LoginScreenWidget = Cast<ULoginScreenWidget>(PushWidget(LoginScreenWidgetClass, NativeUIGameplayTags.UI_Layer_Menu));
			}

#if WITH_EDITOR
			if (GIsEditor)
			{
				// So our controller will work in PIE without needing to click in the viewport
				FSlateApplication::Get().SetUserFocusToGameViewport(0);
			}
#endif
		}
	}));

	LocalPlayer->CallAndRegister_OnPassportInitialized(UCustomLocalPlayer::FPlayerPassportInitializedDelegates::FDelegate::CreateWeakLambda(this, [this](bool IsInitialized)
	{
		if (LoginScreenWidget && LoginScreenWidget->GetClass()->ImplementsInterface(UPassportListenerInterface::StaticClass()))
		{
			IPassportListenerInterface::Execute_OnPassportInitialized(LoginScreenWidget, IsInitialized);
		}
	}));

	LocalPlayer->CallAndRegister_OnPlayerLoggedIn(UCustomLocalPlayer::FPlayerLoggedInDelegate::FDelegate::CreateWeakLambda(this, [this](bool IsLoggedIn)
	{
		if (LoginScreenWidget && LoginScreenWidget->GetClass()->ImplementsInterface(UPassportListenerInterface::StaticClass()))
		{
			IPassportListenerInterface::Execute_OnPassportLoggedIn(LoginScreenWidget, IsLoggedIn);
		}
	}));

	LocalPlayer->CallAndRegister_OnPlayerPassportDataObtained(UCustomLocalPlayer::FPlayerPassportDataObtained::FDelegate::CreateWeakLambda(this, [this]()
	{
		if (LoginScreenWidget && LoginScreenWidget->GetClass()->ImplementsInterface(UPassportListenerInterface::StaticClass()))
		{
			IPassportListenerInterface::Execute_OnPassportDataObtained(LoginScreenWidget);
		}

		// create marketplace policy
		if (!MarketplacePolicyClass.IsNull())
		{
			MarketplacePolicy = NewObject<UMarketplacePolicy>(this, MarketplacePolicyClass.LoadSynchronous());
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

UActivatableWidget* UGameUIPolicy::PushWidget(TSoftClassPtr<UActivatableWidget> WidgetClassPtr, FGameplayTag LayerTag)
{
	TSubclassOf<UActivatableWidget> LoadedClass = WidgetClassPtr.LoadSynchronous();

	if (ensure(LoadedClass && !LoadedClass->HasAnyClassFlags(CLASS_Abstract)))
	{
		return RootLayout->PushWidgetToLayerStack(LayerTag, LoadedClass);
	}
	else
	{
		UE_LOG(LogSampleGame, Error, TEXT("Widget class is not assigned."));
		return nullptr;
	}
}