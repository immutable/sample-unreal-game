#include "CustomBlueprintFunctionLibrary.h"

#include "LogSampleGame.h"
#include "UIGameplayTags.h"
#include "Dialog/DialogSubsystem.h"
#include "UI/Data/NFTMetadataAttributeDataAsset.h"
#include "UI/GameUIManagerSubsystem.h"


FNFTMetadataAttribute_TraitType UCustomBlueprintFunctionLibrary::MakeNFTMetadataAttribute_TraitType(FString TraitType, TArray<FString> Values)
{
	return FNFTMetadataAttribute_TraitType({TraitType, Values});
}

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

void UCustomBlueprintFunctionLibrary::ShowTransakWidget(const ULocalPlayer* LocalPlayer)
{
	if (!LocalPlayer)
	{
		UE_LOG(LogSampleGame, Error, TEXT("LocalPlayer is null"));
		
		return;
	}

	if (UDialogSubsystem* DialogSubsystem = LocalPlayer->GetSubsystem<UDialogSubsystem>())
	{
		DialogSubsystem->ShowDialog(NativeUIGameplayTags.UI_Dialog_Transak, UDialogSubsystem::CreateTransakDescriptor());
	}
}
