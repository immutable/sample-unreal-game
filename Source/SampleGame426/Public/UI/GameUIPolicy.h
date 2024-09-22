#pragma once

#include "PrimaryGameLayout.h"
#include "Marketplace/MarketplacePolicy.h"

#include "GameUIPolicy.generated.h"


class UCustomLocalPlayer;

UCLASS(Abstract, Blueprintable, Within = GameUIManagerSubsystem)
class UGameUIPolicy : public UObject
{
	GENERATED_BODY()

public:
	template <typename GameUIPolicyClass = UGameUIPolicy>
	static GameUIPolicyClass* GetGameUIPolicyAs(const UObject* WorldContextObject)
	{
		return Cast<GameUIPolicyClass>(GetGameUIPolicy(WorldContextObject));
	}

	static UGameUIPolicy* GetGameUIPolicy(const UObject* WorldContextObject);
	virtual UWorld* GetWorld() const override;
	class UGameUIManagerSubsystem* GetOwningUIManager() const;
	UPrimaryGameLayout* GetRootLayout() const;
	UMarketplacePolicy* GetMarketplacePolicy() const;

private:
	void NotifyPlayerAdded(UCustomLocalPlayer* LocalPlayer);
	void NotifyPlayerDestroyed(UCustomLocalPlayer* LocalPlayer);
	UActivatableWidget* PushWidget(TSoftClassPtr<UActivatableWidget> WidgetClassPtr, FGameplayTag LayerTag);

	friend class UGameUIManagerSubsystem;

private:
	UPROPERTY(EditAnywhere, Category = "Immutable")
	TSoftClassPtr<UPrimaryGameLayout> LayoutClass;

	UPROPERTY(EditAnywhere, Category = "Immutable")
	TSoftClassPtr<UActivatableWidget> LoginScreenWidgetClass;
	
	UPROPERTY(EditAnywhere, Category = "Immutable")
    TSoftClassPtr<UActivatableWidget> FrontEndWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Marketplace")
	TSoftClassPtr<UMarketplacePolicy> MarketplacePolicyClass;
	
	UPROPERTY(Transient)
	UPrimaryGameLayout* RootLayout = nullptr;

	UPROPERTY(Transient)
	UMarketplacePolicy* MarketplacePolicy = nullptr;
};
