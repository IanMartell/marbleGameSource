// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestHud.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SOptions : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SOptions) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class ATestHud>, OwningHUD)

	SLATE_ARGUMENT(APlayerController*, playerOnePlayerController)

	SLATE_ARGUMENT(UObject*, standardWorldContextObject)

	SLATE_ARGUMENT(TArray<UAudioComponent*>, hoverGrowAudioComponents)

	SLATE_ARGUMENT(TArray<UAudioComponent*>, hoverShrinkAudioComponents)

	SLATE_ARGUMENT(TArray <UAudioComponent*>, purpleLullabyAudioComponents)

	SLATE_ARGUMENT(UMaterial*, gameFrameColor_SMUI)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

	void OnAudioPressed();
	void OnAudioReleased();
	void OnAudioHovered();
	void OnAudioUnHovered();

	void OnGraphicsPressed();
	void OnGraphicsReleased();
	void OnGraphicsHovered();
	void OnGraphicsUnHovered();

	void OnControlsPressed();
	void OnControlsReleased();
	void OnControlsHovered();
	void OnControlsUnHovered();

	void OnAccessabilityPressed();
	void OnAccessabilityReleased();
	void OnAccessabilityHovered();
	void OnAccessabilityUnHovered();

	void OnBackFloorOneReleased();
	void OnBackFloorOnePressed();
	void OnBackFloorOneHovered();
	void OnBackFloorOneUnHovered();

	void OnBackToMenuReleased();
	void OnBackToMenuPressed();
	void OnBackToMenuHovered();
	void OnBackToMenuUnHovered();

	void OnMasterCommitted(const FText& InText, const ETextCommit::Type InTextAction);
	void OnMusicCommitted(const FText& InText, const ETextCommit::Type InTextAction);
	void OnAtmosphereCommitted(const FText& InText, const ETextCommit::Type InTextAction);
	void OnSFXCommitted(const FText& InText, const ETextCommit::Type InTextAction);

	FMargin CalculateTitlePosition(FVector2D funcViewportSize);
	FMargin CalculateMenuTextPos(int textIndex, int numberOfLetters);
	FMargin GrowMargin(FMargin inMargin);
	FMargin GrownMargin(FMargin inMargin);
	FMargin ShrinkMargin(FMargin inMargin, int marginIndex);
	float CalculateGrownMarginX(FMargin inMargin);
	float CalculateGrownMarginY(FMargin inMargin);
	FMargin CalculateBackButtonPosition(FVector2D paramViewportSize);
	FMargin CalculateLeftColumnPos(int textIndex, int numberOfLetters);
	FMargin CalculateRightColumnPos(int textIndex, int numberOfLetters);
	void PlayChordToActiveNote();

	UPROPERTY() TWeakObjectPtr<class ATestHud> OwningHUD;
	UPROPERTY() APlayerController* playerOnePlayerController;
	UPROPERTY() UObject* standardWorldContextObject;
	UPROPERTY() USaveGameOne* currentSave;

	UPROPERTY() UMaterial* gameFrameColor_SMUI;

	UPROPERTY() FSlateBrush* gameFrameColor_SB;

	UPROPERTY() FVector2D viewportSize;
	UPROPERTY() FVector2D adjustedViewportSize;
	UPROPERTY() float DPIScale;

	UPROPERTY() TSharedPtr< class SOverlay> masterOverlay;
	UPROPERTY() TSharedPtr< class SOverlay> mainOptionsOverlay;
	UPROPERTY() TSharedPtr< class SOverlay> audioOverlay;

	UPROPERTY() TSharedPtr<class SBox> audioBox;
	UPROPERTY() TSharedPtr<class SBox> graphicsBox;
	UPROPERTY() TSharedPtr<class SBox> controlsBox;
	UPROPERTY() TSharedPtr<class SBox> accessabilityBox;
	UPROPERTY() TSharedPtr<class SBox> firstFloorBackBox;
	UPROPERTY() TSharedPtr<class SBox> toMenuBackBox;

	UPROPERTY() TSharedPtr<class SBox> masterTextBox;
	UPROPERTY() TSharedPtr<class SBox> musicTextBox;
	UPROPERTY() TSharedPtr<class SBox> atmosphereTextBox;
	UPROPERTY() TSharedPtr<class SBox> sfxTextBox;
	UPROPERTY() TSharedPtr<class SBox> masterInteractiveBox;
	UPROPERTY() TSharedPtr<class SBox> masterBackgroundBox;
	UPROPERTY() TSharedPtr<class SBox> musicInteractiveBox;
	UPROPERTY() TSharedPtr<class SBox> musicBackgroundBox;
	UPROPERTY() TSharedPtr<class SBox> atmosphereInteractiveBox;
	UPROPERTY() TSharedPtr<class SBox> atmosphereBackgroundBox;
	UPROPERTY() TSharedPtr<class SBox> sfxInteractiveBox;
	UPROPERTY() TSharedPtr<class SBox> sfxBackgroundBox;

	UPROPERTY() TSharedPtr<class SEditableText> masterEditableTextBox;
	UPROPERTY() TSharedPtr<class SEditableText> musicEditableTextBox;
	UPROPERTY() TSharedPtr<class SEditableText> atmosphereEditableTextBox;
	UPROPERTY() TSharedPtr<class SEditableText> sfxEditableTextBox;

	UPROPERTY() TSharedPtr<class STextBlock> audioText;
	UPROPERTY() TSharedPtr<class STextBlock> graphicsText;
	UPROPERTY() TSharedPtr<class STextBlock> controlsText;
	UPROPERTY() TSharedPtr<class STextBlock> accessabilityText;
	UPROPERTY() TSharedPtr<class STextBlock> backText;

	UPROPERTY() FSlateFontInfo titleFont;
	UPROPERTY() FSlateFontInfo subTitleFont;
	UPROPERTY() FSlateFontInfo menuFont;

	UPROPERTY() FMargin audioMargin;
	UPROPERTY() FMargin graphicsMargin;
	UPROPERTY() FMargin controlsMargin;
	UPROPERTY() FMargin accessabilityMargin;
	UPROPERTY() FMargin backMargin;

	UPROPERTY() FButtonStyle* transparentButtonStyle;


	UPROPERTY() TArray<FMargin> completedMargins;
	UPROPERTY() TArray<FSlateFontInfo> completedFonts;
	UPROPERTY() TArray<float> completedOffsets;
	UPROPERTY() float grownOpacity;
	UPROPERTY() float multiplierOfOffset;
	UPROPERTY() float multiplierOfPerimeterExpansion;
	UPROPERTY() bool clicked;
	UPROPERTY() TArray<TSharedPtr<class SBox>> shrinkingBoxes;
	UPROPERTY() TArray<TSharedPtr<class STextBlock>> shrinkingTextBlocks;
	UPROPERTY() TArray<FSlateFontInfo> shrinkingTexts;
	UPROPERTY() TArray<float> shrinkingTimes;
	UPROPERTY() TArray<FMargin> shrinkingMargins;
	UPROPERTY() TArray<FMargin> shrinkingMarginsStartingPoints;
	UPROPERTY() TArray<float> shrinkingAdjustedMarginSizesX;
	UPROPERTY() TArray<float> shrinkingAdjustedMarginSizesY;
	UPROPERTY() TArray<float> shrinkingFontSizes;
	UPROPERTY() TArray<float> shrinkingFontSizesStartingPoints;
	UPROPERTY() TArray<float> shrinkingAdjustedFontSizes;
	UPROPERTY() TArray<TSharedPtr<class SBox>> grownBox;
	UPROPERTY() TArray<float> shrinkTargets;
	UPROPERTY() TArray<TSharedPtr<class SBox>> growingBox;
	UPROPERTY() FSlateFontInfo growingFont;
	UPROPERTY() TSharedPtr<class STextBlock> growingTextBlock;
	UPROPERTY() FMargin growingMargin;
	UPROPERTY() float growingFontSize;
	UPROPERTY() float startingFontSize;
	UPROPERTY() FMargin startingMargin;
	UPROPERTY() float adjustedSizeX;
	UPROPERTY() float adjustedSizeY;
	UPROPERTY() float adjustedStartingFontSize;
	UPROPERTY() FMargin adjustedStartingFMargin;
	UPROPERTY() float growTime;
	UPROPERTY() float extentOfGrowth;
	UPROPERTY() int indexOfShrinkingSubject;
	UPROPERTY() float standardShadowOffset;
	UPROPERTY() float startingShadowOffset;
	UPROPERTY() float growingOffset;
	UPROPERTY() float adjustedGrowingOffset;
	UPROPERTY() TArray <float> shrinkingOffset;
	UPROPERTY() TArray <float> startingShrinkingOffset;
	UPROPERTY() TArray <float> adjustedShrinkingOffset;
	UPROPERTY() float standardOpacity;
	UPROPERTY() float startingOpacity;
	UPROPERTY() FLinearColor growingLinearColor;
	UPROPERTY() float growingOpacity;
	UPROPERTY() float adjustedGrowingOpacity;
	UPROPERTY() TArray<float> startingShrinkingOpacities;
	UPROPERTY() TArray<FLinearColor> shrinkingLinearColors;
	UPROPERTY() TArray<float> shrinkingOpacities;
	UPROPERTY() TArray<float> adjustedShrinkingOpacities;

	UPROPERTY() TArray<int> childrensCornerNotes;
	UPROPERTY() int childrensCornerIndex;

	UPROPERTY() float audioTimer;
	UPROPERTY() int audioCycleTracker;

	UPROPERTY() UAudioComponent* hoverGrowAudioComponent;
	UPROPERTY() UAudioComponent* hoverShrinkAudioComponent;

	UPROPERTY() TArray<UAudioComponent*> hoverGrowAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> hoverShrinkAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> purpleLullabyAudioComponents;

	UPROPERTY() int activeNoteIndex;
	TArray< TArray <int> > correspondingChordsToNotes = { { 0 }, { 1 }, { 0, 3}, { 1 }, { 0, 2, 3}, { 1 }, { 2, 3}, { 3 } };
	TArray< TArray <int> > chordIndexes = { { 0, 2, 4 }, { 1, 3, 5 }, { 2, 4, 6 }, { 4, 6, 7 } };

	bool makeSave;
};
