#include "Base/ActivatableWidgetContainer.h"

#include "Containers/Ticker.h"
#include "Stats/Stats.h"
#include "TimerManager.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/SOverlay.h"

#include "Base/ActivatableWidget.h"

#define LOCTEXT_NAMESPACE "ImmutableUI"

UActivatableWidget* ActivatableWidgetFromSlate(const TSharedPtr<SWidget>& SlateWidget)
{
	if (SlateWidget && SlateWidget != SNullWidget::NullWidget && ensure(SlateWidget->GetType().IsEqual(TEXT("SObjectWidget"))))
	{
		UActivatableWidget* ActivatableWidget = Cast<UActivatableWidget>(StaticCastSharedPtr<SObjectWidget>(SlateWidget)->GetWidgetObject());
		if (ensure(ActivatableWidget))
		{
			return ActivatableWidget;
		}
	}
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
// UActivatableWidgetContainer
//////////////////////////////////////////////////////////////////////////

UActivatableWidgetContainer::UActivatableWidgetContainer(const FObjectInitializer& Initializer) :
	Super(Initializer),
	GeneratedWidgetsPool(*this)
{
	SetVisibility(ESlateVisibility::Collapsed);
}

#if WITH_EDITOR
const FText UActivatableWidgetContainer::GetPaletteCategory()
{
	return LOCTEXT("SAMPLEGAME426_UI", "Immutable");
}
#endif

int32 UActivatableWidgetContainer::GetNumWidgets() const
{
	return WidgetList.Num();
}

const TArray<UActivatableWidget*>& UActivatableWidgetContainer::GetWidgetList() const
{
	return WidgetList;
}

UActivatableWidget* UActivatableWidgetContainer::GetActiveWidget() const
{
	return MySwitcher ? ActivatableWidgetFromSlate(MySwitcher->GetActiveWidget()) : nullptr;
}

UActivatableWidgetContainer::FOnDisplayedWidgetChanged& UActivatableWidgetContainer::OnDisplayedWidgetChanged()
{
	return OnDisplayedWidgetChangedEvent;
}

UActivatableWidgetContainer::FTransitioningChanged& UActivatableWidgetContainer::OnTransitioningChanged()
{
	return OnTransitioningChangedEvent;
}

void UActivatableWidgetContainer::AddWidgetInstance(UActivatableWidget& ActivatableWidget)
{
	RegisterInstanceInternal(ActivatableWidget);
}

void UActivatableWidgetContainer::RemoveWidget(UActivatableWidget* WidgetToRemove)
{
	if (WidgetToRemove)
	{
		RemoveWidget(*WidgetToRemove);
	}
}

void UActivatableWidgetContainer::ClearWidgets()
{
	SetSwitcherIndex(0);
}

void UActivatableWidgetContainer::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyOverlay.Reset();
	MySwitcher.Reset();
	ReleasedWidgets.Empty();

	GeneratedWidgetsPool.ReleaseAllSlateResources();
}

TSharedRef<SWidget> UActivatableWidgetContainer::RebuildWidget()
{
	MyOverlay = SNew(SOverlay)
	+ SOverlay::Slot()
	[
		SAssignNew(MySwitcher, SAnimatedSwitcher)
		.TransitionCurveType(TransitionCurveType)
		.TransitionDuration(TransitionDuration)
		.TransitionType(TransitionType)
		.OnActiveIndexChanged_UObject(this, &UActivatableWidgetContainer::HandleActiveIndexChanged)
		.OnIsTransitioningChanged_UObject(this, &UActivatableWidgetContainer::HandleSwitcherIsTransitioningChanged)
	];

	// We always want a 0th slot to be able to animate the first real entry in and out
	MySwitcher->AddSlot()[SNullWidget::NullWidget];

	return MyOverlay.ToSharedRef();
}

void UActivatableWidgetContainer::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (!IsDesignTime())
	{
		// When initially created, fake that we just did an initial transition to index 0
		HandleActiveIndexChanged(0);
	}
}

