// Fill out your copyright notice in the Description page of Project Settings.


#include "STestWidgetThree.h"
#include "SlateOptMacros.h"
#include "GameFramework/Actor.h"
#include "Math/Vector2D.h"
#include "Layout/Geometry.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#define LOCTEXT_NAMESPACE "TestSlate"
//UE_DISABLE_OPTIMIZATION

const FMargin CalculateTilePosition(FVector2D tileCoords, FVector2D adjustedViewportSize)//this has been adjusted to respond to 1D arr coordinates
{//this will only work if screenSize.X >= screenSize.Y
	float viewportX = adjustedViewportSize.X;
	float viewportY = adjustedViewportSize.Y;
	float fOne = (viewportX - viewportY) / 2;
	float leftPad = fOne + (viewportY / 15) * tileCoords.X;
	float topPad = (viewportY / 15) * tileCoords.Y;
	float rightPad = fOne + (viewportY / 15) * (15 - (tileCoords.X + 1));
	float bottomPad = viewportY - (viewportY / 15) * (tileCoords.Y + 1);

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

FMargin STestWidgetThree::ShrinkMarble(FMargin inPadding, double factorOfShrinkage)
{
	float halfSizeOfTile = (adjustedViewportSize.Y / 15) / 2;
	float leftPad = inPadding.Left + halfSizeOfTile * factorOfShrinkage;
	float topPad = inPadding.Top + halfSizeOfTile * factorOfShrinkage;
	float rightPad = inPadding.Right + halfSizeOfTile * factorOfShrinkage;
	float bottomPad = inPadding.Bottom + halfSizeOfTile * factorOfShrinkage;

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

const FMargin CalculateLargeTilePosition(FVector2D tileCoords, FVector2D adjustedViewportSize)
{// this functions calculates the large tile positions correctly when the coordinates of the top left nineth of the large tile are used to calculate it's postion. e.g tileCoords = (0, 0) places a large tile in the top left of the screen fully display while tileCoords = (14, 14) places a large tile in the bottom right mostly off screen
	float viewportX = adjustedViewportSize.X;
	float viewportY = adjustedViewportSize.Y;
	float fOne = (viewportX - viewportY) / 2;
	float leftPad = fOne + (viewportY / 15) * tileCoords.X;
	float topPad = (viewportY / 15) * tileCoords.Y;
	float rightPad = fOne + (viewportY / 15) * (15 - (tileCoords.X + 3));
	float bottomPad = viewportY - (viewportY / 15) * (tileCoords.Y + 3);

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

const FVector2D CalculateMarblePositionCenters(FVector2D tileCoords)
{
	int tileCoordsX = FMath::RoundHalfToZero(tileCoords.X);
	int tileCoordsY = FMath::RoundHalfToZero(tileCoords.Y);

	return FVector2D(tileCoordsX, tileCoordsY);
}

const FMargin CalculateScorePos(FVector2D adjustedViewportSize)
{
	float viewportX = adjustedViewportSize.X;
	float viewportY = adjustedViewportSize.Y;
	float fOne = (viewportX - viewportY) / 2;
	float leftPad = fOne / 6;
	float topPad = viewportY / 10;
	float rightPad = (fOne / 6) + viewportY + fOne;
	float bottomPad = (viewportY / 10) * 8.5;

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

const FMargin CalculateTimePos(FVector2D adjustedViewportSize)
{
	float viewportX = adjustedViewportSize.X;
	float viewportY = adjustedViewportSize.Y;
	float fOne = (viewportX - viewportY) / 2;
	float leftPad = (fOne / 6) + viewportY + fOne;
	float topPad = viewportY / 10;
	float rightPad = (fOne / 6);
	float bottomPad = (viewportY / 10) * 8.5;

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

const FMargin CalculateCountdownPos(FVector2D adjustedViewport)
{
	float fOne = (adjustedViewport.X - adjustedViewport.Y) / 2;
	float leftPad = adjustedViewport.Y * 0.43 + fOne;
	float topPad = adjustedViewport.Y * 0.43;
	float rightPad = adjustedViewport.Y * 0.43 + fOne;
	float bottomPad = adjustedViewport.Y * 0.43;

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

/*float STestWidgetThree::CalculateGrownMarginX(FMargin inMargin)
{
	float sizeX = adjustedViewportSize.X - (inMargin.Left + inMargin.Right);
	float newSizeX = ((sizeX - (1.42 * sizeX)) / 2) / 2;

	return newSizeX;
}*/

float STestWidgetThree::CalculateAdjustedCountdownMargin(FMargin inMargin)
{
	float sizeY = adjustedViewportSize.Y - (inMargin.Top + inMargin.Bottom);
	float newSizeY = ((sizeY - (1.42 * sizeY)) / 2) / 2;

	return newSizeY;
}

FMargin STestWidgetThree::GrowCountdownMargin(FMargin inMargin)
{
	FMargin newMargin = inMargin;
	float sizeX = (adjustedCountdownMargin * sin(9.42 * (countdownEffectClock - 0.167))) + adjustedCountdownMargin;
	float sizeY = (adjustedCountdownMargin * sin(9.42 * (countdownEffectClock - 0.167))) + adjustedCountdownMargin;
	newMargin.Left += sizeX;
	newMargin.Top += sizeY;
	newMargin.Right += sizeX;
	newMargin.Bottom += sizeY;

	return newMargin;
}

//you could change the size of the background tiles without changing the size of the track tiles because they are being calculated seperately. just moving down to 12 x 12 would have a big impact on performance
void STestWidgetThree::Construct(const FArguments& InArgs)//at some point I will need to write a destructor considering all the 'new' keywords used here
{
	SetCanTick(true);
	bCanSupportFocus = true;
	currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));// Cast<USaveGameOne>(UGameplayStatics::CreateSaveGameObject(USaveGameOne::StaticClass()));
	//lastSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));
	maxLevel = currentSave->GetMaxLevel();
	highscores = currentSave->GetHighscores();
	highscoreDataOne = currentSave->GetHighscoreDataOne();
	highscoreDataTwo = currentSave->GetHighscoreDataTwo();

	OwningHUD = InArgs._OwningHUD;
	standardWorldContextObject = InArgs._standardWorldContextObject;
	landscapeArr = InArgs._landscapeArr;
	trackArr = InArgs._trackArr;
	pondSpecifierArr = InArgs._pondSpecifierArr;
	pondPositionArr = InArgs._pondPositionArr;
	tileIsIntersection = InArgs._tileIsIntersection;
	playerOnePlayerController = InArgs._playerOnePlayerController;
	startingPos = InArgs._startingPos;
	startingDir = InArgs._startingDir;
	holePositions = InArgs._holePositions;
	grass_VMUI_1 = InArgs._grass_VMUI_1;
	grass_VMUI_2 = InArgs._grass_VMUI_2;
	grass_VMUI_3 = InArgs._grass_VMUI_3;
	pondHorizontal_VMUI = InArgs._pondHorizontal_VMUI;
	pondVerticleFlowingLeft_VMUI = InArgs._pondVerticleFlowingLeft_VMUI;
	pondVerticleFlowingRight_VMUI = InArgs._pondVerticleFlowingRight_VMUI;
	riverFlowingDown_VMUI_1 = InArgs._riverFlowingDown_VMUI_1;
	riverFlowingDown_VMUI_2 = InArgs._riverFlowingDown_VMUI_2;
	riverFlowingDown_VMUI_3 = InArgs._riverFlowingDown_VMUI_3;
	riverFlowingLeft_VMUI_1 = InArgs._riverFlowingLeft_VMUI_1;
	riverFlowingLeft_VMUI_2 = InArgs._riverFlowingLeft_VMUI_2;
	riverFlowingLeft_VMUI_3 = InArgs._riverFlowingLeft_VMUI_3;
	riverFlowingRight_VMUI_1 = InArgs._riverFlowingRight_VMUI_1;
	riverFlowingRight_VMUI_2 = InArgs._riverFlowingRight_VMUI_2;
	riverFlowingRight_VMUI_3 = InArgs._riverFlowingRight_VMUI_3;
	mountain_VMUI_1 = InArgs._mountain_VMUI_1;
	tree_VMUI_1 = InArgs._tree_VMUI_1;
	tree_VMUI_2 = InArgs._tree_VMUI_2;
	tree_VMUI_3 = InArgs._tree_VMUI_3;
	tree_VMUI_4 = InArgs._tree_VMUI_4;
	tree_VMUI_5 = InArgs._tree_VMUI_5;
	waterfall_VMUI = InArgs._waterfall_VMUI;
	riverTurning_VMUI_1 = InArgs._riverTurning_VMUI_1;
	riverTurning_VMUI_2 = InArgs._riverTurning_VMUI_2;
	riverTurning_VMUI_3 = InArgs._riverTurning_VMUI_3;
	riverTurning_VMUI_4 = InArgs._riverTurning_VMUI_4;
	holeFromDown_VMUI = InArgs._holeFromDown_VMUI;
	holeFromLeft_VMUI = InArgs._holeFromLeft_VMUI;
	holeFromRight_VMUI = InArgs._holeFromRight_VMUI;
	flag_VMUI_1 = InArgs._flag_VMUI_1;
	flag_VMUI_2 = InArgs._flag_VMUI_2;
	flag_VMUI_3 = InArgs._flag_VMUI_3;
	flag_VMUI_4 = InArgs._flag_VMUI_4;
	flag_VMUI_5 = InArgs._flag_VMUI_5;
	flag_VMUI_6 = InArgs._flag_VMUI_6;
	flag_VMUI_7 = InArgs._flag_VMUI_7;
	flag_VMUI_8 = InArgs._flag_VMUI_8;
	flag_VMUI_9 = InArgs._flag_VMUI_9;
	flag_VMUI_10 = InArgs._flag_VMUI_10;
	flag_VMUI_11 = InArgs._flag_VMUI_11;
	flag_VMUI_12 = InArgs._flag_VMUI_12;
	flag_VMUI_13 = InArgs._flag_VMUI_13;
	flag_VMUI_14 = InArgs._flag_VMUI_14;
	flag_VMUI_15 = InArgs._flag_VMUI_15;
	flag_VMUI_16 = InArgs._flag_VMUI_16;
	holeFromUp_VMUI = InArgs._holeFromUp_VMUI;
	buttonFromDownTurningRightZero_SMUI = InArgs._buttonFromDownTurningRightZero_SMUI;
	buttonFromDownTurningRightOne_SMUI = InArgs._buttonFromDownTurningRightOne_SMUI;
	buttonFromDownTurningRightTwo_SMUI = InArgs._buttonFromDownTurningRightTwo_SMUI;
	buttonFromDownTurningRightThree_SMUI = InArgs._buttonFromDownTurningRightThree_SMUI;
	buttonFromDownTurningLeftZero_SMUI = InArgs._buttonFromDownTurningLeftZero_SMUI;
	buttonFromDownTurningLeftOne_SMUI = InArgs._buttonFromDownTurningLeftOne_SMUI;
	buttonFromDownTurningLeftTwo_SMUI = InArgs._buttonFromDownTurningLeftTwo_SMUI;
	buttonFromDownTurningLeftThree_SMUI = InArgs._buttonFromDownTurningLeftThree_SMUI;
	buttonFromLeftTurningRightZero_SMUI = InArgs._buttonFromLeftTurningRightZero_SMUI;
	buttonFromLeftTurningRightOne_SMUI = InArgs._buttonFromLeftTurningRightOne_SMUI;
	buttonFromLeftTurningRightTwo_SMUI = InArgs._buttonFromLeftTurningRightTwo_SMUI;
	buttonFromLeftTurningRightThree_SMUI = InArgs._buttonFromLeftTurningRightThree_SMUI;
	buttonFromLeftTurningLeftZero_SMUI = InArgs._buttonFromLeftTurningLeftZero_SMUI;
	buttonFromLeftTurningLeftOne_SMUI = InArgs._buttonFromLeftTurningLeftOne_SMUI;
	buttonFromLeftTurningLeftTwo_SMUI = InArgs._buttonFromLeftTurningLeftTwo_SMUI;
	buttonFromLeftTurningLeftThree_SMUI = InArgs._buttonFromLeftTurningLeftThree_SMUI;
	buttonFromRightTurningRightZero_SMUI = InArgs._buttonFromRightTurningRightZero_SMUI;
	buttonFromRightTurningRightOne_SMUI = InArgs._buttonFromRightTurningRightOne_SMUI;
	buttonFromRightTurningRightTwo_SMUI = InArgs._buttonFromRightTurningRightTwo_SMUI;
	buttonFromRightTurningRightThree_SMUI = InArgs._buttonFromRightTurningRightThree_SMUI;
	buttonFromRightTurningLeftZero_SMUI = InArgs._buttonFromRightTurningLeftZero_SMUI;
	buttonFromRightTurningLeftOne_SMUI = InArgs._buttonFromRightTurningLeftOne_SMUI;
	buttonFromRightTurningLeftTwo_SMUI = InArgs._buttonFromRightTurningLeftTwo_SMUI;
	buttonFromRightTurningLeftThree_SMUI = InArgs._buttonFromRightTurningLeftThree_SMUI;
	buttonFromUpTurningRightZero_SMUI = InArgs._buttonFromUpTurningRightZero_SMUI;
	buttonFromUpTurningRightOne_SMUI = InArgs._buttonFromUpTurningRightOne_SMUI;
	buttonFromUpTurningRightTwo_SMUI = InArgs._buttonFromUpTurningRightTwo_SMUI;
	buttonFromUpTurningRightThree_SMUI = InArgs._buttonFromUpTurningRightThree_SMUI;
	buttonFromUpTurningLeftZero_SMUI = InArgs._buttonFromUpTurningLeftZero_SMUI;
	buttonFromUpTurningLeftOne_SMUI = InArgs._buttonFromUpTurningLeftOne_SMUI;
	buttonFromUpTurningLeftTwo_SMUI = InArgs._buttonFromUpTurningLeftTwo_SMUI;
	buttonFromUpTurningLeftThree_SMUI = InArgs._buttonFromUpTurningLeftThree_SMUI;
	verticleRail_SMUI = InArgs._verticleRail_SMUI;
	horizontalRail_SMUI = InArgs._horizontalRail_SMUI;
	railTurningOne_SMUI = InArgs._railTurningOne_SMUI;
	railTurningTwo_SMUI = InArgs._railTurningTwo_SMUI;
	railTurningThree_SMUI = InArgs._railTurningThree_SMUI;
	focusCursor_SMUI = InArgs._focusCursor_SMUI;
	railTurningFour_SMUI = InArgs._railTurningFour_SMUI;
	gameFrameColor_SMUI = InArgs._gameFrameColor_SMUI;
	emptyImg_SMUI = InArgs._emptyImg_SMUI;
	marble_SMUI_1 = InArgs._marble_SMUI_1;
	marble_SMUI_2 = InArgs._marble_SMUI_2;
	marble_SMUI_3 = InArgs._marble_SMUI_3;
	marble_SMUI_4 = InArgs._marble_SMUI_4;
	marble_SMUI_5 = InArgs._marble_SMUI_5;
	marble_SMUI_6 = InArgs._marble_SMUI_6;
	marble_SMUI_7 = InArgs._marble_SMUI_7;
	marble_SMUI_8 = InArgs._marble_SMUI_8;
	marble_SMUI_9 = InArgs._marble_SMUI_9;
	marble_SMUI_10 = InArgs._marble_SMUI_10;
	marble_SMUI_11 = InArgs._marble_SMUI_11;
	marble_SMUI_12 = InArgs._marble_SMUI_12;
	marble_SMUI_13 = InArgs._marble_SMUI_13;
	marble_SMUI_14 = InArgs._marble_SMUI_14;
	marble_SMUI_15 = InArgs._marble_SMUI_15;
	marble_SMUI_16 = InArgs._marble_SMUI_16;
	intersectionDownAudioComponent = InArgs._intersectionDownAudioComponent;
	intersectionUpAudioComponent = InArgs._intersectionUpAudioComponent;
	windAudioComponents = InArgs._windAudioComponents;
	riverAudioComponents = InArgs._riverAudioComponents;
	waterfallAudioComponents = InArgs._waterfallAudioComponents;
	scoringAudioComponents = InArgs._scoringAudioComponents;
	missAudioComponent = InArgs._missAudioComponent;
	songAudioComponents = InArgs._songAudioComponents;
	environmentAudio = InArgs._environmentAudio;
	songPlaying = InArgs._songPlaying;
	songPlayingIndex = InArgs._songPlayingIndex;
	quantityOfMarblesToSpawn = InArgs._quantityOfMarblesToSpawn;

	grass_SB_1 = new FSlateBrush();
	grass_SB_1->SetResourceObject(grass_VMUI_1);
	grass_SB_2 = new FSlateBrush();
	grass_SB_2->SetResourceObject(grass_VMUI_2);
	grass_SB_3 = new FSlateBrush();
	grass_SB_3->SetResourceObject(grass_VMUI_3);
	pondHorizontal_SB = new FSlateBrush();
	pondHorizontal_SB->SetResourceObject(pondHorizontal_VMUI);
	pondVerticleFlowingLeft_SB = new FSlateBrush();
	pondVerticleFlowingLeft_SB->SetResourceObject(pondVerticleFlowingLeft_VMUI);
	pondVerticleFlowingRight_SB = new FSlateBrush();
	pondVerticleFlowingRight_SB->SetResourceObject(pondVerticleFlowingRight_VMUI);
	riverFlowingDown_SB_1 = new FSlateBrush();
	riverFlowingDown_SB_1->SetResourceObject(riverFlowingDown_VMUI_1);
	riverFlowingDown_SB_2 = new FSlateBrush();
	riverFlowingDown_SB_2->SetResourceObject(riverFlowingDown_VMUI_2);
	riverFlowingDown_SB_3 = new FSlateBrush();
	riverFlowingDown_SB_3->SetResourceObject(riverFlowingDown_VMUI_3);
	riverFlowingLeft_SB_1 = new FSlateBrush();
	riverFlowingLeft_SB_1->SetResourceObject(riverFlowingLeft_VMUI_1);
	riverFlowingLeft_SB_2 = new FSlateBrush();
	riverFlowingLeft_SB_2->SetResourceObject(riverFlowingLeft_VMUI_2);
	riverFlowingLeft_SB_3 = new FSlateBrush();
	riverFlowingLeft_SB_3->SetResourceObject(riverFlowingLeft_VMUI_3);
	riverFlowingRight_SB_1 = new FSlateBrush();
	riverFlowingRight_SB_1->SetResourceObject(riverFlowingRight_VMUI_1);
	riverFlowingRight_SB_2 = new FSlateBrush();
	riverFlowingRight_SB_2->SetResourceObject(riverFlowingRight_VMUI_2);
	riverFlowingRight_SB_3 = new FSlateBrush();
	riverFlowingRight_SB_3->SetResourceObject(riverFlowingRight_VMUI_3);
	tree_SB_1 = new FSlateBrush();
	tree_SB_1->SetResourceObject(tree_VMUI_1);
	tree_SB_2 = new FSlateBrush();
	tree_SB_2->SetResourceObject(tree_VMUI_2);
	tree_SB_3 = new FSlateBrush();
	tree_SB_3->SetResourceObject(tree_VMUI_3);
	tree_SB_4 = new FSlateBrush();
	tree_SB_4->SetResourceObject(tree_VMUI_4);
	tree_SB_5 = new FSlateBrush();
	tree_SB_5->SetResourceObject(tree_VMUI_5);
	waterfall_SB = new FSlateBrush();
	waterfall_SB->SetResourceObject(waterfall_VMUI);
	riverTurning_SB_1 = new FSlateBrush();
	riverTurning_SB_1->SetResourceObject(riverTurning_VMUI_1);
	riverTurning_SB_2 = new FSlateBrush();
	riverTurning_SB_2->SetResourceObject(riverTurning_VMUI_2);
	riverTurning_SB_3 = new FSlateBrush();
	riverTurning_SB_3->SetResourceObject(riverTurning_VMUI_3);
	riverTurning_SB_4 = new FSlateBrush();
	riverTurning_SB_4->SetResourceObject(riverTurning_VMUI_4);
	mountain_SB_1 = new FSlateBrush();
	mountain_SB_1->SetResourceObject(mountain_VMUI_1);

	holeFromDown_SB = new FSlateBrush();
	holeFromLeft_SB = new FSlateBrush();
	holeFromRight_SB = new FSlateBrush();
	holeFromUp_SB = new FSlateBrush();
	holeFromDown_SB->SetResourceObject(holeFromDown_VMUI);
	holeFromLeft_SB->SetResourceObject(holeFromLeft_VMUI);
	holeFromRight_SB->SetResourceObject(holeFromRight_VMUI);
	holeFromUp_SB->SetResourceObject(holeFromUp_VMUI);

	flag_SB_1 = new FSlateBrush();
	flag_SB_1->SetResourceObject(flag_VMUI_1);
	flag_SB_2 = new FSlateBrush();
	flag_SB_2->SetResourceObject(flag_VMUI_2);
	flag_SB_3 = new FSlateBrush();
	flag_SB_3->SetResourceObject(flag_VMUI_3);
	flag_SB_4 = new FSlateBrush();
	flag_SB_4->SetResourceObject(flag_VMUI_4);
	flag_SB_5 = new FSlateBrush();
	flag_SB_5->SetResourceObject(flag_VMUI_5);
	flag_SB_6 = new FSlateBrush();
	flag_SB_6->SetResourceObject(flag_VMUI_6);
	flag_SB_7 = new FSlateBrush();
	flag_SB_7->SetResourceObject(flag_VMUI_7);
	flag_SB_8 = new FSlateBrush();
	flag_SB_8->SetResourceObject(flag_VMUI_8);
	flag_SB_9 = new FSlateBrush();
	flag_SB_9->SetResourceObject(flag_VMUI_9);
	flag_SB_10 = new FSlateBrush();
	flag_SB_10->SetResourceObject(flag_VMUI_10);
	flag_SB_11 = new FSlateBrush();
	flag_SB_11->SetResourceObject(flag_VMUI_11);
	flag_SB_12 = new FSlateBrush();
	flag_SB_12->SetResourceObject(flag_VMUI_12);
	flag_SB_13 = new FSlateBrush();
	flag_SB_13->SetResourceObject(flag_VMUI_13);
	flag_SB_14 = new FSlateBrush();
	flag_SB_14->SetResourceObject(flag_VMUI_14);
	flag_SB_15 = new FSlateBrush();
	flag_SB_15->SetResourceObject(flag_VMUI_15);
	flag_SB_16 = new FSlateBrush();
	flag_SB_16->SetResourceObject(flag_VMUI_16);

	buttonFromDownTurningRightZero_SB = new FSlateBrush();
	buttonFromDownTurningRightOne_SB = new FSlateBrush();
	buttonFromDownTurningRightTwo_SB = new FSlateBrush();
	buttonFromDownTurningRightThree_SB = new FSlateBrush();
	buttonFromDownTurningLeftZero_SB = new FSlateBrush();
	buttonFromDownTurningLeftOne_SB = new FSlateBrush();
	buttonFromDownTurningLeftTwo_SB = new FSlateBrush();
	buttonFromDownTurningLeftThree_SB = new FSlateBrush();
	buttonFromLeftTurningRightZero_SB = new FSlateBrush();
	buttonFromLeftTurningRightOne_SB = new FSlateBrush();
	buttonFromLeftTurningRightTwo_SB = new FSlateBrush();
	buttonFromLeftTurningRightThree_SB = new FSlateBrush();
	buttonFromLeftTurningLeftZero_SB = new FSlateBrush();
	buttonFromLeftTurningLeftOne_SB = new FSlateBrush();
	buttonFromLeftTurningLeftTwo_SB = new FSlateBrush();
	buttonFromLeftTurningLeftThree_SB = new FSlateBrush();
	buttonFromRightTurningRightZero_SB = new FSlateBrush();
	buttonFromRightTurningRightOne_SB = new FSlateBrush();
	buttonFromRightTurningRightTwo_SB = new FSlateBrush();
	buttonFromRightTurningRightThree_SB = new FSlateBrush();
	buttonFromRightTurningLeftZero_SB = new FSlateBrush();
	buttonFromRightTurningLeftOne_SB = new FSlateBrush();
	buttonFromRightTurningLeftTwo_SB = new FSlateBrush();
	buttonFromRightTurningLeftThree_SB = new FSlateBrush();
	buttonFromUpTurningRightZero_SB = new FSlateBrush();
	buttonFromUpTurningRightOne_SB = new FSlateBrush();
	buttonFromUpTurningRightTwo_SB = new FSlateBrush();
	buttonFromUpTurningRightThree_SB = new FSlateBrush();
	buttonFromUpTurningLeftZero_SB = new FSlateBrush();
	buttonFromUpTurningLeftOne_SB = new FSlateBrush();
	buttonFromUpTurningLeftTwo_SB = new FSlateBrush();
	buttonFromUpTurningLeftThree_SB = new FSlateBrush();
	buttonFromDownTurningRightZero_SB->SetResourceObject(buttonFromDownTurningRightZero_SMUI);
	buttonFromDownTurningRightOne_SB->SetResourceObject(buttonFromDownTurningRightOne_SMUI);
	buttonFromDownTurningRightTwo_SB->SetResourceObject(buttonFromDownTurningRightTwo_SMUI);
	buttonFromDownTurningRightThree_SB->SetResourceObject(buttonFromDownTurningRightThree_SMUI);
	buttonFromDownTurningLeftZero_SB->SetResourceObject(buttonFromDownTurningLeftZero_SMUI);
	buttonFromDownTurningLeftOne_SB->SetResourceObject(buttonFromDownTurningLeftOne_SMUI);
	buttonFromDownTurningLeftTwo_SB->SetResourceObject(buttonFromDownTurningLeftTwo_SMUI);
	buttonFromDownTurningLeftThree_SB->SetResourceObject(buttonFromDownTurningLeftThree_SMUI);
	buttonFromLeftTurningRightZero_SB->SetResourceObject(buttonFromLeftTurningRightZero_SMUI);
	buttonFromLeftTurningRightOne_SB->SetResourceObject(buttonFromLeftTurningRightOne_SMUI);
	buttonFromLeftTurningRightTwo_SB->SetResourceObject(buttonFromLeftTurningRightTwo_SMUI);
	buttonFromLeftTurningRightThree_SB->SetResourceObject(buttonFromLeftTurningRightThree_SMUI);
	buttonFromLeftTurningLeftZero_SB->SetResourceObject(buttonFromLeftTurningLeftZero_SMUI);
	buttonFromLeftTurningLeftOne_SB->SetResourceObject(buttonFromLeftTurningLeftOne_SMUI);
	buttonFromLeftTurningLeftTwo_SB->SetResourceObject(buttonFromLeftTurningLeftTwo_SMUI);
	buttonFromLeftTurningLeftThree_SB->SetResourceObject(buttonFromLeftTurningLeftThree_SMUI);
	buttonFromRightTurningRightZero_SB->SetResourceObject(buttonFromRightTurningRightZero_SMUI);
	buttonFromRightTurningRightOne_SB->SetResourceObject(buttonFromRightTurningRightOne_SMUI);
	buttonFromRightTurningRightTwo_SB->SetResourceObject(buttonFromRightTurningRightTwo_SMUI);
	buttonFromRightTurningRightThree_SB->SetResourceObject(buttonFromRightTurningRightThree_SMUI);
	buttonFromRightTurningLeftZero_SB->SetResourceObject(buttonFromRightTurningLeftZero_SMUI);
	buttonFromRightTurningLeftOne_SB->SetResourceObject(buttonFromRightTurningLeftOne_SMUI);
	buttonFromRightTurningLeftTwo_SB->SetResourceObject(buttonFromRightTurningLeftTwo_SMUI);
	buttonFromRightTurningLeftThree_SB->SetResourceObject(buttonFromRightTurningLeftThree_SMUI);
	buttonFromUpTurningRightZero_SB->SetResourceObject(buttonFromUpTurningRightZero_SMUI);
	buttonFromUpTurningRightOne_SB->SetResourceObject(buttonFromUpTurningRightOne_SMUI);
	buttonFromUpTurningRightTwo_SB->SetResourceObject(buttonFromUpTurningRightTwo_SMUI);
	buttonFromUpTurningRightThree_SB->SetResourceObject(buttonFromUpTurningRightThree_SMUI);
	buttonFromUpTurningLeftZero_SB->SetResourceObject(buttonFromUpTurningLeftZero_SMUI);
	buttonFromUpTurningLeftOne_SB->SetResourceObject(buttonFromUpTurningLeftOne_SMUI);
	buttonFromUpTurningLeftTwo_SB->SetResourceObject(buttonFromUpTurningLeftTwo_SMUI);
	buttonFromUpTurningLeftThree_SB->SetResourceObject(buttonFromUpTurningLeftThree_SMUI);

	verticleRail_SB = new FSlateBrush();
	horizontalRail_SB = new FSlateBrush();
	railTurningOne_SB = new FSlateBrush();
	railTurningTwo_SB = new FSlateBrush();
	railTurningThree_SB = new FSlateBrush();
	railTurningFour_SB = new FSlateBrush();
	verticleRail_SB->SetResourceObject(verticleRail_SMUI);
	horizontalRail_SB->SetResourceObject(horizontalRail_SMUI);
	railTurningOne_SB->SetResourceObject(railTurningOne_SMUI);
	railTurningTwo_SB->SetResourceObject(railTurningTwo_SMUI);
	railTurningThree_SB->SetResourceObject(railTurningThree_SMUI);
	railTurningFour_SB->SetResourceObject(railTurningFour_SMUI);

	marble_SB_1 = new FSlateBrush();
	marble_SB_2 = new FSlateBrush();
	marble_SB_3 = new FSlateBrush();
	marble_SB_4 = new FSlateBrush();
	marble_SB_5 = new FSlateBrush();
	marble_SB_6 = new FSlateBrush();
	marble_SB_7 = new FSlateBrush();
	marble_SB_8 = new FSlateBrush();
	marble_SB_9 = new FSlateBrush();
	marble_SB_10 = new FSlateBrush();
	marble_SB_11 = new FSlateBrush();
	marble_SB_12 = new FSlateBrush();
	marble_SB_13 = new FSlateBrush();
	marble_SB_14 = new FSlateBrush();
	marble_SB_15 = new FSlateBrush();
	marble_SB_16 = new FSlateBrush();
	marble_SB_1->SetResourceObject(marble_SMUI_1);
	marble_SB_2->SetResourceObject(marble_SMUI_2);
	marble_SB_3->SetResourceObject(marble_SMUI_3);
	marble_SB_4->SetResourceObject(marble_SMUI_4);
	marble_SB_5->SetResourceObject(marble_SMUI_5);
	marble_SB_6->SetResourceObject(marble_SMUI_6);
	marble_SB_7->SetResourceObject(marble_SMUI_7);
	marble_SB_8->SetResourceObject(marble_SMUI_8);
	marble_SB_9->SetResourceObject(marble_SMUI_9);
	marble_SB_10->SetResourceObject(marble_SMUI_10);
	marble_SB_11->SetResourceObject(marble_SMUI_11);
	marble_SB_12->SetResourceObject(marble_SMUI_12);
	marble_SB_13->SetResourceObject(marble_SMUI_13);
	marble_SB_14->SetResourceObject(marble_SMUI_14);
	marble_SB_15->SetResourceObject(marble_SMUI_15);
	marble_SB_16->SetResourceObject(marble_SMUI_16);

	focusCursor_SB = new FSlateBrush();
	focusCursor_SB->SetResourceObject(focusCursor_SMUI);

	gameFrameColor_SB = new FSlateBrush();
	gameFrameColor_SB->SetResourceObject(gameFrameColor_SMUI);

	emptyImg_SB = new FSlateBrush();
	emptyImg_SB->SetResourceObject(emptyImg_SMUI);

	if (maxLevel == 0 && highscores[0] == 0)
	{
		OwningHUD->MakeAchievement(0);
	}

	landscapeStuff = { grass_SB_1, holeFromDown_SB, holeFromLeft_SB, holeFromRight_SB, holeFromUp_SB, grass_SB_2, grass_SB_3, pondHorizontal_SB, pondVerticleFlowingLeft_SB, pondVerticleFlowingRight_SB, waterfall_SB, riverFlowingDown_SB_1, riverFlowingDown_SB_2, riverFlowingDown_SB_3, riverFlowingLeft_SB_1, riverFlowingLeft_SB_2, riverFlowingLeft_SB_3, riverFlowingRight_SB_1, riverFlowingRight_SB_2, riverFlowingRight_SB_3, tree_SB_1, tree_SB_2, tree_SB_3, tree_SB_4, tree_SB_5, riverTurning_SB_1, riverTurning_SB_2, riverTurning_SB_3, riverTurning_SB_4, emptyImg_SB, grass_SB_1, grass_SB_2, grass_SB_3, mountain_SB_1 };
	trackStuff = { emptyImg_SB, verticleRail_SB, horizontalRail_SB, railTurningOne_SB, railTurningTwo_SB, railTurningThree_SB, railTurningFour_SB, buttonFromDownTurningRightZero_SB, buttonFromDownTurningLeftZero_SB, buttonFromLeftTurningRightZero_SB, buttonFromLeftTurningLeftZero_SB, buttonFromRightTurningRightZero_SB, buttonFromRightTurningLeftZero_SB, buttonFromUpTurningRightZero_SB, buttonFromUpTurningLeftZero_SB };//the first element for this arr is an empty image ALSO I should change this to an array of fully assembled widget structures with the intersection having their logic built in

	flags = { flag_SB_1, flag_SB_2, flag_SB_3, flag_SB_4, flag_SB_5, flag_SB_6, flag_SB_7, flag_SB_8, flag_SB_9, flag_SB_10, flag_SB_11, flag_SB_12, flag_SB_13, flag_SB_14, flag_SB_15, flag_SB_16, };
	marbles = { marble_SB_1, marble_SB_2, marble_SB_3, marble_SB_4, marble_SB_5, marble_SB_6, marble_SB_7, marble_SB_8, marble_SB_9, marble_SB_10, marble_SB_11, marble_SB_12, marble_SB_13, marble_SB_14, marble_SB_15, marble_SB_16, };

	for (int a = 0; a < holePositions.Num(); a++)
	{//feb 15 just encountered a bug where holePositions.Num() was 18 instead of the projected 9. this was because convertedHolePositions in TestHud was not being reset during regeneration. is this the only variable I forgot to designate to reset during regeneration? yes there is.. the river.
		relevantFlags.Add(flags[a]);
		relevantMarbles.Add(marbles[a]);
	}
	for (int a = 0; a < holePositions.Num(); a++)
	{
		int x = FMath::RandRange(0, relevantFlags.Num() - 1);

		flagsRandomized.Add(relevantFlags[x]);
		marblesRandomized.Add(relevantMarbles[x]);

		relevantFlags.RemoveAt(x);
		relevantMarbles.RemoveAt(x);
	}

	intersections = {
		{ buttonFromDownTurningRightZero_SB, buttonFromDownTurningRightOne_SB, buttonFromDownTurningRightTwo_SB, buttonFromDownTurningRightThree_SB },
		{ buttonFromDownTurningLeftZero_SB, buttonFromDownTurningLeftOne_SB, buttonFromDownTurningLeftTwo_SB, buttonFromDownTurningLeftThree_SB },
		{ buttonFromLeftTurningRightZero_SB, buttonFromLeftTurningRightOne_SB, buttonFromLeftTurningRightTwo_SB, buttonFromLeftTurningRightThree_SB },
		{ buttonFromLeftTurningLeftZero_SB, buttonFromLeftTurningLeftOne_SB, buttonFromLeftTurningLeftTwo_SB, buttonFromLeftTurningLeftThree_SB },
		{ buttonFromRightTurningRightZero_SB, buttonFromRightTurningRightOne_SB, buttonFromRightTurningRightTwo_SB, buttonFromRightTurningRightThree_SB },
		{ buttonFromRightTurningLeftZero_SB, buttonFromRightTurningLeftOne_SB, buttonFromRightTurningLeftTwo_SB, buttonFromRightTurningLeftThree_SB },
		{ buttonFromUpTurningRightZero_SB, buttonFromUpTurningRightOne_SB, buttonFromUpTurningRightTwo_SB, buttonFromUpTurningRightThree_SB },
		{ buttonFromUpTurningLeftZero_SB, buttonFromUpTurningLeftOne_SB, buttonFromUpTurningLeftTwo_SB, buttonFromUpTurningLeftThree_SB }
	};

	GEngine->GameViewport->GetViewportSize(viewportSize);
	int32 X = FGenericPlatformMath::FloorToInt(viewportSize.X);
	int32 Y = FGenericPlatformMath::FloorToInt(viewportSize.Y);
	DPIScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(X, Y));
	adjustedViewportSize = (1 / DPIScale) * viewportSize;

	const FMargin contentPadding = FMargin(166.f, 100.f);
	const FMargin rowPadding_15 = FMargin(420.0f, 1008.0f, 1428.0f, 0.0f);
	const FMargin buttonPadding = FMargin(10.f);

	const FText titleText = LOCTEXT("GameTitle", "Marble Game");
	const FText playText = LOCTEXT("PlayGame", "Play");
	const FText settingsText = LOCTEXT("Settings", "Settings");
	const FText quitText = LOCTEXT("QuitGame", "Quit");

	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 40.f;

	FSlateFontInfo TitleTextStyle = ButtonTextStyle;
	TitleTextStyle.Size = 60.f;

	masterButtonStyle = new FButtonStyle();
	masterButtonStyle->SetNormalPadding(FMargin());

	if (!songPlaying)
	{
		songAudioComponents[songPlayingIndex]->Stop();
	}

	scoringSoundEffectIndex = FMath::RandRange(0, 2);

	for (int a = 0; a < 2; a++)
	{
		windAudioComponents[a]->Stop();
		riverAudioComponents[a]->Stop();
		waterfallAudioComponents[a]->Stop();
	}

	switch (environmentAudio)
	{
	case 0:
		windAudioComponents[0]->Play();

		riverAudioComponents[0]->Play();
		break;
	case 1:
		windAudioComponents[0]->Play();

		waterfallAudioComponents[0]->Play();
		break;
	default:
		break;
	}

	switch (startingDir)
	{
	case 2:
		startingPos.X = -1;
		startingMarbleMovementTracker[0] = 1;
		break;
	case 3:
		startingPos.Y = -1;
		startingMarbleMovementTracker[1] = 1;
		break;
	case 4:
		startingPos.X = 15;//does this need to be 15 or 16?
		startingMarbleMovementTracker[0] = -1;
		break;
	default:
		break;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "startingPos two: " + startingPos.ToString() + " | startingDir two: " + FString::FromInt(startingDir));
	speedsOfMarbles = { 0.75, 0.7828, 0.8182, 0.8443, 0.8578, 0.8670, 0.8726, 0.8913, 0.9076, 0.9212, 0.9257, 0.9292, 0.9315, 0.9333 };
	quantitiesOfMarbles = { 0, 4, 8, 12, 15, 18, 21, 24, 27, 30, 32, 34, 36, 38 };


	quantityOfMarbles = quantityOfMarblesToSpawn + quantitiesOfMarbles[holePositions.Num() - 3];//check
	speedMultiplier = speedsOfMarbles[holePositions.Num() - 3];
	// s = 0.8 and i = 33 is 0.0242424
	//see desmos and notes for breakdown of equation, but C = i/i^2 * 1/s  C is concentration, i is interval of marble spawn, s is speed of marble. when i increases from 33 marbles over 120 seconds by 1 marble s needs to grow at a linear rate to maintain the same C but that rate varies by intended C and starting s

	//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "quantity: " + FString::FromInt(quantityOfMarbles));
	//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "speed: " + FString::SanitizeFloat(speedMultiplier));

	timeToCoverOneTileDividedByTwo = (1 / speedMultiplier) / 2;

	spawningWindow = (float)((float)timeOfGame / (float)quantityOfMarbles);
	//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "speed: " + FString::SanitizeFloat(spawningWindow));

	for (int a = 0; a < marblesRandomized.Num() * 6; a++)
	{
		if (a % 6 < 3)
		{
			marblesThisGameProxy.Add(1);
		}
		else
		{
			marblesThisGameProxy.Add(0);
		}
	}
	for (int a = 0; a < marblesRandomized.Num(); a++)
	{
		marblesThisGameProxyTracker.Add(2);
	}

	for (int a = 0; a < quantityOfMarbles; a++)
	{
		marbleProxyIndexToAdd = FMath::RandRange(0, marblesThisGameProxy.Num() - 1);

		if (marblesThisGameProxy[marbleProxyIndexToAdd] != 0)
		{
			marbleIndexToAdd = marbleProxyIndexToAdd / 6;

			for (int b = 0; b < marblesRandomized.Num(); b++)
			{
				if (marbleIndexToAdd == b)
				{
					marblesThisGameProxy[b * 6 + marblesThisGameProxyTracker[b]] = 0;
					marblesThisGameProxyTracker[b] = FMath::Clamp(marblesThisGameProxyTracker[b] - 1, 0, 5);
					marblesThisGameProxy[b * 6 + marblesThisGameProxyTracker[b]] = 0;
					marblesThisGameProxyTracker[b] = FMath::Clamp(marblesThisGameProxyTracker[b] - 1, 0, 5);
					marblesThisGameProxy[b * 6 + marblesThisGameProxyTracker[b]] = 0;
					marblesThisGameProxyTracker[b] = FMath::Clamp(marblesThisGameProxyTracker[b] - 1, 0, 5);
					marblesThisGameProxy[b * 6 + marblesThisGameProxyTracker[b]] = 0;
					marblesThisGameProxyTracker[b] = FMath::Clamp(marblesThisGameProxyTracker[b] - 1, 0, 5);
					marblesThisGameProxy[b * 6 + marblesThisGameProxyTracker[b]] = 0;
					marblesThisGameProxyTracker[b] = FMath::Clamp(marblesThisGameProxyTracker[b] - 1, 0, 5);
				}
				else
				{
					marblesThisGameProxyTracker[b] = FMath::Clamp(marblesThisGameProxyTracker[b] + 1, 0, 5);
					marblesThisGameProxy[b * 6 + marblesThisGameProxyTracker[b]] = 1;
				}
			}
			marblesThisGame.Add(marblesRandomized[marbleIndexToAdd]);
			marbleIndexesBeingAdded.Add(marbleIndexToAdd);

			timeIntoWindowMarbleIsSpawned.Add((float)((float)((float)spawningWindow / (float)6) * (float)FMath::RandRange(2, 4)) + (float)((float)spawningWindow * (float)a));
		}//timeIntoWindowMarbleIsSpawned.Add((float)((float)((float)spawningWindow / (float)6) * (float)FMath::RandRange(2, 4)) + (float)((float)spawningWindow * (float)a));
		else
		{
			a -= 1;
		}
	}

	timeIntoWindowMarbleIsSpawned.Add(timeOfGame + 1);
	marbleIndexToSpawn = 0;

	marbleOverlay = SNew(SOverlay);

	scoreText = SNew(STextBlock);
	scoreText->SetJustification(ETextJustify::Center);
	scoreText->SetColorAndOpacity(FColor::Orange);
	currentScore = FText::FromString("Score: " + FString::FromInt(playerScore) + " of " + FString::FromInt(maximumPossibleScore));
	scoreText->SetText(currentScore);
	scoreTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	if ((double)((double)adjustedViewportSize.X / (double)adjustedViewportSize.Y) < (double)((double)2367 / (double)1273))//theres a ration of viewportSize.X to viewportSize.Y, after a certain point you should go from using one axis to calculate font size to the other
	{
		scoreTextStyle.Size = (adjustedViewportSize.X - adjustedViewportSize.Y) * 0.04;
	}
	else
	{
		scoreTextStyle.Size = adjustedViewportSize.Y * 0.033;
	}
	scoreText->SetFont(scoreTextStyle);

	timeText = SNew(STextBlock);
	timeText->SetJustification(ETextJustify::Center);
	timeText->SetColorAndOpacity(FColor::Orange);
	currentTimeText = FText::FromString("Time: " + FString::FromInt(FMath::RoundToZero((double)currentTime / 60)) + ":" + FString::FromInt(currentTime % 60));
	timeText->SetText(currentTimeText);
	timeText->SetFont(scoreTextStyle);

	largeTilesOverlay = SNew(SOverlay);
	for (int a = 0; a < pondPositionArr.Num(); a++)
	{
		largeTilesOverlay->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateLargeTilePosition(pondPositionArr[a], adjustedViewportSize))
			[
				SNew(SImage)
					.Image(landscapeStuff[pondSpecifierArr[a]])
			];
	}

	landscapeOverlay = SNew(SOverlay);
	for (int a = 0; a < 225; a++)
	{
		landscapeOverlay->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
			[
				SNew(SImage)
					.Image(landscapeStuff[landscapeArr[a]])
			];
	}

	flagsOverlay = SNew(SOverlay);
	for (int a = 0; a < holePositions.Num(); a++)
	{
		flagsOverlay->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(holePositions[a], adjustedViewportSize))
			[
				SNew(SImage)
					.Image(flagsRandomized[a])
			];
	}

	frameColorOverlay = SNew(SOverlay);
	frameColorOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(FMargin(0, 0, (adjustedViewportSize.X - adjustedViewportSize.Y) / 2 + adjustedViewportSize.Y, 0))
		[
			SNew(SImage)
				.Image(gameFrameColor_SB)
		];
	frameColorOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(FMargin((adjustedViewportSize.X - adjustedViewportSize.Y) / 2 + adjustedViewportSize.Y, 0, 0, 0))
		[
			SNew(SImage)
				.Image(gameFrameColor_SB)
		];

	trackOverlay = SNew(SOverlay);
	intersectionButtonsOverlay = SNew(SOverlay);
	for (int a = 0; a < 225; a++)
	{
		if (!tileIsIntersection[a])
		{
			trackOverlay->AddSlot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
				[
					SNew(SImage)
						.Image(trackStuff[trackArr[a]])
				];
		}
		else
		{
			switch (currentIntersection)
			{
			case 1:
				intersectionImages.Add(SNew(SImage));
				intersectionImages[0]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);
				intersectionPositions.Add(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)));

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionImages[0].ToSharedRef()
					];

				intersectionButtonsArray.Add(SNew(SButton)
					.ContentPadding(FMargin())
					.ButtonStyle(masterButtonStyle)
					.OnPressed(this, &STestWidgetThree::OnIntersectionPressedOne)
					.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedOne)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
					.ButtonColorAndOpacity(FLinearColor::Transparent)
					.IsEnabled(true));

				intersectionButtonsOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionButtonsArray[0].ToSharedRef()
					];

				break;
			case 2:
				intersectionImages.Add(SNew(SImage));
				intersectionImages[1]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);
				intersectionPositions.Add(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)));

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionImages[1].ToSharedRef()
					];

				intersectionButtonsArray.Add(SNew(SButton)
					.ContentPadding(FMargin())
					.ButtonStyle(masterButtonStyle)
					.OnPressed(this, &STestWidgetThree::OnIntersectionPressedTwo)
					.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedTwo)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
					.ButtonColorAndOpacity(FLinearColor::Transparent)
					.IsEnabled(true));

				intersectionButtonsOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionButtonsArray[1].ToSharedRef()
					];

				break;
			case 3:
				intersectionImages.Add(SNew(SImage));
				intersectionImages[2]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);
				intersectionPositions.Add(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)));

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionImages[2].ToSharedRef()
					];

				intersectionButtonsArray.Add(SNew(SButton)
					.ContentPadding(FMargin())
					.ButtonStyle(masterButtonStyle)
					.OnPressed(this, &STestWidgetThree::OnIntersectionPressedThree)
					.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedThree)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
					.ButtonColorAndOpacity(FLinearColor::Transparent)
					.IsEnabled(true));

				intersectionButtonsOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionButtonsArray[2].ToSharedRef()
					];

				break;
			case 4:
				intersectionImages.Add(SNew(SImage));
				intersectionImages[3]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);
				intersectionPositions.Add(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)));

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionImages[3].ToSharedRef()
					];

				intersectionButtonsArray.Add(SNew(SButton)
					.ContentPadding(FMargin())
					.ButtonStyle(masterButtonStyle)
					.OnPressed(this, &STestWidgetThree::OnIntersectionPressedFour)
					.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedFour)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
					.ButtonColorAndOpacity(FLinearColor::Transparent)
					.IsEnabled(true));

				intersectionButtonsOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionButtonsArray[3].ToSharedRef()
					];

				break;
			case 5:
				intersectionImages.Add(SNew(SImage));
				intersectionImages[4]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);
				intersectionPositions.Add(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)));

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionImages[4].ToSharedRef()
					];

				intersectionButtonsArray.Add(SNew(SButton)
					.ContentPadding(FMargin())
					.ButtonStyle(masterButtonStyle)
					.OnPressed(this, &STestWidgetThree::OnIntersectionPressedFive)
					.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedFive)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
					.ButtonColorAndOpacity(FLinearColor::Transparent)
					.IsEnabled(true));

				intersectionButtonsOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionButtonsArray[4].ToSharedRef()
					];

				break;
			case 6:
				intersectionImages.Add(SNew(SImage));
				intersectionImages[5]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);
				intersectionPositions.Add(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)));

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionImages[5].ToSharedRef()
					];

				intersectionButtonsArray.Add(SNew(SButton)
					.ContentPadding(FMargin())
					.ButtonStyle(masterButtonStyle)
					.OnPressed(this, &STestWidgetThree::OnIntersectionPressedSix)
					.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedSix)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
					.ButtonColorAndOpacity(FLinearColor::Transparent)
					.IsEnabled(true));

				intersectionButtonsOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionButtonsArray[5].ToSharedRef()
					];

				break;
			case 7:
				intersectionImages.Add(SNew(SImage));
				intersectionImages[6]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);
				intersectionPositions.Add(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)));

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionImages[6].ToSharedRef()
					];

				intersectionButtonsArray.Add(SNew(SButton)
					.ContentPadding(FMargin())
					.ButtonStyle(masterButtonStyle)
					.OnPressed(this, &STestWidgetThree::OnIntersectionPressedSeven)
					.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedSeven)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
					.ButtonColorAndOpacity(FLinearColor::Transparent)
					.IsEnabled(true));

				intersectionButtonsOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionButtonsArray[6].ToSharedRef()
					];

				break;
			case 8:
				intersectionImages.Add(SNew(SImage));
				intersectionImages[7]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);
				intersectionPositions.Add(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)));

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionImages[7].ToSharedRef()
					];

				intersectionButtonsArray.Add(SNew(SButton)
					.ContentPadding(FMargin())
					.ButtonStyle(masterButtonStyle)
					.OnPressed(this, &STestWidgetThree::OnIntersectionPressedEight)
					.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedEight)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
					.ButtonColorAndOpacity(FLinearColor::Transparent)
					.IsEnabled(true));

				intersectionButtonsOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionButtonsArray[7].ToSharedRef()
					];

				break;
			case 9:
				intersectionImages.Add(SNew(SImage));
				intersectionImages[8]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);
				intersectionPositions.Add(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)));

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionImages[8].ToSharedRef()
					];

				intersectionButtonsArray.Add(SNew(SButton)
					.ContentPadding(FMargin())
					.ButtonStyle(masterButtonStyle)
					.OnPressed(this, &STestWidgetThree::OnIntersectionPressedNine)
					.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedNine)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
					.ButtonColorAndOpacity(FLinearColor::Transparent)
					.IsEnabled(true));

				intersectionButtonsOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionButtonsArray[8].ToSharedRef()
					];

				break;
			case 10:
				intersectionImages.Add(SNew(SImage));
				intersectionImages[9]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);
				intersectionPositions.Add(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)));

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionImages[9].ToSharedRef()
					];

				intersectionButtonsArray.Add(SNew(SButton)
					.ContentPadding(FMargin())
					.ButtonStyle(masterButtonStyle)
					.OnPressed(this, &STestWidgetThree::OnIntersectionPressedTen)
					.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedTen)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
					.ButtonColorAndOpacity(FLinearColor::Transparent)
					.IsEnabled(true));

				intersectionButtonsOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionButtonsArray[9].ToSharedRef()
					];

				break;
			case 11:
				intersectionImages.Add(SNew(SImage));
				intersectionImages[10]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);
				intersectionPositions.Add(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)));

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionImages[10].ToSharedRef()
					];

				intersectionButtonsArray.Add(SNew(SButton)
					.ContentPadding(FMargin())
					.ButtonStyle(masterButtonStyle)
					.OnPressed(this, &STestWidgetThree::OnIntersectionPressedEleven)
					.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedEleven)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
					.ButtonColorAndOpacity(FLinearColor::Transparent)
					.IsEnabled(true));

				intersectionButtonsOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionButtonsArray[10].ToSharedRef()
					];

				break;
			case 12:
				intersectionImages.Add(SNew(SImage));
				intersectionImages[11]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);
				intersectionPositions.Add(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)));

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionImages[11].ToSharedRef()
					];

				intersectionButtonsArray.Add(SNew(SButton)
					.ContentPadding(FMargin())
					.ButtonStyle(masterButtonStyle)
					.OnPressed(this, &STestWidgetThree::OnIntersectionPressedTwelve)
					.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedTwelve)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
					.ButtonColorAndOpacity(FLinearColor::Transparent)
					.IsEnabled(true));

				intersectionButtonsOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionButtonsArray[11].ToSharedRef()
					];

				break;
			case 13:
				intersectionImages.Add(SNew(SImage));
				intersectionImages[12]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);
				intersectionPositions.Add(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)));

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionImages[12].ToSharedRef()
					];

				intersectionButtonsArray.Add(SNew(SButton)
					.ContentPadding(FMargin())
					.ButtonStyle(masterButtonStyle)
					.OnPressed(this, &STestWidgetThree::OnIntersectionPressedThirteen)
					.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedThirteen)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
					.ButtonColorAndOpacity(FLinearColor::Transparent)
					.IsEnabled(true));

				intersectionButtonsOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionButtonsArray[12].ToSharedRef()
					];

				break;
			case 14:
				intersectionImages.Add(SNew(SImage));
				intersectionImages[13]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);
				intersectionPositions.Add(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)));

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionImages[13].ToSharedRef()
					];

				intersectionButtonsArray.Add(SNew(SButton)
					.ContentPadding(FMargin())
					.ButtonStyle(masterButtonStyle)
					.OnPressed(this, &STestWidgetThree::OnIntersectionPressedFourteen)
					.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedFourteen)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
					.ButtonColorAndOpacity(FLinearColor::Transparent)
					.IsEnabled(true));

				intersectionButtonsOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionButtonsArray[13].ToSharedRef()
					];

				break;
			case 15:
				intersectionImages.Add(SNew(SImage));
				intersectionImages[14]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);
				intersectionPositions.Add(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)));

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionImages[14].ToSharedRef()
					];

				intersectionButtonsArray.Add(SNew(SButton)
					.ContentPadding(FMargin())
					.ButtonStyle(masterButtonStyle)
					.OnPressed(this, &STestWidgetThree::OnIntersectionPressedFifteen)
					.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedFifteen)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
					.ButtonColorAndOpacity(FLinearColor::Transparent)
					.IsEnabled(true));

				intersectionButtonsOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionButtonsArray[14].ToSharedRef()
					];

				break;
			case 16:
				intersectionImages.Add(SNew(SImage));
				intersectionImages[15]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);
				intersectionPositions.Add(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)));

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionImages[15].ToSharedRef()
					];

				intersectionButtonsArray.Add(SNew(SButton)
					.ContentPadding(FMargin())
					.ButtonStyle(masterButtonStyle)
					.OnPressed(this, &STestWidgetThree::OnIntersectionPressedSixteen)
					.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedSixteen)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
					.ButtonColorAndOpacity(FLinearColor::Transparent)
					.IsEnabled(true));

				intersectionButtonsOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionButtonsArray[15].ToSharedRef()
					];

				break;
			case 17:
				intersectionImages.Add(SNew(SImage));
				intersectionImages[16]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);
				intersectionPositions.Add(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)));

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionImages[16].ToSharedRef()
					];

				intersectionButtonsArray.Add(SNew(SButton)
					.ContentPadding(FMargin())
					.ButtonStyle(masterButtonStyle)
					.OnPressed(this, &STestWidgetThree::OnIntersectionPressedSeventeen)
					.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedSeventeen)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
					.ButtonColorAndOpacity(FLinearColor::Transparent)
					.IsEnabled(true));

				intersectionButtonsOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						intersectionButtonsArray[16].ToSharedRef()
					];

				break;
			default:
				break;
			}

			currentIntersection += 1;
			intersectionsKeys.Add(trackArr[a]);
			intersectionLocations.Add(a);//so the first solution I can imagine is to translate the indices into vector2D locations, then every frame measure the distance between the cursor and every intersection and whichevers shortest gets highlighted. Second I could store positional data on how each intersections positions relate to eachother at init, then record how the mouse position changed from the last frame. If I know intersection 1 is at 0,0 and intersection 2 is at 5, 0 and the prior highlighted intersection was 1 and the mouse moved + 2, 0 I know it was moving toward intersection 2 and away from 1. this would be probably faster to process but signifigantly harder to execute. I'm going option 1.
		}
	}

	for (int a = 0; a < intersectionLocations.Num(); a++)
	{
		intersectionTileLocations.Add(FVector2D(((viewportSize.X - viewportSize.Y) / 2) + (viewportSize.Y / 30) + ((viewportSize.Y / 15) * (intersectionLocations[a] % 15)), (viewportSize.Y / 30) + ((viewportSize.Y / 15) * FMath::RoundToZero((float)(intersectionLocations[a] / 15)))));
	}

	for (int a = 0; a < intersectionLocations.Num(); a++)
	{
		switch (FMath::DivideAndRoundDown(intersectionsKeys[a] , 2)) // pi/8 = 0.3927f
		{
		case 0: // intersection dir 3
			intersectionAlterationBoundaries.Add(FMath::DivideAndRoundDown(intersectionLocations[a], 15) + 0.1073);
			break;
		case 1: // intersection dir 4
			intersectionAlterationBoundaries.Add((intersectionLocations[a] % 15) - 0.1073);
			break;
		case 2: // intersection dir 2
			intersectionAlterationBoundaries.Add((intersectionLocations[a] % 15) + 0.1073);
			break;
		case 3: // intersection dir 1
			intersectionAlterationBoundaries.Add(FMath::DivideAndRoundDown(intersectionLocations[a], 15) - 0.1073);
			break;
		default:
			GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "faulty intersection boundary calculation");
			break;
		}
	}

	autoIntersectionButton = SNew(SButton)
		.ContentPadding(FMargin())
		.ButtonStyle(masterButtonStyle)
		.OnPressed(this, &STestWidgetThree::OnAutoIntersectionPressed)
		.OnReleased(this, &STestWidgetThree::OnAutoIntersectionReleased)
		.ButtonColorAndOpacity(FLinearColor::Transparent)
		.IsEnabled(true);

	focusCursorBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SImage)
				.Image(focusCursor_SB)
		];

	autoCursorModeOn = currentSave->GetAutoCursorOn();//this will be set to the value retrieved from the save file when testing completes
	indexOfIntersectionInFocusSafety = false;
	tempIndexOfIntersectionInFocus = 0;

	if (autoCursorModeOn)
	{
		for (int a = 0; a < intersectionButtonsArray.Num(); a++)
		{
			intersectionButtonsArray[a]->SetEnabled(false);
		}

		intersectionButtonsOverlay->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin())//this should make the button the size of the entire screen. Bigger even than the game display. it does not? this must mean the overlay is restricted to the game board somewhere.
			[
				autoIntersectionButton.ToSharedRef()
			];

		trackOverlay->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				focusCursorBox.ToSharedRef()
			];

		playerOnePlayerController->GetMousePosition(mouseX, mouseY);

		for (int a = 0; a < intersectionTileLocations.Num(); a++)
		{
			intersectionDistancesFromMouse.Add(pow(0.5, pow(2, intersectionTileLocations[a].X - mouseX) + pow(2, intersectionTileLocations[a].Y - mouseY)));
		}

		distanceBetweenMouseAndIntersectionFloatOne = intersectionDistancesFromMouse[0];
		for (int a = 1; a < intersectionDistancesFromMouse.Num(); a++)
		{
			if (intersectionDistancesFromMouse[a] < distanceBetweenMouseAndIntersectionFloatOne)
			{
				distanceBetweenMouseAndIntersectionFloatOne = intersectionDistancesFromMouse[a];
				indexOfIntersectionInFocus = a;
			}
		}

		focusCursorBox->SetPadding(CalculateLargeTilePosition(FVector2D(intersectionPositions[indexOfIntersectionInFocus].X - 1, intersectionPositions[indexOfIntersectionInFocus].Y - 1), adjustedViewportSize));
	}

	pauseOverlay = SNew(SOverlay);
	pauseBlur = SNew(SBackgroundBlur)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.BlurStrength(0);

	countdownOverlay = SNew(SOverlay);
	countdownFont = FCoreStyle::Get().GetFontStyle("Roboto"); //test italic
	countdownFont.Size = 0.0866 * adjustedViewportSize.Y;
	adjustedStartingFontSize = ((1.155 * countdownFont.Size) - countdownFont.Size) / 2;
	countdownMargin = CalculateCountdownPos(adjustedViewportSize);
	adjustedCountdownMargin = CalculateAdjustedCountdownMargin(countdownMargin);
	adjustedStartingOpacity = 0.5;
	countdownText = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FLinearColor(1, 1, 1, 0))
		.Font(countdownFont)
		.Text(FText::FromString("0"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.004, adjustedViewportSize.Y * 0.004))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 0));
	countdownBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(countdownMargin)
		[
			countdownText.ToSharedRef()
		];
	countdownOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			countdownBox.ToSharedRef()
		];

	ChildSlot //so it appears I cannot write code to systematically build only as much widget as necessary and will instead need to list out 225 landscape SImages and 225 track SImages and fill them as needed. but hold on, there is still some testing to be done, what if I store the initial SOverlay so I can reference it directly. ( this will mean potentially creating a new SOverlay sub class? no nvm I will just need to check through the childSlot logic to see if theres a way to display an already existing SOverlay, or to assign the SNew(SOverlay to an identity
		[
			SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					largeTilesOverlay.ToSharedRef()
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					landscapeOverlay.ToSharedRef()
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					trackOverlay.ToSharedRef()
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					marbleOverlay.ToSharedRef()
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					flagsOverlay.ToSharedRef()
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					countdownOverlay.ToSharedRef()
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					intersectionButtonsOverlay.ToSharedRef()
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					frameColorOverlay.ToSharedRef()
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(CalculateScorePos(adjustedViewportSize))
				[
					scoreText.ToSharedRef()
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(CalculateTimePos(adjustedViewportSize))
				[
					timeText.ToSharedRef()
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					pauseOverlay.ToSharedRef()
				]
		];
}

