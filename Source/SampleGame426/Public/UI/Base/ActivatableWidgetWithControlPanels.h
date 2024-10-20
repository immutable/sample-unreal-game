#pragma once

#include "ActivatableWidget.h"
#include "SelectionSet.h"
#include "Data/ControlPanelButtonDataAsset.h"

#include "ActivatableWidgetWithControlPanels.generated.h"


enum class EAWStackControlPanelSide : uint8;
class UActivatableWidgetWithControlPanels;

USTRUCT(BlueprintType)
struct FActivatableWidgetWithControlPanelsGroup
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActivatableWidgetGroup")
	FString GroupName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActivatableWidgetGroup")
	TArray<TSoftClassPtr<UActivatableWidgetWithControlPanels>> WidgetClassesGroup;

	UPROPERTY(Transient)
	TArray<UActivatableWidgetWithControlPanels*> WidgetsInGroup;
};

UCLASS()
class UActivatableWidgetWithControlPanels : public UActivatableWidget
{
	GENERATED_BODY()

public:
	FString GetTitle() const;
	void SetIndexInGroup(int32 InIndex) { IndexInGroup = InIndex; }
	int32 GetIndexInGroup() const { return IndexInGroup; }
	void SetGroup(FActivatableWidgetWithControlPanelsGroup* InGroup) { PartOfGroup = InGroup; }
	const FActivatableWidgetWithControlPanelsGroup* GetGroup() const { return PartOfGroup; }
	
	virtual void SetupControlButtons(class UAWStackWithControlPanels* HostLayer) {}
	virtual bool CanBeReleased() const override { return bCanBeReleased; }
	void SetCanBeReleased() { bCanBeReleased = true; }

protected:
	/* UUserWidget interface */
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;
	virtual void OnWidgetRebuilt() override;
	virtual void NativeDestruct() override;
	/* UUserWidget interface */

	/* UActivatableWidget interface */
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	/* UActivatableWidget interface */

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
	FString WidgetTitle;
	UPROPERTY()
	TMap<FGameplayTag, UControlPanelButton*> ControlPanelButtons;

private:
	bool bCanBeReleased = false;
	int32 IndexInGroup = -1;
	FActivatableWidgetWithControlPanelsGroup* PartOfGroup = nullptr;

};
