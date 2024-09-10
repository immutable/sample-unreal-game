#pragma once

#include "GameFramework/PlayerController.h"

#include "CustomPlayerController.generated.h"

class UObject;

/**
 *
 *  
 */
UCLASS(Blueprintable)
class SAMPLEGAME426_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	//~ Begin APlayerController interface
	virtual void ReceivedPlayer() override;
	//~ End APlayerController interface
};
