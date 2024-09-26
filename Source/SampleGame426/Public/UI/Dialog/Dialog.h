#pragma once

#include "Base/ActivatableWidget.h"
#include "DialogDescriptors.h"

#include "Dialog.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogResultDelegate, EDialogResult, Result);

/*
 * 
 */
UCLASS(Abstract)
class SAMPLEGAME426_API UDialog : public UActivatableWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Immutable")
	void SetupDialog(const UDialogDescriptor* Descriptor);

	UFUNCTION(BlueprintCallable, Category = "Immutable")
	void OnDialogAction(const FDialogAction& ExecutedAction);

	UFUNCTION(BlueprintCallable, Category = "Immutable")
	void KillDialog();

public:
	UPROPERTY(BlueprintAssignable)
	FDialogResultDelegate DialogResultDelegate;
	
};
