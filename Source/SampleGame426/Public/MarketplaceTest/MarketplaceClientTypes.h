#pragma once

#include "CoreMinimal.h"
#include "JsonObjectConverter.h"
#include "MarketplaceClientTypes.generated.h"

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
    FULFILL_ORDER UMETA(DisplayName = "Fulfill Order")
};


USTRUCT(BlueprintType)
struct FAction
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FString Type;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    FTransaction PopulatedTransactions;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MarketplaceClientTypes")
    EPurpose Purpose;

    FString ToString() const
    {
        FString OutputString;
        FJsonObjectConverter::UStructToJsonObjectString(*this, OutputString);
        return OutputString;
    }
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
