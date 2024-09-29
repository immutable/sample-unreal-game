#include "Base/AWStackWithControlPanels.h"

#include "UIGameplayTags.h"
#include "Base/ActivatableWidget.h"
#include "Base/ActivatableWidgetWithControlPanels.h"
#include "Widgets/Images/SImage.h"


TSharedRef<SWidget> UAWStackWithControlPanels::RebuildWidget()
{
	TSharedRef<SWidget> Original = Super::RebuildWidget();
	TSharedRef<SWidget> TopPanelSlate = SNullWidget::NullWidget;

	if (!TopPanelWidget && TopPanelWidgetClass)
	{
		TopPanelWidget = CreateWidget<UActivatableWidget>(this, TopPanelWidgetClass);
		TopPanelSlate = TopPanelWidget->TakeWidget();
	}
	
	SAssignNew(MyVerticalBox, SVerticalBox)

	+ SVerticalBox::Slot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	.AutoHeight()
	[
		TopPanelSlate
	]
	
	+ SVerticalBox::Slot()
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
			Original
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
	];

	return MyVerticalBox.ToSharedRef();
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

	if (!IsDesignTime())
	{
		AddButtonToLeft(FUIControlPanelButtons::Back);
		AddButtonToRight(FUIControlPanelButtons::Forward);
	}
}

void UAWStackWithControlPanels::OnWidgetAddedToList(UActivatableWidget& AddedWidget)
{
	Super::OnWidgetAddedToList(AddedWidget);

	UActivatableWidgetWithControlPanels* Widget = Cast<UActivatableWidgetWithControlPanels>(&AddedWidget);

	if (Widget)
	{
		const TMap<FGameplayTag, EAWStackControlPanelSide>& ButtonsData = Widget->GetControlButtonsData();
		TMap<FGameplayTag, UControlPanelButton*> Buttons;

		if (Widget->IsSwitchBetweenWindowsHandler())
		{
			Buttons.Add(FUIControlPanelButtons::Back, GetButton(FUIControlPanelButtons::Back));
			Buttons.Add(FUIControlPanelButtons::Forward, GetButton(FUIControlPanelButtons::Forward));
		}
		for(auto ButtonData : ButtonsData)
		{
			Buttons.Add(ButtonData.Key, AddButton(ButtonData.Key, ButtonData.Value));
		}

		Widget->SetupControlButtons(Buttons);
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

	MyVerticalBox.Reset();
	LeftControlPanel.Reset();
	RightControlPanel.Reset();
	ControlPanelButtons.Empty();
}

UControlPanelButton* UAWStackWithControlPanels::AddButton(FGameplayTag ButtonTag, EAWStackControlPanelSide Side)
{
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

	UControlPanelButton* Button = GetButton(ButtonTag);
	
	if (Button)
	{
		return Button;
	}

	Button = GeneratedWidgetsPool.GetOrCreateInstance<UControlPanelButton>(ButtonClass);

	ControlPanelButtons.Add(ButtonTag, Button);	
	
	FControlPanelButtonDisplayInfo *Info = Data->DisplayInfo.Find(ButtonTag);

	if (Info)
	{
		Button->SetIcon(Info->Icon);
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