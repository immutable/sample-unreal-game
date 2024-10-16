#include "Dialog/DialogSubsystem.h"

#include "GameUIManagerSubsystem.h"
#include "GameUIPolicy.h"
#include "UIGameplayTags.h"
#include "Engine/GameInstance.h"

#define LOCTEXT_NAMESPACE "ImmutableUI"


UDialogDescriptor_OneAction* UDialogSubsystem::CreateErrorDescriptor(const FString& Header, const FString& Body)
{
	UDialogDescriptor_OneAction* Descriptor = NewObject<UDialogDescriptor_OneAction>();

	Descriptor->Header = FText::FromString(Header);
	Descriptor->Body = FText::FromString(Body);
	Descriptor->Action.Result = EDialogResult::Confirmed;
	Descriptor->ActionText = LOCTEXT("Ok", "Ok");

	return Descriptor;
}

UErrorDialogDescriptorWithErrorText* UDialogSubsystem::CreateErrorDescriptorWithErrorText(const FString& Header, const FString& Body, const FString& Error)
{
	UErrorDialogDescriptorWithErrorText* Descriptor = NewObject<UErrorDialogDescriptorWithErrorText>();

	Descriptor->Header = FText::FromString(Header);
	Descriptor->Body = FText::FromString(Body);
	Descriptor->ErrorText = FText::FromString(Error);
	Descriptor->Action.Result = EDialogResult::Confirmed;
	Descriptor->ActionText = LOCTEXT("Ok", "Ok");

	return Descriptor;
}

const FDialogType* UDialogSubsystem::GetDialogType(FGameplayTag DialogType) const
{
	const UGameInstance* GameInstance = GetLocalPlayer()->GetGameInstance();

	if (UGameUIManagerSubsystem* UIManager = GameInstance->GetSubsystem<UGameUIManagerSubsystem>())
	{
		if (const UGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
		{
			return Policy->GetDialogType(DialogType);
		}
	}
	
	return nullptr;
}

void UDialogSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UDialogSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

UDialog* UDialogSubsystem::ShowDialog(const FGameplayTag& DialogType, const UDialogDescriptor* Descriptor)
{
	auto DialogData = GetDialogType(DialogType);

	if (DialogData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Error dialog data is not assigned"));
		
		return nullptr;
	}

	auto Dialog = Cast<UDialog>(UGameUIManagerSubsystem::PushWidgetToLayer(GetLocalPlayer(), FUILayers::Modal,  DialogData->Dialog.LoadSynchronous()));

	if (!Dialog)
	{
		return nullptr;
	}
	
	Dialog->SetupDialog(Descriptor);

	return Dialog;
}



#undef LOCTEXT_NAMESPACE
