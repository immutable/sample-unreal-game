#include "Dialog/DialogDescriptors.h"

inline FString FDialogAction::GetActionName() const
{
	switch (Result)
	{
	case EDialogResult::Confirmed: return TEXT("Confirmed");
	case EDialogResult::Cancelled: return TEXT("Cancelled");
	default: return TEXT("Unknown");
	}
}