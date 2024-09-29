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
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "ControlPanel")
	void Enable();
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "ControlPanel")
	void Disable();
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "ControlPanel")
	void Hide();
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "ControlPanel")
	void Show();

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
