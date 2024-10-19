#pragma once

#include "CustomUserWidget.h"

#include "TopPanelButton.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SAMPLEGAME426_API UTopPanelButton : public UCustomUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	void Show();
	void Hide();

	void SetIndex(int32 Index) { ButtonIndex = Index; }
	int32 GetIndex() const { return ButtonIndex; }
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void BP_SetText(const FString& Name);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void BP_OnClick();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void BP_OnHovered();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void BP_OnUnhovered();

	DECLARE_DELEGATE_OneParam(FOnClick, UTopPanelButton*);

	FOnClick OnClickDelegate;

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

private:
	int32 ButtonIndex = -1;

};
