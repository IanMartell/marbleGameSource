// Fill out your copyright notice in the Description page of Project Settings.


#include "SResultsBlur.h"
#include "Widgets/Layout/SBackgroundBlur.h"
#include "Components/AudioComponent.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

FMargin SResultsBlur::CalculateHighscorePos(int textIndex, int numberOfLetters)
{//since the buttons expand from the center they must be aligned from the center. this means for them to line up vertically the left and right pads need to be calculated so their centers are always equivalent
	float fOne = ((adjustedViewportSize.X - adjustedViewportSize.Y) / 2) + (adjustedViewportSize.Y * 0.5);
	float fThree = ((adjustedViewportSize.X - adjustedViewportSize.Y) / 2) + ((adjustedViewportSize.Y / 10) * 5);
	float fTwo = FMath::DivideAndRoundUp(numberOfLetters, 5);
	float leftPad = fOne - ((adjustedViewportSize.Y / 10) * fTwo);
	float topPad = adjustedViewportSize.Y * (0.25 + (0.1 * textIndex));
	float rightPad = adjustedViewportSize.X - (leftPad + ((adjustedViewportSize.Y / 5) * fTwo));
	float bottomPad = adjustedViewportSize.Y * (0.675 - (0.1 * textIndex));

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

void SResultsBlur::Construct(const FArguments& InArgs)
{
	SetCanTick(true);
	currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));
	bCanSupportFocus = true;

	OwningHUD = InArgs._OwningHUD;
	rainstickAudioComponent = InArgs._rainstickAudioComponent;
	victoryAudioComponents = InArgs._victoryAudioComponents;
	newMaxLevel = InArgs._newMaxLevel;

	GEngine->GameViewport->GetViewportSize(viewportSize);
	int32 X = FGenericPlatformMath::FloorToInt(viewportSize.X);
	int32 Y = FGenericPlatformMath::FloorToInt(viewportSize.Y);
	DPIScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(X, Y));
	adjustedViewportSize = (1 / DPIScale) * viewportSize;

	destroySelf = false;

	titleFont = FCoreStyle::Get().GetFontStyle("Roboto");
	titleFont.Size = 0.05 * adjustedViewportSize.Y;
	scoreFont = FCoreStyle::Get().GetFontStyle("Roboto");
	scoreFont.Size = 0.035 * adjustedViewportSize.Y;

	standardOpacity = 1;
	standardBlur = 30;

	rainstickAudioComponent->SetVolumeMultiplier(12.0);
	rainstickAudioComponent->Stop();

	masterButtonStyle = new FButtonStyle();
	masterButtonStyle->SetNormalPadding(FMargin());

	blur = SNew(SBackgroundBlur)
		.BlurStrength(standardBlur); // when lerping in and out the lighting gets all jittery. can SForegroundBlur be used instead? No doesn't exist.

	resultsTextOne = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::White)
		.Font(titleFont)
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	if (currentSave->GetScoreThisGame() > currentSave->GetHighscores()[1])
	{
		if (newMaxLevel)
		{
			resultsTextOne->SetText(FText::FromString("Level " + FString::FromInt(currentSave->GetMaxLevel() + 3) + " Unlocked!"));
			victoryAudioComponents[FMath::RandRange(0, 2)]->Play();
			OwningHUD->newMaxLevel = false;
		}
		else
		{
			resultsTextOne->SetText(FText::FromString("New Highscore!"));
		}
	}
	else
	{
		resultsTextOne->SetText(FText::FromString("Score"));
	}

	resultsTextTwo = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::White)
		.Font(scoreFont)
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity))
		.Text(FText::FromString("Marbles Sorted = " + FString::FromInt(currentSave->GetHighscoreDataTwo())));

	resultsTextThree = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::White)
		.Font(scoreFont)
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity))
		.Text(FText::FromString("Difficulty = " + FString::FromInt(currentSave->GetHighscoreDataOne())));

	resultsTextFour = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::White)
		.Font(scoreFont)
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity))
		.Text(FText::FromString(FString::FromInt(currentSave->GetHighscoreDataTwo()) + " X " + FString::SanitizeFloat(1.2) + "^" + FString::FromInt(currentSave->GetHighscoreDataOne())));

	resultsTextFive = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::White)
		.Font(scoreFont)
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity))
		.Text(FText::FromString(FString::FromInt(currentSave->GetHighscoreDataTwo() * pow(1.2, currentSave->GetHighscoreDataOne()))));

	resultsTextSix = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::White)
		.Font(scoreFont)
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity))
		.Text(FText::FromString("Click Anywhere"));

	resultsOverlay = SNew(SOverlay);

	resultsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			blur.ToSharedRef()
		];

	resultsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateHighscorePos(0, 11))
		[
			resultsTextOne.ToSharedRef()
		];

	resultsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateHighscorePos(1, 11))
		[
			resultsTextTwo.ToSharedRef()
		];

	resultsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateHighscorePos(2, 11))
		[
			resultsTextThree.ToSharedRef()
		];

	resultsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateHighscorePos(3, 6))
		[
			resultsTextFour.ToSharedRef()
		];

	resultsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateHighscorePos(4, 1))
		[
			resultsTextFive.ToSharedRef()
		];

	resultsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateHighscorePos(6, 6))
		[
			resultsTextSix.ToSharedRef()
		];

	resultsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SButton)
				.ContentPadding(FMargin())
				.ButtonStyle(masterButtonStyle)
				.OnReleased(this, &SResultsBlur::Released)
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
					resultsOverlay.ToSharedRef()
				]
		];
}

