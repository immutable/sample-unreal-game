#include "LoginScreenWidget.h"

#include "CustomLocalPlayer.h"

void ULoginScreenWidget::NativeOnActivated()
{
	// Super::NativeOnActivated();
	//
	// auto LocalPlayer = GetOwningCustomLocalPLayer();
	//
	// LocalPlayer->CallAndRegister_OnPlayerLoggedIn(UCustomLocalPlayer::FPlayerLoggedInDelegate::FDelegate::CreateUObject(this, &ULoginScreenWidget::OnPassportLoggedIn));
}

// void ULoginScreenWidget::OnPassportLoggedIn(bool IsLoggedIn)
// {
// 	if (IsLoggedIn)
// 	{
// 		InternalProcessDeactivation();
// 	}
// }
