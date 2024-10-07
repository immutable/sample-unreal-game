#include "Dialog/Dialog.h"

#include "LogSampleGame.h"


UDialog::UDialog(const FObjectInitializer& Initializer)
: Super(Initializer)
{
	bSetVisibilityOnDeactivated = true;
}

void UDialog::OnDialogAction(const FDialogAction& ExecutedAction)
{
	UE_LOG(LogSampleGame, Log, TEXT("Dialog action was executed %s"), *ExecutedAction.GetActionName());
	DialogResultDelegate.Broadcast(ExecutedAction.Result);
}

void UDialog::KillDialog()
{
	NativeDestruct();
}
