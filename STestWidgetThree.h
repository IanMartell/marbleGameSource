// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "TestHud.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "Widgets/SPanel.h"
#include "Delegates/Delegate.h"
#include "GameFramework/GameUserSettings.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/SOverlay.h"
#include "Widgets/Layout/SBackgroundBlur.h"
#include "Materials/MaterialInterface.h"
#include "Framework/Application/SlateApplication.h"
#include "Engine/Classes/Materials/Material.h"

/**
 *
 */
class STestWidgetThree : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(STestWidgetThree) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class ATestHud>, OwningHUD)

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

	FVector2D PrepTurnMarble(int currentMarble, FVector2d marblePosition, int dirOfMarble, bool isIntersection, int trackArrValue);
	FVector2D TurnMarble(int currentMarble, FVector2D marblePosition);
	FMargin ShrinkMarble(FMargin inPadding, double factorOfShrinkage);

	// constructor variables

	TWeakObjectPtr<class ATestHud> OwningHUD;

	TArray<int> landscapeArr;
	TArray<int> trackArr;
	TArray<int> pondSpecifierArr;
	TArray<FVector2D> pondPositionArr;
	TArray<bool> tileIsIntersection;
	TArray<FVector2D> holePositions;

	APlayerController* playerOnePlayerController;

	UMaterial* grass_VMUI_1;
	UMaterial* grass_VMUI_2;
	UMaterial* grass_VMUI_3;
	UMaterial* pondHorizontal_VMUI;
	UMaterial* pondVerticleFlowingLeft_VMUI;
	UMaterial* pondVerticleFlowingRight_VMUI;
	UMaterial* riverFlowingDown_VMUI_1;
	UMaterial* riverFlowingDown_VMUI_2;
	UMaterial* riverFlowingDown_VMUI_3;
	UMaterial* riverFlowingLeft_VMUI_1;
	UMaterial* riverFlowingLeft_VMUI_2;
	UMaterial* riverFlowingLeft_VMUI_3;
	UMaterial* riverFlowingRight_VMUI_1;
	UMaterial* riverFlowingRight_VMUI_2;
	UMaterial* riverFlowingRight_VMUI_3;
	UMaterial* tree_VMUI_1;
	UMaterial* tree_VMUI_2;
	UMaterial* tree_VMUI_3;
	UMaterial* tree_VMUI_4;
	UMaterial* tree_VMUI_5;
	UMaterial* waterfall_VMUI;
	UMaterial* riverTurning_VMUI_1;
	UMaterial* riverTurning_VMUI_2;
	UMaterial* riverTurning_VMUI_3;
	UMaterial* riverTurning_VMUI_4;

	UMaterial* mountain_VMUI_1;

	UMaterial* holeFromDown_VMUI;
	UMaterial* holeFromLeft_VMUI;
	UMaterial* holeFromRight_VMUI;
	UMaterial* holeFromUp_VMUI;

	UMaterial* flag_VMUI_1;
	UMaterial* flag_VMUI_2;
	UMaterial* flag_VMUI_3;
	UMaterial* flag_VMUI_4;
	UMaterial* flag_VMUI_5;
	UMaterial* flag_VMUI_6;
	UMaterial* flag_VMUI_7;
	UMaterial* flag_VMUI_8;
	UMaterial* flag_VMUI_9;
	UMaterial* flag_VMUI_10;
	UMaterial* flag_VMUI_11;
	UMaterial* flag_VMUI_12;
	UMaterial* flag_VMUI_13;
	UMaterial* flag_VMUI_14;
	UMaterial* flag_VMUI_15;
	UMaterial* flag_VMUI_16;

	UMaterial* buttonFromDownTurningRightZero_SMUI;
	UMaterial* buttonFromDownTurningRightOne_SMUI;
	UMaterial* buttonFromDownTurningRightTwo_SMUI;
	UMaterial* buttonFromDownTurningRightThree_SMUI;
	UMaterial* buttonFromDownTurningLeftZero_SMUI;
	UMaterial* buttonFromDownTurningLeftOne_SMUI;
	UMaterial* buttonFromDownTurningLeftTwo_SMUI;
	UMaterial* buttonFromDownTurningLeftThree_SMUI;
	UMaterial* buttonFromLeftTurningRightZero_SMUI;
	UMaterial* buttonFromLeftTurningRightOne_SMUI;
	UMaterial* buttonFromLeftTurningRightTwo_SMUI;
	UMaterial* buttonFromLeftTurningRightThree_SMUI;
	UMaterial* buttonFromLeftTurningLeftZero_SMUI;
	UMaterial* buttonFromLeftTurningLeftOne_SMUI;
	UMaterial* buttonFromLeftTurningLeftTwo_SMUI;
	UMaterial* buttonFromLeftTurningLeftThree_SMUI;
	UMaterial* buttonFromRightTurningRightZero_SMUI;
	UMaterial* buttonFromRightTurningRightOne_SMUI;
	UMaterial* buttonFromRightTurningRightTwo_SMUI;
	UMaterial* buttonFromRightTurningRightThree_SMUI;
	UMaterial* buttonFromRightTurningLeftZero_SMUI;
	UMaterial* buttonFromRightTurningLeftOne_SMUI;
	UMaterial* buttonFromRightTurningLeftTwo_SMUI;
	UMaterial* buttonFromRightTurningLeftThree_SMUI;
	UMaterial* buttonFromUpTurningRightZero_SMUI;
	UMaterial* buttonFromUpTurningRightOne_SMUI;
	UMaterial* buttonFromUpTurningRightTwo_SMUI;
	UMaterial* buttonFromUpTurningRightThree_SMUI;
	UMaterial* buttonFromUpTurningLeftZero_SMUI;
	UMaterial* buttonFromUpTurningLeftOne_SMUI;
	UMaterial* buttonFromUpTurningLeftTwo_SMUI;
	UMaterial* buttonFromUpTurningLeftThree_SMUI;
	
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
	UMaterial* marble_SMUI_8;
	UMaterial* marble_SMUI_9;
	UMaterial* marble_SMUI_10;
	UMaterial* marble_SMUI_11;
	UMaterial* marble_SMUI_12;
	UMaterial* marble_SMUI_13;
	UMaterial* marble_SMUI_14;
	UMaterial* marble_SMUI_15;
	UMaterial* marble_SMUI_16;

	UMaterial* gameFrameColor_SMUI;

	UMaterial* emptyImg_SMUI;

	//variables and data structures associated with constructor vars
	UMaterial* placeholderTrash;

	//slate brushes
	FSlateBrush* grass_SB_1;
	FSlateBrush* grass_SB_2;
	FSlateBrush* grass_SB_3;
	FSlateBrush* pondHorizontal_SB;
	FSlateBrush* pondVerticleFlowingLeft_SB;
	FSlateBrush* pondVerticleFlowingRight_SB;
	FSlateBrush* riverFlowingDown_SB_1;
	FSlateBrush* riverFlowingDown_SB_2;
	FSlateBrush* riverFlowingDown_SB_3;
	FSlateBrush* riverFlowingLeft_SB_1;
	FSlateBrush* riverFlowingLeft_SB_2;
	FSlateBrush* riverFlowingLeft_SB_3;
	FSlateBrush* riverFlowingRight_SB_1;
	FSlateBrush* riverFlowingRight_SB_2;
	FSlateBrush* riverFlowingRight_SB_3;
	FSlateBrush* tree_SB_1;
	FSlateBrush* tree_SB_2;
	FSlateBrush* tree_SB_3;
	FSlateBrush* tree_SB_4;
	FSlateBrush* tree_SB_5;
	FSlateBrush* waterfall_SB;
	FSlateBrush* riverTurning_SB_1;
	FSlateBrush* riverTurning_SB_2;
	FSlateBrush* riverTurning_SB_3;
	FSlateBrush* riverTurning_SB_4;

	FSlateBrush* mountain_SB_1;

	FSlateBrush* holeFromDown_SB;
	FSlateBrush* holeFromLeft_SB;
	FSlateBrush* holeFromRight_SB;
	FSlateBrush* holeFromUp_SB;

	FSlateBrush* flag_SB_1;
	FSlateBrush* flag_SB_2;
	FSlateBrush* flag_SB_3;
	FSlateBrush* flag_SB_4;
	FSlateBrush* flag_SB_5;
	FSlateBrush* flag_SB_6;
	FSlateBrush* flag_SB_7;
	FSlateBrush* flag_SB_8;
	FSlateBrush* flag_SB_9;
	FSlateBrush* flag_SB_10;
	FSlateBrush* flag_SB_11;
	FSlateBrush* flag_SB_12;
	FSlateBrush* flag_SB_13;
	FSlateBrush* flag_SB_14;
	FSlateBrush* flag_SB_15;
	FSlateBrush* flag_SB_16;

	FSlateBrush* buttonFromDownTurningRightZero_SB;
	FSlateBrush* buttonFromDownTurningRightOne_SB;
	FSlateBrush* buttonFromDownTurningRightTwo_SB;
	FSlateBrush* buttonFromDownTurningRightThree_SB;
	FSlateBrush* buttonFromDownTurningLeftZero_SB;
	FSlateBrush* buttonFromDownTurningLeftOne_SB;
	FSlateBrush* buttonFromDownTurningLeftTwo_SB;
	FSlateBrush* buttonFromDownTurningLeftThree_SB;
	FSlateBrush* buttonFromLeftTurningRightZero_SB;
	FSlateBrush* buttonFromLeftTurningRightOne_SB;
	FSlateBrush* buttonFromLeftTurningRightTwo_SB;
	FSlateBrush* buttonFromLeftTurningRightThree_SB;
	FSlateBrush* buttonFromLeftTurningLeftZero_SB;
	FSlateBrush* buttonFromLeftTurningLeftOne_SB;
	FSlateBrush* buttonFromLeftTurningLeftTwo_SB;
	FSlateBrush* buttonFromLeftTurningLeftThree_SB;
	FSlateBrush* buttonFromRightTurningRightZero_SB;
	FSlateBrush* buttonFromRightTurningRightOne_SB;
	FSlateBrush* buttonFromRightTurningRightTwo_SB;
	FSlateBrush* buttonFromRightTurningRightThree_SB;
	FSlateBrush* buttonFromRightTurningLeftZero_SB;
	FSlateBrush* buttonFromRightTurningLeftOne_SB;
	FSlateBrush* buttonFromRightTurningLeftTwo_SB;
	FSlateBrush* buttonFromRightTurningLeftThree_SB;
	FSlateBrush* buttonFromUpTurningRightZero_SB;
	FSlateBrush* buttonFromUpTurningRightOne_SB;
	FSlateBrush* buttonFromUpTurningRightTwo_SB;
	FSlateBrush* buttonFromUpTurningRightThree_SB;
	FSlateBrush* buttonFromUpTurningLeftZero_SB;
	FSlateBrush* buttonFromUpTurningLeftOne_SB;
	FSlateBrush* buttonFromUpTurningLeftTwo_SB;
	FSlateBrush* buttonFromUpTurningLeftThree_SB;

	FSlateBrush* verticleRail_SB;
	FSlateBrush* horizontalRail_SB;

	FSlateBrush* railTurningOne_SB;
	FSlateBrush* railTurningTwo_SB;
	FSlateBrush* railTurningThree_SB;
	FSlateBrush* railTurningFour_SB;

	FSlateBrush* marble_SB_1;
	FSlateBrush* marble_SB_2;
	FSlateBrush* marble_SB_3;
	FSlateBrush* marble_SB_4;
	FSlateBrush* marble_SB_5;
	FSlateBrush* marble_SB_6;
	FSlateBrush* marble_SB_7;
	FSlateBrush* marble_SB_8;
	FSlateBrush* marble_SB_9;
	FSlateBrush* marble_SB_10;
	FSlateBrush* marble_SB_11;
	FSlateBrush* marble_SB_12;
	FSlateBrush* marble_SB_13;
	FSlateBrush* marble_SB_14;
	FSlateBrush* marble_SB_15;
	FSlateBrush* marble_SB_16;

	FSlateBrush* gameFrameColor_SB;

	FSlateBrush* emptyImg_SB;

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

	TArray<FSlateBrush*> landscapeStuff;
	TArray<FSlateBrush*> trackStuff;
	TArray<FSlateBrush*> flags;
	TArray<FSlateBrush*> relevantFlags;
	TArray<FSlateBrush*> flagsRandomized;
	TArray<FSlateBrush*> marbles;
	TArray<FSlateBrush*> relevantMarbles;
	TArray<FSlateBrush*> marblesRandomized;

	FVector2D startingPos;
	int startingDir;

	// misc variables and data structures

	FString materialPath = FPaths::ProjectContentDir() / TEXT("/Game/Movies/videoMaterialsForUI/grass_VMUI_1");

	FVector2D viewportSize;
	FVector2D adjustedViewportSize;

	FMargin testFMargin;

	FButtonStyle* masterButtonStyle;

