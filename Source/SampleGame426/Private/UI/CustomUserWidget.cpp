#include "CustomUserWidget.h"

#include "CustomLocalPlayer.h"

UCustomLocalPlayer* UCustomUserWidget::GetOwningCustomLocalPLayer() const
{
	return Cast<UCustomLocalPlayer>(GetOwningLocalPlayer());
}
