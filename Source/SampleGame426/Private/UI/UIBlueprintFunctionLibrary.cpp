#include "UIBlueprintFunctionLibrary.h"

#include "Data/NFTMetadataAttributeDataAsset.h"


FNFTMetadataAttribute_TraitType UUIBlueprintFunctionLibrary::MakeNFTMetadataAttribute_TraitType(FString TraitType, TArray<FString> Values)
{
	return FNFTMetadataAttribute_TraitType({ TraitType, Values } );
}
