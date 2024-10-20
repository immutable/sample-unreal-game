#include "Base/ActivatableWidgetWithControlPanels.h"

#include "UIGameplayTags.h"
#include "Base/AWStackWithControlPanels.h"
#include "Marketplace/SearchStacksWidget.h"


FString UActivatableWidgetWithControlPanels::GetTitle() const
{
	return WidgetTitle;
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