void STestWidgetThree::OnIntersectionPressedOne()
{
	intersectionCycle[0] = (intersectionCycle[0] + 1) % 4;
	intersectionImages[0]->SetImage(intersections[intersectionsKeys[0]][intersectionCycle[0]]);
	intersectionDownAudioComponent->Play();
}
void STestWidgetThree::OnIntersectionReleasedOne()
{
	intersectionCycle[0] = (intersectionCycle[0] + 1) % 4;
	intersectionImages[0]->SetImage(intersections[intersectionsKeys[0]][intersectionCycle[0]]);
	intersectionUpAudioComponent->Play();
	//OwningHUD->SetFocusToGame();

	if (intersectionsContainingMarbles.Find(intersectionLocations[0]) + 1)
	{
		AlterMarbleTurn(0, intersectionsContainingMarbles.Find(intersectionLocations[0]));
	}
}

void STestWidgetThree::OnIntersectionPressedTwo()
{
	intersectionCycle[1] = (intersectionCycle[1] + 1) % 4;
	intersectionImages[1]->SetImage(intersections[intersectionsKeys[1]][intersectionCycle[1]]);
	intersectionDownAudioComponent->Play();
}
void STestWidgetThree::OnIntersectionReleasedTwo()
{
	intersectionCycle[1] = (intersectionCycle[1] + 1) % 4;
	intersectionImages[1]->SetImage(intersections[intersectionsKeys[1]][intersectionCycle[1]]);
	intersectionUpAudioComponent->Play();
	//OwningHUD->SetFocusToGame();

	if (intersectionsContainingMarbles.Find(intersectionLocations[1]) + 1)
	{
		AlterMarbleTurn(1, intersectionsContainingMarbles.Find(intersectionLocations[1]));
	}
}

