#include "Base/ItemWidget.h"

void UItemWidget::SetOriginalState()
{
	SetVisibility(ESlateVisibility::Hidden);

#if WITH_EDITOR
	// In editor, always make visible all items to ease design 
	if (IsDesignTime())
	{
		SetVisibility(ESlateVisibility::Visible);
	}
#endif
}

bool UItemWidget::Initialize()
{
	bool Result = Super::Initialize();

	if (!IsDesignTime())
	{
		SetOriginalState();
	}

	return Result;
}

