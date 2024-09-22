#pragma once

#include "GameplayTagContainer.h"
#include "Base/ControlPanelButton.h"

#include "ControlPanelButtonDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FControlPanelButtonDisplayInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Display Info")
    FSlateBrush Icon;

    UPROPERTY(EditDefaultsOnly, Category = "Display Info")
    FSlateBrush Background;
};

/*
 * 
 */
UCLASS(BlueprintType, Const)
class SAMPLEGAME426_API UControlPanelButtonDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = Entry, meta = (AllowAbstract))
	TSoftClassPtr<UControlPanelButton> ControlButtonClass;
	
	UPROPERTY(EditDefaultsOnly, Category = ListEntries, meta = (AllowAbstract))
	TMap<FGameplayTag, FControlPanelButtonDisplayInfo> DisplayInfo;

};

