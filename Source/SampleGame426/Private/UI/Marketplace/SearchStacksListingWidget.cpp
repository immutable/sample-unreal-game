#include "Marketplace/SearchStacksListingWidget.h"

#include "CustomGameInstance.h"
#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "LogSampleGame.h"
#include "OpenAPIListing.h"
#include "OpenAPIStackBundle.h"
#include "UIGameplayTags.h"
#include "Marketplace/MarketplacePolicy.h"
#include "Marketplace/SearchStacksListing_ListingsWidget.h"
#include "OpenAPIFulfillOrderRequest.h"
#include "OpenAPIOrderbookApiOperations.h"

#define MP_DESCRIPTION_DESCRIPTION TEXT("Description")
#define MP_DESCRIPTION_CREATED_AT TEXT("Created at")
#define MP_DESCRIPTION_UPDATED_AT TEXT("Updated at")

#define LOCTEXT_NAMESPACE "ImmutableUI"

void USearchStacksListingWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (Listings)
	{
		Listings->RegisterOnSelectionStatusChange(USearchStacksListing_ListingsWidget::FOnSelectionStatusChange::CreateUObject(this, &USearchStacksListingWidget::OnSelectionStatusChange));		
	}
}

void USearchStacksListingWidget::SetupControlButtons(class UAWStackWithControlPanels* HostPanel)
{
	Super::SetupControlButtons(HostPanel);

	BuyButton = HostPanel->GetButton(FUIControlPanelButtons::Buy);

	if (BuyButton)
	{
		BuyButton->OnPanelButtonClicked.AddUniqueDynamic(this, &USearchStacksListingWidget::OnBuyButtonClicked);
	}
}

void USearchStacksListingWidget::ProcessModel(const ImmutableOpenAPI::Model& Data)
{
	auto StackBundle = static_cast<const ImmutableOpenAPI::OpenAPIStackBundle&>(Data);

	FString StackName = StackBundle.Stack.Name.GetValue();

	// set name and thumbnail
	if (UMarketplacePolicy* Policy = GetOwningCustomLocalPLayer()->GetGameUIPolicy()->GetMarketplacePolicy())
	{
		FName RowName = FName(*StackName.Replace(TEXT(" "),TEXT("_")));
		auto DatatableRow = Policy->FindNFTTextureRow(RowName);
		
		if (!DatatableRow)
		{
			UE_LOG(LogSampleGame, Error, TEXT("MarketplaceItemWidget - No data row %s was not found"), *RowName.ToString());
			return;
		}
		
		UTexture2D* SourceTexturePtr = DatatableRow->Thumbnail.LoadSynchronous();

		if (SourceTexturePtr)
		{
			SetThumbnail(SourceTexturePtr);
		}	
		SetName(DatatableRow->Name);
	}

	// set nft info
	FString Description = StackBundle.Stack.Description.IsSet() ? StackBundle.Stack.Description.GetValue() : TEXT("");
	
	AddDescriptionRecord(MP_DESCRIPTION_DESCRIPTION, Description);
	AddDescriptionRecord(MP_DESCRIPTION_CREATED_AT, StackBundle.Stack.CreatedAt.ToString());
	AddDescriptionRecord(MP_DESCRIPTION_UPDATED_AT, StackBundle.Stack.UpdatedAt.ToString());

	if (StackBundle.Stack.Attributes.IsSet())
	{
		for (auto Attribute : StackBundle.Stack.Attributes.GetValue())
		{
			TSharedPtr<FJsonValue> Value;

			AddMetadataAttribute(Attribute.TraitType, Attribute.Value);
		}
	}

	const auto StackNumber = StackBundle.Listings.Num();

	for (int32 i = 0; i < StackNumber; ++i)
	{
		Listings->AddItem(StackBundle.Listings[i], i % 2 == 0);
	}

	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void USearchStacksListingWidget::OnSelectionStatusChange(bool IsAnyItemSelected)
{
	if (!BuyButton || IsAnyItemSelected == BuyButton->IsButtonEnabled())
	{
		return;
	}
	
	IsAnyItemSelected ? BuyButton->Enable() : BuyButton->Disable();
}

void USearchStacksListingWidget::OnBuyButtonClicked(FGameplayTag ButtonTag)
{
	UCustomLocalPlayer* LocalPlayer = Cast<UCustomLocalPlayer>(GetOwningLocalPlayer());
	UMarketplacePolicy* Policy = LocalPlayer->GetGameUIPolicy()->GetMarketplacePolicy();

	if (!Policy)
	{
		return;
	}
	
	if(Listings->GetSelectedItemWidget())
	{
		ImmutableTsSdkApi::OpenAPIFulfillOrderRequest RequestData;
		ImmutableTsSdkApi::OpenAPIOrderbookApi::FulfillOrderRequest Request;

		RequestData.ListingId = Listings->GetSelectedItemWidget()->GetListingId();
		RequestData.TakerAddress = LocalPlayer->GetPassportWalletAddress();
		Request.OpenAPIFulfillOrderRequest = RequestData;

		ProcessingDialog = UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::Process, UDialogSubsystem::CreateProcessDescriptor(TEXT("Buying..."), TEXT("Started fulfilling order..."), { EDialogResult::Cancelled, LOCTEXT("Cancel", "Cancel") }));
		ProcessingDialog->DialogResultDelegate.AddUniqueDynamic(this, &USearchStacksListingWidget::OnProcessDialogAction);	
		Policy->GetTsSdkAPI()->FulfillOrder(Request, ImmutableTsSdkApi::OpenAPIOrderbookApi::FFulfillOrderDelegate::CreateUObject(this, &USearchStacksListingWidget::OnFulfillOrder));
	}
}

