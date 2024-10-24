#include "UIBlueprintFunctionLibrary.h"

#include "LogSampleGame.h"
#include "UI/Data/NFTMetadataAttributeDataAsset.h"
#include "UI/GameUIManagerSubsystem.h"

FNFTMetadataAttribute_TraitType UUIBlueprintFunctionLibrary::MakeNFTMetadataAttribute_TraitType(FString TraitType, TArray<FString> Values)
{
	return FNFTMetadataAttribute_TraitType({TraitType, Values});
}

void UUIBlueprintFunctionLibrary::LogError(const FString& ErrorMessage)
{
	UE_LOG(LogSampleGame, Error, TEXT("Outside of source code: %s"), *ErrorMessage)
}

void UUIBlueprintFunctionLibrary::ShowThrobber(const ULocalPlayer* LocalPlayer)
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

void UUIBlueprintFunctionLibrary::HideThrobber(const ULocalPlayer* LocalPlayer)
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