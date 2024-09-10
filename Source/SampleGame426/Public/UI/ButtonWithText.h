// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonBase.h"
#include "ButtonWithText.generated.h"

/**
 *	
 */
UCLASS(meta=(DisableNativeTick))
class SAMPLEGAME426_API UButtonWithText : public UButtonBase
{
	GENERATED_BODY()

public:

protected:
	virtual void NativePreConstruct() override;

protected:
	UPROPERTY(EditAnywhere, Category="Custom", meta=(MultiLine="false"))
	FText TitleText;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* Title;
};
