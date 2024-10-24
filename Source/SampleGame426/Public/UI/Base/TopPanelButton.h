#pragma once

#include "CustomUserWidget.h"

#include "TopPanelButton.generated.h"

/**
 * @class UTopPanelButton 
 * @brief A user widget button for top panel with additional wrapper functionality
 */
UCLASS(Abstract)
class SAMPLEGAME426_API UTopPanelButton : public UCustomUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE_OneParam(FOnClick, UTopPanelButton*);

public:
	/** UUserWidget: Interface Begin */
	virtual void NativeOnInitialized() override;
	/** UUserWidget: Interface End */

	int32 GetIndex() const;

	void SetIndex(int32 NewIndex);

	void Show();
	void Hide();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void BP_SetText(const FString& Name);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void BP_OnClick();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void BP_OnHovered();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void BP_OnUnhovered();

protected:
	/** UUserWidget: Interface Begin */
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	/** UUserWidget: Interface End */

public:
	FOnClick OnClickDelegate;

private:
	int32 ButtonIndex = -1;
};