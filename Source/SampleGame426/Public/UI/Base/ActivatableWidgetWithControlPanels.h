#pragma once

#include "GameplayTags.h"

#include "UI/Base/ActivatableWidget.h"

#include "ActivatableWidgetWithControlPanels.generated.h"

class UAWStackWithControlPanels;
class UActivatableWidgetWithControlPanels;
class UControlPanelButton;

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

/**
 * @class UActivatableWidgetWithControlPanels
 * @brief Activatable widget with (UControlPanelButton) widget grouping
 */
UCLASS()
class UActivatableWidgetWithControlPanels : public UActivatableWidget
{
	GENERATED_BODY()

public:
	/** UActivatableWidget: Interface Begin */
	virtual bool CanBeReleased() const override;
	virtual void Reset() override;
	/** UActivatableWidget: Interface End */

	UFUNCTION(BlueprintPure)
	FString GetWidgetTitle() const;

	UFUNCTION(BlueprintPure)
	int32 GetIndexInGroup() const;

	const FActivatableWidgetWithControlPanelsGroup* GetOwningGroup() const;

	UFUNCTION(BlueprintCallable)
	void SetIndexInGroup(int32 NewIndexInGroup);

	UFUNCTION(BlueprintCallable)
	void SetCanBeReleased();

	void SetOwningGroup(FActivatableWidgetWithControlPanelsGroup* NewOwningGroup);

	UFUNCTION(BlueprintCallable)
	virtual void Refresh() {}

	virtual void SetupControlButtons(UAWStackWithControlPanels* HostLayer) {}

protected:
	/** UUserWidget: Interface Begin */
	virtual void NativeDestruct() override;
	/** UUserWidget: Interface End */

	/** UActivatableWidget: Interface Begin */
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	/** UActivatableWidget: Interface Begin */

	UFUNCTION(BlueprintImplementableEvent, Category = "ActivatableWidget", Meta = (DisplayName = "On Back Button Clicked"))
	void BP_OnBackButtonClicked();

	UFUNCTION(BlueprintImplementableEvent, Category = "ActivatableWidget", Meta = (DisplayName = "On Forward Button Clicked"))
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

	/** The index of this widget within its group. */
	int32 IndexInGroup = -1;

	/** The group in which owns this widget. */
	FActivatableWidgetWithControlPanelsGroup* OwningGroup = nullptr;
};