#pragma once

#include "NFTMetadataAttributeDataAsset.h"
#include "Base/ActivatableWidget.h"
#include "UI/Interfaces/IMarketplaceMetadataAttribute.h"
#include "UI/Interfaces/IMarketplaceMetadataAttributeValue.h"

#include "MarketplaceSearchOptionWidget.generated.h"


UCLASS(Abstract)
class SAMPLEGAME426_API UMarketplaceSearchOptionWidget : public UActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnActivated() override;

	UFUNCTION(BlueprintImplementableEvent)
	void AddMetadataFilter(const FString& Name, const TArray<FString>& Values);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Metadata")
	TSoftObjectPtr<UNFTMetadataAttributeDataAsset> AttributeMetadata;
	
};