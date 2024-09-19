#pragma once

#include "CoreMinimal.h"

#include "GetBalanceResponse.generated.h"

USTRUCT(BlueprintType)
struct FGetBalanceResponse
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Quantity;
};
