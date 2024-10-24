#pragma once

#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"

#include "ControlPanelButton.generated.h"

class UImage;
class UTextBlock;

UENUM(BlueprintType)
enum class EAWStackControlPanelSide : uint8
{
	Left,
	Right,
};

/**
 * @class UControlPanelButton 
 * @brief A user widget button tailored for control panels
 */
UCLASS(Abstract)
class SAMPLEGAME426_API UControlPanelButton : public UUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE_OneParam(FOnControlPanelButtonClick, FGameplayTag);

public:
	/** UUserWidget: Interface Begin */
	virtual bool Initialize() override;
	/** UUserWidget: Interface End */

	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Control Panel")
	bool IsEnabled() const;

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Control Panel")
	void SetEnable(bool bNewIsEnabled = true);

	void SetIcon(const FSlateBrush& NewIcon);
	void SetButtonTag(FGameplayTag& NewButtonTag);
	void SetName(const FText& NewName);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "Control Panel")
	void SetColor(const FLinearColor& NewColor);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Control Panel")
	void Show();

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Control Panel")
	void Hide();

	void RegisterOnClick(const FOnControlPanelButtonClick& InOnControlPanelButtonClick);

protected:
	/** UUserWidget: Interface Begin */
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	/** UUserWidget: Interface End */

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "Control Panel")
	void BP_OnActivationStatusChanged(bool IsEnabled);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "Control Panel")
	void BP_OnHovered();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "Control Panel")
	void BP_OnUnhovered();

protected:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UImage* Icon = nullptr;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UTextBlock* ButtonName = nullptr;

private:
	FOnControlPanelButtonClick OnControlPanelButtonClickDelegate;
	FGameplayTag ButtonTag;
	bool bIsEnabled = true;
};