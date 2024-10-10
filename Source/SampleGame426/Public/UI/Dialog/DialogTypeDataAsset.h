#pragma once

#include "Dialog.h"
#include "GameplayTagContainer.h"

#include "DialogTypeDataAsset.generated.h"


USTRUCT(BlueprintType)
struct SAMPLEGAME426_API FDialogType
{
	GENERATED_BODY()
		
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UDialog> Dialog;

	UPROPERTY(EditAnywhere)
	FText DefaultHeader;
};


UCLASS(BlueprintType, Const)
class SAMPLEGAME426_API UDialogTypeDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, FDialogType> Dialogs;
};