void STestWidgetThree::OnIntersectionPressedThree()
{
	intersectionCycle[2] = (intersectionCycle[2] + 1) % 4;
	intersectionImages[2]->SetImage(intersections[intersectionsKeys[2]][intersectionCycle[2]]);
	intersectionDownAudioComponent->Play();
}
void STestWidgetThree::OnIntersectionReleasedThree()
{
	intersectionCycle[2] = (intersectionCycle[2] + 1) % 4;
	intersectionImages[2]->SetImage(intersections[intersectionsKeys[2]][intersectionCycle[2]]);
	intersectionUpAudioComponent->Play();
	//OwningHUD->SetFocusToGame();

	if (intersectionsContainingMarbles.Find(intersectionLocations[2]) + 1)
	{
		AlterMarbleTurn(2, intersectionsContainingMarbles.Find(intersectionLocations[2]));
	}
}

void STestWidgetThree::OnIntersectionPressedFour()
{
	intersectionCycle[3] = (intersectionCycle[3] + 1) % 4;
	intersectionImages[3]->SetImage(intersections[intersectionsKeys[3]][intersectionCycle[3]]);
	intersectionDownAudioComponent->Play();
}
void STestWidgetThree::OnIntersectionReleasedFour()
{
	intersectionCycle[3] = (intersectionCycle[3] + 1) % 4;
	intersectionImages[3]->SetImage(intersections[intersectionsKeys[3]][intersectionCycle[3]]);
	intersectionUpAudioComponent->Play();
	//OwningHUD->SetFocusToGame();

	if (intersectionsContainingMarbles.Find(intersectionLocations[3]) + 1)
	{
		AlterMarbleTurn(3, intersectionsContainingMarbles.Find(intersectionLocations[3]));
	}
}

void STestWidgetThree::OnIntersectionPressedFive()
{
	intersectionCycle[4] = (intersectionCycle[4] + 1) % 4;
	intersectionImages[4]->SetImage(intersections[intersectionsKeys[4]][intersectionCycle[4]]);
	intersectionDownAudioComponent->Play();
}
void STestWidgetThree::OnIntersectionReleasedFive()
{
	intersectionCycle[4] = (intersectionCycle[4] + 1) % 4;
	intersectionImages[4]->SetImage(intersections[intersectionsKeys[4]][intersectionCycle[4]]);
	intersectionUpAudioComponent->Play();
	//OwningHUD->SetFocusToGame();

	if (intersectionsContainingMarbles.Find(intersectionLocations[4]) + 1)
	{
		AlterMarbleTurn(4, intersectionsContainingMarbles.Find(intersectionLocations[4]));
	}
}

void STestWidgetThree::OnIntersectionPressedSix()
{
	intersectionCycle[5] = (intersectionCycle[5] + 1) % 4;
	intersectionImages[5]->SetImage(intersections[intersectionsKeys[5]][intersectionCycle[5]]);
	intersectionDownAudioComponent->Play();
}
void STestWidgetThree::OnIntersectionReleasedSix()
{
	intersectionCycle[5] = (intersectionCycle[5] + 1) % 4;
	intersectionImages[5]->SetImage(intersections[intersectionsKeys[5]][intersectionCycle[5]]);
	intersectionUpAudioComponent->Play();
	//OwningHUD->SetFocusToGame();

	if (intersectionsContainingMarbles.Find(intersectionLocations[5]) + 1)
	{
		AlterMarbleTurn(5, intersectionsContainingMarbles.Find(intersectionLocations[5]));
	}
}

void STestWidgetThree::OnIntersectionPressedSeven()
{
	intersectionCycle[6] = (intersectionCycle[6] + 1) % 4;
	intersectionImages[6]->SetImage(intersections[intersectionsKeys[6]][intersectionCycle[6]]);
	intersectionDownAudioComponent->Play();
}
void STestWidgetThree::OnIntersectionReleasedSeven()
{
	intersectionCycle[6] = (intersectionCycle[6] + 1) % 4;
	intersectionImages[6]->SetImage(intersections[intersectionsKeys[6]][intersectionCycle[6]]);
	intersectionUpAudioComponent->Play();
	//OwningHUD->SetFocusToGame();

	if (intersectionsContainingMarbles.Find(intersectionLocations[6]) + 1)
	{
		AlterMarbleTurn(6, intersectionsContainingMarbles.Find(intersectionLocations[6]));
	}
}

