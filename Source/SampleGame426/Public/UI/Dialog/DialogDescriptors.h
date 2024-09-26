#pragma once

#include "DialogDescriptors.generated.h"


UENUM(BlueprintType)
enum class EDialogResult : uint8
{
	Confirmed,
	Declined,
	Cancelled,
	Killed,
	Retried,
	Unknown UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FDialogAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDialogResult Result = EDialogResult::Unknown;
	
	FString GetActionName() const
	{
		switch (Result)
		{
		case EDialogResult::Confirmed: return TEXT("Confirmed");
		case EDialogResult::Declined: return TEXT("Declined");
		case EDialogResult::Cancelled: return TEXT("Cancelled");
		case EDialogResult::Killed: return TEXT("Killed");
		case EDialogResult::Retried: return TEXT("Retried");
		default: return TEXT("Unknown");
		}
	}
};

UCLASS(BlueprintType, MinimalAPI, Transient)
class UDialogDescriptor : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Header;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Body;
};

UCLASS()
class UDialogDescriptor_OneAction : public UDialogDescriptor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FText ActionText;
	
	UPROPERTY(BlueprintReadWrite)
	FDialogAction Action;
};

UCLASS()
class UDialogDescriptor_TwoActions : public UDialogDescriptor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FText ActionOneText;

	UPROPERTY(BlueprintReadWrite)
	FText ActionTwoText;

	UPROPERTY(BlueprintReadWrite)
	FDialogAction OneAction;

	UPROPERTY(BlueprintReadWrite)
	FDialogAction TwoAction;
};