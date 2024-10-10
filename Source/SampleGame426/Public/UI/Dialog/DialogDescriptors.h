#pragma once

#include "DialogDescriptors.generated.h"


UENUM(BlueprintType)
enum class EDialogResult : uint8
{
	Confirmed,
	Cancelled,
	Closed,
	Unknown UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FDialogAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDialogResult Result = EDialogResult::Unknown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ActionText;
	
	FString GetActionName() const
	{
		switch (Result)
		{
		case EDialogResult::Confirmed: return TEXT("Confirmed");
		case EDialogResult::Cancelled: return TEXT("Cancelled");
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
	FDialogAction Action;
};

UCLASS()
class UDialogDescriptor_TwoActions : public UDialogDescriptor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FDialogAction OneAction;

	UPROPERTY(BlueprintReadWrite)
	FDialogAction TwoAction;
};


UCLASS()
class UErrorDialogDescriptorWithErrorText : public UDialogDescriptor_OneAction
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FText ErrorText;
	
};

UCLASS()
class USellDialogDescriptor : public UDialogDescriptor_TwoActions
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FText Price;
	
};