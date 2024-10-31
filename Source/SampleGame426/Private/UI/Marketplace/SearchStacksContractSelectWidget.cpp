#include "Marketplace/SearchStacksContractSelectWidget.h"

#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "UIGameplayTags.h"
#include "Base/AWStackWithControlPanels.h"
#include "Base/ItemWidget.h"
#include "Components/GridPanel.h"
#include "Marketplace/MarketplacePolicy.h"


void USearchStacksContractSelectWidget::OnItemSelectionChange(bool IsSelected, UItemWidget* ItemWidget)
{
	ItemSelectionChange(IsSelected, ItemWidget);
}

void USearchStacksContractSelectWidget::OnItemDoubleClick(UItemWidget* InItemWidget)
{
	ItemSelectionChange(true, InItemWidget);
	
	if (FiltersButton)
	{
		FiltersButton->ExecuteOnClick();	
	}
}

void USearchStacksContractSelectWidget::SetupControlButtons(class UAWStackWithControlPanels* HostLayer)
{
	Super::SetupControlButtons(HostLayer);

	FiltersButton = HostLayer->AddButton(NativeUIGameplayTags.UI_ControlPanel_Button_Filters);

	if (FiltersButton)
	{
		FiltersButton->RegisterOnClick(UControlPanelButton::FOnControlPanelButtonClick::CreateWeakLambda(this, [HostLayer](FGameplayTag ButtonTag)
		{
			HostLayer->MoveToNextWidgetInGroup();
		}));

		ControlPanelButtons.Add(NativeUIGameplayTags.UI_ControlPanel_Button_Filters, FiltersButton);

		if (SelectedItemWidget)
		{
			FiltersButton->SetEnable();
		}
	}
}

void USearchStacksContractSelectWidget::Refresh()
{
	Super::Refresh();
	
	LoadContracts();
}

void USearchStacksContractSelectWidget::LoadContracts()
{
	UMarketplacePolicy* Policy = GetOwningCustomLocalPLayer()->GetGameUIPolicy()->GetMarketplacePolicy();

	if (!Policy || !GridPanel)
	{
		return;
	}

	auto& Contracts = Policy->GetContracts();

	for (auto Contract : Contracts)
	{
		USearchStacksContractSelectItemWidget* ItemWidget = CreateWidget<USearchStacksContractSelectItemWidget>(GridPanel, ItemWidgetClass.LoadSynchronous());

		if (ItemWidget)
		{
			ItemWidget->SetName(Contract);
			ItemWidget->SetContractAddress(Contract);
			ItemWidget->RegisterOnSelectionChange(UItemWidget::FOnSelectionChange::CreateUObject(this, &USearchStacksContractSelectWidget::OnItemSelectionChange));
			ItemWidget->RegisterOnDoubleClick(UItemWidget::FOnDoubleClick::CreateUObject(this, &USearchStacksContractSelectWidget::OnItemDoubleClick));
			ItemWidget->Show();
			GridPanel->AddChildToGrid(ItemWidget);
		}
	}

	if (GridPanel->GetChildrenCount() > 0)
	{
		UItemWidget* ItemWidget = Cast<UItemWidget>(GridPanel->GetChildAt(0));
		// potentially SelectedItemWidget maybe null, we won't have selection in that case
		ItemSelectionChange(ItemWidget != nullptr, ItemWidget);
	}
}

void USearchStacksContractSelectWidget::ItemSelectionChange(bool IsSelected, UItemWidget* ItemWidget)
{
	if (IsSelected && SelectedItemWidget != ItemWidget)
	{
		if (SelectedItemWidget)
		{
			SelectedItemWidget->SetSelection(false);
		}
		SelectedItemWidget = ItemWidget;
		SelectedItemWidget->SetSelection(true);
		if (FiltersButton)
		{
			FiltersButton->SetEnable();	
		}

		if (UMarketplacePolicy* Policy = GetOwningCustomLocalPLayer()->GetGameUIPolicy()->GetMarketplacePolicy())
		{
			if (USearchStacksContractSelectItemWidget* Item = Cast<USearchStacksContractSelectItemWidget>(SelectedItemWidget))
			{
				Policy->SetSelectedContractAddress(Item->GetContractAddress());	
			}
		}
			
		return;
	}

	if (!IsSelected && SelectedItemWidget == ItemWidget)
	{
		SelectedItemWidget = nullptr;
		if (FiltersButton)
		{
			FiltersButton->SetEnable(false);
		}
		if (UMarketplacePolicy* Policy = GetOwningCustomLocalPLayer()->GetGameUIPolicy()->GetMarketplacePolicy())
		{
			Policy->SetSelectedContractAddress(TEXT(""));	
		}
	}
}
