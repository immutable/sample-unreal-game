#pragma once

#include "DialogButton.h"
#include "Base/ActivatableWidget.h"
#include "DialogDescriptors.h"

#include "Dialog.generated.h"


class UButton;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDialogResultDelegate, UDialog*, DialogPtr, EDialogResult, Result);

/*
 * 
 */
UCLASS(Abstract)
class SAMPLEGAME426_API UDialog : public UActivatableWidget
{
	GENERATED_BODY()
	
public:
	UDialog(const FObjectInitializer& Initializer);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Immutable")
	void SetupDialog(const UDialogDescriptor* Descriptor);

	UFUNCTION(BlueprintCallable, Category = "Immutable")
	virtual void ExecuteDialogAction(const UDialogButton* Button);

	UFUNCTION(BlueprintCallable, Category = "Immutable")
	virtual void KillDialog();

public:
	UPROPERTY(BlueprintAssignable)
	FDialogResultDelegate DialogResultDelegate;
	
};

/*
 * 
 */
UCLASS(Abstract)
class SAMPLEGAME426_API USellDialog : public UDialog
{
	GENERATED_BODY()
	
public:
	virtual void ExecuteDialogAction(const UDialogButton* Button) override;
	
	FString GetPrice() const;

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UEditableTextBox* PriceEditableTextBox;

};
