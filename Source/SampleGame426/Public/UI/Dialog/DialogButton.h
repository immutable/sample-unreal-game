#pragma once

#include "CustomUserWidget.h"
#include "DialogDescriptors.h"

#include "DialogButton.generated.h"


/**
 * 
 */
UCLASS(Abstract)
class SAMPLEGAME426_API UDialogButton : public UCustomUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = Dialog)
	void SetButtonAction(const FDialogAction& Action);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = Dialog)
	const FDialogAction& GetButtonAction() const;

	UFUNCTION(BlueprintImplementableEvent, Category = Dialog)
	void BP_SetActionText(const FText& Text);

protected:
	FDialogAction ButtonAction;
};
