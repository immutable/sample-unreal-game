#include "Dialog/Dialog.h"

#include "LogSampleGame.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"


UDialog::UDialog(const FObjectInitializer& Initializer)
: Super(Initializer)
{
	bSetVisibilityOnDeactivated = true;
}

void UDialog::ExecuteDialogAction(const UDialogButton* Button)
{
	check(Button && Button->GetButtonAction().Result != EDialogResult::Unknown);

	const FDialogAction& Action = Button->GetButtonAction();
	
	UE_LOG(LogSampleGame, Log, TEXT("Dialog action was executed %s"), *Action.GetActionName());
	DialogResultDelegate.Broadcast(this, Action.Result);

	if (Action.Result == EDialogResult::Cancelled || Action.Result == EDialogResult::Closed)
	{
		KillDialog();
	}
}

void UDialog::KillDialog()
{
	NativeDestruct();
}

void UDialog::SetDialogTag(FGameplayTag Tag)
{
	DialogTag = Tag;
}

FGameplayTag UDialog::GetDialogTag() const
{
	return DialogTag;
}

void USellDialog::ExecuteDialogAction(const UDialogButton* Button)
{
	check(Button && Button->GetButtonAction().Result != EDialogResult::Unknown);

	const FDialogAction& Action = Button->GetButtonAction();
	FText PriceText = PriceEditableTextBox->GetText();

	if (Action.Result == EDialogResult::Confirmed && !PriceText.IsNumeric())
	{
		return;
	}

	Super::ExecuteDialogAction(Button);
}

FString USellDialog::GetPrice() const
{
	// return FCString::Atof(*PriceEditableTextBox->GetText().ToString());
	return  PriceEditableTextBox->GetText().ToString();
}