void UActivatableWidgetContainer::OnWidgetAddedToList(UActivatableWidget& AddedWidget)
{
	unimplemented();
}

void UActivatableWidgetContainer::SetSwitcherActiveWidget(UActivatableWidget& AddedWidget, bool bInstantTransition)
{
	TSharedPtr<SWidget> SlateWidget = AddedWidget.GetCachedWidget();

	if (MySwitcher && SlateWidget)
	{
		// if (DisplayedWidget && DisplayedWidget->IsActivated())
		// {
		// 	DisplayedWidget->DeactivateWidget();
		// }

		//AddedWidget.ActivateWidget();
		int32 WidgetIndex = MySwitcher->GetWidgetIndex(SlateWidget.ToSharedRef());

		if (WidgetIndex != INDEX_NONE)
		{
			//MySwitcher->SetActiveWidget(SlateWidget.ToSharedRef());
			SetSwitcherIndex(WidgetIndex);
		}
	}
}

void UActivatableWidgetContainer::SetSwitcherIndex(int32 TargetIndex, bool bInstantTransition /*= false*/)
{
	if (MySwitcher && MySwitcher->GetActiveWidgetIndex() != TargetIndex)
	{
		if (DisplayedWidget)
		{
			if (DisplayedWidget->IsActivated())
			{
				DisplayedWidget->DeactivateWidget();
			}
		}

		MySwitcher->TransitionToIndex(TargetIndex, bInstantTransition);
	}
}

UActivatableWidget* UActivatableWidgetContainer::BP_AddWidget(TSubclassOf<UActivatableWidget> ActivatableWidgetClass)
{
	return AddWidgetInternal(ActivatableWidgetClass, [](UActivatableWidget&)
	{
	});
}

void UActivatableWidgetContainer::RemoveWidget(UActivatableWidget& WidgetToRemove)
{
	if (&WidgetToRemove == GetActiveWidget())
	{
		// To remove the active widget, just deactivate it (if it's already deactivated, then we're already in the process of ditching it)
		if (WidgetToRemove.IsActivated())
		{
			WidgetToRemove.DeactivateWidget();
		}
	}
	else
	{
		// Otherwise if the widget isn't actually being shown right now, yank it right on out
		TSharedPtr<SWidget> CachedWidget = WidgetToRemove.GetCachedWidget();
		if (CachedWidget && MySwitcher)
		{
			ReleaseWidget(CachedWidget.ToSharedRef());
		}
	}
}

UActivatableWidget* UActivatableWidgetContainer::AddWidgetInternal(TSubclassOf<UActivatableWidget> ActivatableWidgetClass, TFunctionRef<void(UActivatableWidget&)> InitFunc)
{
	if (UActivatableWidget* WidgetInstance = GeneratedWidgetsPool.GetOrCreateInstance(ActivatableWidgetClass))
	{
		InitFunc(*WidgetInstance);
		RegisterInstanceInternal(*WidgetInstance);
		return WidgetInstance;
	}
	return nullptr;
}

void UActivatableWidgetContainer::RegisterInstanceInternal(UActivatableWidget& NewWidget)
{
	if (ensure(!WidgetList.Contains(&NewWidget)))
	{
		WidgetList.Add(&NewWidget);
		OnWidgetAddedToList(NewWidget);
	}
}

void UActivatableWidgetContainer::HandleSwitcherIsTransitioningChanged(bool bIsTransitioning)
{
	OnTransitioningChangedEvent.Broadcast(this, bIsTransitioning);
}

