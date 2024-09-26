#pragma once

#include "Base/ActivatableWidget.h"
#include "DialogDescriptors.h"

#include "Dialog.generated.h"


DECLARE_DYNAMIC_DELEGATE_OneParam(FDialogResultDelegate, EDialogResult, Result);

/*
 * 
 */
UCLASS(Abstract)
class SAMPLEGAME426_API UDialog : public UActivatableWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent, Category = "Immutable")
	void BP_OnSetupDialog(const FDialogDescriptor& Descriptor);

	UFUNCTION(BlueprintCallable, Category = "Immutable")
	void OnDialogAction(const FDialogAction& ExecutedAction);

	UFUNCTION(BlueprintCallable, Category = "Immutable")
	void SetupDialog(const FDialogDescriptor& Descriptor, FDialogResultDelegate Delegate);

	virtual void KillDialog();

private:
	FDialogResultDelegate ResultCallbackDelegate;
	
};
