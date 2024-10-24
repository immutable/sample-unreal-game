#pragma once

#include "GameplayTagContainer.h"

#include "UI/Base/ActivatableWidgetContainer.h"
#include "UI/Data/ControlPanelButtonDataAsset.h"

#include "AWStackWithControlPanels.generated.h"

struct FActivatableWidgetWithControlPanelsGroup;

class UAWStackTopControlPanel;
class UCustomUserWidget;
class UTopPanelButton;

/**
 * @class UAWStackWithControlPanels 
 * @brief Slate widget with the functionality to manage and organise multiple control panels.
 */
UCLASS()
class UAWStackWithControlPanels : public UActivatableWidgetStack
{
	GENERATED_BODY()

public:
	UAWStackWithControlPanels(const FObjectInitializer& Initializer);

	/** UWidget: Interface Begin */
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	/** UWidget: Interface End */

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Immutable Marketplace")
	UControlPanelButton* AddButtonToLeft(FGameplayTag ButtonTag);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Immutable Marketplace")
	UControlPanelButton* AddButtonToRight(FGameplayTag ButtonTag);

	UControlPanelButton* GetButton(FGameplayTag ButtonTag);
	UControlPanelButton* AddButton(FGameplayTag ButtonTag, EAWStackControlPanelSide Side);

	void MoveToNextWidgetInGroup();
	void MoveToPrevWidgetInGroup();

protected:
	/** UWidget: Interface Begin */
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void OnWidgetRebuilt() override;
	virtual void SynchronizeProperties() override;
	/** UWidget: Interface End */

	/** UActivatableWidgetContainer: Interface Begin */
	virtual void OnWidgetAddedToList(UActivatableWidget& AddedWidget) override;
	/** UActivatableWidgetContainer: Interface End */

	void OnControlPanelButtonClicked(FGameplayTag ButtonTag);
	void OnMainPanelButtonClicked(UTopPanelButton* Button);
	void OnSecondaryPanelButtonClicked(UTopPanelButton* Button);

private:
	void BuildTopPanel();
	void BuildControlPanel();
	void ShowWidgetFromGroup(FActivatableWidgetWithControlPanelsGroup*, int32 WidgetIndex = 0);
	void ClearWidgetFromGroup(FActivatableWidgetWithControlPanelsGroup* Group);

protected:
	UPROPERTY(EditAnywhere, Category = "Window Settings")
	TSoftObjectPtr<UControlPanelButtonDataAsset> ControlPanelButtonDefaults;

	UPROPERTY(EditAnywhere, Category = "Window Settings")
	TSubclassOf<UAWStackTopControlPanel> TopPanelWidgetClass;

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
	TArray<FActivatableWidgetWithControlPanelsGroup> WidgetGroups;

private:
	UPROPERTY(Transient)
	UAWStackTopControlPanel* TopPanelWidget = nullptr;

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
	TMap<UTopPanelButton*, FActivatableWidgetWithControlPanelsGroup*> MapMainButtonToWidgetGroup;
	TPair<FActivatableWidgetWithControlPanelsGroup* /* Group */, int32 /* Widget Index */> DisplayedWidgetGroupPair;
};