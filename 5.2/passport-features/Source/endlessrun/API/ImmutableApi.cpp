#include "ImmutableApi.h"

#include <string>

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Immutable/Misc/ImtblLogging.h"


bool UImmutableApi::MintTokens(int Quantity, const FString& WalletAddress, const FImtblApiResponseDelegate& ResponseDelegate)
{
	IMTBL_LOG("Minting %d tokens...", Quantity)
	
	if (WalletAddress.IsEmpty()) {
		IMTBL_ERR("Wallet address is empty.")
		return false;
	}

	ResponseDelegates.Remove("MintTokens");
	ResponseDelegates.Add("MintTokens", ResponseDelegate);
	// Create an http request
	// The request will execute asynchronously, and call us back on the Lambda below
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> pRequest = HttpModule.CreateRequest();

	// This is where we set the HTTP method (GET, POST, etc)
	pRequest->SetVerb(TEXT("POST"));

	// We'll need to tell the server what type of content to expect in the POST data
	pRequest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));

	FString RequestContent = TEXT("toUserWallet=") + WalletAddress + TEXT("&number=") + FString::FromInt(Quantity);
	// Set the POST content
	pRequest->SetContentAsString(RequestContent);
	
	// Set the http URL
	pRequest->SetURL(MintServerBaseUrl + FString("/mint/token"));

	// Set the callback, which will execute when the HTTP call is complete
	pRequest->OnProcessRequestComplete().BindLambda(
		// Here, we "capture" the 'this' pointer (the "&"), so our lambda can call this
		// class's methods in the callback.
		[ResponseDelegate](
			FHttpRequestPtr pRequest,
			FHttpResponsePtr pResponse,
			bool connectedSuccessfully)  {

			ResponseDelegate.ExecuteIfBound(FImtblAPIResponse{connectedSuccessfully, pRequest, pResponse});
			
			//SendResponse("MintTokens", pRequest, pResponse, connectedSuccessfully);
			if (connectedSuccessfully) {
				// We should have a JSON response - attempt to process it.
				IMTBL_LOG("Mint Token Response: %s", *pResponse->GetContentAsString());
			}
			else {
				switch (pRequest->GetStatus()) {
				case EHttpRequestStatus::Failed_ConnectionError:
					IMTBL_ERR("Connection failed.")
				default:
					IMTBL_ERR("Request failed.")
				}
			}
		}
	);

	// Finally, submit the request for processing
	return pRequest->ProcessRequest();
}


bool UImmutableApi::MintSkin(const FString& WalletAddress, const FImtblApiResponseDelegate& ResponseDelegate)
{
	IMTBL_LOG("Minting skin...")
	
	if (WalletAddress.IsEmpty()) {
		IMTBL_ERR("Wallet address is empty.")
		return false;
	}

	ResponseDelegates.Remove("MintSkin");
	ResponseDelegates.Add("MintSkin", ResponseDelegate);
	// Create an http request
	// The request will execute asynchronously, and call us back on the Lambda below
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> pRequest = HttpModule.CreateRequest();

	// This is where we set the HTTP method (GET, POST, etc)
	pRequest->SetVerb(TEXT("POST"));

	// We'll need to tell the server what type of content to expect in the POST data
	pRequest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));

	FString RequestContent = TEXT("toUserWallet=") + WalletAddress;
	// Set the POST content
	pRequest->SetContentAsString(RequestContent);
	
	// Set the http URL
	pRequest->SetURL(MintServerBaseUrl + FString("/mint/skin"));

	// Set the callback, which will execute when the HTTP call is complete
	pRequest->OnProcessRequestComplete().BindLambda(
		// Here, we "capture" the 'this' pointer (the "&"), so our lambda can call this
		// class's methods in the callback.
		[&](
			FHttpRequestPtr pRequest,
			FHttpResponsePtr pResponse,
			bool connectedSuccessfully)  {

			SendResponse("MintSkin", pRequest, pResponse, connectedSuccessfully);
			if (connectedSuccessfully) {

				// We should have a JSON response - attempt to process it.
				IMTBL_LOG("Mint Skin Response: %s", *pResponse->GetContentAsString());
			}
			else {
				switch (pRequest->GetStatus()) {
				case EHttpRequestStatus::Failed_ConnectionError:
					IMTBL_ERR("Connection failed.")
				default:
					IMTBL_ERR("Request failed.")
				}
			}
		}
	);

	// Finally, submit the request for processing
	return pRequest->ProcessRequest();
}

