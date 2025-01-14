﻿#pragma once

#include "Subsystems/LocalPlayerSubsystem.h"

#include "InformationSubsystem.generated.h"

class UTextBlock;

UCLASS()
class SAMPLEGAME426_API UInformationSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ShowDisplayMessage(const FString& Message);

	UFUNCTION(BlueprintCallable)
	void SetDisplayMessageBlock(UTextBlock* TextBlock);

protected:
	UPROPERTY(Transient)
	TWeakObjectPtr<UTextBlock> MessageBlock;
};