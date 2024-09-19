#pragma once

#include "Base/ActivatableWidget.h"
#include "UI/Interfaces/IOpenAPIProcessorInterface.h"

#include "MarketplaceItemFullWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SAMPLEGAME426_API UMarketplaceItemFullWidget : public UActivatableWidget, public IOpenAPIProcessorInterface
{
	GENERATED_BODY()

public:
	virtual void ProcessModel(const OpenAPI::Model* Data) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void OnProcessModel();
	

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UMarketplaceListingsWidget* Listings = nullptr;
	
};
