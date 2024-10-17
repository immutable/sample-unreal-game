#pragma once

#include "CustomUserWidget.h"

#include "AWStackTopControlPanel.generated.h"


/**
 * 
 */
UCLASS(Abstract)
class SAMPLEGAME426_API UAWStackTopControlPanel : public UCustomUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void SetTitle(const FString& WidgetTitle);
};
