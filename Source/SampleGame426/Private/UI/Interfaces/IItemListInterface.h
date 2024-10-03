
#pragma once

#include "UObject/Interface.h"

#include "IItemListInterface.generated.h"

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
	virtual void RefreshItemList(TOptional<FString> PageCursor) = 0;
};
