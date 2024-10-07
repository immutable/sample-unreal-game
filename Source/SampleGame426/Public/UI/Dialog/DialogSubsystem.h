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

	UFUNCTION(BlueprintCallable)
	UDialog* ShowDialog(const FGameplayTag& DialogType, const UDialogDescriptor* Descriptor);

	static UDialogDescriptor_OneAction* CreateErrorDescriptor(const FString& Header, const FString& Body);
	static UErrorDialogDescriptorWithErrorText* CreateErrorDescriptorWithErrorText(const FString& Header, const FString& Body, const FString& Error);

private:
	const FDialogType* GetDialogType(FGameplayTag DialogType) const;

};
