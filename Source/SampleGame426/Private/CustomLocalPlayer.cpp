﻿#include "CustomLocalPlayer.h"

#include "CustomGameInstance.h"
#include "GameUIManagerSubsystem.h"
#include "OpenAPIOrderbookApiOperations.h"
#include "UIGameplayTags.h"
#include "Dialog/DialogSubsystem.h"
#include "Immutable/ImmutableSubsystem.h"
#include "Settings/SampleGameSettings.h"


UCustomLocalPlayer::UCustomLocalPlayer()
	: Super(FObjectInitializer::Get())
{
}

FDelegateHandle UCustomLocalPlayer::CallAndRegister_OnPlayerControllerSet(FPlayerControllerSetDelegate::FDelegate Delegate)
{
	APlayerController* PC = GetPlayerController(GetWorld());

	if (PC)
	{
		Delegate.ExecuteIfBound(this, PC);
	}

	return OnPlayerControllerSet.Add(Delegate);
}

FDelegateHandle UCustomLocalPlayer::CallAndRegister_OnPassportInitialized(FPlayerPassportInitializedDelegates::FDelegate Delegate)
{
	if (IsPassportInitialized)
	{
		Delegate.ExecuteIfBound(IsPassportInitialized);	
	}

	return OnPlayerPassportInitialized.Add(Delegate);
}

FDelegateHandle UCustomLocalPlayer::CallAndRegister_OnPlayerLoggedIn(FPlayerLoggedInDelegate::FDelegate Delegate)
{
	return OnPlayerLoggedIn.Add(Delegate);
}

FDelegateHandle UCustomLocalPlayer::CallAndRegister_OnPlayerPassportDataObtained(FPlayerPassportDataObtained::FDelegate Delegate)
{
	if (CheckAllPassportDataObtained())
	{
		Delegate.ExecuteIfBound();
	}

	return OnPlayerPassportDataObtained.Add(Delegate);
}

void UCustomLocalPlayer::PlayerAdded(class UGameViewportClient* InViewportClient, int32 InControllerID)
{
	Super::PlayerAdded(InViewportClient, InControllerID);

	InitializePassport();
}

void UCustomLocalPlayer::LoginPassport()
{
	 if (Passport.IsValid())
	 {
	 	Passport->HasStoredCredentials(UImmutablePassport::FImtblPassportResponseDelegate::CreateLambda([this](FImmutablePassportResult Result)
	 	{
	 		Passport->Connect(true, Result.Success, UImmutablePassport::FImtblPassportResponseDelegate::CreateUObject(this, &UCustomLocalPlayer::OnPassportLoggedIn));	
	 	}));
	 }
}

bool UCustomLocalPlayer::IsPassportLoggedIn()
{
	return IsLocalPlayerLoggedIn;
}

FString UCustomLocalPlayer::GetPassportWalletAddress()
{
	return PassportWalletAddress;
}

float UCustomLocalPlayer::GetBalance()
{
	return PassportWalletBalance;
}

void UCustomLocalPlayer::UpdateBalance()
{
	if (!IsLocalPlayerLoggedIn)
	{
		return;
	}

	UMarketplacePolicy* MarketplacePolicy = GetGameUIPolicy()->GetMarketplacePolicy();

	if (!MarketplacePolicy)
	{
		return;
	}

	ImmutableTsSdkApi::OpenAPIOrderbookApi::TokenBalanceRequest Request;

	Request.WalletAddress = PassportWalletAddress;
	Request.ContractAddress = MarketplacePolicy->GetBalanceContractAddress();

	MarketplacePolicy->GetTsSdkAPI()->TokenBalance(Request, ImmutableTsSdkApi::OpenAPIOrderbookApi::FTokenBalanceDelegate::CreateUObject(this, &UCustomLocalPlayer::OnBalanceUpdateResponse));
}

void UCustomLocalPlayer::SignSubmitApproval(const FString& To, const FString& Data, TFunction<void(FString TransactionHash, FString Status)> Callback)
{
	FImtblTransactionRequest Request;

	Request.to = To;
	Request.data = Data;
	Request.value = "0";
	
	Passport->ZkEvmSendTransactionWithConfirmation(Request, UImmutablePassport::FImtblPassportResponseDelegate::CreateWeakLambda(this, [this, Callback](FImmutablePassportResult Result)
	{
		if (!Result.Success)
		{
			UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::ErrorFull, UDialogSubsystem::CreateErrorDescriptorWithErrorText(TEXT("Error"), TEXT("Failed to sign and submit transaction"), Result.Error));
			return;
		}

		auto Receipt = JsonObjectToUStruct<FZkEvmTransactionReceipt>(Result.Response.JsonObject);
		FString TransactionHash, Status;

		if (Receipt.IsSet())
		{
			TransactionHash = Receipt.GetValue().transactionHash;
			Status = Receipt.GetValue().status;
		}
		
		Callback(TransactionHash, Status);
	}));
}

void UCustomLocalPlayer::SignData(const FString& SingableMessageJson, TFunction<void(const FString& Signature)> Callback)
{
	if (SingableMessageJson.IsEmpty())
	{
		UCustomGameInstance::SendDisplayMessage(this, TEXT("CreateListing: Input json string is empty!"));
		return;
	}
	
	// FZkEvmSignTypedDataV4Request Request;
	//
	// if (!FJsonObjectConverter::JsonObjectStringToUStruct(SingableMessageJson, &Request, 0, 0))
	// {
	// 	UCustomGameInstance::SendRunningLineMessage(this, TEXT("CreateListing: Failed to convert json string to sign type data structure!"));
	// 	return;
	// }
	
	Passport->ZkEvmSignTypedDataV4(SingableMessageJson, UImmutablePassport::FImtblPassportResponseDelegate::CreateWeakLambda(this, [this, Callback](FImmutablePassportResult Result)
	{
		if (!Result.Success)
		{
			UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::ErrorFull, UDialogSubsystem::CreateErrorDescriptorWithErrorText(TEXT("Error"), TEXT("Failed to sign type data"), Result.Error));
			return;
		}
		Callback(UImmutablePassport::GetResponseResultAsString(Result.Response));
	}));
}

