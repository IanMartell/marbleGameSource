// Fill out your copyright notice in the Description page of Project Settings.


#include "SCompanySplash.h"
#include "SlateOptMacros.h"
#include "Components/AudioComponent.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

FMargin SCompanySplash::CalculateSplashMarginOne()
{
	float fOne = (adjustedViewportSize.X - adjustedViewportSize.Y) / 2;
	
	return FMargin(fOne, 0, fOne, 0);
}

FMargin SCompanySplash::CalculateSplashMarginTwo()
{
	float fOne = (adjustedViewportSize.X - adjustedViewportSize.Y) / 2;

	return FMargin(fOne, (adjustedViewportSize.Y * 0.0034), fOne, ((adjustedViewportSize.Y * 0.0034) * -1));
}

FMargin SCompanySplash::CalculateStartingTextMargin()
{
	float fOne = ((adjustedViewportSize.X - adjustedViewportSize.Y) / 2) + (adjustedViewportSize.Y * 0.2125);
	float fTwo = ((adjustedViewportSize.Y * 0.075) * -1.0);

	return FMargin(fOne, adjustedViewportSize.Y, fOne,  fTwo);
}

void SCompanySplash::Construct(const FArguments& InArgs)
{
	SetCanTick(true);
	bCanSupportFocus = true;

	OwningHUD = InArgs._OwningHUD;
	goodUseSplashBootNoGrass_SMUI = InArgs._goodUseSplashBootNoGrass_SMUI;
	goodUseSplashGrass_SMUI = InArgs._goodUseSplashGrass_SMUI;
	goodUseDigitalText_SMUI = InArgs._goodUseDigitalText_SMUI;
	splashGrassArr = InArgs._splashGrassArr;
	splashBootArr = InArgs._splashBootArr;
	black_SMUI = InArgs._black_SMUI;
	shovelingDirtAudioComponent = InArgs._shovelingDirtAudioComponent;

	shovelingDirtAudioComponent->Stop();

	for (int a = 0; a < 5; a++)
	{
		splashBootSBArr.Add(new FSlateBrush());
		splashBootSBArr[a]->SetResourceObject(splashBootArr[a]);
	}

	for (int a = 0; a < 17; a++)
	{
		splashGrassSBArr.Add(new FSlateBrush());
		splashGrassSBArr[a]->SetResourceObject(splashGrassArr[a]);
	}

	goodUseDigitalText_SB = new FSlateBrush();
	goodUseDigitalText_SB->SetResourceObject(goodUseDigitalText_SMUI);

	black_SB = new FSlateBrush();
	black_SB->SetResourceObject(black_SMUI);

	masterButtonStyle = new FButtonStyle();
	masterButtonStyle->SetNormalPadding(FMargin());

	timer = 0;
	trackerOne = 0;
	trackerTwo = 0;

	splashScreenOverlay = SNew(SOverlay);

	splashScreenOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.ColorAndOpacity(FLinearColor(0, 0, 0, 1))
		];

	imageOne = SNew(SImage)
		.Image(black_SB);

	imageBoxOne = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(FMargin());

	textBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(FMargin());

	splashScreenOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			imageBoxOne.ToSharedRef()
		];

	splashScreenOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			textBox.ToSharedRef()
		];

	splashScreenOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SButton)
			.ContentPadding(FMargin())
			.ButtonStyle(masterButtonStyle)
			.OnReleased(this, &SCompanySplash::Released)
			.ButtonColorAndOpacity(FLinearColor::Transparent)
			.IsEnabled(true)
		];

	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			splashScreenOverlay.ToSharedRef()
		]
	];
}

void SCompanySplash::Released()
{
	OwningHUD->DestroySplash();
}

void SCompanySplash::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if (canTick)
	{
		timer += InDeltaTime;

		intOne = FMath::DivideAndRoundDown((double)timer - 0.5, 0.0194);

		if (trackerOne < intOne && trackerOne < 17)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "tracker before: " + FString::FromInt(trackerOne));
			trackerOne = intOne;

			imageOne->SetImage(splashGrassSBArr[trackerOne - 1]);

			if (trackerOne > 12)
			{
				if (trackerOne == 13)
				{
					textBox->SetContent(SNew(SImage).Image(goodUseDigitalText_SB));
				}

				shiftingMargin = ((double)adjustedMarginFloat * (double)sin((double)31.4159 * (double)((double)((double)timer - (double)0.7329) - (double)0.05))) + (double)adjustedMarginFloat;
				textBox->SetPadding(FMargin((double)startingTextMargin.Left, (double)((double)startingTextMargin.Top - (double)shiftingMargin), (double)startingTextMargin.Right, (double)((double)startingTextMargin.Bottom + (double)shiftingMargin)));
			}

			//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "tracker after: " + FString::FromInt(trackerOne));
			//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "timer: " + FString::SanitizeFloat(timer));
		}

		intTwo = FMath::DivideAndRoundDown((double)timer - 1.5, (double)0.1);

		if (trackerTwo < intTwo && trackerTwo < 5)
		{
			trackerTwo = intTwo;

			imageOne->SetImage(splashBootSBArr[trackerTwo - 1]);

			if (trackerTwo == 4)
			{
				shovelingDirtAudioComponent->Play();
			}
		}

		if (timer > 5)
		{
			OwningHUD->DestroySplash();
		}
	}
	else
	{
		GEngine->GameViewport->GetViewportSize(viewportSize);
		if (viewportSize.Y > 10 && viewportSize.X > 10)//testing required
		{
			int32 X = FGenericPlatformMath::FloorToInt(viewportSize.X);
			int32 Y = FGenericPlatformMath::FloorToInt(viewportSize.Y);
			DPIScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(X, Y));
			adjustedViewportSize = (1 / DPIScale) * viewportSize;

			startingTextMargin = CalculateStartingTextMargin();
			adjustedMarginFloat = (float)((float)adjustedViewportSize.Y * (float)0.04375);

			imageBoxOne->SetPadding(CalculateSplashMarginOne());
			imageBoxOne->SetContent(imageOne.ToSharedRef());

			canTick = true;
		}
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