void STestWidgetThree::OnIntersectionPressedEight()
{
	intersectionCycle[7] = (intersectionCycle[7] + 1) % 4;
	intersectionImages[7]->SetImage(intersections[intersectionsKeys[7]][intersectionCycle[7]]);
	intersectionDownAudioComponent->Play();
}
void STestWidgetThree::OnIntersectionReleasedEight()
{
	intersectionCycle[7] = (intersectionCycle[7] + 1) % 4;
	intersectionImages[7]->SetImage(intersections[intersectionsKeys[7]][intersectionCycle[7]]);
	intersectionUpAudioComponent->Play();
	//OwningHUD->SetFocusToGame();

	if (intersectionsContainingMarbles.Find(intersectionLocations[7]) + 1)
	{
		AlterMarbleTurn(7, intersectionsContainingMarbles.Find(intersectionLocations[7]));
	}
}

void STestWidgetThree::OnIntersectionPressedNine()
{
	intersectionCycle[8] = (intersectionCycle[8] + 1) % 4;
	intersectionImages[8]->SetImage(intersections[intersectionsKeys[8]][intersectionCycle[8]]);
	intersectionDownAudioComponent->Play();
}
void STestWidgetThree::OnIntersectionReleasedNine()
{
	intersectionCycle[8] = (intersectionCycle[8] + 1) % 4;
	intersectionImages[8]->SetImage(intersections[intersectionsKeys[8]][intersectionCycle[8]]);
	intersectionUpAudioComponent->Play();
	//OwningHUD->SetFocusToGame();

	if (intersectionsContainingMarbles.Find(intersectionLocations[8]) + 1)
	{
		AlterMarbleTurn(8, intersectionsContainingMarbles.Find(intersectionLocations[8]));
	}
}

void STestWidgetThree::OnIntersectionPressedTen()
{
	intersectionCycle[9] = (intersectionCycle[9] + 1) % 4;
	intersectionImages[9]->SetImage(intersections[intersectionsKeys[9]][intersectionCycle[9]]);
	intersectionDownAudioComponent->Play();
}
void STestWidgetThree::OnIntersectionReleasedTen()
{
	intersectionCycle[9] = (intersectionCycle[9] + 1) % 4;
	intersectionImages[9]->SetImage(intersections[intersectionsKeys[9]][intersectionCycle[9]]);
	intersectionUpAudioComponent->Play();
	//OwningHUD->SetFocusToGame();

	if (intersectionsContainingMarbles.Find(intersectionLocations[9]) + 1)
	{
		AlterMarbleTurn(9, intersectionsContainingMarbles.Find(intersectionLocations[9]));
	}
}

void STestWidgetThree::OnIntersectionPressedEleven()
{
	intersectionCycle[10] = (intersectionCycle[10] + 1) % 4;
	intersectionImages[10]->SetImage(intersections[intersectionsKeys[10]][intersectionCycle[10]]);
	intersectionDownAudioComponent->Play();
}
void STestWidgetThree::OnIntersectionReleasedEleven()
{
	intersectionCycle[10] = (intersectionCycle[10] + 1) % 4;
	intersectionImages[10]->SetImage(intersections[intersectionsKeys[10]][intersectionCycle[10]]);
	intersectionUpAudioComponent->Play();
	//OwningHUD->SetFocusToGame();

	if (intersectionsContainingMarbles.Find(intersectionLocations[10]) + 1)
	{
		AlterMarbleTurn(10, intersectionsContainingMarbles.Find(intersectionLocations[10]));
	}
}

void STestWidgetThree::OnIntersectionPressedTwelve()
{
	intersectionCycle[11] = (intersectionCycle[11] + 1) % 4;
	intersectionImages[11]->SetImage(intersections[intersectionsKeys[11]][intersectionCycle[11]]);
	intersectionDownAudioComponent->Play();
}
void STestWidgetThree::OnIntersectionReleasedTwelve()
{
	intersectionCycle[11] = (intersectionCycle[11] + 1) % 4;
	intersectionImages[11]->SetImage(intersections[intersectionsKeys[11]][intersectionCycle[11]]);
	intersectionUpAudioComponent->Play();
	//OwningHUD->SetFocusToGame();

	if (intersectionsContainingMarbles.Find(intersectionLocations[11]) + 1)
	{
		AlterMarbleTurn(11, intersectionsContainingMarbles.Find(intersectionLocations[11]));
	}
}

void STestWidgetThree::OnIntersectionPressedThirteen()
{
	intersectionCycle[12] = (intersectionCycle[12] + 1) % 4;
	intersectionImages[12]->SetImage(intersections[intersectionsKeys[12]][intersectionCycle[12]]);
	intersectionDownAudioComponent->Play();
}
void STestWidgetThree::OnIntersectionReleasedThirteen()
{
	intersectionCycle[12] = (intersectionCycle[12] + 1) % 4;
	intersectionImages[12]->SetImage(intersections[intersectionsKeys[12]][intersectionCycle[12]]);
	intersectionUpAudioComponent->Play();
	//OwningHUD->SetFocusToGame();

	if (intersectionsContainingMarbles.Find(intersectionLocations[12]) + 1)
	{
		AlterMarbleTurn(12, intersectionsContainingMarbles.Find(intersectionLocations[12]));
	}
}

void STestWidgetThree::OnIntersectionPressedFourteen()
{
	intersectionCycle[13] = (intersectionCycle[13] + 1) % 4;
	intersectionImages[13]->SetImage(intersections[intersectionsKeys[13]][intersectionCycle[13]]);
	intersectionDownAudioComponent->Play();
}
void STestWidgetThree::OnIntersectionReleasedFourteen()
{
	intersectionCycle[13] = (intersectionCycle[13] + 1) % 4;
	intersectionImages[13]->SetImage(intersections[intersectionsKeys[13]][intersectionCycle[13]]);
	intersectionUpAudioComponent->Play();
	//OwningHUD->SetFocusToGame();

	if (intersectionsContainingMarbles.Find(intersectionLocations[13]) + 1)
	{
		AlterMarbleTurn(13, intersectionsContainingMarbles.Find(intersectionLocations[13]));
	}
}

void STestWidgetThree::OnIntersectionPressedFifteen()
{
	intersectionCycle[14] = (intersectionCycle[14] + 1) % 4;
	intersectionImages[14]->SetImage(intersections[intersectionsKeys[14]][intersectionCycle[14]]);
	intersectionDownAudioComponent->Play();
}
void STestWidgetThree::OnIntersectionReleasedFifteen()
{
	intersectionCycle[14] = (intersectionCycle[14] + 1) % 4;
	intersectionImages[14]->SetImage(intersections[intersectionsKeys[14]][intersectionCycle[14]]);
	intersectionUpAudioComponent->Play();
	//OwningHUD->SetFocusToGame();

	if (intersectionsContainingMarbles.Find(intersectionLocations[14]) + 1)
	{
		AlterMarbleTurn(14, intersectionsContainingMarbles.Find(intersectionLocations[14]));
	}
}

void STestWidgetThree::OnIntersectionPressedSixteen()
{
	intersectionCycle[15] = (intersectionCycle[15] + 1) % 4;
	intersectionImages[15]->SetImage(intersections[intersectionsKeys[15]][intersectionCycle[15]]);
	intersectionDownAudioComponent->Play();
}
void STestWidgetThree::OnIntersectionReleasedSixteen()
{
	intersectionCycle[15] = (intersectionCycle[15] + 1) % 4;
	intersectionImages[15]->SetImage(intersections[intersectionsKeys[15]][intersectionCycle[15]]);
	intersectionUpAudioComponent->Play();
	//OwningHUD->SetFocusToGame();

	if (intersectionsContainingMarbles.Find(intersectionLocations[15]) + 1)
	{
		AlterMarbleTurn(15, intersectionsContainingMarbles.Find(intersectionLocations[15]));
	}
}

void STestWidgetThree::OnIntersectionPressedSeventeen()
{
	intersectionCycle[16] = (intersectionCycle[16] + 1) % 4;
	intersectionImages[16]->SetImage(intersections[intersectionsKeys[16]][intersectionCycle[16]]);
	intersectionDownAudioComponent->Play();
}
void STestWidgetThree::OnIntersectionReleasedSeventeen()
{
	intersectionCycle[16] = (intersectionCycle[16] + 1) % 4;
	intersectionImages[16]->SetImage(intersections[intersectionsKeys[16]][intersectionCycle[16]]);
	intersectionUpAudioComponent->Play();
	//OwningHUD->SetFocusToGame();

	if (intersectionsContainingMarbles.Find(intersectionLocations[16]) + 1)
	{
		AlterMarbleTurn(16, intersectionsContainingMarbles.Find(intersectionLocations[16]));
	}
}

void STestWidgetThree::OnAutoIntersectionPressed()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "auto intersection pressed");
	indexOfIntersectionInFocusSafety = true;

	intersectionCycle[indexOfIntersectionInFocus] = (intersectionCycle[indexOfIntersectionInFocus] + 1) % 4;
	intersectionImages[indexOfIntersectionInFocus]->SetImage(intersections[intersectionsKeys[indexOfIntersectionInFocus]][intersectionCycle[indexOfIntersectionInFocus]]);
	intersectionDownAudioComponent->Play();
}
void STestWidgetThree::OnAutoIntersectionReleased()
{
	intersectionCycle[indexOfIntersectionInFocus] = (intersectionCycle[indexOfIntersectionInFocus] + 1) % 4;
	intersectionImages[indexOfIntersectionInFocus]->SetImage(intersections[intersectionsKeys[indexOfIntersectionInFocus]][intersectionCycle[indexOfIntersectionInFocus]]);
	intersectionUpAudioComponent->Play();
	//OwningHUD->SetFocusToGame();// are we sure this should be called every button press?? !!! TESTING REQUIRED !!!

	indexOfIntersectionInFocusSafety = false;

	if (intersectionsContainingMarbles.Find(intersectionLocations[indexOfIntersectionInFocus]) + 1)
	{
		AlterMarbleTurn(indexOfIntersectionInFocus, intersectionsContainingMarbles.Find(intersectionLocations[indexOfIntersectionInFocus]));
	}
}

void STestWidgetThree::EnableAutoCursor(bool inBool)
{
	if (inBool)
	{
		for (int a = 0; a < intersectionButtonsArray.Num(); a++)
		{
			intersectionButtonsArray[a]->SetEnabled(false);
		}

		intersectionButtonsOverlay->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin())//this should make the button the size of the entire screen. Bigger even than the game display.
			[
				autoIntersectionButton.ToSharedRef()
			];

		trackOverlay->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				focusCursorBox.ToSharedRef()
			];

		autoCursorModeOn = true;

		intersectionDistancesFromMouse.Empty();

		playerOnePlayerController->GetMousePosition(mouseX, mouseY);

		for (int a = 0; a < intersectionTileLocations.Num(); a++)
		{
			intersectionDistancesFromMouse.Add(FMath::Sqrt(FMath::Abs((intersectionTileLocations[a].X - mouseX) * (intersectionTileLocations[a].X - mouseX)) + FMath::Abs((intersectionTileLocations[a].Y - mouseY) * (intersectionTileLocations[a].Y - mouseY))));
		}

		distanceBetweenMouseAndIntersectionFloatOne = intersectionDistancesFromMouse[0];
		tempIndexOfIntersectionInFocus = 0;
		for (int a = 1; a < intersectionDistancesFromMouse.Num(); a++)
		{
			if (distanceBetweenMouseAndIntersectionFloatOne > intersectionDistancesFromMouse[a])
			{
				distanceBetweenMouseAndIntersectionFloatOne = intersectionDistancesFromMouse[a];
				tempIndexOfIntersectionInFocus = a;
			}
		}

		if (!indexOfIntersectionInFocusSafety)
		{
			indexOfIntersectionInFocus = tempIndexOfIntersectionInFocus;
		}

		focusCursorBox->SetPadding(CalculateLargeTilePosition(FVector2D(intersectionPositions[indexOfIntersectionInFocus].X - 1, intersectionPositions[indexOfIntersectionInFocus].Y - 1), adjustedViewportSize));
	}
	else
	{
		intersectionButtonsOverlay->RemoveSlot(autoIntersectionButton.ToSharedRef());
		trackOverlay->RemoveSlot(focusCursorBox.ToSharedRef());

		for (int a = 0; a < intersectionButtonsArray.Num(); a++)
		{
			intersectionButtonsArray[a]->SetEnabled(true);
		}

		autoCursorModeOn = false;
	}
}

FReply STestWidgetThree::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& InMouseEvent)
{
	currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));
	FKey inButton = InMouseEvent.GetEffectingButton();

	if (inButton == currentSave->GetPauseMouse())
	{// I should test this if (!paused) conditional to make sure the else block is not running. If the else block is running I'll need to double check it is functioning properly
		if (!paused)
		{
			OwningHUD->DisplayPauseScreen();
			paused = true;

			switch (environmentAudio)
			{
			case 0:
				windAudioComponents[audioCycleTracker % 2]->SetPaused(true);

				riverAudioComponents[audioCycleTracker % 2]->SetPaused(true);
				break;
			case 1:
				windAudioComponents[audioCycleTracker % 2]->SetPaused(true);

				waterfallAudioComponents[audioCycleTracker % 2]->SetPaused(true);
				break;
			default:
				break;
			}

			if (songAudioComponents[songPlayingIndex]->IsPlaying())//this conditional here is a little concerning
			{
				songAudioComponents[songPlayingIndex]->SetPaused(true);
			}
		}
		else
		{
			OwningHUD->PrepDestroyPauseScreen();
			GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "tabFromSTestWidget");
		}
	}

	/*if (inButton == EKeys::LeftMouseButton)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "click");
	}*/

	return FReply::Handled();
}

FReply STestWidgetThree::OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	/*if (InKeyEvent.GetKey() == EKeys::Q)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "q");
	}*/
	currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));

	if (InKeyEvent.GetKey() == currentSave->GetPauseKey())
	{
		if (!paused)
		{
			OwningHUD->DisplayPauseScreen();
			paused = true;

			switch (environmentAudio)
			{
			case 0:
				windAudioComponents[audioCycleTracker % 2]->SetPaused(true);

				riverAudioComponents[audioCycleTracker % 2]->SetPaused(true);
				break;
			case 1:
				windAudioComponents[audioCycleTracker % 2]->SetPaused(true);

				waterfallAudioComponents[audioCycleTracker % 2]->SetPaused(true);
				break;
			default:
				break;
			}

			if (songAudioComponents[songPlayingIndex]->IsPlaying())//this conditional here is a little concerning
			{
				songAudioComponents[songPlayingIndex]->SetPaused(true);
			}
		}
		else
		{
			OwningHUD->PrepDestroyPauseScreen();
			GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "tabFromSTestWidget");
		}
	}

	/*if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		OwningHUD->HouseKeeping();
		OwningHUD->ResetRegenLevel();

		UKismetSystemLibrary::QuitGame(playerOnePlayerController, playerOnePlayerController, EQuitPreference::Quit, false);
	}*/

	return FReply::Handled();
}

FVector2D STestWidgetThree::PrepTurnMarble(int currentMarble, FVector2d marblePosition, int dirOfMarble, bool isIntersection, int trackArrValue)
{
	int turnBeingMade;

	if (isIntersection)
	{
		turnBeingMade = trackArrValue + 4;
	}
	else
	{
		turnBeingMade = trackArrValue - 3;
	}

	switch (dirOfMarble)
	{
	case 1:
		marblePosAtArcInvo[currentMarble] = marblePosition;
		marblePosAtArcInvo[currentMarble].Y = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y) + 0.5;

		if (turnBeingMade == 1 || turnBeingMade == 4)//1 is right, 2 is left, 4 is right, 5 is left
		{
			turnToExecute[currentMarble] = 0;
		}
		else
		{
			turnToExecute[currentMarble] = 1;
		}
		break;
	case 2:
		marblePosAtArcInvo[currentMarble] = marblePosition;

		if (marblePosition.X < 0)
		{
			marblePosAtArcInvo[currentMarble].X = -0.5;
		}
		else
		{
			marblePosAtArcInvo[currentMarble].X = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].X) + 0.5;
		}

		if (turnBeingMade == 2 || turnBeingMade == 6)//2 is right, 3 is left, 6 is right, 7 is left
		{
			turnToExecute[currentMarble] = 2;
		}
		else
		{
			turnToExecute[currentMarble] = 3;
		}
		break;
	case 3:
		marblePosAtArcInvo[currentMarble] = marblePosition;

		if (marblePosition.Y < 0)
		{
			marblePosAtArcInvo[currentMarble].Y = -0.5;
		}
		else
		{
			marblePosAtArcInvo[currentMarble].Y = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y) + 0.5;
		}

		if (turnBeingMade == 3 || turnBeingMade == 10)//0 is left, 3 is right, 10 is right, 11 is left
		{
			turnToExecute[currentMarble] = 4;
		}
		else
		{
			turnToExecute[currentMarble] = 5;
		}
		break;
	case 4:
		marblePosAtArcInvo[currentMarble] = marblePosition;
		marblePosAtArcInvo[currentMarble].X = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].X) + 0.5;

		if (turnBeingMade == 0 || turnBeingMade == 8)//0 is right, 1 is left, 8 is right, 9 is left
		{
			turnToExecute[currentMarble] = 6;
		}
		else
		{
			turnToExecute[currentMarble] = 7;
		}
		break;
	default:
		break;
	}

	return TurnMarble(currentMarble, marblePosition);
}

FVector2D STestWidgetThree::TurnMarble(int currentMarble, FVector2D marblePosition)
{
	FVector2D convertedMarblePos;

	switch (turnToExecute[currentMarble])
	{
	case 0: // marble dir 1, turning right
		if (marblePosAtArcInvo[currentMarble].Y - marblePosition.Y >= 0.7854)
		{
			marbleIsTurning[currentMarble] = false;
			dirOfMarbles[currentMarble] = 2;
			marbleMovementTracker[currentMarble][0] = 1;
			marbleMovementTracker[currentMarble][1] = 0;
			marblePositions[currentMarble].X = FMath::RoundHalfFromZero(marblePosAtArcInvo[currentMarble].X) + 0.5;
			marblePositions[currentMarble].Y = FMath::RoundHalfFromZero(marblePosAtArcInvo[currentMarble].Y - 0.5);
			convertedMarblePos = marblePositions[currentMarble];
			break;
		}
		convertedMarblePos.X = marblePosAtArcInvo[currentMarble].X + 0.5 - (0.5 * (sin(1.57079 - (((marblePosAtArcInvo[currentMarble].Y - marblePosition.Y) / 0.7854) * 1.57079))));
		convertedMarblePos.Y = marblePosAtArcInvo[currentMarble].Y - 0.5 * sin(((marblePosAtArcInvo[currentMarble].Y - marblePosition.Y) / 0.7854) * 1.57079);

		break;
	case 1: // marble dir 1 turning left
		if (marblePosAtArcInvo[currentMarble].Y - marblePosition.Y >= 0.7854)
		{
			marbleIsTurning[currentMarble] = false;
			dirOfMarbles[currentMarble] = 4;
			marbleMovementTracker[currentMarble][0] = -1;
			marbleMovementTracker[currentMarble][1] = 0;
			marblePositions[currentMarble].X = FMath::RoundHalfFromZero(marblePosAtArcInvo[currentMarble].X) - 0.5;
			marblePositions[currentMarble].Y = FMath::RoundHalfFromZero(marblePosAtArcInvo[currentMarble].Y - 0.5);
			convertedMarblePos = marblePositions[currentMarble];
			break;
		}
		convertedMarblePos.X = marblePosAtArcInvo[currentMarble].X - (0.5 - (0.5 * (sin(1.57079 - (((marblePosAtArcInvo[currentMarble].Y - marblePosition.Y) / 0.7854) * 1.57079)))));
		convertedMarblePos.Y = marblePosAtArcInvo[currentMarble].Y - 0.5 * sin(((marblePosAtArcInvo[currentMarble].Y - marblePosition.Y) / 0.7854) * 1.57079);

		break;
	case 2: // marble dir 2 turning right
		if (marblePosAtArcInvo[currentMarble].X - marblePosition.X <= -0.7854)
		{
			marbleIsTurning[currentMarble] = false;
			dirOfMarbles[currentMarble] = 3;
			marbleMovementTracker[currentMarble][0] = 0;
			marbleMovementTracker[currentMarble][1] = 1;
			marblePositions[currentMarble].X = FMath::RoundHalfFromZero(marblePosAtArcInvo[currentMarble].X + 0.5);
			marblePositions[currentMarble].Y = FMath::RoundHalfFromZero(marblePosAtArcInvo[currentMarble].Y) + 0.5;
			convertedMarblePos = marblePositions[currentMarble];
			break;
		}
		convertedMarblePos.X = marblePosAtArcInvo[currentMarble].X + 0.5 * sin(((marblePosition.X - marblePosAtArcInvo[currentMarble].X) / 0.7854) * 1.57079);
		convertedMarblePos.Y = marblePosAtArcInvo[currentMarble].Y + 0.5 - (0.5 * (sin(1.57079 - (((marblePosition.X - marblePosAtArcInvo[currentMarble].X) / 0.7854) * 1.57079))));

		break;
	case 3: // marble dir 2 turning left
		if (marblePosAtArcInvo[currentMarble].X - marblePosition.X <= -0.7854)
		{
			marbleIsTurning[currentMarble] = false;
			dirOfMarbles[currentMarble] = 1;
			marbleMovementTracker[currentMarble][0] = 0;
			marbleMovementTracker[currentMarble][1] = -1;
			marblePositions[currentMarble].X = FMath::RoundHalfFromZero(marblePosAtArcInvo[currentMarble].X + 0.5);
			marblePositions[currentMarble].Y = FMath::RoundHalfFromZero(marblePosAtArcInvo[currentMarble].Y) - 0.5;
			convertedMarblePos = marblePositions[currentMarble];
			break;
		}
		convertedMarblePos.X = marblePosAtArcInvo[currentMarble].X + 0.5 * sin(((marblePosition.X - marblePosAtArcInvo[currentMarble].X) / 0.7854) * 1.57079);
		convertedMarblePos.Y = marblePosAtArcInvo[currentMarble].Y - (0.5 - (0.5 * sin(1.57079 - (((marblePosition.X - marblePosAtArcInvo[currentMarble].X) / 0.7854) * 1.57079))));

		break;
	case 4: // marble dir 3 turning right
		if (marblePosAtArcInvo[currentMarble].Y - marblePosition.Y <= -0.7854)
		{
			marbleIsTurning[currentMarble] = false;
			dirOfMarbles[currentMarble] = 4;
			marbleMovementTracker[currentMarble][0] = -1;
			marbleMovementTracker[currentMarble][1] = 0;
			marblePositions[currentMarble].X = FMath::RoundHalfFromZero(marblePosAtArcInvo[currentMarble].X) - 0.5;
			marblePositions[currentMarble].Y = FMath::RoundHalfFromZero(marblePosAtArcInvo[currentMarble].Y + 0.5);
			convertedMarblePos = marblePositions[currentMarble];
			break;
		}
		convertedMarblePos.X = marblePosAtArcInvo[currentMarble].X - (0.5 - (0.5 * (sin(1.57079 - (((marblePosition.Y - marblePosAtArcInvo[currentMarble].Y) / 0.7854) * 1.57079)))));
		convertedMarblePos.Y = marblePosAtArcInvo[currentMarble].Y + 0.5 * sin(((marblePosition.Y - marblePosAtArcInvo[currentMarble].Y) / 0.7854) * 1.57079);

		break;
	case 5: // marble dir 3 turning left
		if (marblePosAtArcInvo[currentMarble].Y - marblePosition.Y <= -0.7854)
		{
			marbleIsTurning[currentMarble] = false;
			dirOfMarbles[currentMarble] = 2;
			marbleMovementTracker[currentMarble][0] = 1;
			marbleMovementTracker[currentMarble][1] = 0;
			marblePositions[currentMarble].X = FMath::RoundHalfFromZero(marblePosAtArcInvo[currentMarble].X) + 0.5;
			marblePositions[currentMarble].Y = FMath::RoundHalfFromZero(marblePosAtArcInvo[currentMarble].Y + 0.5);
			convertedMarblePos = marblePositions[currentMarble];
			break;
		}
		convertedMarblePos.X = marblePosAtArcInvo[currentMarble].X + 0.5 - (0.5 * (sin(1.57079 - (((marblePosition.Y - marblePosAtArcInvo[currentMarble].Y) / 0.7854) * 1.57079))));
		convertedMarblePos.Y = marblePosAtArcInvo[currentMarble].Y + 0.5 * sin(((marblePosition.Y - marblePosAtArcInvo[currentMarble].Y) / 0.7854) * 1.57079);

		break;
	case 6: // marble dir 4 turning right
		if (marblePosAtArcInvo[currentMarble].X - marblePosition.X >= 0.7854)
		{
			marbleIsTurning[currentMarble] = false;
			dirOfMarbles[currentMarble] = 1;
			marbleMovementTracker[currentMarble][0] = 0;
			marbleMovementTracker[currentMarble][1] = -1;
			marblePositions[currentMarble].X = FMath::RoundHalfFromZero(marblePosAtArcInvo[currentMarble].X - 0.5);
			marblePositions[currentMarble].Y = FMath::RoundHalfFromZero(marblePosAtArcInvo[currentMarble].Y) - 0.5;
			convertedMarblePos = marblePositions[currentMarble];
			break;
		}
		convertedMarblePos.X = marblePosAtArcInvo[currentMarble].X - 0.5 * sin(((marblePosAtArcInvo[currentMarble].X - marblePosition.X) / 0.7854) * 1.57079);
		convertedMarblePos.Y = marblePosAtArcInvo[currentMarble].Y - (0.5 - (0.5 * (sin(1.57079 - (((marblePosAtArcInvo[currentMarble].X - marblePosition.X) / 0.7854) * 1.57079)))));

		break;
	case 7: // marble dir 4 turning left
		if (marblePosAtArcInvo[currentMarble].X - marblePosition.X >= 0.7854)
		{
			marbleIsTurning[currentMarble] = false;
			dirOfMarbles[currentMarble] = 3;
			marbleMovementTracker[currentMarble][0] = 0;
			marbleMovementTracker[currentMarble][1] = 1;
			marblePositions[currentMarble].X = FMath::RoundHalfFromZero(marblePosAtArcInvo[currentMarble].X - 0.5);
			marblePositions[currentMarble].Y = FMath::RoundHalfFromZero(marblePosAtArcInvo[currentMarble].Y) + 0.5;
			convertedMarblePos = marblePositions[currentMarble];
			break;
		}
		convertedMarblePos.X = marblePosAtArcInvo[currentMarble].X - 0.5 * sin(((marblePosAtArcInvo[currentMarble].X - marblePosition.X) / 0.7854) * 1.57079);
		convertedMarblePos.Y = marblePosAtArcInvo[currentMarble].Y + (0.5 - (0.5 * sin(1.57079 - (((marblePosition.X - marblePosAtArcInvo[currentMarble].X) / 0.7854) * 1.57079))));

		break;
	default:
		break;
	}

	marblesPosStorage[currentMarble] = convertedMarblePos;
	return convertedMarblePos;
}// to find the halfway point of a turn all you need to do is figure out which direction the marbles are coming from, and then once the marble has passed through 1 quarter of the length of the tile along the axis on which it was originally traveling the marble would be past halfway through a turn. This means also you will need to limit the marbles continuing straight through an intersection to only be allowed to convert to turning within the same window of time, which is not 25% or 50%, it is in fact 39% of the tile.

