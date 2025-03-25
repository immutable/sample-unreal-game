#include "Base/AWStackWithControlPanels.h"

#include "Components/VerticalBox.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/SOverlay.h"

#include "Base/AWStackTopControlPanel.h"
#include "Base/ActivatableWidget.h"
#include "Base/ActivatableWidgetWithControlPanels.h"
#include "Base/TopPanelButton.h"
#include "LogSampleGame.h"
#include "UI/UIGameplayTags.h"

UAWStackWithControlPanels::UAWStackWithControlPanels(const FObjectInitializer& Initializer) :
	Super(Initializer)
{
	DisplayedWidgetGroupPair = TPair<FActivatableWidgetWithControlPanelsGroup*, int32>(nullptr, -1);
}

void UAWStackWithControlPanels::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	if (TopPanelWidget)
	{
		if (TopPanelWidget->GetCachedWidget())
		{
			MyVerticalBox->RemoveSlot(TopPanelWidget->GetCachedWidget().ToSharedRef());
		}

		TopPanelWidget = nullptr;
	}

	if (BottomPanelWidget)
	{
		if (BottomPanelWidget->GetCachedWidget())
		{
			MyVerticalBox->RemoveSlot(BottomPanelWidget->GetCachedWidget().ToSharedRef());
		}

		BottomPanelWidget = nullptr;
	}

	MyVerticalBox.Reset();
	ButtonPanel.Reset();
	ControlPanelButtons.Empty();

	for (auto WidgetGroup : WidgetGroups)
	{
		ClearWidgetFromGroup(&WidgetGroup);
	}
}

UControlPanelButton* UAWStackWithControlPanels::GetButton(FGameplayTag ButtonTag)
{
	if (ControlPanelButtons.Contains(ButtonTag))
	{
		return ControlPanelButtons.FindRef(ButtonTag);
	}

	return nullptr;
}

UControlPanelButton* UAWStackWithControlPanels::AddButton(FGameplayTag ButtonTag)
{
	UControlPanelButton* Button = GetButton(ButtonTag);

	if (Button)
	{
		return Button;
	}

	UControlPanelButtonDataAsset* Data = ControlPanelButtonDefaults.LoadSynchronous();

	if (!Data)
	{
		return nullptr;
	}

	UClass* ButtonClass = Data->ControlButtonClass.LoadSynchronous();

	if (!ButtonClass)
	{
		return nullptr;
	}

	Button = GeneratedWidgetsPool.GetOrCreateInstance<UControlPanelButton>(ButtonClass);

	ControlPanelButtons.Add(ButtonTag, Button);

	FControlPanelButtonDisplayInfo* Info = Data->DisplayInfo.Find(ButtonTag);

	if (Info)
	{
		Button->SetName(Info->Name);
		Button->SetColor(Info->ColorAndOpacity);
		Button->SetButtonTag(ButtonTag);
	}

	ButtonPanel
		->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Top)
		.AutoHeight()
		.Padding(ButtonPadding)
	[
		Button->TakeWidget()
	];

	return Button;
}

void UAWStackWithControlPanels::MoveToNextWidgetInGroup()
{
	auto DisplayedWidgetGroup = DisplayedWidgetGroupPair.Key;

	if (!DisplayedWidgetGroup)
	{
		return;
	}

	int32 WidgetIndex = DisplayedWidgetGroupPair.Value + 1;
	int32 WidgetIndexLimit = DisplayedWidgetGroup->WidgetsInGroup.Num();

	if (WidgetIndex < WidgetIndexLimit)
	{
		ShowWidgetFromGroup(DisplayedWidgetGroup, WidgetIndex);
	}

	if (ActiveSecondaryButton)
	{
		auto* NextActiveSecondaryButton = TopPanelWidget->GetNextSecondaryButton(ActiveSecondaryButton);

		if (NextActiveSecondaryButton)
		{
			ActiveSecondaryButton->BP_OnHighlightChanged(false);
			ActiveSecondaryButton = NextActiveSecondaryButton;
			ActiveSecondaryButton->BP_OnHighlightChanged(true);
		}
	}
}

void UAWStackWithControlPanels::MoveToPrevWidgetInGroup()
{
	auto DisplayedWidgetGroup = DisplayedWidgetGroupPair.Key;

	if (!DisplayedWidgetGroup)
	{
		return;
	}

	int32 WidgetIndex = DisplayedWidgetGroupPair.Value - 1;
	int32 WidgetIndexLimit = 0;

	if (WidgetIndex >= WidgetIndexLimit)
	{
		ShowWidgetFromGroup(DisplayedWidgetGroup, WidgetIndex);
	}

	if (ActiveSecondaryButton)
	{
		auto* PrevActiveSecondaryButton = TopPanelWidget->GetPrevSecondaryButton(ActiveSecondaryButton);

		if (PrevActiveSecondaryButton)
		{
			ActiveSecondaryButton->BP_OnHighlightChanged(false);
			ActiveSecondaryButton = PrevActiveSecondaryButton;
			ActiveSecondaryButton->BP_OnHighlightChanged(true);
		}
	}
}

