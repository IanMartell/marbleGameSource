// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "mediaPlayer.h"
#include "MediaSource.h"
#include "BaseMediaSource.h"
#include "ImgMediaSource.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGameOne.h"
#include "Framework/Application/SlateApplication.h"
#include "Engine/EngineBaseTypes.h"
#include "TestHud.generated.h"

/**
 *
 */
UCLASS()
class MARBLEGAMEBLUEPRINT_API ATestHud : public AHUD
{
	GENERATED_BODY()

public:
	//stuff for accessing content browser assets
	ATestHud();//resharper? visual assist check discord

	UPROPERTY() UMaterial* grass_VMUI_1;// all uobject variables must be uproperty otherwise the garbage collecter will collect them
	UPROPERTY() UMediaPlayer* grass_MP_1;//change the umaerial to material interface
	UPROPERTY() UMaterial* grass_VMUI_2;
	UPROPERTY() UMediaPlayer* grass_MP_2;
	UPROPERTY() UMaterial* grass_VMUI_3;
	UPROPERTY() UMediaPlayer* grass_MP_3;
	UPROPERTY() UMaterial* pondHorizontal_VMUI;
	UPROPERTY() UMediaPlayer* pondHorizontal_MP;
	UPROPERTY() UMaterial* pondVerticleFlowingLeft_VMUI;
	UPROPERTY() UMediaPlayer* pondVerticleFlowingLeft_MP;
	UPROPERTY() UMaterial* pondVerticleFlowingRight_VMUI;
	UPROPERTY() UMediaPlayer* pondVerticleFlowingRight_MP;
	UPROPERTY() UMaterial* riverFlowingDown_VMUI_1;
	UPROPERTY() UMediaPlayer* riverFlowingDown_MP_1;
	UPROPERTY() UMaterial* riverFlowingDown_VMUI_2;
	UPROPERTY() UMediaPlayer* riverFlowingDown_MP_2;
	UPROPERTY() UMaterial* riverFlowingDown_VMUI_3;
	UPROPERTY() UMediaPlayer* riverFlowingDown_MP_3;
	UPROPERTY() UMaterial* riverFlowingLeft_VMUI_1;
	UPROPERTY() UMediaPlayer* riverFlowingLeft_MP_1;
	UPROPERTY() UMaterial* riverFlowingLeft_VMUI_2;
	UPROPERTY() UMediaPlayer* riverFlowingLeft_MP_2;
	UPROPERTY() UMaterial* riverFlowingLeft_VMUI_3;
	UPROPERTY() UMediaPlayer* riverFlowingLeft_MP_3;
	UPROPERTY() UMaterial* riverFlowingRight_VMUI_1;
	UPROPERTY() UMediaPlayer* riverFlowingRight_MP_1;
	UPROPERTY() UMaterial* riverFlowingRight_VMUI_2;
	UPROPERTY() UMediaPlayer* riverFlowingRight_MP_2;
	UPROPERTY() UMaterial* riverFlowingRight_VMUI_3;
	UPROPERTY() UMediaPlayer* riverFlowingRight_MP_3;
	UPROPERTY() UMaterial* tree_VMUI_1;
	UPROPERTY() UMediaPlayer* tree_MP_1;
	UPROPERTY() UMaterial* tree_VMUI_2;
	UPROPERTY() UMediaPlayer* tree_MP_2;
	UPROPERTY() UMaterial* tree_VMUI_3;
	UPROPERTY() UMediaPlayer* tree_MP_3;
	UPROPERTY() UMaterial* tree_VMUI_4;
	UPROPERTY() UMediaPlayer* tree_MP_4;
	UPROPERTY() UMaterial* tree_VMUI_5;
	UPROPERTY() UMediaPlayer* tree_MP_5;
	UPROPERTY() UMaterial* waterfall_VMUI;
	UPROPERTY() UMediaPlayer* waterfall_MP;
	UPROPERTY() UMaterial* riverTurning_VMUI_1;
	UPROPERTY() UMediaPlayer* riverTurning_MP_1;
	UPROPERTY() UMaterial* riverTurning_VMUI_2;
	UPROPERTY() UMediaPlayer* riverTurning_MP_2;
	UPROPERTY() UMaterial* riverTurning_VMUI_3;
	UPROPERTY() UMediaPlayer* riverTurning_MP_3;
	UPROPERTY() UMaterial* riverTurning_VMUI_4;
	UPROPERTY() UMediaPlayer* riverTurning_MP_4;
	UPROPERTY() UMaterial* mountain_VMUI_1;
	UPROPERTY() UMediaPlayer* mountain_MP_1;

