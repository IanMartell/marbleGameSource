// Fill out your copyright notice in the Description page of Project Settings.

#include "STestWidgetThree.h"
#include <string>
#include "UObject/ConstructorHelpers.h"
#include "Math/Vector2D.h"
#include "Layout/Geometry.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"

#define LOCTEXT_NAMESPACE "TestSlate"

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

const FMargin CalculateLargeTilePosition(FVector2D tileCoords, FVector2D adjustedViewportSize)
{
	float viewportX = adjustedViewportSize.X;
	float viewportY = adjustedViewportSize.Y;
	float fOne = (viewportX - viewportY) / 2;
	float leftPad = fOne + (viewportY / 15) * tileCoords.X;
	float topPad = (viewportY / 15) * tileCoords.Y;
	float rightPad = fOne + (viewportY / 15) * (15 - (tileCoords.X + 3));
	float bottomPad = viewportY - (viewportY / 15) * (tileCoords.Y + 3);

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

//you could change the size of the background tiles without changing the size of the track tiles because they are being calculated seperately. just moving down to 12 x 12 would have a big impact on performance
void STestWidgetThree::Construct(const FArguments& InArgs)//at some point I will need to write a destructor considering all the 'new' keywords used here
{
	SetCanTick(true);
	bCanSupportFocus = true;

	OwningHUD = InArgs._OwningHUD;
	landscapeArr = InArgs._landscapeArr;
	trackArr = InArgs._trackArr;
	pondSpecifierArr = InArgs._pondSpecifierArr;
	pondPositionArr = InArgs._pondPositionArr;
	tileIsIntersection = InArgs._tileIsIntersection;
	playerOnePlayerController = InArgs._playerOnePlayerController;
	startingPos = InArgs._startingPos;
	startingDir = InArgs._startingDir;
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
	railTurningFour_SMUI = InArgs._railTurningFour_SMUI;
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

	emptyImg_SB = new FSlateBrush();
	emptyImg_SB->SetResourceObject(emptyImg_SMUI);

	landscapeStuff = { grass_SB_1, holeFromDown_SB, holeFromLeft_SB, holeFromRight_SB, holeFromUp_SB, grass_SB_2, grass_SB_3, pondHorizontal_SB, pondVerticleFlowingLeft_SB, pondVerticleFlowingRight_SB, waterfall_SB, riverFlowingDown_SB_1, riverFlowingDown_SB_2, riverFlowingDown_SB_3, riverFlowingLeft_SB_1, riverFlowingLeft_SB_2, riverFlowingLeft_SB_3, riverFlowingRight_SB_1, riverFlowingRight_SB_2, riverFlowingRight_SB_3, tree_SB_1, tree_SB_2, tree_SB_3, tree_SB_4, tree_SB_5, riverTurning_SB_1, riverTurning_SB_2, riverTurning_SB_3, riverTurning_SB_4, emptyImg_SB };
	trackStuff = { emptyImg_SB, verticleRail_SB, horizontalRail_SB, railTurningOne_SB, railTurningTwo_SB, railTurningThree_SB, railTurningFour_SB, buttonFromDownTurningRightZero_SB, buttonFromDownTurningLeftZero_SB, buttonFromLeftTurningRightZero_SB, buttonFromLeftTurningLeftZero_SB, buttonFromRightTurningRightZero_SB, buttonFromRightTurningLeftZero_SB, buttonFromUpTurningRightZero_SB, buttonFromUpTurningLeftZero_SB};//the first element for this arr is an empty image ALSO I should change this to an array of fully assembled widget structures with the intersection having their logic built in

	flags = { flag_SB_1, flag_SB_2, flag_SB_3, flag_SB_4, flag_SB_5, flag_SB_6, flag_SB_7, flag_SB_8, flag_SB_9, flag_SB_10, flag_SB_11, flag_SB_12, flag_SB_13, flag_SB_14, flag_SB_15, flag_SB_16, };
	marbles = { marble_SB_1, marble_SB_2, marble_SB_3, marble_SB_4, marble_SB_5, marble_SB_6, marble_SB_7, marble_SB_8, marble_SB_9, marble_SB_10, marble_SB_11, marble_SB_12, marble_SB_13, marble_SB_14, marble_SB_15, marble_SB_16, };

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

	//now that the track is built you can control the marbles movement merely by left turns, right turns or straight track. from the marbles starting direction a left turn will incriment the marble direction counter clockwise and a right turn clockwise 

	marbleOneBox = SNew(SBox)
		.Padding(CalculateTilePosition(FVector2D(0, 0), adjustedViewportSize))
		[
			SNew(SImage)
			.Image(marble_SB_1)
		];

	marbleOverlay = SNew(SOverlay);
	marbleOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			marbleOneBox.ToSharedRef()
		];

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

	trackOverlay = SNew(SOverlay);
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
			case 1 :
				intersectionImages.Add(SNew(SImage));
				intersectionImages[0]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						SNew(SButton)
						.ContentPadding(FMargin())
						.ButtonStyle(masterButtonStyle)
						.OnPressed(this, &STestWidgetThree::OnIntersectionPressedOne)
						.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedOne)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
						.ButtonColorAndOpacity(FLinearColor::Transparent)
						.IsEnabled(true)///weerrks so now can I nest the rail stuff in buttons?
						[
							intersectionImages[0].ToSharedRef()
						]
					];

				intersectionsKeys.Add(trackArr[a]);

				break;
			case 2 :
				intersectionImages.Add(SNew(SImage));
				intersectionImages[1]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						SNew(SButton)
							.ContentPadding(FMargin())
							.ButtonStyle(masterButtonStyle)
							.OnPressed(this, &STestWidgetThree::OnIntersectionPressedTwo)
							.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedTwo)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
							.ButtonColorAndOpacity(FLinearColor::Transparent)
							.IsEnabled(true)///weerrks so now can I nest the rail stuff in buttons?
							[
								intersectionImages[1].ToSharedRef()
							]
					];

				intersectionsKeys.Add(trackArr[a]);

				break;
			case 3 :
				intersectionImages.Add(SNew(SImage));
				intersectionImages[2]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						SNew(SButton)
							.ContentPadding(FMargin())
							.ButtonStyle(masterButtonStyle)
							.OnPressed(this, &STestWidgetThree::OnIntersectionPressedThree)
							.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedThree)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
							.ButtonColorAndOpacity(FLinearColor::Transparent)
							.IsEnabled(true)///weerrks so now can I nest the rail stuff in buttons?
							[
								intersectionImages[2].ToSharedRef()
							]
					];

				intersectionsKeys.Add(trackArr[a]);

				break;
			case 4 :
				intersectionImages.Add(SNew(SImage));
				intersectionImages[3]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						SNew(SButton)
							.ContentPadding(FMargin())
							.ButtonStyle(masterButtonStyle)
							.OnPressed(this, &STestWidgetThree::OnIntersectionPressedFour)
							.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedFour)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
							.ButtonColorAndOpacity(FLinearColor::Transparent)
							.IsEnabled(true)///weerrks so now can I nest the rail stuff in buttons?
							[
								intersectionImages[3].ToSharedRef()
							]
					];

				intersectionsKeys.Add(trackArr[a]);

				break;
			case 5 :
				intersectionImages.Add(SNew(SImage));
				intersectionImages[4]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						SNew(SButton)
							.ContentPadding(FMargin())
							.ButtonStyle(masterButtonStyle)
							.OnPressed(this, &STestWidgetThree::OnIntersectionPressedFive)
							.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedFive)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
							.ButtonColorAndOpacity(FLinearColor::Transparent)
							.IsEnabled(true)///weerrks so now can I nest the rail stuff in buttons?
							[
								intersectionImages[4].ToSharedRef()
							]
					];

				intersectionsKeys.Add(trackArr[a]);

				break;
			case 6 :
				intersectionImages.Add(SNew(SImage));
				intersectionImages[5]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						SNew(SButton)
							.ContentPadding(FMargin())
							.ButtonStyle(masterButtonStyle)
							.OnPressed(this, &STestWidgetThree::OnIntersectionPressedSix)
							.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedSix)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
							.ButtonColorAndOpacity(FLinearColor::Transparent)
							.IsEnabled(true)///weerrks so now can I nest the rail stuff in buttons?
							[
								intersectionImages[5].ToSharedRef()
							]
					];

				intersectionsKeys.Add(trackArr[a]);

				break;
			case 7 :
				intersectionImages.Add(SNew(SImage));
				intersectionImages[6]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						SNew(SButton)
							.ContentPadding(FMargin())
							.ButtonStyle(masterButtonStyle)
							.OnPressed(this, &STestWidgetThree::OnIntersectionPressedSeven)
							.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedSeven)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
							.ButtonColorAndOpacity(FLinearColor::Transparent)
							.IsEnabled(true)///weerrks so now can I nest the rail stuff in buttons?
							[
								intersectionImages[6].ToSharedRef()
							]
					];

				intersectionsKeys.Add(trackArr[a]);

				break;
			case 8 :
				intersectionImages.Add(SNew(SImage));
				intersectionImages[7]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						SNew(SButton)
							.ContentPadding(FMargin())
							.ButtonStyle(masterButtonStyle)
							.OnPressed(this, &STestWidgetThree::OnIntersectionPressedEight)
							.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedEight)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
							.ButtonColorAndOpacity(FLinearColor::Transparent)
							.IsEnabled(true)///weerrks so now can I nest the rail stuff in buttons?
							[
								intersectionImages[7].ToSharedRef()
							]
					];

				intersectionsKeys.Add(trackArr[a]);

				break;
			case 9 :
				intersectionImages.Add(SNew(SImage));
				intersectionImages[8]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						SNew(SButton)
							.ContentPadding(FMargin())
							.ButtonStyle(masterButtonStyle)
							.OnPressed(this, &STestWidgetThree::OnIntersectionPressedNine)
							.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedNine)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
							.ButtonColorAndOpacity(FLinearColor::Transparent)
							.IsEnabled(true)///weerrks so now can I nest the rail stuff in buttons?
							[
								intersectionImages[8].ToSharedRef()
							]
					];

				intersectionsKeys.Add(trackArr[a]);

				break;
			case 10 :
				intersectionImages.Add(SNew(SImage));
				intersectionImages[9]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						SNew(SButton)
							.ContentPadding(FMargin())
							.ButtonStyle(masterButtonStyle)
							.OnPressed(this, &STestWidgetThree::OnIntersectionPressedTen)
							.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedTen)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
							.ButtonColorAndOpacity(FLinearColor::Transparent)
							.IsEnabled(true)///weerrks so now can I nest the rail stuff in buttons?
							[
								intersectionImages[9].ToSharedRef()
							]
					];

				intersectionsKeys.Add(trackArr[a]);

				break;
			case 11 :
				intersectionImages.Add(SNew(SImage));
				intersectionImages[10]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						SNew(SButton)
							.ContentPadding(FMargin())
							.ButtonStyle(masterButtonStyle)
							.OnPressed(this, &STestWidgetThree::OnIntersectionPressedEleven)
							.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedEleven)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
							.ButtonColorAndOpacity(FLinearColor::Transparent)
							.IsEnabled(true)///weerrks so now can I nest the rail stuff in buttons?
							[
								intersectionImages[10].ToSharedRef()
							]
					];

				intersectionsKeys.Add(trackArr[a]);

				break;
			case 12 :
				intersectionImages.Add(SNew(SImage));
				intersectionImages[11]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						SNew(SButton)
							.ContentPadding(FMargin())
							.ButtonStyle(masterButtonStyle)
							.OnPressed(this, &STestWidgetThree::OnIntersectionPressedTwelve)
							.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedTwelve)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
							.ButtonColorAndOpacity(FLinearColor::Transparent)
							.IsEnabled(true)///weerrks so now can I nest the rail stuff in buttons?
							[
								intersectionImages[11].ToSharedRef()
							]
					];

				intersectionsKeys.Add(trackArr[a]);

				break;
			case 13 :
				intersectionImages.Add(SNew(SImage));
				intersectionImages[12]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						SNew(SButton)
							.ContentPadding(FMargin())
							.ButtonStyle(masterButtonStyle)
							.OnPressed(this, &STestWidgetThree::OnIntersectionPressedThirteen)
							.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedThirteen)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
							.ButtonColorAndOpacity(FLinearColor::Transparent)
							.IsEnabled(true)///weerrks so now can I nest the rail stuff in buttons?
							[
								intersectionImages[12].ToSharedRef()
							]
					];

				intersectionsKeys.Add(trackArr[a]);

				break;
			case 14 :
				intersectionImages.Add(SNew(SImage));
				intersectionImages[13]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						SNew(SButton)
							.ContentPadding(FMargin())
							.ButtonStyle(masterButtonStyle)
							.OnPressed(this, &STestWidgetThree::OnIntersectionPressedFourteen)
							.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedFourteen)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
							.ButtonColorAndOpacity(FLinearColor::Transparent)
							.IsEnabled(true)///weerrks so now can I nest the rail stuff in buttons?
							[
								intersectionImages[13].ToSharedRef()
							]
					];

				intersectionsKeys.Add(trackArr[a]);

				break;
			case 15 :
				intersectionImages.Add(SNew(SImage));
				intersectionImages[14]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						SNew(SButton)
							.ContentPadding(FMargin())
							.ButtonStyle(masterButtonStyle)
							.OnPressed(this, &STestWidgetThree::OnIntersectionPressedFifteen)
							.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedFifteen)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
							.ButtonColorAndOpacity(FLinearColor::Transparent)
							.IsEnabled(true)///weerrks so now can I nest the rail stuff in buttons?
							[
								intersectionImages[14].ToSharedRef()
							]
					];

				intersectionsKeys.Add(trackArr[a]);

				break;
			case 16 :
				intersectionImages.Add(SNew(SImage));
				intersectionImages[15]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						SNew(SButton)
							.ContentPadding(FMargin())
							.ButtonStyle(masterButtonStyle)
							.OnPressed(this, &STestWidgetThree::OnIntersectionPressedSixteen)
							.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedSixteen)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
							.ButtonColorAndOpacity(FLinearColor::Transparent)
							.IsEnabled(true)///weerrks so now can I nest the rail stuff in buttons?
							[
								intersectionImages[15].ToSharedRef()
							]
					];

				intersectionsKeys.Add(trackArr[a]);

				break;
			case 17 :
				intersectionImages.Add(SNew(SImage));
				intersectionImages[16]->SetImage(intersections[trackArr[a]][0]);
				intersectionCycle.Add(0);

				trackOverlay->AddSlot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
					[
						SNew(SButton)
							.ContentPadding(FMargin())
							.ButtonStyle(masterButtonStyle)
							.OnPressed(this, &STestWidgetThree::OnIntersectionPressedSeventeen)
							.OnReleased(this, &STestWidgetThree::OnIntersectionReleasedSeventeen)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
							.ButtonColorAndOpacity(FLinearColor::Transparent)
							.IsEnabled(true)///weerrks so now can I nest the rail stuff in buttons?
							[
								intersectionImages[16].ToSharedRef()
							]
					];

				intersectionsKeys.Add(trackArr[a]);

				break;
			default:
				break;
			}

			currentIntersection += 1;
		}
	}

	b = 0;
	deleteMe = 0;

	testFMargin = FMargin(485.0f* 1.85185f, 537.6f* 1.85185f, 1022.6f* 1.85185f, 0.0f);

	ChildSlot //so it appears I cannot write code to systematically build only as much widget as necessary and will instead need to list out 225 landscape SImages and 225 track SImages and fill them as needed. but hold on, there is still some testing to be done, what if I store the initial SOverlay so I can reference it directly. ( this will mean potentially creating a new SOverlay sub class? no nvm I will just need to check through the childSlot logic to see if theres a way to display an already existing SOverlay, or to assign the SNew(SOverlay to an identity
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.ColorAndOpacity(FColor::Orange)
			]

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
			//.Padding(CalculateTilePosition(FVector2D(14, 14), adjustedViewportSize))
			[
				marbleOverlay.ToSharedRef()
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				trackOverlay.ToSharedRef()
			]

		];
}

