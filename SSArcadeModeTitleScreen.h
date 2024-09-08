
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

	SLATE_ARGUMENT(APlayerController*, playerOnePlayerController)

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

	void PlayChordToActiveNote();
	void ReturnToMenu();

	UPROPERTY() FMargin CalculateTitlePosition(FVector2D funcViewportSize);
	UPROPERTY() FMargin CalculateMenuTextPos(int textIndex, int numberOfLetters);
	UPROPERTY() FMargin CalculateHighscorePos(int textIndex, int numberOfLetters);
	UPROPERTY() FMargin CalculateLastGamePos(int textIndex, int numberOfLetters);
	UPROPERTY() float CalculateGrownMarginX(FMargin inMargin);
	UPROPERTY() float CalculateGrownMarginY(FMargin inMargin);
	UPROPERTY() FMargin GrowMargin(FMargin inMargin);
	UPROPERTY() FMargin GrownMargin(FMargin inMargin);
	UPROPERTY() FMargin ShrinkMargin(FMargin inMargin, int marginIndex);

	UPROPERTY() TWeakObjectPtr<class ATestHud> OwningHUD;
	UPROPERTY() APlayerController* playerOnePlayerController;
	UPROPERTY() UObject* standardWorldContextObject;
	UPROPERTY() USaveGameOne* currentSave;

	UPROPERTY() TArray<UMaterial*> backgroundMaterials;
	UPROPERTY() TArray<FSlateBrush*> backgroundStuff;
	UPROPERTY() bool backgroundIsLargeTile;

	UPROPERTY() UMaterial* gameFrameColor_SMUI;

	UPROPERTY() FSlateBrush* gameFrameColor_SB;
	UPROPERTY() FSlateBrush* background_SB_1;
	UPROPERTY() FSlateBrush* background_SB_2;
	UPROPERTY() FSlateBrush* background_SB_3;
	UPROPERTY() FSlateBrush* background_SB_4;
	UPROPERTY() FSlateBrush* background_SB_5;
	UPROPERTY() FSlateBrush* background_SB_6;
	UPROPERTY() FSlateBrush* background_SB_7;
	UPROPERTY() FSlateBrush* background_SB_8;
	UPROPERTY() FSlateBrush* background_SB_9;

	UPROPERTY() USoundBase* hoverGrow;
	UPROPERTY() USoundBase* hoverShrink;

	UPROPERTY() TSharedPtr< class SOverlay> backgroundOverlay;
	UPROPERTY() TSharedPtr< class SOverlay> frameColorOverlay;
	UPROPERTY() TSharedPtr< class SOverlay> masterOverlay;
	UPROPERTY() TSharedPtr< class SOverlay> levelSelectionOverlay;
	UPROPERTY() TSharedPtr< class SOverlay> mainMenuOverlay;
	UPROPERTY() TSharedPtr< class SOverlay> resultsOverlay;

	UPROPERTY() FVector2D viewportSize;
	UPROPERTY() FVector2D adjustedViewportSize;
	UPROPERTY() float DPIScale;

	UPROPERTY() FSlateFontInfo titleFont;
	UPROPERTY() FSlateFontInfo subTitleFont;
	UPROPERTY() FSlateFontInfo menuFont;
	UPROPERTY() FSlateFontInfo levelSelectorFont;
	UPROPERTY() FSlateFontInfo scoreFont;
	UPROPERTY() FText titleText;

	UPROPERTY() TSharedPtr<class SBox> playBox;
	UPROPERTY() TSharedPtr<class SBox> resultsBox;
	UPROPERTY() TSharedPtr<class SBox> optionsBox;
	UPROPERTY() TSharedPtr<class SBox> quitBox;
	UPROPERTY() TSharedPtr<class SBox> firstFloorBackBox;

	UPROPERTY() TSharedPtr<class STextBlock> playText;
	UPROPERTY() TSharedPtr<class STextBlock> resultsText;
	UPROPERTY() TSharedPtr<class STextBlock> optionsText;
	UPROPERTY() TSharedPtr<class STextBlock> quitText;
	UPROPERTY() TSharedPtr<class STextBlock> backText;

	UPROPERTY() FButtonStyle* transparentButtonStyle;

	UPROPERTY() TArray< TSharedPtr< class SBox> > levelSelectionBoxes;
	UPROPERTY() TArray< TSharedPtr< class STextBlock> > levelSelectionTexts;
	UPROPERTY() TArray <bool> enabledLevels;

	UPROPERTY() FMargin playMargin;
	UPROPERTY() FMargin resultsMargin;
	UPROPERTY() FMargin optionsMargin;
	UPROPERTY() FMargin quitMargin;
	UPROPERTY() FMargin backMargin;
	UPROPERTY() TArray<FMargin> levelSelectionMargins;

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

	UPROPERTY() bool displayResults;

	UPROPERTY() TArray<int> childrensCornerNotes;
	UPROPERTY() int childrensCornerIndex;

	UPROPERTY() int environmentAudio;
	UPROPERTY() float audioTimer;
	UPROPERTY() int audioCycleTracker;

	UPROPERTY() UAudioComponent* hoverGrowAudioComponent;
	UPROPERTY() UAudioComponent* hoverShrinkAudioComponent;

	UPROPERTY() TArray<UAudioComponent*> hoverGrowAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> hoverShrinkAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> windAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> windWithSheepAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> riverAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> waterfallAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> purpleLullabyAudioComponents;

	UPROPERTY() int activeNoteIndex;
	TArray< TArray <int> > correspondingChordsToNotes = { { 0 }, { 1 }, { 0, 3}, { 1 }, { 0, 2, 3}, { 1 }, { 2, 3}, { 3 } };
	TArray< TArray <int> > chordIndexes = { { 0, 2, 4 }, { 1, 3, 5 }, { 2, 4, 6 }, { 4, 6, 7 } };
	UPROPERTY() bool sheep;
};