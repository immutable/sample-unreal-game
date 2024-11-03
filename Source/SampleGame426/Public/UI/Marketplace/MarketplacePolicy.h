#pragma once

#include "APIOrderbookApi.h"
#include "APIMetadataSearchApi.h"
#include "APIOrdersApi.h"
#include "Data/NFTMetadataAttributeDataAsset.h"
#include "NFT/NFT_TableRowBase.h"

#include "MarketplacePolicy.generated.h"


class UCustomLocalPlayer;

/**
 * @class UMarketplacePolicy
 * @brief Manages the policies and rules for the game's marketplace.
 * @details This class centralizes the management of marketplace functionality, including caching data for search stack queries and accessing various APIs such as Immutable zkEVM API and Orderbook API. It provides methods to:
 * - Retrieve NFT data table and specific NFT texture rows.
 * - Access instances of Immutable zkEVM API and Orderbook API for marketplace and inventory queries.
 * - Get API-related data such as contract addresses for NFTs and cryptocurrencies, API endpoints, and associated chains.
 * @note This class serves as a centralized storage for marketplace/inventory search query data and related configurations.
 */
UCLASS(Abstract)
class UMarketplacePolicy : public UObject
{
	GENERATED_BODY()

public:
	/* UObject Interface */
	virtual void PostInitProperties() override;
	/* UObject Interface */

	/**
	 * Retrieves the data table containing NFT information such as unique NFT name and thumbnail image.
	 *
	 * @return A pointer to the UDataTable that holds the NFT data.
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	UDataTable* GetNFTDatatable();
	/**
	 * Finds and returns an NFT texture row based on the provided unique NFT name.
	 *
	 * @param RowName The name of the row to find.
	 * @return A pointer to the found a datable row, or nullptr if no matching row is found.
	 */
	FNFT_TableRowBase* FindNFTTextureRow(FName RowName);

	/**
	 * Retrieves the search stacks instance of Immutable zkEVM API. Primarily used for the marketplace NFT search queries. 
	 * @see ImmutablezkEVMAPI::APIStacksApi in ImmutableOpenAPI plugin.
	 *
	 * @return A pointer to an ImmutablezkEVMAPI::APIStacksApi instance.
	 */
	ImmutablezkEVMAPI::APIMetadataSearchApi* GetStacksAPI()
	{
		return MetadataSearchAPI.Get();
	}
	
	/**
	 * Retrieves the orders instance of Immutable zkEVM API. Primarily used for the player's Inventory NFT queries. 
	 * @see ImmutablezkEVMAPI::APIOrdersApi in ImmutableOpenAPI plugin.
	 *
	 * @return A pointer to an instance of ImmutablezkEVMAPI::APIOrdersApi.
	 */
	ImmutablezkEVMAPI::APIOrdersApi* GetOrdersAPI()
	{
		return OrdersAPI.Get();
	}

	/**
	 * Retrieves the name of the chain used to pass to the Immutable zkEVM API and Orderbook API.
	 *
	 * @return A constant reference to an FString containing the name of the chain.
	 */
	const FString& GetChainName()
	{
		return SearchAPIChainName;
	}

	/**
	 * Retrieves the list of NFT contracts used in the APIs' queries.
	 *
	 * @return A constant reference to an array of strings representing the contracts.
	 */
	const TArray<FString>& GetContracts()
	{
		return StackContractAddress;
	}
	
	/**
	 * @brief Retrieves the instance of Orderbook API.
	 * @see ImmutableOrderbook::APIOrderbookApi in ImmutableTsSdkApi plugin.
	 *
	 * @return A pointer to the ImmutableOrderbook::APIOrderbookApi instance.
	 */
	ImmutableOrderbook::APIOrderbookApi* GetTsSdkAPI();
	
	/**
	 * @brief Retrieves the cryptocurrency contract address associated with the user's wallet balance.
	 *
	 * @return A string representing the contract address.
	 */
	FString GetBalanceContractAddress() const; 

	/**
	 * Setter and getter of the cached keyword for the marketplace search.
	 * @see USearchStacksOptionWidget for more details on how it is used.
	 *
	 * @param Keyword The keyword to be set.
	 */
	void SetKeyword(const FString& Keyword);
	const FString& GetKeyword() const
	{
		return SearchStacksKeyword;		
	}
	/**
	 * Setter and getter of the traits for the marketplace search.
	 * @see USearchStacksOptionWidget for more details on how it is used.
	 *
	 * @param Traits An array of FNFTMetadataAttribute_TraitType objects representing the traits to be set.
	 */
	void SetTraits(const TArray<FNFTMetadataAttribute_TraitType>& Traits);
	const FString& GetTraits() const
	{
		return SearchStacksTraits;
	}

	/**
	 * Setter and getter of the selected NFT contract address for the marketplace search filters.
	 * @see USearchStacksContractSelectWidget for more details on how it is used.
	 *
	 * @param InSelectedContractAddress NFT contract address used to obtain metadata filters to perform further search of NFTs.
	 */
	void SetSelectedContractAddress(const FString& InSelectedContractAddress) { SelectedContractAddress = InSelectedContractAddress; }
	const FString& GetSelectedContractAddress() { return SelectedContractAddress; }
	
protected:
	/// A pointer to a UDataTable that holds the NFT data.
	/// This data table is used to manage and access information related to NFTs within the marketplace.
	UPROPERTY(EditAnywhere, Category = "Game", meta = (RequiredAssetDataTags = "RowStructure=NFT_TableRowBase"))
	UDataTable* NFT_Datatable;
	
	// Online values:

	/// The URL for the Immutable zkEVM API.
	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Online")
	FString ImmutableAPIURL;

	/// The URL for the Orderbook API.
	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Online")
	FString TsSdkAPIURL;

	/// The name of the API chain used by Immutable zkEVM API and Orderbook API.
	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Online")
	FString SearchAPIChainName;
	
	/// The maximum number of retry attempts allowed.
	/// This variable is used to limit the number of times a certain HTTP operation can be retried.
	/// Default value is set to 0.
	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Online")
	uint32 RetryLimitCount = 0;

	/// The relative timeout in seconds for retrying a HTTP operation.
	/// This value determines the delay before a retry attempt is made.
	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Online")
	double RetryTimeoutRelativeSeconds = 1.0;

	/// The address of the cryptocurrency contract in the blockchain.
	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Search NFT stacks")
	FString BalanceContractAddress;

	/// An array of NFT contract addresses used for searching NFTs in the marketplace or displaying them in the player's inventory.
	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Search NFT stacks")
	TArray<FString> StackContractAddress;

	UPROPERTY(EditDefaultsOnly, Category = "Marketplace|Search NFT stacks")
	/// The number of fractional digits to displayed in widgets with fees and prices.
	/// see: USearchStacksListing_ListingsWidget::AddItem and FMathUtility::ConvertWeiStringToFloatValueString
	int32 NumberFractionalDigits = 4;

private:
	TUniquePtr<ImmutablezkEVMAPI::HttpRetryManager> HttpRetryManager;

	TUniquePtr<ImmutablezkEVMAPI::APIMetadataSearchApi> MetadataSearchAPI;
	TUniquePtr<ImmutablezkEVMAPI::APIOrdersApi> OrdersAPI;

	TUniquePtr<ImmutableOrderbook::APIOrderbookApi> TsSdkAPI;

	FString SearchStacksKeyword;
	FString SearchStacksTraits;
	FString SelectedContractAddress;
	
};
