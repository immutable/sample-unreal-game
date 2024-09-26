#include "Dialog/DialogSubsystem.h"

#include "GameUIManagerSubsystem.h"
#include "GameUIPolicy.h"
#include "UIGameplayTags.h"
#include "Engine/GameInstance.h"

#define LOCTEXT_NAMESPACE "ImmutableUI"

FDialogDescriptor UDialogSubsystem::CreateErrorDescriptor(const FText& Header, const FText& Body)
{
	FDialogDescriptor_OneAction Descriptor;

	Descriptor.Header = Header;
	Descriptor.Body = Body;
	Descriptor.Action.Result = EDialogResult::Confirmed;
	Descriptor.ActionText = LOCTEXT("Ok", "Ok");

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

void UDialogSubsystem::ShowError(const FDialogDescriptor& DialogDescriptor, FDialogResultDelegate ResultCallback)
{
	auto DialogData = GetDialogType(FUIDialogTypes::Error);

	if (DialogData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Error dialog data is not assigned"));
		
		return;
	}

	UDialog* Dialog =  Cast<UDialog>(UGameUIManagerSubsystem::PushWidgetToLayer(GetLocalPlayer(), FUILayers::Modal,  DialogData->Dialog.LoadSynchronous()));

	if (Dialog)
	{
		Dialog->SetupDialog(DialogDescriptor, ResultCallback);
	}
}

#undef LOCTEXT_NAMESPACE