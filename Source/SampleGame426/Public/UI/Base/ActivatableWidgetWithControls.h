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
	void AddButtonToLeft(FGameplayTag ButtonTag);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Immutable Marketplace")
	void AddButtonToRight(FGameplayTag ButtonTag);

	UFUNCTION(BlueprintImplementableEvent)
	void OnControlButtonClicked(FGameplayTag ButtonTag);

protected:
	/* UUserWidget interface */
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;
	/* UUserWidget interface */

private:
	void AddButton(FGameplayTag ButtonTag, SHorizontalBox::FSlot* HorizontalSlot);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Metadata")
	TSoftObjectPtr<UControlPanelButtonDataAsset> ControlPanelButtonDefaults;
	
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
};