TSharedRef<SWidget> UAWStackWithControlPanels::RebuildWidget()
{
	TSharedRef<SWidget> Original = Super::RebuildWidget();
	TSharedRef<SWidget> TopPanelSlate = SNullWidget::NullWidget;
	TSharedRef<SWidget> BottomPanelSlate = SNullWidget::NullWidget;

	if (!TopPanelWidget && TopPanelWidgetClass)
	{
		TopPanelWidget = CreateWidget<UAWStackTopControlPanel>(this, TopPanelWidgetClass);
		TopPanelSlate = TopPanelWidget->TakeWidget();
	}

	if (!BottomPanelWidget && BottomPanelWidgetClass)
	{
		BottomPanelWidget = CreateWidget<UCustomUserWidget>(this, BottomPanelWidgetClass);
		BottomPanelSlate = BottomPanelWidget->TakeWidget();
	}

	SAssignNew(MyVerticalBox, SVerticalBox)

	+ SVerticalBox::Slot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	.FillHeight(TopPanelVerticalHeightFill)
	[
		TopPanelSlate
	]

	+ SVerticalBox::Slot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	.FillHeight(WindowPanelVerticalHeightFill)
	[
		SNew(SHorizontalBox)

		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.FillWidth(WindowPanelHorizontalWidthFill)
		.Padding(WindowPanelPadding)
		[
			SNew(SOverlay)

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&WindowPanelBackgroundBrush)
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				Original
			]
		]

		+ SHorizontalBox::Slot()
		.FillWidth(ButtonPanelHorizontalWidthFill)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(ButtonPanelPadding)
		[
			SNew(SOverlay)

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&ButtonPanelBackgroundBrush)
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(ButtonPanel, SVerticalBox)
			]
		]
	]

	+ SVerticalBox::Slot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	.FillHeight(BottomPanelVerticalHeightFill)
	[
		BottomPanelSlate
	];

	return MyVerticalBox.ToSharedRef();
}

void UAWStackWithControlPanels::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (IsDesignTime())
	{
		return;
	}

	BuildTopPanel();
}

void UAWStackWithControlPanels::SynchronizeProperties()
{
	Super::SynchronizeProperties();

#if WITH_EDITOR
	if (IsDesignTime())
	{
		ControlPanelButtons.Empty();
		ButtonPanel->ClearChildren();
		for (int32 i = 0; i < 5; ++i)
		{
			AddButton(NativeUIGameplayTags.UI_ControlPanel_Button_Empty);
		}
	}
#endif
}

void UAWStackWithControlPanels::OnWidgetAddedToList(UActivatableWidget& AddedWidget)
{
	Super::OnWidgetAddedToList(AddedWidget);

	if (UActivatableWidgetWithControlPanels* Widget = Cast<UActivatableWidgetWithControlPanels>(&AddedWidget))
	{
		Widget->SetupControlButtons(this);
		Widget->Refresh();
	}
}

void UAWStackWithControlPanels::OnControlPanelButtonClicked(FGameplayTag ButtonTag)
{
	if (ButtonTag.MatchesTagExact(NativeUIGameplayTags.UI_ControlPanel_Button_Back))
	{
		MoveToPrevWidgetInGroup();
	}

	if (ButtonTag.MatchesTagExact(NativeUIGameplayTags.UI_ControlPanel_Button_Forward))
	{
		MoveToNextWidgetInGroup();
	}
}

void UAWStackWithControlPanels::OnMainPanelButtonClicked(UTopPanelButton* Button)
{
	auto Group = MapMainButtonToWidgetGroup.Find(Button);

	if (!Group)
	{
		return;
	}

	if (ActiveMainButton != Button)
	{
		if (ActiveMainButton && DisplayedWidgetGroupPair.Key)
		{
			ActiveMainButton->BP_OnHighlightChanged(false);
			ClearWidgetFromGroup(DisplayedWidgetGroupPair.Key);
			DisplayedWidgetGroupPair.Key = nullptr;
			DisplayedWidgetGroupPair.Value = -1;
		}
		ActiveMainButton = Button;
		ActiveMainButton->BP_OnHighlightChanged(true);
		ShowWidgetFromGroup(*Group);
		TopPanelWidget->ShowSecondaryButtons(Button);

		// highlight first secondary button in the group
		auto* SecondaryButtons = TopPanelWidget->GetSecondaryButtons(Button);

		if (SecondaryButtons && SecondaryButtons->Num() > 0)
		{
			ActiveSecondaryButton = (*SecondaryButtons)[0];
			ActiveSecondaryButton->BP_OnHighlightChanged(true);
		}
	}
}

