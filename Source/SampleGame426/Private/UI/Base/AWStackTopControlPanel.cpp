#include "Base/AWStackTopControlPanel.h"

#include "Components/HorizontalBox.h"

#include "UI/Base/TopPanelButton.h"

UTopPanelButton* UAWStackTopControlPanel::GetMainButton(UTopPanelButton* SecondaryButton)
{
	return *MapSecondaryToMainButtons.Find(SecondaryButton);
}

TArray<UTopPanelButton*>* UAWStackTopControlPanel::GetSecondaryButtons(UTopPanelButton* MainButton)
{
	return MapMainToSecondaryButtons.Find(MainButton);
}

UTopPanelButton* UAWStackTopControlPanel::AddMainButton(const FString& ButtonTitle, int32 Index)
{
	check(MainButtonPanel);

	UClass* LoadedClass = MainButtonClass.LoadSynchronous();

	if (!MainButtonPanel || !LoadedClass)
	{
		return nullptr;
	}

	auto Button = CreateWidget<UTopPanelButton>(this, LoadedClass);

	if (Button)
	{
		MainButtonPanel->AddChildToHorizontalBox(Button);
		Button->BP_SetText(ButtonTitle);
		MapMainToSecondaryButtons.Add(Button);
		Button->Show();
		Button->SetIndex(Index);

		return Button;
	}

	return nullptr;
}

UTopPanelButton* UAWStackTopControlPanel::AddSecondaryButton(UTopPanelButton* MainButton, const FString& ButtonTitle, int32 Index)
{
	check(SecondaryButtonPanel);
	check(MainButton);

	TArray<UTopPanelButton*>* SecondaryButtons = MapMainToSecondaryButtons.Find(MainButton);

	if (!SecondaryButtons)
	{
		return nullptr;
	}

	UClass* LoaddedClass = SecondaryButtonClass.LoadSynchronous();

	if (!SecondaryButtonPanel || !LoaddedClass)
	{
		return nullptr;
	}

	auto Button = CreateWidget<UTopPanelButton>(this, LoaddedClass);

	if (Button)
	{
		SecondaryButtonPanel->AddChildToHorizontalBox(Button);
		Button->BP_SetText(ButtonTitle);
		SecondaryButtons->Add(Button);
		MapSecondaryToMainButtons.Add(Button, MainButton);
		Button->SetIndex(Index);

		return Button;
	}

	return nullptr;
}

void UAWStackTopControlPanel::ShowSecondaryButtons(UTopPanelButton* MainButton)
{
	TArray<UTopPanelButton*>* NewSecondaryButtons = MapMainToSecondaryButtons.Find(MainButton);

	if (!MainButton || !NewSecondaryButtons)
	{
		return;
	}

	if (TArray<UTopPanelButton*>* ShownSecondaryButtons = MapMainToSecondaryButtons.Find(ShownMainButton))
	{
		for (auto* Button : *ShownSecondaryButtons)
		{
			Button->Hide();
		}
	}

	for (auto* Button : *NewSecondaryButtons)
	{
		Button->Show();
	}

	ShownMainButton = MainButton;
}