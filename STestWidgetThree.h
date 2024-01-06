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

	SLATE_ARGUMENT(TArray<bool>, tileIsIntersection)

	SLATE_ARGUMENT(APlayerController*, playerOnePlayerController)

	SLATE_ARGUMENT(UMaterial*, grass_VMUI_1)

	SLATE_ARGUMENT(UMaterial*, holeFromDown_VMUI)

	SLATE_ARGUMENT(UMaterial*, holeFromLeft_VMUI)

	SLATE_ARGUMENT(UMaterial*, holeFromRight_VMUI)

	SLATE_ARGUMENT(UMaterial*, holeFromUp_VMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromDownTurningRightZero_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromDownTurningLeftZero_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromLeftTurningRightZero_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromLeftTurningLeftZero_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromRightTurningRightZero_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromRightTurningLeftZero_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromUpTurningRightZero_SMUI)

	SLATE_ARGUMENT(UMaterial*, buttonFromUpTurningLeftZero_SMUI)

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

	SLATE_ARGUMENT(UMaterial*, emptyImg_SMUI)

	//SLATE_ARGUMENT(FVector2D, viewportSize)

	SLATE_END_ARGS()

	//every widget needs a construction function
	void Construct(const FArguments& InArgs);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

	FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);

	virtual bool IsInteractable() const override { return true; };
	virtual bool SupportsKeyboardFocus() const override { return true; };
	
	FReply OnClicked() const;
	FReply OnQuitClicked() const;
	void OnIntersectionPressed();
	void OnIntersectionReleased();

	// constructor variables

	TWeakObjectPtr<class ATestHud> OwningHUD;

	TArray<int> landscapeArr;
	TArray<int> trackArr;
	TArray<bool> tileIsIntersection;

	APlayerController* playerOnePlayerController;

	UMaterial* grass_VMUI_1;

	UMaterial* holeFromDown_VMUI;
	UMaterial* holeFromLeft_VMUI;
	UMaterial* holeFromRight_VMUI;
	UMaterial* holeFromUp_VMUI;

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

	UMaterial* emptyImg_SMUI;

	//variables and data structures associated with constructor vars
	UMaterial* placeholderTrash;

	//slate brushes
	FSlateBrush* grass_SB_1;

	FSlateBrush* holeFromDown_SB;
	FSlateBrush* holeFromLeft_SB;
	FSlateBrush* holeFromRight_SB;
	FSlateBrush* holeFromUp_SB;

	FSlateBrush* buttonFromDownTurningRightZero_SB;
	FSlateBrush* buttonFromDownTurningLeftZero_SB;
	FSlateBrush* buttonFromLeftTurningRightZero_SB;
	FSlateBrush* buttonFromLeftTurningLeftZero_SB;
	FSlateBrush* buttonFromRightTurningRightZero_SB;
	FSlateBrush* buttonFromRightTurningLeftZero_SB;
	FSlateBrush* buttonFromUpTurningRightZero_SB;
	FSlateBrush* buttonFromUpTurningLeftZero_SB;

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

	// misc variables and data structures

	FString materialPath = FPaths::ProjectContentDir() / TEXT("/Game/Movies/videoMaterialsForUI/grass_VMUI_1");

	FVector2D viewportSize;
	FVector2D adjustedViewportSize;

	FMargin testFMargin;

	FButtonStyle* masterButtonStyle;

public: 
	TSharedPtr<class SWindow> windowOne;
	TSharedPtr<class SImage> marbleOne;
	FWindowStyle marbleWindowStyle;
	TSharedPtr< class SOverlay> marbleOverlay;
	TSharedPtr< class FOverlaySlot> marbleOneSlot;
	TSharedPtr< class SBox> marbleOneBox;

	float DPIScale;

	UPROPERTY() FVector2D screenPosition;
	UPROPERTY() FVector2D screenSize;

	float viewportX = 0.0f;
	float viewportY = 0.0f;
	int deleteMe;
	int b;

	FMargin changingPosition;
};
