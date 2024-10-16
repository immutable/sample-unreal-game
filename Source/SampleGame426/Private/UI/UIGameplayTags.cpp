#include "UIGameplayTags.h"


FGameplayTag FUILayers::MenuWithControls;
FGameplayTag FUILayers::Menu;
FGameplayTag FUILayers::Modal;

FGameplayTag FUIControlPanelButtons::Empty;
FGameplayTag FUIControlPanelButtons::NextPage;
FGameplayTag FUIControlPanelButtons::PreviousPage;
FGameplayTag FUIControlPanelButtons::Forward;
FGameplayTag FUIControlPanelButtons::Back;
FGameplayTag FUIControlPanelButtons::Buy;
FGameplayTag FUIControlPanelButtons::Sell;
FGameplayTag FUIControlPanelButtons::CancelSell;

FGameplayTag FUIDialogTypes::None;
FGameplayTag FUIDialogTypes::ErrorSimple;
FGameplayTag FUIDialogTypes::ErrorFull;
FGameplayTag FUIDialogTypes::Confirmation;
FGameplayTag FUIDialogTypes::Message;
FGameplayTag FUIDialogTypes::Sell;


inline FGameplayTag RequestGameplayTag(const FString& Prefix, const FString& Name)
{
	return FGameplayTag::RequestGameplayTag(*(Prefix + Name));
}

void FUILayers::InitUIGameplayTags_Layers()
{
	FString Prefix = TEXT("UI.Layer.");

	FUILayers::MenuWithControls	= RequestGameplayTag(Prefix, TEXT("MenuWithControls"));
	FUILayers::Menu				= RequestGameplayTag(Prefix, TEXT("Menu"));
	FUILayers::Modal			= RequestGameplayTag(Prefix, TEXT("Modal"));
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
	FUIControlPanelButtons::Sell			= RequestGameplayTag(Prefix, TEXT("Sell"));
	FUIControlPanelButtons::CancelSell		= RequestGameplayTag(Prefix, TEXT("CancelSell"));
}

void FUIDialogTypes::InitUIGameplayTags_DialogTypes()
{
	FString Prefix = TEXT("UI.Dialog.");

	FUIDialogTypes::None		    = RequestGameplayTag(Prefix, TEXT("None"));
	FUIDialogTypes::ErrorSimple		= RequestGameplayTag(Prefix, TEXT("ErrorSimple"));
	FUIDialogTypes::ErrorFull		= RequestGameplayTag(Prefix, TEXT("ErrorFull"));
	FUIDialogTypes::Confirmation	= RequestGameplayTag(Prefix, TEXT("Confirmation"));
	FUIDialogTypes::Message			= RequestGameplayTag(Prefix, TEXT("Message"));
	FUIDialogTypes::Sell			= RequestGameplayTag(Prefix, TEXT("Sell"));
}