void UAWStackWithControlPanels::OnSecondaryPanelButtonClicked(UTopPanelButton* Button)
{
	auto MainButton = TopPanelWidget->GetMainButton(Button);
	auto Group = MapMainButtonToWidgetGroup.Find(MainButton);

	if (!Group)
	{
		return;
	}

	if (ActiveSecondaryButton != Button)
	{
		if (ActiveSecondaryButton)
		{
			ActiveSecondaryButton->BP_OnHighlightChanged(false);
		}
		ShowWidgetFromGroup(*Group, Button->GetIndex());
		ActiveSecondaryButton = Button;
		ActiveSecondaryButton->BP_OnHighlightChanged(true);
	}
}

void UAWStackWithControlPanels::BuildTopPanel()
{
	if (TopPanelWidget)
	{
		for (int32 i = 0; i < WidgetGroups.Num(); ++i)
		{
			auto& Group = WidgetGroups[i];
			auto* MainButton = TopPanelWidget->AddMainButton(Group.GroupName, i);

			check(MainButton);
			MainButton->OnClickDelegate = UTopPanelButton::FOnClick::CreateUObject(this, &UAWStackWithControlPanels::OnMainPanelButtonClicked);
			MapMainButtonToWidgetGroup.Add(MainButton, &Group);

			auto ListOfSoftWidgetClass = Group.WidgetClassesGroup;

			Group.WidgetsInGroup.Init(nullptr, Group.WidgetClassesGroup.Num());
			// for (const auto SoftWidgetClass : ListOfSoftWidgetClass)
			for (int32 WidgetClassIndex = 0; WidgetClassIndex < Group.WidgetClassesGroup.Num(); ++WidgetClassIndex)
			{
				auto* WidgetClass = Group.WidgetClassesGroup[WidgetClassIndex].LoadSynchronous();

				if (!WidgetClass)
				{
					UE_LOG(LogTemp, Error, TEXT("Widget class cannot be loaded %s"), *Group.WidgetClassesGroup[WidgetClassIndex].ToString());

					continue;
				}

				auto WidgetCDO = Cast<UActivatableWidgetWithControlPanels>(WidgetClass->GetDefaultObject(false));

				if (!WidgetCDO)
				{
					UE_LOG(LogSampleGame, Error, TEXT("Failed to cast group widget %s"), *Group.WidgetClassesGroup[WidgetClassIndex].ToString());
				}

				auto* SecondaryButton = TopPanelWidget->AddSecondaryButton(MainButton, WidgetCDO->GetWidgetTitle(), WidgetClassIndex);

				check(SecondaryButton);
				SecondaryButton->OnClickDelegate = UTopPanelButton::FOnClick::CreateUObject(this, &UAWStackWithControlPanels::OnSecondaryPanelButtonClicked);
			}
		}
	}
}

void UAWStackWithControlPanels::BuildControlPanel()
{
	if (!PreviousWidgetInGroupButton)
	{
		PreviousWidgetInGroupButton = AddButton(NativeUIGameplayTags.UI_ControlPanel_Button_Back);
		PreviousWidgetInGroupButton->RegisterOnClick(UControlPanelButton::FOnControlPanelButtonClick::CreateUObject(this, &UAWStackWithControlPanels::OnControlPanelButtonClicked));
	}
	if (!NextWidgetInGroupButton)
	{
		NextWidgetInGroupButton = AddButton(NativeUIGameplayTags.UI_ControlPanel_Button_Forward);
		NextWidgetInGroupButton->RegisterOnClick(UControlPanelButton::FOnControlPanelButtonClick::CreateUObject(this, &UAWStackWithControlPanels::OnControlPanelButtonClicked));
	}
}

void UAWStackWithControlPanels::ShowWidgetFromGroup(FActivatableWidgetWithControlPanelsGroup* Group, int32 WidgetIndex)
{
	if (!Group)
	{
		return;
	}

	UActivatableWidgetWithControlPanels* Widget = Group->WidgetsInGroup[WidgetIndex];

	if (!Widget)
	{
		Widget = AddWidget<UActivatableWidgetWithControlPanels>(Group->WidgetClassesGroup[WidgetIndex].LoadSynchronous());
		Group->WidgetsInGroup[WidgetIndex] = Widget;
		Widget->Reset();
		Widget->SetIndexInGroup(WidgetIndex);
		Widget->SetOwningGroup(Group);
	}
	else
	{
		SetSwitcherActiveWidget(*Widget);
		Widget->Refresh();
	}

	DisplayedWidgetGroupPair.Key = Group;
	DisplayedWidgetGroupPair.Value = WidgetIndex;
}

void UAWStackWithControlPanels::ClearWidgetFromGroup(FActivatableWidgetWithControlPanelsGroup* Group)
{
	int32 NumberOfWidgets = Group->WidgetsInGroup.Num();
	for (int32 i = 0; i < NumberOfWidgets; ++i)
	{
		if (Group->WidgetsInGroup[i])
		{
			Group->WidgetsInGroup[i]->SetCanBeReleased();
			RemoveWidget(*Group->WidgetsInGroup[i]);
			Group->WidgetsInGroup[i] = nullptr;
		}
	}
}