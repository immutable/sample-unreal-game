#pragma once

#include "PrimaryGameLayout.h"

#include "GameUIPolicy.generated.h"


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
	UPrimaryGameLayout* GetRootLayout(const ULocalPlayer* LocalPlayer) const;

protected:
	void CreateLayoutWidget(ULocalPlayer* LocalPlayer);
	
private:
	void NotifyPlayerAdded(ULocalPlayer* LocalPlayer);
	void NotifyPlayerDestroyed(ULocalPlayer* LocalPlayer);

	friend class UGameUIManagerSubsystem;

private:
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UPrimaryGameLayout> LayoutClass;

	UPROPERTY(Transient)
	UPrimaryGameLayout* RootLayout = nullptr;
};
