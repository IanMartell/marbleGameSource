// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "mediaPlayer.h"
#include "MediaSource.h"
#include "BaseMediaSource.h"
#include "ImgMediaSource.h"
#include "Kismet/GameplayStatics.h"
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

	UMaterial* grass_VMUI_1;// all uobject variables must be uproperty otherwise the garbage collecter will collect them
	UMediaPlayer* grass_MP_1;//change the umaerial to material interface
	UMaterial* grass_VMUI_2;
	UMediaPlayer* grass_MP_2;
	UMaterial* grass_VMUI_3;
	UMediaPlayer* grass_MP_3;
	UMaterial* pondHorizontal_VMUI;
	UMediaPlayer* pondHorizontal_MP;
	UMaterial* pondVerticleFlowingLeft_VMUI;
	UMediaPlayer* pondVerticleFlowingLeft_MP;
	UMaterial* pondVerticleFlowingRight_VMUI;
	UMediaPlayer* pondVerticleFlowingRight_MP;
	UMaterial* riverFlowingDown_VMUI_1;
	UMediaPlayer* riverFlowingDown_MP_1;
	UMaterial* riverFlowingDown_VMUI_2;
	UMediaPlayer* riverFlowingDown_MP_2;
	UMaterial* riverFlowingDown_VMUI_3;
	UMediaPlayer* riverFlowingDown_MP_3;
	UMaterial* riverFlowingLeft_VMUI_1;
	UMediaPlayer* riverFlowingLeft_MP_1;
	UMaterial* riverFlowingLeft_VMUI_2;
	UMediaPlayer* riverFlowingLeft_MP_2;
	UMaterial* riverFlowingLeft_VMUI_3;
	UMediaPlayer* riverFlowingLeft_MP_3;
	UMaterial* riverFlowingRight_VMUI_1;
	UMediaPlayer* riverFlowingRight_MP_1;
	UMaterial* riverFlowingRight_VMUI_2;
	UMediaPlayer* riverFlowingRight_MP_2;
	UMaterial* riverFlowingRight_VMUI_3;
	UMediaPlayer* riverFlowingRight_MP_3;
	UMaterial* tree_VMUI_1;
	UMediaPlayer* tree_MP_1;
	UMaterial* tree_VMUI_2;
	UMediaPlayer* tree_MP_2;
	UMaterial* tree_VMUI_3;
	UMediaPlayer* tree_MP_3;
	UMaterial* tree_VMUI_4;
	UMediaPlayer* tree_MP_4;
	UMaterial* tree_VMUI_5;
	UMediaPlayer* tree_MP_5;
	UMaterial* waterfall_VMUI;
	UMediaPlayer* waterfall_MP;
	UMaterial* riverTurning_VMUI_1;
	UMediaPlayer* riverTurning_MP_1;
	UMaterial* riverTurning_VMUI_2;
	UMediaPlayer* riverTurning_MP_2;
	UMaterial* riverTurning_VMUI_3;
	UMediaPlayer* riverTurning_MP_3;
	UMaterial* riverTurning_VMUI_4;
	UMediaPlayer* riverTurning_MP_4;

	UMaterial* holeFromDown_VMUI;
	UMediaPlayer* holeFromDown_MP;
	UMaterial* holeFromLeft_VMUI;
	UMediaPlayer* holeFromLeft_MP;
	UMaterial* holeFromRight_VMUI;
	UMediaPlayer* holeFromRight_MP;
	UMaterial* holeFromUp_VMUI;
	UMediaPlayer* holeFromUp_MP;

	UMaterial* buttonFromDownTurningRightZero_SMUI;
	UMaterial* buttonFromDownTurningLeftZero_SMUI;
	UMaterial* buttonFromLeftTurningRightZero_SMUI;
	UMaterial* buttonFromLeftTurningLeftZero_SMUI;
	UMaterial* buttonFromRightTurningRightZero_SMUI;
	UMaterial* buttonFromRightTurningLeftZero_SMUI;
	UMaterial* buttonFromUpTurningRightZero_SMUI;
	UMaterial* buttonFromUpTurningLeftZero_SMUI;

	UMaterial* verticleRail_SMUI;
	UMaterial* horizontalRail_SMUI;

	UMaterial* railTurningOne_SMUI;
	UMaterial* railTurningTwo_SMUI;
	UMaterial* railTurningThree_SMUI;
	UMaterial* railTurningFour_SMUI;

	UMaterial* marble_SMUI_1;
	UMaterial* marble_SMUI_2;
	UMaterial* marble_SMUI_3;
	UMaterial* marble_SMUI_4;
	UMaterial* marble_SMUI_5;
	UMaterial* marble_SMUI_6;
	UMaterial* marble_SMUI_7;

	UMaterial* placeholderTrash;
	UMaterial* emptyImg_SMUI;
	//data structures of content browser assets
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

	TArray<TArray<UMaterial*> > turningTrack =
	{ //Ive only got 4 turning track sprites but I should set this up like I set up the intersectionButtons
		// 0 for right, 1 for left, 2 for intersection, 3 for straight track (two for intersection?! really? how are you gonna do that)
		{//index 0
			{ placeholderTrash }
		},
		{//index 1 (from up?)
			{ railTurningFour_SMUI, railTurningOne_SMUI, placeholderTrash, verticleRail_SMUI }
		},
		{//index 2 (from left?)
			{ railTurningThree_SMUI, railTurningFour_SMUI, placeholderTrash, horizontalRail_SMUI }
		},
		{//index 3 (from down?)
			{ railTurningTwo_SMUI, railTurningThree_SMUI, placeholderTrash, verticleRail_SMUI }
		},
		{//index 4 (from right?)
			{ railTurningOne_SMUI, railTurningTwo_SMUI, placeholderTrash, horizontalRail_SMUI }
		}
	};

