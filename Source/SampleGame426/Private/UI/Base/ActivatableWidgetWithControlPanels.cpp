#include "Base/ActivatableWidgetWithControlPanels.h"

#include "UIGameplayTags.h"
#include "Components/Button.h"
#include "Marketplace/SearchStacksWidget.h"
#include "ThirdParty/PhysX3/NvCloth/samples/external/imgui/1.49/imgui.h"


FString UActivatableWidgetWithControlPanels::GetWidgetTitle() const
{
	return WidgetTitle;
}

const TMap<FGameplayTag, EAWStackControlPanelSide>& UActivatableWidgetWithControlPanels::GetControlButtonsData() const
{
	return ControlPanelButtonsData; 
}

void UActivatableWidgetWithControlPanels::SetupControlButtons(UAWStackWithControlPanels* HostPanel)
{
	if (SwitchBetweenWindowsHandler)
	{
		PreviousWidgetButton = HostPanel->AddButtonToLeft(FUIControlPanelButtons::Back);
		NextWidgetButton = HostPanel->AddButtonToLeft(FUIControlPanelButtons::Forward);
	}
	for(auto ButtonData : ControlPanelButtonsData)
	{
		UControlPanelButton* NewButton = ButtonData.Value == EAWStackControlPanelSide::Left ? HostPanel->AddButtonToLeft(ButtonData.Key) : NewButton = HostPanel->AddButtonToRight(ButtonData.Key);

		if (NewButton)
		{
			ControlPanelButtons.Add(ButtonData.Key, NewButton);
		}
	}

	BP_SetupControlButtons(ControlPanelButtons);
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

void UActivatableWidgetWithControlPanels::NativeDestruct()
{
	Super::NativeDestruct();

	ControlPanelButtons.Reset();
	ControlPanelButtonsData.Reset();
}

void UActivatableWidgetWithControlPanels::NativeOnActivated()
{
	Super::NativeOnActivated();

	for (auto Button : ControlPanelButtons)
	{
		Button.Value->Show();
	}
}

void UActivatableWidgetWithControlPanels::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();
	
	for (auto Button : ControlPanelButtons)
	{
		Button.Value->Hide();
	}
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
