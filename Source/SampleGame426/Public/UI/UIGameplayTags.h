#pragma once

#include "GameplayTagContainer.h"


struct SAMPLEGAME426_API FUIControlPanelButtons
{
	static FGameplayTag NextPage;
	static FGameplayTag PreviousPage;
	static FGameplayTag Back;
	static FGameplayTag Forward;
	static FGameplayTag Buy;

	static void InitUIGameplayTags_IconButtons();
};


