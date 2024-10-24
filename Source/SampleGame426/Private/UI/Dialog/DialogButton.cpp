#include "Dialog/DialogButton.h"

const FDialogAction& UDialogButton::GetButtonAction() const
{
	return ButtonAction;
}

void UDialogButton::SetButtonAction(const FDialogAction& Action)
{
	ButtonAction = Action;
	BP_SetActionText(ButtonAction.ActionText);
}