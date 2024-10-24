#pragma once

#include "GameplayTagContainer.h"

#include "UI/Base/ActivatableWidgetContainer.h"
#include "UI/Data/ControlPanelButtonDataAsset.h"
#include "UI/Base/ControlPanelButton.h"

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
	UControlPanelButton* GetButton(FGameplayTag ButtonTag);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Immutable Marketplace")
	UControlPanelButton* AddButton(FGameplayTag ButtonTag);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Immutable Marketplace")
	void MoveToNextWidgetInGroup();

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Immutable Marketplace")
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
	FSlateBrush ButtonPanelBackgroundBrush;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window Settings")
	FSlateBrush WindowPanelBackgroundBrush;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Settings")
	FMargin WindowPanelPadding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Settings")
	FMargin ButtonPanelPadding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Settings")
	FMargin ButtonPadding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window Settings")
	float TopPanelVerticalHeightFill = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window Settings")
	float WindowPanelVerticalHeightFill = 0.9f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window Settings")
	float BottomPanelVerticalHeightFill = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window Settings")
	float ButtonPanelHorizontalWidthFill = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Window Settings")
	float WindowPanelHorizontalWidthFill = 0.9f;

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

	UPROPERTY(Transient)
	UTopPanelButton* ActiveMainButton = nullptr;

	UPROPERTY(Transient)
	UTopPanelButton* ActiveSecondaryButton = nullptr;

	TSharedPtr<SVerticalBox> MyVerticalBox;
	TSharedPtr<SVerticalBox> ButtonPanel;

	TMap<UTopPanelButton*, FActivatableWidgetWithControlPanelsGroup*> MapMainButtonToWidgetGroup;
	TPair<FActivatableWidgetWithControlPanelsGroup* /* Group */, int32 /* Widget Index */> DisplayedWidgetGroupPair;
};