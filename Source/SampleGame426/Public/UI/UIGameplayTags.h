#pragma once

#include "GameplayTagContainer.h"


struct SAMPLEGAME426_API FUILayers
{
	static FGameplayTag MenuWithControls;
	static FGameplayTag Menu;
	static FGameplayTag Modal;

	static void InitUIGameplayTags_Layers();
};

struct SAMPLEGAME426_API FUIControlPanelButtons
{
	static FGameplayTag Empty;
	static FGameplayTag NextPage;
	static FGameplayTag PreviousPage;
	static FGameplayTag Back;
	static FGameplayTag Forward;
	static FGameplayTag Buy;
	static FGameplayTag Sell;
	static FGameplayTag CancelSell;

	static void InitUIGameplayTags_ControlPanelButtons();
};

struct SAMPLEGAME426_API FUIDialogTypes
{
	static FGameplayTag None;
	static FGameplayTag ErrorSimple;
	static FGameplayTag ErrorFull;
	static FGameplayTag Confirmation;
	static FGameplayTag Message;
	static FGameplayTag Sell;
	static FGameplayTag Process;

	static void InitUIGameplayTags_DialogTypes();
};


