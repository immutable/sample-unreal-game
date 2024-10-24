#pragma once

#include "Blueprint/UserWidget.h"

#include "ItemListWidget.generated.h"

class UItemWidget;

/**
 * @class UItemListWidget
 * @brief A user widget with the functionality of displaying child widgets in a grid like fashion
 */
UCLASS(Abstract)
class SAMPLEGAME426_API UItemListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	int32 GetNumberOfColumns() const;
	int32 GetNumberOfRows() const;
	UItemWidget* GetItem(int32 Id);
	UItemWidget* GetItem(int32 Column, int32 Row);
	UItemWidget* GetSelectedItem() const;

	void ResetPanelItems();

protected:
	/** UUserWidget: Interface Begin */
	virtual TSharedRef<SWidget> RebuildWidget() override;
	/** UUserWidget: Interface Begin */

protected:
	UPROPERTY(EditAnywhere, Category = "Immutable")
	TSoftClassPtr<UItemWidget> ItemClass;

	UPROPERTY(EditDefaultsOnly, Category = "Immutable")
	int32 NumberOfRows = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Immutable")
	int32 NumberOfColumns = 5;

	UPROPERTY(EditAnywhere, Category = "Immutable")
	FMargin ItemPadding;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	class UGridPanel* ListPanel = nullptr;

private:
	TArray<UItemWidget*> CachedItems;
};