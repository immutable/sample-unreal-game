#include "Dialog/DialogSubsystem.h"

#include "GameUIManagerSubsystem.h"
#include "GameUIPolicy.h"
#include "UIGameplayTags.h"
#include "Engine/GameInstance.h"

#define LOCTEXT_NAMESPACE "ImmutableUI"

UDialogDescriptor_OneAction* UDialogSubsystem::CreateErrorDescriptor(const FText& Header, const FText& Body)
{
	UDialogDescriptor_OneAction* Descriptor = NewObject<UDialogDescriptor_OneAction>();

	Descriptor->Header = Header;
	Descriptor->Body = Body;
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

UDialog* UDialogSubsystem::ShowError(const UDialogDescriptor* Descriptor)
{
	auto DialogData = GetDialogType(FUIDialogTypes::Error);

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
