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
	void SetIcon(const FSlateBrush& InBrush);
	void SetButtonTag(FGameplayTag& InTag);
	void Enable();
	void Disable();

	/* UUserWidget */
	virtual bool Initialize() override;
	/* UUserWidget */
	
protected:
	UFUNCTION()
	void HandleButtonClicked();

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UImage* Icon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UButton* ButtonHitbox;

	FGameplayTag ButtonTag;
	
};