protected:
	//protected init stuff
	TSharedPtr<class SLoadingScreenOne> loadingSlateWidget;
	TSharedPtr<class SWidget> slateWidgetContainerOne;

	TSharedPtr<class STestWidgetThree> gameSlateWidget;
	TSharedPtr<class SWidget> slateWidgetContainerTwo; // we use this container to remove and add the menu to the screen

	virtual void BeginPlay() override;

public:
	APlayerController* playerOnePlayerController;

	//level randomizer algorithm stuff
	TArray<FVector2D> arrOfViableHoleCoordinates;
	TArray<FVector2D> arrOfViableHoleCoordinatesBase = { FVector2D(12, 2), FVector2D(12, 1), FVector2D(11, 2), FVector2D(11, 1), FVector2D(10, 2), FVector2D(10, 1), FVector2D(9, 2), FVector2D(9, 1), FVector2D(8, 2), FVector2D(8, 1), FVector2D(7, 2), FVector2D(7, 1), FVector2D(6, 2), FVector2D(6, 1), FVector2D(5, 2), FVector2D(5, 1), FVector2D(4, 2), FVector2D(4, 1) };
	TArray<FVector2D> holePositions;

	int negativeOneZeroOrOne;

	TArray<int> test;
	TArray<int> listOfHolePositionGroupings;

	int holeCoordinateOrientation;
	int numberOfHoles = 8;

	TArray<TArray<int>> nestedTArr;

	int extentOfAdjustment = 2 - FMath::Clamp(numberOfHoles - 8, 0, 1);

	TArray<int> regenerateLevel;

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

	TArray<int> landscapeArr = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	TArray<int> trackArr = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	TArray<bool> tileIsIntersection = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

	TArray<int> tileIsTrack = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	TArray<FVector2D> pondPositionArr;
	TArray<int> pondSpecifierArr;

	void GenerateLevel();

	void GenerateHolePositions();

	void GenerateTrackShape();

	void BuildLevel();

	void HouseKeeping();

	void ResetRegenLevel();

};