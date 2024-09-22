#include "Marketplace/MarketplaceSearchOptionWidget.h"

#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "Marketplace/MarketplacePolicy.h"
#include "Online/ImmutableQuery.h"


void UMarketplaceSearchOptionWidget::NativeOnActivated()
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

void UMarketplaceSearchOptionWidget::SetKeyword(const FString& Keyword)
{
	if (UMarketplacePolicy* Policy = GetOwningCustomLocalPLayer()->GetGameUIPolicy()->GetMarketplacePolicy())
	{
		Policy->SetKeyword(Keyword);		
	}
}

void UMarketplaceSearchOptionWidget::SetTraits(const TArray<FNFTMetadataAttribute_TraitType>& Traits)
{
	if (UMarketplacePolicy* Policy = GetOwningCustomLocalPLayer()->GetGameUIPolicy()->GetMarketplacePolicy())
	{
		TArray<ImmutableQuery::FMP_SearchStacksRequestTraitData> SearchTraits;
		
		for (const auto Trait : Traits)
		{
			SearchTraits.Add({ Trait.Name, Trait.Values });
		}
		
		Policy->SetTraits(SearchTraits);
	}
}
