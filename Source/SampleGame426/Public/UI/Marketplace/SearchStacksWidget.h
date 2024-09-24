#pragma once

#include "OpenAPIPage.h"
#include "OpenAPISearchApi.h"
#include "Base/ActivatableWidgetWithControls.h"
#include "Base/ItemListWidget.h"
#include "UI/Interfaces/ItemListInterface.h"

#include "SearchStacksWidget.generated.h"


/*
 * 
 */
UCLASS(Abstract)
class SAMPLEGAME426_API USearchStacksWidget : public UActivatableWidgetWithControls, public IItemListInterface
{
	GENERATED_BODY()

public:
	virtual void RefreshItemList(TOptional<FString> PageCursor) override;

protected:
	/* UActivatableWidget */
	virtual void NativeOnActivated() override;
	virtual void OnWidgetRebuilt() override;
	/* UActivatableWidget */

	void OnSearchStacksResponse(const ImmutableOpenAPI::OpenAPISearchApi::SearchStacksResponse& Response);
	virtual void OnControlButtonClicked_Implementation(FGameplayTag ButtonTag) override;

private:
	void HandlePageData(const ImmutableOpenAPI::OpenAPIPage& PageData);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UItemListWidget* ListPanel = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* PreviousPageButton = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* NextPageButton = nullptr;

	ImmutableOpenAPI::OpenAPIPage PageCursors;
	
};