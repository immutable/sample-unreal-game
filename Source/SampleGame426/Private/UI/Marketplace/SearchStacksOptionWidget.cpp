#include "Marketplace/SearchStacksOptionWidget.h"

#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
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

// void USearchStacksOptionWidget::SetupControlButtons_Implementation(TMap<FGameplayTag, UControlPanelButton*>& Buttons)
// {
// 	Super::SetupControlButtons_Implementation(Buttons);
//
// 	for (auto Button : Buttons)
// 	{
// 		Button.Value->OnPanelButtonClicked.AddUniqueDynamic(this, &USearchStacksOptionWidget::OnPageDirectionButtonClicked);
// 	}
// 	
// }
//
// void USearchStacksOptionWidget::OnForwardButtonClicked(FGameplayTag ButtonTag)
// {
// 	Super::OnForwardButtonClicked(ButtonTag);
//
// 	
// }
