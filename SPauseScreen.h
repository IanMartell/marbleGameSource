// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyHUD.h"
#include "SaveGameOne.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SPauseScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPauseScreen) {}

		SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwningHUD)

		SLATE_ARGUMENT(TArray<UAudioComponent*>, hoverGrowAudioComponents)

		SLATE_ARGUMENT(TArray<UAudioComponent*>, hoverShrinkAudioComponents)

		SLATE_ARGUMENT(TArray <UAudioComponent*>, purpleLullabyAudioComponents)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

	FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);

	void OnResumePressed();
	void OnResumeReleased();
	void OnResumeHovered();
	void OnResumeUnHovered();

	void OnRestartPressed();
	void OnRestartReleased();
	void OnRestartHovered();
	void OnRestartUnHovered();

	void OnOptionsPressed();
	void OnOptionsReleased();
	void OnOptionsHovered();
	void OnOptionsUnHovered();

	void OnQuitToMenuPressed();
	void OnQuitToMenuReleased();
	void OnQuitToMenuHovered();
	void OnQuitToMenuUnHovered();

	FMargin CalculateTitlePosition(FVector2D funcViewportSize);
	FMargin CalculateMenuTextPos(int textIndex, int numberOfLetters);
	float CalculateGrownMarginX(FMargin inMargin);
	float CalculateGrownMarginY(FMargin inMargin);
	FMargin GrowMargin(FMargin inMargin);
	FMargin GrownMargin(FMargin inMargin);
	FMargin ShrinkMargin(FMargin inMargin, int marginIndex);
	void PlayChordToActiveNote();
	void ReturnToLanding();

	TWeakObjectPtr<class AMyHUD> OwningHUD;
	USaveGameOne* currentSave;

	TSharedPtr< class SOverlay> masterOverlay;
	TSharedPtr< class SOverlay> mainPauseOverlay;
	TSharedPtr<class SBackgroundBlur> blur;

	TSharedPtr<class SBox> resumeBox;
	TSharedPtr<class SBox> restartBox;
	TSharedPtr<class SBox> optionsBox;
	TSharedPtr<class SBox> quitToMenuBox;

	TSharedPtr<class STextBlock> titleTextBlock;
	TSharedPtr<class STextBlock> resumeText;
	TSharedPtr<class STextBlock> restartText;
	TSharedPtr<class STextBlock> optionsText;
	TSharedPtr<class STextBlock> quitToMenuText;

	FSlateFontInfo titleFont;
	FSlateFontInfo subTitleFont;
	FSlateFontInfo menuFont;
	FText titleText;

	FButtonStyle* transparentButtonStyle;

	FLinearColor textColor;
	FLinearColor shadowColor;

	FMargin resumeMargin;
	FMargin restartMargin;
	FMargin optionsMargin;
	FMargin quitToMenuMargin;

	FVector2D viewportSize;
	FVector2D adjustedViewportSize;
	float DPIScale;

	float standardOpacity;
	float standardBlur;
	float clock;
	float deathClock;

	bool destroyPauseScreen;
	bool spawnPauseScreen;

	bool clicked;

	float grownOpacity;
	float multiplierOfOffset;
	float multiplierOfPerimeterExpansion;
	TArray<TSharedPtr<class SBox>> shrinkingBoxes;
	TArray<TSharedPtr<class STextBlock>> shrinkingTextBlocks;
	TArray<FSlateFontInfo> shrinkingTexts;
	TArray<float> shrinkingTimes;
	TArray<FMargin> shrinkingMargins;
	TArray<FMargin> shrinkingMarginsStartingPoints;
	TArray<float> shrinkingAdjustedMarginSizesX;
	TArray<float> shrinkingAdjustedMarginSizesY;
	TArray<float> shrinkingFontSizes;
	TArray<float> shrinkingFontSizesStartingPoints;
	TArray<float> shrinkingAdjustedFontSizes;
	TArray<TSharedPtr<class SBox>> grownBox;
	TArray<float> shrinkTargets;
	TArray<TSharedPtr<class SBox>> growingBox;
	FSlateFontInfo growingFont;
	TSharedPtr<class STextBlock> growingTextBlock;
	FMargin growingMargin;
	float growingFontSize;
	float startingFontSize;
	FMargin startingMargin;
	float adjustedSizeX;
	float adjustedSizeY;
	float adjustedStartingFontSize;
	FMargin adjustedStartingFMargin;
	float growTime;
	float extentOfGrowth;
	int indexOfShrinkingSubject;
	float standardShadowOffset;
	float startingShadowOffset;
	float growingOffset;
	float adjustedGrowingOffset;
	TArray <float> shrinkingOffset;
	TArray <float> startingShrinkingOffset;
	TArray <float> adjustedShrinkingOffset;
	float startingOpacity;
	FLinearColor growingLinearColor;
	float growingOpacity;
	float adjustedGrowingOpacity;
	TArray<float> startingShrinkingOpacities;
	TArray<FLinearColor> shrinkingLinearColors;
	TArray<float> shrinkingOpacities;
	TArray<float> adjustedShrinkingOpacities;
	TArray<FMargin> completedMargins;
	TArray<FSlateFontInfo> completedFonts;
	TArray<float> completedOffsets;
	float newOpacity;

	int activeNoteIndex;
	TArray< TArray <int> > correspondingChordsToNotes = { { 0 }, { 1 }, { 0, 3}, { 1 }, { 0, 2, 3}, { 1 }, { 2, 3}, { 3 } };
	TArray< TArray <int> > chordIndexes = { { 0, 2, 4 }, { 1, 3, 5 }, { 2, 4, 6 }, { 4, 6, 7 } };

	UPROPERTY() TArray<UAudioComponent*> hoverGrowAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> hoverShrinkAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> purpleLullabyAudioComponents;

	TArray<int> childrensCornerNotes;
	int childrensCornerIndex;
};
