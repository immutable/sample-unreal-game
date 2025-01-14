#pragma once

#include "CustomUserWidget.h"

#include "BalanceWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class SAMPLEGAME426_API UBalanceWidget : public UCustomUserWidget, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void ShowAddFundsWidget();

	UFUNCTION(BlueprintCallable)
	void Refresh();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBalanceInProgress();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBalanceFinished();

	//~ Begin FTickableGameObject Interface
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	//~ End FTickableGameObject Interface

protected:
	UFUNCTION()
	void OnIMRBalanceUpdated(float TokenBalance);
	UFUNCTION()
	void OnIMXBalanceUpdated(const FString& TokenBalance);
	UFUNCTION()
	void OnUSDCBalanceUpdated(float TokenBalance);

private:
	void CheckBalanceInProgress();

protected:
	UPROPERTY(EditDefaultsOnly)
	float AutoBalanceRefreshRate = 30.0f;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* IMRBalance = nullptr;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* IMXBalance = nullptr;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* USDCBalance = nullptr;

private:
	FTimerHandle AutoRefreshBalanceTimerHandle;
	bool bIsIMRBalanceUpdateInProgress = false;
	bool bIsIMXBalanceUpdateInProgress = false;
	bool bIsUSDCBalanceUpdateInProgress = false;

	float CurrentBalanceUpdateTimerDuration = 0.f;
};
