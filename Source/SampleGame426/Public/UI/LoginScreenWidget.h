#pragma once

#include "ActivatableWidget.h"

#include "LoginScreenWidget.generated.h"


UCLASS(Abstract)
class SAMPLEGAME426_API ULoginScreenWidget : public UActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnActivated() override;

private:
	void OnPassportLoggedIn(bool IsLoggedIn);

};