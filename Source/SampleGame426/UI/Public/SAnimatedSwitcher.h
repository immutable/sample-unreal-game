#include "Widgets/Layout/SWidgetSwitcher.h"


class  SAnimatedSwitcher : public SWidgetSwitcher
{
public:
	SLATE_BEGIN_ARGS(SAnimatedSwitcher)
	: _InitialIndex(0)
	{}

	SLATE_ARGUMENT(int32, InitialIndex)
	
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);
	
	FSlot* GetChildSlot(int32 SlotIndex);
};
