#pragma once

#include "OpenAPIPage.h"
#include "OpenAPIStacksApi.h"
#include "OpenAPIStacksApiOperations.h"
#include "Base/ActivatableWidgetWithControlPanels.h"
#include "Base/ItemListWidget.h"
#include "UI/Interfaces/IItemListInterface.h"

#include "SearchStacksWidget.generated.h"

UENUM()
enum class ESearchStacks_SortCategories : uint8
{
	Price
};


/*
 * 
 */
UCLASS(Abstract)
class SAMPLEGAME426_API USearchStacksWidget : public UActivatableWidgetWithControlPanels, public IItemListInterface
{
	GENERATED_BODY()

public:
	virtual void RefreshItemList(TOptional<FString> PageCursor) override;
	UItemWidget* GetSelectedItem() const { return SelectedItemWidget; }

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure)
	ESearchStacks_SortCategories GetSortCategory();
	UFUNCTION(BlueprintImplementableEvent, BlueprintPure)
	bool GetSortOrder();

	virtual void Refresh() override;

protected:
	/* UActivatableWidget */
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	virtual void OnWidgetRebuilt() override;
	/* UActivatableWidget */

	void OnSearchStacksResponse(const ImmutableOpenAPI::OpenAPIStacksApi::SearchStacksResponse& Response);
	virtual void SetupControlButtons(class UAWStackWithControlPanels* HostLayer) override;

private:
	void HandlePageData(const ImmutableOpenAPI::OpenAPIPage& PageData);
	void HandleSorting(TOptional<ImmutableOpenAPI::OpenAPIStacksApi::SearchStacksRequest::SortByEnum>& Sorting);
	void ItemSelectionChange(bool IsSelected, UItemWidget* ItemWidget);
	void OnControlButtonClicked(FGameplayTag ButtonTag);
	void OnItemSelectionChange(bool IsSelected, UItemWidget* ItemWidget);
	void OnItemDoubleClick(UItemWidget* InItemWidget);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UItemListWidget* ListPanel = nullptr;
	UPROPERTY(EditAnywhere, Category = "Marketplace")
	TSoftClassPtr<class USearchStacksListingWidget> SearchStacksListingWidgetClass;

private:
	ImmutableOpenAPI::OpenAPIPage PageCursors;
	UItemWidget* SelectedItemWidget = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* PreviousPageButton = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* NextPageButton = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* NFTInfoButton = nullptr;
	
};
