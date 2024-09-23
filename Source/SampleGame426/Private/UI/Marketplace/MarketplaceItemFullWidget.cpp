#include "Marketplace/MarketplaceItemFullWidget.h"

#include "OpenAPIListing.h"
#include "OpenAPIStackBundle.h"
#include "Marketplace/MarketplaceListingsWidget.h"

#define MP_DESCRIPTION_DESCRIPTION TEXT("Description")
#define MP_DESCRIPTION_CREATED_AT TEXT("Created at")
#define MP_DESCRIPTION_UPDATED_AT TEXT("Updated at")


void UMarketplaceItemFullWidget::ProcessModel(const ImmutableOpenAPI::Model& Data)
{
	auto StackBundle = static_cast<const ImmutableOpenAPI::OpenAPIStackBundle&>(Data);

	FString StackName = StackBundle.Stack.Name.GetValue();

	SetThumbnail(StackName);
	SetName(StackName);

	FString Description = StackBundle.Stack.Description.IsSet() ? StackBundle.Stack.Description.GetValue() : TEXT("");
	
	AddDescriptionRecord(MP_DESCRIPTION_DESCRIPTION, Description);
	AddDescriptionRecord(MP_DESCRIPTION_CREATED_AT, StackBundle.Stack.CreatedAt.ToString());
	AddDescriptionRecord(MP_DESCRIPTION_UPDATED_AT, StackBundle.Stack.UpdatedAt.ToString());

	if (StackBundle.Stack.Attributes.IsSet())
	{
		for (auto Attribute : StackBundle.Stack.Attributes.GetValue())
		{
			TSharedPtr<FJsonValue> Value;

			Attribute.Value.FromJson(Value);
			AddMetadataAttribute(Attribute.TraitType, Value->AsString());
		}
	}
	

	for (const auto& Listing : StackBundle.Listings)
	{
		Listings->AddItem(Listing);
	}
}
