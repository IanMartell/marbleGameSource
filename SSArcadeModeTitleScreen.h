// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "TestHud.h"

/**
 * 
 */
class SSArcadeModeTitleScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLoadingScreenOne) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class ATestHud>, OwningHUD)

	SLATE_ARGUMENT(APlayerController*, playerOnePlayerController)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
    
    TWeakObjectPtr<class ATestHud> OwningHUD;

	APlayerController* playerOnePlayerController;
    
    FVector2D viewportSize;
	FVector2D adjustedViewportSize;
};
