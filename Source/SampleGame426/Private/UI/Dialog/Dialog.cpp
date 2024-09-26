#include "Dialog/Dialog.h"

#include "LogSampleGame.h"


void UDialog::OnDialogAction(const FDialogAction& ExecutedAction)
{
	UE_LOG(LogSampleGame, Log, TEXT("Dialog action was executed %s"), *ExecutedAction.GetActionName());
	ResultCallbackDelegate.ExecuteIfBound(ExecutedAction.Result);
}

void UDialog::SetupDialog(const FDialogDescriptor& Descriptor, FDialogResultDelegate Delegate)
{
	BP_OnSetupDialog(Descriptor);	
	ResultCallbackDelegate = Delegate; 
}

void UDialog::KillDialog()
{
	ResultCallbackDelegate.Unbind();
	NativeDestruct();
}
