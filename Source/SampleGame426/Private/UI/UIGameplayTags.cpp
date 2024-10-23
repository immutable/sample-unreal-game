#include "UIGameplayTags.h"

#include "GameplayTagsManager.h"

void FNativeUIGameplayTags::AddTags()
{
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();

	UI_Layer_MenuWithControls				= Manager.AddNativeGameplayTag(TEXT("UI.Layer.MenuWithControls"));
	UI_Layer_Menu							= Manager.AddNativeGameplayTag(TEXT("UI.Layer.Menu"));
	UI_Layer_Modal							= Manager.AddNativeGameplayTag(TEXT("UI.Layer.Modal"));

	UI_Dialog_None							= Manager.AddNativeGameplayTag(TEXT("UI.Dialog.None"));
	UI_Dialog_ErrorSimple					= Manager.AddNativeGameplayTag(TEXT("UI.Dialog.ErrorSimple"));
	UI_Dialog_ErrorFull						= Manager.AddNativeGameplayTag(TEXT("UI.Dialog.ErrorFull"));
	UI_Dialog_Confirmation					= Manager.AddNativeGameplayTag(TEXT("UI.Dialog.Confirmation"));
	UI_Dialog_Message						= Manager.AddNativeGameplayTag(TEXT("UI.Dialog.Message"));
	UI_Dialog_Sell							= Manager.AddNativeGameplayTag(TEXT("UI.Dialog.Sell"));
	UI_Dialog_Process						= Manager.AddNativeGameplayTag(TEXT("UI.Dialog.Process"));

	UI_ControlPanel_Button_Empty			= Manager.AddNativeGameplayTag(TEXT("UI.ControlPanel.Button.Empty"));
	UI_ControlPanel_Button_NextPage			= Manager.AddNativeGameplayTag(TEXT("UI.ControlPanel.Button.NextPage"));
	UI_ControlPanel_Button_PreviousPage		= Manager.AddNativeGameplayTag(TEXT("UI.ControlPanel.Button.PreviousPage"));
	UI_ControlPanel_Button_Forward			= Manager.AddNativeGameplayTag(TEXT("UI.ControlPanel.Button.Forward"));
	UI_ControlPanel_Button_Back				= Manager.AddNativeGameplayTag(TEXT("UI.ControlPanel.Button.Back"));
	UI_ControlPanel_Button_Buy				= Manager.AddNativeGameplayTag(TEXT("UI.ControlPanel.Button.Buy"));
	UI_ControlPanel_Button_Sell				= Manager.AddNativeGameplayTag(TEXT("UI.ControlPanel.Button.Sell"));
	UI_ControlPanel_Button_CancelSell		= Manager.AddNativeGameplayTag(TEXT("UI.ControlPanel.Button.CancelSell"));
	UI_ControlPanel_Button_NFTInfo			= Manager.AddNativeGameplayTag(TEXT("UI.ControlPanel.Button.NFTInfo"));
	UI_ControlPanel_Button_Search			= Manager.AddNativeGameplayTag(TEXT("UI.ControlPanel.Button.Search"));
}