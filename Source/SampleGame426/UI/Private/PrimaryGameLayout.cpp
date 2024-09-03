
#include "PrimaryGameLayout.h"

#include "ActivatableWidgetContainer.h"
#include "GameUIManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"


/*static*/ UPrimaryGameLayout* UPrimaryGameLayout::GetPrimaryGameLayoutForPrimaryPlayer(const UObject* WorldContextObject)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	APlayerController* PlayerController = GameInstance->GetPrimaryPlayerController(false);
	return GetPrimaryGameLayout(PlayerController);
}

/*static*/ UPrimaryGameLayout* UPrimaryGameLayout::GetPrimaryGameLayout(APlayerController* PlayerController)
{
	return PlayerController ? GetPrimaryGameLayout(Cast<ULocalPlayer>(PlayerController->Player)) : nullptr;
}

/*static*/ UPrimaryGameLayout* UPrimaryGameLayout::GetPrimaryGameLayout(ULocalPlayer* LocalPlayer)
{
	if (LocalPlayer)
	{
		if (const UGameInstance* GameInstance = LocalPlayer->GetGameInstance())
		{
			if (UGameUIManagerSubsystem* UIManager = GameInstance->GetSubsystem<UGameUIManagerSubsystem>())
			{
				if (const UGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
				{
					if (UPrimaryGameLayout* RootLayout = Policy->GetRootLayout(LocalPlayer))
					{
						return RootLayout;
					}
				}
			}
		}
	}

	return nullptr;
}

void UPrimaryGameLayout::RegisterLayer(FGameplayTag LayerTag, UActivatableWidgetContainer* LayerWidget)
{
	if (!IsDesignTime())
	{
		Layers.Add(LayerTag, LayerWidget);
	}
}

void UPrimaryGameLayout::FindAndRemoveWidgetFromLayer(UActivatableWidget* ActivatableWidget)
{
	// We're not sure what layer the widget is on so go searching.
	for (const auto& LayerKVP : Layers)
	{
		LayerKVP.Value->RemoveWidget(*ActivatableWidget);
	}
}

UActivatableWidgetContainer* UPrimaryGameLayout::GetLayerWidget(FGameplayTag LayerName)
{
	return Layers.FindRef(LayerName);
}
