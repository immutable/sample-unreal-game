// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MarketplaceClientTypes.h"
#include "UObject/Object.h"
#include "Immutable/ImmutablePassport.h"

#include "MarketplaceClient.generated.h"

// delegate that takes an array
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFulfillOrderReturned, const TArray<FAction>&, OrderActions);

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

	// Get Unsigned Fulfill Order Transaction
	UFUNCTION(BlueprintCallable, Category = "MarketplaceClient")
	void GetUnsignedFulfillOrderTransactions(const FString& ListingId, const FString& TakerAddress);

	// List a fox skin NFT for sale
	// TODO

	// Cancel item for sale
	// TODO

	UPROPERTY(BlueprintAssignable, Category = "MarketplaceClient")
	FOnFulfillOrderReturned OnFulfillOrderReturned;
};
