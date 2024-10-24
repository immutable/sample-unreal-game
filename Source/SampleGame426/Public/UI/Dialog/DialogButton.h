#pragma once

#include "CustomUserWidget.h"
#include "UI/Dialog/DialogDescriptors.h"

#include "DialogButton.generated.h"

/**
 * @class UDialogButton
 * @breif A user widget button for dialogs
 */
UCLASS(Abstract)
class SAMPLEGAME426_API UDialogButton : public UCustomUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = Dialog)
	const FDialogAction& GetButtonAction() const;

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = Dialog)
	void SetButtonAction(const FDialogAction& Action);

	UFUNCTION(BlueprintImplementableEvent, Category = Dialog)
	void BP_SetActionText(const FText& Text);

protected:
	FDialogAction ButtonAction;
};