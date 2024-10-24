#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "Data/NFTMetadataAttributeDataAsset.h"

#include "UIBlueprintFunctionLibrary.generated.h"

UCLASS()
class SAMPLEGAME426_API UUIBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Immutable Marketplace", meta = (NativeMakeFunc))
	static FNFTMetadataAttribute_TraitType MakeNFTMetadataAttribute_TraitType(FString TraitType, TArray<FString> Values);

	UFUNCTION(BlueprintCallable, Category = "Immutable Utility")
	static void LogError(const FString& ErrorMessage);

	UFUNCTION(BlueprintCallable, Category = "Immutable Utility")
	static void ShowThrobber(const ULocalPlayer* LocalPlayer);

	UFUNCTION(BlueprintCallable, Category = "Immutable Utility")
	static void HideThrobber(const ULocalPlayer* LocalPlayer);
};