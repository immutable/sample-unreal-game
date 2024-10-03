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

void UCustomButtonBase::OnActualButtonClicked()
{
	BP_OnButtonCLicked();
}

void UCustomButtonBase::ChangeEnableStatus(bool EnableStatus)
{
	ActualButton->SetIsEnabled(EnableStatus);
	BP_ChangeEnableStatus(EnableStatus);
}
