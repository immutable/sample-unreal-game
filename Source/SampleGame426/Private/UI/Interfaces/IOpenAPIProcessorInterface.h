#pragma once

#include "ImmutableOpenAPI/Public/OpenAPIBaseModel.h"
#include "UObject/Interface.h"

#include "IOpenAPIProcessorInterface.generated.h"


/**
 * 
 */
UINTERFACE()
class SAMPLEGAME426_API UMarketplaceOpenAPIProcessorInterface : public UInterface
{
	GENERATED_BODY()
};

class SAMPLEGAME426_API IMarketplaceOpenAPIProcessorInterface
{
	GENERATED_BODY()

public:
	/**  */
	virtual void ProcessModel(const ImmutableOpenAPI::Model& Data) = 0;
	
};


UINTERFACE()
class SAMPLEGAME426_API UInventoryOpenAPIProcessorInterface : public UInterface
{
	GENERATED_BODY()
};

class SAMPLEGAME426_API IInventoryOpenAPIProcessorInterface
{
	GENERATED_BODY()

public:
	/**  */
	virtual void ProcessModel(const ImmutableOpenAPI::Model& Data) = 0;
};
