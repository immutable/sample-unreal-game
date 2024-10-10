#pragma once

#include "CustomUserWidget.h"

#include "ItemWidget.generated.h"


/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class SAMPLEGAME426_API UItemWidget : public UCustomUserWidget
{
	GENERATED_BODY()

public:
	virtual void SetOriginalState();

protected:
	virtual bool Initialize() override; 

};