	UPROPERTY() UMaterial* holeFromDown_VMUI;
	UPROPERTY() UMediaPlayer* holeFromDown_MP;
	UPROPERTY() UMaterial* holeFromLeft_VMUI;
	UPROPERTY() UMediaPlayer* holeFromLeft_MP;
	UPROPERTY() UMaterial* holeFromRight_VMUI;
	UPROPERTY() UMediaPlayer* holeFromRight_MP;
	UPROPERTY() UMaterial* holeFromUp_VMUI;
	UPROPERTY() UMediaPlayer* holeFromUp_MP;

	UPROPERTY() UMaterial* flag_VMUI_1;
	UPROPERTY() UMediaPlayer* flag_MP_1;
	UPROPERTY() UMaterial* flag_VMUI_2;
	UPROPERTY() UMediaPlayer* flag_MP_2;
	UPROPERTY() UMaterial* flag_VMUI_3;
	UPROPERTY() UMediaPlayer* flag_MP_3;
	UPROPERTY() UMaterial* flag_VMUI_4;
	UPROPERTY() UMediaPlayer* flag_MP_4;
	UPROPERTY() UMaterial* flag_VMUI_5;
	UPROPERTY() UMediaPlayer* flag_MP_5;
	UPROPERTY() UMaterial* flag_VMUI_6;
	UPROPERTY() UMediaPlayer* flag_MP_6;
	UPROPERTY() UMaterial* flag_VMUI_7;
	UPROPERTY() UMediaPlayer* flag_MP_7;
	UPROPERTY() UMaterial* flag_VMUI_8;
	UPROPERTY() UMediaPlayer* flag_MP_8;
	UPROPERTY() UMaterial* flag_VMUI_9;
	UPROPERTY() UMediaPlayer* flag_MP_9;
	UPROPERTY() UMaterial* flag_VMUI_10;
	UPROPERTY() UMediaPlayer* flag_MP_10;
	UPROPERTY() UMaterial* flag_VMUI_11;
	UPROPERTY() UMediaPlayer* flag_MP_11;
	UPROPERTY() UMaterial* flag_VMUI_12;
	UPROPERTY() UMediaPlayer* flag_MP_12;
	UPROPERTY() UMaterial* flag_VMUI_13;
	UPROPERTY() UMediaPlayer* flag_MP_13;
	UPROPERTY() UMaterial* flag_VMUI_14;
	UPROPERTY() UMediaPlayer* flag_MP_14;
	UPROPERTY() UMaterial* flag_VMUI_15;
	UPROPERTY() UMediaPlayer* flag_MP_15;
	UPROPERTY() UMaterial* flag_VMUI_16;
	UPROPERTY() UMediaPlayer* flag_MP_16;

	UPROPERTY() UMaterial* curtains_VMUI;
	UPROPERTY() UMediaPlayer* curtains_MP;

	UPROPERTY() UImgMediaSource* grass_IS_1;
	UPROPERTY() UImgMediaSource* grass_IS_2;
	UPROPERTY() UImgMediaSource* grass_IS_3;
	UPROPERTY() UImgMediaSource* pondHorizontal_IS;
	UPROPERTY() UImgMediaSource* pondVerticleFlowingLeft_IS;
	UPROPERTY() UImgMediaSource* pondVerticleFlowingRight_IS;
	UPROPERTY() UImgMediaSource* riverFlowingDown_IS_1;
	UPROPERTY() UImgMediaSource* riverFlowingDown_IS_2;
	UPROPERTY() UImgMediaSource* riverFlowingDown_IS_3;
	UPROPERTY() UImgMediaSource* riverFlowingLeft_IS_1;
	UPROPERTY() UImgMediaSource* riverFlowingLeft_IS_2;
	UPROPERTY() UImgMediaSource* riverFlowingLeft_IS_3;
	UPROPERTY() UImgMediaSource* riverFlowingRight_IS_1;
	UPROPERTY() UImgMediaSource* riverFlowingRight_IS_2;
	UPROPERTY() UImgMediaSource* riverFlowingRight_IS_3;
	UPROPERTY() UImgMediaSource* tree_IS_1;
	UPROPERTY() UImgMediaSource* tree_IS_2;
	UPROPERTY() UImgMediaSource* tree_IS_3;
	UPROPERTY() UImgMediaSource* tree_IS_4;
	UPROPERTY() UImgMediaSource* tree_IS_5;
	UPROPERTY() UImgMediaSource* waterfall_IS;
	UPROPERTY() UImgMediaSource* riverTurning_IS_1;
	UPROPERTY() UImgMediaSource* riverTurning_IS_2;
	UPROPERTY() UImgMediaSource* riverTurning_IS_3;
	UPROPERTY() UImgMediaSource* riverTurning_IS_4;
	UPROPERTY() UImgMediaSource* mountain_IS_1;

