#include "CustomLocalPlayer.h"

#include "GameUIManagerSubsystem.h"
#include "LogSampleGame.h"
#include "Immutable/ImmutableDataTypes.h"
#include "Immutable/ImmutablePassport.h"
#include "Immutable/ImmutableSubsystem.h"
#include "Settings/SampleGameSettings.h"

UCustomLocalPlayer::UCustomLocalPlayer()
	: Super(FObjectInitializer::Get())
{
}

FDelegateHandle UCustomLocalPlayer::CallAndRegister_OnPlayerControllerSet(FPlayerControllerSetDelegate::FDelegate Delegate)
{
	APlayerController* PC = GetPlayerController(GetWorld());

	if (PC)
	{
		Delegate.Execute(this, PC);
	}

	return OnPlayerControllerSet.Add(Delegate);
}

FDelegateHandle UCustomLocalPlayer::CallAndRegister_OnPlayerLoggedIn(FPlayerLoggedInDelegate::FDelegate Delegate)
{
	return OnPlayerLoggedIn.Add(Delegate);
}

FDelegateHandle UCustomLocalPlayer::CallAndRegister_OnPlayerPassportIsRunning(
	FPlayerPassportIsRunningDelegate::FDelegate Delegate)
{
	return OnPlayerPassportIsRunning.Add(Delegate);
}

void UCustomLocalPlayer::PlayerAdded(class UGameViewportClient* InViewportClient, int32 InControllerID)
{
	Super::PlayerAdded(InViewportClient, InControllerID);

	InitializePassport();
}

void UCustomLocalPlayer::LoginPassport()
{
	if (Passport.IsValid())
	{
		Passport->Connect(true, true, UImmutablePassport::FImtblPassportResponseDelegate::CreateUObject(this, &UCustomLocalPlayer::OnPassportLoggedIn));
	}
}

UPrimaryGameLayout* UCustomLocalPlayer::GetRootUILayout() const
{
	if (UGameUIManagerSubsystem* UIManager = GetGameInstance()->GetSubsystem<UGameUIManagerSubsystem>())
	{
		if (UGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
		{
			return Policy->GetRootLayout();
		}
	}

	return nullptr;
}

void UCustomLocalPlayer::InitializePassport()
{
	auto ImmutableSubsystem = GetGameInstance()->GetSubsystem<UImmutableSubsystem>();

	if (ImmutableSubsystem)
	{
		ImmutableSubsystem->WhenReady(this, &UCustomLocalPlayer::OnPassportIsRunning);
	}
}

void UCustomLocalPlayer::OnPassportIsRunning(TWeakObjectPtr<class UImtblJSConnector> JSConnector)
{
	auto Settings = GetDefault<USampleGameSettings>();

	if (!Settings)
	{
		// TODO Handle system error
		return;
	}
	
	auto ImmutableSubsystem = GetGameInstance()->GetSubsystem<UImmutableSubsystem>();
	Passport = ImmutableSubsystem->GetPassport();
		
	if (Passport.IsValid())
	{
		FImmutablePassportInitData Data;

		Data.clientId = Settings->ClientID;
		Data.logoutRedirectUri = Settings->RedirectURI;
		Data.logoutRedirectUri = Settings->LogoutURI;
		Data.environment = Settings->Environment;
			
		Passport->Initialize(Data, UImmutablePassport::FImtblPassportResponseDelegate::CreateUObject(this, &UCustomLocalPlayer::OnPassportInitialized));
	}	
}

void UCustomLocalPlayer::OnPassportInitialized(FImmutablePassportResult Result)
{
	if (Result.Success)
	{
		UE_LOG(LogSampleGame, Log, TEXT("Immutable Passport initialized successfully"));
		OnPlayerPassportIsRunning.Broadcast();
	}
	else
	{
		// TODO Handle system error
		UE_LOG(LogSampleGame, Log, TEXT("Immutable Passport is not initialized with error: %s"), *Result.Error);
	}
}

void UCustomLocalPlayer::OnPassportLoggedIn(struct FImmutablePassportResult Result)
{
	OnPlayerLoggedIn.Broadcast(Result.Success);
	if (!Result.Success)
	{
		//TODO Handle system error	
	}
}
