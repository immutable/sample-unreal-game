#pragma once

#include "Base/ActivatableWidget.h"
#include "Base/ItemListWidget.h"
#include "UI/Interfaces/ItemListInterface.h"

#include "MarketplaceWidget.generated.h"

namespace ImmutableQuery
{
	struct FMP_SearchStacksRequestData;
}

UCLASS(Abstract)
class SAMPLEGAME426_API UMarketplaceWidget : public UActivatableWidget, public IItemListInterface
{
	GENERATED_BODY()

public:
	virtual void RefreshItemList() override;

protected:
	/* UActivatableWidget */
	virtual void NativeOnActivated() override;
	/* UActivatableWidget */

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UItemListWidget* ListPanel = nullptr;
	
};