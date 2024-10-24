#pragma once

#include "GameFramework/PlayerController.h"

#include "CustomPlayerController.generated.h"

UCLASS(Blueprintable)
class SAMPLEGAME426_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/** APlayerController: Interface Begin */
	virtual void ReceivedPlayer() override;
	/** APlayerController: Interface End */
};