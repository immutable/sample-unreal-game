#pragma once

#include "Base/ItemWidget.h"
#include "UI/Interfaces/IOpenAPIProcessorInterface.h"

#include "SearchNFTsItemWidget.generated.h"


namespace ImmutableIndexerSearchAPI
{
	class OpenAPINFTBundle;
}

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class SAMPLEGAME426_API USearchNFTsItemWidget : public UItemWidget, public IInventoryOpenAPIProcessorInterface
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual void ProcessModel(const ImmutableIndexerSearchAPI::Model& Data) override;

	DECLARE_DELEGATE_TwoParams(FOnSearchNFTsItemWidgetSelection, bool /* IsSelected */, USearchNFTsItemWidget* /* SearchNFTsItemWidget */)
	
	void RegisterOnSelection(const FOnSearchNFTsItemWidgetSelection& SelectionDelegate);

	FString GetTokenId() const;
	FString GetContractAddress() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void BP_OnSelectButtonClick(bool IsSelected);

protected:
	void SetTextureNFT(TSoftObjectPtr<UTexture2D> Texture);
	void SetName(const FString& Name);
	void SetBalance(int32 Balance);

private:
	UFUNCTION()
	void OnSelectButtonClicked();

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UButton* SelectButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta=(BindWidget))
	class UTextBlock* NFTName = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta=(BindWidget))
	class UImage* NFTThumbnail  = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory", meta=(BindWidget))
	class UTextBlock* NFTBalance  = nullptr;
	UPROPERTY(BlueprintReadOnly)
	bool IsItemSelected = false;
	
private:
	TSharedPtr<ImmutableIndexerSearchAPI::OpenAPINFTBundle> NFTBundle;
	FOnSearchNFTsItemWidgetSelection OnSearchNFTsItemWidgetSelectionDelegate;
	
};
