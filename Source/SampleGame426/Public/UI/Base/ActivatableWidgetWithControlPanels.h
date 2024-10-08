﻿#pragma once

#include "ActivatableWidget.h"
#include "AWStackWithControlPanels.h"
#include "Data/ControlPanelButtonDataAsset.h"

#include "ActivatableWidgetWithControlPanels.generated.h"


UCLASS()
class UActivatableWidgetWithControlPanels : public UActivatableWidget
{
	GENERATED_BODY()

public:
	const TMap<FGameplayTag, EAWStackControlPanelSide>& GetControlButtonsData() const;

	virtual void SetupControlButtons(TMap<FGameplayTag, UControlPanelButton*>& Buttons);
	UFUNCTION(BlueprintImplementableEvent, Category = "Immutable")
	void BP_SetupControlButtons(const TMap<FGameplayTag, UControlPanelButton*>& Buttons);

	bool IsSwitchBetweenWindowsHandler() const { return SwitchBetweenWindowsHandler; }

protected:
	/* UUserWidget interface */
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;
	virtual void OnWidgetRebuilt() override;
	/* UUserWidget interface */

	UFUNCTION(BlueprintImplementableEvent, Category = Immutable, meta = (DisplayName = "On Back Button Clicked"))
	void BP_OnBackButtonClicked();

	UFUNCTION(BlueprintImplementableEvent, Category = Immutable, meta = (DisplayName = "On Forward Button Clicked"))
	void BP_OnForwardButtonClicked();

	UFUNCTION()
	virtual void OnBackButtonClicked(FGameplayTag ButtonTag);
	UFUNCTION()
	virtual void OnForwardButtonClicked(FGameplayTag ButtonTag);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Settings")
	TMap<FGameplayTag, EAWStackControlPanelSide> ControlPanelButtonsData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window Settings")
	bool SwitchBetweenWindowsHandler = true;
};