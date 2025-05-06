// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "mediaPlayer.h"
#include "ImgMediaSource.h"
#include "MyHUD.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class FIVEPOINTFOURREBUILD_API SMediaPrecacheOperation : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMediaPrecacheOperation) {}

		SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwningHUD)

		/*SLATE_ARGUMENT(UImgMediaSource*, grass_IS_1)

		SLATE_ARGUMENT(UImgMediaSource*, grass_IS_2)

		SLATE_ARGUMENT(UImgMediaSource*, grass_IS_3)

		SLATE_ARGUMENT(UImgMediaSource*, pondHorizontal_IS)

		SLATE_ARGUMENT(UImgMediaSource*, pondVerticleFlowingLeft_IS)

		SLATE_ARGUMENT(UImgMediaSource*, pondVerticleFlowingRight_IS)

		SLATE_ARGUMENT(UImgMediaSource*, riverFlowingDown_IS_1)

		SLATE_ARGUMENT(UImgMediaSource*, riverFlowingDown_IS_2)

		SLATE_ARGUMENT(UImgMediaSource*, riverFlowingDown_IS_3)

		SLATE_ARGUMENT(UImgMediaSource*, riverFlowingLeft_IS_1)

		SLATE_ARGUMENT(UImgMediaSource*, riverFlowingLeft_IS_2)

		SLATE_ARGUMENT(UImgMediaSource*, riverFlowingLeft_IS_3)

		SLATE_ARGUMENT(UImgMediaSource*, riverFlowingRight_IS_1)

		SLATE_ARGUMENT(UImgMediaSource*, riverFlowingRight_IS_2)

		SLATE_ARGUMENT(UImgMediaSource*, riverFlowingRight_IS_3)

		SLATE_ARGUMENT(UImgMediaSource*, tree_IS_1)

		SLATE_ARGUMENT(UImgMediaSource*, tree_IS_2)

		SLATE_ARGUMENT(UImgMediaSource*, tree_IS_3)

		SLATE_ARGUMENT(UImgMediaSource*, tree_IS_4)

		SLATE_ARGUMENT(UImgMediaSource*, tree_IS_5)

		SLATE_ARGUMENT(UImgMediaSource*, waterfall_IS)

		SLATE_ARGUMENT(UImgMediaSource*, riverTurning_IS_1)

		SLATE_ARGUMENT(UImgMediaSource*, riverTurning_IS_2)

		SLATE_ARGUMENT(UImgMediaSource*, riverTurning_IS_3)

		SLATE_ARGUMENT(UImgMediaSource*, riverTurning_IS_4)

		SLATE_ARGUMENT(UImgMediaSource*, mountain_IS_1)

		SLATE_ARGUMENT(UImgMediaSource*, holeFromDown_IS)

		SLATE_ARGUMENT(UImgMediaSource*, holeFromLeft_IS)

		SLATE_ARGUMENT(UImgMediaSource*, holeFromRight_IS)

		SLATE_ARGUMENT(UImgMediaSource*, holeFromUp_IS)

		SLATE_ARGUMENT(UImgMediaSource*, flag_IS_1)

		SLATE_ARGUMENT(UImgMediaSource*, flag_IS_2)

		SLATE_ARGUMENT(UImgMediaSource*, flag_IS_3)

		SLATE_ARGUMENT(UImgMediaSource*, flag_IS_4)

		SLATE_ARGUMENT(UImgMediaSource*, flag_IS_5)

		SLATE_ARGUMENT(UImgMediaSource*, flag_IS_6)

		SLATE_ARGUMENT(UImgMediaSource*, flag_IS_7)

		SLATE_ARGUMENT(UImgMediaSource*, flag_IS_8)

		SLATE_ARGUMENT(UImgMediaSource*, flag_IS_9)

		SLATE_ARGUMENT(UImgMediaSource*, flag_IS_10)

		SLATE_ARGUMENT(UImgMediaSource*, flag_IS_11)

		SLATE_ARGUMENT(UImgMediaSource*, flag_IS_12)

		SLATE_ARGUMENT(UImgMediaSource*, flag_IS_13)

		SLATE_ARGUMENT(UImgMediaSource*, flag_IS_14)

		SLATE_ARGUMENT(UImgMediaSource*, flag_IS_15)

		SLATE_ARGUMENT(UImgMediaSource*, flag_IS_16)

		SLATE_ARGUMENT(UImgMediaSource*, curtains_IS)

		SLATE_ARGUMENT(UImgMediaSource*, neon_IS)

		SLATE_ARGUMENT(UMediaPlayer*, grass_MP_1)

		SLATE_ARGUMENT(UMediaPlayer*, grass_MP_2)

		SLATE_ARGUMENT(UMediaPlayer*, grass_MP_3)

		SLATE_ARGUMENT(UMediaPlayer*, pondHorizontal_MP)

		SLATE_ARGUMENT(UMediaPlayer*, pondVerticleFlowingLeft_MP)

		SLATE_ARGUMENT(UMediaPlayer*, pondVerticleFlowingRight_MP)

		SLATE_ARGUMENT(UMediaPlayer*, riverFlowingDown_MP_1)

		SLATE_ARGUMENT(UMediaPlayer*, riverFlowingDown_MP_2)

		SLATE_ARGUMENT(UMediaPlayer*, riverFlowingDown_MP_3)

		SLATE_ARGUMENT(UMediaPlayer*, riverFlowingLeft_MP_1)

		SLATE_ARGUMENT(UMediaPlayer*, riverFlowingLeft_MP_2)

		SLATE_ARGUMENT(UMediaPlayer*, riverFlowingLeft_MP_3)

		SLATE_ARGUMENT(UMediaPlayer*, riverFlowingRight_MP_1)

		SLATE_ARGUMENT(UMediaPlayer*, riverFlowingRight_MP_2)

		SLATE_ARGUMENT(UMediaPlayer*, riverFlowingRight_MP_3)

		SLATE_ARGUMENT(UMediaPlayer*, tree_MP_1)

		SLATE_ARGUMENT(UMediaPlayer*, tree_MP_2)

		SLATE_ARGUMENT(UMediaPlayer*, tree_MP_3)

		SLATE_ARGUMENT(UMediaPlayer*, tree_MP_4)

		SLATE_ARGUMENT(UMediaPlayer*, tree_MP_5)

		SLATE_ARGUMENT(UMediaPlayer*, waterfall_MP)

		SLATE_ARGUMENT(UMediaPlayer*, riverTurning_MP_1)

		SLATE_ARGUMENT(UMediaPlayer*, riverTurning_MP_2)

		SLATE_ARGUMENT(UMediaPlayer*, riverTurning_MP_3)

		SLATE_ARGUMENT(UMediaPlayer*, riverTurning_MP_4)

		SLATE_ARGUMENT(UMediaPlayer*, mountain_MP_1)

		SLATE_ARGUMENT(UMediaPlayer*, holeFromDown_MP)

		SLATE_ARGUMENT(UMediaPlayer*, holeFromLeft_MP)

		SLATE_ARGUMENT(UMediaPlayer*, holeFromRight_MP)

		SLATE_ARGUMENT(UMediaPlayer*, holeFromUp_MP)

		SLATE_ARGUMENT(UMediaPlayer*, flag_MP_1)

		SLATE_ARGUMENT(UMediaPlayer*, flag_MP_2)

		SLATE_ARGUMENT(UMediaPlayer*, flag_MP_3)

		SLATE_ARGUMENT(UMediaPlayer*, flag_MP_4)

		SLATE_ARGUMENT(UMediaPlayer*, flag_MP_5)

		SLATE_ARGUMENT(UMediaPlayer*, flag_MP_6)

		SLATE_ARGUMENT(UMediaPlayer*, flag_MP_7)

		SLATE_ARGUMENT(UMediaPlayer*, flag_MP_8)

		SLATE_ARGUMENT(UMediaPlayer*, flag_MP_9)

		SLATE_ARGUMENT(UMediaPlayer*, flag_MP_10)

		SLATE_ARGUMENT(UMediaPlayer*, flag_MP_11)

		SLATE_ARGUMENT(UMediaPlayer*, flag_MP_12)

		SLATE_ARGUMENT(UMediaPlayer*, flag_MP_13)

		SLATE_ARGUMENT(UMediaPlayer*, flag_MP_14)

		SLATE_ARGUMENT(UMediaPlayer*, flag_MP_15)

		SLATE_ARGUMENT(UMediaPlayer*, flag_MP_16)

		SLATE_ARGUMENT(UMediaPlayer*, curtains_MP)

		SLATE_ARGUMENT(UMediaPlayer*, neon_MP)*/

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

		SLATE_ARGUMENT(UMaterial*, curtains_VMUI)

		SLATE_ARGUMENT(UMaterial*, neon_VMUI)

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

		SLATE_ARGUMENT(UMaterial*, focusCursor_SMUI)

		SLATE_ARGUMENT(UMaterial*, gameFrameColor_SMUI)

		SLATE_ARGUMENT(UMaterial*, emptyImg_SMUI)

		SLATE_ARGUMENT(UMaterial*, goodUseSplashBootNoGrass_SMUI)

		SLATE_ARGUMENT(UMaterial*, goodUseSplashGrass_SMUI)

		SLATE_ARGUMENT(UMaterial*, goodUseDigitalText_SMUI)

		SLATE_ARGUMENT(TArray <UMaterial*>, splashGrassArr)

		SLATE_ARGUMENT(TArray <UMaterial*>, splashBootArr)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

	const FMargin CalculateTilePosition(FVector2D tileCoords);
	const FMargin CalculateLargeTilePosition(FVector2D tileCoords);

	UPROPERTY() TWeakObjectPtr<class AMyHUD> OwningHUD;

	UPROPERTY() FVector2D viewportSize;
	UPROPERTY() FVector2D adjustedViewportSize;
	UPROPERTY() float DPIScale;

	UPROPERTY() TArray <UImgMediaSource*> all_IS;
	UPROPERTY() TArray <UMediaPlayer*> all_MP;
	UPROPERTY() TArray <UMaterial*> all_VMUI;
	UPROPERTY() TArray <FSlateBrush*> all_VSB;
	UPROPERTY() TArray <UMaterial*> all_SMUI;
	UPROPERTY() TArray <FSlateBrush*> all_SB;

	UPROPERTY() TSharedPtr< class SOverlay> VMUI_Overlay;
	UPROPERTY() TSharedPtr< class SOverlay> SMUI_Overlay;

	UPROPERTY() TArray <UMaterial*> splashBootArr;
	UPROPERTY() TArray <UMaterial*> splashGrassArr;

	UPROPERTY() int timer;
	UPROPERTY() int coef;
	UPROPERTY() bool operate;
	UPROPERTY() bool operateTwo;
	UPROPERTY() bool operateThree;


};
