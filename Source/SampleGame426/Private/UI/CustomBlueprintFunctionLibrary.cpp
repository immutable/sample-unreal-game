#include "CustomBlueprintFunctionLibrary.h"

#include "Dialog/DialogSubsystem.h"
#include "UI/GameUIManagerSubsystem.h"
#include "UI/UIGameplayTags.h"
#include "LogSampleGame.h"

void UCustomBlueprintFunctionLibrary::LogError(const FString& ErrorMessage)
{
	UE_LOG(LogSampleGame, Error, TEXT("Outside of source code: %s"), *ErrorMessage)
}

void UCustomBlueprintFunctionLibrary::ShowThrobber(const ULocalPlayer* LocalPlayer)
{
	if (!LocalPlayer)
	{
		//UE_LOG ERROR
		return;
	}

	if (UGameUIManagerSubsystem* UIManager = LocalPlayer->GetGameInstance()->GetSubsystem<UGameUIManagerSubsystem>())
	{
		if (UGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
		{
			Policy->ShowThrobber();
		}
	}
}

void UCustomBlueprintFunctionLibrary::HideThrobber(const ULocalPlayer* LocalPlayer)
{
	if (!LocalPlayer)
	{
		//UE_LOG ERROR
		return;
	}

	if (UGameUIManagerSubsystem* UIManager = LocalPlayer->GetGameInstance()->GetSubsystem<UGameUIManagerSubsystem>())
	{
		if (UGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
		{
			Policy->HideThrobber();
		}
	}
}

void UCustomBlueprintFunctionLibrary::ShowOnRampWidget(const ULocalPlayer* LocalPlayer)
{
	if (!LocalPlayer)
	{
		UE_LOG(LogSampleGame, Error, TEXT("LocalPlayer is null"));

		return;
	}

	if (UDialogSubsystem* DialogSubsystem = LocalPlayer->GetSubsystem<UDialogSubsystem>())
	{
		DialogSubsystem->ShowDialog(NativeUIGameplayTags.UI_Dialog_OnRamp, UDialogSubsystem::CreateOnRampDescriptor());
	}
}