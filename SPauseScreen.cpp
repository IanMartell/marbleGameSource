// Fill out your copyright notice in the Description page of Project Settings.


#include "SPauseScreen.h"
#include "Widgets/Layout/SBackgroundBlur.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "Components/AudioComponent.h"
#include "SlateOptMacros.h"

FMargin SPauseScreen::CalculateTitlePosition(FVector2D funcViewportSize)
{//your sub titles will use this same positioning but the a different text style
	float leftPad = funcViewportSize.X * 0.1;
	float topPad = funcViewportSize.Y * 0.1;
	float rightPad = funcViewportSize.X * 0.1;
	float bottomPad = funcViewportSize.Y * 0.75;

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

FMargin SPauseScreen::CalculateMenuTextPos(int textIndex, int numberOfLetters)
{//since the buttons expand from the center they must be aligned from the center. this means for them to line up vertically the left and right pads need to be calculated so their centers are always equivalent
	float fOne = ((adjustedViewportSize.X - adjustedViewportSize.Y) / 2) + ((adjustedViewportSize.Y / 10) * 5);
	float fThree = ((adjustedViewportSize.X - adjustedViewportSize.Y) / 2) + ((adjustedViewportSize.Y / 10) * 5);
	float fTwo = FMath::DivideAndRoundUp(numberOfLetters, 5);
	float leftPad = fOne - ((adjustedViewportSize.Y / 10) * fTwo);
	float topPad = adjustedViewportSize.Y * (0.35 + (0.15 * textIndex));
	float rightPad = fThree - ((adjustedViewportSize.Y / 10) * fTwo);
	float bottomPad = adjustedViewportSize.Y * (0.575 - (0.15 * textIndex));

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

float SPauseScreen::CalculateGrownMarginX(FMargin inMargin)
{
	float sizeX = adjustedViewportSize.X - (inMargin.Left + inMargin.Right);
	float newSizeX = ((sizeX - (extentOfGrowth * sizeX)) / 2) / 2;

	return newSizeX;
}

float SPauseScreen::CalculateGrownMarginY(FMargin inMargin)
{
	float sizeY = adjustedViewportSize.Y - (inMargin.Top + inMargin.Bottom);
	float newSizeY = ((sizeY - (extentOfGrowth * sizeY)) / 2) / 2;

	return newSizeY;
}

FMargin SPauseScreen::GrownMargin(FMargin inMargin)
{
	FMargin newMargin = inMargin;
	float sizeX = adjustedViewportSize.X - (inMargin.Left + inMargin.Right);
	float sizeY = adjustedViewportSize.Y - (inMargin.Top + inMargin.Bottom);
	newMargin.Left += (sizeX - (sizeX * multiplierOfPerimeterExpansion)) / 2;
	newMargin.Top += (sizeY - (sizeY * multiplierOfPerimeterExpansion)) / 2;
	newMargin.Right += (sizeX - (sizeX * multiplierOfPerimeterExpansion)) / 2;
	newMargin.Bottom += (sizeY - (sizeY * multiplierOfPerimeterExpansion)) / 2;

	return newMargin;
}

FMargin SPauseScreen::GrowMargin(FMargin inMargin)
{
	FMargin newMargin = inMargin;
	float sizeX = (adjustedSizeX * sin(37.7 * (growTime - 0.0416))) + adjustedSizeX;
	float sizeY = (adjustedSizeY * sin(37.7 * (growTime - 0.0416))) + adjustedSizeY;
	newMargin.Left += sizeX;
	newMargin.Top += sizeY;
	newMargin.Right += sizeX;
	newMargin.Bottom += sizeY;

	return newMargin;
}

FMargin SPauseScreen::ShrinkMargin(FMargin inMargin, int marginIndex)
{
	FMargin newMargin = inMargin;
	float sizeX = (shrinkingAdjustedMarginSizesX[marginIndex] * sin(37.7 * (shrinkingTimes[marginIndex] - 0.0416))) + shrinkingAdjustedMarginSizesX[marginIndex];
	float sizeY = (shrinkingAdjustedMarginSizesY[marginIndex] * sin(37.7 * (shrinkingTimes[marginIndex] - 0.0416))) + shrinkingAdjustedMarginSizesY[marginIndex];
	newMargin.Left += sizeX;
	newMargin.Top += sizeY;
	newMargin.Right += sizeX;
	newMargin.Bottom += sizeY;

	return newMargin;
}

void SPauseScreen::PlayChordToActiveNote()
{
	for (int a : chordIndexes[correspondingChordsToNotes[activeNoteIndex][FMath::RandRange(0, correspondingChordsToNotes[activeNoteIndex].Num() - 1)]])
	{
		if (a != activeNoteIndex)
		{
			purpleLullabyAudioComponents[a]->Play();
		}
	}
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SPauseScreen::Construct(const FArguments& InArgs)
{
	SetCanTick(true);
	bCanSupportFocus = true;
	currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));

	OwningHUD = InArgs._OwningHUD;
	hoverGrowAudioComponents = InArgs._hoverGrowAudioComponents;
	hoverShrinkAudioComponents = InArgs._hoverShrinkAudioComponents;
	purpleLullabyAudioComponents = InArgs._purpleLullabyAudioComponents;

	GEngine->GameViewport->GetViewportSize(viewportSize);
	int32 X = FGenericPlatformMath::FloorToInt(viewportSize.X);
	int32 Y = FGenericPlatformMath::FloorToInt(viewportSize.Y);
	DPIScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(X, Y));
	adjustedViewportSize = (1 / DPIScale) * viewportSize;

	childrensCornerNotes = { 8, 11, 12, 13, 8, 11, 13, 12, 7, 11, 12, 14, 9, 10, 14, 13, 8, 11, 13, 15, 10, 11, 15, 14, 9, 11, 14, 16, 9, 14, 16, 15, 11, 13, 15, 18, 13, 15, 18, 19, 13, 15, 19, 18, 13, 15, 18, 17, 13, 15, 17, 16, 13, 15, 16, 15, 11, 13, 15, 14, 11, 13, 14, 13, 10, 11, 13, 12, 9, 11, 12, 15, 10, 13, 15, 16, 11, 13, 16, 13, 9, 11, 13, 12, 9, 11, 12, 11, 8, 9, 11, 10, 7, 8, 10, 0, 4, 5, 6, 7, 9, 11, 12, 13, 12, 11, 9, 7, 6, 5, 4, 0, 4, 5, 6, 7, 9, 11, 12, 13, 12, 11, 9, 7, 6, 5, 4, 0, 4, 5, 6, 7, 22, 11, 12, 13, 12, 11, 9, 7, 6, 5, 4, 0, 4, 5, 6, 7, 22, 11, 12, 13, 12, 11, 10, 7, 6, 5, 4 };
	childrensCornerIndex = -1;

	clock = 0;
	deathClock = 0;
	destroyPauseScreen = false;
	spawnPauseScreen = true;

	titleFont = FCoreStyle::Get().GetFontStyle("EmbossedText");
	titleFont.Size = 0.06 * adjustedViewportSize.Y;
	titleText = FText::FromString("Pause Menu");
	subTitleFont = FCoreStyle::Get().GetFontStyle("Roboto");
	subTitleFont.Size = 0.05 * adjustedViewportSize.Y;
	menuFont = FCoreStyle::Get().GetFontStyle("Roboto");
	menuFont.Size = 0.04 * adjustedViewportSize.Y;

	standardOpacity = 1.0;
	standardShadowOffset = 0.003;
	standardBlur = 30;
	multiplierOfPerimeterExpansion = 1.225;
	multiplierOfOffset = 4;
	grownOpacity = 0.6;

	transparentButtonStyle = new FButtonStyle();
	transparentButtonStyle->SetNormalPadding(FMargin());

	textColor = FLinearColor(255, 165, 0, 0);
	shadowColor = FLinearColor(0, 0, 0, 0);

	resumeMargin = CalculateMenuTextPos(0, 4);
	restartMargin = CalculateMenuTextPos(1, 7);
	optionsMargin = CalculateMenuTextPos(2, 7);
	quitToMenuMargin = CalculateMenuTextPos(3, 7);

	resumeText = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(textColor)
		.Font(menuFont)
		.Text(FText::FromString("Play"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * standardShadowOffset, adjustedViewportSize.Y * standardShadowOffset))
		.ShadowColorAndOpacity(shadowColor);

	resumeBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(resumeMargin)
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SPauseScreen::OnResumePressed)
				.OnReleased(this, &SPauseScreen::OnResumeReleased)
				.OnHovered(this, &SPauseScreen::OnResumeHovered)
				.OnUnhovered(this, &SPauseScreen::OnResumeUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					resumeText.ToSharedRef()
				]
		];

	restartText = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(textColor)
		.Font(menuFont)
		.Text(FText::FromString("Restart"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * standardShadowOffset, adjustedViewportSize.Y * standardShadowOffset))
		.ShadowColorAndOpacity(shadowColor);

	restartBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(restartMargin)
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SPauseScreen::OnRestartPressed)
				.OnReleased(this, &SPauseScreen::OnRestartReleased)
				.OnHovered(this, &SPauseScreen::OnRestartHovered)
				.OnUnhovered(this, &SPauseScreen::OnRestartUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					restartText.ToSharedRef()
				]
		];

	optionsText = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(textColor)
		.Font(menuFont)
		.Text(FText::FromString("Options"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * standardShadowOffset, adjustedViewportSize.Y * standardShadowOffset))
		.ShadowColorAndOpacity(shadowColor);

	optionsBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(optionsMargin)
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SPauseScreen::OnOptionsPressed)
				.OnReleased(this, &SPauseScreen::OnOptionsReleased)
				.OnHovered(this, &SPauseScreen::OnOptionsHovered)
				.OnUnhovered(this, &SPauseScreen::OnOptionsUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					optionsText.ToSharedRef()
				]
		];

	quitToMenuText = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(textColor)
		.Font(menuFont)
		.Text(FText::FromString("Quit To Menu"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * standardShadowOffset, adjustedViewportSize.Y * standardShadowOffset))
		.ShadowColorAndOpacity(shadowColor);

	quitToMenuBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(quitToMenuMargin)
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SPauseScreen::OnQuitToMenuPressed)
				.OnReleased(this, &SPauseScreen::OnQuitToMenuReleased)
				.OnHovered(this, &SPauseScreen::OnQuitToMenuHovered)
				.OnUnhovered(this, &SPauseScreen::OnQuitToMenuUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					quitToMenuText.ToSharedRef()
				]
		];


	mainPauseOverlay = SNew(SOverlay);

	titleTextBlock = SNew(STextBlock)
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(textColor)
		.Font(titleFont)
		.Text(titleText)
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * standardShadowOffset, adjustedViewportSize.Y * standardShadowOffset))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 0));

	mainPauseOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateTitlePosition(adjustedViewportSize))
		[
			titleTextBlock.ToSharedRef()
		];

	mainPauseOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			resumeBox.ToSharedRef()
		];

	mainPauseOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			restartBox.ToSharedRef()
		];

	mainPauseOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			optionsBox.ToSharedRef()
		];

	mainPauseOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			quitToMenuBox.ToSharedRef()
		];

	blur = SNew(SBackgroundBlur)
		.BlurStrength(0.0);

	masterOverlay = SNew(SOverlay);
	masterOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			blur.ToSharedRef()
		];

	masterOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			mainPauseOverlay.ToSharedRef()
		];

	ChildSlot
		[
			SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					masterOverlay.ToSharedRef()
				]
		];

}

