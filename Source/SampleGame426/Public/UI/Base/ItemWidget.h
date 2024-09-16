#pragma once

#include "Blueprint/UserWidget.h"

#include "ItemWidget.generated.h"


namespace OpenAPI
{
	class Model;
}

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class SAMPLEGAME426_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void ProcessModel(const OpenAPI::Model* Data) {};

};
