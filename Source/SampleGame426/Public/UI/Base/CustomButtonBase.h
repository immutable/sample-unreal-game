#pragma once

#include "Blueprint/UserWidget.h"

#include "CustomButtonBase.generated.h"

class UButton;

DECLARE_DYNAMIC_DELEGATE(FOnCustomButtonClicked);

/**
 * @class UCustomButtonBase
 * @brief A user widget button with additional wrapper functionality
 */
UCLASS()
class SAMPLEGAME426_API UCustomButtonBase : public UUserWidget
{
	GENERATED_BODY()

public:
	/** UUserWidget: Interface Begin */
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	/** UUserWidget: Interface End */

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Button")
	virtual void ChangeEnableStatus(bool bNewEnableStatus);

	UFUNCTION(BlueprintImplementableEvent, Category = "Button", Meta = (DisplayName = "On Button Clicked"))
	void BP_OnButtonClicked();

	UFUNCTION(BlueprintImplementableEvent, Category = "Button", Meta = (DisplayName = "Change Enable Status"))
	void BP_ChangeEnableStatus(bool bEnableStatus);

protected:
	UFUNCTION()
	virtual void OnActualButtonClicked();

protected:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UButton* ActualButton = nullptr;
};