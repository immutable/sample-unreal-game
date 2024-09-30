#include "UIGameplayTags.h"


FGameplayTag FUIErrors::Undefined;

FGameplayTag FUILayers::Menu;
FGameplayTag FUILayers::Modal;

FGameplayTag FUIControlPanelButtons::Empty;
FGameplayTag FUIControlPanelButtons::NextPage;
FGameplayTag FUIControlPanelButtons::PreviousPage;
FGameplayTag FUIControlPanelButtons::Forward;
FGameplayTag FUIControlPanelButtons::Back;
FGameplayTag FUIControlPanelButtons::Buy;

FGameplayTag FUIDialogTypes::Error;
FGameplayTag FUIDialogTypes::Confirmation;


inline FGameplayTag RequestGameplayTag(const FString& Prefix, const FString& Name)
{
	return FGameplayTag::RequestGameplayTag(*(Prefix + Name));
}

void FUIErrors::InitUIGameplayTags_Errors()
{
	FString Prefix = TEXT("UI.Errors.");

	FUIErrors::Undefined = RequestGameplayTag(Prefix, TEXT("Undefined"));
}

void FUILayers::InitUIGameplayTags_Layers()
{
	FString Prefix = TEXT("UI.Layer.");

	FUILayers::Menu		= RequestGameplayTag(Prefix, TEXT("Menu"));
	FUILayers::Modal	= RequestGameplayTag(Prefix, TEXT("Modal"));
}

void FUIControlPanelButtons::InitUIGameplayTags_ControlPanelButtons()
{
	FString Prefix = TEXT("UI.ControlPanel.Button.");

	FUIControlPanelButtons::Empty			= RequestGameplayTag(Prefix, TEXT("Empty"));
	FUIControlPanelButtons::NextPage		= RequestGameplayTag(Prefix, TEXT("NextPage"));
	FUIControlPanelButtons::PreviousPage	= RequestGameplayTag(Prefix, TEXT("PreviousPage"));
	FUIControlPanelButtons::Forward			= RequestGameplayTag(Prefix, TEXT("Forward"));
	FUIControlPanelButtons::Back			= RequestGameplayTag(Prefix, TEXT("Back"));
	FUIControlPanelButtons::Buy				= RequestGameplayTag(Prefix, TEXT("Buy"));
}

void FUIDialogTypes::InitUIGameplayTags_DialogTypes()
{
	FString Prefix = TEXT("UI.Dialog.");

	FUIDialogTypes::Error			= RequestGameplayTag(Prefix, TEXT("Error"));
	FUIDialogTypes::Confirmation	= RequestGameplayTag(Prefix, TEXT("Confirmation"));
}
