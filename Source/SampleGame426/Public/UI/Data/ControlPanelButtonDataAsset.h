#pragma once

#include "GameplayTagContainer.h"

#include "ControlPanelButtonDataAsset.generated.h"

class UControlPanelButton;

/**
 * @struct FControlPanelButtonDisplayInfo
 * @brief A structure to encapsulate the display info for a control panel
 */
USTRUCT(BlueprintType)
struct FControlPanelButtonDisplayInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Display Info")
	FText Name;

	UPROPERTY(EditDefaultsOnly, Category = "Display Info")
	FSlateBrush Icon;

	UPROPERTY(EditDefaultsOnly, Category = "Display Info", Meta = (sRGB = "true"))
	FLinearColor ColorAndOpacity;
};

/**
 * @class UControlPanelButtonDataAsset
 * @brief Data asset for control panel buttons
 */
UCLASS(BlueprintType, Const)
class SAMPLEGAME426_API UControlPanelButtonDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Entry", Meta = (AllowAbstract))
	TSoftClassPtr<UControlPanelButton> ControlButtonClass;

	UPROPERTY(EditDefaultsOnly, Category = "ListEntries", Meta = (AllowAbstract))
	TMap<FGameplayTag, FControlPanelButtonDisplayInfo> DisplayInfo;
};