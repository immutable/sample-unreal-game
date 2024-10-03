#pragma once

#include "ImmutableTsSdkApi_DefaultApi.h"
#include "OpenAPISearchApi.h"
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
	UMarketplacePolicy();
	/* UObject Interface */
	virtual void PostInitProperties() override;
	/* UObject Interface */

	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	class UDataTable* GetNFTDatatable();
	FNFT_TableRowBase* FindNFTTextureRow(FName RowName);

	ImmutableOpenAPI::OpenAPISearchApi* GetOpenAPISearchApi();
	TSharedPtr<ImmutableOpenAPI::OpenAPISearchApi::SearchStacksRequest> GetSearchStacksRequest();
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
	FString SearchStacksChainName;

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
	TSharedPtr<ImmutableOpenAPI::OpenAPISearchApi::SearchStacksRequest> SearchStacksRequestData;
	TUniquePtr<ImmutableOpenAPI::OpenAPISearchApi> SearchAPI;
	TUniquePtr<ImmutableOpenAPI::HttpRetryManager> HttpRetryManager;
	TUniquePtr<ImmutableTsSdkApi::ImmutableTsSdkApi_DefaultApi> TsSdkAPI;

};
