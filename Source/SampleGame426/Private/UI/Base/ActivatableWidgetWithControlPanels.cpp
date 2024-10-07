#include "Base/ActivatableWidgetWithControlPanels.h"

#include "UIGameplayTags.h"
#include "Components/Button.h"
#include "Marketplace/SearchStacksWidget.h"
#include "ThirdParty/PhysX3/NvCloth/samples/external/imgui/1.49/imgui.h"


const TMap<FGameplayTag, EAWStackControlPanelSide>& UActivatableWidgetWithControlPanels::GetControlButtonsData() const
{
	return ControlPanelButtonsData; 
}

void UActivatableWidgetWithControlPanels::SetupControlButtons(TMap<FGameplayTag, UControlPanelButton*>& Buttons)
{
	if (SwitchBetweenWindowsHandler)
	{
		UControlPanelButton *Button = nullptr;
		
		if (Buttons.RemoveAndCopyValue(FUIControlPanelButtons::Forward, Button))
		{
			Button->OnPanelButtonClicked.AddUniqueDynamic(this, &USearchStacksWidget::OnForwardButtonClicked);
		}
		if (Buttons.RemoveAndCopyValue(FUIControlPanelButtons::Back, Button))
		{
			Button->OnPanelButtonClicked.AddUniqueDynamic(this, &USearchStacksWidget::OnBackButtonClicked);
		}
	}

	BP_SetupControlButtons(Buttons);
}

TSharedRef<SWidget> UActivatableWidgetWithControlPanels::RebuildWidget()
{
	return Super::RebuildWidget();
}

void UActivatableWidgetWithControlPanels::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UActivatableWidgetWithControlPanels::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
}

void UActivatableWidgetWithControlPanels::OnBackButtonClicked(FGameplayTag ButtonTag)
{
	DeactivateWidget();
	BP_OnBackButtonClicked();
}

void UActivatableWidgetWithControlPanels::OnForwardButtonClicked(FGameplayTag ButtonTag)
{
	BP_OnForwardButtonClicked();
}
