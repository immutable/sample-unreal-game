#pragma once

#include "NFTMetadataAttributeDataAsset.generated.h"


// enum class DisplayTypeEnum
// {
// 	Number,
// 	BoostPercentage,
// 	BoostNumber,
// 	Date,
//   };

UENUM()
enum ENFTMetadataAttribute_DisplayType
{
	Number				UMETA(DisplayName="Number"),
	BoostPercentage		UMETA(DisplayName="Boost Percentage"),
	BoostNumber			UMETA(DisplayName="Boost Number"),
	Date				UMETA(DisplayName="Date"),
	Custom				UMETA(DisplayName="Custom"),
};

USTRUCT(BlueprintType, meta=(HasNativeMake="/Script/SampleGame426.UI.UIBlueprintFunctionLibrary.MakeNFTMetadataAttribute_TraitType"))
struct SAMPLEGAME426_API FNFTMetadataAttribute_TraitType
{
	GENERATED_BODY()
		
	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	TArray<FString> Values;
};

UCLASS(BlueprintType, Const)
class SAMPLEGAME426_API UNFTMetadataAttributeDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Immutable Marketplace")
	TArray<FNFTMetadataAttribute_TraitType> TraitType;
	 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Immutable Marketplace")
	TEnumAsByte<ENFTMetadataAttribute_DisplayType> DisplayType; 
};
