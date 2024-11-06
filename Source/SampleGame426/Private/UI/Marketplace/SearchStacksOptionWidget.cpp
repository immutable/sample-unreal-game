#include "Marketplace/SearchStacksOptionWidget.h"

#include "APIMetadataSearchApiOperations.h"
#include "CustomGameInstance.h"
#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "UIGameplayTags.h"
#include "Base/AWStackWithControlPanels.h"
#include "Immutable/ImmutableUtilities.h"
#include "Marketplace/MarketplacePolicy.h"


void USearchStacksOptionWidget::RefreshItemList(TOptional<FString> PageCursor)
{
	UMarketplacePolicy* Policy = GetOwningCustomLocalPLayer()->GetGameUIPolicy()->GetMarketplacePolicy();
	UApplicationConfig* ImmutableConfig = FImmutableUtilities::GetDefaultApplicationConfig();

	if (!Policy || !ImmutableConfig)
	{
		return;
	}

	ImmutablezkEVMAPI::APIMetadataSearchApi::ListFiltersRequest ListFiltersRequest;
	
	ListFiltersRequest.ContractAddress = Policy->GetSelectedContractAddress();
	ListFiltersRequest.ChainName = ImmutableConfig->GetzkEVMAPIChainName();

	Policy->GetStacksAPI()->ListFilters(ListFiltersRequest, ImmutablezkEVMAPI::APIMetadataSearchApi::FListFiltersDelegate::CreateUObject(this, &USearchStacksOptionWidget::OnListFiltersResponse));	
}

void USearchStacksOptionWidget::Refresh()
{
	Super::Refresh();

	RefreshItemList(TOptional<FString>());
}

void USearchStacksOptionWidget::SetKeyword(const FString& Keyword)
{
	if (UMarketplacePolicy* Policy = GetOwningCustomLocalPLayer()->GetGameUIPolicy()->GetMarketplacePolicy())
	{
		Policy->SetKeyword(Keyword);		
	}
}

void USearchStacksOptionWidget::SetTraits(const TArray<FNFTMetadataAttribute_TraitType>& Traits)
{
	if (UMarketplacePolicy* Policy = GetOwningCustomLocalPLayer()->GetGameUIPolicy()->GetMarketplacePolicy())
	{
		Policy->SetTraits(Traits);
	}
}

void USearchStacksOptionWidget::SetupControlButtons(UAWStackWithControlPanels* HostLayer)
{
	Super::SetupControlButtons(HostLayer);

	SearchButton = HostLayer->AddButton(NativeUIGameplayTags.UI_ControlPanel_Button_Search);

	if (SearchButton)
	{
		SearchButton->RegisterOnClick(UControlPanelButton::FOnControlPanelButtonClick::CreateWeakLambda(this, [this, HostLayer](FGameplayTag ButtonTag)
		{
			OnSearchInitilized();
			HostLayer->MoveToNextWidgetInGroup();
		}));
		ControlPanelButtons.Add(NativeUIGameplayTags.UI_ControlPanel_Button_Search, SearchButton);
		SearchButton->SetEnable();
	}
}

void USearchStacksOptionWidget::OnListFiltersResponse(const ImmutablezkEVMAPI::APIMetadataSearchApi::ListFiltersResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		UCustomGameInstance::SendDialogMessage(this, NativeUIGameplayTags.UI_Dialog_ErrorFull, UDialogSubsystem::CreateErrorDescriptorWithErrorText(TEXT("Error"), TEXT("Failed to acquire list of filters"), Response.GetHttpResponse()->GetContentAsString()));
		
		return;
	}

	auto Filters = Response.Content.Result.Filters;

	for (auto Filter : Filters)
	{
		TArray<FString> StringValues;
		
		for (auto FilterValue : Filter.Values)
		{
			StringValues.Add(FilterValue.Value);
		}
		
		AddMetadataFilter(Filter.Name, StringValues);
	}
}
