#pragma once

#include "Base/ActivatableWidgetWithControlPanels.h"
#include "Marketplace/SearchStacksContractSelectItemWidget.h"
#include "Base/ControlPanelButton.h"

#include "SearchStacksContractSelectWidget.generated.h"


class UGridPanel;

/**
 * 
 */
UCLASS(Abstract)
class SAMPLEGAME426_API USearchStacksContractSelectWidget : public UActivatableWidgetWithControlPanels
{
	GENERATED_BODY()

protected:
	// Item selection handler
	void ItemSelectionChange(bool IsSelected, UItemWidget* ItemWidget);
	// Item selection handler
	void OnItemSelectionChange(bool IsSelected, UItemWidget* ItemWidget);
	// Item double click handler
	void OnItemDoubleClick(UItemWidget* InItemWidget);

	/* UActivatableWidgetWithControlPanels interface */
	virtual void SetupControlButtons(class UAWStackWithControlPanels* HostLayer) override;
	virtual void Refresh() override;
	/* UActivatableWidgetWithControlPanels interface */

private:
	void LoadContracts();

protected:
	UPROPERTY(EditAnywhere, Category = "Marketplace")
	TSoftClassPtr<class USearchStacksContractSelectItemWidget> ItemWidgetClass;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UGridPanel* GridPanel = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* FiltersButton = nullptr;

private:
	UPROPERTY()
	UItemWidget* SelectedItemWidget = nullptr;
	
};