	UPROPERTY() UImgMediaSource* holeFromDown_IS;
	UPROPERTY() UImgMediaSource* holeFromLeft_IS;
	UPROPERTY() UImgMediaSource* holeFromRight_IS;
	UPROPERTY() UImgMediaSource* holeFromUp_IS;

	UPROPERTY() UImgMediaSource* flag_IS_1;
	UPROPERTY() UImgMediaSource* flag_IS_2;
	UPROPERTY() UImgMediaSource* flag_IS_3;
	UPROPERTY() UImgMediaSource* flag_IS_4;
	UPROPERTY() UImgMediaSource* flag_IS_5;
	UPROPERTY() UImgMediaSource* flag_IS_6;
	UPROPERTY() UImgMediaSource* flag_IS_7;
	UPROPERTY() UImgMediaSource* flag_IS_8;
	UPROPERTY() UImgMediaSource* flag_IS_9;
	UPROPERTY() UImgMediaSource* flag_IS_10;
	UPROPERTY() UImgMediaSource* flag_IS_11;
	UPROPERTY() UImgMediaSource* flag_IS_12;
	UPROPERTY() UImgMediaSource* flag_IS_13;
	UPROPERTY() UImgMediaSource* flag_IS_14;
	UPROPERTY() UImgMediaSource* flag_IS_15;
	UPROPERTY() UImgMediaSource* flag_IS_16;

	UPROPERTY() UImgMediaSource* curtains_IS;

	UPROPERTY() UMaterial* buttonFromDownTurningRightZero_SMUI;
	UPROPERTY() UMaterial* buttonFromDownTurningRightOne_SMUI;
	UPROPERTY() UMaterial* buttonFromDownTurningRightTwo_SMUI;
	UPROPERTY() UMaterial* buttonFromDownTurningRightThree_SMUI;
	UPROPERTY() UMaterial* buttonFromDownTurningLeftZero_SMUI;
	UPROPERTY() UMaterial* buttonFromDownTurningLeftOne_SMUI;
	UPROPERTY() UMaterial* buttonFromDownTurningLeftTwo_SMUI;
	UPROPERTY() UMaterial* buttonFromDownTurningLeftThree_SMUI;
	UPROPERTY() UMaterial* buttonFromLeftTurningRightZero_SMUI;
	UPROPERTY() UMaterial* buttonFromLeftTurningRightOne_SMUI;
	UPROPERTY() UMaterial* buttonFromLeftTurningRightTwo_SMUI;
	UPROPERTY() UMaterial* buttonFromLeftTurningRightThree_SMUI;
	UPROPERTY() UMaterial* buttonFromLeftTurningLeftZero_SMUI;
	UPROPERTY() UMaterial* buttonFromLeftTurningLeftOne_SMUI;
	UPROPERTY() UMaterial* buttonFromLeftTurningLeftTwo_SMUI;
	UPROPERTY() UMaterial* buttonFromLeftTurningLeftThree_SMUI;
	UPROPERTY() UMaterial* buttonFromRightTurningRightZero_SMUI;
	UPROPERTY() UMaterial* buttonFromRightTurningRightOne_SMUI;
	UPROPERTY() UMaterial* buttonFromRightTurningRightTwo_SMUI;
	UPROPERTY() UMaterial* buttonFromRightTurningRightThree_SMUI;
	UPROPERTY() UMaterial* buttonFromRightTurningLeftZero_SMUI;
	UPROPERTY() UMaterial* buttonFromRightTurningLeftOne_SMUI;
	UPROPERTY() UMaterial* buttonFromRightTurningLeftTwo_SMUI;
	UPROPERTY() UMaterial* buttonFromRightTurningLeftThree_SMUI;
	UPROPERTY() UMaterial* buttonFromUpTurningRightZero_SMUI;
	UPROPERTY() UMaterial* buttonFromUpTurningRightOne_SMUI;
	UPROPERTY() UMaterial* buttonFromUpTurningRightTwo_SMUI;
	UPROPERTY() UMaterial* buttonFromUpTurningRightThree_SMUI;
	UPROPERTY() UMaterial* buttonFromUpTurningLeftZero_SMUI;
	UPROPERTY() UMaterial* buttonFromUpTurningLeftOne_SMUI;
	UPROPERTY() UMaterial* buttonFromUpTurningLeftTwo_SMUI;
	UPROPERTY() UMaterial* buttonFromUpTurningLeftThree_SMUI;