bool UImmutableApi::GetTokens(int Quantity, const FString& TokenAddress, const FString& WalletAddress, const FImtblApiResponseDelegate& ResponseDelegate)
{
	IMTBL_LOG("Get Tokens...")
	
	if (WalletAddress.IsEmpty()) {
		IMTBL_ERR("Wallet address is empty.")
		return false;
	}

	if (TokenAddress.IsEmpty()) {
		IMTBL_ERR("Token address is empty.")
		return false;
	}

	ResponseDelegates.Remove("GetTokens");
	ResponseDelegates.Add("GetTokens", ResponseDelegate);
	
	// Create an http request
	// The request will execute asynchronously, and call us back on the Lambda below
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> pRequest = HttpModule.CreateRequest();

	// This is where we set the HTTP method (GET, POST, etc)
	pRequest->SetVerb(TEXT("GET"));

	// We'll need to tell the server what type of content to expect in the POST data
	pRequest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));

	FString uriQuery = TEXT("collection=") + TokenAddress + TEXT("&page_size=") + FString::FromInt(Quantity) + TEXT("&user=") + WalletAddress;
	
	// Set the http URL
	pRequest->SetURL(ImxApiBaseUrl + FString("/v1/assets?" + uriQuery));

	// Set the callback, which will execute when the HTTP call is complete
	pRequest->OnProcessRequestComplete().BindLambda(
		// Here, we "capture" the 'this' pointer (the "&"), so our lambda can call this
		// class's methods in the callback.
		[ResponseDelegate](
			FHttpRequestPtr pRequest,
			FHttpResponsePtr pResponse,
			bool connectedSuccessfully)  {

			ResponseDelegate.ExecuteIfBound(FImtblAPIResponse{connectedSuccessfully, pRequest, pResponse});
			//SendResponse("GetTokens", pRequest, pResponse, connectedSuccessfully);
			if (connectedSuccessfully) {
				// We should have a JSON response - attempt to process it.
				IMTBL_LOG("Get Tokens Response0: %s", *pResponse->GetContentAsString());
			}
			else {
				switch (pRequest->GetStatus()) {
				case EHttpRequestStatus::Failed_ConnectionError:
					IMTBL_ERR("Connection failed.")
				default:
					IMTBL_ERR("Request failed.")
				}
			}
		}
	);

	// Finally, submit the request for processing
	return pRequest->ProcessRequest();
}

void UImmutableApi::SendResponse(FString RequestName, FHttpRequestPtr pRequest,
			FHttpResponsePtr pResponse,
			bool connectedSuccessfully)
{
	FImtblApiResponseDelegate ResponseDelegate;
	if (ResponseDelegates.RemoveAndCopyValue(RequestName, ResponseDelegate))
	{
		ResponseDelegate.ExecuteIfBound(FImtblAPIResponse{connectedSuccessfully, pRequest, pResponse});
	}
}

bool UImmutableApi::GetSkin(const FString& TokenAddress, const FString& WalletAddress, const FImtblApiResponseDelegate& ResponseDelegate)
{
	IMTBL_LOG("Get Skin...")
	
	if (WalletAddress.IsEmpty()) {
		IMTBL_ERR("Wallet address is empty.")
		return false;
	}

	if (TokenAddress.IsEmpty()) {
		IMTBL_ERR("Token address is empty.")
		return false;
	}

	ResponseDelegates.Remove("GetSkin");
	ResponseDelegates.Add("GetSkin", ResponseDelegate);
	
	// Create an http request
	// The request will execute asynchronously, and call us back on the Lambda below
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> pRequest = HttpModule.CreateRequest();

	// This is where we set the HTTP method (GET, POST, etc)
	pRequest->SetVerb(TEXT("GET"));

	// We'll need to tell the server what type of content to expect in the POST data
	pRequest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));

	FString uriQuery = TEXT("collection=") + TokenAddress + TEXT("&user=") + WalletAddress;
	
	// Set the http URL
	pRequest->SetURL(ImxApiBaseUrl + FString("/v1/assets?" + uriQuery));

	// Set the callback, which will execute when the HTTP call is complete
	pRequest->OnProcessRequestComplete().BindLambda(
		// Here, we "capture" the 'this' pointer (the "&"), so our lambda can call this
		// class's methods in the callback.
		[&](
			FHttpRequestPtr pRequest,
			FHttpResponsePtr pResponse,
			bool connectedSuccessfully)  {

			SendResponse("GetSkin", pRequest, pResponse, connectedSuccessfully);
			if (connectedSuccessfully) {

				// We should have a JSON response - attempt to process it.
				IMTBL_LOG("Get Skin Response0: %s", *pResponse->GetContentAsString());
			}
			else {
				switch (pRequest->GetStatus()) {
				case EHttpRequestStatus::Failed_ConnectionError:
					IMTBL_ERR("Connection failed.")
				default:
					IMTBL_ERR("Request failed.")
				}
			}
		}
	);

	// Finally, submit the request for processing
	return pRequest->ProcessRequest();
}