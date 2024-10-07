#pragma once

#include "UObject/Interface.h"

#include "IPassportListnerInterface.generated.h"

/**
 * 
 */
UINTERFACE(BlueprintType)
class SAMPLEGAME426_API UPassportListenerInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class SAMPLEGAME426_API IPassportListenerInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	/**  */
	UFUNCTION(BlueprintImplementableEvent, Category = Immutable)
	void OnPassportInitialized();

	UFUNCTION(BlueprintImplementableEvent, Category = Immutable)
	void OnPassportLoggedIn();

	UFUNCTION(BlueprintImplementableEvent, Category = Immutable)
	void OnPassportLoggedOut();
};
