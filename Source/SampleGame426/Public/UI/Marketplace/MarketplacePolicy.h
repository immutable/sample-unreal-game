#pragma once

#include "OpenAPIOrderbookApi.h"
#include "OpenAPIStacksApi.h"
#include "OpenAPIOrdersApi.h"
#include "Data/NFTMetadataAttributeDataAsset.h"
#include "NFT/NFT_TableRowBase.h"

#include "MarketplacePolicy.generated.h"


class UCustomLocalPlayer;
/*
 * 
 */
UCLASS(Abstract)
class UMarketplacePolicy : public UObject
{
	GENERATED_BODY()

public:
	/* UObject Interface */
	virtual void PostInitProperties() override;
	/* UObject Interface */

	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	UDataTable* GetNFTDatatable();
	FNFT_TableRowBase* FindNFTTextureRow(FName RowName);

	ImmutableOpenAPI::OpenAPIStacksApi* GetStacksAPI()
	{
		return StacksAPI.Get();
	}
	
	ImmutableOpenAPI::OpenAPIOrdersApi* GetOrdersAPI()
	{
		return OrdersAPI.Get();
	}

	const FString& GetChainName()
	{
		return SearchAPIChainName;
	}

	const TArray<FString>& GetContracts()
	{
		return StackContractAddress;
	}
	
	ImmutableTsSdkApi::OpenAPIOrderbookApi* GetTsSdkAPI();
	
	FString GetBalanceContractAddress() const; 

	void SetKeyword(const FString& Keyword);
	void SetTraits(const TArray<FNFTMetadataAttribute_TraitType>& Traits);
	const FString& GetKeyword() const
	{
		return SearchStacksKeyword;		
	}

	const FString& GetTraits() const
	{
		return SearchStacksTraits;
	}
	
protected:
	// must be global
	UPROPERTY(EditAnywhere, Category = "Game", meta = (RequiredAssetDataTags = "RowStructure=NFT_TableRowBase"))
	UDataTable* NFT_Datatable;
	
	// Online values:
	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Online")
	FString ImmutableAPIURL;

	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Online")
	FString TsSdkAPIURL;

	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Online")
	FString SearchAPIChainName;
	
	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Online")
	FString IndexerStacksAPIChainName;

	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Online")
	uint32 RetryLimitCount = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Online")
	double RetryTimeoutRelativeSeconds = 1.0;

	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Search NFT stacks")
	FString BalanceContractAddress;
	
	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Search NFT stacks")
	TArray<FString> StackContractAddress;

	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Search NFT stacks")
	int32 NumberFractionalDigits = 4;

private:
	TUniquePtr<ImmutableOpenAPI::HttpRetryManager> HttpRetryManager;

	TUniquePtr<ImmutableOpenAPI::OpenAPIStacksApi> StacksAPI;
	TUniquePtr<ImmutableOpenAPI::OpenAPIOrdersApi> OrdersAPI;

	TUniquePtr<ImmutableTsSdkApi::OpenAPIOrderbookApi> TsSdkAPI;

	FString SearchStacksKeyword;
	FString SearchStacksTraits;
	
};
