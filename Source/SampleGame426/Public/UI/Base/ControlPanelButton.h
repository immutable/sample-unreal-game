#pragma once

#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"

#include "ControlPanelButton.generated.h"

UENUM(BlueprintType)
enum class EAWStackControlPanelSide : uint8
{
	Left,
	Right,
};

/**
 * 
 */
UCLASS(Abstract)
class SAMPLEGAME426_API UControlPanelButton : public UUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnControlPanelButtonClicked, FGameplayTag, ButtonTag);
	
	void SetIcon(const FSlateBrush& InBrush);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "Control Panel")
	void SetColor(const FLinearColor& InColor);
	void SetButtonTag(FGameplayTag& InTag);
	void SetName(const FText& InName);
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Control Panel")
	void SetEnable(bool IsEnabled = true);
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Control Panel")
	bool IsEnabled();
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Control Panel")
	void Hide();
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Control Panel")
	void Show();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "Control Panel")
	void BP_OnActivationStatusChanged(bool IsEnabled);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "Control Panel")
	void BP_OnHovered();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "Control Panel")
	void BP_OnUnhovered();

	/* UUserWidget */
	virtual bool Initialize() override;
	/* UUserWidget */
	
protected:
	/* UUserWidget interface */
	virtual void NativeDestruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	/* UUserWidget interface */
	
	UFUNCTION()
	void HandleButtonClicked();

public:
	UPROPERTY(BlueprintAssignable)
	FOnControlPanelButtonClicked OnPanelButtonClicked;

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UImage* Icon;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* ButtonName = nullptr;

private:
	FGameplayTag ButtonTag;
	bool bIsEnabled = true;
	
};
