#pragma once

#include "OpenAPIOrderbookApi.h"
#include "Base/ActivatableWidgetWithControlPanels.h"
#include "Base/ItemWidget.h"
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
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	virtual void SetupControlButtons(class UAWStackWithControlPanels* HostLayer) override;
	virtual void ProcessModel(const ImmutableOpenAPI::Model& Data) override;
	virtual void Refresh() override;

protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void AddDescriptionRecord(const FString& Name, const FString& Value);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void AddMetadataAttribute(const FString& Name, const FString& Value);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void SetThumbnail(UTexture2D* Thumbnail);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void SetName(const FString& Name);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void BP_Reset();

private:
	void OnItemSelectionStatusChange(bool IsItemSelected, UItemWidget* ItemWidget);
	void OnFulfillOrder(const ImmutableTsSdkApi::OpenAPIOrderbookApi::FulfillOrderResponse& Response);
	void OnBuyButtonClicked(FGameplayTag ButtonTag);
	UFUNCTION()
	void OnProcessDialogAction(UDialog* DialogPtr, EDialogResult Result);
	
protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class USearchStacksListing_ListingsWidget* Listings = nullptr;

	UItemWidget* SelectedItem = nullptr;
	UControlPanelButton* BuyButton = nullptr;
	UDialog* ProcessingDialog = nullptr;
};
