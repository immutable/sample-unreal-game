#include "CustomButtonBase.h"

#include "Components/Button.h"

void UCustomButtonBase::NativeConstruct()
{
	Super::NativeConstruct();

	ActualButton->OnClicked.AddDynamic(this, &UCustomButtonBase::OnActualButtonClicked);
}

void UCustomButtonBase::OnActualButtonClicked()
{
	BP_OnButtonCLicked();
}