FReply STestWidgetThree::OnClicked() const
{
	UGameUserSettings* myGameSettings = GEngine->GetGameUserSettings();

	FGeometry testGeometry = GetPaintSpaceGeometry();
	float y = testGeometry.GetAbsoluteSize().Component(1);

	GEngine->AddOnScreenDebugMessage(-1, 200.0, FColor::Blue, FString::SanitizeFloat(y));

	return FReply::Handled();
}

FReply STestWidgetThree::OnQuitClicked() const
{
	if (OwningHUD.IsValid())
	{
		if (APlayerController* PC = OwningHUD->PlayerOwner)
		{
			PC->ConsoleCommand("Quit");
		}
	}

	return FReply::Handled();
}

void STestWidgetThree::OnIntersectionPressedOne()
{
	intersectionCycle[0] = (intersectionCycle[0] + 1) % 4;
	intersectionImages[0]->SetImage(intersections[intersectionsKeys[0]][intersectionCycle[0]]);
}
void STestWidgetThree::OnIntersectionReleasedOne()
{
	intersectionCycle[0] = (intersectionCycle[0] + 1) % 4;
	intersectionImages[0]->SetImage(intersections[intersectionsKeys[0]][intersectionCycle[0]]);
}

void STestWidgetThree::OnIntersectionPressedTwo()
{
	intersectionCycle[1] = (intersectionCycle[1] + 1) % 4;
	intersectionImages[1]->SetImage(intersections[intersectionsKeys[1]][intersectionCycle[1]]);
}
void STestWidgetThree::OnIntersectionReleasedTwo()
{
	intersectionCycle[1] = (intersectionCycle[1] + 1) % 4;
	intersectionImages[1]->SetImage(intersections[intersectionsKeys[1]][intersectionCycle[1]]);
}