	UPROPERTY() UMaterial* verticleRail_SMUI;
	UPROPERTY() UMaterial* horizontalRail_SMUI;

	UPROPERTY() UMaterial* railTurningOne_SMUI;
	UPROPERTY() UMaterial* railTurningTwo_SMUI;
	UPROPERTY() UMaterial* railTurningThree_SMUI;
	UPROPERTY() UMaterial* railTurningFour_SMUI;

	UPROPERTY() UMaterial* marble_SMUI_1;
	UPROPERTY() UMaterial* marble_SMUI_2;
	UPROPERTY() UMaterial* marble_SMUI_3;
	UPROPERTY() UMaterial* marble_SMUI_4;
	UPROPERTY() UMaterial* marble_SMUI_5;
	UPROPERTY() UMaterial* marble_SMUI_6;
	UPROPERTY() UMaterial* marble_SMUI_7;
	UPROPERTY() UMaterial* marble_SMUI_8;
	UPROPERTY() UMaterial* marble_SMUI_9;
	UPROPERTY() UMaterial* marble_SMUI_10;
	UPROPERTY() UMaterial* marble_SMUI_11;
	UPROPERTY() UMaterial* marble_SMUI_12;
	UPROPERTY() UMaterial* marble_SMUI_13;
	UPROPERTY() UMaterial* marble_SMUI_14;
	UPROPERTY() UMaterial* marble_SMUI_15;
	UPROPERTY() UMaterial* marble_SMUI_16;

	UPROPERTY() UMaterial* gameFrameColor_SMUI;

	UPROPERTY() UMaterial* goodUseSplashBootNoGrass_SMUI;
	UPROPERTY() UMaterial* goodUseSplashGrass_SMUI;
	UPROPERTY() UMaterial* goodUseDigitalText_SMUI;

	UPROPERTY() TArray <UMaterial*> splashGrassArr;
	UPROPERTY() TArray <UMaterial*> splashBootArr;

	UPROPERTY() UMaterial* placeholderTrash;
	UPROPERTY() UMaterial* emptyImg_SMUI;

	//sound effects stuff

	UPROPERTY() USoundBase* intersectionButtonPressed;
	UPROPERTY() USoundBase* intersectionButtonReleased;
	UPROPERTY() USoundBase* hoverGrow;
	UPROPERTY() USoundBase* hoverShrink;
	UPROPERTY() USoundBase* curtainClosing;
	UPROPERTY() USoundBase* curtainOpening;
	UPROPERTY() USoundBase* rainstick;
	UPROPERTY() USoundBase* wind;
	UPROPERTY() USoundBase* windWithSheep;
	UPROPERTY() USoundBase* river;
	UPROPERTY() USoundBase* waterfall;

	UPROPERTY() TArray <USoundBase*> hoverGrows;
	UPROPERTY() TArray <USoundBase*> hoverShrinks;
	UPROPERTY() TArray <USoundBase*> purpleLullaby;
	UPROPERTY() TArray <USoundBase*> purpleLullabyTwo;

	UPROPERTY() USoundBase* songOne;

