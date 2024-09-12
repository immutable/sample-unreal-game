#include "Marketplace.h"

#include "HttpModule.h"
#include "LogSampleGame.h"
#include "Interfaces/IHttpResponse.h"


#define CHANI_NAME			TEXT("imtbl-zkevm-devnet")
#define SEARCH_BASE_URL		TEXT("https://api.dev.immutable.com/experimental/chains/{0}/search/stacks")

const FString FMarketplaceRequestQueryParameters::ContactAddress = TEXT("contract_address");
const FString FMarketplaceRequestQueryParameters::AccountAddress = TEXT("account_address");
const FString FMarketplaceRequestQueryParameters::Keyword = TEXT("keyword");
const FString FMarketplaceRequestQueryParameters::PageCursor = TEXT("page_cursor");
const FString FMarketplaceRequestQueryParameters::PageSize = TEXT("page_size");
const FString FMarketplaceRequestQueryParameters::Trait = TEXT("trait");
const FString FMarketplaceRequestQueryParameters::OnlyIncludeOwnerListings = TEXT("only_include_owner_listings");


void FMarketplace::QueryStacks(const FMarketplaceRequestData& RequestData, FOnHttpRequestComplete OnHttpRequestComplete)
{
	const FString URL = GetMarketplaceUrl();
	//FString URL = TEXT("https://api.dev.immutable.com/experimental/chains/imtbl-zkevm-devnet/search/stacks?contract_address=0xcdbee7935e1b0eaabdee64219182602df0d8d094&account_address=0x8c864b96826f3b897cc125a23bc93ab3ebb173ab&page_size=10&cursor=eyJ0eXBlIjoibmV4dCIsIml0ZW0iOnsic3RhY2tfaWQiOiIwMTkxZDlkNi1iMDQ5LTc1NmMtNzE3Ny0xZTgzYjdmMzNiNTYiLCJjcmVhdGVkX2F0IjoiMjAyNC0wOS0xMFQwMjo1MDoxMS40MDA3OFoifX0");
	
	UE_LOG(LogSampleGame, Log, TEXT("GET Marketplace stacks from URL: %s"), *URL)

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(TEXT("GET"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	HttpRequest->SetHeader(TEXT("Accept"), TEXT("application/json"));
	HttpRequest->SetContentAsString(BuildGETContentString(RequestData));
	HttpRequest->OnProcessRequestComplete().BindStatic(&FMarketplace::OnQueryStacksComplete, OnHttpRequestComplete);
	HttpRequest->ProcessRequest();
}

FString FMarketplace::BuildGETContentString(const FMarketplaceRequestData& RequestData)
{
	FString Content;

	for (auto Address : RequestData.ContactAddress)
	{
		Content += TEXT("&") + FMarketplaceRequestQueryParameters::ContactAddress + TEXT("=") + Address;	
	}

	if (!RequestData.AccountAddress.IsEmpty())
	{
		Content += TEXT("&") + FMarketplaceRequestQueryParameters::AccountAddress + TEXT("=") + RequestData.AccountAddress;	
	}

	if (!RequestData.Keyword.IsEmpty())
	{
		Content += TEXT("&") + FMarketplaceRequestQueryParameters::Keyword + TEXT("=") + RequestData.Keyword;	
	}

	if (!RequestData.PageCursor.IsEmpty())
	{
		Content += TEXT("&") + FMarketplaceRequestQueryParameters::PageCursor + TEXT("=") + RequestData.PageCursor;
	}

	if (RequestData.PageSize > 0)
	{
		Content += TEXT("&") + FMarketplaceRequestQueryParameters::PageSize + TEXT("=") + FString::FromInt(RequestData.PageSize);
	}

	Content += TEXT("&") + FMarketplaceRequestQueryParameters::OnlyIncludeOwnerListings + TEXT("=") + (RequestData.OnlyIncludeOwnerListings ? TEXT("true") : TEXT("false"));
	
	Content.RemoveAt(0);
	
	return Content;
}

FString FMarketplace::GetMarketplaceUrl()
{
	const FString MARKETPLACE_URL = FString::Format(SEARCH_BASE_URL, { CHANI_NAME });

	return MARKETPLACE_URL;
}

void FMarketplace::OnQueryStacksComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool IsSuccessful,
                                         FOnHttpRequestComplete OnHttpRequestComplete)
{
	if (IsSuccessful)
	{
		FString Content = Response->GetContentAsString();
		TSharedPtr<FJsonObject> RootJsonObject;
		UE_LOG(LogSampleGame, Log, TEXT("%s"), *Content);
		// Parse the JSON
		const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Content);
		if (FJsonSerializer::Deserialize(JsonReader, RootJsonObject))
		{
			
		}

		OnHttpRequestComplete.Execute(true);
	}
}
