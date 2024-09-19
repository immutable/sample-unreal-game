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

USTRUCT(BlueprintType)
struct SAMPLEGAME426_API FNFTMetadataAttribute_TraitType
{
	GENERATED_BODY()
		
	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	TArray<FString> Values;
};


UCLASS()
class SAMPLEGAME426_API UNFTMetadataAttributeDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FNFTMetadataAttribute_TraitType> TraitType;
	 
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ENFTMetadataAttribute_DisplayType> DisplayType; 
};
