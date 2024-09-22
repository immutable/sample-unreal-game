#include "Base/ActivatableWidgetWithControls.h"

#include "Components/Button.h"

inline void UActivatableWidgetWithControls::AddButton(FGameplayTag ButtonTag, SHorizontalBox::FSlot* HorizontalSlot)
{
	UControlPanelButtonDataAsset* Data = ControlPanelButtonDefaults.LoadSynchronous();
	
	if (!Data)
	{
		return;
	}

	UClass* ButtonClass = Data->ControlButtonClass.LoadSynchronous();

	if (!ButtonClass)
	{
		return;
	}

	UControlPanelButton* Button = Cast<UControlPanelButton>(CreateWidget(this, ButtonClass, TEXT("ControlPanelButton")));

	FControlPanelButtonDisplayInfo *Info = Data->DisplayInfo.Find(ButtonTag);

	if (Info)
	{
		Button->SetIcon(Info->Icon);
		Button->SetButtonTag(ButtonTag);
	}
	
	auto VerticalBox = StaticCastSharedRef<SVerticalBox>(HorizontalSlot->GetWidget());
	
	SVerticalBox::FSlot* VerticalBoxSlot = &VerticalBox->AddSlot()
	.HAlign(HAlign_Center)
	.VAlign(VAlign_Top)
	.AutoHeight()
	[
		Button->TakeWidget()	
	];
	
	Buttons.Add(Button);
}

void UActivatableWidgetWithControls::AddButtonToLeft(FGameplayTag ButtonTag)
{
	AddButton(ButtonTag, LeftPanelVerticalBoxSlot);
}

void UActivatableWidgetWithControls::AddButtonToRight(FGameplayTag ButtonTag)
{
	AddButton(ButtonTag, RightPanelVerticalBoxSlot);
}

TSharedRef<SWidget> UActivatableWidgetWithControls::RebuildWidget()
{
	TSharedRef<SWidget> RootWidget = Super::RebuildWidget();

	TSharedPtr<SHorizontalBox> HBox = SNew(SHorizontalBox);

	LeftPanelVerticalBoxSlot = &HBox->AddSlot()
		.FillWidth(LeftPanelHorizontalWidthFill)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SVerticalBox)
		];

	CenterPanelVerticalBoxSlot = &HBox->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.FillWidth(CenterPanelHorizontalWidthFill)
		[
			RootWidget
		];

	RightPanelVerticalBoxSlot = &HBox->AddSlot()
		.FillWidth(RightPanelHorizontalWidthFill)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SVerticalBox)
		];

	return HBox.ToSharedRef();
}

void UActivatableWidgetWithControls::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	LeftPanelVerticalBoxSlot->FillWidth(LeftPanelHorizontalWidthFill);
	CenterPanelVerticalBoxSlot->FillWidth(CenterPanelHorizontalWidthFill);
	RightPanelVerticalBoxSlot->FillWidth(RightPanelHorizontalWidthFill);
}