FReply SPauseScreen::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Q)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "q");
	}

	if (InKeyEvent.GetKey() == EKeys::Tab)
	{
		destroyPauseScreen = true;
		GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "tab");//why isnt this working
	}

	if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		//in the final product the escape key will take the place of the tab key wherever the tab key is used
	}
	GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "anything");

	return FReply::Handled();
}

void SPauseScreen::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	for (int a = 0; a < shrinkingBoxes.Num(); a++)
	{
		shrinkingTimes[a] += InDeltaTime;
		shrinkingMargins[a] = ShrinkMargin(shrinkingMarginsStartingPoints[a], a);
		shrinkingFontSizes[a] = shrinkingFontSizesStartingPoints[a] + ((shrinkingAdjustedFontSizes[a] * sin(37.7 * (shrinkingTimes[a] - 0.0416))) + shrinkingAdjustedFontSizes[a]);
		shrinkingOffset[a] = startingShrinkingOffset[a] + ((adjustedShrinkingOffset[a] * sin(37.7 * (shrinkingTimes[a] - 0.0416))) + adjustedShrinkingOffset[a]);
		shrinkingOpacities[a] = startingShrinkingOpacities[a] + ((adjustedShrinkingOpacities[a] * sin(37.7 * (shrinkingTimes[a] - 0.0416))) + adjustedShrinkingOpacities[a]);
		shrinkingLinearColors[a].A = shrinkingOpacities[a];

		shrinkingBoxes[a]->SetPadding(shrinkingMargins[a]);
		shrinkingTexts[a].Size = shrinkingFontSizes[a];
		shrinkingTextBlocks[a]->SetFont(shrinkingTexts[a]);
		shrinkingTextBlocks[a]->SetShadowOffset(FVector2D(shrinkingOffset[a] * adjustedViewportSize.Y, shrinkingOffset[a] * adjustedViewportSize.Y));
		shrinkingTextBlocks[a]->SetShadowColorAndOpacity(shrinkingLinearColors[a]);

		if (shrinkingTimes[a] + InDeltaTime >= 0.083)
		{
			shrinkingBoxes[a]->SetPadding(completedMargins[a]);
			shrinkingTextBlocks[a]->SetFont(completedFonts[a]);
			shrinkingTextBlocks[a]->SetShadowOffset(FVector2D(completedOffsets[a] * adjustedViewportSize.Y, completedOffsets[a] * adjustedViewportSize.Y));

			shrinkingOpacities.RemoveAt(a);
			shrinkingLinearColors.RemoveAt(a);
			startingShrinkingOpacities.RemoveAt(a);
			adjustedShrinkingOpacities.RemoveAt(a);
			shrinkingOffset.RemoveAt(a);
			startingShrinkingOffset.RemoveAt(a);
			adjustedShrinkingOffset.RemoveAt(a);
			shrinkingBoxes.RemoveAt(a);
			shrinkingTextBlocks.RemoveAt(a);
			shrinkingTexts.RemoveAt(a);
			shrinkingMargins.RemoveAt(a);
			shrinkingMarginsStartingPoints.RemoveAt(a);
			shrinkingAdjustedMarginSizesX.RemoveAt(a);
			shrinkingAdjustedMarginSizesY.RemoveAt(a);
			shrinkingFontSizes.RemoveAt(a);
			shrinkingFontSizesStartingPoints.RemoveAt(a);
			shrinkingAdjustedFontSizes.RemoveAt(a);
			shrinkingTimes.RemoveAt(a);
			completedMargins.RemoveAt(a);
			completedFonts.RemoveAt(a);
			completedOffsets.RemoveAt(a);

			a -= 1;
		}
	}

	if (growingBox.Num() > 0)
	{
		growTime += InDeltaTime;
		growingMargin = GrowMargin(startingMargin);
		growingFontSize = startingFontSize + ((adjustedStartingFontSize * sin(37.7 * (growTime - 0.0416))) + adjustedStartingFontSize);
		growingOffset = startingShadowOffset + ((adjustedGrowingOffset * sin(37.7 * (growTime - 0.0416))) + adjustedGrowingOffset);
		growingOpacity = startingOpacity + ((adjustedGrowingOpacity * sin(37.7 * (growTime - 0.0416))) + adjustedGrowingOpacity);
		growingLinearColor.A = growingOpacity;

		growingBox[0]->SetPadding(growingMargin);
		growingFont.Size = growingFontSize;
		growingTextBlock->SetFont(growingFont);
		growingTextBlock->SetShadowOffset(FVector2D(growingOffset * adjustedViewportSize.Y, growingOffset * adjustedViewportSize.Y));
		growingTextBlock->SetShadowColorAndOpacity(growingLinearColor);

		if (growTime + InDeltaTime >= 0.083)
		{
			grownBox.Add(growingBox[0]);

			growingBox.RemoveAt(0);
		}
	}

	if (spawnPauseScreen)
	{
		clock += InDeltaTime;

		blur->SetBlurStrength(((standardBlur / 2) * sin(37.7 * (clock - 0.04166))) + (standardBlur / 2));

		textColor = FLinearColor(255, 165, 0, (0.5 * sin(37.7 * (clock - 0.04166))) + 0.5);
		shadowColor = FLinearColor(0, 0, 0, (0.5 * sin(37.7 * (clock - 0.04166))) + 0.5);

		titleTextBlock->SetColorAndOpacity(textColor);
		titleTextBlock->SetShadowColorAndOpacity(shadowColor);
		resumeText->SetColorAndOpacity(textColor);
		resumeText->SetShadowColorAndOpacity(shadowColor);
		restartText->SetColorAndOpacity(textColor);
		restartText->SetShadowColorAndOpacity(shadowColor);
		optionsText->SetColorAndOpacity(textColor);
		optionsText->SetShadowColorAndOpacity(shadowColor);
		quitToMenuText->SetColorAndOpacity(textColor);
		quitToMenuText->SetShadowColorAndOpacity(shadowColor);

		if (clock >= 0.0833)
		{
			spawnPauseScreen = false;
		}
	}

	if (destroyPauseScreen)
	{
		deathClock += InDeltaTime;

		blur->SetBlurStrength(standardBlur - (((standardBlur / 2) * sin(37.7 * (clock - 0.04166))) + (standardBlur / 2)));

		newOpacity = 1 - ((0.5 * sin(37.7 * (deathClock - 0.04166))) + 0.5);

		textColor = FLinearColor(255, 165, 0, newOpacity);
		shadowColor = FLinearColor(0, 0, 0, newOpacity);

		titleTextBlock->SetColorAndOpacity(textColor);
		titleTextBlock->SetShadowColorAndOpacity(shadowColor);
		resumeText->SetColorAndOpacity(textColor);
		resumeText->SetShadowColorAndOpacity(shadowColor);
		restartText->SetColorAndOpacity(textColor);
		restartText->SetShadowColorAndOpacity(shadowColor);
		optionsText->SetColorAndOpacity(textColor);
		optionsText->SetShadowColorAndOpacity(shadowColor);
		quitToMenuText->SetColorAndOpacity(textColor);
		quitToMenuText->SetShadowColorAndOpacity(shadowColor);

		if (deathClock + InDeltaTime >= 0.0833)
		{
			OwningHUD->DestroyPauseScreen();
		}
	}
}

