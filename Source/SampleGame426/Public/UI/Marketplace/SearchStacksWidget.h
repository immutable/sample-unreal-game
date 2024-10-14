#pragma once

#include "OpenAPIPage.h"
#include "OpenAPIStacksApi.h"
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
	virtual void RefreshItemList(TOptional<FString> PageCursor) override;

protected:
	/* UActivatableWidget */
	virtual void NativeOnActivated() override;
	virtual void OnWidgetRebuilt() override;
	/* UActivatableWidget */

	void OnSearchStacksResponse(const ImmutableOpenAPI::OpenAPIStacksApi::SearchStacksResponse& Response);
	virtual void SetupControlButtons(class UAWStackWithControlPanels* HostPanel) override;

private:
	void HandlePageData(const ImmutableOpenAPI::OpenAPIPage& PageData);

	UFUNCTION()
	void OnPageDirectionButtonClicked(FGameplayTag ButtonTag);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UItemListWidget* ListPanel = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* PreviousPageButton = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* NextPageButton = nullptr;

	ImmutableOpenAPI::OpenAPIPage PageCursors;
	
};