void STestWidgetThree::OnIntersectionPressedThree()
{
	intersectionCycle[2] = (intersectionCycle[2] + 1) % 4;
	intersectionImages[2]->SetImage(intersections[intersectionsKeys[2]][intersectionCycle[2]]);
}
void STestWidgetThree::OnIntersectionReleasedThree()
{
	intersectionCycle[2] = (intersectionCycle[2] + 1) % 4;
	intersectionImages[2]->SetImage(intersections[intersectionsKeys[2]][intersectionCycle[2]]);
}

void STestWidgetThree::OnIntersectionPressedFour()
{
	intersectionCycle[3] = (intersectionCycle[3] + 1) % 4;
	intersectionImages[3]->SetImage(intersections[intersectionsKeys[3]][intersectionCycle[3]]);
}
void STestWidgetThree::OnIntersectionReleasedFour()
{
	intersectionCycle[3] = (intersectionCycle[3] + 1) % 4;
	intersectionImages[3]->SetImage(intersections[intersectionsKeys[3]][intersectionCycle[3]]);
}

void STestWidgetThree::OnIntersectionPressedFive()
{
	intersectionCycle[4] = (intersectionCycle[4] + 1) % 4;
	intersectionImages[4]->SetImage(intersections[intersectionsKeys[4]][intersectionCycle[4]]);
}
void STestWidgetThree::OnIntersectionReleasedFive()
{
	intersectionCycle[4] = (intersectionCycle[4] + 1) % 4;
	intersectionImages[4]->SetImage(intersections[intersectionsKeys[4]][intersectionCycle[4]]);
}

