#pragma once
#include "ActivatableWidget.h"
#include "Data/ControlPanelButtonDataAsset.h"

#include "ActivatableWidgetWithControls.generated.h"



UCLASS()
class UActivatableWidgetWithControls : public UActivatableWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Immutable Marketplace")
	UControlPanelButton* AddButtonToLeft(FGameplayTag ButtonTag);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Immutable Marketplace")
	UControlPanelButton* AddButtonToRight(FGameplayTag ButtonTag);

	UFUNCTION(BlueprintNativeEvent)
	void OnControlButtonClicked(FGameplayTag ButtonTag);
	virtual void OnControlButtonClicked_Implementation(FGameplayTag ButtonTag);

protected:
	/* UUserWidget interface */
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;
	//virtual void NativeOnInitialized() override;
	virtual void OnWidgetRebuilt() override;
	/* UUserWidget interface */

private:
	UControlPanelButton* AddButton(FGameplayTag ButtonTag, SHorizontalBox::FSlot* HorizontalSlot);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Metadata")
	TSoftObjectPtr<UControlPanelButtonDataAsset> ControlPanelButtonDefaults;

	UPROPERTY(EditAnywhere, Category = "Window Settings")
	bool bIsSwitchBetweenWidgetsHandler = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window Settings")
	float LeftPanelHorizontalWidthFill = 0.05f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window Settings")
	float RightPanelHorizontalWidthFill = 0.05f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window Settings")
	float CenterPanelHorizontalWidthFill = 0.9f;

	SHorizontalBox::FSlot* LeftPanelVerticalBoxSlot;
	SHorizontalBox::FSlot* RightPanelVerticalBoxSlot;
	SHorizontalBox::FSlot* CenterPanelVerticalBoxSlot;

	UPROPERTY()
	TArray<UControlPanelButton*> Buttons;

	UPROPERTY(Transient)
	UControlPanelButton* NextWidgetButton = nullptr;

	UPROPERTY(Transient)
	UControlPanelButton* PreviousWidgetButton = nullptr;
};
