#include "Base/ActivatableWidgetWithControlPanels.h"

#include "UIGameplayTags.h"
#include "Base/AWStackWithControlPanels.h"
#include "Marketplace/SearchStacksWidget.h"


// UActivatableWidgetWithControlPanels::UActivatableWidgetWithControlPanels(const FObjectInitializer& ObjectInitializer)
// 	: Super(ObjectInitializer)
// {
// }

FString UActivatableWidgetWithControlPanels::GetTitle() const
{
	return WidgetTitle;
}

// const TMap<FGameplayTag, EAWStackControlPanelSide>& UActivatableWidgetWithControlPanels::GetControlButtonsData() const
// {
// 	return ControlPanelButtonsData; 
// }

void UActivatableWidgetWithControlPanels::SetupControlButtons(UAWStackWithControlPanels* HostLayer)
{
	// for(auto ButtonData : ControlPanelButtonsData)
	// {
	// 	UControlPanelButton* NewButton = ButtonData.Value == EAWStackControlPanelSide::Left ? HostPanel->AddButtonToLeft(ButtonData.Key) : NewButton = HostPanel->AddButtonToRight(ButtonData.Key);
	//
	// 	if (NewButton)
	// 	{
	// 		ControlPanelButtons.Add(ButtonData.Key, NewButton);
	// 	}
	// }
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
