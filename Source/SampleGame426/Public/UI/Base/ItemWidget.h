#pragma once

#include "CustomUserWidget.h"

#include "ItemWidget.generated.h"

/**
 * @class UItemWidget
 * @brief A user widget with additional wrapper functionality for mouse related interactions
 */
UCLASS(Abstract, BlueprintType)
class SAMPLEGAME426_API UItemWidget : public UCustomUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE_TwoParams(FOnSelectionChange, bool /* bIsSelected */, UItemWidget* /* ItemWidget */)
	DECLARE_DELEGATE_OneParam(FOnDoubleClick, UItemWidget* /* ItemWidget */)

public:
	virtual void SetOriginalState();
	virtual void SetSelection(bool IsSelected);

	void Show();
	void Hide();

	void RegisterOnSelectionChange(const FOnSelectionChange& InOnSelectionChangeDelegate);
	void RegisterOnDoubleClick(const FOnDoubleClick& InOnDoubleClickDelegate);

protected:
	/** UUserWidget: Interface Begin */
	virtual bool Initialize() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	/** UUserWidget: Interface End */

	virtual void OnClick();
	virtual void OnDoubleClick();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "ItemWidget")
	void BP_OnSelectionChange(bool IsSelected);

private:
	FOnSelectionChange OnSelectionChangeDelegate;
	FOnDoubleClick OnDoubleClickDelegate;
	bool bIsSelected = false;
};