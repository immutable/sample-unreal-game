#include "InformationSubsystem.h"

#include "Components/TextBlock.h"


void UInformationSubsystem::SetDisplayMessageBlock(UTextBlock* TextBlock)
{
	if (TextBlock)
	{
		MessageBlock = TextBlock;
	}
}

void UInformationSubsystem::ShowDisplayMessage(const FString& Message)
{
	if (!MessageBlock.IsValid() || Message.IsEmpty())
	{
		return;
	}

	MessageBlock->SetText(FText::FromString(Message));
}
