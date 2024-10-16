#pragma once

#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"

#include "ControlPanelButton.generated.h"

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
	void SetIconColor(const FLinearColor& InColor);
	void SetButtonTag(FGameplayTag& InTag);
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Control Panel")
	void Enable();
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Control Panel")
	void Disable();
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Control Panel")
	bool IsEnabled();
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Control Panel")
	void Hide();
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Control Panel")
	void Show();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "Control Panel")
	void BP_OnActivationStatusChanged(bool IsEnabled);

	bool IsButtonEnabled() const;

	/* UUserWidget */
	virtual bool Initialize() override;
	/* UUserWidget */
	
protected:
	virtual void NativeDestruct() override;
	
	UFUNCTION()
	void HandleButtonClicked();

public:
	UPROPERTY(BlueprintAssignable)
	FOnControlPanelButtonClicked OnPanelButtonClicked;

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UImage* Icon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UButton* ButtonHitbox;

	FGameplayTag ButtonTag;
	
};
