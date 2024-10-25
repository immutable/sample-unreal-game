#pragma once

#include "GameFramework/GameModeBase.h"
#include "GameUIPolicy.h"

#include "CustomGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEGAME426_API ACustomGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void InitializeHUDForPlayer_Implementation(APlayerController* NewPlayer) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes", Meta = (DisplayName = "UI Policy Class"))
	TSoftClassPtr<UGameUIPolicy> UIPolicyClass;
};
