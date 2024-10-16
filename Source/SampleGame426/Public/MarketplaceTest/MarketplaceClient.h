// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MarketplaceClientTypes.h"
#include "UObject/Object.h"
#include "Immutable/ImmutablePassport.h"

#include "MarketplaceClient.generated.h"

// delegate that takes an array
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFulfillOrderReturned, const TArray<FAction>&, OrderActions);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPrepareListingReturned, const FPrepareListingResponse, PrepareListingResponse);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCreateListingReturned, const FCreateListingResponse, CreateListingResponse);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCancelListingReturned, const FCancelListingResponse, CancelListingResponse);

/**
 * 
 */
UCLASS(Blueprintable)
class SAMPLEGAME426_API UMarketplaceClient : public UObject
{
	GENERATED_BODY()

public:
	// Get market listings
	// TODO

	// Get listing by ID
	// TODO

	// Get Unsigned Fulfill Order Transaction
	UFUNCTION(BlueprintCallable, Category = "MarketplaceClient")
	void GetUnsignedFulfillOrderTransactions(const FString& ListingId, const FString& TakerAddress);

	// Prepare listing
	UFUNCTION(BlueprintCallable, Category = "MarketplaceClient")
	void PrepareListing(const FString& MakerAddress, FBuy Buy, FSell Sell);
	
	// Create listing
	UFUNCTION(BlueprintCallable, Category = "MarketplaceClient")
	void CreateListing(FOrderComponents OrderComponents, const FString& OrderHash, const FString& OrderSignature);

	// Cancel item for sale
	UFUNCTION(BlueprintCallable, Category = "MarketplaceClient")
	void CancelListing(const FString& ListingId, const FString& WalletAddress);

	UPROPERTY(BlueprintAssignable, Category = "MarketplaceClient")
	FOnFulfillOrderReturned OnFulfillOrderReturned;

	UPROPERTY(BlueprintAssignable, Category = "MarketplaceClient")
	FOnPrepareListingReturned OnPrepareListingReturned;

	UPROPERTY(BlueprintAssignable, Category = "MarketplaceClient")
	FOnCreateListingReturned OnCreateListingReturned;

	UPROPERTY(BlueprintAssignable, Category = "MarketplaceClient")
	FOnCancelListingReturned OnCancelListingReturned;
};
