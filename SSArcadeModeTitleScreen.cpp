// Fill out your copyright notice in the Description page of Project Settings.


#include "SSArcadeModeTitleScreen.h"
#include "SlateOptMacros.h"

const FMargin CalculateTitlePosition(FVector2D viewportSize)
{
	float leftPad = viewportSize.X * 0.1;
	float topPad = viewportSize.Y * 0.1;
	float rightPad = viewportSize.X * 0.5;
	float bottomPad = viewportSize.Y * 0.8;

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

const FMargin CalculateSubTitlePosition(FVector2D viewportSize)
{
	float leftPad = viewportSize.X * 0.1;
	float topPad = viewportSize.Y * 0.1;
	float rightPad = viewportSize.X * 0.6;
	float bottomPad = viewportSize.Y * 0.85;

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

const FMargin CalculateMenuTextPosition(FVector2D viewportSize, int textIndex)
{
	float leftPad = viewportSize.X * 0.2;
	float topPad = viewportSize.Y * (0.3 + textIndex);
	float rightPad = viewportSize.X * 0.6;
	float bottomPad = viewportSize.Y * (0.625 - textIndex);

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

const FMargin CalculateBackgroundPositions(FVector2D viewportSize, int index)
{//this will only work if screenSize.X >= screenSize.Y
	float viewportX = adjustedViewportSize.X;
	float viewportY = adjustedViewportSize.Y;
	float fOne = (viewportX - viewportY) / 2;
	float leftPad = fOne + (viewportY / 3) * (index % 3);
	float topPad = (viewportY / 3) * FMath::DivideAndRoundDown(index, 3);
	float rightPad = fOne + (viewportY / 3) * (2 - (index % 3));
	float bottomPad = viewportY - (viewportY / 3) * (1 + FMath::DivideAndRoundDown(index, 3));

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSArcadeModeTitleScreen::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;

	OwningHUD = InArgs._OwningHUD;
	playerOnePlayerController = InArgs._playerOnePlayerController;
	gameFrameColor_SMUI = InArgs._gameFrameColor_SMUI;
	backgroundStuff = InArgs._backgroundStuff;

	gameFrameColor_SB = new FSlateBrush();
	gameFrameColor_SB->SetResourceObject(gameFrameColor_SMUI);
	
	GEngine->GameViewport->GetViewportSize(viewportSize);
	int32 X = FGenericPlatformMath::FloorToInt(viewportSize.X);
	int32 Y = FGenericPlatformMath::FloorToInt(viewportSize.Y);
	DPIScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(X, Y));
	adjustedViewportSize = (1 / DPIScale) * viewportSize;

	titleTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	titleTextStyle.Size = 0.06 * adjustedViewportSize.Y;
	titleText = FText::FromString("Mind Marbles");

	frameColorOverlay = SNew(SOverlay);

	backgroundOverlay = SNew(SOverlay);
	for (int a = 0; a < 9; a++)
	{
		backgroundOverlay->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateBackgroundPositions(adjustedViewportSize, a))
			[
				SNew(SImage)
				.Image(backgroundStuff[a])
			]
	}

	ChildSlot
	[
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			frameColorOverlay.ToSharedRef()
		]
	]
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
