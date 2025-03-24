#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "CustomBlueprintFunctionLibrary.generated.h"

UCLASS()
class SAMPLEGAME426_API UCustomBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Immutable Utility")
	static void LogError(const FString& ErrorMessage);

	UFUNCTION(BlueprintCallable, Category = "Immutable Utility")
	static void ShowThrobber(const ULocalPlayer* LocalPlayer);

	UFUNCTION(BlueprintCallable, Category = "Immutable Utility")
	static void HideThrobber(const ULocalPlayer* LocalPlayer);

	UFUNCTION(BlueprintCallable, Category = "Immutable Utility")
	static void ShowOnRampWidget(const ULocalPlayer* LocalPlayer);
};