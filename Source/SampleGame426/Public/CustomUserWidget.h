
#pragma once

#include "Blueprint/UserWidget.h"

#include "CustomUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEGAME426_API UCustomUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Widget")
	virtual class UCustomLocalPlayer* GetOwningCustomLocalPLayer() const;
};