void SPauseScreen::OnResumeHovered()
{
	if (!destroyPauseScreen)
	{
		if (shrinkingBoxes.Find(resumeBox) + 1)
		{
			indexOfShrinkingSubject = shrinkingBoxes.Find(resumeBox);
			extentOfGrowth = menuFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size; //am I going to need multiple extentOfGrowths? if it is only implimented in growing and not in shrinking then no: just the one should suffice
			growingOffset = shrinkingOffset[indexOfShrinkingSubject];
			growingMargin = shrinkingMargins[indexOfShrinkingSubject];
			growingFont = shrinkingTexts[indexOfShrinkingSubject];
			growingLinearColor = shrinkingLinearColors[indexOfShrinkingSubject];
			growingOpacity = shrinkingOpacities[indexOfShrinkingSubject];

			hoverShrinkAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();

			shrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			shrinkingLinearColors.RemoveAt(indexOfShrinkingSubject);
			startingShrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			adjustedShrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			shrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			startingShrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			adjustedShrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			shrinkingBoxes.RemoveAt(indexOfShrinkingSubject);
			shrinkingTextBlocks.RemoveAt(indexOfShrinkingSubject);
			shrinkingTexts.RemoveAt(indexOfShrinkingSubject);
			shrinkingMargins.RemoveAt(indexOfShrinkingSubject);
			shrinkingMarginsStartingPoints.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedMarginSizesX.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedMarginSizesY.RemoveAt(indexOfShrinkingSubject);
			shrinkingFontSizes.RemoveAt(indexOfShrinkingSubject);
			shrinkingFontSizesStartingPoints.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedFontSizes.RemoveAt(indexOfShrinkingSubject);
			shrinkingTimes.RemoveAt(indexOfShrinkingSubject);
			completedMargins.RemoveAt(indexOfShrinkingSubject);
			completedFonts.RemoveAt(indexOfShrinkingSubject);
			completedOffsets.RemoveAt(indexOfShrinkingSubject);
		}
		else
		{
			extentOfGrowth = multiplierOfPerimeterExpansion;

			growingFont = menuFont;
			growingOffset = standardShadowOffset;
			growingMargin = resumeMargin;
			growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
			growingOpacity = standardOpacity;
		}

		startingOpacity = growingOpacity;
		adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
		startingMargin = growingMargin;
		startingFontSize = menuFont.Size;
		startingShadowOffset = growingOffset;
		adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
		adjustedSizeX = CalculateGrownMarginX(startingMargin);
		adjustedSizeY = CalculateGrownMarginY(startingMargin);
		adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
		growingBox.Add(resumeBox);
		growingTextBlock = resumeText;
		growTime = 0;

		childrensCornerIndex = (childrensCornerIndex + 1) % 159;
		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
	}
}
void SPauseScreen::OnResumeUnHovered()
{
	if (!destroyPauseScreen)
	{
		if (clicked)
		{
			clicked = false;
		}
		else
		{
			if (growingBox.Num() > 0)
			{
				shrinkingBoxes.Add(growingBox[0]);

				growingBox.RemoveAt(0);
			}
			else
			{
				shrinkingBoxes.Add(grownBox[0]);
				grownBox.RemoveAt(0);

				growingMargin = GrownMargin(resumeMargin);
				growingFont.Size = menuFont.Size * multiplierOfPerimeterExpansion;
				growingOffset = standardShadowOffset * multiplierOfOffset;
				growingLinearColor = FLinearColor(0, 0, 0, grownOpacity);
				growingOpacity = grownOpacity;

				hoverShrinkAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
			}

			shrinkingOpacities.Add(growingOpacity);
			shrinkingLinearColors.Add(growingLinearColor);
			startingShrinkingOpacities.Add(growingOpacity);
			adjustedShrinkingOpacities.Add((1 - growingOpacity) / 2);
			shrinkingOffset.Add(growingOffset);
			startingShrinkingOffset.Add(growingOffset);
			adjustedShrinkingOffset.Add((0.003 - growingOffset) / 2);
			shrinkingTextBlocks.Add(growingTextBlock);
			shrinkingTexts.Add(growingFont);
			shrinkingMargins.Add(growingMargin);
			shrinkingMarginsStartingPoints.Add(growingMargin);
			shrinkingAdjustedMarginSizesX.Add((resumeMargin - growingMargin).Left / 2);
			shrinkingAdjustedMarginSizesY.Add((resumeMargin - growingMargin).Top / 2);
			shrinkingFontSizes.Add(growingFontSize);
			shrinkingFontSizesStartingPoints.Add(growingFontSize);
			shrinkingAdjustedFontSizes.Add((menuFont.Size - growingFont.Size) / 2);
			shrinkingTimes.Add(0);
			completedMargins.Add(resumeMargin);
			completedFonts.Add(menuFont);
			completedOffsets.Add(standardShadowOffset);

			hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
		}
	}
}
void SPauseScreen::OnResumePressed()
{
	if (!destroyPauseScreen)
	{
		activeNoteIndex = FMath::RandRange(0, 7);
		purpleLullabyAudioComponents[activeNoteIndex]->Play();

		resumeText->SetColorAndOpacity(FColor::White);
	}
}
void SPauseScreen::OnResumeReleased()
{
	if (!destroyPauseScreen)
	{
		destroyPauseScreen = true;

		PlayChordToActiveNote();

		resumeText->SetColorAndOpacity(FColor::Orange);
		resumeBox->SetPadding(resumeMargin);
		resumeText->SetFont(menuFont);
		resumeText->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
		resumeText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

		if (growingBox.Num() > 0)
		{
			growingBox.RemoveAt(0);
			clicked = true;
		}
		else if (grownBox.Num() > 0)
		{
			grownBox.RemoveAt(0);
			clicked = true;
		}
		else if (shrinkingBoxes.Find(resumeBox) + 1)
		{
			indexOfShrinkingSubject = shrinkingBoxes.Find(resumeBox);

			shrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			shrinkingLinearColors.RemoveAt(indexOfShrinkingSubject);
			startingShrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			adjustedShrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			shrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			startingShrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			adjustedShrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			shrinkingBoxes.RemoveAt(indexOfShrinkingSubject);
			shrinkingTextBlocks.RemoveAt(indexOfShrinkingSubject);
			shrinkingTexts.RemoveAt(indexOfShrinkingSubject);
			shrinkingMargins.RemoveAt(indexOfShrinkingSubject);
			shrinkingMarginsStartingPoints.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedMarginSizesX.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedMarginSizesY.RemoveAt(indexOfShrinkingSubject);
			shrinkingFontSizes.RemoveAt(indexOfShrinkingSubject);
			shrinkingFontSizesStartingPoints.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedFontSizes.RemoveAt(indexOfShrinkingSubject);
			shrinkingTimes.RemoveAt(indexOfShrinkingSubject);
			completedMargins.RemoveAt(indexOfShrinkingSubject);
			completedFonts.RemoveAt(indexOfShrinkingSubject);
			completedOffsets.RemoveAt(indexOfShrinkingSubject);
		}
	}
}