void STestWidgetThree::AlterMarbleTurn(int originatingIntersection, int currentMarbleIndex) // maybe I should add a sound effect for when a turn correction works, and one for when it doesn't
{
	currentMarbleIndex = marblesInsideIntersections[currentMarbleIndex];

	// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "alterTurn Triggered");

	switch (intersectionsKeys[originatingIntersection])
	{
	case 0: // button from down turning right

		if (marblePositions[currentMarbleIndex].Y > intersectionAlterationBoundaries[originatingIntersection])//REMEMBER: the y axis is inverted so the marble moving down the screen means going up the Y coordinates, and when a marble enters a tile when it's moving straight along a cardinal direction it enters halfway between integers, ie 4.5, 5.5
		{
			// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "alterTurn Engaged | int orientation: " + FString::FromInt(intersectionsKeys[originatingIntersection]) + " | currentMarble: " + FString::FromInt(currentMarbleIndex) + " | marblePosition: " + marblePositions[currentMarbleIndex].ToString() + " | intersectionAlterationBoundary: " + FString::SanitizeFloat(intersectionAlterationBoundaries[originatingIntersection]));

			marblePosAtArcInvo[currentMarbleIndex] = marblePositions[currentMarbleIndex];

			if (intersectionCycle[originatingIntersection] < 2) // this would mean the intersection was turned at time of pressing
			{
				absDistancesToCorrection[currentMarbleIndex].X = marblesPosStorage[currentMarbleIndex].X - marblePositions[currentMarbleIndex].X;
				absDistancesToCorrection[currentMarbleIndex].Y = marblesPosStorage[currentMarbleIndex].Y - (FMath::RoundToZero(marblesPosStorage[currentMarbleIndex].Y) - 0.5);

				coefA = absDistancesToCorrection[currentMarbleIndex].Y / 5;
				coefB = coefA * 4;
				coefF = absDistancesToCorrection[currentMarbleIndex].X;
				coefF = ((coefF / ((coefF / 2) * sin(((1 / coefB) * 3.1416) * (0 + ((coefB / 2) - coefA))) + (coefF / 2))) * coefF) / 2;
				coefH = coefA * 5;
				arcLengthOfAlterations[currentMarbleIndex] = 0;
				distA = (coefB + coefA) / 12;
				distB = coefF;

				for (int a = 1; a <= 12; a++)
				{
					distB = FMath::Abs(distB - (coefF * sin((1 / coefB) * 3.1416 * ( (a * distA) + ( (0.5 * coefB) - coefA) ) ) + coefF));// is coefF correct here or does it need to be doubled?
					arcLengthOfAlterations[currentMarbleIndex] += FMath::Sqrt((distA * distA) + (distB * distB));
				}

				coefI = arcLengthOfAlterations[currentMarbleIndex] * 0.8;
				coefJ = arcLengthOfAlterations[currentMarbleIndex] * 0.2;
				coefV = coefH / (-1 * ( ( (coefF / 2) * sin( (1 / (coefI / 2) ) * 3.1416 * (arcLengthOfAlterations[currentMarbleIndex] + (coefI / 4) ) ) + (coefF / 2) ) - arcLengthOfAlterations[currentMarbleIndex] - coefF) );
				coefFTwo = coefF * sin(((1 / coefI) * 3.1416) * (0 + ((coefI / 2) - coefJ)));

				coefficientsA[currentMarbleIndex] = { coefF, coefFTwo, coefI, coefJ, coefV };

				marblesTurnAlterationToStraight[currentMarbleIndex] = true;
			}
			else 
			{
				if (!marbleTurnAltering[currentMarbleIndex])
				{
					marblesPosStorage[currentMarbleIndex] = marblePositions[currentMarbleIndex];
					marbleIsTurning[currentMarbleIndex] = true;
				}

				absDistancesToCorrection[currentMarbleIndex].X = (marblePositions[currentMarbleIndex].X + 0.5) - marblesPosStorage[currentMarbleIndex].X;
				absDistancesToCorrection[currentMarbleIndex].Y = marblesPosStorage[currentMarbleIndex].Y - FMath::RoundToZero(marblesPosStorage[currentMarbleIndex].Y);

				coefF = absDistancesToCorrection[currentMarbleIndex].Y;
				coefB = coefF * 3.1416;
				arcLengthOfAlterations[currentMarbleIndex] = 0.5 * coefB;
				coefV = (absDistancesToCorrection[currentMarbleIndex].X - (coefF * sin((3.1416 / coefB) * arcLengthOfAlterations[currentMarbleIndex]) ) ) + arcLengthOfAlterations[currentMarbleIndex];

				coefficientsA[currentMarbleIndex] = { coefB, coefF, coefV };

				marblesTurnAlterationToStraight[currentMarbleIndex] = false;
			}

			alterationToExecute[currentMarbleIndex] = 0;
			// marbleIsTurning[currentMarbleIndex] = true; this shouldn't be needed here
			marbleTurnAltering[currentMarbleIndex] = true;
			marblesActualPosAtArcInvo[currentMarbleIndex] = marblesPosStorage[currentMarbleIndex];
		}/*
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "alterTurn disengaged");
		}*/

		break;
	case 1: // button from down turning left

		if (marblePositions[currentMarbleIndex].Y > intersectionAlterationBoundaries[originatingIntersection])//REMEMBER: the y axis is inverted so the marble moving down the screen means going up the Y coordinates, and when a marble enters a tile when it's moving straight along a cardinal direction it enters halfway between integers, ie 4.5, 5.5
		{
			// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "alterTurn Engaged | int orientation: " + FString::FromInt(intersectionsKeys[originatingIntersection]) + " | currentMarble: " + FString::FromInt(currentMarbleIndex) + " | marblePosition: " + marblePositions[currentMarbleIndex].ToString() + " | intersectionAlterationBoundary: " + FString::SanitizeFloat(intersectionAlterationBoundaries[originatingIntersection]));

			marblePosAtArcInvo[currentMarbleIndex] = marblePositions[currentMarbleIndex];

			if (intersectionCycle[originatingIntersection] < 2) // this would mean the intersection was turned at time of pressing
			{
				absDistancesToCorrection[currentMarbleIndex].X = marblePositions[currentMarbleIndex].X - marblesPosStorage[currentMarbleIndex].X;
				absDistancesToCorrection[currentMarbleIndex].Y = marblesPosStorage[currentMarbleIndex].Y - (FMath::RoundToZero(marblesPosStorage[currentMarbleIndex].Y) - 0.5);

				// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "marblePosStorage.Y: " + FString::SanitizeFloat(marblesPosStorage[currentMarbleIndex].Y) + " | absoluteDistanceToCorrection.Y: " + FString::SanitizeFloat(absDistancesToCorrection[currentMarbleIndex].Y) + " | marblePosStorage.X: " + FString::SanitizeFloat(marblesPosStorage[currentMarbleIndex].X) + " | absoluteDistanceToCorrection.X : " + FString::SanitizeFloat(absDistancesToCorrection[currentMarbleIndex].X));


				coefA = absDistancesToCorrection[currentMarbleIndex].Y / 5;
				coefB = coefA * 4;
				coefF = absDistancesToCorrection[currentMarbleIndex].X;
				coefF = ((coefF / ((coefF / 2) * sin(((1 / coefB) * 3.1416) * (0 + ((coefB / 2) - coefA))) + (coefF / 2))) * coefF) / 2;
				coefH = coefA * 5;
				arcLengthOfAlterations[currentMarbleIndex] = 0;
				distA = (coefB + coefA) / 12;
				distB = coefF;

				for (int a = 1; a <= 12; a++)
				{
					distB = FMath::Abs(distB - (coefF * sin((1 / coefB) * 3.1416 * ((a * distA) + ((0.5 * coefB) - coefA))) + coefF));// is coefF correct here or does it need to be doubled?
					arcLengthOfAlterations[currentMarbleIndex] += FMath::Sqrt((distA * distA) + (distB * distB));
				}

				coefI = arcLengthOfAlterations[currentMarbleIndex] * 0.8;
				coefJ = arcLengthOfAlterations[currentMarbleIndex] * 0.2;
				coefV = coefH / (-1 * (((coefF / 2) * sin((1 / (coefI / 2)) * 3.1416 * (arcLengthOfAlterations[currentMarbleIndex] + (coefI / 4))) + (coefF / 2)) - arcLengthOfAlterations[currentMarbleIndex] - coefF));
				coefFTwo = coefF * sin(((1 / coefI) * 3.1416) * (0 + ((coefI / 2) - coefJ)));

				//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "A: " + FString::SanitizeFloat(coefA) + " | B: " + FString::SanitizeFloat(coefB) + " | F: " + FString::SanitizeFloat(coefF) + " | H: " + FString::SanitizeFloat(coefH) + " | arc: " + FString::SanitizeFloat(arcLengthOfAlterations[currentMarbleIndex]) + " | I: " + FString::SanitizeFloat(coefI) + " | J: " + FString::SanitizeFloat(coefJ) + " | V: " + FString::SanitizeFloat(coefV) + " | F2: " + FString::SanitizeFloat(coefFTwo));

				coefficientsA[currentMarbleIndex] = { coefF, coefFTwo, coefI, coefJ, coefV };

				marblesTurnAlterationToStraight[currentMarbleIndex] = true;
			}
			else
			{
				if (!marbleTurnAltering[currentMarbleIndex])
				{
					marblesPosStorage[currentMarbleIndex] = marblePositions[currentMarbleIndex];
					marbleIsTurning[currentMarbleIndex] = true;
				}

				absDistancesToCorrection[currentMarbleIndex].X = marblesPosStorage[currentMarbleIndex].X - (marblePositions[currentMarbleIndex].X - 0.5);
				absDistancesToCorrection[currentMarbleIndex].Y = marblesPosStorage[currentMarbleIndex].Y - FMath::RoundToZero(marblesPosStorage[currentMarbleIndex].Y);

				coefF = absDistancesToCorrection[currentMarbleIndex].Y;
				coefB = coefF * 3.1416;
				arcLengthOfAlterations[currentMarbleIndex] = 0.5 * coefB;
				coefV = (absDistancesToCorrection[currentMarbleIndex].X - (coefF * sin((3.1416 / coefB) * arcLengthOfAlterations[currentMarbleIndex]))) + arcLengthOfAlterations[currentMarbleIndex];

				coefficientsA[currentMarbleIndex] = { coefB, coefF, coefV };

				marblesTurnAlterationToStraight[currentMarbleIndex] = false;
			}

			alterationToExecute[currentMarbleIndex] = 1;
			marbleTurnAltering[currentMarbleIndex] = true;
			marblesActualPosAtArcInvo[currentMarbleIndex] = marblesPosStorage[currentMarbleIndex];
		}/*
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "alterTurn disengaged");
		}*/

		break;
	case 2: // button from left turning right

		if (marblePositions[currentMarbleIndex].X < intersectionAlterationBoundaries[originatingIntersection])//REMEMBER: the y axis is inverted so the marble moving down the screen means going up the Y coordinates, and when a marble enters a tile when it's moving straight along a cardinal direction it enters halfway between integers, ie 4.5, 5.5
		{
			// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "alterTurn Engaged | int orientation: " + FString::FromInt(intersectionsKeys[originatingIntersection]) + " | currentMarble: " + FString::FromInt(currentMarbleIndex) + " | marblePosition: " + marblePositions[currentMarbleIndex].ToString() + " | intersectionAlterationBoundary: " + FString::SanitizeFloat(intersectionAlterationBoundaries[originatingIntersection]));

			marblePosAtArcInvo[currentMarbleIndex] = marblePositions[currentMarbleIndex];

			if (intersectionCycle[originatingIntersection] < 2) // this would mean the intersection was turned at time of pressing
			{
				absDistancesToCorrection[currentMarbleIndex].X = (FMath::RoundFromZero(marblesPosStorage[currentMarbleIndex].X) + 0.5) - marblesPosStorage[currentMarbleIndex].X;
				absDistancesToCorrection[currentMarbleIndex].Y = marblesPosStorage[currentMarbleIndex].Y - marblePositions[currentMarbleIndex].Y;

				coefA = absDistancesToCorrection[currentMarbleIndex].X / 5;
				coefB = coefA * 4;
				coefF = absDistancesToCorrection[currentMarbleIndex].Y;
				coefF = ((coefF / ((coefF / 2) * sin(((1 / coefB) * 3.1416) * (0 + ((coefB / 2) - coefA))) + (coefF / 2))) * coefF) / 2;
				coefH = coefA * 5;
				arcLengthOfAlterations[currentMarbleIndex] = 0;
				distA = (coefB + coefA) / 12;
				distB = coefF;

				for (int a = 1; a <= 12; a++)
				{
					distB = FMath::Abs(distB - (coefF * sin((1 / coefB) * 3.1416 * ((a * distA) + ((0.5 * coefB) - coefA))) + coefF));// is coefF correct here or does it need to be doubled?
					arcLengthOfAlterations[currentMarbleIndex] += FMath::Sqrt((distA * distA) + (distB * distB));
				}

				coefI = arcLengthOfAlterations[currentMarbleIndex] * 0.8;
				coefJ = arcLengthOfAlterations[currentMarbleIndex] * 0.2;
				coefV = coefH / (-1 * (((coefF / 2) * sin((1 / (coefI / 2)) * 3.1416 * (arcLengthOfAlterations[currentMarbleIndex] + (coefI / 4))) + (coefF / 2)) - arcLengthOfAlterations[currentMarbleIndex] - coefF));
				coefFTwo = coefF * sin(((1 / coefI) * 3.1416) * (0 + ((coefI / 2) - coefJ)));

				coefficientsA[currentMarbleIndex] = { coefF, coefFTwo, coefI, coefJ, coefV };

				marblesTurnAlterationToStraight[currentMarbleIndex] = true;
			}
			else
			{
				if (!marbleTurnAltering[currentMarbleIndex])
				{
					marblesPosStorage[currentMarbleIndex] = marblePositions[currentMarbleIndex];
					marbleIsTurning[currentMarbleIndex] = true;
				}

				absDistancesToCorrection[currentMarbleIndex].X = FMath::RoundFromZero(marblesPosStorage[currentMarbleIndex].X) - marblesPosStorage[currentMarbleIndex].X;
				absDistancesToCorrection[currentMarbleIndex].Y = (marblePositions[currentMarbleIndex].Y + 0.5) - marblesPosStorage[currentMarbleIndex].Y;

				coefF = absDistancesToCorrection[currentMarbleIndex].X;
				coefB = coefF * 3.1416;
				arcLengthOfAlterations[currentMarbleIndex] = 0.5 * coefB;
				coefV = (absDistancesToCorrection[currentMarbleIndex].Y - (coefF * sin((3.1416 / coefB) * arcLengthOfAlterations[currentMarbleIndex]))) + arcLengthOfAlterations[currentMarbleIndex];

				coefficientsA[currentMarbleIndex] = { coefB, coefF, coefV };

				marblesTurnAlterationToStraight[currentMarbleIndex] = false;
			}

			alterationToExecute[currentMarbleIndex] = 2;
			// marbleIsTurning[currentMarbleIndex] = true; this shouldn't be needed here
			marbleTurnAltering[currentMarbleIndex] = true;
			marblesActualPosAtArcInvo[currentMarbleIndex] = marblesPosStorage[currentMarbleIndex];
		}/*
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "alterTurn disengaged | marblePosition: " + marblePositions[currentMarbleIndex].ToString() + " | intersectionAlterationBoundary: " + FString::SanitizeFloat(intersectionAlterationBoundaries[originatingIntersection]) + " | intersectionKey: " + FString::FromInt(intersectionsKeys[originatingIntersection]));
		}*/
		break;
	case 3: // button from left turning left

		if (marblePositions[currentMarbleIndex].X < intersectionAlterationBoundaries[originatingIntersection])//REMEMBER: the y axis is inverted so the marble moving down the screen means going up the Y coordinates, and when a marble enters a tile when it's moving straight along a cardinal direction it enters halfway between integers, ie 4.5, 5.5
		{
			// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "alterTurn Engaged | int orientation: " + FString::FromInt(intersectionsKeys[originatingIntersection]) + " | currentMarble: " + FString::FromInt(currentMarbleIndex) + " | marblePosition: " + marblePositions[currentMarbleIndex].ToString() + " | intersectionAlterationBoundary: " + FString::SanitizeFloat(intersectionAlterationBoundaries[originatingIntersection]));

			marblePosAtArcInvo[currentMarbleIndex] = marblePositions[currentMarbleIndex];

			if (intersectionCycle[originatingIntersection] < 2) // this would mean the intersection was turned at time of pressing
			{
				absDistancesToCorrection[currentMarbleIndex].X = (FMath::RoundFromZero(marblesPosStorage[currentMarbleIndex].X) + 0.5) - marblesPosStorage[currentMarbleIndex].X;
				absDistancesToCorrection[currentMarbleIndex].Y = marblePositions[currentMarbleIndex].Y - marblesPosStorage[currentMarbleIndex].Y;

				coefA = absDistancesToCorrection[currentMarbleIndex].X / 5;
				coefB = coefA * 4;
				coefF = absDistancesToCorrection[currentMarbleIndex].Y;
				coefF = ((coefF / ((coefF / 2) * sin(((1 / coefB) * 3.1416) * (0 + ((coefB / 2) - coefA))) + (coefF / 2))) * coefF) / 2;
				coefH = coefA * 5;
				arcLengthOfAlterations[currentMarbleIndex] = 0;
				distA = (coefB + coefA) / 12;
				distB = coefF;

				for (int a = 1; a <= 12; a++)
				{
					distB = FMath::Abs(distB - (coefF * sin((1 / coefB) * 3.1416 * ((a * distA) + ((0.5 * coefB) - coefA))) + coefF));// is coefF correct here or does it need to be doubled?
					arcLengthOfAlterations[currentMarbleIndex] += FMath::Sqrt((distA * distA) + (distB * distB));
				}

				coefI = arcLengthOfAlterations[currentMarbleIndex] * 0.8;
				coefJ = arcLengthOfAlterations[currentMarbleIndex] * 0.2;
				coefV = coefH / (-1 * (((coefF / 2) * sin((1 / (coefI / 2)) * 3.1416 * (arcLengthOfAlterations[currentMarbleIndex] + (coefI / 4))) + (coefF / 2)) - arcLengthOfAlterations[currentMarbleIndex] - coefF));
				coefFTwo = coefF * sin(((1 / coefI) * 3.1416) * (0 + ((coefI / 2) - coefJ)));

				coefficientsA[currentMarbleIndex] = { coefF, coefFTwo, coefI, coefJ, coefV };

				marblesTurnAlterationToStraight[currentMarbleIndex] = true;
			}
			else
			{
				if (!marbleTurnAltering[currentMarbleIndex])
				{
					marblesPosStorage[currentMarbleIndex] = marblePositions[currentMarbleIndex];
					marbleIsTurning[currentMarbleIndex] = true;
				}

				absDistancesToCorrection[currentMarbleIndex].X = FMath::RoundFromZero(marblesPosStorage[currentMarbleIndex].X) - marblesPosStorage[currentMarbleIndex].X;
				absDistancesToCorrection[currentMarbleIndex].Y = marblesPosStorage[currentMarbleIndex].Y - (marblePositions[currentMarbleIndex].Y - 0.5);

				coefF = absDistancesToCorrection[currentMarbleIndex].X;
				coefB = coefF * 3.1416;
				arcLengthOfAlterations[currentMarbleIndex] = 0.5 * coefB;
				coefV = (absDistancesToCorrection[currentMarbleIndex].Y - (coefF * sin((3.1416 / coefB) * arcLengthOfAlterations[currentMarbleIndex]))) + arcLengthOfAlterations[currentMarbleIndex];

				coefficientsA[currentMarbleIndex] = { coefB, coefF, coefV };

				marblesTurnAlterationToStraight[currentMarbleIndex] = false;
			}

			alterationToExecute[currentMarbleIndex] = 3;
			// marbleIsTurning[currentMarbleIndex] = true; this shouldn't be needed here
			marbleTurnAltering[currentMarbleIndex] = true;
			marblesActualPosAtArcInvo[currentMarbleIndex] = marblesPosStorage[currentMarbleIndex];
		}/*
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "alterTurn disengaged | marblePosition: " + marblePositions[currentMarbleIndex].ToString() + " | intersectionAlterationBoundary: " + FString::SanitizeFloat(intersectionAlterationBoundaries[originatingIntersection]) + " | intersectionKey: " + FString::FromInt(intersectionsKeys[originatingIntersection]));
		}*/
		break;
	case 4: // button from right turning right

		if (marblePositions[currentMarbleIndex].X > intersectionAlterationBoundaries[originatingIntersection])//REMEMBER: the y axis is inverted so the marble moving down the screen means going up the Y coordinates, and when a marble enters a tile when it's moving straight along a cardinal direction it enters halfway between integers, ie 4.5, 5.5
		{
			// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "alterTurn Engaged | int orientation: " + FString::FromInt(intersectionsKeys[originatingIntersection]) + " | currentMarble: " + FString::FromInt(currentMarbleIndex) + " | marblePosition: " + marblePositions[currentMarbleIndex].ToString() + " | intersectionAlterationBoundary: " + FString::SanitizeFloat(intersectionAlterationBoundaries[originatingIntersection]));

			marblePosAtArcInvo[currentMarbleIndex] = marblePositions[currentMarbleIndex];

			if (intersectionCycle[originatingIntersection] < 2) // this would mean the intersection was turned at time of pressing
			{
				absDistancesToCorrection[currentMarbleIndex].X = marblesPosStorage[currentMarbleIndex].X - (FMath::RoundToZero(marblesPosStorage[currentMarbleIndex].X) - 0.5);
				absDistancesToCorrection[currentMarbleIndex].Y = marblePositions[currentMarbleIndex].Y - marblesPosStorage[currentMarbleIndex].Y;

				coefA = absDistancesToCorrection[currentMarbleIndex].X / 5;
				coefB = coefA * 4;
				coefF = absDistancesToCorrection[currentMarbleIndex].Y;
				coefF = ((coefF / ((coefF / 2) * sin(((1 / coefB) * 3.1416) * (0 + ((coefB / 2) - coefA))) + (coefF / 2))) * coefF) / 2;
				coefH = coefA * 5;
				arcLengthOfAlterations[currentMarbleIndex] = 0;
				distA = (coefB + coefA) / 12;
				distB = coefF;

				for (int a = 1; a <= 12; a++)
				{
					distB = FMath::Abs(distB - (coefF * sin((1 / coefB) * 3.1416 * ((a * distA) + ((0.5 * coefB) - coefA))) + coefF));// is coefF correct here or does it need to be doubled?
					arcLengthOfAlterations[currentMarbleIndex] += FMath::Sqrt((distA * distA) + (distB * distB));
				}

				coefI = arcLengthOfAlterations[currentMarbleIndex] * 0.8;
				coefJ = arcLengthOfAlterations[currentMarbleIndex] * 0.2;
				coefV = coefH / (-1 * (((coefF / 2) * sin((1 / (coefI / 2)) * 3.1416 * (arcLengthOfAlterations[currentMarbleIndex] + (coefI / 4))) + (coefF / 2)) - arcLengthOfAlterations[currentMarbleIndex] - coefF));
				coefFTwo = coefF * sin(((1 / coefI) * 3.1416) * (0 + ((coefI / 2) - coefJ)));

				coefficientsA[currentMarbleIndex] = { coefF, coefFTwo, coefI, coefJ, coefV };

				marblesTurnAlterationToStraight[currentMarbleIndex] = true;
			}
			else
			{
				if (!marbleTurnAltering[currentMarbleIndex])
				{
					marblesPosStorage[currentMarbleIndex] = marblePositions[currentMarbleIndex];
					marbleIsTurning[currentMarbleIndex] = true;
				}

				absDistancesToCorrection[currentMarbleIndex].X = marblesPosStorage[currentMarbleIndex].X - FMath::RoundToZero(marblesPosStorage[currentMarbleIndex].X);
				absDistancesToCorrection[currentMarbleIndex].Y = marblesPosStorage[currentMarbleIndex].Y - (marblePositions[currentMarbleIndex].Y - 0.5);

				coefF = absDistancesToCorrection[currentMarbleIndex].X;
				coefB = coefF * 3.1416;
				arcLengthOfAlterations[currentMarbleIndex] = 0.5 * coefB;
				coefV = (absDistancesToCorrection[currentMarbleIndex].Y - (coefF * sin((3.1416 / coefB) * arcLengthOfAlterations[currentMarbleIndex]))) + arcLengthOfAlterations[currentMarbleIndex];

				coefficientsA[currentMarbleIndex] = { coefB, coefF, coefV };

				marblesTurnAlterationToStraight[currentMarbleIndex] = false;
			}

			alterationToExecute[currentMarbleIndex] = 4;
			// marbleIsTurning[currentMarbleIndex] = true; this shouldn't be needed here
			marbleTurnAltering[currentMarbleIndex] = true;
			marblesActualPosAtArcInvo[currentMarbleIndex] = marblesPosStorage[currentMarbleIndex];
		}/*
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "alterTurn disengaged | marblePosition: " + marblePositions[currentMarbleIndex].ToString() + " | intersectionAlterationBoundary: " + FString::SanitizeFloat(intersectionAlterationBoundaries[originatingIntersection]) + " | intersectionKey: " + FString::FromInt(intersectionsKeys[originatingIntersection]));
		}*/
		break;
	case 5: // button from right turning left

		if (marblePositions[currentMarbleIndex].X > intersectionAlterationBoundaries[originatingIntersection])//REMEMBER: the y axis is inverted so the marble moving down the screen means going up the Y coordinates, and when a marble enters a tile when it's moving straight along a cardinal direction it enters halfway between integers, ie 4.5, 5.5
		{
			// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "alterTurn Engaged | int orientation: " + FString::FromInt(intersectionsKeys[originatingIntersection]) + " | currentMarble: " + FString::FromInt(currentMarbleIndex) + " | marblePosition: " + marblePositions[currentMarbleIndex].ToString() + " | intersectionAlterationBoundary: " + FString::SanitizeFloat(intersectionAlterationBoundaries[originatingIntersection]));

			marblePosAtArcInvo[currentMarbleIndex] = marblePositions[currentMarbleIndex];

			if (intersectionCycle[originatingIntersection] < 2) // this would mean the intersection was turned at time of pressing
			{
				absDistancesToCorrection[currentMarbleIndex].X = marblesPosStorage[currentMarbleIndex].X - (FMath::RoundToZero(marblesPosStorage[currentMarbleIndex].X) - 0.5);
				absDistancesToCorrection[currentMarbleIndex].Y = marblesPosStorage[currentMarbleIndex].Y - marblePositions[currentMarbleIndex].Y;

				coefA = absDistancesToCorrection[currentMarbleIndex].X / 5;
				coefB = coefA * 4;
				coefF = absDistancesToCorrection[currentMarbleIndex].Y;
				coefF = ((coefF / ((coefF / 2) * sin(((1 / coefB) * 3.1416) * (0 + ((coefB / 2) - coefA))) + (coefF / 2))) * coefF) / 2;
				coefH = coefA * 5;
				arcLengthOfAlterations[currentMarbleIndex] = 0;
				distA = (coefB + coefA) / 12;
				distB = coefF;

				for (int a = 1; a <= 12; a++)
				{
					distB = FMath::Abs(distB - (coefF * sin((1 / coefB) * 3.1416 * ((a * distA) + ((0.5 * coefB) - coefA))) + coefF));// is coefF correct here or does it need to be doubled?
					arcLengthOfAlterations[currentMarbleIndex] += FMath::Sqrt((distA * distA) + (distB * distB));
				}

				coefI = arcLengthOfAlterations[currentMarbleIndex] * 0.8;
				coefJ = arcLengthOfAlterations[currentMarbleIndex] * 0.2;
				coefV = coefH / (-1 * (((coefF / 2) * sin((1 / (coefI / 2)) * 3.1416 * (arcLengthOfAlterations[currentMarbleIndex] + (coefI / 4))) + (coefF / 2)) - arcLengthOfAlterations[currentMarbleIndex] - coefF));
				coefFTwo = coefF * sin(((1 / coefI) * 3.1416) * (0 + ((coefI / 2) - coefJ)));

				coefficientsA[currentMarbleIndex] = { coefF, coefFTwo, coefI, coefJ, coefV };

				marblesTurnAlterationToStraight[currentMarbleIndex] = true;
			}
			else
			{
				if (!marbleTurnAltering[currentMarbleIndex])
				{
					marblesPosStorage[currentMarbleIndex] = marblePositions[currentMarbleIndex];
					marbleIsTurning[currentMarbleIndex] = true;
				}

				absDistancesToCorrection[currentMarbleIndex].X = marblesPosStorage[currentMarbleIndex].X - FMath::RoundToZero(marblesPosStorage[currentMarbleIndex].X);
				absDistancesToCorrection[currentMarbleIndex].Y = (marblePositions[currentMarbleIndex].Y + 0.5) - marblesPosStorage[currentMarbleIndex].Y;

				coefF = absDistancesToCorrection[currentMarbleIndex].X;
				coefB = coefF * 3.1416;
				arcLengthOfAlterations[currentMarbleIndex] = 0.5 * coefB;
				coefV = (absDistancesToCorrection[currentMarbleIndex].Y - (coefF * sin((3.1416 / coefB) * arcLengthOfAlterations[currentMarbleIndex]))) + arcLengthOfAlterations[currentMarbleIndex];

				coefficientsA[currentMarbleIndex] = { coefB, coefF, coefV };

				marblesTurnAlterationToStraight[currentMarbleIndex] = false;
			}

			alterationToExecute[currentMarbleIndex] = 5;
			// marbleIsTurning[currentMarbleIndex] = true; this shouldn't be needed here
			marbleTurnAltering[currentMarbleIndex] = true;
			marblesActualPosAtArcInvo[currentMarbleIndex] = marblesPosStorage[currentMarbleIndex];
		}/*
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "alterTurn disengaged | marblePosition: " + marblePositions[currentMarbleIndex].ToString() + " | intersectionAlterationBoundary: " + FString::SanitizeFloat(intersectionAlterationBoundaries[originatingIntersection]) + " | intersectionKey: " + FString::FromInt(intersectionsKeys[originatingIntersection]));
		}*/
		break;
	case 6: // button from up turning right

		if (marblePositions[currentMarbleIndex].Y < intersectionAlterationBoundaries[originatingIntersection])//REMEMBER: the y axis is inverted so the marble moving down the screen means going up the Y coordinates, and when a marble enters a tile when it's moving straight along a cardinal direction it enters halfway between integers, ie 4.5, 5.5
		{
			// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "alterTurn Engaged | int orientation: " + FString::FromInt(intersectionsKeys[originatingIntersection]) + " | currentMarble: " + FString::FromInt(currentMarbleIndex) + " | marblePosition: " + marblePositions[currentMarbleIndex].ToString() + " | intersectionAlterationBoundary: " + FString::SanitizeFloat(intersectionAlterationBoundaries[originatingIntersection]));

			marblePosAtArcInvo[currentMarbleIndex] = marblePositions[currentMarbleIndex];

			if (intersectionCycle[originatingIntersection] < 2) // this would mean the intersection was turned at time of pressing
			{
				absDistancesToCorrection[currentMarbleIndex].X = marblePositions[currentMarbleIndex].X - marblesPosStorage[currentMarbleIndex].X;
				absDistancesToCorrection[currentMarbleIndex].Y = (FMath::RoundFromZero(marblesPosStorage[currentMarbleIndex].Y) + 0.5) - marblesPosStorage[currentMarbleIndex].Y;

				// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "marblePosStorage.Y: " + FString::SanitizeFloat(marblesPosStorage[currentMarbleIndex].Y) + " | absoluteDistanceToCorrection.Y: " + FString::SanitizeFloat(absDistancesToCorrection[currentMarbleIndex].Y) + " | marblePosStorage.X: " + FString::SanitizeFloat(marblesPosStorage[currentMarbleIndex].X) + " | absoluteDistanceToCorrection.X : " + FString::SanitizeFloat(absDistancesToCorrection[currentMarbleIndex].X));


				coefA = absDistancesToCorrection[currentMarbleIndex].Y / 5;
				coefB = coefA * 4;
				coefF = absDistancesToCorrection[currentMarbleIndex].X;
				coefF = ((coefF / ((coefF / 2) * sin(((1 / coefB) * 3.1416) * (0 + ((coefB / 2) - coefA))) + (coefF / 2))) * coefF) / 2;
				coefH = coefA * 5;
				arcLengthOfAlterations[currentMarbleIndex] = 0;
				distA = (coefB + coefA) / 12;
				distB = coefF;

				for (int a = 1; a <= 12; a++)
				{
					distB = FMath::Abs(distB - (coefF * sin((1 / coefB) * 3.1416 * ((a * distA) + ((0.5 * coefB) - coefA))) + coefF));// is coefF correct here or does it need to be doubled?
					arcLengthOfAlterations[currentMarbleIndex] += FMath::Sqrt((distA * distA) + (distB * distB));
				}

				coefI = arcLengthOfAlterations[currentMarbleIndex] * 0.8;
				coefJ = arcLengthOfAlterations[currentMarbleIndex] * 0.2;
				coefV = coefH / (-1 * (((coefF / 2) * sin((1 / (coefI / 2)) * 3.1416 * (arcLengthOfAlterations[currentMarbleIndex] + (coefI / 4))) + (coefF / 2)) - arcLengthOfAlterations[currentMarbleIndex] - coefF));
				coefFTwo = coefF * sin(((1 / coefI) * 3.1416) * (0 + ((coefI / 2) - coefJ)));

				//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "A: " + FString::SanitizeFloat(coefA) + " | B: " + FString::SanitizeFloat(coefB) + " | F: " + FString::SanitizeFloat(coefF) + " | H: " + FString::SanitizeFloat(coefH) + " | arc: " + FString::SanitizeFloat(arcLengthOfAlterations[currentMarbleIndex]) + " | I: " + FString::SanitizeFloat(coefI) + " | J: " + FString::SanitizeFloat(coefJ) + " | V: " + FString::SanitizeFloat(coefV) + " | F2: " + FString::SanitizeFloat(coefFTwo));

				coefficientsA[currentMarbleIndex] = { coefF, coefFTwo, coefI, coefJ, coefV };

				marblesTurnAlterationToStraight[currentMarbleIndex] = true;
			}
			else
			{
				if (!marbleTurnAltering[currentMarbleIndex])
				{
					marblesPosStorage[currentMarbleIndex] = marblePositions[currentMarbleIndex];
					marbleIsTurning[currentMarbleIndex] = true;
				}

				absDistancesToCorrection[currentMarbleIndex].X = marblesPosStorage[currentMarbleIndex].X - (marblePositions[currentMarbleIndex].X - 0.5);
				absDistancesToCorrection[currentMarbleIndex].Y = FMath::RoundFromZero(marblesPosStorage[currentMarbleIndex].Y) - marblesPosStorage[currentMarbleIndex].Y;

				coefF = absDistancesToCorrection[currentMarbleIndex].Y;
				coefB = coefF * 3.1416;
				arcLengthOfAlterations[currentMarbleIndex] = 0.5 * coefB;
				coefV = (absDistancesToCorrection[currentMarbleIndex].X - (coefF * sin((3.1416 / coefB) * arcLengthOfAlterations[currentMarbleIndex]))) + arcLengthOfAlterations[currentMarbleIndex];

				coefficientsA[currentMarbleIndex] = { coefB, coefF, coefV };

				marblesTurnAlterationToStraight[currentMarbleIndex] = false;
			}

			alterationToExecute[currentMarbleIndex] = 6;
			marbleTurnAltering[currentMarbleIndex] = true;
			marblesActualPosAtArcInvo[currentMarbleIndex] = marblesPosStorage[currentMarbleIndex];
		}/*
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "alterTurn disengaged");
		}*/
		break;
	case 7: // button from up turning left

		if (marblePositions[currentMarbleIndex].Y < intersectionAlterationBoundaries[originatingIntersection])//REMEMBER: the y axis is inverted so the marble moving down the screen means going up the Y coordinates, and when a marble enters a tile when it's moving straight along a cardinal direction it enters halfway between integers, ie 4.5, 5.5
		{
			// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "alterTurn Engaged | int orientation: " + FString::FromInt(intersectionsKeys[originatingIntersection]) + " | currentMarble: " + FString::FromInt(currentMarbleIndex) + " | marblePosition: " + marblePositions[currentMarbleIndex].ToString() + " | intersectionAlterationBoundary: " + FString::SanitizeFloat(intersectionAlterationBoundaries[originatingIntersection]));

			marblePosAtArcInvo[currentMarbleIndex] = marblePositions[currentMarbleIndex];

			if (intersectionCycle[originatingIntersection] < 2) // this would mean the intersection was turned at time of pressing
			{
				absDistancesToCorrection[currentMarbleIndex].X = marblesPosStorage[currentMarbleIndex].X - marblePositions[currentMarbleIndex].X;
				absDistancesToCorrection[currentMarbleIndex].Y = (FMath::RoundFromZero(marblesPosStorage[currentMarbleIndex].Y) + 0.5) - marblesPosStorage[currentMarbleIndex].Y;

				// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "marblePosStorage.Y: " + FString::SanitizeFloat(marblesPosStorage[currentMarbleIndex].Y) + " | absoluteDistanceToCorrection.Y: " + FString::SanitizeFloat(absDistancesToCorrection[currentMarbleIndex].Y) + " | marblePosStorage.X: " + FString::SanitizeFloat(marblesPosStorage[currentMarbleIndex].X) + " | absoluteDistanceToCorrection.X : " + FString::SanitizeFloat(absDistancesToCorrection[currentMarbleIndex].X));


				coefA = absDistancesToCorrection[currentMarbleIndex].Y / 5;
				coefB = coefA * 4;
				coefF = absDistancesToCorrection[currentMarbleIndex].X;
				coefF = ((coefF / ((coefF / 2) * sin(((1 / coefB) * 3.1416) * (0 + ((coefB / 2) - coefA))) + (coefF / 2))) * coefF) / 2;
				coefH = coefA * 5;
				arcLengthOfAlterations[currentMarbleIndex] = 0;
				distA = (coefB + coefA) / 12;
				distB = coefF;

				for (int a = 1; a <= 12; a++)
				{
					distB = FMath::Abs(distB - (coefF * sin((1 / coefB) * 3.1416 * ((a * distA) + ((0.5 * coefB) - coefA))) + coefF));// is coefF correct here or does it need to be doubled?
					arcLengthOfAlterations[currentMarbleIndex] += FMath::Sqrt((distA * distA) + (distB * distB));
				}

				coefI = arcLengthOfAlterations[currentMarbleIndex] * 0.8;
				coefJ = arcLengthOfAlterations[currentMarbleIndex] * 0.2;
				coefV = coefH / (-1 * (((coefF / 2) * sin((1 / (coefI / 2)) * 3.1416 * (arcLengthOfAlterations[currentMarbleIndex] + (coefI / 4))) + (coefF / 2)) - arcLengthOfAlterations[currentMarbleIndex] - coefF));
				coefFTwo = coefF * sin(((1 / coefI) * 3.1416) * (0 + ((coefI / 2) - coefJ)));

				//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "A: " + FString::SanitizeFloat(coefA) + " | B: " + FString::SanitizeFloat(coefB) + " | F: " + FString::SanitizeFloat(coefF) + " | H: " + FString::SanitizeFloat(coefH) + " | arc: " + FString::SanitizeFloat(arcLengthOfAlterations[currentMarbleIndex]) + " | I: " + FString::SanitizeFloat(coefI) + " | J: " + FString::SanitizeFloat(coefJ) + " | V: " + FString::SanitizeFloat(coefV) + " | F2: " + FString::SanitizeFloat(coefFTwo));

				coefficientsA[currentMarbleIndex] = { coefF, coefFTwo, coefI, coefJ, coefV };

				marblesTurnAlterationToStraight[currentMarbleIndex] = true;
			}
			else
			{
				if (!marbleTurnAltering[currentMarbleIndex])
				{
					marblesPosStorage[currentMarbleIndex] = marblePositions[currentMarbleIndex];
					marbleIsTurning[currentMarbleIndex] = true;
				}

				absDistancesToCorrection[currentMarbleIndex].X = (marblePositions[currentMarbleIndex].X + 0.5) - marblesPosStorage[currentMarbleIndex].X;
				absDistancesToCorrection[currentMarbleIndex].Y = FMath::RoundFromZero(marblesPosStorage[currentMarbleIndex].Y) - marblesPosStorage[currentMarbleIndex].Y;

				coefF = absDistancesToCorrection[currentMarbleIndex].Y;
				coefB = coefF * 3.1416;
				arcLengthOfAlterations[currentMarbleIndex] = 0.5 * coefB;
				coefV = (absDistancesToCorrection[currentMarbleIndex].X - (coefF * sin((3.1416 / coefB) * arcLengthOfAlterations[currentMarbleIndex]))) + arcLengthOfAlterations[currentMarbleIndex];

				coefficientsA[currentMarbleIndex] = { coefB, coefF, coefV };

				marblesTurnAlterationToStraight[currentMarbleIndex] = false;
			}

			alterationToExecute[currentMarbleIndex] = 7;
			marbleTurnAltering[currentMarbleIndex] = true;
			marblesActualPosAtArcInvo[currentMarbleIndex] = marblesPosStorage[currentMarbleIndex];
		}/*
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "alterTurn disengaged");
		}*/
		break;
	}
}

