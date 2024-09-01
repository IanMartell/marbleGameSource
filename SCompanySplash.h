// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "TestHud.h"

/**
 * 
 */
class MARBLEGAMEBLUEPRINT_API SCompanySplash : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCompanySplash) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class ATestHud>, OwningHUD)

	SLATE_ARGUMENT(UMaterial*, goodUseSplashBootNoGrass_SMUI)

	SLATE_ARGUMENT(UMaterial*, goodUseSplashGrass_SMUI)

	SLATE_ARGUMENT(UMaterial*, goodUseDigitalText_SMUI)

	SLATE_ARGUMENT(TArray <UMaterial*>, splashGrassArr)

	SLATE_ARGUMENT(TArray <UMaterial*>, splashBootArr)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void Released();
	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);
	FMargin CalculateSplashMarginOne();
	FMargin CalculateSplashMarginTwo();
	FMargin CalculateStartingTextMargin();

	TWeakObjectPtr<class ATestHud> OwningHUD;

	UMaterial* goodUseSplashBootNoGrass_SMUI;
	UMaterial* goodUseSplashGrass_SMUI;
	UMaterial* goodUseDigitalText_SMUI;
	TArray <UMaterial*> splashGrassArr;
	TArray <UMaterial*> splashBootArr;

	UPROPERTY() TArray <FSlateBrush*> splashBootSBArr;
	UPROPERTY() TArray <FSlateBrush*> splashGrassSBArr;
	FSlateBrush* goodUseDigitalText_SB;

	FVector2D viewportSize;
	UPROPERTY() FVector2D adjustedViewportSize;
	float DPIScale;

	TSharedPtr< class SOverlay> splashScreenOverlay;
	TSharedPtr<class SBox>  imageBoxOne;
	TSharedPtr<class SImage>  imageOne;
	TSharedPtr<class SBox>  textBox;

	FButtonStyle* masterButtonStyle;

	double timer;
	int trackerOne;
	int trackerTwo;
	int intOne;
	int intTwo;
	FMargin startingTextMargin;
	float adjustedMarginFloat;
	double shiftingMargin;
};
