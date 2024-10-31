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

UTopPanelButton* UAWStackTopControlPanel::GetNextSecondaryButton(UTopPanelButton* SecondaryButton)
{
	if (!DisplayedSecondaryButtons)
	{
		return nullptr;
	}

	int32 Index = INDEX_NONE;

	if (DisplayedSecondaryButtons->Find(SecondaryButton, Index) && DisplayedSecondaryButtons->Num() > Index + 1)
	{
		return (*DisplayedSecondaryButtons)[Index + 1];
	}

	return nullptr;
}

UTopPanelButton* UAWStackTopControlPanel::GetPrevSecondaryButton(UTopPanelButton* SecondaryButton)
{
	if (!DisplayedSecondaryButtons)
	{
		return nullptr;
	}

	int32 Index = INDEX_NONE;

	if (DisplayedSecondaryButtons->Find(SecondaryButton, Index) && Index - 1 > 0)
	{
		return (*DisplayedSecondaryButtons)[Index - 1];
	}

	return nullptr;
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

	if (DisplayedSecondaryButtons)
	{
		for (auto* Button : *DisplayedSecondaryButtons)
		{
			Button->Hide();
		}
	}

	for (auto* Button : *NewSecondaryButtons)
	{
		Button->Show();
	}

	DisplayedSecondaryButtons = NewSecondaryButtons;
	SelectedMainButton = MainButton;
}