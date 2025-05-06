// Fill out your copyright notice in the Description page of Project Settings.


#include "SMediaPrecacheOperation.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "SlateOptMacros.h"

const FMargin SMediaPrecacheOperation::CalculateTilePosition(FVector2D tileCoords)//this has been adjusted to respond to 1D arr coordinates
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

const FMargin SMediaPrecacheOperation::CalculateLargeTilePosition(FVector2D tileCoords)
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

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMediaPrecacheOperation::Construct(const FArguments& InArgs)
{
	OwningHUD = InArgs._OwningHUD;
	/*all_IS.Add(InArgs._neon_IS);
	all_IS.Add(InArgs._curtains_IS);
	all_IS.Add(InArgs._grass_IS_1);
	all_IS.Add(InArgs._grass_IS_2);
	all_IS.Add(InArgs._grass_IS_3);
	all_IS.Add(InArgs._pondHorizontal_IS);
	all_IS.Add(InArgs._pondVerticleFlowingLeft_IS);
	all_IS.Add(InArgs._pondVerticleFlowingRight_IS);
	all_IS.Add(InArgs._riverFlowingDown_IS_1);
	all_IS.Add(InArgs._riverFlowingDown_IS_2);
	all_IS.Add(InArgs._riverFlowingDown_IS_3);
	all_IS.Add(InArgs._riverFlowingLeft_IS_1);
	all_IS.Add(InArgs._riverFlowingLeft_IS_2);
	all_IS.Add(InArgs._riverFlowingLeft_IS_3);
	all_IS.Add(InArgs._riverFlowingRight_IS_1);
	all_IS.Add(InArgs._riverFlowingRight_IS_2);
	all_IS.Add(InArgs._riverFlowingRight_IS_3);
	all_IS.Add(InArgs._tree_IS_1);
	all_IS.Add(InArgs._tree_IS_2);
	all_IS.Add(InArgs._tree_IS_3);
	all_IS.Add(InArgs._tree_IS_4);
	all_IS.Add(InArgs._tree_IS_5);
	all_IS.Add(InArgs._waterfall_IS);
	all_IS.Add(InArgs._riverTurning_IS_1);
	all_IS.Add(InArgs._riverTurning_IS_2);
	all_IS.Add(InArgs._riverTurning_IS_3);
	all_IS.Add(InArgs._riverTurning_IS_4);
	all_IS.Add(InArgs._mountain_IS_1);
	all_IS.Add(InArgs._holeFromDown_IS);
	all_IS.Add(InArgs._holeFromLeft_IS);
	all_IS.Add(InArgs._holeFromRight_IS);
	all_IS.Add(InArgs._holeFromUp_IS);
	all_IS.Add(InArgs._flag_IS_1);
	all_IS.Add(InArgs._flag_IS_2);
	all_IS.Add(InArgs._flag_IS_3);
	all_IS.Add(InArgs._flag_IS_4);
	all_IS.Add(InArgs._flag_IS_5);
	all_IS.Add(InArgs._flag_IS_6);
	all_IS.Add(InArgs._flag_IS_7);
	all_IS.Add(InArgs._flag_IS_8);
	all_IS.Add(InArgs._flag_IS_9);
	all_IS.Add(InArgs._flag_IS_10);
	all_IS.Add(InArgs._flag_IS_11);
	all_IS.Add(InArgs._flag_IS_12);
	all_IS.Add(InArgs._flag_IS_13);
	all_IS.Add(InArgs._flag_IS_14);
	all_IS.Add(InArgs._flag_IS_15);
	all_IS.Add(InArgs._flag_IS_16);*/

	all_VMUI.Add(InArgs._neon_VMUI);
	all_VMUI.Add(InArgs._curtains_VMUI);
	all_VMUI.Add(InArgs._grass_VMUI_1);
	all_VMUI.Add(InArgs._grass_VMUI_2);
	all_VMUI.Add(InArgs._grass_VMUI_3);
	all_VMUI.Add(InArgs._pondHorizontal_VMUI);
	all_VMUI.Add(InArgs._pondVerticleFlowingLeft_VMUI);
	all_VMUI.Add(InArgs._pondVerticleFlowingRight_VMUI);
	all_VMUI.Add(InArgs._riverFlowingDown_VMUI_1);
	all_VMUI.Add(InArgs._riverFlowingDown_VMUI_2);
	all_VMUI.Add(InArgs._riverFlowingDown_VMUI_3);
	all_VMUI.Add(InArgs._riverFlowingLeft_VMUI_1);
	all_VMUI.Add(InArgs._riverFlowingLeft_VMUI_2);
	all_VMUI.Add(InArgs._riverFlowingLeft_VMUI_3);
	all_VMUI.Add(InArgs._riverFlowingRight_VMUI_1);
	all_VMUI.Add(InArgs._riverFlowingRight_VMUI_2);
	all_VMUI.Add(InArgs._riverFlowingRight_VMUI_3);
	all_VMUI.Add(InArgs._tree_VMUI_1);
	all_VMUI.Add(InArgs._tree_VMUI_2);
	all_VMUI.Add(InArgs._tree_VMUI_3);
	all_VMUI.Add(InArgs._tree_VMUI_4);
	all_VMUI.Add(InArgs._tree_VMUI_5);
	all_VMUI.Add(InArgs._waterfall_VMUI);
	all_VMUI.Add(InArgs._riverTurning_VMUI_1);
	all_VMUI.Add(InArgs._riverTurning_VMUI_2);
	all_VMUI.Add(InArgs._riverTurning_VMUI_3);
	all_VMUI.Add(InArgs._riverTurning_VMUI_4);
	all_VMUI.Add(InArgs._mountain_VMUI_1);
	all_VMUI.Add(InArgs._holeFromDown_VMUI);
	all_VMUI.Add(InArgs._holeFromLeft_VMUI);
	all_VMUI.Add(InArgs._holeFromRight_VMUI);
	all_VMUI.Add(InArgs._holeFromUp_VMUI);
	all_VMUI.Add(InArgs._flag_VMUI_1);
	all_VMUI.Add(InArgs._flag_VMUI_2);
	all_VMUI.Add(InArgs._flag_VMUI_3);
	all_VMUI.Add(InArgs._flag_VMUI_4);
	all_VMUI.Add(InArgs._flag_VMUI_5);
	all_VMUI.Add(InArgs._flag_VMUI_6);
	all_VMUI.Add(InArgs._flag_VMUI_7);
	all_VMUI.Add(InArgs._flag_VMUI_8);
	all_VMUI.Add(InArgs._flag_VMUI_9);
	all_VMUI.Add(InArgs._flag_VMUI_10);
	all_VMUI.Add(InArgs._flag_VMUI_11);
	all_VMUI.Add(InArgs._flag_VMUI_12);
	all_VMUI.Add(InArgs._flag_VMUI_13);
	all_VMUI.Add(InArgs._flag_VMUI_14);
	all_VMUI.Add(InArgs._flag_VMUI_15);
	all_VMUI.Add(InArgs._flag_VMUI_16);
	all_SMUI.Add(InArgs._buttonFromDownTurningRightZero_SMUI);
	all_SMUI.Add(InArgs._buttonFromDownTurningRightOne_SMUI);
	all_SMUI.Add(InArgs._buttonFromDownTurningRightTwo_SMUI);
	all_SMUI.Add(InArgs._buttonFromDownTurningRightThree_SMUI);
	all_SMUI.Add(InArgs._buttonFromDownTurningLeftZero_SMUI);
	all_SMUI.Add(InArgs._buttonFromDownTurningLeftOne_SMUI);
	all_SMUI.Add(InArgs._buttonFromDownTurningLeftTwo_SMUI);
	all_SMUI.Add(InArgs._buttonFromDownTurningLeftThree_SMUI);
	all_SMUI.Add(InArgs._buttonFromLeftTurningRightZero_SMUI);
	all_SMUI.Add(InArgs._buttonFromLeftTurningRightOne_SMUI);
	all_SMUI.Add(InArgs._buttonFromLeftTurningRightTwo_SMUI);
	all_SMUI.Add(InArgs._buttonFromLeftTurningRightThree_SMUI);
	all_SMUI.Add(InArgs._buttonFromLeftTurningLeftZero_SMUI);
	all_SMUI.Add(InArgs._buttonFromLeftTurningLeftOne_SMUI);
	all_SMUI.Add(InArgs._buttonFromLeftTurningLeftTwo_SMUI);
	all_SMUI.Add(InArgs._buttonFromLeftTurningLeftThree_SMUI);
	all_SMUI.Add(InArgs._buttonFromRightTurningRightZero_SMUI);
	all_SMUI.Add(InArgs._buttonFromRightTurningRightOne_SMUI);
	all_SMUI.Add(InArgs._buttonFromRightTurningRightTwo_SMUI);
	all_SMUI.Add(InArgs._buttonFromRightTurningRightThree_SMUI);
	all_SMUI.Add(InArgs._buttonFromRightTurningLeftZero_SMUI);
	all_SMUI.Add(InArgs._buttonFromRightTurningLeftOne_SMUI);
	all_SMUI.Add(InArgs._buttonFromRightTurningLeftTwo_SMUI);
	all_SMUI.Add(InArgs._buttonFromRightTurningLeftThree_SMUI);
	all_SMUI.Add(InArgs._buttonFromUpTurningRightZero_SMUI);
	all_SMUI.Add(InArgs._buttonFromUpTurningRightOne_SMUI);
	all_SMUI.Add(InArgs._buttonFromUpTurningRightTwo_SMUI);
	all_SMUI.Add(InArgs._buttonFromUpTurningRightThree_SMUI);
	all_SMUI.Add(InArgs._buttonFromUpTurningLeftZero_SMUI);
	all_SMUI.Add(InArgs._buttonFromUpTurningLeftOne_SMUI);
	all_SMUI.Add(InArgs._buttonFromUpTurningLeftTwo_SMUI);
	all_SMUI.Add(InArgs._buttonFromUpTurningLeftThree_SMUI);
	all_SMUI.Add(InArgs._verticleRail_SMUI);
	all_SMUI.Add(InArgs._horizontalRail_SMUI);
	all_SMUI.Add(InArgs._railTurningOne_SMUI);
	all_SMUI.Add(InArgs._railTurningTwo_SMUI);
	all_SMUI.Add(InArgs._railTurningThree_SMUI);
	all_SMUI.Add(InArgs._railTurningFour_SMUI);
	all_SMUI.Add(InArgs._marble_SMUI_1);
	all_SMUI.Add(InArgs._marble_SMUI_2);
	all_SMUI.Add(InArgs._marble_SMUI_3);
	all_SMUI.Add(InArgs._marble_SMUI_4);
	all_SMUI.Add(InArgs._marble_SMUI_5);
	all_SMUI.Add(InArgs._marble_SMUI_6);
	all_SMUI.Add(InArgs._marble_SMUI_7);
	all_SMUI.Add(InArgs._marble_SMUI_8);
	all_SMUI.Add(InArgs._marble_SMUI_9);
	all_SMUI.Add(InArgs._marble_SMUI_10);
	all_SMUI.Add(InArgs._marble_SMUI_11);
	all_SMUI.Add(InArgs._marble_SMUI_12);
	all_SMUI.Add(InArgs._marble_SMUI_13);
	all_SMUI.Add(InArgs._marble_SMUI_14);
	all_SMUI.Add(InArgs._marble_SMUI_15);
	all_SMUI.Add(InArgs._marble_SMUI_16);
	all_SMUI.Add(InArgs._focusCursor_SMUI);
	all_SMUI.Add(InArgs._gameFrameColor_SMUI);
	all_SMUI.Add(InArgs._emptyImg_SMUI);
	all_SMUI.Add(InArgs._goodUseSplashBootNoGrass_SMUI);
	all_SMUI.Add(InArgs._goodUseSplashGrass_SMUI);
	all_SMUI.Add(InArgs._goodUseDigitalText_SMUI);
	all_SMUI.Append(InArgs._splashBootArr);
	all_SMUI.Append(InArgs._splashGrassArr);

	GEngine->GameViewport->GetViewportSize(viewportSize);
	int32 X = FGenericPlatformMath::FloorToInt(viewportSize.X);
	int32 Y = FGenericPlatformMath::FloorToInt(viewportSize.Y);
	DPIScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(X, Y));
	adjustedViewportSize = (1 / DPIScale) * viewportSize;

	//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "precache");
	//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "all_VMUI.Num(): " + FString::FromInt(all_VMUI.Num()));

	operate = true;
	operateTwo = true;
	operateThree = true;
	coef = 1;
	timer = 0;

	for (int a = 0; a < all_VMUI.Num(); a++)
	{
		all_VSB.Add(new FSlateBrush());
		all_VSB[a]->SetResourceObject(all_VMUI[a]);
	}

	for (int a = 0; a < all_SMUI.Num(); a++)
	{
		all_SB.Add(new FSlateBrush());
		all_SB[a]->SetResourceObject(all_SMUI[a]);
	}

	VMUI_Overlay = SNew(SOverlay);

	for (int a = 0; a < all_VSB.Num(); a++)
	{
		VMUI_Overlay->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15))))
			[
				SNew(SImage)
				.Image(all_VSB[a])
			];
	}

	SMUI_Overlay = SNew(SOverlay);

	for (int a = 0; a < all_SMUI.Num(); a++)
	{
		SMUI_Overlay->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D((224 - a) % 15, FMath::DivideAndRoundDown(224 - a, 15))))
			[
				SNew(SImage)
					.Image(all_SB[a])
			];
	}

	
	ChildSlot
	[
		SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				VMUI_Overlay.ToSharedRef()
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SMUI_Overlay.ToSharedRef()
			]
	];
}

void SMediaPrecacheOperation::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if (operate)
	{
		if (timer % coef == 0)
		{
			OwningHUD->ExecutePrecache(timer / coef);
		}

		if ((timer + coef) / coef >= all_VSB.Num())
		{
			operate = false;
		}
	}

	if (operateTwo)
	{
		if (timer > 520)
		{
			OwningHUD->HideLogoSplash();
			operateTwo = false;
		}
	}

	if (operateThree)
	{
		if (timer > 540)
		{
			OwningHUD->DestroyMediaPrecacheOperation();
			operateThree = false;
		}

	}

	timer += 1;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