void STestWidgetThree::OnIntersectionPressedSix()
{
	intersectionCycle[5] = (intersectionCycle[5] + 1) % 4;
	intersectionImages[5]->SetImage(intersections[intersectionsKeys[5]][intersectionCycle[5]]);
}
void STestWidgetThree::OnIntersectionReleasedSix()
{
	intersectionCycle[5] = (intersectionCycle[5] + 1) % 4;
	intersectionImages[5]->SetImage(intersections[intersectionsKeys[5]][intersectionCycle[5]]);
}

void STestWidgetThree::OnIntersectionPressedSeven()
{
	intersectionCycle[6] = (intersectionCycle[6] + 1) % 4;
	intersectionImages[6]->SetImage(intersections[intersectionsKeys[6]][intersectionCycle[6]]);
}
void STestWidgetThree::OnIntersectionReleasedSeven()
{
	intersectionCycle[6] = (intersectionCycle[6] + 1) % 4;
	intersectionImages[6]->SetImage(intersections[intersectionsKeys[6]][intersectionCycle[6]]);
}

void STestWidgetThree::OnIntersectionPressedEight()
{
	intersectionCycle[7] = (intersectionCycle[7] + 1) % 4;
	intersectionImages[7]->SetImage(intersections[intersectionsKeys[7]][intersectionCycle[7]]);
}
void STestWidgetThree::OnIntersectionReleasedEight()
{
	intersectionCycle[7] = (intersectionCycle[7] + 1) % 4;
	intersectionImages[7]->SetImage(intersections[intersectionsKeys[7]][intersectionCycle[7]]);
}