void USearchStacksListingWidget::OnProcessDialogAction(UDialog* DialogPtr, EDialogResult Result)
{
	if (Result == EDialogResult::Closed || Result == EDialogResult::Cancelled)
	{
		DialogPtr->KillDialog();
	}
}

void USearchStacksListingWidget::OnFulfillOrder(const ImmutableTsSdkApi::OpenAPIOrderbookApi::FulfillOrderResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		UE_LOG(LogSampleGame, Error, TEXT("OnFulfillOrder error: %s"), *Response.GetHttpResponse()->GetContentAsString());
		ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Buying error!"), TEXT("Failed to fulfill your order"), { EDialogResult::Closed, LOCTEXT("Close", "Close") }, false));

		return;
	}

	if (Response.Content.Actions.IsSet())
	{
		auto Actions = Response.Content.Actions.GetValue();

		const auto* ApprovalAction = Actions.FindByPredicate([this](const ImmutableTsSdkApi::OpenAPITransactionAction& Action){ return Action.Purpose.GetValue().Value == ImmutableTsSdkApi::OpenAPITransactionPurpose::Values::Approval; });
		const auto* FulfillOrderAction = Actions.FindByPredicate([this](const ImmutableTsSdkApi::OpenAPITransactionAction& Action){ return Action.Purpose.GetValue().Value == ImmutableTsSdkApi::OpenAPITransactionPurpose::Values::FulfillOrder; });

		if (!FulfillOrderAction)
		{
			ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Buying error!"), TEXT("Failed to find fulfill order purpose in transaction actions"), { EDialogResult::Closed, LOCTEXT("Close", "Close") }, false));
		
			return;
		}

		auto FulfillOrderLambda = [this, Action = *FulfillOrderAction]()
		{
			GetOwningCustomLocalPLayer()->SignSubmitApproval(Action.PopulatedTransactions->To.GetValue(), Action.PopulatedTransactions->Data.GetValue(), [this](FString TransactionHash, FString Status)
			{
				ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Buying success!"), TEXT("Transaction complete successfully! Enjoy your new purchase!"), { EDialogResult::Closed, LOCTEXT("Close", "Close") }, false));
				GetOwningCustomLocalPLayer()->UpdateBalance();
			});
		};
		
		if (ApprovalAction)
		{
			GetOwningCustomLocalPLayer()->SignSubmitApproval(ApprovalAction->PopulatedTransactions->To.GetValue(), ApprovalAction->PopulatedTransactions->Data.GetValue(), [this, FulfillOrderLambda](FString TransactionHash, FString Status)
			{
				ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Buying..."), TEXT("Approval for purchase is processed!"), { EDialogResult::Cancelled, LOCTEXT("Cancel", "Cancel") }));
				FulfillOrderLambda();
			});
		}
		else
		{
			FulfillOrderLambda();
		}
	}
}

