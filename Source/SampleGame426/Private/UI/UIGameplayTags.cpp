#include "UIGameplayTags.h"

FGameplayTag FUIControlPanelButtons::Empty;
FGameplayTag FUIControlPanelButtons::NextPage;
FGameplayTag FUIControlPanelButtons::PreviousPage;
FGameplayTag FUIControlPanelButtons::Forward;
FGameplayTag FUIControlPanelButtons::Back;
FGameplayTag FUIControlPanelButtons::Buy;

inline FGameplayTag RequestGameplayTag(const FString& Prefix, const FString& Name)
{
	return FGameplayTag::RequestGameplayTag(*(Prefix + Name));
}

void FUIControlPanelButtons::InitUIGameplayTags_IconButtons()
{
	FString Prefix = TEXT("UI.ControlPanel.Button.");

	FUIControlPanelButtons::Empty			= RequestGameplayTag(Prefix, TEXT("Empty"));
	FUIControlPanelButtons::NextPage		= RequestGameplayTag(Prefix, TEXT("NextPage"));
	FUIControlPanelButtons::PreviousPage	= RequestGameplayTag(Prefix, TEXT("PreviousPage"));
	FUIControlPanelButtons::Forward			= RequestGameplayTag(Prefix, TEXT("Forward"));
	FUIControlPanelButtons::Back			= RequestGameplayTag(Prefix, TEXT("Back"));
	FUIControlPanelButtons::Buy				= RequestGameplayTag(Prefix, TEXT("Buy"));
}
