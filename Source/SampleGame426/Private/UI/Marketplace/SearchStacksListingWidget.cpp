#include "Marketplace/SearchStacksListingWidget.h"

#include "CustomGameInstance.h"
#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "LogSampleGame.h"
#include "APIListing.h"
#include "APIStackBundle.h"
#include "UIGameplayTags.h"
#include "Marketplace/MarketplacePolicy.h"
#include "Marketplace/SearchStacksListing_ListingsWidget.h"
#include "APIFulfillOrderRequest.h"
#include "APIOrderbookApiOperations.h"
#include "Base/AWStackWithControlPanels.h"
#include "Marketplace/SearchStacksWidget.h"
#include "Marketplace/SearchStacksItemWidget.h"

#define MP_DESCRIPTION_DESCRIPTION TEXT("Description")
#define MP_DESCRIPTION_CREATED_AT TEXT("Created at")
#define MP_DESCRIPTION_UPDATED_AT TEXT("Updated at")

#define LOCTEXT_NAMESPACE "ImmutableUI"


void USearchStacksListingWidget::SetupControlButtons(class UAWStackWithControlPanels* HostLayer)
{
	Super::SetupControlButtons(HostLayer);

	BuyButton = HostLayer->AddButton(NativeUIGameplayTags.UI_ControlPanel_Button_Buy);

	if (BuyButton)
	{
		BuyButton->RegisterOnClick(UControlPanelButton::FOnControlPanelButtonClick::CreateUObject(this, &USearchStacksListingWidget::OnControlButtonClicked));
		ControlPanelButtons.Add(NativeUIGameplayTags.UI_ControlPanel_Button_Buy, BuyButton);
	}
}

void USearchStacksListingWidget::ProcessModel(const ImmutablezkEVMAPI::Model& Data)
{
	if (!Listings)
	{
		return;
	}

	Listings->Reset();
	BP_Reset();
	
	auto StackBundle = static_cast<const ImmutablezkEVMAPI::APIStackBundle&>(Data);

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
		Listings->AddItem(StackBundle.Listings[i], i % 2 == 0, UItemWidget::FOnSelectionChange::CreateUObject(this, &USearchStacksListingWidget::OnItemSelectionStatusChange));
	}
}

void USearchStacksListingWidget::Refresh()
{
	auto Group = GetOwningGroup();
	
	if (!Group)
	{
		return;
	}

	USearchStacksWidget* ResultsWidget = Cast<USearchStacksWidget>(Group->WidgetsInGroup[GetIndexInGroup() - 1]);

	if (!ResultsWidget)
	{
		return;
	}

	USearchStacksItemWidget* ItemWidget = Cast<USearchStacksItemWidget>(ResultsWidget->GetSelectedItem());
	
	if (ItemWidget && ItemWidget->GetStackBundle().IsValid())
	{
		ProcessModel(*ItemWidget->GetStackBundle().Get());
	}
}

void USearchStacksListingWidget::OnItemSelectionStatusChange(bool IsItemSelected, UItemWidget* ItemWidget)
{
	if (BuyButton)
	{
		BuyButton->SetEnable(IsItemSelected);
	}

	if (IsItemSelected)
	{
		SelectedItem = ItemWidget;
	}
	else
	{
		SelectedItem = nullptr;
	}
}

void USearchStacksListingWidget::OnBuyButtonClicked(UDialog* DialogPtr, EDialogResult Result)
{
	if (!DialogPtr || Result != EDialogResult::Confirmed)
	{
		return;
	}

	DialogPtr->KillDialog();
	
	UCustomLocalPlayer* LocalPlayer = Cast<UCustomLocalPlayer>(GetOwningLocalPlayer());
	UMarketplacePolicy* Policy = LocalPlayer->GetGameUIPolicy()->GetMarketplacePolicy();

	if (!Policy)
	{
		return;
	}

	auto ListingItemWidget = Cast<USearchStacksListing_ListingItemWidget>(SelectedItem);
	
	if(ListingItemWidget)
	{
		ProcessingDialog = UCustomGameInstance::SendDialogMessage(this, NativeUIGameplayTags.UI_Dialog_Process, UDialogSubsystem::CreateProcessDescriptor(TEXT("Buying..."), TEXT("Started fulfilling order..."), {EDialogResult::Cancelled, LOCTEXT("Cancel", "Cancel")}));
		ProcessingDialog->DialogResultDelegate.AddUniqueDynamic(this, &USearchStacksListingWidget::OnProcessDialogAction);	

		/**
		 * Step 1(Buying): Initiates the fulfillment of an order using the the Orderbook API.
		 * This function creates a request to fulfill an order by setting the necessary
		 * request data, including the listing ID and the taker address. It then sends
		 * the request using the FulfillOrder method of the Orderbook API.
		 * @see ImmutableOrderbook::APIOrderbookApi::FulfillOrderRequest
		 *
		 * @param RequestData The data required to fulfill the order, including the listing ID and taker address.
		 * @param Request The request object that will be sent to the Orderbook API.
		 */
		ImmutableOrderbook::APIFulfillOrderRequest RequestData;
		ImmutableOrderbook::APIOrderbookApi::FulfillOrderRequest Request;

		RequestData.ListingId = ListingItemWidget->GetListingId();
		RequestData.TakerAddress = LocalPlayer->GetPassportWalletAddress();

		Request.APIFulfillOrderRequest = RequestData;
		
		Policy->GetTsSdkAPI()->FulfillOrder(Request, ImmutableOrderbook::APIOrderbookApi::FFulfillOrderDelegate::CreateUObject(this, &USearchStacksListingWidget::OnFulfillOrder));
	}
}

