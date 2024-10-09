#pragma once

#include "ImmutableTsSdkApi_DefaultApi.h"
#include "ImmutableOpenAPI/Public/OpenAPISearchApi.h"
#include "ImmutableIndexerSearchAPI/Public/OpenAPIStacksApi.h"
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
	enum
	{
		
	};
	
	/* UObject Interface */
	virtual void PostInitProperties() override;
	/* UObject Interface */

	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	UDataTable* GetNFTDatatable();
	FNFT_TableRowBase* FindNFTTextureRow(FName RowName);

	ImmutableOpenAPI::OpenAPISearchApi* GetSearchAPI();
	TSharedPtr<ImmutableOpenAPI::OpenAPISearchApi::SearchStacksRequest> GetSearchAPI_SearchStacksRequest();
	ImmutableIndexerSearchAPI::OpenAPIStacksApi* GetIndexerStacksAPI();
	TSharedPtr<ImmutableIndexerSearchAPI::OpenAPIStacksApi::SearchNFTsRequest> GetIndexerStacksAPI_SearchNfTsRequest();
	ImmutableTsSdkApi::ImmutableTsSdkApi_DefaultApi* GetTsSdkAPI();
	
	FString GetBalanceContractAddress() const; 

	void SetPageSize(int32 PageSize);
	void SetPageCursor(TOptional<FString> PageCursor);
	void SetAccount(const FString& Account);
	void SetKeyword(const FString& Keyword);
	void SetTraits(const TArray<FNFTMetadataAttribute_TraitType>& Traits);
	void SetOnlyIncludeOwnerListings(bool OnlyIncludeOwnerListings);
	
protected:
	// must be global
	UPROPERTY(EditAnywhere, Category = "Game", meta = (RequiredAssetDataTags = "RowStructure=NFT_TableRowBase"))
	UDataTable* NFT_Datatable;
	
	// Online values:
	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Online")
	FString MarketplaceAPIURL;

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
	TSharedPtr<ImmutableOpenAPI::OpenAPISearchApi::SearchStacksRequest> SearchAPI_SearchStacksRequest;
	TUniquePtr<ImmutableOpenAPI::OpenAPISearchApi> SearchAPI;
	TUniquePtr<ImmutableOpenAPI::HttpRetryManager> SearchAPI_HttpRetryManager;

	TSharedPtr<ImmutableIndexerSearchAPI::OpenAPIStacksApi::SearchNFTsRequest> IndexerStacksAPI_SearchNfTsRequest;
	TUniquePtr<ImmutableIndexerSearchAPI::OpenAPIStacksApi> IndexerStacksAPI;
	TUniquePtr<ImmutableIndexerSearchAPI::HttpRetryManager> IndexerStacksAPI_HttpRetryManager;

	TUniquePtr<ImmutableTsSdkApi::ImmutableTsSdkApi_DefaultApi> TsSdkAPI;

};
