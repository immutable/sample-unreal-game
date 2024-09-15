#pragma once

#include "Base/ActivatableWidget.h"
#include "Base/ItemListWidget.h"
#include "Interfaces/ItemListInterface.h"

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

private:
	TSharedPtr<ImmutableQuery::FMP_SearchStacksRequestData> BuildRequestData(const FString& PageCursor);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UItemListWidget* ListPanel = nullptr;

private:
	int32 PageSize = 10;
	
};