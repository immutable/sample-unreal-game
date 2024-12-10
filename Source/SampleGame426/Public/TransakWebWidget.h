#pragma once

#include "WebBrowser.h"
#include "Blueprint/UserWidget.h"

#include "TransakWebWidget.generated.h"


/**
 * 
 */
UCLASS(Abstract)
class SAMPLEGAME426_API UTransakWebWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintCallable)
	void Load(const FString& WalletAddress, const FString& Email, const FString& ProductsAvailed, const FString& ScreenTitle);
	
private:
	FString ComputePath(const FString& WalletAddress, const FString& Email, const FString& ProductsAvailed, const FString& ScreenTitle);
	UFUNCTION()
	void OnConsoleMessage(const FString& Message, const FString& Source, int32 Line);
	UFUNCTION()
	void OnUrlChanged(const FText& Text);
	void LoadURL();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Web", meta=(BindWidget))
	UWebBrowser* WebBrowserWidget = nullptr;

private:
	FString UrlToLoad;
};
