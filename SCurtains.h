// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "TestHud.h"

/**
 * 
 */
class SCurtains : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCurtains) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class ATestHud>, OwningHUD)

	SLATE_ARGUMENT(UMaterial*, curtains_VMUI)

	SLATE_ARGUMENT(UAudioComponent*, curtainOpeningAudioComponent)

	SLATE_ARGUMENT(int, x)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

	TWeakObjectPtr<class ATestHud> OwningHUD;

	UAudioComponent* curtainOpeningAudioComponent;

	UMaterial* curtains_VMUI;
	FSlateBrush* curtains_SB;

	TSharedPtr<class SOverlay> curtainOverlay;

	int x;

	float timeToLoadStage;
	bool canLoad;
	bool canPlaySoundEffect;
};
