#include "Marketplace/SearchStacksWidget.h"

#include "CustomGameInstance.h"
#include "CustomLocalPlayer.h"
#include "GameUIPolicy.h"
#include "IContentBrowserSingleton.h"
#include "OpenAPISearchApiOperations.h"
#include "UIGameplayTags.h"
#include "UI/Marketplace/MarketplacePolicy.h"
#include "Base/ItemWidget.h"
#include "Dialog/DialogSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"


USearchStacksWidget::USearchStacksWidget()
{
	ControlPanelButtonsData.Add(FUIControlPanelButtons::NextPage, EAWStackControlPanelSide::Right);
	ControlPanelButtonsData.Add(FUIControlPanelButtons::PreviousPage, EAWStackControlPanelSide::Left);
}

void USearchStacksWidget::RefreshItemList(TOptional<FString> PageCursor)
{
	if (!bInitialized)
	{
		return;
	}

	if (!ListPanel)
	{
		return;
	}

	ListPanel->ResetPanelItems();

	UMarketplacePolicy* Policy = GetOwningCustomLocalPLayer()->GetGameUIPolicy()->GetMarketplacePolicy();

	if (!Policy)
	{
		return;
	}

	Policy->SetPageSize(ListPanel->GetNumberOfColumns() * ListPanel->GetNumberOfRows());
	Policy->SetPageCursor(PageCursor);
	Policy->GetOpenAPISearchApi()->SearchStacks(*Policy->GetSearchStacksRequest(), ImmutableOpenAPI::OpenAPISearchApi::FSearchStacksDelegate::CreateUObject(this, &USearchStacksWidget::OnSearchStacksResponse));
}

void USearchStacksWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	RefreshItemList(TOptional<FString>());
}

void USearchStacksWidget::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
}

void USearchStacksWidget::OnSearchStacksResponse(const ImmutableOpenAPI::OpenAPISearchApi::SearchStacksResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::ErrorFull, UDialogSubsystem::CreateErrorDescriptorWithErrorText(TEXT("Error"), TEXT("Failed to acquire search stacks result"), Response.GetResponseString()));
		
		return;
	}

	int32 NumberOfColumns = ListPanel->GetNumberOfColumns();
	// int32 NumberOfRows = ListPanel->GetNumberOfRows();
	int32 NumberOfResults = Response.Content.Result.Num();

	HandlePageData(Response.Content.Page);
	for (int32 ResultId = 0; ResultId < NumberOfResults; ResultId++)
	{
		int32 Row = ResultId / NumberOfColumns;
		int32 Column = ResultId - Row * NumberOfColumns;
		auto ItemWidget = ListPanel->GetItem(Column, Row);

		ItemWidget->ProcessModel(Response.Content.Result[ResultId]);
	}
}

void USearchStacksWidget::SetupControlButtons(TMap<FGameplayTag, UControlPanelButton*>& Buttons)
{
	for (auto Button : Buttons)
	{
		if (Button.Key.MatchesTagExact(FUIControlPanelButtons::PreviousPage))
		{
			PreviousPageButton = Button.Value;
		}
		if (Button.Key.MatchesTagExact(FUIControlPanelButtons::NextPage))
		{
			NextPageButton = Button.Value;
		}
		Button.Value->OnPanelButtonClicked.AddUniqueDynamic(this, &USearchStacksWidget::OnPageDirectionButtonClicked);
	}
	
	Super::SetupControlButtons(Buttons);
}

void USearchStacksWidget::HandlePageData(const ImmutableOpenAPI::OpenAPIPage& PageData)
{
	PageCursors = PageData;

	if (NextPageButton)
	{
		PageCursors.NextCursor.IsSet() ? NextPageButton->Show() : NextPageButton->Hide();	
	}
	if (PreviousPageButton)
	{
		PageCursors.PreviousCursor.IsSet() ? PreviousPageButton->Show() : PreviousPageButton->Hide();
	}
}

void USearchStacksWidget::OnPageDirectionButtonClicked(FGameplayTag ButtonTag)
{
	if (ButtonTag.MatchesTagExact(FUIControlPanelButtons::PreviousPage))
	{
		RefreshItemList(PageCursors.PreviousCursor);
	}
	if (ButtonTag.MatchesTagExact(FUIControlPanelButtons::NextPage))
	{
		RefreshItemList(PageCursors.NextCursor);
	}
}
