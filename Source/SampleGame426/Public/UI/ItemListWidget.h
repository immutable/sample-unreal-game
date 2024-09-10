
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/ItemListInterface.h"

#include "ItemListWidget.generated.h"


/**
 * 
 */
UCLASS(Abstract)
class SAMPLEGAME426_API UItemListWidget : public UUserWidget, public IItemListInterface
{
	GENERATED_BODY()

public:
	/* IItemListInterface */
	virtual void RefreshItemList() override;
	/* IItemListInterface */

protected:
	/* UUserWidget */
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void NativeConstruct() override;
	/* UUserWidget */

	void FillGrid();

protected:
	UPROPERTY(EditAnywhere, Category = "Immutable")
	TSoftClassPtr<class UItemWidget> ItemClass;

	UPROPERTY(EditAnywhere, Category = "Immutable")
	int32 NumberOfRows = 4;
	
	UPROPERTY(EditAnywhere, Category = "Immutable")
	int32 NumberOfColumns = 5;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UUniformGridPanel* ListPanel = nullptr;

private:
	TArray<UItemWidget*> CachedItems;

};
