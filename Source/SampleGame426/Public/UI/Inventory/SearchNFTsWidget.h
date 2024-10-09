#pragma once

#include "UI/Interfaces/IItemListInterface.h"
#include "Base/ItemListWidget.h"
#include "OpenAPIStacksApi.h"
#include "Base/ActivatableWidgetWithControlPanels.h"
#include "ImmutableIndexerSearchAPI/Public/OpenAPIPage.h"

#include "SearchNFTsWidget.generated.h"


UCLASS(Abstract)
class SAMPLEGAME426_API USearchNfTsWidget : public UActivatableWidgetWithControlPanels, public IItemListInterface
{
	GENERATED_BODY()

public:
	virtual void RefreshItemList(TOptional<FString> PageCursor) override;

protected:
	/* UActivatableWidget */
	virtual void NativeOnActivated() override;
	/* UActivatableWidget */
	
	virtual void SetupControlButtons(TMap<FGameplayTag, UControlPanelButton*>& Buttons) override;

	void OnSearchNFTsResponse(const ImmutableIndexerSearchAPI::OpenAPIStacksApi::SearchNFTsResponse& Response);
	//virtual void ProcessModel(const ImmutableIndexerSearchAPI::Model& Data) override;
	
private:
	void HandlePageData(const ImmutableIndexerSearchAPI::OpenAPIPage& PageData);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UItemListWidget* ListPanel = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* PreviousPageButton = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* NextPageButton = nullptr;

	ImmutableIndexerSearchAPI::OpenAPIPage PageCursors;

};
