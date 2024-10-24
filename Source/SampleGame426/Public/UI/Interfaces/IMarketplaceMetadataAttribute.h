#pragma once

#include "UObject/Interface.h"

#include "IMarketplaceMetadataAttribute.generated.h"

UINTERFACE(BlueprintType)
class SAMPLEGAME426_API UMarketplaceMetadataAttribute : public UInterface
{
	GENERATED_BODY()
};

class SAMPLEGAME426_API IMarketplaceMetadataAttribute
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Immutable")
	void SetTraitName(const FString& TraitName);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Immutable")
	void AddValue(const FString& ValueName);
};