void SPauseScreen::OnRestartHovered()
{
	if (!destroyPauseScreen)
	{
		if (shrinkingBoxes.Find(restartBox) + 1)
		{
			indexOfShrinkingSubject = shrinkingBoxes.Find(restartBox);
			extentOfGrowth = menuFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size; //am I going to need multiple extentOfGrowths? if it is only implimented in growing and not in shrinking then no: just the one should suffice
			growingOffset = shrinkingOffset[indexOfShrinkingSubject];
			growingMargin = shrinkingMargins[indexOfShrinkingSubject];
			growingFont = shrinkingTexts[indexOfShrinkingSubject];
			growingLinearColor = shrinkingLinearColors[indexOfShrinkingSubject];
			growingOpacity = shrinkingOpacities[indexOfShrinkingSubject];

			hoverShrinkAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();

			shrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			shrinkingLinearColors.RemoveAt(indexOfShrinkingSubject);
			startingShrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			adjustedShrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			shrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			startingShrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			adjustedShrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			shrinkingBoxes.RemoveAt(indexOfShrinkingSubject);
			shrinkingTextBlocks.RemoveAt(indexOfShrinkingSubject);
			shrinkingTexts.RemoveAt(indexOfShrinkingSubject);
			shrinkingMargins.RemoveAt(indexOfShrinkingSubject);
			shrinkingMarginsStartingPoints.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedMarginSizesX.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedMarginSizesY.RemoveAt(indexOfShrinkingSubject);
			shrinkingFontSizes.RemoveAt(indexOfShrinkingSubject);
			shrinkingFontSizesStartingPoints.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedFontSizes.RemoveAt(indexOfShrinkingSubject);
			shrinkingTimes.RemoveAt(indexOfShrinkingSubject);
			completedMargins.RemoveAt(indexOfShrinkingSubject);
			completedFonts.RemoveAt(indexOfShrinkingSubject);
			completedOffsets.RemoveAt(indexOfShrinkingSubject);
		}
		else
		{
			extentOfGrowth = multiplierOfPerimeterExpansion;

			growingFont = menuFont;
			growingOffset = standardShadowOffset;
			growingMargin = restartMargin;
			growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
			growingOpacity = standardOpacity;
		}

		startingOpacity = growingOpacity;
		adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
		startingMargin = growingMargin;
		startingFontSize = menuFont.Size;
		startingShadowOffset = growingOffset;
		adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
		adjustedSizeX = CalculateGrownMarginX(startingMargin);
		adjustedSizeY = CalculateGrownMarginY(startingMargin);
		adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
		growingBox.Add(restartBox);
		growingTextBlock = restartText;
		growTime = 0;

		childrensCornerIndex = (childrensCornerIndex + 1) % 159;
		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
	}
}
void SPauseScreen::OnRestartUnHovered()
{
	if (!destroyPauseScreen)
	{
		if (clicked)
		{
			clicked = false;
		}
		else
		{
			if (growingBox.Num() > 0)
			{
				shrinkingBoxes.Add(growingBox[0]);

				growingBox.RemoveAt(0);
			}
			else
			{
				shrinkingBoxes.Add(grownBox[0]);
				grownBox.RemoveAt(0);

				growingMargin = GrownMargin(restartMargin);
				growingFont.Size = menuFont.Size * multiplierOfPerimeterExpansion;
				growingOffset = standardShadowOffset * multiplierOfOffset;
				growingLinearColor = FLinearColor(0, 0, 0, grownOpacity);
				growingOpacity = grownOpacity;

				hoverShrinkAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
			}

			shrinkingOpacities.Add(growingOpacity);
			shrinkingLinearColors.Add(growingLinearColor);
			startingShrinkingOpacities.Add(growingOpacity);
			adjustedShrinkingOpacities.Add((1 - growingOpacity) / 2);
			shrinkingOffset.Add(growingOffset);
			startingShrinkingOffset.Add(growingOffset);
			adjustedShrinkingOffset.Add((0.003 - growingOffset) / 2);
			shrinkingTextBlocks.Add(growingTextBlock);
			shrinkingTexts.Add(growingFont);
			shrinkingMargins.Add(growingMargin);
			shrinkingMarginsStartingPoints.Add(growingMargin);
			shrinkingAdjustedMarginSizesX.Add((restartMargin - growingMargin).Left / 2);
			shrinkingAdjustedMarginSizesY.Add((restartMargin - growingMargin).Top / 2);
			shrinkingFontSizes.Add(growingFontSize);
			shrinkingFontSizesStartingPoints.Add(growingFontSize);
			shrinkingAdjustedFontSizes.Add((menuFont.Size - growingFont.Size) / 2);
			shrinkingTimes.Add(0);
			completedMargins.Add(restartMargin);
			completedFonts.Add(menuFont);
			completedOffsets.Add(standardShadowOffset);

			hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
		}
	}
}
void SPauseScreen::OnRestartPressed()
{
	if (!destroyPauseScreen)
	{
		activeNoteIndex = FMath::RandRange(0, 7);
		purpleLullabyAudioComponents[activeNoteIndex]->Play();

		restartText->SetColorAndOpacity(FColor::White);
	}
}
void SPauseScreen::OnRestartReleased()
{
	if (!destroyPauseScreen)
	{
		destroyPauseScreen = true;
		OwningHUD->DisplayCurtains(OwningHUD->numberOfHoles);

		PlayChordToActiveNote();

		restartText->SetColorAndOpacity(FColor::Orange);
		restartBox->SetPadding(restartMargin);
		restartText->SetFont(menuFont);
		restartText->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
		restartText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

		if (growingBox.Num() > 0)
		{
			growingBox.RemoveAt(0);
			clicked = true;
		}
		else if (grownBox.Num() > 0)
		{
			grownBox.RemoveAt(0);
			clicked = true;
		}
		else if (shrinkingBoxes.Find(restartBox) + 1)
		{
			indexOfShrinkingSubject = shrinkingBoxes.Find(restartBox);

			shrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			shrinkingLinearColors.RemoveAt(indexOfShrinkingSubject);
			startingShrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			adjustedShrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			shrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			startingShrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			adjustedShrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			shrinkingBoxes.RemoveAt(indexOfShrinkingSubject);
			shrinkingTextBlocks.RemoveAt(indexOfShrinkingSubject);
			shrinkingTexts.RemoveAt(indexOfShrinkingSubject);
			shrinkingMargins.RemoveAt(indexOfShrinkingSubject);
			shrinkingMarginsStartingPoints.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedMarginSizesX.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedMarginSizesY.RemoveAt(indexOfShrinkingSubject);
			shrinkingFontSizes.RemoveAt(indexOfShrinkingSubject);
			shrinkingFontSizesStartingPoints.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedFontSizes.RemoveAt(indexOfShrinkingSubject);
			shrinkingTimes.RemoveAt(indexOfShrinkingSubject);
			completedMargins.RemoveAt(indexOfShrinkingSubject);
			completedFonts.RemoveAt(indexOfShrinkingSubject);
			completedOffsets.RemoveAt(indexOfShrinkingSubject);
		}
	}
}