FReply SResultsBlur::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::AnyKey && destroySelf == false)
	{
		destroySelf = true;
		timer = 0;
		rainstickAudioComponent->Play();
	}

	if (InKeyEvent.GetKey() == EKeys::Q && destroySelf == false)
	{
		destroySelf = true;
		timer = 0;
		rainstickAudioComponent->Play();
	}

	return FReply::Handled();
}

void SResultsBlur::Released()
{
	if (destroySelf == false)
	{
		destroySelf = true;
		timer = 0;
		rainstickAudioComponent->Play();
	}
}

void SResultsBlur::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if (destroySelf)
	{
		timer += InDeltaTime;
		shrinkingOpacityWhite = FLinearColor(1, 1, 1, standardOpacity - ((0.5 * sin(37.7 * (timer - 0.04166))) + 0.5));
		shrinkingOpacityBlack = FLinearColor(0, 0, 0, standardOpacity - ((0.5 * sin(37.7 * (timer - 0.04166))) + 0.5));

		blur->SetBlurStrength(standardBlur - ((15 * sin(37.7 * (timer - 0.04166))) + 15));
		resultsTextOne->SetColorAndOpacity(shrinkingOpacityWhite);
		resultsTextOne->SetShadowColorAndOpacity(shrinkingOpacityBlack);
		resultsTextTwo->SetColorAndOpacity(shrinkingOpacityWhite);
		resultsTextTwo->SetShadowColorAndOpacity(shrinkingOpacityBlack);
		resultsTextThree->SetColorAndOpacity(shrinkingOpacityWhite);
		resultsTextThree->SetShadowColorAndOpacity(shrinkingOpacityBlack);
		resultsTextFour->SetColorAndOpacity(shrinkingOpacityWhite);
		resultsTextFour->SetShadowColorAndOpacity(shrinkingOpacityBlack);
		resultsTextFive->SetColorAndOpacity(shrinkingOpacityWhite);
		resultsTextFive->SetShadowColorAndOpacity(shrinkingOpacityBlack);
		resultsTextSix->SetColorAndOpacity(shrinkingOpacityWhite);
		resultsTextSix->SetShadowColorAndOpacity(shrinkingOpacityBlack);

		if (timer >= 0.0833)
		{
			OwningHUD->RemoveResultsBlur();
		}
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
