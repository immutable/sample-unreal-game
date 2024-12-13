#include "BalanceWidget.h"

#include "CustomBlueprintFunctionLibrary.h"
#include "CustomLocalPlayer.h"
#include "Components/TextBlock.h"

void UBalanceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (auto* OwningCustomLocalPLayer = GetOwningCustomLocalPLayer())
	{
		OwningCustomLocalPLayer->OnIMRBalanceUpdated.AddUniqueDynamic(this, &UBalanceWidget::OnIMRBalanceUpdated);
		OwningCustomLocalPLayer->OnIMXBalanceUpdated.AddUniqueDynamic(this, &UBalanceWidget::OnIMXBalanceUpdated);
	}
}

void UBalanceWidget::ShowAddFundsWidget()
{
	UCustomBlueprintFunctionLibrary::ShowTransakWidget(GetOwningCustomLocalPLayer());
}

void UBalanceWidget::Refresh()
{
	if (auto* OwningCustomLocalPLayer = GetOwningCustomLocalPLayer())
	{
		OwningCustomLocalPLayer->UpdateBalance();
		UpdateBalanceInProgress();
		bIsIMRBalanceUpdateInProgress = true;
		bIsIMXBalanceUpdateInProgress = true;
	}
	CurrentBalanceUpdateTimerDuration = 0.0f;
}

void UBalanceWidget::Tick(float DeltaTime)
{
	CurrentBalanceUpdateTimerDuration += DeltaTime;

	if (CurrentBalanceUpdateTimerDuration > AutoBalanceRefreshRate)
	{
		Refresh();
	}
}

TStatId UBalanceWidget::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UBalanceWidget, STATGROUP_Tickables);
}

void UBalanceWidget::OnIMRBalanceUpdated(float TokenBalance)
{
	if (IMRBalance)
	{
		const FNumberFormattingOptions FormatOptions = FNumberFormattingOptions()
			.SetMinimumFractionalDigits(3)
			.SetMaximumFractionalDigits(3);
	
		IMRBalance->SetText(FText::AsNumber(TokenBalance, &FormatOptions));
	}
	bIsIMRBalanceUpdateInProgress = false;
	CheckBalanceInProgress();
}

void UBalanceWidget::OnIMXBalanceUpdated(const FString& TokenBalance)
{
	if (IMXBalance)
	{
		IMXBalance->SetText(FText::FromString(*TokenBalance));
	}
	bIsIMXBalanceUpdateInProgress = false;
	CheckBalanceInProgress();
}

void UBalanceWidget::CheckBalanceInProgress()
{
	if (bIsIMRBalanceUpdateInProgress || bIsIMRBalanceUpdateInProgress)
	{
		return;
	}

	UpdateBalanceFinished();
}

void UBalanceWidget::StartTimer()
{
	
}
