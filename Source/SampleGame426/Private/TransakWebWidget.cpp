#include "TransakWebWidget.h"

#include "PlatformHttp.h"
#include "Immutable/ImmutableUtilities.h"


void UTransakWebWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (WebBrowserWidget)
    {
        WebBrowserWidget->OnConsoleMessage.AddUniqueDynamic(this, &UTransakWebWidget::OnConsoleMessage);
        WebBrowserWidget->OnUrlChanged.AddUniqueDynamic(this, &UTransakWebWidget::OnUrlChanged);
        // WebBrowserWidget->LoadURL(TEXT("about:blank"));
    }
}

void UTransakWebWidget::Load(const FString& WalletAddress, const FString& Email, const FString& ProductsAvailed, const FString& ScreenTitle)
{
    UrlToLoad = ComputePath(WalletAddress, Email, ProductsAvailed, ScreenTitle);

    if (WebBrowserWidget == nullptr)
    {
        UrlToLoad.Empty();
    }
}

FString UTransakWebWidget::ComputePath(const FString& WalletAddress, const FString& Email, const FString& ProductsAvailed, const FString& ScreenTitle)
{
    UTransakConfig* TransakConfig = FImmutableUtilities::GetDefaultTransakConfig();

    if (!TransakConfig)
    {
        return "";
    }

    FString Path = TransakConfig->GetURL();
    TArray<FString> QueryParams;
    
    QueryParams.Add(FString(TEXT("apiKey=")) + FPlatformHttp::UrlEncode(TransakConfig->GetAPIKey()));
    QueryParams.Add(FString(TEXT("email=")) + FPlatformHttp::UrlEncode(Email));
    QueryParams.Add(FString(TEXT("walletAddress=")) + FPlatformHttp::UrlEncode(WalletAddress));
    QueryParams.Add(FString(TEXT("themeColor=")) + FPlatformHttp::UrlEncode(TransakConfig->GetThemeColor().ToString()));
    QueryParams.Add(FString(TEXT("isAutoFillUserData=")) + FPlatformHttp::UrlEncode(TransakConfig->IsAutoFillUserData() ? TEXT("true") : TEXT("false")));
    QueryParams.Add(FString(TEXT("disableWalletAddressForm=")) + FPlatformHttp::UrlEncode(TransakConfig->DisableWalletAddressForm() ? TEXT("true") : TEXT("false")));

    if (!TransakConfig->GetNetwork().IsEmpty())
    {
        QueryParams.Add(FString(TEXT("network=")) + FPlatformHttp::UrlEncode(TransakConfig->GetNetwork()));
    }
    
    if (!ProductsAvailed.IsEmpty())
    {
        QueryParams.Add(FString(TEXT("productsAvailed=")) + FPlatformHttp::UrlEncode(ProductsAvailed));    
    }
    
    if (!ScreenTitle.IsEmpty())
    {
        QueryParams.Add(FString(TEXT("exchangeScreenTitle=")) + FPlatformHttp::UrlEncode(ScreenTitle));    
    }
    
    if (!TransakConfig->GetDefaultCryptoCurrency().IsEmpty())
    {
        QueryParams.Add(FString(TEXT("defaultCryptoCurrency=")) + FPlatformHttp::UrlEncode(TransakConfig->GetDefaultCryptoCurrency()));
    }

    if (!TransakConfig->GetDefaultFiatAmount().IsEmpty())
    {
        QueryParams.Add(FString(TEXT("defaultFiatAmount=")) + FPlatformHttp::UrlEncode(TransakConfig->GetDefaultFiatAmount()));
    }
    
    if (!TransakConfig->GetDefaultFiatCurrency().IsEmpty())
    {
        QueryParams.Add(FString(TEXT("defaultFiatCurrency=")) + FPlatformHttp::UrlEncode(TransakConfig->GetDefaultFiatCurrency()));
    }

    if (!TransakConfig->GetDefaultPaymentMethod().IsEmpty())
    {
        QueryParams.Add(FString(TEXT("defaultPaymentMethod=")) + FPlatformHttp::UrlEncode(TransakConfig->GetDefaultPaymentMethod()));
    }

    if (TransakConfig->GetCryptoCurrencyList().Num() > 0)
    {
        QueryParams.Add(FString(TEXT("cryptoCurrencyList=")) + FPlatformHttp::UrlEncode(FString::Join(TransakConfig->GetCryptoCurrencyList(), TEXT(","))));
    }
    
    if (TransakConfig->GetDisablePaymentMethods().Num() > 0)
    {
        QueryParams.Add(FString(TEXT("disablePaymentMethods=")) + FPlatformHttp::UrlEncode(FString::Join(TransakConfig->GetDisablePaymentMethods(), TEXT(","))));
    }
    
    Path += TEXT("?");
    Path += FString::Join(QueryParams, TEXT("&"));

    return Path;
}

void UTransakWebWidget::OnConsoleMessage(const FString& Message, const FString& Source, int32 Line)
{
    UE_LOG(LogTemp, Display, TEXT("%s"), *Message);
}

void UTransakWebWidget::OnUrlChanged(const FText& Text)
{
    LoadURL();
}

void UTransakWebWidget::LoadURL()
{
    if (!UrlToLoad.IsEmpty())
    {
        WebBrowserWidget->LoadURL(UrlToLoad);
        UrlToLoad.Empty();
    }
}
