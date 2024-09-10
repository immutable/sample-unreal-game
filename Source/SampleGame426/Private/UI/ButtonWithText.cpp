// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonWithText.h"

#include "Components/TextBlock.h"

void UButtonWithText::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (Title)
	{
		Title->SetText(TitleText);
	}
}
