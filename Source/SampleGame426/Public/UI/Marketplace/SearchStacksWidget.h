#pragma once

#include "OpenAPISearchApi.h"
#include "Base/ActivatableWidget.h"
#include "Base/ItemListWidget.h"
#include "UI/Interfaces/ItemListInterface.h"

#include "SearchStacksWidget.generated.h"


/*
 * 
 */
UCLASS(Abstract)
class SAMPLEGAME426_API USearchStacksWidget : public UActivatableWidget, public IItemListInterface
{
	GENERATED_BODY()

public:
	virtual void RefreshItemList() override;

protected:
	/* UActivatableWidget */
	virtual void NativeOnActivated() override;
	/* UActivatableWidget */

	void OnSearchStacksResponse(const ImmutableOpenAPI::OpenAPISearchApi::SearchStacksResponse& Response);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UItemListWidget* ListPanel = nullptr;
	
};