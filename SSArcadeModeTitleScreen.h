
#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "TestHud.h"
#include "Components/AudioComponent.h"
#include "SaveGameOne.h"

/**
 *
 */
class SSArcadeModeTitleScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSArcadeModeTitleScreen) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class ATestHud>, OwningHUD)

	SLATE_ARGUMENT(UObject*, standardWorldContextObject)

	SLATE_ARGUMENT(TArray<UMaterial*>, backgroundMaterials)

	SLATE_ARGUMENT(bool, backgroundIsLargeTile)

	SLATE_ARGUMENT(bool, displayResults)

	SLATE_ARGUMENT(UMaterial*, gameFrameColor_SMUI)

	SLATE_ARGUMENT(USoundBase*, hoverGrow)

	SLATE_ARGUMENT(USoundBase*, hoverShrink)

	SLATE_ARGUMENT(TArray<UAudioComponent*>, hoverGrowAudioComponents)

	SLATE_ARGUMENT(TArray<UAudioComponent*>, hoverShrinkAudioComponents)

	SLATE_ARGUMENT(TArray <UAudioComponent*>, windAudioComponents)

	SLATE_ARGUMENT(TArray <UAudioComponent*>, windWithSheepAudioComponents)

	SLATE_ARGUMENT(TArray <UAudioComponent*>, riverAudioComponents)

	SLATE_ARGUMENT(TArray <UAudioComponent*>, waterfallAudioComponents)

	SLATE_ARGUMENT(TArray <UAudioComponent*>, purpleLullabyAudioComponents)

	SLATE_ARGUMENT(int, environmentAudio)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

	void OnPlayPressed();
	void OnPlayReleased();
	void OnPlayHovered();
	void OnPlayUnHovered();

	void OnResultsPressed();
	void OnResultsReleased();
	void OnResultsHovered();
	void OnResultsUnHovered();

	void OnOptionsPressed();
	void OnOptionsReleased();
	void OnOptionsHovered();
	void OnOptionsUnHovered();

	void OnQuitPressed();
	void OnQuitReleased();
	void OnQuitHovered();
	void OnQuitUnHovered();

	void OnBackFloorOneReleased();
	void OnBackFloorOnePressed();
	void OnBackFloorOneHovered();
	void OnBackFloorOneUnHovered();

	void PlayPressed_3();
	void PlayPressed_4();
	void PlayPressed_5();
	void PlayPressed_6();
	void PlayPressed_7();
	void PlayPressed_8();
	void PlayPressed_9();
	void PlayPressed_10();
	void PlayPressed_11();
	void PlayPressed_12();
	void PlayPressed_13();
	void PlayPressed_14();
	void PlayPressed_15();
	void PlayPressed_16();
	void PlayReleased_3();
	void PlayReleased_4();
	void PlayReleased_5();
	void PlayReleased_6();
	void PlayReleased_7();
	void PlayReleased_8();
	void PlayReleased_9();
	void PlayReleased_10();
	void PlayReleased_11();
	void PlayReleased_12();
	void PlayReleased_13();
	void PlayReleased_14();
	void PlayReleased_15();
	void PlayReleased_16();
	void PlayHovered_3();
	void PlayHovered_4();
	void PlayHovered_5();
	void PlayHovered_6();
	void PlayHovered_7();
	void PlayHovered_8();
	void PlayHovered_9();
	void PlayHovered_10();
	void PlayHovered_11();
	void PlayHovered_12();
	void PlayHovered_13();
	void PlayHovered_14();
	void PlayHovered_15();
	void PlayHovered_16();
	void PlayUnHovered_3();
	void PlayUnHovered_4();
	void PlayUnHovered_5();
	void PlayUnHovered_6();
	void PlayUnHovered_7();
	void PlayUnHovered_8();
	void PlayUnHovered_9();
	void PlayUnHovered_10();
	void PlayUnHovered_11();
	void PlayUnHovered_12();
	void PlayUnHovered_13();
	void PlayUnHovered_14();
	void PlayUnHovered_15();
	void PlayUnHovered_16();

	FMargin CalculateTitlePosition(FVector2D funcViewportSize);
	FMargin CalculateMenuTextPos(int textIndex, int numberOfLetters);
	FMargin CalculateHighscorePos(int textIndex, int numberOfLetters);
	FMargin CalculateLastGamePos(int textIndex, int numberOfLetters);
	float CalculateGrownMarginX(FMargin inMargin);
	float CalculateGrownMarginY(FMargin inMargin);
	FMargin GrowMargin(FMargin inMargin);
	FMargin GrownMargin(FMargin inMargin);
	FMargin ShrinkMargin(FMargin inMargin, int marginIndex);
	void PlayChordToActiveNote();

	TWeakObjectPtr<class ATestHud> OwningHUD;
	UObject* standardWorldContextObject;
	USaveGameOne* currentSave;

	TArray<UMaterial*> backgroundMaterials;
	TArray<FSlateBrush*> backgroundStuff;
	bool backgroundIsLargeTile;

	UMaterial* gameFrameColor_SMUI;

	FSlateBrush* gameFrameColor_SB;
	FSlateBrush* background_SB_1;
	FSlateBrush* background_SB_2;
	FSlateBrush* background_SB_3;
	FSlateBrush* background_SB_4;
	FSlateBrush* background_SB_5;
	FSlateBrush* background_SB_6;
	FSlateBrush* background_SB_7;
	FSlateBrush* background_SB_8;
	FSlateBrush* background_SB_9;

	USoundBase* hoverGrow;
	USoundBase* hoverShrink;

	TSharedPtr< class SOverlay> backgroundOverlay;
	TSharedPtr< class SOverlay> frameColorOverlay;
	TSharedPtr< class SOverlay> masterOverlay;
	TSharedPtr< class SOverlay> levelSelectionOverlay;
	TSharedPtr< class SOverlay> mainMenuOverlay;
	TSharedPtr< class SOverlay> resultsOverlay;

	FVector2D viewportSize;
	FVector2D adjustedViewportSize;
	float DPIScale;

	FSlateFontInfo titleFont;
	FSlateFontInfo subTitleFont;
	FSlateFontInfo menuFont;
	FSlateFontInfo levelSelectorFont;
	FSlateFontInfo scoreFont;
	FText titleText;

	TSharedPtr<class SBox> playBox;
	TSharedPtr<class SBox> resultsBox;
	TSharedPtr<class SBox> optionsBox;
	TSharedPtr<class SBox> quitBox;
	TSharedPtr<class SBox> firstFloorBackBox;

	TSharedPtr<class STextBlock> playText;
	TSharedPtr<class STextBlock> resultsText;
	TSharedPtr<class STextBlock> optionsText;
	TSharedPtr<class STextBlock> quitText;
	TSharedPtr<class STextBlock> backText;

	FButtonStyle* transparentButtonStyle;

	TArray< TSharedPtr< class SBox> > levelSelectionBoxes;
	TArray< TSharedPtr< class STextBlock> > levelSelectionTexts;
	TArray <bool> enabledLevels;

	FMargin playMargin;
	FMargin resultsMargin;
	FMargin optionsMargin;
	FMargin quitMargin;
	FMargin backMargin;
	TArray<FMargin> levelSelectionMargins;

	TArray<FMargin> completedMargins;
	TArray<FSlateFontInfo> completedFonts;
	TArray<float> completedOffsets;

	float grownOpacity;
	float multiplierOfOffset;
	float multiplierOfPerimeterExpansion;

	bool clicked;

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
	float standardOpacity;
	float startingOpacity;
	FLinearColor growingLinearColor;
	float growingOpacity;
	float adjustedGrowingOpacity;
	TArray<float> startingShrinkingOpacities;
	TArray<FLinearColor> shrinkingLinearColors;
	TArray<float> shrinkingOpacities;
	TArray<float> adjustedShrinkingOpacities;

	bool displayResults;

	TArray<int> childrensCornerNotes;
	int childrensCornerIndex;

	int environmentAudio;
	float audioTimer;
	int audioCycleTracker;

	UAudioComponent* hoverGrowAudioComponent;
	UAudioComponent* hoverShrinkAudioComponent;

	UPROPERTY() TArray<UAudioComponent*> hoverGrowAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> hoverShrinkAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> windAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> windWithSheepAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> riverAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> waterfallAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> purpleLullabyAudioComponents;

	int activeNoteIndex;
	TArray< TArray <int> > correspondingChordsToNotes = { { 0 }, { 1 }, { 0, 3}, { 1 }, { 0, 2, 3}, { 1 }, { 2, 3}, { 3 } };
	TArray< TArray <int> > chordIndexes = { { 0, 2, 4 }, { 1, 3, 5 }, { 2, 4, 6 }, { 4, 6, 7 } };
};