FVector2D STestWidgetThree::EnactAlteration(int currentMarble, FVector2D marblePosition)
{
	FVector2D convertedMarblePos;

	// I'm going to need a different way of checking when the alteration is over than how it's done in the turn function. The regular turn function uses the marblePosition but due to the nuance of this alteration functionality the exact marblePosition as calculated in the tick at the time of the completion of the alteration could be somewhat variable. Note: I believe marblePosition is calculated assuming the vector is the center point of the tile. maybe you could add a check in every switch case to see if the marble centerpoint has left the current tile upon completion of the enactAlteration logic for that frame.

	//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "alteringToStraight: " + FString::FromInt(marblesTurnAlterationToStraight[currentMarble]) + " | alteration index" + FString::FromInt(alterationToExecute[currentMarble]) + " | coefX: " + FString::SanitizeFloat(marblePosition.Y - marblePosAtArcInvo[currentMarble].Y) + " | Arc length" + FString::SanitizeFloat(arcLengthOfAlterations[currentMarble]));

	if (marblesTurnAlterationToStraight[currentMarble])
	{
		switch (alterationToExecute[currentMarble])
		{
		case 0: // button from down turning right
			coefX = marblePosAtArcInvo[currentMarble].Y - marblePosition.Y;

			if (coefX > arcLengthOfAlterations[currentMarble])
			{
				marbleIsTurning[currentMarble] = false;
				marbleTurnAltering[currentMarble] = false;
				dirOfMarbles[currentMarble] = 1;
				marbleMovementTracker[currentMarble][0] = 0;
				marbleMovementTracker[currentMarble][1] = -1;
				//marblePositions[currentMarble].X = marblePosAtArcInvo[currentMarble].X; //in this case marblePositions.X will have never been altered.
				marblePositions[currentMarble].Y = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y) - 0.5;
				convertedMarblePos = marblePositions[currentMarble];

				// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "currentMarble at termination: " + FString::FromInt(currentMarble) + " | marblePos.Y: " + FString::SanitizeFloat(FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y) - 0.5));

				break;
			}

			//{ coefF 0, coefFTwo 1, coefI 2, coefJ 3, coefV 4 }
			convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X + ((coefficientsA[currentMarble][0] * sin(((1 / coefficientsA[currentMarble][2]) * 3.1416) * (coefX + ((0.5 * coefficientsA[currentMarble][2]) - coefficientsA[currentMarble][3])))) - coefficientsA[currentMarble][1]);
			convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y - (-1 * ( ( (coefficientsA[currentMarble][0] / 2) * sin( ( (1 / (coefficientsA[currentMarble][2] / 2) ) * 3.1416) * (coefX+(coefficientsA[currentMarble][2]/4) ) ) + (coefficientsA[currentMarble][0] /2) ) - (coefficientsA[currentMarble][4] *coefX) - coefficientsA[currentMarble][0]) );

			break;
		case 1: // button from down turning left
			coefX = marblePosAtArcInvo[currentMarble].Y - marblePosition.Y;

			if (coefX > arcLengthOfAlterations[currentMarble])
			{
				marbleIsTurning[currentMarble] = false;
				marbleTurnAltering[currentMarble] = false;
				dirOfMarbles[currentMarble] = 1;
				marbleMovementTracker[currentMarble][0] = 0;
				marbleMovementTracker[currentMarble][1] = -1;
				//marblePositions[currentMarble].X = FMath::RoundHalfFromZero(marblePosAtArcInvo[currentMarble].X - 0.5); in this case marblePositions.X will have never been altered.
				marblePositions[currentMarble].Y = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y) - 0.5;
				convertedMarblePos = marblePositions[currentMarble];

				// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "currentMarble at termination: " + FString::FromInt(currentMarble) + " | marblePos.Y: " + FString::SanitizeFloat(FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y) - 0.5));

				break;
			}

			//{ coefF 0, coefFTwo 1, coefI 2, coefJ 3, coefV 4 }
			convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X - ((coefficientsA[currentMarble][0] * sin(((1 / coefficientsA[currentMarble][2]) * 3.1416) * (coefX + ((0.5 * coefficientsA[currentMarble][2]) - coefficientsA[currentMarble][3])))) - coefficientsA[currentMarble][1]);
			convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y - (-1 * (((coefficientsA[currentMarble][0] / 2) * sin(((1 / (coefficientsA[currentMarble][2] / 2)) * 3.1416) * (coefX + (coefficientsA[currentMarble][2] / 4))) + (coefficientsA[currentMarble][0] / 2)) - (coefficientsA[currentMarble][4] * coefX) - coefficientsA[currentMarble][0]));

			break;
		case 2: // button from left turning right
			coefX = marblePosition.X - marblePosAtArcInvo[currentMarble].X;

			if (coefX > arcLengthOfAlterations[currentMarble])
			{
				marbleIsTurning[currentMarble] = false;
				marbleTurnAltering[currentMarble] = false;
				dirOfMarbles[currentMarble] = 2;
				marbleMovementTracker[currentMarble][0] = 1;
				marbleMovementTracker[currentMarble][1] = 0;
				marblePositions[currentMarble].X = FMath::RoundFromZero(marblePosAtArcInvo[currentMarble].X) + 0.5;
				//marblePositions[currentMarble].Y = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y) - 0.5;
				convertedMarblePos = marblePositions[currentMarble];

				// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "currentMarble at termination: " + FString::FromInt(currentMarble) + " | marblePos.Y: " + FString::SanitizeFloat(FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y) - 0.5));

				break;
			}

			//{ coefF 0, coefFTwo 1, coefI 2, coefJ 3, coefV 4 }
			convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X + (-1 * (((coefficientsA[currentMarble][0] / 2) * sin(((1 / (coefficientsA[currentMarble][2] / 2)) * 3.1416) * (coefX + (coefficientsA[currentMarble][2] / 4))) + (coefficientsA[currentMarble][0] / 2)) - (coefficientsA[currentMarble][4] * coefX) - coefficientsA[currentMarble][0]));
			convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y + ((coefficientsA[currentMarble][0] * sin(((1 / coefficientsA[currentMarble][2]) * 3.1416) * (coefX + ((0.5 * coefficientsA[currentMarble][2]) - coefficientsA[currentMarble][3])))) - coefficientsA[currentMarble][1]);
			break;
		case 3: // button from left turning left
			coefX = marblePosition.X - marblePosAtArcInvo[currentMarble].X;

			if (coefX > arcLengthOfAlterations[currentMarble])
			{
				marbleIsTurning[currentMarble] = false;
				marbleTurnAltering[currentMarble] = false;
				dirOfMarbles[currentMarble] = 2;
				marbleMovementTracker[currentMarble][0] = 1;
				marbleMovementTracker[currentMarble][1] = 0;
				marblePositions[currentMarble].X = FMath::RoundFromZero(marblePosAtArcInvo[currentMarble].X) + 0.5;
				//marblePositions[currentMarble].Y = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y) - 0.5;
				convertedMarblePos = marblePositions[currentMarble];

				// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "currentMarble at termination: " + FString::FromInt(currentMarble) + " | marblePos.Y: " + FString::SanitizeFloat(FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y) - 0.5));

				break;
			}

			//{ coefF 0, coefFTwo 1, coefI 2, coefJ 3, coefV 4 }
			convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X + (-1 * (((coefficientsA[currentMarble][0] / 2) * sin(((1 / (coefficientsA[currentMarble][2] / 2)) * 3.1416) * (coefX + (coefficientsA[currentMarble][2] / 4))) + (coefficientsA[currentMarble][0] / 2)) - (coefficientsA[currentMarble][4] * coefX) - coefficientsA[currentMarble][0]));
			convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y - ((coefficientsA[currentMarble][0] * sin(((1 / coefficientsA[currentMarble][2]) * 3.1416) * (coefX + ((0.5 * coefficientsA[currentMarble][2]) - coefficientsA[currentMarble][3])))) - coefficientsA[currentMarble][1]);
			break;
		case 4: // button from right turning right
			coefX = marblePosAtArcInvo[currentMarble].X - marblePosition.X;

			if (coefX > arcLengthOfAlterations[currentMarble])
			{
				marbleIsTurning[currentMarble] = false;
				marbleTurnAltering[currentMarble] = false;
				dirOfMarbles[currentMarble] = 4;
				marbleMovementTracker[currentMarble][0] = -1;
				marbleMovementTracker[currentMarble][1] = 0;
				marblePositions[currentMarble].X = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].X) - 0.5;
				//marblePositions[currentMarble].Y = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y) - 0.5;
				convertedMarblePos = marblePositions[currentMarble];

				// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "currentMarble at termination: " + FString::FromInt(currentMarble) + " | marblePos.Y: " + FString::SanitizeFloat(FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y) - 0.5));

				break;
			}

			//{ coefF 0, coefFTwo 1, coefI 2, coefJ 3, coefV 4 }
			convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X - (-1 * (((coefficientsA[currentMarble][0] / 2) * sin(((1 / (coefficientsA[currentMarble][2] / 2)) * 3.1416) * (coefX + (coefficientsA[currentMarble][2] / 4))) + (coefficientsA[currentMarble][0] / 2)) - (coefficientsA[currentMarble][4] * coefX) - coefficientsA[currentMarble][0]));
			convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y - ((coefficientsA[currentMarble][0] * sin(((1 / coefficientsA[currentMarble][2]) * 3.1416) * (coefX + ((0.5 * coefficientsA[currentMarble][2]) - coefficientsA[currentMarble][3])))) - coefficientsA[currentMarble][1]);
			break;
		case 5: // button from right turning left
			coefX = marblePosAtArcInvo[currentMarble].X - marblePosition.X;

			if (coefX > arcLengthOfAlterations[currentMarble])
			{
				marbleIsTurning[currentMarble] = false;
				marbleTurnAltering[currentMarble] = false;
				dirOfMarbles[currentMarble] = 4;
				marbleMovementTracker[currentMarble][0] = -1;
				marbleMovementTracker[currentMarble][1] = 0;
				marblePositions[currentMarble].X = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].X) - 0.5;
				//marblePositions[currentMarble].Y = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y) - 0.5;
				convertedMarblePos = marblePositions[currentMarble];

				// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "currentMarble at termination: " + FString::FromInt(currentMarble) + " | marblePos.Y: " + FString::SanitizeFloat(FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y) - 0.5));

				break;
			}

			//{ coefF 0, coefFTwo 1, coefI 2, coefJ 3, coefV 4 }
			convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X - (-1 * (((coefficientsA[currentMarble][0] / 2) * sin(((1 / (coefficientsA[currentMarble][2] / 2)) * 3.1416) * (coefX + (coefficientsA[currentMarble][2] / 4))) + (coefficientsA[currentMarble][0] / 2)) - (coefficientsA[currentMarble][4] * coefX) - coefficientsA[currentMarble][0]));
			convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y + ((coefficientsA[currentMarble][0] * sin(((1 / coefficientsA[currentMarble][2]) * 3.1416) * (coefX + ((0.5 * coefficientsA[currentMarble][2]) - coefficientsA[currentMarble][3])))) - coefficientsA[currentMarble][1]);
			break;
		case 6: // button from up turning right
			coefX = marblePosition.Y - marblePosAtArcInvo[currentMarble].Y;

			if (coefX > arcLengthOfAlterations[currentMarble])
			{
				marbleIsTurning[currentMarble] = false;
				marbleTurnAltering[currentMarble] = false;
				dirOfMarbles[currentMarble] = 3;
				marbleMovementTracker[currentMarble][0] = 0;
				marbleMovementTracker[currentMarble][1] = 1;
				//marblePositions[currentMarble].X = FMath::RoundHalfFromZero(marblePosAtArcInvo[currentMarble].X - 0.5); in this case marblePositions.X will have never been altered.
				marblePositions[currentMarble].Y = FMath::RoundFromZero(marblePosAtArcInvo[currentMarble].Y) + 0.5;
				convertedMarblePos = marblePositions[currentMarble];

				// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "currentMarble at termination: " + FString::FromInt(currentMarble) + " | marblePos.Y: " + FString::SanitizeFloat(FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y) - 0.5));

				break;
			}

			//{ coefF 0, coefFTwo 1, coefI 2, coefJ 3, coefV 4 }
			convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X - ((coefficientsA[currentMarble][0] * sin(((1 / coefficientsA[currentMarble][2]) * 3.1416) * (coefX + ((0.5 * coefficientsA[currentMarble][2]) - coefficientsA[currentMarble][3])))) - coefficientsA[currentMarble][1]);
			convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y + (-1 * (((coefficientsA[currentMarble][0] / 2) * sin(((1 / (coefficientsA[currentMarble][2] / 2)) * 3.1416) * (coefX + (coefficientsA[currentMarble][2] / 4))) + (coefficientsA[currentMarble][0] / 2)) - (coefficientsA[currentMarble][4] * coefX) - coefficientsA[currentMarble][0]));

			break;
		case 7: // button from up turning left
			coefX = marblePosition.Y - marblePosAtArcInvo[currentMarble].Y;

			if (coefX > arcLengthOfAlterations[currentMarble])
			{
				marbleIsTurning[currentMarble] = false;
				marbleTurnAltering[currentMarble] = false;
				dirOfMarbles[currentMarble] = 3;
				marbleMovementTracker[currentMarble][0] = 0;
				marbleMovementTracker[currentMarble][1] = 1;
				//marblePositions[currentMarble].X = FMath::RoundHalfFromZero(marblePosAtArcInvo[currentMarble].X - 0.5); in this case marblePositions.X will have never been altered.
				marblePositions[currentMarble].Y = FMath::RoundFromZero(marblePosAtArcInvo[currentMarble].Y) + 0.5;
				convertedMarblePos = marblePositions[currentMarble];

				// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "currentMarble at termination: " + FString::FromInt(currentMarble) + " | marblePos.Y: " + FString::SanitizeFloat(FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y) - 0.5));

				break;
			}

			//{ coefF 0, coefFTwo 1, coefI 2, coefJ 3, coefV 4 }
			convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X + ((coefficientsA[currentMarble][0] * sin(((1 / coefficientsA[currentMarble][2]) * 3.1416) * (coefX + ((0.5 * coefficientsA[currentMarble][2]) - coefficientsA[currentMarble][3])))) - coefficientsA[currentMarble][1]);
			convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y + (-1 * (((coefficientsA[currentMarble][0] / 2) * sin(((1 / (coefficientsA[currentMarble][2] / 2)) * 3.1416) * (coefX + (coefficientsA[currentMarble][2] / 4))) + (coefficientsA[currentMarble][0] / 2)) - (coefficientsA[currentMarble][4] * coefX) - coefficientsA[currentMarble][0]));

			break;
		}
	}
	else
	{
		switch (alterationToExecute[currentMarble])
		{
		case 0: // button from down turning right

			coefX = marblePosAtArcInvo[currentMarble].Y - marblePosition.Y;

			if (coefX > arcLengthOfAlterations[currentMarble])
			{
				if (coefX > coefficientsA[currentMarble][2])
				{
					marbleIsTurning[currentMarble] = false;
					marbleTurnAltering[currentMarble] = false;
					dirOfMarbles[currentMarble] = 2;
					marbleMovementTracker[currentMarble][0] = 1;
					marbleMovementTracker[currentMarble][1] = 0;
					marblePositions[currentMarble].X += 0.5;
					marblePositions[currentMarble].Y = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y);
					convertedMarblePos = marblePositions[currentMarble];

					// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "currentMarble at termination: " + FString::FromInt(currentMarble));

					break;
				}

				//{ coefB 0, coefF 1, coefV 2 }
				convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X + coefficientsA[currentMarble][1] + (coefX - arcLengthOfAlterations[currentMarble]);
				convertedMarblePos.Y = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y);
			}
			else
			{
				convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X + ((coefficientsA[currentMarble][1] * sin((3.1416 / coefficientsA[currentMarble][0]) * (coefX - (coefficientsA[currentMarble][0] / 2)))) + coefficientsA[currentMarble][1]);
				convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y - (coefficientsA[currentMarble][1]*sin((3.1416/ coefficientsA[currentMarble][0]) * coefX));
			}
			break;
		case 1: // button from down turning left

			coefX = marblePosAtArcInvo[currentMarble].Y - marblePosition.Y;

			if (coefX > arcLengthOfAlterations[currentMarble])
			{
				if (coefX > coefficientsA[currentMarble][2])
				{
					marbleIsTurning[currentMarble] = false;
					marbleTurnAltering[currentMarble] = false;
					dirOfMarbles[currentMarble] = 4;
					marbleMovementTracker[currentMarble][0] = -1;
					marbleMovementTracker[currentMarble][1] = 0;
					marblePositions[currentMarble].X -= 0.5;
					marblePositions[currentMarble].Y = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y);
					convertedMarblePos = marblePositions[currentMarble];

					// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "currentMarble at termination: " + FString::FromInt(currentMarble));

					break;
				}

				//{ coefB 0, coefF 1, coefV 2 }
				convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X - coefficientsA[currentMarble][1] - (coefX - arcLengthOfAlterations[currentMarble]);;
				convertedMarblePos.Y = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].Y);
			}
			else
			{
				convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X - ((coefficientsA[currentMarble][1] * sin((3.1416 / coefficientsA[currentMarble][0]) * (coefX - (coefficientsA[currentMarble][0] / 2)))) + coefficientsA[currentMarble][1]);
				convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y - (coefficientsA[currentMarble][1] * sin((3.1416 / coefficientsA[currentMarble][0]) * coefX));
			}
			break;
		case 2: // button from left turning right

			coefX = marblePosition.X - marblePosAtArcInvo[currentMarble].X;

			if (coefX > arcLengthOfAlterations[currentMarble])
			{
				if (coefX > coefficientsA[currentMarble][2])
				{
					marbleIsTurning[currentMarble] = false;
					marbleTurnAltering[currentMarble] = false;
					dirOfMarbles[currentMarble] = 3;
					marbleMovementTracker[currentMarble][0] = 0;
					marbleMovementTracker[currentMarble][1] = 1;
					marblePositions[currentMarble].X = FMath::RoundFromZero(marblePosAtArcInvo[currentMarble].X);
					marblePositions[currentMarble].Y += 0.5;
					convertedMarblePos = marblePositions[currentMarble];

					// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "currentMarble at termination: " + FString::FromInt(currentMarble));

					break;
				}

				//{ coefB 0, coefF 1, coefV 2 }
				convertedMarblePos.X = FMath::RoundFromZero(marblePosAtArcInvo[currentMarble].X);
				convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y + coefficientsA[currentMarble][1] + (coefX - arcLengthOfAlterations[currentMarble]);
				//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, " 2-2 | convertedMarblePos: " + convertedMarblePos.ToString());
			}
			else
			{
				convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X + (coefficientsA[currentMarble][1] * sin((3.1416 / coefficientsA[currentMarble][0]) * coefX));
				convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y + ((coefficientsA[currentMarble][1] * sin((3.1416 / coefficientsA[currentMarble][0]) * (coefX - (coefficientsA[currentMarble][0] / 2)))) + coefficientsA[currentMarble][1]);
				//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, " 2-1 | convertedMarblePos: " + convertedMarblePos.ToString());
			}
			break;
		case 3: // button from left turning left

			coefX = marblePosition.X - marblePosAtArcInvo[currentMarble].X;

			if (coefX > arcLengthOfAlterations[currentMarble])
			{
				if (coefX > coefficientsA[currentMarble][2])
				{
					marbleIsTurning[currentMarble] = false;
					marbleTurnAltering[currentMarble] = false;
					dirOfMarbles[currentMarble] = 1;
					marbleMovementTracker[currentMarble][0] = 0;
					marbleMovementTracker[currentMarble][1] = -1;
					marblePositions[currentMarble].X = FMath::RoundFromZero(marblePosAtArcInvo[currentMarble].X);
					marblePositions[currentMarble].Y -= 0.5;
					convertedMarblePos = marblePositions[currentMarble];

					// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "currentMarble at termination: " + FString::FromInt(currentMarble));

					break;
				}

				//{ coefB 0, coefF 1, coefV 2 }
				convertedMarblePos.X = FMath::RoundFromZero(marblePosAtArcInvo[currentMarble].X);
				convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y - coefficientsA[currentMarble][1] - (coefX - arcLengthOfAlterations[currentMarble]);
				//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, " 2-2 | convertedMarblePos: " + convertedMarblePos.ToString());
			}
			else
			{
				convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X + (coefficientsA[currentMarble][1] * sin((3.1416 / coefficientsA[currentMarble][0]) * coefX));
				convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y - ((coefficientsA[currentMarble][1] * sin((3.1416 / coefficientsA[currentMarble][0]) * (coefX - (coefficientsA[currentMarble][0] / 2)))) + coefficientsA[currentMarble][1]);
				//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, " 2-1 | convertedMarblePos: " + convertedMarblePos.ToString());
			}
			break;
		case 4: // button from right turning right

			coefX = marblePosAtArcInvo[currentMarble].X - marblePosition.X;

			if (coefX > arcLengthOfAlterations[currentMarble])
			{
				if (coefX > coefficientsA[currentMarble][2])
				{
					marbleIsTurning[currentMarble] = false;
					marbleTurnAltering[currentMarble] = false;
					dirOfMarbles[currentMarble] = 1;
					marbleMovementTracker[currentMarble][0] = 0;
					marbleMovementTracker[currentMarble][1] = -1;
					marblePositions[currentMarble].X = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].X);
					marblePositions[currentMarble].Y -= 0.5;
					convertedMarblePos = marblePositions[currentMarble];

					// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "currentMarble at termination: " + FString::FromInt(currentMarble));

					break;
				}

				//{ coefB 0, coefF 1, coefV 2 }
				convertedMarblePos.X = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].X);
				convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y - coefficientsA[currentMarble][1] - (coefX - arcLengthOfAlterations[currentMarble]);
				//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, " 2-2 | convertedMarblePos: " + convertedMarblePos.ToString());
			}
			else
			{
				convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X - (coefficientsA[currentMarble][1] * sin((3.1416 / coefficientsA[currentMarble][0]) * coefX));
				convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y - ((coefficientsA[currentMarble][1] * sin((3.1416 / coefficientsA[currentMarble][0]) * (coefX - (coefficientsA[currentMarble][0] / 2)))) + coefficientsA[currentMarble][1]);
				//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, " 2-1 | convertedMarblePos: " + convertedMarblePos.ToString());
			}
			break;
		case 5: // button from right turning left

			coefX = marblePosAtArcInvo[currentMarble].X - marblePosition.X;

			if (coefX > arcLengthOfAlterations[currentMarble])
			{
				if (coefX > coefficientsA[currentMarble][2])
				{
					marbleIsTurning[currentMarble] = false;
					marbleTurnAltering[currentMarble] = false;
					dirOfMarbles[currentMarble] = 3;
					marbleMovementTracker[currentMarble][0] = 0;
					marbleMovementTracker[currentMarble][1] = 1;
					marblePositions[currentMarble].X = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].X);
					marblePositions[currentMarble].Y += 0.5;
					convertedMarblePos = marblePositions[currentMarble];

					// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "currentMarble at termination: " + FString::FromInt(currentMarble));

					break;
				}

				//{ coefB 0, coefF 1, coefV 2 }
				convertedMarblePos.X = FMath::RoundToZero(marblePosAtArcInvo[currentMarble].X);
				convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y + coefficientsA[currentMarble][1] + (coefX - arcLengthOfAlterations[currentMarble]);
				//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, " 2-2 | convertedMarblePos: " + convertedMarblePos.ToString());
			}
			else
			{
				convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X - (coefficientsA[currentMarble][1] * sin((3.1416 / coefficientsA[currentMarble][0]) * coefX));
				convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y + ((coefficientsA[currentMarble][1] * sin((3.1416 / coefficientsA[currentMarble][0]) * (coefX - (coefficientsA[currentMarble][0] / 2)))) + coefficientsA[currentMarble][1]);
				//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, " 2-1 | convertedMarblePos: " + convertedMarblePos.ToString());
			}
			break;
		case 6: // button from up turning right

			coefX = marblePosition.Y - marblePosAtArcInvo[currentMarble].Y;

			if (coefX > arcLengthOfAlterations[currentMarble])
			{
				if (coefX > coefficientsA[currentMarble][2])
				{
					marbleIsTurning[currentMarble] = false;
					marbleTurnAltering[currentMarble] = false;
					dirOfMarbles[currentMarble] = 4;
					marbleMovementTracker[currentMarble][0] = -1;
					marbleMovementTracker[currentMarble][1] = 0;
					marblePositions[currentMarble].X -= 0.5;
					marblePositions[currentMarble].Y = FMath::RoundFromZero(marblePosAtArcInvo[currentMarble].Y);
					convertedMarblePos = marblePositions[currentMarble];

					// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "currentMarble at termination: " + FString::FromInt(currentMarble));

					break;
				}

				//{ coefB 0, coefF 1, coefV 2 }
				convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X - coefficientsA[currentMarble][1] - (coefX - arcLengthOfAlterations[currentMarble]);;
				convertedMarblePos.Y = FMath::RoundFromZero(marblePosAtArcInvo[currentMarble].Y);
			}
			else
			{
				convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X - ((coefficientsA[currentMarble][1] * sin((3.1416 / coefficientsA[currentMarble][0]) * (coefX - (coefficientsA[currentMarble][0] / 2)))) + coefficientsA[currentMarble][1]);
				convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y + (coefficientsA[currentMarble][1] * sin((3.1416 / coefficientsA[currentMarble][0]) * coefX));
			}
			break;
		case 7: // button from up turning left

			coefX = marblePosition.Y - marblePosAtArcInvo[currentMarble].Y;

			if (coefX > arcLengthOfAlterations[currentMarble])
			{
				if (coefX > coefficientsA[currentMarble][2])
				{
					marbleIsTurning[currentMarble] = false;
					marbleTurnAltering[currentMarble] = false;
					dirOfMarbles[currentMarble] = 2;
					marbleMovementTracker[currentMarble][0] = 1;
					marbleMovementTracker[currentMarble][1] = 0;
					marblePositions[currentMarble].X += 0.5;
					marblePositions[currentMarble].Y = FMath::RoundFromZero(marblePosAtArcInvo[currentMarble].Y);
					convertedMarblePos = marblePositions[currentMarble];

					// GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "currentMarble at termination: " + FString::FromInt(currentMarble));

					break;
				}

				//{ coefB 0, coefF 1, coefV 2 }
				convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X + coefficientsA[currentMarble][1] + (coefX - arcLengthOfAlterations[currentMarble]);;
				convertedMarblePos.Y = FMath::RoundFromZero(marblePosAtArcInvo[currentMarble].Y);
			}
			else
			{
				convertedMarblePos.X = marblesActualPosAtArcInvo[currentMarble].X + ((coefficientsA[currentMarble][1] * sin((3.1416 / coefficientsA[currentMarble][0]) * (coefX - (coefficientsA[currentMarble][0] / 2)))) + coefficientsA[currentMarble][1]);
				convertedMarblePos.Y = marblesActualPosAtArcInvo[currentMarble].Y + (coefficientsA[currentMarble][1] * sin((3.1416 / coefficientsA[currentMarble][0]) * coefX));
			}
			break;
		}
	}

	marblesPosStorage[currentMarble] = convertedMarblePos;

	//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "convertedMarblePos: " + convertedMarblePos.ToString());

	return convertedMarblePos;
}

