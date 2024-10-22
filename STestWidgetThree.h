// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MyHUD.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "Widgets/SPanel.h"
#include "Delegates/Delegate.h"
#include "GameFramework/GameUserSettings.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Images/SImage.h"
#include "SaveGameOne.h"
#include "Widgets/SOverlay.h"
#include "Widgets/Layout/SBackgroundBlur.h"
#include "Materials/MaterialInterface.h"
#include "Framework/Application/SlateApplication.h"
//#include "Engine/Classes/Materials/Material.h"

/**
 * 
 */
class STestWidgetThree : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(STestWidgetThree) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwningHUD)

	SLATE_ARGUMENT(UObject*, standardWorldContextObject)

	SLATE_ARGUMENT(TArray<int>, landscapeArr)

	SLATE_ARGUMENT(TArray<int>, trackArr)

	SLATE_ARGUMENT(TArray<int>, pondSpecifierArr)

	SLATE_ARGUMENT(TArray<FVector2D>, pondPositionArr)

	SLATE_ARGUMENT(TArray<bool>, tileIsIntersection)

	SLATE_ARGUMENT(APlayerController*, playerOnePlayerController)

	SLATE_ARGUMENT(FVector2D, startingPos)

	SLATE_ARGUMENT(int, startingDir)

	SLATE_ARGUMENT(TArray<FVector2D>, holePositions)

	SLATE_ARGUMENT(UMaterial*, grass_VMUI_1)

	SLATE_ARGUMENT(UMaterial*, grass_VMUI_2)

	SLATE_ARGUMENT(UMaterial*, grass_VMUI_3)

	SLATE_ARGUMENT(UMaterial*, pondHorizontal_VMUI)

	SLATE_ARGUMENT(UMaterial*, pondVerticleFlowingLeft_VMUI)

	SLATE_ARGUMENT(UMaterial*, pondVerticleFlowingRight_VMUI)

	SLATE_ARGUMENT(UMaterial*, riverFlowingDown_VMUI_1)

	SLATE_ARGUMENT(UMaterial*, riverFlowingDown_VMUI_2)

	SLATE_ARGUMENT(UMaterial*, riverFlowingDown_VMUI_3)

	SLATE_ARGUMENT(UMaterial*, riverFlowingLeft_VMUI_1)

	SLATE_ARGUMENT(UMaterial*, riverFlowingLeft_VMUI_2)

	SLATE_ARGUMENT(UMaterial*, riverFlowingLeft_VMUI_3)

	SLATE_ARGUMENT(UMaterial*, riverFlowingRight_VMUI_1)

	SLATE_ARGUMENT(UMaterial*, riverFlowingRight_VMUI_2)

	SLATE_ARGUMENT(UMaterial*, riverFlowingRight_VMUI_3)

	SLATE_ARGUMENT(UMaterial*, tree_VMUI_1)

	SLATE_ARGUMENT(UMaterial*, tree_VMUI_2)

	SLATE_ARGUMENT(UMaterial*, tree_VMUI_3)

	SLATE_ARGUMENT(UMaterial*, tree_VMUI_4)

	SLATE_ARGUMENT(UMaterial*, tree_VMUI_5)

	SLATE_ARGUMENT(UMaterial*, waterfall_VMUI)

	SLATE_ARGUMENT(UMaterial*, riverTurning_VMUI_1)

	SLATE_ARGUMENT(UMaterial*, riverTurning_VMUI_2)

	SLATE_ARGUMENT(UMaterial*, riverTurning_VMUI_3)

	SLATE_ARGUMENT(UMaterial*, riverTurning_VMUI_4)

	SLATE_ARGUMENT(UMaterial*, mountain_VMUI_1)

	SLATE_ARGUMENT(UMaterial*, holeFromDown_VMUI)

	SLATE_ARGUMENT(UMaterial*, holeFromLeft_VMUI)

	SLATE_ARGUMENT(UMaterial*, holeFromRight_VMUI)

	SLATE_ARGUMENT(UMaterial*, holeFromUp_VMUI)

	SLATE_ARGUMENT(UMaterial*, flag_VMUI_1)

	SLATE_ARGUMENT(UMaterial*, flag_VMUI_2)

	SLATE_ARGUMENT(UMaterial*, flag_VMUI_3)

	SLATE_ARGUMENT(UMaterial*, flag_VMUI_4)

	SLATE_ARGUMENT(UMaterial*, flag_VMUI_5)

	SLATE_ARGUMENT(UMaterial*, flag_VMUI_6)

	SLATE_ARGUMENT(UMaterial*, flag_VMUI_7)

	SLATE_ARGUMENT(UMaterial*, flag_VMUI_8)

	SLATE_ARGUMENT(UMaterial*, flag_VMUI_9)

	SLATE_ARGUMENT(UMaterial*, flag_VMUI_10)

	SLATE_ARGUMENT(UMaterial*, flag_VMUI_11)

	SLATE_ARGUMENT(UMaterial*, flag_VMUI_12)

	SLATE_ARGUMENT(UMaterial*, flag_VMUI_13)

	SLATE_ARGUMENT(UMaterial*, flag_VMUI_14)

	SLATE_ARGUMENT(UMaterial*, flag_VMUI_15)

	SLATE_ARGUMENT(UMaterial*, flag_VMUI_16)

	SLATE_ARGUMENT(UMaterial*, buttonFromDownTurningRightZero_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromDownTurningRightOne_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromDownTurningRightTwo_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromDownTurningRightThree_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromDownTurningLeftZero_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromDownTurningLeftOne_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromDownTurningLeftTwo_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromDownTurningLeftThree_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromLeftTurningRightZero_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromLeftTurningRightOne_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromLeftTurningRightTwo_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromLeftTurningRightThree_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromLeftTurningLeftZero_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromLeftTurningLeftOne_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromLeftTurningLeftTwo_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromLeftTurningLeftThree_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromRightTurningRightZero_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromRightTurningRightOne_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromRightTurningRightTwo_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromRightTurningRightThree_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromRightTurningLeftZero_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromRightTurningLeftOne_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromRightTurningLeftTwo_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromRightTurningLeftThree_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromUpTurningRightZero_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromUpTurningRightOne_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromUpTurningRightTwo_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromUpTurningRightThree_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromUpTurningLeftZero_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromUpTurningLeftOne_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromUpTurningLeftTwo_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromUpTurningLeftThree_SMUI)

	SLATE_ARGUMENT(UMaterial*, verticleRail_SMUI)

	SLATE_ARGUMENT(UMaterial*, horizontalRail_SMUI)

	SLATE_ARGUMENT(UMaterial*, railTurningOne_SMUI)

	SLATE_ARGUMENT(UMaterial*, railTurningTwo_SMUI)

	SLATE_ARGUMENT(UMaterial*, railTurningThree_SMUI)

	SLATE_ARGUMENT(UMaterial*, railTurningFour_SMUI)

	SLATE_ARGUMENT(UMaterial*, marble_SMUI_1)

	SLATE_ARGUMENT(UMaterial*, marble_SMUI_2)

	SLATE_ARGUMENT(UMaterial*, marble_SMUI_3)

	SLATE_ARGUMENT(UMaterial*, marble_SMUI_4)

	SLATE_ARGUMENT(UMaterial*, marble_SMUI_5)

	SLATE_ARGUMENT(UMaterial*, marble_SMUI_6)

	SLATE_ARGUMENT(UMaterial*, marble_SMUI_7)

	SLATE_ARGUMENT(UMaterial*, marble_SMUI_8)

	SLATE_ARGUMENT(UMaterial*, marble_SMUI_9)

	SLATE_ARGUMENT(UMaterial*, marble_SMUI_10)

	SLATE_ARGUMENT(UMaterial*, marble_SMUI_11)

	SLATE_ARGUMENT(UMaterial*, marble_SMUI_12)

	SLATE_ARGUMENT(UMaterial*, marble_SMUI_13)

	SLATE_ARGUMENT(UMaterial*, marble_SMUI_14)

	SLATE_ARGUMENT(UMaterial*, marble_SMUI_15)

	SLATE_ARGUMENT(UMaterial*, marble_SMUI_16)

	SLATE_ARGUMENT(UMaterial*, gameFrameColor_SMUI)

	SLATE_ARGUMENT(UMaterial*, emptyImg_SMUI)

	SLATE_ARGUMENT(UAudioComponent*, intersectionDownAudioComponent)

	SLATE_ARGUMENT(UAudioComponent*, intersectionUpAudioComponent)

	SLATE_ARGUMENT(TArray <UAudioComponent*>, windAudioComponents)

	SLATE_ARGUMENT(TArray <UAudioComponent*>, riverAudioComponents)

	SLATE_ARGUMENT(TArray <UAudioComponent*>, waterfallAudioComponents)

	SLATE_ARGUMENT(TArray <UAudioComponent*>, scoringAudioComponents)

	SLATE_ARGUMENT(UAudioComponent*, missAudioComponent)

	SLATE_ARGUMENT(TArray <UAudioComponent*>, songAudioComponents)

	SLATE_ARGUMENT(int, environmentAudio)

	SLATE_ARGUMENT(bool, songPlaying)

	SLATE_ARGUMENT(int, songPlayingIndex)

	//SLATE_ARGUMENT(FVector2D, viewportSize)

	SLATE_END_ARGS()

	//every widget needs a construction function
	void Construct(const FArguments& InArgs);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

	FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);

	virtual bool IsInteractable() const override { return true; };
	virtual bool SupportsKeyboardFocus() const override { return true; };

	void OnIntersectionPressedOne();
	void OnIntersectionReleasedOne();
	void OnIntersectionPressedTwo();
	void OnIntersectionReleasedTwo();
	void OnIntersectionPressedThree();
	void OnIntersectionReleasedThree();
	void OnIntersectionPressedFour();
	void OnIntersectionReleasedFour();
	void OnIntersectionPressedFive();
	void OnIntersectionReleasedFive();
	void OnIntersectionPressedSix();
	void OnIntersectionReleasedSix();
	void OnIntersectionPressedSeven();
	void OnIntersectionReleasedSeven();
	void OnIntersectionPressedEight();
	void OnIntersectionReleasedEight();
	void OnIntersectionPressedNine();
	void OnIntersectionReleasedNine();
	void OnIntersectionPressedTen();
	void OnIntersectionReleasedTen();
	void OnIntersectionPressedEleven();
	void OnIntersectionReleasedEleven();
	void OnIntersectionPressedTwelve();
	void OnIntersectionReleasedTwelve();
	void OnIntersectionPressedThirteen();
	void OnIntersectionReleasedThirteen();
	void OnIntersectionPressedFourteen();
	void OnIntersectionReleasedFourteen();
	void OnIntersectionPressedFifteen();
	void OnIntersectionReleasedFifteen();
	void OnIntersectionPressedSixteen();
	void OnIntersectionReleasedSixteen();
	void OnIntersectionPressedSeventeen();
	void OnIntersectionReleasedSeventeen();

	//float CalculateGrownMarginX(FMargin inMargin);
	float CalculateAdjustedCountdownMargin(FMargin inMargin);
	FMargin GrowCountdownMargin(FMargin inMargin);

	void PlayGame();

	UPROPERTY(SaveGame) USaveGameOne* currentSave;
	UPROPERTY(SaveGame) USaveGameOne* lastSave;

	FVector2D PrepTurnMarble(int currentMarble, FVector2d marblePosition, int dirOfMarble, bool isIntersection, int trackArrValue);
	FVector2D TurnMarble(int currentMarble, FVector2D marblePosition);
	FMargin ShrinkMarble(FMargin inPadding, double factorOfShrinkage);

	// constructor variables

	UPROPERTY() TWeakObjectPtr<class AMyHUD> OwningHUD;
	UPROPERTY() UObject* standardWorldContextObject;

	UPROPERTY() TArray<int> landscapeArr;
	UPROPERTY() TArray<int> trackArr;
	UPROPERTY() TArray<int> pondSpecifierArr;
	UPROPERTY() TArray<FVector2D> pondPositionArr;
	UPROPERTY() TArray<bool> tileIsIntersection;
	UPROPERTY() TArray<FVector2D> holePositions;

	UPROPERTY() APlayerController* playerOnePlayerController;

	UPROPERTY() UMaterial* grass_VMUI_1;
	UPROPERTY() UMaterial* grass_VMUI_2;
	UPROPERTY() UMaterial* grass_VMUI_3;
	UPROPERTY() UMaterial* pondHorizontal_VMUI;
	UPROPERTY() UMaterial* pondVerticleFlowingLeft_VMUI;
	UPROPERTY() UMaterial* pondVerticleFlowingRight_VMUI;
	UPROPERTY() UMaterial* riverFlowingDown_VMUI_1;
	UPROPERTY() UMaterial* riverFlowingDown_VMUI_2;
	UPROPERTY() UMaterial* riverFlowingDown_VMUI_3;
	UPROPERTY() UMaterial* riverFlowingLeft_VMUI_1;
	UPROPERTY() UMaterial* riverFlowingLeft_VMUI_2;
	UPROPERTY() UMaterial* riverFlowingLeft_VMUI_3;
	UPROPERTY() UMaterial* riverFlowingRight_VMUI_1;
	UPROPERTY() UMaterial* riverFlowingRight_VMUI_2;
	UPROPERTY() UMaterial* riverFlowingRight_VMUI_3;
	UPROPERTY() UMaterial* tree_VMUI_1;
	UPROPERTY() UMaterial* tree_VMUI_2;
	UPROPERTY() UMaterial* tree_VMUI_3;
	UPROPERTY() UMaterial* tree_VMUI_4;
	UPROPERTY() UMaterial* tree_VMUI_5;
	UPROPERTY() UMaterial* waterfall_VMUI;
	UPROPERTY() UMaterial* riverTurning_VMUI_1;
	UPROPERTY() UMaterial* riverTurning_VMUI_2;
	UPROPERTY() UMaterial* riverTurning_VMUI_3;
	UPROPERTY() UMaterial* riverTurning_VMUI_4;

	UPROPERTY() UMaterial* mountain_VMUI_1;

	UPROPERTY() UMaterial* holeFromDown_VMUI;
	UPROPERTY() UMaterial* holeFromLeft_VMUI;
	UPROPERTY() UMaterial* holeFromRight_VMUI;
	UPROPERTY() UMaterial* holeFromUp_VMUI;

	UPROPERTY() UMaterial* flag_VMUI_1;
	UPROPERTY() UMaterial* flag_VMUI_2;
	UPROPERTY() UMaterial* flag_VMUI_3;
	UPROPERTY() UMaterial* flag_VMUI_4;
	UPROPERTY() UMaterial* flag_VMUI_5;
	UPROPERTY() UMaterial* flag_VMUI_6;
	UPROPERTY() UMaterial* flag_VMUI_7;
	UPROPERTY() UMaterial* flag_VMUI_8;
	UPROPERTY() UMaterial* flag_VMUI_9;
	UPROPERTY() UMaterial* flag_VMUI_10;
	UPROPERTY() UMaterial* flag_VMUI_11;
	UPROPERTY() UMaterial* flag_VMUI_12;
	UPROPERTY() UMaterial* flag_VMUI_13;
	UPROPERTY() UMaterial* flag_VMUI_14;
	UPROPERTY() UMaterial* flag_VMUI_15;
	UPROPERTY() UMaterial* flag_VMUI_16;

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

	UPROPERTY() UMaterial* emptyImg_SMUI;

	//variables and data structures associated with constructor vars
	UPROPERTY() UMaterial* placeholderTrash;

	//slate brushes
	UPROPERTY() FSlateBrush* grass_SB_1;
	UPROPERTY() FSlateBrush* grass_SB_2;
	UPROPERTY() FSlateBrush* grass_SB_3;
	UPROPERTY() FSlateBrush* pondHorizontal_SB;
	UPROPERTY() FSlateBrush* pondVerticleFlowingLeft_SB;
	UPROPERTY() FSlateBrush* pondVerticleFlowingRight_SB;
	UPROPERTY() FSlateBrush* riverFlowingDown_SB_1;
	UPROPERTY() FSlateBrush* riverFlowingDown_SB_2;
	UPROPERTY() FSlateBrush* riverFlowingDown_SB_3;
	UPROPERTY() FSlateBrush* riverFlowingLeft_SB_1;
	UPROPERTY() FSlateBrush* riverFlowingLeft_SB_2;
	UPROPERTY() FSlateBrush* riverFlowingLeft_SB_3;
	UPROPERTY() FSlateBrush* riverFlowingRight_SB_1;
	UPROPERTY() FSlateBrush* riverFlowingRight_SB_2;
	UPROPERTY() FSlateBrush* riverFlowingRight_SB_3;
	UPROPERTY() FSlateBrush* tree_SB_1;
	UPROPERTY() FSlateBrush* tree_SB_2;
	UPROPERTY() FSlateBrush* tree_SB_3;
	UPROPERTY() FSlateBrush* tree_SB_4;
	UPROPERTY() FSlateBrush* tree_SB_5;
	UPROPERTY() FSlateBrush* waterfall_SB;
	UPROPERTY() FSlateBrush* riverTurning_SB_1;
	UPROPERTY() FSlateBrush* riverTurning_SB_2;
	UPROPERTY() FSlateBrush* riverTurning_SB_3;
	UPROPERTY() FSlateBrush* riverTurning_SB_4;

	UPROPERTY() FSlateBrush* mountain_SB_1;

	UPROPERTY() FSlateBrush* holeFromDown_SB;
	UPROPERTY() FSlateBrush* holeFromLeft_SB;
	UPROPERTY() FSlateBrush* holeFromRight_SB;
	UPROPERTY() FSlateBrush* holeFromUp_SB;

	UPROPERTY() FSlateBrush* flag_SB_1;
	UPROPERTY() FSlateBrush* flag_SB_2;
	UPROPERTY() FSlateBrush* flag_SB_3;
	UPROPERTY() FSlateBrush* flag_SB_4;
	UPROPERTY() FSlateBrush* flag_SB_5;
	UPROPERTY() FSlateBrush* flag_SB_6;
	UPROPERTY() FSlateBrush* flag_SB_7;
	UPROPERTY() FSlateBrush* flag_SB_8;
	UPROPERTY() FSlateBrush* flag_SB_9;
	UPROPERTY() FSlateBrush* flag_SB_10;
	UPROPERTY() FSlateBrush* flag_SB_11;
	UPROPERTY() FSlateBrush* flag_SB_12;
	UPROPERTY() FSlateBrush* flag_SB_13;
	UPROPERTY() FSlateBrush* flag_SB_14;
	UPROPERTY() FSlateBrush* flag_SB_15;
	UPROPERTY() FSlateBrush* flag_SB_16;

	UPROPERTY() FSlateBrush* buttonFromDownTurningRightZero_SB;
	UPROPERTY() FSlateBrush* buttonFromDownTurningRightOne_SB;
	UPROPERTY() FSlateBrush* buttonFromDownTurningRightTwo_SB;
	UPROPERTY() FSlateBrush* buttonFromDownTurningRightThree_SB;
	UPROPERTY() FSlateBrush* buttonFromDownTurningLeftZero_SB;
	UPROPERTY() FSlateBrush* buttonFromDownTurningLeftOne_SB;
	UPROPERTY() FSlateBrush* buttonFromDownTurningLeftTwo_SB;
	UPROPERTY() FSlateBrush* buttonFromDownTurningLeftThree_SB;
	UPROPERTY() FSlateBrush* buttonFromLeftTurningRightZero_SB;
	UPROPERTY() FSlateBrush* buttonFromLeftTurningRightOne_SB;
	UPROPERTY() FSlateBrush* buttonFromLeftTurningRightTwo_SB;
	UPROPERTY() FSlateBrush* buttonFromLeftTurningRightThree_SB;
	UPROPERTY() FSlateBrush* buttonFromLeftTurningLeftZero_SB;
	UPROPERTY() FSlateBrush* buttonFromLeftTurningLeftOne_SB;
	UPROPERTY() FSlateBrush* buttonFromLeftTurningLeftTwo_SB;
	UPROPERTY() FSlateBrush* buttonFromLeftTurningLeftThree_SB;
	UPROPERTY() FSlateBrush* buttonFromRightTurningRightZero_SB;
	UPROPERTY() FSlateBrush* buttonFromRightTurningRightOne_SB;
	UPROPERTY() FSlateBrush* buttonFromRightTurningRightTwo_SB;
	UPROPERTY() FSlateBrush* buttonFromRightTurningRightThree_SB;
	UPROPERTY() FSlateBrush* buttonFromRightTurningLeftZero_SB;
	UPROPERTY() FSlateBrush* buttonFromRightTurningLeftOne_SB;
	UPROPERTY() FSlateBrush* buttonFromRightTurningLeftTwo_SB;
	UPROPERTY() FSlateBrush* buttonFromRightTurningLeftThree_SB;
	UPROPERTY() FSlateBrush* buttonFromUpTurningRightZero_SB;
	UPROPERTY() FSlateBrush* buttonFromUpTurningRightOne_SB;
	UPROPERTY() FSlateBrush* buttonFromUpTurningRightTwo_SB;
	UPROPERTY() FSlateBrush* buttonFromUpTurningRightThree_SB;
	UPROPERTY() FSlateBrush* buttonFromUpTurningLeftZero_SB;
	UPROPERTY() FSlateBrush* buttonFromUpTurningLeftOne_SB;
	UPROPERTY() FSlateBrush* buttonFromUpTurningLeftTwo_SB;
	UPROPERTY() FSlateBrush* buttonFromUpTurningLeftThree_SB;

	UPROPERTY() FSlateBrush* verticleRail_SB;
	UPROPERTY() FSlateBrush* horizontalRail_SB;

	UPROPERTY() FSlateBrush* railTurningOne_SB;
	UPROPERTY() FSlateBrush* railTurningTwo_SB;
	UPROPERTY() FSlateBrush* railTurningThree_SB;
	UPROPERTY() FSlateBrush* railTurningFour_SB;

	UPROPERTY() FSlateBrush* marble_SB_1;
	UPROPERTY() FSlateBrush* marble_SB_2;
	UPROPERTY() FSlateBrush* marble_SB_3;
	UPROPERTY() FSlateBrush* marble_SB_4;
	UPROPERTY() FSlateBrush* marble_SB_5;
	UPROPERTY() FSlateBrush* marble_SB_6;
	UPROPERTY() FSlateBrush* marble_SB_7;
	UPROPERTY() FSlateBrush* marble_SB_8;
	UPROPERTY() FSlateBrush* marble_SB_9;
	UPROPERTY() FSlateBrush* marble_SB_10;
	UPROPERTY() FSlateBrush* marble_SB_11;
	UPROPERTY() FSlateBrush* marble_SB_12;
	UPROPERTY() FSlateBrush* marble_SB_13;
	UPROPERTY() FSlateBrush* marble_SB_14;
	UPROPERTY() FSlateBrush* marble_SB_15;
	UPROPERTY() FSlateBrush* marble_SB_16;

	UPROPERTY() FSlateBrush* gameFrameColor_SB;

	UPROPERTY() FSlateBrush* emptyImg_SB;

	TArray<TArray<TArray<UMaterial*> > > intersectionButtons =
	{ // 0 for right, 1 for left, 2 for straight(which means horizontal track for the even indices and verticle track for the odd indices
		{//index 0
			{ placeholderTrash }
		},
		{//index 1
			{ buttonFromDownTurningRightZero_SMUI },
			{ buttonFromDownTurningLeftZero_SMUI }
		},
		{//index 2
			{ buttonFromLeftTurningRightZero_SMUI },
			{ buttonFromLeftTurningLeftZero_SMUI }
		},
		{//index 3
			{ buttonFromUpTurningRightZero_SMUI },
			{ buttonFromUpTurningLeftZero_SMUI }
		},
		{//index 4
			{ buttonFromRightTurningRightZero_SMUI },
			{ buttonFromRightTurningLeftZero_SMUI }
		}
	};

	UPROPERTY() TArray<FSlateBrush*> landscapeStuff;
	UPROPERTY() TArray<FSlateBrush*> trackStuff;
	UPROPERTY() TArray<FSlateBrush*> flags;
	UPROPERTY() TArray<FSlateBrush*> relevantFlags;
	UPROPERTY() TArray<FSlateBrush*> flagsRandomized;
	UPROPERTY() TArray<FSlateBrush*> marbles;
	UPROPERTY() TArray<FSlateBrush*> relevantMarbles;
	UPROPERTY() TArray<FSlateBrush*> marblesRandomized;

	UPROPERTY() UAudioComponent* intersectionDownAudioComponent;
	UPROPERTY() UAudioComponent* intersectionUpAudioComponent;

	UPROPERTY() TArray<UAudioComponent*> windAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> riverAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> waterfallAudioComponents;
	UPROPERTY() TArray<UAudioComponent*> scoringAudioComponents;

	UPROPERTY() UAudioComponent* missAudioComponent;
	UPROPERTY() TArray<UAudioComponent*> songAudioComponents;

	//UPROPERTY() UAudioComponent* songOneAudioComponent;
	UPROPERTY() bool songPlaying;
	UPROPERTY() bool songBool;

	UPROPERTY() FVector2D startingPos;
	UPROPERTY() int startingDir;

	// misc variables and data structures

	UPROPERTY() FString materialPath = FPaths::ProjectContentDir() / TEXT("/Game/Movies/videoMaterialsForUI/grass_VMUI_1");

	UPROPERTY() FVector2D viewportSize;
	UPROPERTY() FVector2D adjustedViewportSize;

	UPROPERTY() FMargin testFMargin;

	UPROPERTY() FButtonStyle* masterButtonStyle;

