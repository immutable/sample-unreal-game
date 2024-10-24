#pragma once

#include "CustomButtonBase.h"

#include "CustomButtonWithText.generated.h"

/**
 * @class UCustomButtonWithText
 * @brief A custom button with text
 */
UCLASS(Meta = (DisableNativeTick))
class SAMPLEGAME426_API UCustomButtonWithText : public UCustomButtonBase
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Button", Meta = (MultiLine = "false"))
	FText TitleText;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	class UTextBlock* Title;
};