#pragma once

#include "Base/ActivatableWidgetWithControlPanels.h"
#include "UI/Interfaces/IItemListInterface.h"
#include "Marketplace/MarketplacePolicy.h"
#include "Base/ItemListWidget.h"
#include "Inventory/SearchNFTsItemWidget.h"
#include "OpenAPIStacksApi.h"
#include "OpenAPIOrderbookApi.h"
#include "OpenAPIOrdersApi.h"
#include "OpenAPIPage.h"

#include "SearchNFTsWidget.generated.h"


UCLASS(Abstract)
class SAMPLEGAME426_API USearchNfTsWidget : public UActivatableWidgetWithControlPanels, public IItemListInterface
{
	GENERATED_BODY()

public:
	virtual void RefreshItemList(TOptional<FString> PageCursor) override;

protected:
	/* UUserWidget */
	virtual void NativeOnInitialized() override;
	/* UUserWidget */
	/* UActivatableWidget */
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	/* UActivatableWidget */
	
	virtual void SetupControlButtons(class UAWStackWithControlPanels* HostLayer) override;

	void OnSearchNFTsResponse(const ImmutableOpenAPI::OpenAPIStacksApi::SearchNFTsResponse& Response);
	void OnItemSelection(bool IsSelected, UItemWidget* ItemWidget);
	
private:
	void HandlePageData(const ImmutableOpenAPI::OpenAPIPage& PageData);
	void OnButtonClicked(FGameplayTag ButtonTag);
	UFUNCTION()
	void OnPlayerConfirmedSell(UDialog* DialogPtr, EDialogResult Result);
	UFUNCTION()
	void OnPlayerConfirmedCancelSell(UDialog* DialogPtr, EDialogResult Result);
	void OnPrepareListing(const ImmutableTsSdkApi::OpenAPIOrderbookApi::PrepareListingResponse& Response);
	void OnCreateListing(const ImmutableTsSdkApi::OpenAPIOrderbookApi::CreateListingResponse& Response);
	void OnCancelOrdersOnChain(const ImmutableTsSdkApi::OpenAPIOrderbookApi::CancelOrdersOnChainResponse& Response);

	UFUNCTION()
	void OnProcessDialogAction(UDialog* DialogPtr, EDialogResult Result);
	
	void ConfirmListing(const FString& ListingId);
	void OnGetListing(const ImmutableOpenAPI::OpenAPIOrdersApi::GetListingResponse& Response);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UItemListWidget* ListPanel = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* PreviousPageButton = nullptr;
	UPROPERTY(Transient)
	UControlPanelButton* NextPageButton = nullptr;

private:
	TWeakObjectPtr<UMarketplacePolicy> Policy;
	USearchNFTsItemWidget* SelectedItemWidget = nullptr;
	ImmutableOpenAPI::OpenAPIPage PageCursors;
	UControlPanelButton* SellButton = nullptr;
	UControlPanelButton* CancelSellButton = nullptr;
	UDialog* ProcessingDialog = nullptr;

};
