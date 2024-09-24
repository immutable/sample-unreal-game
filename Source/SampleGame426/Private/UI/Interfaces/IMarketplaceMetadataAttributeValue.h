#pragma once

#include "UObject/Interface.h"

#include "IMarketplaceMetadataAttributeValue.generated.h"


/**
 * 
 */
UINTERFACE(BlueprintType)
class SAMPLEGAME426_API UMarketplaceMetadataAttributeValue : public UInterface
{
	GENERATED_BODY()
};

class SAMPLEGAME426_API IMarketplaceMetadataAttributeValue
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Immutable")
	void SetValueName(const FString& ValueName);
};
