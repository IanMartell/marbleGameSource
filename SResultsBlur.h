// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Layout/SBackgroundBlur.h"
#include "SaveGameOne.h"
#include "TestHud.h"

/**
 * 
 */
class SResultsBlur : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SResultsBlur) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class ATestHud>, OwningHUD)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void Pressed();
	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);
	FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);
	FMargin CalculateHighscorePos(int textIndex, int numberOfLetters);

	TWeakObjectPtr<class ATestHud> OwningHUD;
	USaveGameOne* currentSave;

	TSharedPtr< class SOverlay> resultsOverlay;
	TSharedPtr<class STextBlock> resultsTextOne;
	TSharedPtr<class STextBlock> resultsTextTwo;
	TSharedPtr<class STextBlock> resultsTextThree;
	TSharedPtr<class STextBlock> resultsTextFour;
	TSharedPtr<class STextBlock> resultsTextFive;
	FSlateFontInfo scoreFont;
	FSlateFontInfo titleFont;
	TSharedPtr<class SBackgroundBlur> blur;
	
	float standardOpacity;

	FVector2D viewportSize;
	FVector2D adjustedViewportSize;
	float DPIScale;

	bool destroySelf;

	float timer;
	float standardBlur;

	FButtonStyle* masterButtonStyle;
};
