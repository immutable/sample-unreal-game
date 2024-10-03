#pragma once

#include "OpenAPIPage.h"
#include "OpenAPISearchApi.h"
#include "Base/ActivatableWidget.h"
#include "Base/ActivatableWidgetWithControlPanels.h"
#include "Base/ItemListWidget.h"
#include "UI/Interfaces/IItemListInterface.h"

#include "SearchStacksWidget.generated.h"


/*
 * 
 */
UCLASS(Abstract)
class SAMPLEGAME426_API USearchStacksWidget : public UActivatableWidgetWithControlPanels, public IItemListInterface
{
	GENERATED_BODY()

public:
	USearchStacksWidget();
	virtual void RefreshItemList(TOptional<FString> PageCursor) override;

protected:
	/* UActivatableWidget */
	virtual void NativeOnActivated() override;
	virtual void OnWidgetRebuilt() override;
	/* UActivatableWidget */

	void OnSearchStacksResponse(const ImmutableOpenAPI::OpenAPISearchApi::SearchStacksResponse& Response);
	virtual void SetupControlButtons(TMap<FGameplayTag, UControlPanelButton*>& Buttons) override;

private:
	void HandlePageData(const ImmutableOpenAPI::OpenAPIPage& PageData);

	UFUNCTION()
	void OnPageDirectionButtonClicked(FGameplayTag ButtonTag);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UItemListWidget* ListPanel = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* PreviousPageButton = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* NextPageButton = nullptr;

	ImmutableOpenAPI::OpenAPIPage PageCursors;
	
};