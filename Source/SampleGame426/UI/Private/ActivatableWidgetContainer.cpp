
#include "ActivatableWidgetContainer.h"
#include "Widgets/SOverlay.h"
#include "Widgets/Layout/SSpacer.h"
#include "Stats/Stats.h"
#include "TimerManager.h"
#include "Containers/Ticker.h"
#include "ActivatableWidget.h"
#include "SAnimatedSwitcher.h"


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

UActivatableWidgetContainer::UActivatableWidgetContainer(const FObjectInitializer& Initializer)
	: Super(Initializer)
	, GeneratedWidgetsPool(*this)
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UActivatableWidgetContainer::AddWidgetInstance(UActivatableWidget& ActivatableWidget)
{
	RegisterInstanceInternal(ActivatableWidget);
}

UActivatableWidget* UActivatableWidgetContainer::GetActiveWidget() const
{
	return MySwitcher ? ActivatableWidgetFromSlate(MySwitcher->GetActiveWidget()) : nullptr;
}

int32 UActivatableWidgetContainer::GetNumWidgets() const
{
	return WidgetList.Num();
}

void UActivatableWidgetContainer::RemoveWidget(UActivatableWidget* WidgetToRemove)
{
	if (WidgetToRemove)
	{
		RemoveWidget(*WidgetToRemove);
	}
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
		else
		{
			bRemoveDisplayedWidgetPostTransition = true;
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

void UActivatableWidgetContainer::ClearWidgets()
{
	SetSwitcherIndex(0);
}

TSharedRef<SWidget> UActivatableWidgetContainer::RebuildWidget()
{
	MyOverlay = SNew(SOverlay)
		+ SOverlay::Slot()
		[
			SAssignNew(MySwitcher, SAnimatedSwitcher)
		]
		+ SOverlay::Slot()
		[
			SAssignNew(MyInputGuard, SSpacer)
			.Visibility(EVisibility::Collapsed)
		];

	// We always want a 0th slot to be able to animate the first real entry in and out
	MySwitcher->AddSlot() [SNullWidget::NullWidget];
	
	if (WidgetList.Num() > 0)
	{
		//@todo DanH: We gotta fill up the switcher and activate the right thing. Alternatively we could just flush all the children upon destruction... I think I like that more.
	}

	return MyOverlay.ToSharedRef();
}

void UActivatableWidgetContainer::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyOverlay.Reset();
	MyInputGuard.Reset();
	MySwitcher.Reset();
	ReleasedWidgets.Empty();

	GeneratedWidgetsPool.ReleaseAllSlateResources();
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

void UActivatableWidgetContainer::SetSwitcherIndex(int32 TargetIndex)
{
	if (MySwitcher && MySwitcher->GetActiveWidgetIndex() != TargetIndex)
	{
		if (DisplayedWidget)
		{
			if (DisplayedWidget->IsActivated())
			{
				DisplayedWidget->DeactivateWidget();
			}
			else if (MySwitcher->GetActiveWidgetIndex() != 0)
			{
				// The displayed widget has already been deactivated by something other than us, so it should be removed from the container
				// We still need it to remain briefly though until we transition to the new index - then we can remove this entry's slot
				bRemoveDisplayedWidgetPostTransition = true;
			}
		}

		MySwitcher->SetActiveWidgetIndex(TargetIndex);
	}
}

UActivatableWidget* UActivatableWidgetContainer::BP_AddWidget(TSubclassOf<UActivatableWidget> ActivatableWidgetClass)
{
	return AddWidgetInternal(ActivatableWidgetClass, [](UActivatableWidget&) {});
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
	//@todo DanH: We should do something here to force-disable the bAutoActivate property on the provided widget, since it quite simply makes no sense
	if (ensure(!WidgetList.Contains(&NewWidget)))
	{
		WidgetList.Add(&NewWidget);
		OnWidgetAddedToList(NewWidget);
	}
}

void UActivatableWidgetContainer::HandleSwitcherIsTransitioningChanged(bool bIsTransitioning)
{
	// While the switcher is transitioning, put up the guard to intercept all input
	MyInputGuard->SetVisibility(bIsTransitioning ? EVisibility::Visible : EVisibility::Collapsed);
	OnTransitioningChanged.Broadcast(this, bIsTransitioning);
}

void UActivatableWidgetContainer::HandleActiveWidgetDeactivated(UActivatableWidget* DeactivatedWidget)
{
	// When the currently displayed widget deactivates, transition the switcher to the preceding slot (if it exists)
	// We'll clean up this slot once the switcher index actually changes
	if (ensure(DeactivatedWidget == DisplayedWidget) && MySwitcher && MySwitcher->GetActiveWidgetIndex() > 0)
	{
		MySwitcher->SetActiveWidgetIndex(MySwitcher->GetActiveWidgetIndex() - 1);
	}
}

void UActivatableWidgetContainer::ReleaseWidget(const TSharedRef<SWidget>& WidgetToRelease)
{
	if (UActivatableWidget* ActivatableWidget = ActivatableWidgetFromSlate(WidgetToRelease))
	{
		GeneratedWidgetsPool.Release(ActivatableWidget, true);
		WidgetList.Remove(ActivatableWidget);
	}

	if (MySwitcher->RemoveSlot(WidgetToRelease) != INDEX_NONE)
	{
		ReleasedWidgets.Add(WidgetToRelease);
		if (ReleasedWidgets.Num() == 1)
		{
			FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateWeakLambda(this,
				[this](float)
				{
					QUICK_SCOPE_CYCLE_COUNTER(STAT_UActivatableWidgetContainer_ReleaseWidget);
					ReleasedWidgets.Reset();
					return false;
				}));
		}
	}
}

void UActivatableWidgetContainer::HandleActiveIndexChanged(int32 ActiveWidgetIndex)
{
	// Remove all slots above the currently active one and release the widgets back to the pool
	while (MySwitcher->GetNumWidgets() - 1 > ActiveWidgetIndex)
	{
		TSharedPtr<SWidget> WidgetToRelease = MySwitcher->GetWidget(MySwitcher->GetNumWidgets() - 1);
		if (ensure(WidgetToRelease))
		{
			ReleaseWidget(WidgetToRelease.ToSharedRef());
		}
	}

	// Also remove the widget that we just transitioned away from if desired
	if (DisplayedWidget && bRemoveDisplayedWidgetPostTransition)
	{
		if (TSharedPtr<SWidget> DisplayedSlateWidget = DisplayedWidget->GetCachedWidget())
		{
			ReleaseWidget(DisplayedSlateWidget.ToSharedRef());
		}
	}
	bRemoveDisplayedWidgetPostTransition = false;

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

//////////////////////////////////////////////////////////////////////////
// UActivatableWidgetStack
//////////////////////////////////////////////////////////////////////////

UActivatableWidget* UActivatableWidgetStack::GetRootContent() const
{
	return RootContentWidget;
}

void UActivatableWidgetStack::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	
#if WITH_EDITOR
	if (IsDesignTime() && RootContentWidget && RootContentWidget->GetClass() != RootContentWidgetClass)
	{
		// At design time, account for the possibility of the preview class changing
		if (RootContentWidget->GetCachedWidget())
		{
			MySwitcher->GetChildSlot(0)->DetachWidget();
		}

		RootContentWidget = nullptr;
	}
#endif

	if (!RootContentWidget && RootContentWidgetClass)
	{
		// Establish the root content as the blank 0th slot content
		RootContentWidget = CreateWidget<UActivatableWidget>(this, RootContentWidgetClass);
		MySwitcher->GetChildSlot(0)->AttachWidget(RootContentWidget->TakeWidget());
		
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UActivatableWidgetStack::OnWidgetAddedToList(UActivatableWidget& AddedWidget)
{
	if (MySwitcher)
	{
		//@todo DanH: Rig up something to skip to an index immediately but still play the intro portion of the transition on the new index
		//		Might be as simple as changing the properties to separate intro and outro durations?
		//		Eh, but even in this case we only want to skip when we're going from an empty 0th entry. Every other transition should still do the full fade.

		// Toss the widget onto the end of the switcher's children and transition to it immediately
		MySwitcher->AddSlot() [AddedWidget.TakeWidget()];

		SetSwitcherIndex(MySwitcher->GetNumWidgets() - 1);
	}
}