void USearchStacksListingWidget::OnProcessDialogAction(UDialog* DialogPtr, EDialogResult Result)
{
	if (Result == EDialogResult::Closed || Result == EDialogResult::Cancelled)
	{
		DialogPtr->KillDialog();
	}
}

void USearchStacksListingWidget::OnControlButtonClicked(FGameplayTag ButtonTag)
{
	if (ButtonTag.MatchesTagExact(NativeUIGameplayTags.UI_ControlPanel_Button_Buy))
	{
		UDialog* BuyDialog = UCustomGameInstance::SendDialogMessage(this, NativeUIGameplayTags.UI_Dialog_Confirmation, UDialogSubsystem::CreateConfirmMessageDescriptor(TEXT(""), TEXT("Please confirm that you are ready to purchase this NFT")));

		if (BuyDialog)
		{
			BuyDialog->DialogResultDelegate.AddUniqueDynamic(this, &USearchStacksListingWidget::OnBuyButtonClicked);	
		}
	}
}

void USearchStacksListingWidget::OnFulfillOrder(const ImmutableOrderbook::APIOrderbookApi::FulfillOrderResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		UE_LOG(LogSampleGame, Error, TEXT("OnFulfillOrder error: %s"), *Response.GetHttpResponse()->GetContentAsString());
		ProcessingDialog->UpdateDialogDescriptor(UDialogSubsystem::CreateProcessDescriptor(TEXT("Buying error!"), TEXT("Failed to fulfill your order"), { EDialogResult::Closed, LOCTEXT("Close", "Close") }, false));

		return;
	}

	if (Response.Content.Actions.IsSet())
	{
		/**
		* Step 2(Buying): Processes the response from the FulfillOrder Orderbook API call and handles the required actions.
		* 
		* This function searches for specific actions (Approval and FulfillOrder) in the response content.
		* If the player has never conducted the FulfillOrder operation before, the Approval action must be present in the response.
		* Subsequently, only the FulfillOrder action is required to complete the purchase.
		* 
		* If the Approval action is present, the function signs and submits the transaction to the blockchain via Immutable SDK ZkEvmSendTransactionWithConfirmation.
		* @see https://docs.immutable.com/sdks/zkEVM/unreal#zkevm-send-transaction. It is implemented in UCustomLocalPlayer::SignSubmitApproval.
		* If the FulfillOrder action is present, the function signs and submits the transaction using Immutable SDK ZkEvmSendTransactionWithConfirmation and completes the purchase.
		*/
		auto Actions = Response.Content.Actions.GetValue();

		const auto* ApprovalAction = Actions.FindByPredicate([this](const ImmutableOrderbook::APITransactionAction& Action){ return Action.Purpose.GetValue().Value == ImmutableOrderbook::APITransactionPurpose::Values::Approval; });
		const auto* FulfillOrderAction = Actions.FindByPredicate([this](const ImmutableOrderbook::APITransactionAction& Action){ return Action.Purpose.GetValue().Value == ImmutableOrderbook::APITransactionPurpose::Values::FulfillOrder; });

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

				if (USearchStacksListing_ListingItemWidget* ListingItemWidget = Cast<USearchStacksListing_ListingItemWidget>(SelectedItem))
				{
					ListingItemWidget->SetIsOwned(true);
				}
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

