// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CustomButtonBase.h"

#include "CustomButtonWithText.generated.h"

/**
 *	
 */
UCLASS(meta=(DisableNativeTick))
class SAMPLEGAME426_API UCustomButtonWithText : public UCustomButtonBase
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

protected:
	UPROPERTY(EditAnywhere, Category="Custom", meta=(MultiLine="false"))
	FText TitleText;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* Title;
};
