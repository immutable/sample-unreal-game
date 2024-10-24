#pragma once

#include "GameplayTagContainer.h"

#include "DialogSubsystem.generated.h"

struct FDialogAction;
struct FDialogType;

class UDialogDescriptor;
class UDialogDescriptor_OneAction;
class UDialogDescriptor_TwoActions;
class UErrorDialogDescriptorWithErrorText;
class UProcessDialogDescriptor;

/**
 * @class UDialogSubsystem
 * @brief Subsystem responsible for managing dialogs
 */
UCLASS()
class SAMPLEGAME426_API UDialogSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	static UDialogDescriptor_OneAction* CreateErrorSimpleDescriptor(const FString& Header, const FString& Body);
	static UErrorDialogDescriptorWithErrorText* CreateErrorDescriptorWithErrorText(const FString& Header, const FString& Body, const FString& Error);
	static UDialogDescriptor_OneAction* CreateMessageDescriptor(const FString& Header, const FString& Body);
	static UDialogDescriptor_TwoActions* CreateConfirmMessageDescriptor(const FString& Header, const FString& Body);
	static UDialogDescriptor_TwoActions* CreateSellDescriptor(const FString& Header, const FString& Body);
	static UProcessDialogDescriptor* CreateProcessDescriptor(const FString& Header, const FString& Body, const FDialogAction& Action, bool IsInProgress = true);

public:
	UFUNCTION(BlueprintCallable)
	UDialog* ShowDialog(const FGameplayTag& DialogType, UDialogDescriptor* Descriptor);

private:
	const FDialogType* GetDialogType(FGameplayTag DialogType) const;
};