void STestWidgetThree::OnIntersectionPressedNine()
{
	intersectionCycle[8] = (intersectionCycle[8] + 1) % 4;
	intersectionImages[8]->SetImage(intersections[intersectionsKeys[8]][intersectionCycle[8]]);
}
void STestWidgetThree::OnIntersectionReleasedNine()
{
	intersectionCycle[8] = (intersectionCycle[8] + 1) % 4;
	intersectionImages[8]->SetImage(intersections[intersectionsKeys[8]][intersectionCycle[8]]);
}

void STestWidgetThree::OnIntersectionPressedTen()
{
	intersectionCycle[9] = (intersectionCycle[9] + 1) % 4;
	intersectionImages[9]->SetImage(intersections[intersectionsKeys[9]][intersectionCycle[9]]);
}
void STestWidgetThree::OnIntersectionReleasedTen()
{
	intersectionCycle[9] = (intersectionCycle[9] + 1) % 4;
	intersectionImages[9]->SetImage(intersections[intersectionsKeys[9]][intersectionCycle[9]]);
}

void STestWidgetThree::OnIntersectionPressedEleven()
{
	intersectionCycle[10] = (intersectionCycle[10] + 1) % 4;
	intersectionImages[10]->SetImage(intersections[intersectionsKeys[10]][intersectionCycle[10]]);
}
void STestWidgetThree::OnIntersectionReleasedEleven()
{
	intersectionCycle[10] = (intersectionCycle[10] + 1) % 4;
	intersectionImages[10]->SetImage(intersections[intersectionsKeys[10]][intersectionCycle[10]]);
}

