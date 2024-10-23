// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyHUD.h"
#include "SaveGameOne.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SOptions : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SOptions) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwningHUD)

	SLATE_ARGUMENT(APlayerController*, playerOnePlayerController)

	SLATE_ARGUMENT(UObject*, standardWorldContextObject)

	SLATE_ARGUMENT(TArray<UAudioComponent*>, hoverGrowAudioComponents)

	SLATE_ARGUMENT(TArray<UAudioComponent*>, hoverShrinkAudioComponents)

	SLATE_ARGUMENT(TArray <UAudioComponent*>, purpleLullabyAudioComponents)

	SLATE_ARGUMENT(TArray <UAudioComponent*>, songAudioComponents)

	SLATE_ARGUMENT(UMaterial*, gameFrameColor_SMUI)

	SLATE_ARGUMENT(int, songPlayingIndex)

	SLATE_ARGUMENT(TArray<int>, songCycles)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& InMouseEvent);
	FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);
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

	void OnCreditsPressed();
	void OnCreditsReleased();
	void OnCreditsHovered();
	void OnCreditsUnHovered();

	void OnBackFloorOneReleased();
	void OnBackFloorOnePressed();
	void OnBackFloorOneHovered();
	void OnBackFloorOneUnHovered();

	void OnBackToMenuReleased();
	void OnBackToMenuPressed();
	void OnBackToMenuHovered();
	void OnBackToMenuUnHovered();

	void OnSongCreditOneReleased();
	void OnSongCreditOnePressed();
	void OnSongCreditOneHovered();
	void OnSongCreditOneUnHovered();

	void OnSongCreditTwoReleased();
	void OnSongCreditTwoPressed();
	void OnSongCreditTwoHovered();
	void OnSongCreditTwoUnHovered();

	void OnSongCreditThreeReleased();
	void OnSongCreditThreePressed();
	void OnSongCreditThreeHovered();
	void OnSongCreditThreeUnHovered();

	void OnSongCreditFourReleased();
	void OnSongCreditFourPressed();
	void OnSongCreditFourHovered();
	void OnSongCreditFourUnHovered();

	void OnSongCreditFiveReleased();
	void OnSongCreditFivePressed();
	void OnSongCreditFiveHovered();
	void OnSongCreditFiveUnHovered();

	void OnSongCreditSixReleased();
	void OnSongCreditSixPressed();
	void OnSongCreditSixHovered();
	void OnSongCreditSixUnHovered();

	void OnSongCreditSevenReleased();
	void OnSongCreditSevenPressed();
	void OnSongCreditSevenHovered();
	void OnSongCreditSevenUnHovered();

	void OnSongCreditEightReleased();
	void OnSongCreditEightPressed();
	void OnSongCreditEightHovered();
	void OnSongCreditEightUnHovered();

	void OnPauseBindingResetPressed();
	void OnPauseBindingResetReleased();

	void OnPauseMouseBindingResetPressed();
	void OnPauseMouseBindingResetReleased();

	void OnVSyncChecked(ECheckBoxState InState);

	void OnGammaOneReleased();
	void OnGammaOnePressed();
	void OnGammaOneHovered();
	void OnGammaOneUnHovered();

	void OnGammaTwoReleased();
	void OnGammaTwoPressed();
	void OnGammaTwoHovered();
	void OnGammaTwoUnHovered();

	void OnResetGammaReleased();
	void OnResetGammaPressed();
	void OnResetGammaHovered();
	void OnResetGammaUnHovered();

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
	FMargin CalculateMiddleColumnPos(int textIndex);
	FMargin CalculateCheckBoxPos(int textIndex);
	FMargin TwinButtonsCenter(int verticleIndex, int buttonIndex);
	void PlayChordToActiveNote();

	UPROPERTY() TWeakObjectPtr<class AMyHUD> OwningHUD;
	UPROPERTY() APlayerController* playerOnePlayerController;
	UPROPERTY() UObject* standardWorldContextObject;
	UPROPERTY() USaveGameOne* currentSave;

	UPROPERTY() UMaterial* gameFrameColor_SMUI;

	UPROPERTY() FSlateBrush* gameFrameColor_SB;

	UPROPERTY() FSlateBrush* checkboxBackground_SB;
	UPROPERTY() FSlateBrush* checkboxBackgroundHovered_SB;
	UPROPERTY() FSlateBrush* checkboxCheckedBackground_SB;
	UPROPERTY() FSlateBrush* checkboxCheckedBackgroundHovered_SB;

	UPROPERTY() FVector2D viewportSize;
	UPROPERTY() FVector2D adjustedViewportSize;
	UPROPERTY() float DPIScale;

	UPROPERTY() TSharedPtr< class SOverlay> masterOverlay;
	UPROPERTY() TSharedPtr< class SOverlay> mainOptionsOverlay;
	UPROPERTY() TSharedPtr< class SOverlay> audioOverlay;
	UPROPERTY() TSharedPtr< class SOverlay> controlsOverlay;
	UPROPERTY() TSharedPtr< class SOverlay> creditsOverlay;
	UPROPERTY() TSharedPtr< class SOverlay> graphicsOverlay;

	UPROPERTY() TSharedPtr<class SBox> audioBox;
	UPROPERTY() TSharedPtr<class SBox> graphicsBox;
	UPROPERTY() TSharedPtr<class SBox> controlsBox;
	UPROPERTY() TSharedPtr<class SBox> creditsBox;
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
	UPROPERTY() TSharedPtr<class SBox> keyboardBindingsTextBox;
	UPROPERTY() TSharedPtr<class SBox> pause1TextBox;
	UPROPERTY() TSharedPtr<class SBox> pauseKeyBox;
	UPROPERTY() TSharedPtr<class SBox> pause2TextBox;
	UPROPERTY() TSharedPtr<class SBox> pauseMouseBox;
	UPROPERTY() TSharedPtr<class SBox> controllerBindingsTextBox;

	UPROPERTY() TSharedPtr<class SBox> creditBoxOne;
	UPROPERTY() TSharedPtr<class SBox> creditBoxTwo;
	UPROPERTY() TSharedPtr<class SBox> creditBoxThree;
	UPROPERTY() TSharedPtr<class SBox> creditBoxFour;
	UPROPERTY() TSharedPtr<class SBox> creditBoxFive;
	UPROPERTY() TSharedPtr<class SBox> creditBoxSix;
	UPROPERTY() TSharedPtr<class SBox> creditBoxSeven;
	UPROPERTY() TSharedPtr<class SBox> creditBoxEight;

	UPROPERTY() TSharedPtr<class SEditableText> masterEditableTextBox;
	UPROPERTY() TSharedPtr<class SEditableText> musicEditableTextBox;
	UPROPERTY() TSharedPtr<class SEditableText> atmosphereEditableTextBox;
	UPROPERTY() TSharedPtr<class SEditableText> sfxEditableTextBox;

	UPROPERTY() TSharedPtr<class STextBlock> audioText;
	UPROPERTY() TSharedPtr<class STextBlock> graphicsText;
	UPROPERTY() TSharedPtr<class STextBlock> controlsText;
	UPROPERTY() TSharedPtr<class STextBlock> creditsText;
	UPROPERTY() TSharedPtr<class STextBlock> backText;

	UPROPERTY() TSharedPtr<class STextBlock> creditTextOne;
	UPROPERTY() TSharedPtr<class STextBlock> creditTextTwo;
	UPROPERTY() TSharedPtr<class STextBlock> creditTextThree;
	UPROPERTY() TSharedPtr<class STextBlock> creditTextFour;
	UPROPERTY() TSharedPtr<class STextBlock> creditTextFive;
	UPROPERTY() TSharedPtr<class STextBlock> creditTextSix;
	UPROPERTY() TSharedPtr<class STextBlock> creditTextSeven;
	UPROPERTY() TSharedPtr<class STextBlock> creditTextEight;

	UPROPERTY() TSharedPtr<class STextBlock> pauseKeyText;
	UPROPERTY() TSharedPtr<class SButton> pauseKeyButton;
	UPROPERTY() TSharedPtr<class SImage> pauseKeyBackground;
	UPROPERTY() TSharedPtr<class SBox> pauseKeyBackgroundBox;

	UPROPERTY() TSharedPtr<class STextBlock> pauseMouseText;
	UPROPERTY() TSharedPtr<class SButton> pauseMouseButton;
	UPROPERTY() TSharedPtr<class SImage> pauseMouseBackground;
	UPROPERTY() TSharedPtr<class SBox> pauseMouseBackgroundBox;

	UPROPERTY() TSharedPtr<class SToolTip> songListToolTip;

	UPROPERTY() TSharedPtr<class SBox> vsyncBoxOne;
	UPROPERTY() TSharedPtr<class SBox> vsyncBoxTwo;
	UPROPERTY() TSharedPtr<class SCheckBox> vsyncCheckBox;
	UPROPERTY() TSharedPtr<class SBox> VSyncCheckBoxBackground;

	UPROPERTY() TSharedPtr<class SBox> gammaBox;
	UPROPERTY() TSharedPtr<class SBox> gammaOptionBoxOne;
	UPROPERTY() TSharedPtr<class SBox> gammaOptionBoxTwo;
	UPROPERTY() TSharedPtr<class SBox> gammaResetBox;
	UPROPERTY() TSharedPtr<class STextBlock> gammaTextOne;
	UPROPERTY() TSharedPtr<class STextBlock> gammaTextTwo;
	UPROPERTY() TSharedPtr<class STextBlock> gammaResetText;

	UPROPERTY() FSlateFontInfo titleFont;
	UPROPERTY() FSlateFontInfo subTitleFont;
	UPROPERTY() FSlateFontInfo menuFont;
	UPROPERTY() FSlateFontInfo textFont;

	UPROPERTY() FMargin audioMargin;
	UPROPERTY() FMargin graphicsMargin;
	UPROPERTY() FMargin controlsMargin;
	UPROPERTY() FMargin creditsMargin;
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
	UPROPERTY() TArray<UAudioComponent*> songAudioComponents;

	UPROPERTY() int activeNoteIndex;
	TArray< TArray <int> > correspondingChordsToNotes = { { 0 }, { 1 }, { 0, 3}, { 1 }, { 0, 2, 3}, { 1 }, { 2, 3}, { 3 } };
	TArray< TArray <int> > chordIndexes = { { 0, 2, 4 }, { 1, 3, 5 }, { 2, 4, 6 }, { 4, 6, 7 } };

	bool makeSave;

	UPROPERTY() bool replaceKey;
	UPROPERTY() int keyToReplace;
	UPROPERTY() int songPlayingIndex;
	UPROPERTY() bool songPlaying;
	UPROPERTY() TArray<int> songCycles;

	UPROPERTY() TArray<FColor> songTextColors;
};