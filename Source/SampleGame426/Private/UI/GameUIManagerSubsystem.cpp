#include "GameUIManagerSubsystem.h"

#include "CustomLocalPlayer.h"
#include "UI/UIGameplayTags.h"

UActivatableWidget* UGameUIManagerSubsystem::PushWidgetToLayer(const ULocalPlayer* LocalPlayer, FGameplayTag LayerName, TSubclassOf<UActivatableWidget> WidgetClass)
{
	if (!LocalPlayer)
	{
		//UE_LOG ERROR
		return nullptr;
	}

	if (!WidgetClass)
	{
		//UE_LOG ERROR
		return nullptr;
	}

	if (UGameUIManagerSubsystem* UIManager = LocalPlayer->GetGameInstance()->GetSubsystem<UGameUIManagerSubsystem>())
	{
		if (UGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
		{
			if (UPrimaryGameLayout* RootLayout = Policy->GetRootLayout())
			{
				return RootLayout->PushWidgetToLayerStack(LayerName, WidgetClass);
			}
		}
	}

	return nullptr;
}

void UGameUIManagerSubsystem::PopWidgetFromLayer(UActivatableWidget* ActivatableWidget)
{
	if (const ULocalPlayer* LocalPlayer = ActivatableWidget->GetOwningLocalPlayer())
	{
		if (const UGameUIManagerSubsystem* UIManager = LocalPlayer->GetGameInstance()->GetSubsystem<UGameUIManagerSubsystem>())
		{
			if (const UGameUIPolicy* Policy = UIManager->GetCurrentUIPolicy())
			{
				if (UPrimaryGameLayout* RootLayout = Policy->GetRootLayout())
				{
					RootLayout->FindAndRemoveWidgetFromLayer(ActivatableWidget);
				}
			}
		}
	}
}

void UGameUIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();

	SwitchToPolicy(nullptr);
}

const UGameUIPolicy* UGameUIManagerSubsystem::GetCurrentUIPolicy() const
{
	return CurrentPolicy;
}

UGameUIPolicy* UGameUIManagerSubsystem::GetCurrentUIPolicy()
{
	return CurrentPolicy;
}

const TSoftClassPtr<UGameUIPolicy>& UGameUIManagerSubsystem::GetDefaultUIPolicyClass() const
{
	return DefaultUIPolicyClass;
}

void UGameUIManagerSubsystem::NotifyPlayerAdded(ULocalPlayer* LocalPlayer)
{
	if (ensure(LocalPlayer) && CurrentPolicy)
	{
		CurrentPolicy->NotifyPlayerAdded(Cast<UCustomLocalPlayer>(LocalPlayer));
	}
	else
	{
		OnPolicyChanged.AddWeakLambda(LocalPlayer, [this, LocalPlayer]()
		{
			CurrentPolicy->NotifyPlayerAdded(Cast<UCustomLocalPlayer>(LocalPlayer));
		});
	}
}

void UGameUIManagerSubsystem::NotifyPlayerDestroyed(ULocalPlayer* LocalPlayer)
{
	if (LocalPlayer && CurrentPolicy)
	{
		CurrentPolicy->NotifyPlayerDestroyed(Cast<UCustomLocalPlayer>(LocalPlayer));
	}

	OnPolicyChanged.RemoveAll(LocalPlayer);
}

void UGameUIManagerSubsystem::SwitchToPolicy(TSubclassOf<UGameUIPolicy> PolicyClass)
{
	SwitchToPolicy(NewObject<UGameUIPolicy>(this, PolicyClass));
}

void UGameUIManagerSubsystem::SwitchToPolicy(UGameUIPolicy* InPolicy)
{
	if (CurrentPolicy != InPolicy)
	{
		CurrentPolicy = InPolicy;
	}
}