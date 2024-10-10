#include "Dialog/DialogButton.h"


void UDialogButton::SetButtonAction(const FDialogAction& Action)
{
	ButtonAction = Action;
	BP_SetActionText(ButtonAction.ActionText);
}

const FDialogAction& UDialogButton::GetButtonAction() const
{
	return ButtonAction;
}
