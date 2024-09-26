#include "Dialog/Dialog.h"

#include "LogSampleGame.h"


void UDialog::OnDialogAction(const FDialogAction& ExecutedAction)
{
	UE_LOG(LogSampleGame, Log, TEXT("Dialog action was executed %s"), *ExecutedAction.GetActionName());
	DialogResultDelegate.Broadcast(ExecutedAction.Result);
}

void UDialog::KillDialog()
{
	NativeDestruct();
}
