#include "Base/CustomButtonBase.h"

#include "Components/Button.h"

void UCustomButtonBase::NativeConstruct()
{
	Super::NativeConstruct();

	ActualButton->OnClicked.AddDynamic(this, &UCustomButtonBase::OnActualButtonClicked);
}

void UCustomButtonBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ChangeEnableStatus(false);
}

void UCustomButtonBase::ChangeEnableStatus(bool bNewEnableStatus)
{
	ActualButton->SetIsEnabled(bNewEnableStatus);
	BP_ChangeEnableStatus(bNewEnableStatus);
}

void UCustomButtonBase::OnActualButtonClicked()
{
	BP_OnButtonClicked();
}