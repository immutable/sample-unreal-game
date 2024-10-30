#pragma once

#include "CustomUserWidget.h"

#include "AWStackTopControlPanel.generated.h"

class UHorizontalBox;
class UTopPanelButton;

/**
 * @class UAWStackTopControlPanel  
 * @brief User widget with main and secondary button functionality
 */
UCLASS(Abstract)
class SAMPLEGAME426_API UAWStackTopControlPanel : public UCustomUserWidget
{
	GENERATED_BODY()

public:
	UTopPanelButton* GetMainButton(UTopPanelButton* SecondaryButton);
	TArray<UTopPanelButton*>* GetSecondaryButtons(UTopPanelButton* MainButton);

	UTopPanelButton* AddMainButton(const FString& ButtonTitle, int32 Index);
	UTopPanelButton* AddSecondaryButton(UTopPanelButton* MainButton, const FString& ButtonTitle, int32 Index);

	void ShowSecondaryButtons(UTopPanelButton* MainButton);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buttons")
	TSoftClassPtr<UTopPanelButton> MainButtonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buttons")
	TSoftClassPtr<UTopPanelButton> SecondaryButtonClass;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UHorizontalBox* MainButtonPanel = nullptr;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UHorizontalBox* SecondaryButtonPanel = nullptr;

private:
	TMap<UTopPanelButton* /* Main Button */, TArray<UTopPanelButton*> /* Secondary Buttons */> MapMainToSecondaryButtons;
	TMap<UTopPanelButton* /* Secondary Button */, UTopPanelButton* /* Main Button */> MapSecondaryToMainButtons;

	UPROPERTY(Transient)
	UTopPanelButton* ShownMainButton = nullptr;
};