#pragma once

#include "PrimaryGameLayout.h"

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

public:
	virtual UWorld* GetWorld() const override;
	class UGameUIManagerSubsystem* GetOwningUIManager() const;
	UPrimaryGameLayout* GetRootLayout() const;

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
	
	UPROPERTY(Transient)
	UPrimaryGameLayout* RootLayout = nullptr;

	UPROPERTY(Transient)
	UActivatableWidget* LoginScreenWidget = nullptr;
};
