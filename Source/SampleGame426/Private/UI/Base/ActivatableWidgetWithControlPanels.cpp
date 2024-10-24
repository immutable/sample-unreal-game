#include "Base/ActivatableWidgetWithControlPanels.h"

#include "Base/AWStackWithControlPanels.h"
#include "Marketplace/SearchStacksWidget.h"

bool UActivatableWidgetWithControlPanels::CanBeReleased() const
{
	return bCanBeReleased;
}

void UActivatableWidgetWithControlPanels::Reset()
{
	Super::Reset();

	bCanBeReleased = false;
	IndexInGroup = -1;
	OwningGroup = nullptr;
	ControlPanelButtons.Reset();
}

FString UActivatableWidgetWithControlPanels::GetWidgetTitle() const
{
	return WidgetTitle;
}

int32 UActivatableWidgetWithControlPanels::GetIndexInGroup() const
{
	return IndexInGroup;
}

const FActivatableWidgetWithControlPanelsGroup* UActivatableWidgetWithControlPanels::GetOwningGroup() const
{
	return OwningGroup;
}

void UActivatableWidgetWithControlPanels::SetIndexInGroup(int32 NewIndexInGroup)
{
	IndexInGroup = NewIndexInGroup;
}

void UActivatableWidgetWithControlPanels::SetCanBeReleased()
{
	bCanBeReleased = true;
}

void UActivatableWidgetWithControlPanels::SetOwningGroup(FActivatableWidgetWithControlPanelsGroup* NewOwningGroup)
{
	OwningGroup = NewOwningGroup;
}

void UActivatableWidgetWithControlPanels::Refresh()
{
}

void UActivatableWidgetWithControlPanels::SetupControlButtons(UAWStackWithControlPanels* HostLayer)
{
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