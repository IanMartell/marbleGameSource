// Fill out your copyright notice in the Description page of Project Settings.


#include "SLoadingSplash.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "Widgets/Layout/SBackgroundBlur.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SLoadingSplash::SetOperateFour(bool inBool)
{
	operateFour = inBool;
}

void SLoadingSplash::Construct(const FArguments& InArgs)
{
	OwningHUD = InArgs._OwningHUD;
	black_SMUI = InArgs._black_SMUI;
	logo_SMUI = InArgs._logo_SMUI;

	black_SB = new FSlateBrush();
	black_SB->SetResourceObject(black_SMUI);
	logo_SB = new FSlateBrush();
	logo_SB->SetResourceObject(logo_SMUI);

	GEngine->GameViewport->GetViewportSize(viewportSize);
	int32 X = FGenericPlatformMath::FloorToInt(viewportSize.X);
	int32 Y = FGenericPlatformMath::FloorToInt(viewportSize.Y);
	DPIScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(X, Y));
	adjustedViewportSize = (1 / DPIScale) * viewportSize;

	operate = true;
	operateTwo = true;
	operateThree = false;
	operateFour = false;
	operateTimer = 0;
	fadeTimer = 0;

	fadeLinearColor = FLinearColor(0, 0, 0, 1);

	fade = SNew(SImage)
		.ColorAndOpacity(fadeLinearColor);

	logoImg = SNew(SImage)
		.Image(black_SB);

	boxOne = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			logoImg.ToSharedRef()
		];

	overlay = SNew(SOverlay);

	overlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(FMargin())
		[
			SNew(SImage)
				.Image(black_SB)
		];

	overlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			boxOne.ToSharedRef()
		];

	overlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(FMargin())
		[
			fade.ToSharedRef()
		];

	ChildSlot
	[
		SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				overlay.ToSharedRef()
			]
	];
}

void SLoadingSplash::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if (operateTwo)
	{
		if (operateTimerTwo >= 20)
		{
			GEngine->GameViewport->GetViewportSize(viewportSize);
			int32 X = FGenericPlatformMath::FloorToInt(viewportSize.X);
			int32 Y = FGenericPlatformMath::FloorToInt(viewportSize.Y);
			DPIScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(X, Y));
			adjustedViewportSize = (1 / DPIScale) * viewportSize;

			globalFOne = (adjustedViewportSize.X - ((adjustedViewportSize.Y * 0.6) * 0.8236)) / 2;

			boxOne->SetPadding(FMargin(globalFOne, adjustedViewportSize.Y * 0.2, globalFOne, adjustedViewportSize.Y * 0.2));
			logoImg->SetImage(logo_SB);

			operateTwo = false;
			operateThree = true;
		}

		operateTimerTwo += 1;
	}

	if (operateThree)
	{
		fadeTimer += InDeltaTime;
		fadeLinearColor.A = (float)((float)1 - (float)(((float)0.46 * (float)sin((float)9.425 * (float)(fadeTimer - (float)0.1666))) + (float)0.46));
		fade->SetColorAndOpacity(fadeLinearColor);
		
		if (fadeTimer >= 0.32)
		{
			fadeLinearColor.A = 0.08;
			fade->SetColorAndOpacity(fadeLinearColor);
			operateThree = false;
			fadeTimer = 0;
		}
	}

	if (operate)
	{
		if (operateTimer >= 60)
		{
			OwningHUD->EngageMediaPrecacheOperation();

			operate = false;
		}

		operateTimer += 1;
	}

	if (operateFour)
	{
		fadeTimer += InDeltaTime;
		fadeLinearColor.A = (float)((float)0.08 + (float)(((float)0.46 * (float)sin((float)9.425 * (float)(fadeTimer - (float)0.1666))) + (float)0.46));
		fade->SetColorAndOpacity(fadeLinearColor);

		if (fadeTimer >= 0.32)
		{
			fadeLinearColor.A = 1;
			fade->SetColorAndOpacity(fadeLinearColor);
			operateFour = false;
			fadeTimer = 0;
		}
	}
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
