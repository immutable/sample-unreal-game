#pragma once

#include "Engine/DataAsset.h"

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

/**
 * @struct FNFTMetadataAttribute_TraitType
 * @brief A structure to encapsulate NFT Metadata Attribute Trait Type
 */
USTRUCT(BlueprintType, Meta = (HasNativeMake = "/Script/SampleGame426.NFTMetadataAttribute_TraitTypeStatics.MakeNFTMetadataAttribute_TraitType"))
struct SAMPLEGAME426_API FNFTMetadataAttribute_TraitType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	TArray<FString> Values;
};

UCLASS()
class SAMPLEGAME426_API UNFTMetadataAttribute_TraitTypeStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Immutable|Marketplace", Meta = (NativeMakeFunc))
	static FNFTMetadataAttribute_TraitType MakeNFTMetadataAttribute_TraitType(const FString& TraitType, const TArray<FString>& Values);
};

/**
 * @class UNFTMetadataAttributeDataAsset
 * @brief Data asset for NFT Metadata Attributes
 */
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