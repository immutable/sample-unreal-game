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

/**
 * @struct FDialogAction
 * @breif A structure to encapsulate the details of a dialog's action
 */
USTRUCT(BlueprintType)
struct FDialogAction
{
	GENERATED_BODY()

public:
	FString GetActionName() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDialogResult Result = EDialogResult::Unknown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ActionText;
};

/**
 * @class UDialogDescriptor
 * @brief A class to encapsulate the details of a dialog's content
 */
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

/**
 * @class UDialogDescriptor_OneAction
 * @brief A class to represent a dialog with a single action
 */
UCLASS()
class UDialogDescriptor_OneAction : public UDialogDescriptor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FDialogAction Action;
};

/**
 * @class UDialogDescriptor_TwoActions
 * @brief A class to represent a dialog with a two actions
 */
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

/**
 * @class UErrorDialogDescriptorWithErrorText 
 * @brief A class to represent a dialog with error text
 */
UCLASS()
class UErrorDialogDescriptorWithErrorText : public UDialogDescriptor_OneAction
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FText ErrorText;
};

/**
 * @class UErrorDialogDescriptorWithErrorText 
 * @brief A class to represent a dialog with selling functionality
 */
UCLASS()
class USellDialogDescriptor : public UDialogDescriptor_TwoActions
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FText Price;
};

/**
 * @class UErrorDialogDescriptorWithErrorText 
 * @brief A class to represent a dialog with processing functionality
 */
UCLASS()
class UProcessDialogDescriptor : public UDialogDescriptor_OneAction
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	bool IsInProgress = true;
};