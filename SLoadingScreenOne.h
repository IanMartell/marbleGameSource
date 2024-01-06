// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "TestHud.h"
#include "Kismet/KismetSystemLibrary.h"

/**
 * 
 */
class SLoadingScreenOne : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLoadingScreenOne) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class ATestHud>, OwningHUD)

	SLATE_ARGUMENT(APlayerController*, playerOnePlayerController)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	
	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

	FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);

	virtual bool IsInteractable() const override { return true; };
	virtual bool SupportsKeyboardFocus() const override { return true; };

	TWeakObjectPtr<class ATestHud> OwningHUD;

	APlayerController* playerOnePlayerController;

	FVector2D viewportSize;
	FVector2D adjustedViewportSize;
	float DPIScale;
	int deleteMe;
};
