#pragma once

#include "CustomUserWidget.h"

#include "ItemWidget.generated.h"


/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class SAMPLEGAME426_API UItemWidget : public UCustomUserWidget
{
	GENERATED_BODY()

public:
	void Show();
	void Hide();
	virtual void SetOriginalState();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "ItemWidget")
	void BP_OnSelectionChange(bool IsSelected);

	virtual void SetSelection(bool IsSelected);

	DECLARE_DELEGATE_TwoParams(FOnSelectionChange, bool /* IsSelected */, UItemWidget* /* ItemWidget */)
	DECLARE_DELEGATE_OneParam(FOnDoubleClick, UItemWidget* /* ItemWidget */)
	
	void RegisterOnSelectionChange(const FOnSelectionChange& InOnSelectionChangeDelegate);
	void RegisterOnDoubleClick(const FOnDoubleClick& InOnDoubleClickDelegate);

protected:
	/* UUserWidget interface */
	virtual bool Initialize() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	/* UUserWidget interface */

	virtual void OnClick() {}
	virtual void OnDoubleClick() {}

private:
	FOnSelectionChange OnSelectionChangeDelegate;
	FOnDoubleClick OnDoubleClickDelegate;
	bool bIsSelected = false;
	
};
