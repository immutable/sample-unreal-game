// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SampleGame426GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEGAME426_API ASampleGame426GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	
};
