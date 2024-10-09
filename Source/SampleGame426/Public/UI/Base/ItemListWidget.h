
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ItemListWidget.generated.h"


/**
 * 
 */
UCLASS(Abstract)
class SAMPLEGAME426_API UItemListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ResetPanelItems();
	int32 GetNumberOfColumns() const;
	int32 GetNumberOfRows() const;
	class UItemWidget* GetItem(int32 id);
	class UItemWidget* GetItem(int32 Column, int32 Row);

protected:
	/* UUserWidget */
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void NativeConstruct() override;
	/* UUserWidget */

protected:
	UPROPERTY(EditAnywhere, Category = "Immutable")
	TSoftClassPtr<class UItemWidget> ItemClass;

	UPROPERTY(EditDefaultsOnly, Category = "Immutable")
	int32 NumberOfRows = 4;
	
	UPROPERTY(EditDefaultsOnly, Category = "Immutable")
	int32 NumberOfColumns = 5;

	UPROPERTY(EditAnywhere, Category = "Immutable")
	FMargin ItemPadding;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UGridPanel* ListPanel = nullptr;

private:
	TArray<UItemWidget*> CachedItems;

};