void SPauseScreen::OnOptionsHovered()
{
	if (!destroyPauseScreen)
	{
		if (shrinkingBoxes.Find(optionsBox) + 1)
		{
			indexOfShrinkingSubject = shrinkingBoxes.Find(optionsBox);
			extentOfGrowth = menuFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size; //am I going to need multiple extentOfGrowths? if it is only implimented in growing and not in shrinking then no: just the one should suffice
			growingOffset = shrinkingOffset[indexOfShrinkingSubject];
			growingMargin = shrinkingMargins[indexOfShrinkingSubject];
			growingFont = shrinkingTexts[indexOfShrinkingSubject];
			growingLinearColor = shrinkingLinearColors[indexOfShrinkingSubject];
			growingOpacity = shrinkingOpacities[indexOfShrinkingSubject];

			hoverShrinkAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();

			shrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			shrinkingLinearColors.RemoveAt(indexOfShrinkingSubject);
			startingShrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			adjustedShrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			shrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			startingShrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			adjustedShrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			shrinkingBoxes.RemoveAt(indexOfShrinkingSubject);
			shrinkingTextBlocks.RemoveAt(indexOfShrinkingSubject);
			shrinkingTexts.RemoveAt(indexOfShrinkingSubject);
			shrinkingMargins.RemoveAt(indexOfShrinkingSubject);
			shrinkingMarginsStartingPoints.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedMarginSizesX.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedMarginSizesY.RemoveAt(indexOfShrinkingSubject);
			shrinkingFontSizes.RemoveAt(indexOfShrinkingSubject);
			shrinkingFontSizesStartingPoints.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedFontSizes.RemoveAt(indexOfShrinkingSubject);
			shrinkingTimes.RemoveAt(indexOfShrinkingSubject);
			completedMargins.RemoveAt(indexOfShrinkingSubject);
			completedFonts.RemoveAt(indexOfShrinkingSubject);
			completedOffsets.RemoveAt(indexOfShrinkingSubject);
		}
		else
		{
			extentOfGrowth = multiplierOfPerimeterExpansion;

			growingFont = menuFont;
			growingOffset = standardShadowOffset;
			growingMargin = optionsMargin;
			growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
			growingOpacity = standardOpacity;
		}

		startingOpacity = growingOpacity;
		adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
		startingMargin = growingMargin;
		startingFontSize = menuFont.Size;
		startingShadowOffset = growingOffset;
		adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
		adjustedSizeX = CalculateGrownMarginX(startingMargin);
		adjustedSizeY = CalculateGrownMarginY(startingMargin);
		adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
		growingBox.Add(optionsBox);
		growingTextBlock = optionsText;
		growTime = 0;

		childrensCornerIndex = (childrensCornerIndex + 1) % 159;
		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
	}
}
void SPauseScreen::OnOptionsUnHovered()
{
	if (!destroyPauseScreen)
	{
		if (clicked)
		{
			clicked = false;
		}
		else
		{
			if (growingBox.Num() > 0)
			{
				shrinkingBoxes.Add(growingBox[0]);

				growingBox.RemoveAt(0);
			}
			else
			{
				shrinkingBoxes.Add(grownBox[0]);
				grownBox.RemoveAt(0);

				growingMargin = GrownMargin(optionsMargin);
				growingFont.Size = menuFont.Size * multiplierOfPerimeterExpansion;
				growingOffset = standardShadowOffset * multiplierOfOffset;
				growingLinearColor = FLinearColor(0, 0, 0, grownOpacity);
				growingOpacity = grownOpacity;

				hoverShrinkAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
			}

			shrinkingOpacities.Add(growingOpacity);
			shrinkingLinearColors.Add(growingLinearColor);
			startingShrinkingOpacities.Add(growingOpacity);
			adjustedShrinkingOpacities.Add((1 - growingOpacity) / 2);
			shrinkingOffset.Add(growingOffset);
			startingShrinkingOffset.Add(growingOffset);
			adjustedShrinkingOffset.Add((0.003 - growingOffset) / 2);
			shrinkingTextBlocks.Add(growingTextBlock);
			shrinkingTexts.Add(growingFont);
			shrinkingMargins.Add(growingMargin);
			shrinkingMarginsStartingPoints.Add(growingMargin);
			shrinkingAdjustedMarginSizesX.Add((optionsMargin - growingMargin).Left / 2);
			shrinkingAdjustedMarginSizesY.Add((optionsMargin - growingMargin).Top / 2);
			shrinkingFontSizes.Add(growingFontSize);
			shrinkingFontSizesStartingPoints.Add(growingFontSize);
			shrinkingAdjustedFontSizes.Add((menuFont.Size - growingFont.Size) / 2);
			shrinkingTimes.Add(0);
			completedMargins.Add(optionsMargin);
			completedFonts.Add(menuFont);
			completedOffsets.Add(standardShadowOffset);

			hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
		}
	}
}
void SPauseScreen::OnOptionsPressed()
{
	if (!destroyPauseScreen)
	{
		activeNoteIndex = FMath::RandRange(0, 7);
		purpleLullabyAudioComponents[activeNoteIndex]->Play();

		optionsText->SetColorAndOpacity(FColor::White);
	}
}
void SPauseScreen::OnOptionsReleased()
{
	if (!destroyPauseScreen)
	{
		PlayChordToActiveNote();

		optionsText->SetColorAndOpacity(FColor::Orange);
		optionsBox->SetPadding(optionsMargin);
		optionsText->SetFont(menuFont);
		optionsText->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
		optionsText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

		if (growingBox.Num() > 0)
		{
			growingBox.RemoveAt(0);
			clicked = true;
		}
		else if (grownBox.Num() > 0)
		{
			grownBox.RemoveAt(0);
			clicked = true;
		}
		else if (shrinkingBoxes.Find(optionsBox) + 1)
		{
			indexOfShrinkingSubject = shrinkingBoxes.Find(optionsBox);

			shrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			shrinkingLinearColors.RemoveAt(indexOfShrinkingSubject);
			startingShrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			adjustedShrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			shrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			startingShrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			adjustedShrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			shrinkingBoxes.RemoveAt(indexOfShrinkingSubject);
			shrinkingTextBlocks.RemoveAt(indexOfShrinkingSubject);
			shrinkingTexts.RemoveAt(indexOfShrinkingSubject);
			shrinkingMargins.RemoveAt(indexOfShrinkingSubject);
			shrinkingMarginsStartingPoints.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedMarginSizesX.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedMarginSizesY.RemoveAt(indexOfShrinkingSubject);
			shrinkingFontSizes.RemoveAt(indexOfShrinkingSubject);
			shrinkingFontSizesStartingPoints.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedFontSizes.RemoveAt(indexOfShrinkingSubject);
			shrinkingTimes.RemoveAt(indexOfShrinkingSubject);
			completedMargins.RemoveAt(indexOfShrinkingSubject);
			completedFonts.RemoveAt(indexOfShrinkingSubject);
			completedOffsets.RemoveAt(indexOfShrinkingSubject);
		}
	}

	masterOverlay->RemoveSlot(1);
	OwningHUD->DisplayOptionsMenu(true);
}

