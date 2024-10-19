#pragma once

#include "CustomUserWidget.h"
#include "TopPanelButton.h"

#include "AWStackTopControlPanel.generated.h"


/**
 * 
 */
UCLASS(Abstract)
class SAMPLEGAME426_API UAWStackTopControlPanel : public UCustomUserWidget
{
	GENERATED_BODY()

public:
	UTopPanelButton* AddMainButton(const FString& ButtonTitle, int32 Index);
	UTopPanelButton* AddSecondaryButton(UTopPanelButton* MainButton, const FString& ButtonTitle, int32 Index);
	void ShowSecondaryButtons(UTopPanelButton* MainButton);
	UTopPanelButton* GetMainButton(UTopPanelButton* SecondaryButton);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buttons")
	TSoftClassPtr<UTopPanelButton> MainButtonClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buttons")
	TSoftClassPtr<UTopPanelButton> SecondaryButtonClass;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UHorizontalBox* MainButtonPanel = nullptr;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UHorizontalBox* SecondaryButtonPanel = nullptr;

private:
	TMap<UTopPanelButton* /* Main Button */, TArray<UTopPanelButton*> /* Secondary Buttons */> MapMainToSecondaryButtons;
	TMap<UTopPanelButton* /* Secondary Button */, UTopPanelButton* /* Main Button */> MapSecondaryToMainButtons;
	UTopPanelButton* ShownMainButton = nullptr;
};
