#pragma once

#include "GameplayTagContainer.h"
#include "Base/ActivatableWidgetContainer.h"
#include "Data/ControlPanelButtonDataAsset.h"

#include "AWStackWithControlPanels.generated.h"


class UTopPanelButton;
/**
 *
 */
UCLASS()
class UAWStackWithControlPanels : public UActivatableWidgetStack
{
	GENERATED_BODY()

public:
	UAWStackWithControlPanels(const FObjectInitializer& Initializer);
	
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Immutable Marketplace")
	UControlPanelButton* AddButtonToLeft(FGameplayTag ButtonTag);
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Immutable Marketplace")
	UControlPanelButton* AddButtonToRight(FGameplayTag ButtonTag);
	UControlPanelButton* AddButton(FGameplayTag ButtonTag, EAWStackControlPanelSide Side);
	UControlPanelButton* GetButton(FGameplayTag ButtonTag);

	void MoveToNextWidgetInGroup();
	void MoveToPrevWidgetInGroup();

	/* UWidget interface */
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	/* UWidget interface */

protected:
	/* UWidget interface */
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void OnWidgetRebuilt() override;
	virtual void SynchronizeProperties() override;
	/* UWidget interface */

	virtual void OnWidgetAddedToList(UActivatableWidget& AddedWidget) override;

	void OnControlPanelButtonClicked(FGameplayTag ButtonTag);
	void OnMainPanelButtonClicked(UTopPanelButton* Button);
	void OnSecondaryPanelButtonClicked(UTopPanelButton* Button);

private:
	void BuildTopPanel();
	void BuildControlPanel();
	void ShowWidgetFromGroup(struct FActivatableWidgetWithControlPanelsGroup*, int32 WidgetIndex = 0);
	void ClearWidgetFromGroup(struct FActivatableWidgetWithControlPanelsGroup* Group);

protected:
	UPROPERTY(EditAnywhere, Category = "Window Settings")
	TSoftObjectPtr<UControlPanelButtonDataAsset> ControlPanelButtonDefaults;
	UPROPERTY(EditAnywhere, Category = "Window Settings")
	TSubclassOf<class UAWStackTopControlPanel> TopPanelWidgetClass;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget Groups")
	TArray<struct FActivatableWidgetWithControlPanelsGroup> WidgetGroups;
	
private:
	UPROPERTY(Transient)
	class UAWStackTopControlPanel* TopPanelWidget = nullptr;
	UPROPERTY(Transient)
	UCustomUserWidget* BottomPanelWidget = nullptr;

	UPROPERTY(Transient)
	TMap<FGameplayTag, UControlPanelButton*> ControlPanelButtons;

	UPROPERTY(Transient)
	UControlPanelButton* PreviousWidgetInGroupButton = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* NextWidgetInGroupButton = nullptr;

	TSharedPtr<SVerticalBox> MyVerticalBox;
	TSharedPtr<SVerticalBox> LeftControlPanel;
	TSharedPtr<SVerticalBox> RightControlPanel;

	UTopPanelButton* ActiveMainButton = nullptr;
	UTopPanelButton* ActiveSecondaryButton = nullptr;
	TMap<UTopPanelButton*, struct FActivatableWidgetWithControlPanelsGroup*> MapMainButtonToWidgetGroup;
	TPair<FActivatableWidgetWithControlPanelsGroup* /* Group */, int32 /* Widget Index */> DisplayedWidgetGroupPair;

};
