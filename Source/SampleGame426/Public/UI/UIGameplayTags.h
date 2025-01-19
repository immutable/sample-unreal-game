#pragma once

#include "GameplayTagContainer.h"

struct SAMPLEGAME426_API FNativeUIGameplayTags : public FGameplayTagNativeAdder
{
	/** FGameplayTagNativeAdder: Interface Begin */
	virtual void AddTags() override;
	/** FGameplayTagNativeAdder: Interface End */

	FGameplayTag UI_Layer_MenuWithControls;
	FGameplayTag UI_Layer_Menu;
	FGameplayTag UI_Layer_Modal;

	FGameplayTag UI_Dialog_None;
	FGameplayTag UI_Dialog_ErrorSimple;
	FGameplayTag UI_Dialog_ErrorFull;
	FGameplayTag UI_Dialog_Confirmation;
	FGameplayTag UI_Dialog_Message;
	FGameplayTag UI_Dialog_Sell;
	FGameplayTag UI_Dialog_Process;
	FGameplayTag UI_Dialog_OnRamp;

	FGameplayTag UI_ControlPanel_Button_Empty;
	FGameplayTag UI_ControlPanel_Button_NextPage;
	FGameplayTag UI_ControlPanel_Button_PreviousPage;
	FGameplayTag UI_ControlPanel_Button_Back;
	FGameplayTag UI_ControlPanel_Button_Forward;
	FGameplayTag UI_ControlPanel_Button_Buy;
	FGameplayTag UI_ControlPanel_Button_Sell;
	FGameplayTag UI_ControlPanel_Button_CancelSell;
	FGameplayTag UI_ControlPanel_Button_NFTInfo;
	FGameplayTag UI_ControlPanel_Button_Search;
	FGameplayTag UI_ControlPanel_Button_Filters;
};

static FNativeUIGameplayTags NativeUIGameplayTags;