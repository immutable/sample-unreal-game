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
	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Immutable")
	int32 GetNumberOfColumns() const;

	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Immutable")
	int32 GetNumberOfRows() const;

	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Immutable")
	UItemWidget* GetItemById(int32 Id);

	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Immutable")
	UItemWidget* GetItemByRowColumn(int32 Row, int32 Column);

	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Immutable")
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