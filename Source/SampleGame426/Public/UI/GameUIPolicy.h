#pragma once

#include "LoginScreenWidget.h"
#include "PrimaryGameLayout.h"
#include "Dialog/DialogTypeDataAsset.h"
#include "Marketplace/MarketplacePolicy.h"

#include "GameUIPolicy.generated.h"

class UGameUIManagerSubsystem;
class UCustomLocalPlayer;

UCLASS(Abstract, Blueprintable, Within = "GameUIManagerSubsystem")
class UGameUIPolicy : public UObject
{
	GENERATED_BODY()

	friend UGameUIManagerSubsystem;

public:
	static UGameUIPolicy* GetGameUIPolicy(const UObject* WorldContextObject);

	template <typename GameUIPolicyClass = UGameUIPolicy>
	static GameUIPolicyClass* GetGameUIPolicyAs(const UObject* WorldContextObject);

public:
	/** UWorld: Interface Begin */
	virtual UWorld* GetWorld() const override;
	/** UWorld: Interface End */

	UGameUIManagerSubsystem* GetOwningUIManager() const;
	UPrimaryGameLayout* GetRootLayout() const;
	UMarketplacePolicy* GetMarketplacePolicy() const;
	const FDialogType* GetDialogType(FGameplayTag DialogTag) const;

	void ShowThrobber();
	void HideThrobber();

private:
	void NotifyPlayerAdded(UCustomLocalPlayer* LocalPlayer);
	void NotifyPlayerDestroyed(UCustomLocalPlayer* LocalPlayer);

	UActivatableWidget* PushWidget(TSoftClassPtr<UActivatableWidget> WidgetClassPtr, FGameplayTag LayerTag);

private:
	UPROPERTY(EditAnywhere, Category = "Main")
	TSoftClassPtr<UPrimaryGameLayout> LayoutClass;

	UPROPERTY(EditAnywhere, Category = "Main")
	TSoftClassPtr<ULoginScreenWidget> LoginScreenWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Main")
	TSoftClassPtr<UActivatableWidget> ThrobberScreenWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Dialog")
	TSoftObjectPtr<UDialogTypeDataAsset> DialogTypeDataAsset;

	UPROPERTY(EditAnywhere, Category = "Marketplace")
	TSoftClassPtr<UMarketplacePolicy> MarketplacePolicyClass;

	UPROPERTY(Transient)
	UPrimaryGameLayout* RootLayout = nullptr;

	UPROPERTY(Transient)
	UMarketplacePolicy* MarketplacePolicy = nullptr;

	UPROPERTY(Transient)
	ULoginScreenWidget* LoginScreenWidget = nullptr;

	UPROPERTY(Transient)
	UActivatableWidget* ThrobberScreenWidget = nullptr;
};

template <typename GameUIPolicyClass>
GameUIPolicyClass* UGameUIPolicy::GetGameUIPolicyAs(const UObject* WorldContextObject)
{
	return Cast<GameUIPolicyClass>(GetGameUIPolicy(WorldContextObject));
}