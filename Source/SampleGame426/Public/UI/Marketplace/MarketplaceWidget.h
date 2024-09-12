#pragma once

#include "Base/ActivatableWidget.h"
#include "Base/ItemListWidget.h"
#include "Interfaces/ItemListInterface.h"

#include "MarketplaceWidget.generated.h"


UCLASS(Abstract)
class SAMPLEGAME426_API UMarketplaceWidget : public UActivatableWidget, public IItemListInterface
{
	GENERATED_BODY()

public:
	virtual void RefreshItemList() override;

protected:
	/* UUserWidget */
	virtual void NativeConstruct() override;
	/* UUserWidget */

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UItemListWidget* ListPanel = nullptr;
	
};