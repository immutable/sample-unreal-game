#pragma once

#include "Dialog.h"
#include "DialogTypeDataAsset.h"
#include "GameplayTagContainer.h"
#include "Subsystems/LocalPlayerSubsystem.h"

#include "DialogSubsystem.generated.h"


/**
 * 
 */
UCLASS()
class SAMPLEGAME426_API UDialogSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	UDialog* ShowDialog(const FGameplayTag& DialogType, UDialogDescriptor* Descriptor);

	static UDialogDescriptor_OneAction* CreateErrorSimpleDescriptor(const FString& Header, const FString& Body);
	static UErrorDialogDescriptorWithErrorText* CreateErrorDescriptorWithErrorText(const FString& Header, const FString& Body, const FString& Error);
	static UDialogDescriptor_OneAction* CreateMessageDescriptor(const FString& Header, const FString& Body);
	static UDialogDescriptor_TwoActions* CreateConfirmMessageDescriptor(const FString& Header, const FString& Body);
	static UDialogDescriptor_TwoActions* CreateSellDescriptor(const FString& Header, const FString& Body);
	static UProcessDialogDescriptor* CreateProcessDescriptor(const FString& Header, const FString& Body, const FDialogAction& Action, bool IsInProgress = true);

private:
	const FDialogType* GetDialogType(FGameplayTag DialogType) const;

};