void UActivatableWidgetContainer::HandleActiveIndexChanged(int32 ActiveWidgetIndex)
{
	// Remove all slots above the currently active one and release the widgets back to the pool
	// while (MySwitcher->GetNumWidgets() - 1 > ActiveWidgetIndex)
	// {
	// 	TSharedPtr<SWidget> WidgetToRelease = MySwitcher->GetWidget(MySwitcher->GetNumWidgets() - 1);
	// 	if (ensure(WidgetToRelease))
	// 	{
	// 		ReleaseWidget(WidgetToRelease.ToSharedRef());
	// 	}
	// }

	for (int32 i = 0; i < MySwitcher->GetNumWidgets(); ++i)
	{
		TSharedPtr<SWidget> WidgetToRelease = MySwitcher->GetWidget(i);

		if (ensure(WidgetToRelease))
		{
			ReleaseWidget(WidgetToRelease.ToSharedRef());
		}
	}

	// Also remove the widget that we just transitioned away from if desired
	if (DisplayedWidget && DisplayedWidget->CanBeReleased())
	{
		if (TSharedPtr<SWidget> DisplayedSlateWidget = DisplayedWidget->GetCachedWidget())
		{
			ReleaseWidget(DisplayedSlateWidget.ToSharedRef());
		}
	}

	// Activate the widget that's now being displayed
	DisplayedWidget = ActivatableWidgetFromSlate(MySwitcher->GetActiveWidget());
	if (DisplayedWidget)
	{
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		DisplayedWidget->ActivateWidget();

		if (UWorld* MyWorld = GetWorld())
		{
			FTimerManager& TimerManager = MyWorld->GetTimerManager();
			TimerManager.SetTimerForNextTick(FSimpleDelegate::CreateWeakLambda(this, [this]() { InvalidateLayoutAndVolatility(); }));
		}
	}
	else
	{
		SetVisibility(ESlateVisibility::Collapsed);
	}

	OnDisplayedWidgetChanged().Broadcast(DisplayedWidget);
}

void UActivatableWidgetContainer::HandleActiveWidgetDeactivated(UActivatableWidget* DeactivatedWidget)
{
	// When the currently displayed widget deactivates, transition the switcher to the preceding slot (if it exists)
	// We'll clean up this slot once the switcher index actually changes
	if (ensure(DeactivatedWidget == DisplayedWidget) && MySwitcher && MySwitcher->GetActiveWidgetIndex() > 0)
	{
		DisplayedWidget->OnDeactivated().RemoveAll(this);
		MySwitcher->TransitionToIndex(MySwitcher->GetActiveWidgetIndex() - 1);
	}
}

void UActivatableWidgetContainer::ReleaseWidget(const TSharedRef<SWidget>& WidgetToRelease)
{
	UActivatableWidget* ActivatableWidget = ActivatableWidgetFromSlate(WidgetToRelease);

	if (!ActivatableWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("ActivatableWidget %s is null"), *WidgetToRelease->GetTag().ToString());
		return;
	}

	if (!ActivatableWidget->CanBeReleased())
	{
		return;
	}

	GeneratedWidgetsPool.Release(ActivatableWidget, true);
	WidgetList.Remove(ActivatableWidget);

	if (MySwitcher->RemoveSlot(WidgetToRelease) != INDEX_NONE)
	{
		ReleasedWidgets.Add(WidgetToRelease);
		if (ReleasedWidgets.Num() == 1)
		{
#if UE_5_3_OR_LATER
			FTSTicker::
#else
			FTicker::
#endif
				GetCoreTicker().AddTicker(FTickerDelegate::CreateWeakLambda(this, [this](float)
				{
					QUICK_SCOPE_CYCLE_COUNTER(STAT_UActivatableWidgetContainer_ReleaseWidget);
					ReleasedWidgets.Reset();
					return false;
				}));
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// UActivatableWidgetStack
//////////////////////////////////////////////////////////////////////////

void UActivatableWidgetStack::OnWidgetAddedToList(UActivatableWidget& AddedWidget)
{
	if (MySwitcher)
	{
		//@todo DanH: Rig up something to skip to an index immediately but still play the intro portion of the transition on the new index
		//		Might be as simple as changing the properties to separate intro and outro durations?
		//		Eh, but even in this case we only want to skip when we're going from an empty 0th entry. Every other transition should still do the full fade.

		// Toss the widget onto the end of the switcher's children and transition to it immediately
		MySwitcher->AddSlot()[AddedWidget.TakeWidget()];
		SetSwitcherIndex(MySwitcher->GetNumWidgets() - 1);
	}
}

#undef LOCTEXT_NAMESPACE