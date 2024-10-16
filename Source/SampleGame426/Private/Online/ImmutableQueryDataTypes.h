#pragma once

#include "JsonObjectConverter.h"

#include "ImmutableQueryDataTypes.generated.h"


USTRUCT(BlueprintType)
struct FTokenBalance
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Quantity;
};

USTRUCT(BlueprintType)
struct FTransaction
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString To;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString From;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString GasLimit;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Data;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
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

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Type;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FTransaction PopulatedTransactions;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
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

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString ContractAddress;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString TokenId;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Type;
};

USTRUCT(BlueprintType)
struct FBuy
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Amount;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString ContractAddress;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Type;
};

USTRUCT(BlueprintType)
struct FFee
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Amount;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString RecipientAddress;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Type;
};

USTRUCT(BlueprintType)
struct FStatus
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Name;
};

USTRUCT(BlueprintType)
struct FChain
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Id;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Name;
};

USTRUCT(BlueprintType)
struct FProtocolData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Counter;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString OrderType;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString SeaportAddress;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString SeaportVersion;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString ZoneAddress;
};

USTRUCT(BlueprintType)
struct FFillStatus
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Denominator;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Numerator;
};

USTRUCT(BlueprintType)
struct FOrder
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Id;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString OrderHash;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FSell> Sell;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Signature;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString StartAt;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FStatus Status;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Type;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString UpdatedAt;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString AccountAddress;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FBuy> Buy;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FChain Chain;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString CreatedAt;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString EndAt;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FFee> Fees;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FFillStatus FillStatus;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FProtocolData ProtocolData;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Salt;
};

USTRUCT(BlueprintType)
struct FFulfillOrderResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAction> Actions;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Expiration;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FOrder Order;
};

USTRUCT(BlueprintType)
struct FFulfillOrderRequest
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString ListingId;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString TakerAddress;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FFee TakerFees;
};
