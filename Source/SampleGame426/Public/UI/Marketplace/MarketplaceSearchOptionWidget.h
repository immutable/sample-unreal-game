#pragma once

#include "Base/ActivatableWidgetWithControls.h"
#include "Data/NFTMetadataAttributeDataAsset.h"

#include "MarketplaceSearchOptionWidget.generated.h"


UCLASS(Abstract)
class SAMPLEGAME426_API UMarketplaceSearchOptionWidget : public UActivatableWidgetWithControls
{
	GENERATED_BODY()

public:
	virtual void NativeOnActivated() override;

	UFUNCTION(BlueprintImplementableEvent)
	void AddMetadataFilter(const FString& Name, const TArray<FString>& Values);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void SetKeyword(const FString& Keyword);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void SetTraits(const TArray<FNFTMetadataAttribute_TraitType>& Traits);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Metadata")
	TSoftObjectPtr<UNFTMetadataAttributeDataAsset> AttributeMetadata;
	
};