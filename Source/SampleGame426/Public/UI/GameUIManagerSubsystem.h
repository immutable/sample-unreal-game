#pragma once

#include "Subsystems/GameInstanceSubsystem.h"

#include "UI/GameUIPolicy.h"

#include "GameUIManagerSubsystem.generated.h"

UCLASS(config = "Game")
class UGameUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Immutable")
	static UActivatableWidget* PushWidgetToLayer(const ULocalPlayer* LocalPlayer, UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerName, UPARAM(meta = (AllowAbstract = false)) TSubclassOf<UActivatableWidget> WidgetClass);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Immutable")
	static void PopWidgetFromLayer(UActivatableWidget* ActivatableWidget);

public:
	/** USubsystem: Interface Begin */
	virtual void Deinitialize() override;
	/** USubsystem: Interface End */

	const UGameUIPolicy* GetCurrentUIPolicy() const;
	UGameUIPolicy* GetCurrentUIPolicy();
	const TSoftClassPtr<UGameUIPolicy>& GetDefaultUIPolicyClass() const;

	virtual void NotifyPlayerAdded(ULocalPlayer* LocalPlayer);
	virtual void NotifyPlayerDestroyed(ULocalPlayer* LocalPlayer);

	void SwitchToPolicy(TSubclassOf<UGameUIPolicy> PolicyClass);

protected:
	void SwitchToPolicy(UGameUIPolicy* InPolicy);

protected:
	FSimpleMulticastDelegate OnPolicyChanged;

private:
	UPROPERTY(Transient)
	UGameUIPolicy* CurrentPolicy = nullptr;

	UPROPERTY(config, EditAnywhere)
	TSoftClassPtr<UGameUIPolicy> DefaultUIPolicyClass;
};