void STestWidgetThree::OnIntersectionPressedTwelve()
{
	intersectionCycle[11] = (intersectionCycle[11] + 1) % 4;
	intersectionImages[11]->SetImage(intersections[intersectionsKeys[11]][intersectionCycle[11]]);
}
void STestWidgetThree::OnIntersectionReleasedTwelve()
{
	intersectionCycle[11] = (intersectionCycle[11] + 1) % 4;
	intersectionImages[11]->SetImage(intersections[intersectionsKeys[11]][intersectionCycle[11]]);
}

void STestWidgetThree::OnIntersectionPressedThirteen()
{
	intersectionCycle[12] = (intersectionCycle[12] + 1) % 4;
	intersectionImages[12]->SetImage(intersections[intersectionsKeys[12]][intersectionCycle[12]]);
}
void STestWidgetThree::OnIntersectionReleasedThirteen()
{
	intersectionCycle[12] = (intersectionCycle[12] + 1) % 4;
	intersectionImages[12]->SetImage(intersections[intersectionsKeys[12]][intersectionCycle[12]]);
}

void STestWidgetThree::OnIntersectionPressedFourteen()
{
	intersectionCycle[13] = (intersectionCycle[13] + 1) % 4;
	intersectionImages[13]->SetImage(intersections[intersectionsKeys[13]][intersectionCycle[13]]);
}
void STestWidgetThree::OnIntersectionReleasedFourteen()
{
	intersectionCycle[13] = (intersectionCycle[13] + 1) % 4;
	intersectionImages[13]->SetImage(intersections[intersectionsKeys[13]][intersectionCycle[13]]);
}

void STestWidgetThree::OnIntersectionPressedFifteen()
{
	intersectionCycle[14] = (intersectionCycle[14] + 1) % 4;
	intersectionImages[14]->SetImage(intersections[intersectionsKeys[14]][intersectionCycle[14]]);
}
void STestWidgetThree::OnIntersectionReleasedFifteen()
{
	intersectionCycle[14] = (intersectionCycle[14] + 1) % 4;
	intersectionImages[14]->SetImage(intersections[intersectionsKeys[14]][intersectionCycle[14]]);
}

void STestWidgetThree::OnIntersectionPressedSixteen()
{
	intersectionCycle[15] = (intersectionCycle[15] + 1) % 4;
	intersectionImages[15]->SetImage(intersections[intersectionsKeys[15]][intersectionCycle[15]]);
}
void STestWidgetThree::OnIntersectionReleasedSixteen()
{
	intersectionCycle[15] = (intersectionCycle[15] + 1) % 4;
	intersectionImages[15]->SetImage(intersections[intersectionsKeys[15]][intersectionCycle[15]]);
}

void STestWidgetThree::OnIntersectionPressedSeventeen()
{
	intersectionCycle[16] = (intersectionCycle[16] + 1) % 4;
	intersectionImages[16]->SetImage(intersections[intersectionsKeys[16]][intersectionCycle[16]]);
}
void STestWidgetThree::OnIntersectionReleasedSeventeen()
{
	intersectionCycle[16] = (intersectionCycle[16] + 1) % 4;
	intersectionImages[16]->SetImage(intersections[intersectionsKeys[16]][intersectionCycle[16]]);
}

FReply STestWidgetThree::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Q)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "q");
	}

	if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		OwningHUD->HouseKeeping();
		OwningHUD->ResetRegenLevel();

		UKismetSystemLibrary::QuitGame(playerOnePlayerController, playerOnePlayerController, EQuitPreference::Quit, false);
	}

	return FReply::Handled();
}

void STestWidgetThree::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	if (deleteMe > 29)
	{
		deleteMe = 0;

		marbleOneBox->SetPadding(CalculateTilePosition(FVector2D(b, 0), adjustedViewportSize));
		b++;
	}
	else
	{
		deleteMe++;
	}
}

#undef LOCTEXT_NAMESPACE
