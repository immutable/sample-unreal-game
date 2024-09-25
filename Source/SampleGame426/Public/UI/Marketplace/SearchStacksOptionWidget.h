#pragma once

#include "Base/ActivatableWidgetWithControlPanels.h"
#include "Data/NFTMetadataAttributeDataAsset.h"

#include "SearchStacksOptionWidget.generated.h"


UCLASS(Abstract)
class SAMPLEGAME426_API USearchStacksOptionWidget : public UActivatableWidgetWithControlPanels
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

private:
	// UFUNCTION()
	// virtual void OnForwardButtonClicked(FGameplayTag ButtonTag) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Metadata")
	TSoftObjectPtr<UNFTMetadataAttributeDataAsset> AttributeMetadata;
	
};