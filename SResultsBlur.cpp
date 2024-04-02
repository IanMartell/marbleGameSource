// Fill out your copyright notice in the Description page of Project Settings.


#include "SResultsBlur.h"
#include "SlateOptMacros.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"

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
	standardBlur = 5;

	masterButtonStyle = new FButtonStyle();
	masterButtonStyle->SetNormalPadding(FMargin());

	blur = SNew(SBackgroundBlur)
		.BlurStrength(standardBlur);

	resultsTextOne = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::White)
		.Font(titleFont)
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	if (currentSave->GetScoreThisGame() > currentSave->GetHighscores()[1])
	{
		resultsTextOne->SetText(FText::FromString("New Highscore!"));
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
		[
			SNew(SButton)
			.ContentPadding(FMargin())
			.ButtonStyle(masterButtonStyle)
			.OnPressed(this, &SResultsBlur::Pressed)
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
	}

	return FReply::Handled();
}

void SResultsBlur::Pressed()
{
	if (destroySelf == false)
	{
		destroySelf = true;
		timer = 0;
	}
}

void SResultsBlur::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if (destroySelf)
	{
		timer += InDeltaTime;
		blur->SetBlurStrength(standardBlur - ((2.5 * sin(25.13 * (timer - 0.0625))) + 2.5));
		resultsTextOne->SetColorAndOpacity(FLinearColor( 1, 1, 1, standardOpacity - ((0.5 * sin(25.13 * (timer - 0.0625))) + 0.5)));
		resultsTextOne->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity - ((0.5 * sin(25.13 * (timer - 0.0625))) + 0.5)));
		resultsTextTwo->SetColorAndOpacity(FLinearColor(1, 1, 1, standardOpacity - ((0.5 * sin(25.13 * (timer - 0.0625))) + 0.5)));
		resultsTextTwo->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity - ((0.5 * sin(25.13 * (timer - 0.0625))) + 0.5)));
		resultsTextThree->SetColorAndOpacity(FLinearColor(1, 1, 1, standardOpacity - ((0.5 * sin(25.13 * (timer - 0.0625))) + 0.5)));
		resultsTextThree->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity - ((0.5 * sin(25.13 * (timer - 0.0625))) + 0.5)));
		resultsTextFour->SetColorAndOpacity(FLinearColor(1, 1, 1, standardOpacity - ((0.5 * sin(25.13 * (timer - 0.0625))) + 0.5)));
		resultsTextFour->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity - ((0.5 * sin(25.13 * (timer - 0.0625))) + 0.5)));
		resultsTextFive->SetColorAndOpacity(FLinearColor(1, 1, 1, standardOpacity - ((0.5 * sin(25.13 * (timer - 0.0625))) + 0.5)));
		resultsTextFive->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity - ((0.5 * sin(25.13 * (timer - 0.0625))) + 0.5)));

		if (timer >= 0.125)
		{
			OwningHUD->RemoveResultsBlur();
		}
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
