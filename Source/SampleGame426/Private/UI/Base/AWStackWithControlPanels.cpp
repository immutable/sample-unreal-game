#include "Base/AWStackWithControlPanels.h"

#include "LogSampleGame.h"
#include "UIGameplayTags.h"
#include "Base/ActivatableWidget.h"
#include "Base/ActivatableWidgetWithControlPanels.h"
#include "Base/AWStackTopControlPanel.h"
#include "Widgets/Images/SImage.h"


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
	.FillHeight(CenterPanelVerticalHeightFill)
	[
		SNew(SHorizontalBox)

		+ SHorizontalBox::Slot()
		
		.FillWidth(LeftPanelHorizontalWidthFill)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(PanelsPadding)
		[
			SNew(SOverlay)

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&PanelsBrush)
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(LeftControlPanel, SVerticalBox)
			]
		]
		
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.FillWidth(CenterPanelHorizontalWidthFill)
		.Padding(ActivatableWidgetPadding)
		[
			SNew(SOverlay)

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&ActivatableWidgetBackgroundBrush)
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				Original
			]
		]

		+ SHorizontalBox::Slot()
		.FillWidth(RightPanelHorizontalWidthFill)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(PanelsPadding)
		[
			SNew(SOverlay)

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&PanelsBrush)
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(RightControlPanel, SVerticalBox)
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
		LeftControlPanel->ClearChildren();
		RightControlPanel->ClearChildren();
		for (int32 i = 0; i < 5; ++i)
		{
			AddButtonToLeft(FUIControlPanelButtons::Empty);
			AddButtonToRight(FUIControlPanelButtons::Empty);
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
	}
}

void UAWStackWithControlPanels::OnMainPanelButtonClicked(UTopPanelButton* Button)
{
	TopPanelWidget->ShowSecondaryButtons(Button);
	auto Group = MapMainButtonToWidgetGroup.Find(Button);

	if (!Group)
	{
		return;
	}

	if ((*Group)->WidgetsInGroup.Num() && (*Group)->WidgetsInGroup[0])
	{
		(*Group)->WidgetsInGroup[0]->ActivateWidget();
	}
	else if ((*Group)->WidgetClassesGroup.Num())
	{
		(*Group)->WidgetsInGroup[0] = AddWidget<UActivatableWidgetWithControlPanels>((*Group)->WidgetClassesGroup[0].LoadSynchronous());
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
	
	UActivatableWidgetWithControlPanels* Widget = (*Group)->WidgetsInGroup[Button->GetIndex()];

	if (!Widget)
	{
		(*Group)->WidgetsInGroup[Button->GetIndex()] = AddWidget<UActivatableWidgetWithControlPanels>((*Group)->WidgetClassesGroup[Button->GetIndex()].LoadSynchronous());
	}
	else
	{
		SetSwitcherIndex(Widget->GetSwitcherIndex());
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

				auto* SecondaryButton = TopPanelWidget->AddSecondaryButton(MainButton, WidgetCDO->GetTitle(), WidgetClassIndex);

				check(SecondaryButton);
				SecondaryButton->OnClickDelegate = UTopPanelButton::FOnClick::CreateUObject(this, &UAWStackWithControlPanels::OnSecondaryPanelButtonClicked);
			}
		}
	}
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
	LeftControlPanel.Reset();
	RightControlPanel.Reset();
	ControlPanelButtons.Empty();
}

UControlPanelButton* UAWStackWithControlPanels::AddButton(FGameplayTag ButtonTag, EAWStackControlPanelSide Side)
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
	
	FControlPanelButtonDisplayInfo *Info = Data->DisplayInfo.Find(ButtonTag);

	if (Info)
	{
		Button->SetIcon(Info->Icon);
		Button->SetName(Info->Name);
		Button->SetColor(Info->ColorAndOpacity);
		Button->SetButtonTag(ButtonTag);
	}

	TSharedPtr<SVerticalBox> Panel = Side == EAWStackControlPanelSide::Left ? LeftControlPanel : RightControlPanel;

	Panel->AddSlot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Top)
	.AutoHeight()
	.Padding(ButtonPadding)
	[
		Button->TakeWidget()	
	];

	return Button;
}

UControlPanelButton* UAWStackWithControlPanels::GetButton(FGameplayTag ButtonTag)
{
	if (ControlPanelButtons.Contains(ButtonTag))
	{
		return ControlPanelButtons.FindRef(ButtonTag);
	}
	
	return nullptr;
}

UControlPanelButton* UAWStackWithControlPanels::AddButtonToLeft(FGameplayTag ButtonTag)
{
	return AddButton(ButtonTag, EAWStackControlPanelSide::Left);
}

UControlPanelButton* UAWStackWithControlPanels::AddButtonToRight(FGameplayTag ButtonTag)
{
	return AddButton(ButtonTag, EAWStackControlPanelSide::Right);
}