void SPauseScreen::OnQuitToMenuHovered()
{
	if (!destroyPauseScreen)
	{
		if (shrinkingBoxes.Find(quitToMenuBox) + 1)
		{
			indexOfShrinkingSubject = shrinkingBoxes.Find(quitToMenuBox);
			extentOfGrowth = menuFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size; //am I going to need multiple extentOfGrowths? if it is only implimented in growing and not in shrinking then no: just the one should suffice
			growingOffset = shrinkingOffset[indexOfShrinkingSubject];
			growingMargin = shrinkingMargins[indexOfShrinkingSubject];
			growingFont = shrinkingTexts[indexOfShrinkingSubject];
			growingLinearColor = shrinkingLinearColors[indexOfShrinkingSubject];
			growingOpacity = shrinkingOpacities[indexOfShrinkingSubject];

			hoverShrinkAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();

			shrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			shrinkingLinearColors.RemoveAt(indexOfShrinkingSubject);
			startingShrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			adjustedShrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			shrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			startingShrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			adjustedShrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			shrinkingBoxes.RemoveAt(indexOfShrinkingSubject);
			shrinkingTextBlocks.RemoveAt(indexOfShrinkingSubject);
			shrinkingTexts.RemoveAt(indexOfShrinkingSubject);
			shrinkingMargins.RemoveAt(indexOfShrinkingSubject);
			shrinkingMarginsStartingPoints.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedMarginSizesX.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedMarginSizesY.RemoveAt(indexOfShrinkingSubject);
			shrinkingFontSizes.RemoveAt(indexOfShrinkingSubject);
			shrinkingFontSizesStartingPoints.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedFontSizes.RemoveAt(indexOfShrinkingSubject);
			shrinkingTimes.RemoveAt(indexOfShrinkingSubject);
			completedMargins.RemoveAt(indexOfShrinkingSubject);
			completedFonts.RemoveAt(indexOfShrinkingSubject);
			completedOffsets.RemoveAt(indexOfShrinkingSubject);
		}
		else
		{
			extentOfGrowth = multiplierOfPerimeterExpansion;

			growingFont = menuFont;
			growingOffset = standardShadowOffset;
			growingMargin = quitToMenuMargin;
			growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
			growingOpacity = standardOpacity;
		}

		startingOpacity = growingOpacity;
		adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
		startingMargin = growingMargin;
		startingFontSize = menuFont.Size;
		startingShadowOffset = growingOffset;
		adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
		adjustedSizeX = CalculateGrownMarginX(startingMargin);
		adjustedSizeY = CalculateGrownMarginY(startingMargin);
		adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
		growingBox.Add(quitToMenuBox);
		growingTextBlock = quitToMenuText;
		growTime = 0;

		childrensCornerIndex = (childrensCornerIndex + 1) % 159;
		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
	}
}
void SPauseScreen::OnQuitToMenuUnHovered()
{
	if (!destroyPauseScreen)
	{
		if (clicked)
		{
			clicked = false;
		}
		else
		{
			if (growingBox.Num() > 0)
			{
				shrinkingBoxes.Add(growingBox[0]);

				growingBox.RemoveAt(0);
			}
			else
			{
				shrinkingBoxes.Add(grownBox[0]);
				grownBox.RemoveAt(0);

				growingMargin = GrownMargin(quitToMenuMargin);
				growingFont.Size = menuFont.Size * multiplierOfPerimeterExpansion;
				growingOffset = standardShadowOffset * multiplierOfOffset;
				growingLinearColor = FLinearColor(0, 0, 0, grownOpacity);
				growingOpacity = grownOpacity;

				hoverShrinkAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
			}

			shrinkingOpacities.Add(growingOpacity);
			shrinkingLinearColors.Add(growingLinearColor);
			startingShrinkingOpacities.Add(growingOpacity);
			adjustedShrinkingOpacities.Add((1 - growingOpacity) / 2);
			shrinkingOffset.Add(growingOffset);
			startingShrinkingOffset.Add(growingOffset);
			adjustedShrinkingOffset.Add((0.003 - growingOffset) / 2);
			shrinkingTextBlocks.Add(growingTextBlock);
			shrinkingTexts.Add(growingFont);
			shrinkingMargins.Add(growingMargin);
			shrinkingMarginsStartingPoints.Add(growingMargin);
			shrinkingAdjustedMarginSizesX.Add((quitToMenuMargin - growingMargin).Left / 2);
			shrinkingAdjustedMarginSizesY.Add((quitToMenuMargin - growingMargin).Top / 2);
			shrinkingFontSizes.Add(growingFontSize);
			shrinkingFontSizesStartingPoints.Add(growingFontSize);
			shrinkingAdjustedFontSizes.Add((menuFont.Size - growingFont.Size) / 2);
			shrinkingTimes.Add(0);
			completedMargins.Add(quitToMenuMargin);
			completedFonts.Add(menuFont);
			completedOffsets.Add(standardShadowOffset);

			hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
		}
	}
}
void SPauseScreen::OnQuitToMenuPressed()
{
	if (!destroyPauseScreen)
	{
		activeNoteIndex = FMath::RandRange(0, 7);
		purpleLullabyAudioComponents[activeNoteIndex]->Play();

		quitToMenuText->SetColorAndOpacity(FColor::White);
	}
}
void SPauseScreen::OnQuitToMenuReleased()
{
	if (!destroyPauseScreen)
	{
		destroyPauseScreen = true;
		OwningHUD->songPlaying = false;
		OwningHUD->DisplayCurtains(0, false, false);

		PlayChordToActiveNote();

		quitToMenuText->SetColorAndOpacity(textColor);
		quitToMenuBox->SetPadding(quitToMenuMargin);
		quitToMenuText->SetFont(menuFont);
		quitToMenuText->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
		quitToMenuText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

		if (growingBox.Num() > 0)
		{
			growingBox.RemoveAt(0);
			clicked = true;
		}
		else if (grownBox.Num() > 0)
		{
			grownBox.RemoveAt(0);
			clicked = true;
		}
		else if (shrinkingBoxes.Find(quitToMenuBox) + 1)
		{
			indexOfShrinkingSubject = shrinkingBoxes.Find(quitToMenuBox);

			shrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			shrinkingLinearColors.RemoveAt(indexOfShrinkingSubject);
			startingShrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			adjustedShrinkingOpacities.RemoveAt(indexOfShrinkingSubject);
			shrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			startingShrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			adjustedShrinkingOffset.RemoveAt(indexOfShrinkingSubject);
			shrinkingBoxes.RemoveAt(indexOfShrinkingSubject);
			shrinkingTextBlocks.RemoveAt(indexOfShrinkingSubject);
			shrinkingTexts.RemoveAt(indexOfShrinkingSubject);
			shrinkingMargins.RemoveAt(indexOfShrinkingSubject);
			shrinkingMarginsStartingPoints.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedMarginSizesX.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedMarginSizesY.RemoveAt(indexOfShrinkingSubject);
			shrinkingFontSizes.RemoveAt(indexOfShrinkingSubject);
			shrinkingFontSizesStartingPoints.RemoveAt(indexOfShrinkingSubject);
			shrinkingAdjustedFontSizes.RemoveAt(indexOfShrinkingSubject);
			shrinkingTimes.RemoveAt(indexOfShrinkingSubject);
			completedMargins.RemoveAt(indexOfShrinkingSubject);
			completedFonts.RemoveAt(indexOfShrinkingSubject);
			completedOffsets.RemoveAt(indexOfShrinkingSubject);
		}
	}
}

void SPauseScreen::ReturnToLanding()
{
	masterOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			mainPauseOverlay.ToSharedRef()
		];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

