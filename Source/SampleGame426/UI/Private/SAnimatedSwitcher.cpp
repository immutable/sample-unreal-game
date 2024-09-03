
#include "SAnimatedSwitcher.h"


void SAnimatedSwitcher::Construct(const FArguments& InArgs)
{
	SWidgetSwitcher::Construct(SWidgetSwitcher::FArguments().WidgetIndex(InArgs._InitialIndex));
		
	SetCanTick(false);
}

SWidgetSwitcher::FSlot* SAnimatedSwitcher::GetChildSlot(int32 SlotIndex)
{
	return GetTypedChildren().IsValidIndex(SlotIndex) ? &GetTypedChildren()[SlotIndex] : nullptr;
}