void UCustomLocalPlayer::OnBalanceUpdateResponse(const ImmutableTsSdkApi::OpenAPIOrderbookApi::TokenBalanceResponse& Response)
{
	if (!Response.IsSuccessful())
	{
		UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::ErrorFull, UDialogSubsystem::CreateErrorDescriptorWithErrorText(TEXT("Error"), TEXT("Failed to update balance"), Response.GetResponseString()));
		
		return;
	}

	PassportWalletBalance = FCString::Atof(*Response.Content.Quantity);
	OnBalanceUpdated.Broadcast(PassportWalletBalance);
}

UPrimaryGameLayout* UCustomLocalPlayer::GetRootUILayout() const
{
	if (UGameUIPolicy* Policy = GetGameUIPolicy())
	{
		return Policy->GetRootLayout();
	}

	return nullptr;
}

UGameUIPolicy* UCustomLocalPlayer::GetGameUIPolicy() const
{
	if (UGameUIManagerSubsystem* UIManager = GetGameInstance()->GetSubsystem<UGameUIManagerSubsystem>())
	{
		return UIManager->GetCurrentUIPolicy();
	}

	return nullptr;
}

void UCustomLocalPlayer::InitializePassport()
{
	auto ImmutableSubsystem = GetGameInstance()->GetSubsystem<UImmutableSubsystem>();

	if (ImmutableSubsystem)
	{
		ImmutableSubsystem->WhenReady(this, &UCustomLocalPlayer::OnPassportIsRunning);
	}
}

void UCustomLocalPlayer::OnPassportIsRunning(TWeakObjectPtr<class UImtblJSConnector> JSConnector)
{
	auto Settings = GetDefault<USampleGameSettings>();

	if (!Settings)
	{
		// TODO Handle system error
		return;
	}
	
	auto ImmutableSubsystem = GetGameInstance()->GetSubsystem<UImmutableSubsystem>();
	Passport = ImmutableSubsystem->GetPassport();
		
	if (Passport.IsValid())
	{
		FImmutablePassportInitData Data;

		Data.clientId = Settings->ClientID;
		Data.logoutRedirectUri = Settings->RedirectURI;
		Data.logoutRedirectUri = Settings->LogoutURI;
		Data.environment = Settings->Environment;
			
		Passport->Initialize(Data, UImmutablePassport::FImtblPassportResponseDelegate::CreateUObject(this, &UCustomLocalPlayer::OnPassportInitialized));
	}	
}

void UCustomLocalPlayer::OnPassportInitialized(FImmutablePassportResult Result)
{
	IsPassportInitialized = Result.Success;
	if (OnPlayerPassportInitialized.IsBound())
	{
		OnPlayerPassportInitialized.Broadcast(IsPassportInitialized);	
	}
	if (!IsPassportInitialized)
	{
		UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::ErrorFull, UDialogSubsystem::CreateErrorDescriptorWithErrorText(TEXT("Error"), TEXT("Immutable Passport is not initialized with error"), Result.Error));
	}
}

void UCustomLocalPlayer::OnPassportLoggedIn(FImmutablePassportResult Result)
{
	IsLocalPlayerLoggedIn = Result.Success;
	OnPlayerLoggedIn.Broadcast(Result.Success);

	if (!Result.Success)
	{
		UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::ErrorFull, UDialogSubsystem::CreateErrorDescriptorWithErrorText(TEXT("Error"), TEXT("Failed to login into Immutable Passport"), Result.Error));
	}
	else
	{
		CollectPassportData();
	}
}

void UCustomLocalPlayer::OnPassportLoggedOut(FImmutablePassportResult Result)
{
	if (Result.Success)
	{
	}
	else
	{
	}
}

void UCustomLocalPlayer::CollectPassportData()
{
	if (Passport.IsValid())
	{
		Passport->ConnectEvm(UImmutablePassport::FImtblPassportResponseDelegate::CreateLambda([this](FImmutablePassportResult Result)
		{
			if (Result.Success)
			{
				Passport->ZkEvmRequestAccounts(UImmutablePassport::FImtblPassportResponseDelegate::CreateLambda([this](FImmutablePassportResult Result)
				{
					if (Result.Success)
					{
						const auto RequestAccountsData = FImmutablePassportZkEvmRequestAccountsData::FromJsonObject(Result.Response.JsonObject);

						PassportWalletAddress = RequestAccountsData->accounts[0];
						NotifyIfAllPassportDataObtained();
					}
					else
					{
						UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::ErrorFull, UDialogSubsystem::CreateErrorDescriptorWithErrorText(TEXT("Error"), TEXT("Failed to obtain Immutable Passport data"), Result.Error));
					}
				}));
			}
		}));
	}
}

bool UCustomLocalPlayer::CheckAllPassportDataObtained()
{
	if (PassportWalletAddress.IsEmpty())
	{
		return false;
	}

	return true;
}

void UCustomLocalPlayer::NotifyIfAllPassportDataObtained()
{
	if (!CheckAllPassportDataObtained())
	{
		UCustomGameInstance::SendDialogMessage(this, FUIDialogTypes::ErrorSimple, UDialogSubsystem::CreateErrorSimpleDescriptor(TEXT("Error"), TEXT("Some Immutable Passport data is missing")));
		
		return;
	}

	OnPlayerPassportDataObtained.Broadcast();
}
