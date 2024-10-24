#pragma once

#include "Blueprint/UserWidget.h"

#include "CustomUserWidget.generated.h"

class UCustomLocalPlayer;

/**
 * @class UCustomUserWidget
 * @brief A user widget with additional wrapper functionality
 */
UCLASS()
class SAMPLEGAME426_API UCustomUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Widget")
	virtual UCustomLocalPlayer* GetOwningCustomLocalPLayer() const;
};