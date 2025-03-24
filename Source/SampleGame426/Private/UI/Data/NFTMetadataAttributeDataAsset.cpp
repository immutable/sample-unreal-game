#include "UI/Data/NFTMetadataAttributeDataAsset.h"

FNFTMetadataAttribute_TraitType UNFTMetadataAttribute_TraitTypeStatics::MakeNFTMetadataAttribute_TraitType(const FString& TraitType, const TArray<FString>& Values)
{
	return FNFTMetadataAttribute_TraitType
	{
		TraitType,
		Values
	};
}