#include "Marketplace/MarketplaceSearchOptionWidget.h"

void UMarketplaceSearchOptionWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	if (UNFTMetadataAttributeDataAsset* Metadata = AttributeMetadata.Get())
	{
		for (const auto Trait : Metadata->TraitType)
		{
			AddMetadataFilter(Trait.Name, Trait.Values);	
		}
	}
}
