
#pragma once

#include "OpenAPIBaseModel.h"
#include "UObject/Interface.h"

#include "IOpenAPIProcessorInterface.generated.h"


/**
 * 
 */
UINTERFACE()
class SAMPLEGAME426_API UOpenAPIProcessorInterface : public UInterface
{
	GENERATED_BODY()
};

class SAMPLEGAME426_API IOpenAPIProcessorInterface
{
	GENERATED_BODY()

public:
	/**  */
	virtual void ProcessModel(const OpenAPI::Model* Data) = 0;
};