	UPROPERTY() UAudioComponent* intersectionDownAudioComponent;
	UPROPERTY() UAudioComponent* intersectionUpAudioComponent;
	UPROPERTY() UAudioComponent* curtainClosingAudioComponent;
	UPROPERTY() UAudioComponent* curtainOpeningAudioComponent;
	UPROPERTY() UAudioComponent* rainstickAudioComponent;

	UPROPERTY() TArray <UAudioComponent*> hoverGrowAudioComponents;
	UPROPERTY() TArray <UAudioComponent*> hoverShrinkAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> windAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> windWithSheepAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> riverAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> waterfallAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> purpleLullabyAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> purpleLullabyTwoAudioComponents;

	UPROPERTY() UAudioComponent* songOneAudioComponent;

protected:
	//protected init stuff
	// I just realized if theres ever any variables which are getting garbage collected which I cannot designate as UPROPERTY such as these I could declare and initiliaze them on the stack. the code might run slower that way but it should work
	TSharedPtr<class SLoadingScreenOne> loadingSlateWidget;
	TSharedPtr<class SWidget> slateWidgetContainerOne;

	TSharedPtr<class STestWidgetThree> gameSlateWidget;
	TSharedPtr<class SWeakWidget> slateWidgetContainerTwo; // we use this container to remove and add the menu to the screen. weakWidgets cannot own their content, does this mean I must make these UProperties? probably not everything has worked so far

	TSharedPtr<class SSArcadeModeTitleScreen> mainMenuSlateWidget;
	TSharedPtr<class SWeakWidget> slateWidgetContainerThree;

	TSharedPtr<class SCurtains> curtainsSlateWidget;
	TSharedPtr<class SWidget> slateWidgetContainerFour;

	TSharedPtr<class SCurtainsTwo> curtainsTwoSlateWidget;
	TSharedPtr<class SWidget> slateWidgetContainerFive;

	TSharedPtr<class SResultsBlur> resultsBlurSlateWidget;
	TSharedPtr<class SWeakWidget> slateWidgetContainerSix;

	TSharedPtr<class SCompanySplash> splashScreenSlateWidget;
	TSharedPtr<class SWidget> slateWidgetContainerSeven;

	TSharedPtr<class SPauseScreen> pauseScreenSlateWidget;
	TSharedPtr<class SWidget> slateWidgetContainerEight;

	TSharedPtr<class SOptions> optionsMenuSlateWidget;
	TSharedPtr<class SWidget> slateWidgetContainerNine;

	virtual void BeginPlay() override;

public:
	UPROPERTY() APlayerController* playerOnePlayerController;
	UPROPERTY() UObject* standardWorldContextObject;

	//level randomizer algorithm stuff
	UPROPERTY() TArray<FVector2D> arrOfViableHoleCoordinates;
	UPROPERTY() TArray<FVector2D> arrOfViableHoleCoordinatesBase = { FVector2D(12, 2), FVector2D(12, 1), FVector2D(11, 2), FVector2D(11, 1), FVector2D(10, 2), FVector2D(10, 1), FVector2D(9, 2), FVector2D(9, 1), FVector2D(8, 2), FVector2D(8, 1), FVector2D(7, 2), FVector2D(7, 1), FVector2D(6, 2), FVector2D(6, 1), FVector2D(5, 2), FVector2D(5, 1), FVector2D(4, 2), FVector2D(4, 1) };
	UPROPERTY() TArray<FVector2D> holePositions;
	UPROPERTY() TArray<FVector2D> convertedHolePositions;

	UPROPERTY() int negativeOneZeroOrOne;

	UPROPERTY() TArray<int> test;
	UPROPERTY() TArray<int> listOfHolePositionGroupings;

	UPROPERTY() int holeCoordinateOrientation;
	UPROPERTY() int numberOfHoles = 10;
	UPROPERTY() int holesToGenerate;

	UPROPERTY() FVector2D startingPos;
	UPROPERTY() int startingDir;

	TArray<TArray<int>> nestedTArr;

	UPROPERTY() int extentOfAdjustment = 2 - FMath::Clamp(numberOfHoles - 8, 0, 1);

	UPROPERTY() TArray<int> regenerateLevel;

	UPROPERTY() TArray<UMaterial*> backgroundMaterials;
	UPROPERTY() bool backgroundIsLargeTile;
	UPROPERTY() bool inGame;

