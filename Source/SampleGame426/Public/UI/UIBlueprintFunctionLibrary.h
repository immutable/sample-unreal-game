#pragma once

#include "Data/NFTMetadataAttributeDataAsset.h"
#include "Dialog/Dialog.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "UIBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEGAME426_API UUIBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Immutable Marketplace", meta = (NativeMakeFunc))
	static FNFTMetadataAttribute_TraitType MakeNFTMetadataAttribute_TraitType(FString TraitType, TArray<FString> Values);
};
