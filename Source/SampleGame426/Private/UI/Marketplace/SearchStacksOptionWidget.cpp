#include "Marketplace/SearchStacksOptionWidget.h"

#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "UIGameplayTags.h"
#include "Base/AWStackWithControlPanels.h"
#include "Marketplace/MarketplacePolicy.h"


void USearchStacksOptionWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	if (UNFTMetadataAttributeDataAsset* Metadata = AttributeMetadata.LoadSynchronous())
	{
		for (const auto Trait : Metadata->TraitType)
		{
			AddMetadataFilter(Trait.Name, Trait.Values);	
		}
	}
	if (SearchButton)
	{
		SearchButton->Show();
	}
}

void USearchStacksOptionWidget::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	if (SearchButton)
	{
		SearchButton->Hide();
	}
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
		SearchButton->RegisterOnClick(UControlPanelButton::FOnControlPanelButtonClick::CreateWeakLambda(this, [HostLayer](FGameplayTag ButtonTag)
		{
			HostLayer->MoveToNextWidgetInGroup();
		}));
		SearchButton->SetEnable();
	}
}
