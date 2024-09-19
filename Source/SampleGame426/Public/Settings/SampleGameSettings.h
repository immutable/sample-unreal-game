#pragma once

#include "Engine/DeveloperSettings.h"
#include "Marketplace/NFTMetadataAttributeDataAsset.h"

#include "SampleGameSettings.generated.h"


/**
 * Game project settings
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Immutable Sample Game Settings"))
class SAMPLEGAME426_API USampleGameSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	// Passport values:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Passport")
	FString ClientID;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Passport")
	FString Environment;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Passport")
	FString RedirectURI;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Passport")
	FString LogoutURI;

	// Online values:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Marketplace|Search NFT stacks")
	TArray<FString> ContractAddress;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Marketplace|Search NFT stacks")
	TSoftObjectPtr<UNFTMetadataAttributeDataAsset> SearchMetaAttributes;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Marketplace|Search NFT stacks")
	int32 NumberFractionalDigits = 4;
	
};
