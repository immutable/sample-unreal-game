#pragma once

#include "Blueprint/UserWidget.h"

#include "MarketplaceListingsItemWidget.generated.h"


UCLASS(Abstract, Blueprintable)
class SAMPLEGAME426_API UMarketplaceListingsItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void OnProcessPrice(const FString& TokenID, const FString& Amount, const FString& FeeProtocol, const FString& FeeRoyalty, const FString& Price, const FString& Currency, bool IsToBuy = true);
	
};
