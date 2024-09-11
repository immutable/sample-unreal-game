#include "CustomButtonWithText.h"

#include "Components/TextBlock.h"

void UCustomButtonWithText::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (Title)
	{
		Title->SetText(TitleText);
	}
}
