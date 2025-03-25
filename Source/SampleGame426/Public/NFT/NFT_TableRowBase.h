#pragma once

#include "Engine/DataTable.h"

#include "NFT_TableRowBase.generated.h"

class UTexture2D;

USTRUCT(BlueprintType)
struct SAMPLEGAME426_API FNFT_TableRowBase : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> Thumbnail;
};