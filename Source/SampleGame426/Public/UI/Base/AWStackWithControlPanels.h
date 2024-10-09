#pragma once

#include "GameplayTagContainer.h"
#include "Base/ActivatableWidgetContainer.h"
#include "Data/ControlPanelButtonDataAsset.h"

#include "AWStackWithControlPanels.generated.h"


UENUM(BlueprintType)
enum class EAWStackControlPanelSide : uint8
{
	Left,
	Right,
};
/**
 *
 */
UCLASS()
class UAWStackWithControlPanels : public UActivatableWidgetStack
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Immutable Marketplace")
	UControlPanelButton* AddButtonToLeft(FGameplayTag ButtonTag);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Immutable Marketplace")
	UControlPanelButton* AddButtonToRight(FGameplayTag ButtonTag);

	/* UWidget interface */
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	/* UWidget interface */

protected:
	/* UWidget interface */
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;
	/* UWidget interface */

	virtual void OnWidgetAddedToList(UActivatableWidget& AddedWidget) override;

private:
	UControlPanelButton* AddButton(FGameplayTag ButtonTag, EAWStackControlPanelSide Side);
	UControlPanelButton* GetButton(FGameplayTag ButtonTag);

protected:
	UPROPERTY(EditAnywhere, Category = "Window Settings")
	TSoftObjectPtr<UControlPanelButtonDataAsset> ControlPanelButtonDefaults;
	UPROPERTY(EditAnywhere, Category = "Window Settings")
	TSubclassOf<UCustomUserWidget> TopPanelWidgetClass;
	UPROPERTY(EditAnywhere, Category = "Window Settings")
	TSubclassOf<UCustomUserWidget> BottomPanelWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window Settings")
	FSlateBrush PanelsBrush;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window Settings")
	FSlateBrush ActivatableWidgetBackgroundBrush;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Settings")
	FMargin ActivatableWidgetPadding;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Settings")
	FMargin PanelsPadding;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Settings")
	FMargin ButtonPadding;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window Settings")
	float TopPanelVerticalHeightFill = 0.05f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window Settings")
	float CenterPanelVerticalHeightFill = 0.9f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window Settings")
	float BottomPanelVerticalHeightFill = 0.05f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window Settings")
	float LeftPanelHorizontalWidthFill = 0.05f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window Settings")
	float RightPanelHorizontalWidthFill = 0.05f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window Settings")
	float CenterPanelHorizontalWidthFill = 0.9f;

private:
	UPROPERTY(Transient)
	UCustomUserWidget* TopPanelWidget = nullptr;
	UPROPERTY(Transient)
	UCustomUserWidget* BottomPanelWidget = nullptr;

	UPROPERTY(Transient)
	TMap<FGameplayTag, UControlPanelButton*> ControlPanelButtons;

	TSharedPtr<SVerticalBox> MyVerticalBox;
	TSharedPtr<SVerticalBox> LeftControlPanel;
	TSharedPtr<SVerticalBox> RightControlPanel;

};
