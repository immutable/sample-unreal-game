#include "Dialog/DialogDescriptors.h"

FString FDialogAction::GetActionName() const
{
	return StaticEnum<EDialogResult>()->GetNameStringByValue(static_cast<int64>(Result));
}