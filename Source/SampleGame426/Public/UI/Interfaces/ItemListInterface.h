
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"
#include "UObject/Interface.h"

#include "ItemListInterface.generated.h"

/**
 * 
 */
UINTERFACE(meta = (CannotImplementInterfaceInBlueprint))
class SAMPLEGAME426_API UItemListInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class SAMPLEGAME426_API IItemListInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	/**  */
	virtual void RefreshItemList() = 0;;
};
