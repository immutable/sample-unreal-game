#pragma once

#include "OpenAPIOrderbookApi.h"
#include "Base/ActivatableWidgetWithControlPanels.h"
#include "UI/Interfaces/IOpenAPIProcessorInterface.h"

#include "SearchStacksListingWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SAMPLEGAME426_API USearchStacksListingWidget : public UActivatableWidgetWithControlPanels, public IMarketplaceOpenAPIProcessorInterface
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual void SetupControlButtons(class UAWStackWithControlPanels* HostPanel) override;
	virtual void ProcessModel(const ImmutableOpenAPI::Model& Data) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void AddDescriptionRecord(const FString& Name, const FString& Value);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void AddMetadataAttribute(const FString& Name, const FString& Value);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void SetThumbnail(UTexture2D* Thumbnail);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void SetName(const FString& Name);

private:
	void OnSelectionStatusChange(bool IsAnyItemSelected);
	void OnFulfillOrder(const ImmutableTsSdkApi::OpenAPIOrderbookApi::FulfillOrderResponse& Response);
	UFUNCTION()
	void OnBuyButtonClicked(FGameplayTag ButtonTag);
	UFUNCTION()
	void OnProcessDialogAction(UDialog* DialogPtr, EDialogResult Result);
	
protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class USearchStacksListing_ListingsWidget* Listings = nullptr;

	UControlPanelButton* BuyButton = nullptr;
	UDialog* ProcessingDialog = nullptr;
};
