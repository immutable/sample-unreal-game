#pragma once

#include "GameplayTagContainer.h"
#include "Immutable/Transak/TransakWebBrowser.h"

#include "UI/Base/ActivatableWidget.h"
#include "UI/Dialog/DialogButton.h"
#include "UI/Dialog/DialogDescriptors.h"

#include "Dialog.generated.h"

class UButton;
class UEditableTextBox;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDialogResultDelegate, UDialog*, DialogPtr, EDialogResult, Result);

/**
 * @class UDialog
 * @brief Base class for creating dialogs
 */
UCLASS(Abstract)
class SAMPLEGAME426_API UDialog : public UActivatableWidget
{
	GENERATED_BODY()

public:
	UDialog(const FObjectInitializer& Initializer);

	UFUNCTION(BlueprintCallable, Category = "Immutable")
	virtual void ExecuteDialogAction(const UDialogButton* Button);

	UFUNCTION(BlueprintCallable, Category = "Immutable")
	virtual void KillDialog();

	UFUNCTION(BlueprintPure, Category = "Immutable")
	FGameplayTag GetDialogTag() const;

	UFUNCTION(BlueprintCallable, Category = "Immutable")
	void SetDialogTag(FGameplayTag Tag);

	UFUNCTION(BlueprintImplementableEvent, Category = "Immutable")
	void SetupDialog(const UDialogDescriptor* Descriptor);

	UFUNCTION(BlueprintImplementableEvent, Category = "Immutable")
	void UpdateDialogDescriptor(const UDialogDescriptor* Descriptor);

public:
	UPROPERTY(BlueprintAssignable)
	FDialogResultDelegate DialogResultDelegate;

private:
	FGameplayTag DialogTag;
};

/**
 * @class USellDialog
 * @breif Dialog used for selling
 */
UCLASS(Abstract)
class SAMPLEGAME426_API USellDialog : public UDialog
{
	GENERATED_BODY()

public:
	/** UDialog: Interface Begin */
	virtual void ExecuteDialogAction(const UDialogButton* Button) override;
	/** UDialog: Interface End */

	FString GetPrice() const;

protected:
	UPROPERTY(BlueprintReadOnly, Meta=(BindWidget))
	UEditableTextBox* PriceEditableTextBox;
};


/**
 * @class UTransakDialog
 * @breif Dialog used for Transak Widget
 */
UCLASS(Abstract)
class SAMPLEGAME426_API UTransakDialog : public UDialog
{
	GENERATED_BODY()
protected:
	/** UActivatableWidget: Interface Begin */
	virtual void NativeOnActivated() override;
	/** UActivatableWidget: Interface Begin */

protected:
	UPROPERTY(BlueprintReadOnly, Meta=(BindWidget))
	UTransakWebBrowser* WebBrowser = nullptr;
};