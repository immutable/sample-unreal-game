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
	virtual void ProcessModel(const ImmutableOpenAPI::Model& Data) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void AddDescriptionRecord(const FString& Name, const FString& Value);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void AddMetadataAttribute(const FString& Name, const FString& Value);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void SetThumbnail(const FString& Name);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void SetName(const FString& Name);
	
protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UMarketplaceListingsWidget* Listings = nullptr;
	
};