public: 
	TSharedPtr<class SWindow> windowOne;
	TArray<TSharedPtr<class SBox>> activeMarbles;
	TArray<TSharedPtr<class SBox>> marblesToBeDestroyed;
	TArray<FSlateBrush*> activeMarblesContent;
	TArray<FSlateBrush*> marblesThisGame;
	TArray<int> marblesThisGameProxy;
	TArray<int> marblesThisGameProxyTracker;
	int marbleProxyIndexToAdd;
	int marbleIndexToAdd;
	int marbleIndexToSpawn;
	int marbleIndexToDelete;
	TArray <int> marbleIndexesBeingAdded;
	TArray<double> marblesBeingDestroyedTime;
	TArray<FMargin> marblesShrinking;
	TSharedPtr<class STextBlock>  scoreText;
	FText currentScore;
	int playerScore = 0;
	int maximumPossibleScore = 0;
	FSlateFontInfo scoreTextStyle;
	TSharedPtr<class STextBlock>  timeText;
	FText currentTimeText;
	TSharedPtr< class SOverlay> marbleOverlay;
	TSharedPtr< class FOverlaySlot> marbleOneSlot;

	TSharedPtr<class SOverlay> largeTilesOverlay;
	TSharedPtr<class SOverlay> landscapeOverlay;
	TSharedPtr<class SOverlay> trackOverlay;
	TSharedPtr<class SOverlay> intersectionButtonsOverlay;
	TSharedPtr<class SOverlay> flagsOverlay;
	TSharedPtr<class SOverlay> frameColorOverlay;
	TSharedPtr<class SOverlay> pauseOverlay;

	TSharedPtr<class SBackgroundBlur> pauseBlur;

	TArray<TArray<FSlateBrush*> > intersections;
	TArray<int> intersectionsKeys;
	TArray<int> intersectionCycle;
	TArray< TSharedPtr<class SImage> > intersectionImages;
	TArray<FVector2D> intersectionPositions;

	float DPIScale;

	UPROPERTY() FVector2D screenPosition;
	UPROPERTY() FVector2D screenSize;

	float viewportX = 0.0f;
	float viewportY = 0.0f;
	int deleteMe;
	TArray<FVector2D> marblePositions;
	TArray<FVector2D> marblesToBeDestroyedPosition;
	TArray<FVector2D> marblePositionsCenters;//you need to change this from the center of the marbles "tile" to what appears to be the center of the marble
	TArray<FVector2D> previousTickMarblePositionsCenters;
	int currentIntersection = 1;
	TArray<int> startingMarbleMovementTracker = { { 0, 0 } };
	TArray<TArray<int> > marbleMovementTracker;
	TArray<TArray<int> > marblesToBeDestroyedMovementTracker;
	TArray<bool> marbleIsTurning;
	TArray<int> turnToExecute;
	TArray<int> dirOfMarbles;
	TArray<FVector2D> deltaMarblePos;
	int quantityOfMarbles;

	int timeOfGame = 120;
	double startingTime = 0;
	double fCurrentTime = 0;
	int currentTime = 120;
	double spawningWindow;
	TArray<double> timeIntoWindowMarbleIsSpawned;
	bool gameStarted = false;
	bool gameEnded;
	double speedMultiplier;
	double timeToCoverOneTileDividedByTwo;

	FMargin marbleToBeDestroyedPadding;
};
