#pragma once

#include "GameplayTagContainer.h"


struct SAMPLEGAME426_API FUIErrors
{
	static FGameplayTag Undefined;

	static void InitUIGameplayTags_Errors();
};

struct SAMPLEGAME426_API FUILayers
{
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

	static void InitUIGameplayTags_ControlPanelButtons();
};

struct SAMPLEGAME426_API FUIDialogTypes
{
	static FGameplayTag Error;
	static FGameplayTag Confirmation;

	static void InitUIGameplayTags_DialogTypes();
};