public: 
	UPROPERTY() TSharedPtr<class SWindow> windowOne;
	UPROPERTY() TArray<TSharedPtr<class SBox>> activeMarbles;
	UPROPERTY() TArray<TSharedPtr<class SBox>> marblesToBeDestroyed;
	UPROPERTY() TArray<FSlateBrush*> activeMarblesContent;
	UPROPERTY() TArray<FSlateBrush*> marblesThisGame;
	UPROPERTY() TArray<int> marblesThisGameProxy;
	UPROPERTY() TArray<int> marblesThisGameProxyTracker;
	UPROPERTY() int marbleProxyIndexToAdd;
	UPROPERTY() int marbleIndexToAdd;
	UPROPERTY() int marbleIndexToSpawn;
	UPROPERTY() int marbleIndexToDelete;
	UPROPERTY() TArray <int> marbleIndexesBeingAdded;
	UPROPERTY() TArray<double> marblesBeingDestroyedTime;
	UPROPERTY() TArray<FMargin> marblesShrinking;
	UPROPERTY() TSharedPtr<class STextBlock>  scoreText;
	UPROPERTY() FText currentScore;
	UPROPERTY() int playerScore = 0;
	UPROPERTY() int maximumPossibleScore = 0;
	UPROPERTY() FSlateFontInfo scoreTextStyle;
	UPROPERTY() TSharedPtr<class STextBlock>  timeText;
	UPROPERTY() FText currentTimeText;
	UPROPERTY() TSharedPtr< class SOverlay> marbleOverlay;
	UPROPERTY() TSharedPtr< class FOverlaySlot> marbleOneSlot;
	UPROPERTY() TSharedPtr<class STextBlock>  countdownText;
	UPROPERTY() TSharedPtr<class SBox>  countdownBox;
	UPROPERTY() FSlateFontInfo countdownFont;

	UPROPERTY() TSharedPtr<class SOverlay> largeTilesOverlay;
	UPROPERTY() TSharedPtr<class SOverlay> landscapeOverlay;
	UPROPERTY() TSharedPtr<class SOverlay> trackOverlay;
	UPROPERTY() TSharedPtr<class SOverlay> intersectionButtonsOverlay;
	UPROPERTY() TSharedPtr<class SOverlay> flagsOverlay;
	UPROPERTY() TSharedPtr<class SOverlay> frameColorOverlay;
	UPROPERTY() TSharedPtr<class SOverlay> pauseOverlay;
	UPROPERTY() TSharedPtr<class SOverlay> countdownOverlay;

	UPROPERTY() TSharedPtr<class SBackgroundBlur> pauseBlur;

	UPROPERTY() TArray<TArray<FSlateBrush*> > intersections;
	UPROPERTY() TArray<int> intersectionsKeys;
	UPROPERTY() TArray<int> intersectionCycle;
	UPROPERTY() TArray< TSharedPtr<class SImage> > intersectionImages;
	UPROPERTY() TArray<FVector2D> intersectionPositions;

	UPROPERTY() float DPIScale;

	UPROPERTY() FVector2D screenPosition;
	UPROPERTY() FVector2D screenSize;

	UPROPERTY() float viewportX = 0.0f;
	UPROPERTY() float viewportY = 0.0f;
	UPROPERTY() int deleteMe;
	UPROPERTY() TArray<FVector2D> marblePositions;
	UPROPERTY() TArray<FVector2D> marblesToBeDestroyedPosition;
	UPROPERTY() TArray<FVector2D> marblePositionsCenters;//you need to change this from the center of the marbles "tile" to what appears to be the center of the marble
	UPROPERTY() TArray<FVector2D> previousTickMarblePositionsCenters;
	UPROPERTY() int currentIntersection = 1;
	UPROPERTY() TArray<int> startingMarbleMovementTracker = { { 0, 0 } };
	UPROPERTY() TArray<TArray<int> > marbleMovementTracker;
	UPROPERTY() TArray<TArray<int> > marblesToBeDestroyedMovementTracker;
	UPROPERTY() TArray<bool> marbleIsTurning;
	UPROPERTY() TArray<int> turnToExecute;
	UPROPERTY() TArray<int> dirOfMarbles;
	UPROPERTY() TArray<FVector2D> deltaMarblePos;
	UPROPERTY() int quantityOfMarbles;

	UPROPERTY() int timeOfGame = 120;
	UPROPERTY() double startingTime = 0;
	UPROPERTY() double fCurrentTime = 0;
	UPROPERTY() int currentTime = 120;
	UPROPERTY() double spawningWindow;
	UPROPERTY() TArray<double> timeIntoWindowMarbleIsSpawned;
	UPROPERTY() bool gameStarted = false;
	UPROPERTY() bool gameEnded;
	UPROPERTY() double speedMultiplier;
	UPROPERTY() double timeToCoverOneTileDividedByTwo;

	UPROPERTY() FMargin marbleToBeDestroyedPadding;

	UPROPERTY() bool threeDisplayed;
	UPROPERTY() bool twoDisplayed;
	UPROPERTY() bool oneDisplayed;
	UPROPERTY() bool goDisplayed;

	UPROPERTY() float standardFontSize;
	UPROPERTY() float startingFontSize;
	UPROPERTY() float growingFontSize;
	UPROPERTY() float adjustedStartingFontSize;
	UPROPERTY() float startingOpacity;
	UPROPERTY() float growingOpacity;
	UPROPERTY() float adjustedStartingOpacity;
	UPROPERTY() FSlateFontInfo shiftingFont;
	UPROPERTY() TSharedPtr<class STextBlock> growingText;
	UPROPERTY() TSharedPtr<class SBox> growingBox;
	UPROPERTY() FMargin countdownMargin;
	UPROPERTY() FMargin startingMargin;
	UPROPERTY() FMargin growingMargin;
	UPROPERTY() float adjustedCountdownMargin;
	UPROPERTY() float countdownEffectClock;

	UPROPERTY() int finalScore;
	UPROPERTY() TArray <int> highscores;
	UPROPERTY() int maxLevel;
	UPROPERTY() int highscoreDataOne;
	UPROPERTY() int highscoreDataTwo;
	UPROPERTY() int scoreThisGame;

	UPROPERTY() int environmentAudio;
	UPROPERTY() float audioTimer;
	UPROPERTY() int audioCycleTracker;

	UPROPERTY() int scoringSoundEffectIndex;

	UPROPERTY() bool paused;
	UPROPERTY() int songPlayingIndex;
};
