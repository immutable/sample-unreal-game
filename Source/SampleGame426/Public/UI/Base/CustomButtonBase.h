// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomButtonBase.generated.h"


DECLARE_DYNAMIC_DELEGATE(FOnCustomButtonClicked);

/**
 * 
 */
UCLASS()
class SAMPLEGAME426_API UCustomButtonBase : public UUserWidget
{
	GENERATED_BODY()

public:
	/* UUserWidget */
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	/* UUserWidget */

	UFUNCTION()
	virtual void OnActualButtonClicked();

	UFUNCTION(BlueprintImplementableEvent, Category = UCustomButtonBase, meta = (DisplayName = "On Button Clicked"))
	void BP_OnButtonCLicked();
	//
	// UPROPERTY(BlueprintAssignable, Category = "Immutable", meta = (AllowPrivateAccess = true))
	// FOnCustomButtonClicked OnCustomButtonClicked;

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = UCustomButtonBase)
	virtual void ChangeEnableStatus(bool EnableStatus);

	UFUNCTION(BlueprintImplementableEvent, Category = UCustomButtonBase, meta = (DisplayName = "Change Enable Status"))
	void BP_ChangeEnableStatus(bool EnableStatus);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UButton* ActualButton = nullptr;
	
};