	UPROPERTY() bool goToResults;
	UPROPERTY() bool fromGame;

	UPROPERTY() int environmentAudio;

	UPROPERTY() double masterCoefficient;
	UPROPERTY() double masterCoefficientM;
	UPROPERTY() double masterCoefficientA;
	UPROPERTY() double masterCoefficientS;
	UPROPERTY() double musicCoefficient;
	UPROPERTY() double atmosphereCoefficient;
	UPROPERTY() double sfxCoefficient;
	UPROPERTY() double pingCoefficient;
	UPROPERTY() double destinationCoefficientM;
	UPROPERTY() double destinationCoefficientA;
	UPROPERTY() double destinationCoefficientS;

	UPROPERTY() TArray<UMediaPlayer*> mediaPlayersToClose;

	TArray< TArray <int> > chordIndexes = { { 0, 2, 4 }, { 1, 3, 5 }, { 2, 4, 6 }, { 4, 6, 7 } };// I could easily make this single dimensional if I need to

	UPROPERTY() TArray<bool> activeMediaPlayers = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

	TArray<TArray<TArray<FVector2D> > > holeAndIntersectionPositions =
	{
		{
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) }
		},
		{
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) }
		},
		{
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) }
		},
		{
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) }
		},
		{
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) }
		},
		{
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) }
		},
		{
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) }
		},
		{
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) }
		}
	};

	TArray<TArray<TArray<int> > > arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection =
	{
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 }
		}
	};

	TArray<TArray<TArray<int> > > adjustmentsAppliedToEachIntersection =
	{// 0 is none, 1 is first of pair, 2 is second of pair, 3 signifies 1st of pair is being adjusted to correct for directions of intersections in the pair being on opposite sides
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	};

	TArray<TArray<TArray<int> > > intersectionOrientationsPerGroupPerLevel =
	{// 0 for right, 1 for left, 2 for straight, all coming from the perspective of the previous hole or intersection
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	};

	TArray<TArray<TArray<int> > > firstOfPairIsAboveSecondAllPairs =
	{
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	};

	TArray<TArray<TArray<int> > > firstOfPairIsEvenWithOrLeftOfSecondAllPairs =
	{
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	};

	TArray<TArray<TArray<TArray<int> > > > turnAndIntersectionDistancesPerPair =
	{
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		}
	};

	TArray<TArray<TArray<TArray<int> > > > directionsOfTurns =
	{//0 for right, 1 for left. and then a 2 for the intersection?.. and a 3 for straightTrack? whaat? **currently im using the intersectionOrientations to determine whether or not a intersection position should be straight track, there should not be any 3s in this arr
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		}
	};

	UPROPERTY() TArray<int> landscapeArr = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	UPROPERTY() TArray<int> trackArr = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	UPROPERTY() TArray<bool> tileIsIntersection = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

	UPROPERTY() TArray<int> tileIsTrack = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	UPROPERTY() TArray<int> backgroundArr = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	UPROPERTY() TArray<FVector2D> pondPositionArr;
	UPROPERTY() TArray<int> pondSpecifierArr;
	UPROPERTY() TArray<FVector2D> largeTreeOrMountainPosArr;

	void MasterGenerateLevel(int numHoles);

	void GenerateLevel();

	void GenerateHolePositions();

	void GenerateTrackShape();

	void BuildLevel();

	void HouseKeeping();

	void ResetRegenLevel();

	void GenerateMainMenuBackground();

	void DisplayCurtains(int integerOne, bool goingToGame = true, bool displayResults = false);

	void HideCurtains(bool toGame = true);

	void PreLoadCurtains();

	void ReturnToMainMenu();

	void RemoveResultsBlur();

	void SaveGame(int maxLevel, TArray <int> highscores, int highscoreDataOne, int highscoreDataTwo, int scoreThisGame);

	void DestroySplash();

	void DisplayPauseScreen();

	void DestroyPauseScreen();

	void PrepDestroyPauseScreen();

	void DisplayOptionsMenu(bool cameFromGame);

	void DestroyOptionsMenu();

	void SetFocusToGame();

	void CommitMaster(int newVol);
	void CommitMusic(int newVol);
	void CommitAtmosphere(int newVol);
	void CommitSFX(int newVol);
};