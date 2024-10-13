#pragma once

#include "Base/ActivatableWidgetWithControlPanels.h"
#include "UI/Interfaces/IItemListInterface.h"
#include "Base/ItemListWidget.h"
#include "Inventory/SearchNFTsItemWidget.h"
#include "OpenAPIStacksApi.h"
#include "ImmutableTsSdkApi_DefaultApi.h"
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
	
	virtual void SetupControlButtons(class UAWStackWithControlPanels* HostPanel) override;

	void OnSearchNFTsResponse(const ImmutableIndexerSearchAPI::OpenAPIStacksApi::SearchNFTsResponse& Response);
	void OnItemSelection(bool IsSelected, USearchNFTsItemWidget* ItemWidget);
	
private:
	void HandlePageData(const ImmutableIndexerSearchAPI::OpenAPIPage& PageData);
	UFUNCTION()
	void OnSellButtonClicked(FGameplayTag ButtonTag);
	UFUNCTION()
	void OnPlayerConfirmedSell(UDialog* DialogPtr, EDialogResult Result);
	void OnOrderbookPrepareListingPost(const ImmutableTsSdkApi::ImmutableTsSdkApi_DefaultApi::V1TsSdkOrderbookPrepareListingPostResponse& Response);
	void OnOrderbookCreateListingPost(const ImmutableTsSdkApi::ImmutableTsSdkApi_DefaultApi::V1TsSdkOrderbookCreateListingPostResponse& Response);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UItemListWidget* ListPanel = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* PreviousPageButton = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* NextPageButton = nullptr;

private:
	USearchNFTsItemWidget* SelectedItemWidget = nullptr;
	ImmutableIndexerSearchAPI::OpenAPIPage PageCursors;
	UControlPanelButton* SellButton = nullptr;

};