void STestWidgetThree::PlayGame()
{
	paused = false;

	switch (environmentAudio)
	{
	case 0:
		windAudioComponents[audioCycleTracker % 2]->SetPaused(false);

		riverAudioComponents[audioCycleTracker % 2]->SetPaused(false);
		break;
	case 1:
		windAudioComponents[audioCycleTracker % 2]->SetPaused(false);

		waterfallAudioComponents[audioCycleTracker % 2]->SetPaused(false);
		break;
	default:
		break;
	}

	if (songAudioComponents[songPlayingIndex]->IsPlaying())
	{
		songAudioComponents[songPlayingIndex]->SetPaused(false);
	}
}

//okay. Now, here in this tick create a new partition in which you will check if autoCursorModeOn, if it is find the mouse screen position, find the nearest intersection to the current mouse position, and if that intersection is different than the one last frame move the auto cursor to the new location, recording the new location 

void STestWidgetThree::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	//the quantity of ticks that happen per second directly factors into the turning process, you need to know it and it needs to be stable. adendum: Needs?
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	if (autoCursorModeOn)
	{
		intersectionDistancesFromMouse.Empty();

		playerOnePlayerController->GetMousePosition(mouseX, mouseY);//my tests prove mouseX and mouseY are in relation to viewportSize as defined above. note mouseX works from left to right, but mouse y works from top to bottom
		//so now convert mouseX and Y positions into tile coords. the same format of tileCoords which the intersectionCycle indices are based on.
		for (int a = 0; a < intersectionTileLocations.Num(); a++)
		{
			intersectionDistancesFromMouse.Add(FMath::Sqrt(FMath::Abs((intersectionTileLocations[a].X - mouseX) * (intersectionTileLocations[a].X - mouseX)) + FMath::Abs((intersectionTileLocations[a].Y - mouseY) * (intersectionTileLocations[a].Y - mouseY))));
		}

		distanceBetweenMouseAndIntersectionFloatOne = intersectionDistancesFromMouse[0];
		tempIndexOfIntersectionInFocus = 0;
		for (int a = 1; a < intersectionDistancesFromMouse.Num(); a++)
		{
			if (distanceBetweenMouseAndIntersectionFloatOne > intersectionDistancesFromMouse[a])
			{
				distanceBetweenMouseAndIntersectionFloatOne = intersectionDistancesFromMouse[a];
				tempIndexOfIntersectionInFocus = a;
			}
		}

		if (!indexOfIntersectionInFocusSafety)
		{
			indexOfIntersectionInFocus = tempIndexOfIntersectionInFocus;
		}

		focusCursorBox->SetPadding(CalculateLargeTilePosition( FVector2D(intersectionPositions[indexOfIntersectionInFocus].X -1, intersectionPositions[indexOfIntersectionInFocus].Y - 1), adjustedViewportSize)); //if an intersection is ever on the edge of the screen on the top or left of the screen the focusCursor should display partly off screen with this operation
	}

	if (paused == false)
	{
		audioTimer += InDeltaTime;

		if (audioCycleTracker < FMath::DivideAndRoundDown((int)audioTimer, 120))
		{
			audioCycleTracker += 1;

			switch (environmentAudio)
			{
			case 0:
				windAudioComponents[audioCycleTracker % 2]->Play();

				riverAudioComponents[audioCycleTracker % 2]->Play();
				break;
			case 1:
				windAudioComponents[audioCycleTracker % 2]->Play();

				waterfallAudioComponents[audioCycleTracker % 2]->Play();
				break;
			default:
				break;
			}
		}

		if (!songBool)
		{
			if (audioTimer > 20)
			{
				currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));

				if (songPlaying)
				{
					if (!songAudioComponents[songPlayingIndex]->IsPlaying())//I need to check if this works as expected but Im guessing it does
					{//to test if all of this song credits programming complexity actually worked go into credits, play song. go into game, keep restarting until song ends. then see if new song picks up 
						if (currentSave->GetSongIndexArr().Num() > 0)
						{
							songPlayingIndex = currentSave->GetSongIndexArr().Last();
							songAudioComponents[songPlayingIndex]->Play();
							OwningHUD->songPlayingIndex = songPlayingIndex;
							OwningHUD->songPlaying = false;

							OwningHUD->UpdateSongArr();
						}
					}
				}
				else
				{
					if (currentSave->GetSongIndexArr().Num() > 0)//not only do I have to fix this, but also I have to fix what happens if songs settings are altered during the game. what happens if I deactivate the song currently playing in game for instance?
					{
						songPlayingIndex = currentSave->GetSongIndexArr().Last();
						songAudioComponents[songPlayingIndex]->Play();
						OwningHUD->songPlayingIndex = songPlayingIndex;

						OwningHUD->UpdateSongArr();
					}
				}

				songBool = true;
			}

		}


		for (int a = 0; a < activeMarbles.Num(); a++)
		{
			marblePositions[a].X += InDeltaTime * speedMultiplier * marbleMovementTracker[a][0];
			marblePositions[a].Y += InDeltaTime * speedMultiplier * marbleMovementTracker[a][1];

			if (marbleIsTurning[a])
			{
				if (marbleTurnAltering[a])
				{
					activeMarbles[a]->SetPadding(CalculateTilePosition(EnactAlteration(a, marblePositions[a]), adjustedViewportSize));
				}
				else
				{
					activeMarbles[a]->SetPadding(CalculateTilePosition(TurnMarble(a, marblePositions[a]), adjustedViewportSize));
				}
			}
			else
			{
				if (CalculateMarblePositionCenters(marblePositions[a]) == marblePositionsCenters[a])
				{
					activeMarbles[a]->SetPadding(CalculateTilePosition(marblePositions[a], adjustedViewportSize));
				}
				else
				{
					marblePositionsCenters[a] = CalculateMarblePositionCenters(marblePositions[a]);//this creates an index out of bounds error if the marble goes off screen

					if (marblesInsideIntersections.Find(a) + 1)
					{
						//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "currentMarble: " + FString::FromInt(a) + " | corresponding index within MII: " + FString::FromInt(marblesInsideIntersections[marblesInsideIntersections.Find(a)]) + " | num of MII: " + FString::FromInt(marblesInsideIntersections.Num()));

						intersectionsContainingMarbles.RemoveAt(marblesInsideIntersections.Find(a));
						marblesInsideIntersections.RemoveAt(marblesInsideIntersections.Find(a));

						//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "num of MII after currentMarble removal: " + FString::FromInt(marblesInsideIntersections.Num()));
					}

					if (trackArr[marblePositionsCenters[a].Y * 15 + marblePositionsCenters[a].X] > 2 || tileIsIntersection[marblePositionsCenters[a].Y * 15 + marblePositionsCenters[a].X])//I need to redo how intersections are designated in trackArr so I dont need to include this check for tileIsIntersection in this conditional
					{
						if (tileIsIntersection[marblePositionsCenters[a].Y * 15 + marblePositionsCenters[a].X])
						{
							marblesInsideIntersections.Add(a);
							intersectionsContainingMarbles.Add(marblePositionsCenters[a].Y * 15 + marblePositionsCenters[a].X);

							if (intersectionCycle[intersectionPositions.Find(marblePositionsCenters[a])] > 1)//an error has occured here but only because the marbles were falling of the track unexpectedly after turns
							{
								marbleIsTurning[a] = true;
								activeMarbles[a]->SetPadding(CalculateTilePosition(PrepTurnMarble(a, marblePositions[a], dirOfMarbles[a], true, trackArr[marblePositionsCenters[a].Y * 15 + marblePositionsCenters[a].X]), adjustedViewportSize));
							}
						}
						else
						{
							marbleIsTurning[a] = true;
							activeMarbles[a]->SetPadding(CalculateTilePosition(PrepTurnMarble(a, marblePositions[a], dirOfMarbles[a], false, trackArr[marblePositionsCenters[a].Y * 15 + marblePositionsCenters[a].X]), adjustedViewportSize));
						}
					}
					else if (holePositions.Find(marblePositionsCenters[a]) + 1)
					{//check if the marble matches the flag, "remove" the marble and adjust the score accordingly

						if (holePositions.Find(marblePositionsCenters[a]) == marblesRandomized.Find(activeMarblesContent[a]))
						{
							playerScore += 1;
							maximumPossibleScore += 1;
							currentScore = FText::FromString("Score: " + FString::FromInt(playerScore) + " of " + FString::FromInt(maximumPossibleScore));
							scoreText->SetText(currentScore);
							scoringAudioComponents[scoringSoundEffectIndex]->Stop();

							switch (scoringSoundEffectIndex)
							{
							case 0:
								scoringSoundEffectIndex = FMath::RandRange(1, 2);
								break;
							case 1:
								scoringSoundEffectIndex = FMath::RandRange(1, 2);

								if (scoringSoundEffectIndex == 1)
								{
									scoringSoundEffectIndex = 0;
								}
								break;
							case 2:
								scoringSoundEffectIndex = FMath::RandRange(0, 1);
								break;
							default:
								break;
							}
							scoringAudioComponents[scoringSoundEffectIndex]->Play();
						}
						else
						{
							maximumPossibleScore += 1;
							currentScore = FText::FromString("Score: " + FString::FromInt(playerScore) + " of " + FString::FromInt(maximumPossibleScore));
							scoreText->SetText(currentScore);
							missAudioComponent->Stop();
							missAudioComponent->Play();
						}
						marblesToBeDestroyed.Add(activeMarbles[a]);
						marblesToBeDestroyedMovementTracker.Add(marbleMovementTracker[a]);
						marblesToBeDestroyedPosition.Add(marblePositions[a]);
						marblesBeingDestroyedTime.Add(0);

						activeMarblesContent.RemoveAt(a);
						marbleMovementTracker.RemoveAt(a);
						marblePositions.RemoveAt(a);
						marblePositionsCenters.RemoveAt(a);
						marbleIsTurning.RemoveAt(a);
						marbleTurnAltering.RemoveAt(a);
						marblesTurnAlterationToStraight.RemoveAt(a);
						absDistancesToCorrection.RemoveAt(a);
						alterationToExecute.RemoveAt(a);
						marblesPosStorage.RemoveAt(a);
						marblesActualPosAtArcInvo.RemoveAt(a);
						arcLengthOfAlterations.RemoveAt(a);
						coefficientsA.RemoveAt(a);
						dirOfMarbles.RemoveAt(a);
						turnToExecute.RemoveAt(a);
						marblePosAtArcInvo.RemoveAt(a);
						activeMarbles.RemoveAt(a);

						for (int b = 0; b < marblesInsideIntersections.Num(); b++)
						{
							if (marblesInsideIntersections[b] > a)
							{
								marblesInsideIntersections[b] -= 1;
							}
						}

						a -= 1; // just added this 05/10/25, seems like it really should be here. but what if a is on the last index of activeMarbles, and this happens? if the loop doesn't check the termination reinitialize the termination condition every loop you'll see a crash.
					}
				}
			}
		}

		for (int a = 0; a < marblesToBeDestroyed.Num(); a++)
		{
			marblesBeingDestroyedTime[a] += InDeltaTime;

			marblesToBeDestroyedPosition[a].X += InDeltaTime * speedMultiplier * marblesToBeDestroyedMovementTracker[a][0];
			marblesToBeDestroyedPosition[a].Y += InDeltaTime * speedMultiplier * marblesToBeDestroyedMovementTracker[a][1];

			marbleToBeDestroyedPadding = CalculateTilePosition(marblesToBeDestroyedPosition[a], adjustedViewportSize);
			marblesToBeDestroyed[a]->SetPadding(marbleToBeDestroyedPadding);

			if (marblesBeingDestroyedTime[a] > (1 / speedMultiplier) / 4)
			{
				marblesToBeDestroyed[a]->SetPadding(ShrinkMarble(marbleToBeDestroyedPadding, (marblesBeingDestroyedTime[a] - (1 / speedMultiplier) / 4) / ((1 / speedMultiplier) / 4)));

				if (marblesBeingDestroyedTime[a] > (1 / speedMultiplier) / 2)
				{
					marblesToBeDestroyedMovementTracker.RemoveAt(a);
					marblesToBeDestroyedPosition.RemoveAt(a);
					marblesBeingDestroyedTime.RemoveAt(a);
					marbleOverlay->RemoveSlot(marblesToBeDestroyed[a].ToSharedRef());
					marblesToBeDestroyed.RemoveAt(a);

					a -= 1;

					if (activeMarbles.Num() == 0)
					{//curtains into main menu results screen and update the save file
						finalScore = playerScore * pow(1.2, holePositions.Num() - 3);

						if (playerScore >= maximumPossibleScore - 1 && holePositions.Num() < 16)
						{
							if (holePositions.Num() - 2 > maxLevel)
							{
								maxLevel += 1;
								OwningHUD->newMaxLevel = true;
								OwningHUD->MakeAchievement(maxLevel);
							}
						}

						for (int b = 0; b < highscores.Num(); b++)
						{
							if (finalScore > highscores[b])
							{
								highscores.Insert(finalScore, b);
								highscores.RemoveAt(3);
								break;//if this doesnt break the loop the logic here will be faulty.. wait is this breaking
							}
						}

						highscoreDataOne = holePositions.Num() - 3;
						highscoreDataTwo = playerScore;
						scoreThisGame = finalScore;

						OwningHUD->SaveGame(maxLevel, highscores, highscoreDataOne, highscoreDataTwo, scoreThisGame);

						OwningHUD->songPlaying = false;
						OwningHUD->songPlayingIndex = songPlayingIndex;

						OwningHUD->DisplayCurtains(0, false, true);
					}
				}
			}
		}

		if (!gameEnded)
		{
			if (gameStarted)
			{
				fCurrentTime += InDeltaTime;

				if (fCurrentTime > timeIntoWindowMarbleIsSpawned[marbleIndexToSpawn])
				{
					activeMarbles.Add(SNew(SBox));
					activeMarbles[activeMarbles.Num() - 1]->SetContent(SNew(SImage).Image(marblesThisGame[marbleIndexToSpawn]));
					activeMarbles[activeMarbles.Num() - 1]->SetPadding(CalculateTilePosition(startingPos, adjustedViewportSize));
					activeMarblesContent.Add(marblesThisGame[marbleIndexToSpawn]);

					marbleOverlay->AddSlot()
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						[
							activeMarbles[activeMarbles.Num() - 1].ToSharedRef()
						];

					marbleMovementTracker.Add(startingMarbleMovementTracker);
					marblePositions.Add(startingPos);
					marblePositionsCenters.Add(startingPos);
					marbleIsTurning.Add(false);
					marbleTurnAltering.Add(false);
					marblesTurnAlterationToStraight.Add(false);
					absDistancesToCorrection.Add(FVector2D(0, 0));
					alterationToExecute.Add(0);
					marblesPosStorage.Add(FVector2D(0, 0));
					marblesActualPosAtArcInvo.Add(FVector2D(0, 0));
					arcLengthOfAlterations.Add(0);
					coefficientsA.Add({ 0 });
					dirOfMarbles.Add(startingDir);
					turnToExecute.Add(0);
					marblePosAtArcInvo.Add(FVector2D(0, 0));

					marbleIndexToSpawn += 1;
				}

				if (currentTime != timeOfGame - FMath::RoundToZero(fCurrentTime))
				{
					currentTime = timeOfGame - FMath::RoundToZero(fCurrentTime);

					currentTimeText = FText::FromString("Time: " + FString::FromInt(FMath::RoundToZero((double)currentTime / 60)) + ":" + FString::FromInt(currentTime % 60));
					timeText->SetText(currentTimeText);

					if (currentTime == 0)
					{
						gameEnded = true;
					}
				}
			}
			else
			{
				startingTime += InDeltaTime;

				if (startingTime > 6)
				{
					if (startingTime > 10)
					{
						gameStarted = true;
						countdownOverlay->RemoveSlot(countdownBox.ToSharedRef());
					}
					else if (startingTime > 9)
					{
						if (!goDisplayed)
						{
							goDisplayed = true;
							startingFontSize = countdownFont.Size;
							growingFontSize = 0;
							startingOpacity = 0;
							growingOpacity = 0;
							shiftingFont = countdownFont;
							startingMargin = countdownMargin;
							growingMargin = countdownMargin;
							countdownText->SetText(FText::FromString("GO"));
							countdownEffectClock = 0.0;
							growingText->SetColorAndOpacity(FLinearColor(1, 1, 1, growingOpacity));
							growingText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, growingOpacity));
							growingBox->SetPadding(growingMargin);
							growingText->SetFont(countdownFont);
						}
					}
					else if (startingTime > 8)
					{
						if (!oneDisplayed)
						{
							oneDisplayed = true;
							startingFontSize = countdownFont.Size;
							growingFontSize = 0;
							startingOpacity = 0;
							growingOpacity = 0;
							shiftingFont = countdownFont;
							startingMargin = countdownMargin;
							growingMargin = countdownMargin;
							countdownText->SetText(FText::FromString("1"));
							countdownEffectClock = 0.0;
							growingText->SetColorAndOpacity(FLinearColor(1, 1, 1, growingOpacity));
							growingText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, growingOpacity));
							growingBox->SetPadding(growingMargin);
							growingText->SetFont(countdownFont);
						}
					}
					else if (startingTime > 7)
					{
						if (!twoDisplayed)
						{
							twoDisplayed = true;
							startingFontSize = countdownFont.Size;
							growingFontSize = 0;
							startingOpacity = 0;
							growingOpacity = 0;
							shiftingFont = countdownFont;
							startingMargin = countdownMargin;
							growingMargin = countdownMargin;
							countdownText->SetText(FText::FromString("2"));
							countdownEffectClock = 0.0;
							growingText->SetColorAndOpacity(FLinearColor(1, 1, 1, growingOpacity));
							growingText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, growingOpacity));
							growingBox->SetPadding(growingMargin);
							growingText->SetFont(countdownFont);
						}
					}
					if (!threeDisplayed)
					{
						threeDisplayed = true;
						startingFontSize = countdownFont.Size;
						growingFontSize = 0;
						startingOpacity = 0;
						growingOpacity = 0;
						shiftingFont = countdownFont;
						growingText = countdownText;
						growingBox = countdownBox;
						startingMargin = countdownMargin;
						growingMargin = countdownMargin;
						countdownText->SetText(FText::FromString("3"));//usually you would use FText::FromString("Play") but if this works alls the better
						countdownEffectClock = 0.0;
					}

					countdownEffectClock += InDeltaTime;

					if (countdownEffectClock < 0.33)
					{
						growingMargin = GrowCountdownMargin(startingMargin);
						growingOpacity = (0.5 * sin(9.42 * (countdownEffectClock - 0.167))) + 0.5; //I think this will work
						growingFontSize = startingFontSize + (adjustedStartingFontSize * sin(9.42 * (countdownEffectClock - 0.167))) + adjustedStartingFontSize;

						growingBox->SetPadding(growingMargin);
						shiftingFont.Size = growingFontSize;
						growingText->SetFont(shiftingFont);
						growingText->SetColorAndOpacity(FLinearColor(1, 1, 1, growingOpacity));
						growingText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, growingOpacity));
					}
					else if (countdownEffectClock > 0.833)
					{

					}
					else if (countdownEffectClock > 0.666)
					{
						//growingMargin = GrowCountdownMargin(startingMargin);
						growingOpacity = 1 - ((0.5 * sin(18.85 * ((countdownEffectClock - 0.666) - 0.083))) + 0.5);
						//growingFontSize = 0.1 - (adjustedStartingFontSize * sin(18.85 * ((countdownEffectClock - 0.666) - 0.083))) + adjustedStartingFontSize;

						//growingBox->SetPadding(growingMargin);
						//shiftingFont.Size = growingFontSize;
						//growingText->SetFont(shiftingFont);
						growingText->SetColorAndOpacity(FLinearColor(1, 1, 1, growingOpacity));
						growingText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, growingOpacity));
					}
				}
			}
		}

	}
}

#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
