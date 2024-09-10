#pragma once

#include "Engine/DeveloperSettings.h"

#include "GameSettings.generated.h"


/**
 * Game project settings
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Immutable Game Settings"))
class SAMPLEGAME426_API UGameSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Passport")
	FString ClientID;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Passport")
	FString Environment;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Passport")
	FString RedirectURI;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Passport")
	FString LogoutURI;
};
