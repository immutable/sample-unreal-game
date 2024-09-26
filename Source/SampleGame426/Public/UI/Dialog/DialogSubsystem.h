#pragma once

#include "Dialog.h"
#include "DialogTypeDataAsset.h"
#include "GameplayTagContainer.h"
#include "Subsystems/LocalPlayerSubsystem.h"

#include "DialogSubsystem.generated.h"


/**
 * 
 */
UCLASS(config = Game)
class SAMPLEGAME426_API UDialogSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	UDialogSubsystem() { }

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual void ShowError(const FDialogDescriptor& DialogDescriptor, FDialogResultDelegate ResultCallback = FDialogResultDelegate());
	
	static FDialogDescriptor CreateErrorDescriptor(const FText& Header, const FText& Body);

private:

	const FDialogType* GetDialogType(FGameplayTag DialogType) const;

};
