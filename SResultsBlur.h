// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveGameOne.h"
#include "MyHUD.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SResultsBlur : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SResultsBlur) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwningHUD)

	SLATE_ARGUMENT(UAudioComponent*, rainstickAudioComponent)

	SLATE_ARGUMENT(TArray <UAudioComponent*>, victoryAudioComponents)

	SLATE_ARGUMENT(bool, newMaxLevel)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void Released();
	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);
	FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);
	FMargin CalculateHighscorePos(int textIndex, int numberOfLetters);

	TWeakObjectPtr<class AMyHUD> OwningHUD;
	USaveGameOne* currentSave;

	UAudioComponent* rainstickAudioComponent;
	TArray <UAudioComponent*> victoryAudioComponents;

	TSharedPtr< class SOverlay> resultsOverlay;
	TSharedPtr<class STextBlock> resultsTextOne;
	TSharedPtr<class STextBlock> resultsTextTwo;
	TSharedPtr<class STextBlock> resultsTextThree;
	TSharedPtr<class STextBlock> resultsTextFour;
	TSharedPtr<class STextBlock> resultsTextFive;
	TSharedPtr<class STextBlock> resultsTextSix;
	FSlateFontInfo scoreFont;
	FSlateFontInfo titleFont;
	TSharedPtr<class SBackgroundBlur> blur;

	float standardOpacity;
	FLinearColor shrinkingOpacityWhite;
	FLinearColor shrinkingOpacityBlack;

	FVector2D viewportSize;
	FVector2D adjustedViewportSize;
	float DPIScale;

	bool destroySelf;
	bool newMaxLevel;

	float timer;
	float standardBlur;

	FButtonStyle* masterButtonStyle;
};
