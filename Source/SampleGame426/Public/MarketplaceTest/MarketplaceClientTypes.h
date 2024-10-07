#pragma once

#include "CoreMinimal.h"
#include "JsonObjectConverter.h"
#include "Immutable/ImmutableRequests.h"
#include "MarketplaceClientTypes.generated.h"

USTRUCT(BlueprintType)
struct FDomain
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString ChainId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString VerifyingContract;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString Version;
};

USTRUCT(BlueprintType)
struct FOfferItem
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	uint8 ItemType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString Token;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString IdentifierOrCriteria;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString StartAmount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString EndAmount;
};

USTRUCT(BlueprintType)
struct FConsiderationItem
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	uint8 ItemType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString Token;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString IdentifierOrCriteria;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString StartAmount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString EndAmount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString Recipient;
};

/**
 * "message" object from NESTED INSIDE the "SIGNABLE" action.
 * See FSignableMessage
 */
USTRUCT(BlueprintType)
struct FMessage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString Offerer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString Zone;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	TArray<FOfferItem> Offer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	TArray<FConsiderationItem> Consideration;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	uint8 OrderType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString StartTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString EndTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString ZoneHash;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString Salt;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString ConduitKey;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString Counter;
};

USTRUCT(BlueprintType)
struct FNameType
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString Type;
};

USTRUCT(BlueprintType)
struct FSignableMessageTypes
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	TArray<FNameType> OrderComponents;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	TArray<FNameType> OfferItems;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	TArray<FNameType> ConsiderationItem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	TArray<FNameType> EIP712Domain;

	FString ToString() const
	{
		FString OutputString;
		FJsonObjectConverter::UStructToJsonObjectString(*this, OutputString);
		return OutputString;
	}
};

/**
 * Top level "message" object in the "SIGNABLE" action object
 * Note, this object is called "message" when returned from the prepare listing API
 */
USTRUCT(BlueprintType)
struct FSignableMessage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FZkEvmSignTypedDataV4Domain Domain;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FZkEvmSignTypedDataV4SignableMessageTypes Types;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FZkEvmSignTypedDataV4Message Message;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString PrimaryType;
};

USTRUCT(BlueprintType)
struct FOrderComponents
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString ConduitKey;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	TArray<FConsiderationItem> Consideration;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString EndTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	TArray<FOfferItem> Offer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString Offerer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	uint8 OrderType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString Salt;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString StartTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString TotalOriginalConsiderationItems;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString Zone;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString ZoneHash;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString Counter;
};

USTRUCT(BlueprintType)
struct FTransaction
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString To;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString From;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString GasLimit;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString Data;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    int32 ChainId;
    
    FString ToString() const
    {
        FString OutputString;
        FJsonObjectConverter::UStructToJsonObjectString(*this, OutputString);
        return OutputString;
    }
};

UENUM(BlueprintType)
enum class EPurpose : uint8
{
    APPROVAL UMETA(DisplayName = "Approval"),
    FULFILL_ORDER UMETA(DisplayName = "Fulfill Order"),
	CREATE_LISTING UMETA(DisplayName = "Create Listing")
};

USTRUCT(BlueprintType)
struct FAction
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString Type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString Purpose;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FTransaction PopulatedTransactions;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FSignableMessage Message;

	FString ToString() const
	{
		FString OutputString;
		FJsonObjectConverter::UStructToJsonObjectString(*this, OutputString);
		return OutputString;
	}
};

USTRUCT(BlueprintType)
struct FPrepareListingResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	TArray<FAction> Actions;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FOrderComponents OrderComponents;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString OrderHash;
};

USTRUCT(BlueprintType)
struct FSell
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString ContractAddress;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString TokenId;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString Type;
};

USTRUCT(BlueprintType)
struct FBuy
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString Amount;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString ContractAddress;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString Type;
};

USTRUCT(BlueprintType)
struct FFee
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString Amount;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString RecipientAddress;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString Type;
};

USTRUCT(BlueprintType)
struct FStatus
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString Name;
};

USTRUCT(BlueprintType)
struct FChain
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString Id;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString Name;
};

USTRUCT(BlueprintType)
struct FProtocolData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString Counter;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString OrderType;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString SeaportAddress;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString SeaportVersion;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString ZoneAddress;
};

USTRUCT(BlueprintType)
struct FFillStatus
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString Denominator;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString Numerator;
};

USTRUCT(BlueprintType)
struct FOrder
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString Id;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString OrderHash;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    TArray<FSell> Sell;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString Signature;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString StartAt;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FStatus Status;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString Type;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString UpdatedAt;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString AccountAddress;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    TArray<FBuy> Buy;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FChain Chain;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString CreatedAt;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString EndAt;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    TArray<FFee> Fees;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FFillStatus FillStatus;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FProtocolData ProtocolData;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString Salt;
};

USTRUCT(BlueprintType)
struct FFulfillOrderResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    TArray<FAction> Actions;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString Expiration;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FOrder Order;
};

USTRUCT(BlueprintType)
struct FFulfillOrderRequest
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString ListingId;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString TakerAddress;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FFee TakerFees;
};

USTRUCT(BlueprintType)
struct FPrepareListingRequest
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString MakerAddress;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FBuy Buy;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FSell Sell;
};

USTRUCT(BlueprintType)
struct FCreateListingResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString Id;
};

USTRUCT(BlueprintType)
struct FCreateListingResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FCreateListingResult Result;
};

USTRUCT(BlueprintType)
struct FCreateListingRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	TArray<FFee> MakerFees;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FOrderComponents OrderComponents;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString OrderHash;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
	FString OrderSignature;
};
