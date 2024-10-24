#pragma once

#include "GameplayTagContainer.h"

#include "UI/Dialog/Dialog.h"

#include "DialogTypeDataAsset.generated.h"

/**
 * @struct FDialogType
 * @breif A structure to encapsulate the details of a dialog type
 */
USTRUCT(BlueprintType)
struct SAMPLEGAME426_API FDialogType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UDialog> Dialog;

	UPROPERTY(EditAnywhere)
	FText DefaultHeader;
};

/**
 * @class UDialogTypeDataAsset
 * @brief Data asset for mapping tags to dialog types
 */
UCLASS(BlueprintType, Const)
class SAMPLEGAME426_API UDialogTypeDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, FDialogType> Dialogs;
};