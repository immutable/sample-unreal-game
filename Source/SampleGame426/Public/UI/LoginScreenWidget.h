﻿#pragma once

#include "Base/ActivatableWidget.h"
// #include "UI/Interfaces/IPassportListnerInterface.h"

#include "LoginScreenWidget.generated.h"


UCLASS(Abstract)
class SAMPLEGAME426_API ULoginScreenWidget : public UActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnActivated() override;

};