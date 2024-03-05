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

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSArcadeModeTitleScreen::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;

	OwningHUD = InArgs._OwningHUD;
	playerOnePlayerController = InArgs._playerOnePlayerController;

	GEngine->GameViewport->GetViewportSize(viewportSize);
	int32 X = FGenericPlatformMath::FloorToInt(viewportSize.X);
	int32 Y = FGenericPlatformMath::FloorToInt(viewportSize.Y);
	DPIScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(X, Y));
	adjustedViewportSize = (1 / DPIScale) * viewportSize;
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
