#include "SSArcadeModeTitleScreen.h"
#include "SlateOptMacros.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"

FMargin SSArcadeModeTitleScreen::CalculateTitlePosition(FVector2D funcViewportSize)
{//your sub titles will use this same positioning but the a different text style
	float leftPad = funcViewportSize.X * 0.1;
	float topPad = funcViewportSize.Y * 0.1;
	float rightPad = funcViewportSize.X * 0.1;
	float bottomPad = funcViewportSize.Y * 0.75;

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

FMargin SSArcadeModeTitleScreen::CalculateMenuTextPos(int textIndex, int numberOfLetters)
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

FMargin SSArcadeModeTitleScreen::CalculateHighscorePos(int textIndex, int numberOfLetters)
{//since the buttons expand from the center they must be aligned from the center. this means for them to line up vertically the left and right pads need to be calculated so their centers are always equivalent
	float fOne = ((adjustedViewportSize.X - adjustedViewportSize.Y) / 2) + (adjustedViewportSize.Y * 0.3);
	float fThree = ((adjustedViewportSize.X - adjustedViewportSize.Y) / 2) + ((adjustedViewportSize.Y / 10) * 5);
	float fTwo = FMath::DivideAndRoundUp(numberOfLetters, 5);
	float leftPad = fOne - ((adjustedViewportSize.Y / 10) * fTwo);
	float topPad = adjustedViewportSize.Y * (0.35 + (0.1 * textIndex));
	float rightPad = adjustedViewportSize.X - (leftPad + ((adjustedViewportSize.Y / 5) * fTwo));
	float bottomPad = adjustedViewportSize.Y * (0.575 - (0.1 * textIndex));

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

FMargin SSArcadeModeTitleScreen::CalculateLastGamePos(int textIndex, int numberOfLetters)
{//since the buttons expand from the center they must be aligned from the center. this means for them to line up vertically the left and right pads need to be calculated so their centers are always equivalent
	float fOne = ((adjustedViewportSize.X - adjustedViewportSize.Y) / 2) + (adjustedViewportSize.Y * 0.7);
	float fThree = ((adjustedViewportSize.X - adjustedViewportSize.Y) / 2) + ((adjustedViewportSize.Y / 10) * 5);
	float fTwo = FMath::DivideAndRoundUp(numberOfLetters, 5);
	float leftPad = fOne - ((adjustedViewportSize.Y / 10) * fTwo);
	float topPad = adjustedViewportSize.Y * (0.35 + (0.1 * textIndex));
	float rightPad = adjustedViewportSize.X - (leftPad + ((adjustedViewportSize.Y / 5) * fTwo));
	float bottomPad = adjustedViewportSize.Y * (0.575 - (0.1 * textIndex));

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

FMargin CalculateBackgroundPositions(FVector2D adjustedViewportSize, int index)
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

FMargin CalculateBackButtonPosition(FVector2D viewportSize)
{
	float leftPad = viewportSize.X * 0.1;
	float topPad = viewportSize.Y * 0.75;
	float rightPad = viewportSize.X * 0.75;
	float bottomPad = viewportSize.Y * 0.175;

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

FMargin CalculateLevelSelectionButtonsPositions(FVector2D adjustedViewportSize, int index)
{
	float viewportX = adjustedViewportSize.X;
	float viewportY = adjustedViewportSize.Y;
	float fTwo = (viewportY - (viewportY / 5)) / 8;
	float fOne = ((viewportX - viewportY) / 2) + (viewportY / 10);
	float leftPad = fOne + (fTwo * ((index % 4) * 2));
	float topPad = (viewportY / 12) * ((FMath::DivideAndRoundDown(index, 4) + 2) * 2);
	float rightPad = fOne + (fTwo * (((4 - (index % 4)) * 2) - 1));
	float bottomPad = viewportY - (viewportY / 12) * (((FMath::DivideAndRoundDown(index, 4) + 2) * 2) + 1);

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

float SSArcadeModeTitleScreen::CalculateGrownMarginX(FMargin inMargin)
{
	float sizeX = adjustedViewportSize.X - (inMargin.Left + inMargin.Right);
	float newSizeX = ((sizeX - (extentOfGrowth * sizeX)) / 2) / 2;

	return newSizeX;
}

float SSArcadeModeTitleScreen::CalculateGrownMarginY(FMargin inMargin)
{
	float sizeY = adjustedViewportSize.Y - (inMargin.Top + inMargin.Bottom);
	float newSizeY = ((sizeY - (extentOfGrowth * sizeY)) / 2) / 2;

	return newSizeY;
}

FMargin SSArcadeModeTitleScreen::GrowMargin(FMargin inMargin)
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

FMargin SSArcadeModeTitleScreen::ShrinkMargin(FMargin inMargin, int marginIndex)
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

FMargin SSArcadeModeTitleScreen::GrownMargin(FMargin inMargin)
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

void SSArcadeModeTitleScreen::PlayChordToActiveNote()
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
void SSArcadeModeTitleScreen::Construct(const FArguments& InArgs)
{
	SetCanTick(true);
	bCanSupportFocus = true; //this widget is currently failing to accept focus. my theory is either I need to change the setup to calling a function in the hud to designate focus from this file only after setting bCanSupportFocus = true, set canSupportFocus from the hud
	currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));
	//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, FString::FromInt(currentSave->GetHighscores()[1]));

	OwningHUD = InArgs._OwningHUD;
	playerOnePlayerController = InArgs._playerOnePlayerController;
	standardWorldContextObject = InArgs._standardWorldContextObject;
	gameFrameColor_SMUI = InArgs._gameFrameColor_SMUI;
	backgroundMaterials = InArgs._backgroundMaterials;
	backgroundIsLargeTile = InArgs._backgroundIsLargeTile;
	displayResults = InArgs._displayResults;
	hoverGrow = InArgs._hoverGrow;
	hoverShrink = InArgs._hoverShrink;
	hoverGrowAudioComponents = InArgs._hoverGrowAudioComponents;
	hoverShrinkAudioComponents = InArgs._hoverShrinkAudioComponents;
	windAudioComponents = InArgs._windAudioComponents;
	windWithSheepAudioComponents = InArgs._windWithSheepAudioComponents;
	riverAudioComponents = InArgs._riverAudioComponents;
	waterfallAudioComponents = InArgs._waterfallAudioComponents;
	purpleLullabyAudioComponents = InArgs._purpleLullabyAudioComponents;
	environmentAudio = InArgs._environmentAudio;
	masterCoefficient = InArgs._masterCoefficient;
	atmosphereCoefficient = InArgs._atmosphereCoefficient;
	sfxCoefficient = InArgs._sfxCoefficient;

	gameFrameColor_SB = new FSlateBrush();
	gameFrameColor_SB->SetResourceObject(gameFrameColor_SMUI);

	background_SB_1 = new FSlateBrush();
	background_SB_1->SetResourceObject(backgroundMaterials[0]);
	background_SB_2 = new FSlateBrush();
	background_SB_2->SetResourceObject(backgroundMaterials[1]);
	background_SB_3 = new FSlateBrush();
	background_SB_3->SetResourceObject(backgroundMaterials[2]);
	background_SB_4 = new FSlateBrush();
	background_SB_4->SetResourceObject(backgroundMaterials[3]);
	background_SB_5 = new FSlateBrush();
	background_SB_5->SetResourceObject(backgroundMaterials[4]);
	background_SB_6 = new FSlateBrush();
	background_SB_6->SetResourceObject(backgroundMaterials[5]);
	background_SB_7 = new FSlateBrush();
	background_SB_7->SetResourceObject(backgroundMaterials[6]);
	background_SB_8 = new FSlateBrush();
	background_SB_8->SetResourceObject(backgroundMaterials[7]);
	background_SB_9 = new FSlateBrush();
	background_SB_9->SetResourceObject(backgroundMaterials[8]);

	backgroundStuff = { background_SB_1, background_SB_2, background_SB_3, background_SB_4, background_SB_5, background_SB_6, background_SB_7, background_SB_8, background_SB_9 };

	GEngine->GameViewport->GetViewportSize(viewportSize);
	int32 X = FGenericPlatformMath::FloorToInt(viewportSize.X);
	int32 Y = FGenericPlatformMath::FloorToInt(viewportSize.Y);
	DPIScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(X, Y));
	adjustedViewportSize = (1 / DPIScale) * viewportSize;

	titleFont = FCoreStyle::Get().GetFontStyle("EmbossedText");
	titleFont.Size = 0.06 * adjustedViewportSize.Y;
	titleText = FText::FromString("Sorting Your Marbles");
	subTitleFont = FCoreStyle::Get().GetFontStyle("Roboto");
	subTitleFont.Size = 0.05 * adjustedViewportSize.Y;
	menuFont = FCoreStyle::Get().GetFontStyle("Roboto");
	menuFont.Size = 0.04 * adjustedViewportSize.Y;
	levelSelectorFont = FCoreStyle::Get().GetFontStyle("Roboto");
	levelSelectorFont.Size = 0.04 * adjustedViewportSize.Y;
	scoreFont = FCoreStyle::Get().GetFontStyle("Roboto");
	scoreFont.Size = 0.035 * adjustedViewportSize.Y;
	standardShadowOffset = 0.003;
	standardOpacity = 1.0;
	grownOpacity = 0.6;
	multiplierOfOffset = 4;
	multiplierOfPerimeterExpansion = 1.225;

	playMargin = CalculateMenuTextPos(0, 4);
	resultsMargin = CalculateMenuTextPos(1, 7);
	optionsMargin = CalculateMenuTextPos(2, 7);
	quitMargin = CalculateMenuTextPos(3, 4);
	backMargin = CalculateBackButtonPosition(adjustedViewportSize);

	//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, FString::SanitizeFloat(adjustedViewportSize.Y) + ", " + FString::SanitizeFloat(adjustedViewportSize.X));

	transparentButtonStyle = new FButtonStyle();
	transparentButtonStyle->SetNormalPadding(FMargin());

	childrensCornerNotes = { 8, 11, 12, 13, 8, 11, 13, 12, 7, 11, 12, 14, 9, 10, 14, 13, 8, 11, 13, 15, 10, 11, 15, 14, 9, 11, 14, 16, 9, 14, 16, 15, 11, 13, 15, 18, 13, 15, 18, 19, 13, 15, 19, 18, 13, 15, 18, 17, 13, 15, 17, 16, 13, 15, 16, 15, 11, 13, 15, 14, 11, 13, 14, 13, 10, 11, 13, 12, 9, 11, 12, 15, 10, 13, 15, 16, 11, 13, 16, 13, 9, 11, 13, 12, 9, 11, 12, 11, 8, 9, 11, 10, 7, 8, 10, 0, 4, 5, 6, 7, 9, 11, 12, 13, 12, 11, 9, 7, 6, 5, 4, 0, 4, 5, 6, 7, 9, 11, 12, 13, 12, 11, 9, 7, 6, 5, 4, 0, 4, 5, 6, 7, 22, 11, 12, 13, 12, 11, 9, 7, 6, 5, 4, 0, 4, 5, 6, 7, 22, 11, 12, 13, 12, 11, 10, 7, 6, 5, 4 };
	childrensCornerIndex = -1;

	audioCycleTracker = 0;

	hoverGrowAudioComponent = NewObject<UAudioComponent>(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0));
	hoverGrowAudioComponent->bAutoDestroy = false;
	//testAudioComponent->AutoAttachParent = UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0);
	hoverGrowAudioComponent->SetSound(hoverGrow);
	hoverShrinkAudioComponent = NewObject<UAudioComponent>(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0));
	hoverShrinkAudioComponent->bAutoDestroy = false;
	hoverShrinkAudioComponent->SetSound(hoverShrink);

	for (int a = 0; a < hoverGrowAudioComponents.Num(); a++)
	{
		hoverGrowAudioComponents[a]->SetVolumeMultiplier(((double)7.6 * (double)sfxCoefficient) * (double)masterCoefficient);
		hoverGrowAudioComponents[a]->Stop();
		hoverShrinkAudioComponents[a]->SetVolumeMultiplier(((double)7.6 * (double)sfxCoefficient) * (double)masterCoefficient);
		hoverShrinkAudioComponents[a]->Stop();
	}

	double x = ((double)100 - (double)currentSave->GetMaster()) / (double)50;
	double y = ((double)100 - (double)currentSave->GetAtmosphere()) / (double)50;

	for (int a = 0; a < 2; a++)
	{
		windAudioComponents[a]->SetVolumeMultiplier(((double)1000.0 * (double)pow((double)10, (double)-2 * y)) * (double)pow((double)10, (double)-2 * x));
		windAudioComponents[a]->Stop();
		windWithSheepAudioComponents[a]->SetVolumeMultiplier(((double)1000.0 * (double)pow((double)10, (double)-2 * y)) * (double)pow((double)10, (double)-2 * x));
		windWithSheepAudioComponents[a]->Stop();
		riverAudioComponents[a]->SetVolumeMultiplier(((double)0.33 * (double)atmosphereCoefficient) * (double)masterCoefficient);
		riverAudioComponents[a]->Stop();
		waterfallAudioComponents[a]->SetVolumeMultiplier(((double)0.8 * (double)atmosphereCoefficient) * (double)masterCoefficient);
		waterfallAudioComponents[a]->Stop();
	}

	for (int a = 0; a < purpleLullabyAudioComponents.Num(); a++)
	{
		purpleLullabyAudioComponents[a]->SetVolumeMultiplier(((double)1.0 * (double)sfxCoefficient) * (double)masterCoefficient);
		purpleLullabyAudioComponents[a]->Stop();
	}

	switch (environmentAudio)
	{
	case 0 :
		if (FMath::RandRange(0, 4) == 4)
		{
			windWithSheepAudioComponents[0]->Play();
		}
		else
		{
			windAudioComponents[0]->Play();
		}
		break;
	case 1 :
		if (FMath::RandRange(0, 4) == 4)
		{
			windWithSheepAudioComponents[0]->Play();
		}
		else
		{
			windAudioComponents[0]->Play();
		}

		riverAudioComponents[0]->Play();
		break;
	case 2 :
		if (FMath::RandRange(0, 4) == 4)
		{
			windWithSheepAudioComponents[0]->Play();
		}
		else
		{
			windAudioComponents[0]->Play();
		}

		waterfallAudioComponents[0]->Play();
		break;
	default:
		break;
	}

	frameColorOverlay = SNew(SOverlay);//how are you going to accomplish that fun menu thing where the menu characters swell up under your mouse?
	frameColorOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(FMargin(0, 0, 0, 0))
		[
			SNew(SImage)
			.Image(gameFrameColor_SB)
		];

	backgroundOverlay = SNew(SOverlay);
	if (backgroundIsLargeTile)
	{
		backgroundOverlay->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin((adjustedViewportSize.X - adjustedViewportSize.Y) / 2, 0, (adjustedViewportSize.X - adjustedViewportSize.Y) / 2, 0))
			[
				SNew(SImage)
				.Image(backgroundStuff[0])
			];
	}
	else
	{
		for (int a = 0; a < 9; a++)
		{
			backgroundOverlay->AddSlot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(CalculateBackgroundPositions(adjustedViewportSize, a))
				[
					SNew(SImage)
					.Image(backgroundStuff[a])
				];
		}
	}

	playText = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::Orange)
		.Font(menuFont)
		.Text(FText::FromString("Play"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	playBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(playMargin)
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SSArcadeModeTitleScreen::OnPlayPressed)
				.OnReleased(this, &SSArcadeModeTitleScreen::OnPlayReleased)
				.OnHovered(this, &SSArcadeModeTitleScreen::OnPlayHovered)
				.OnUnhovered(this, &SSArcadeModeTitleScreen::OnPlayUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					playText.ToSharedRef()
				]
		];

	resultsText = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::Orange)
		.Font(menuFont)
		.Text(FText::FromString("Results"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	resultsBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(resultsMargin)
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SSArcadeModeTitleScreen::OnResultsPressed)
				.OnReleased(this, &SSArcadeModeTitleScreen::OnResultsReleased)
				.OnHovered(this, &SSArcadeModeTitleScreen::OnResultsHovered)
				.OnUnhovered(this, &SSArcadeModeTitleScreen::OnResultsUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					resultsText.ToSharedRef()
				]
		];

	optionsText = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::Orange)
		.Font(menuFont)
		.Text(FText::FromString("Options"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	optionsBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(optionsMargin)
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SSArcadeModeTitleScreen::OnOptionsPressed)
				.OnReleased(this, &SSArcadeModeTitleScreen::OnOptionsReleased)
				.OnHovered(this, &SSArcadeModeTitleScreen::OnOptionsHovered)
				.OnUnhovered(this, &SSArcadeModeTitleScreen::OnOptionsUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					optionsText.ToSharedRef()
				]
		];

	quitText = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::Orange)
		.Font(menuFont)
		.Text(FText::FromString("Quit"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	quitBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(quitMargin)
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SSArcadeModeTitleScreen::OnQuitPressed)
				.OnReleased(this, &SSArcadeModeTitleScreen::OnQuitReleased)
				.OnHovered(this, &SSArcadeModeTitleScreen::OnQuitHovered)
				.OnUnhovered(this, &SSArcadeModeTitleScreen::OnQuitUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					quitText.ToSharedRef()
				]
		];


	mainMenuOverlay = SNew(SOverlay);
	mainMenuOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateTitlePosition(adjustedViewportSize))
		[
			SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(titleFont)
				.Text(FText::FromString("Sorting Your Marbles"))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
		];

	mainMenuOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			playBox.ToSharedRef()
		];

	mainMenuOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			resultsBox.ToSharedRef()
		];

	mainMenuOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			optionsBox.ToSharedRef()
		];

	mainMenuOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			quitBox.ToSharedRef()
		];

	for (int a = 0; a < 14; a++)
	{
		if (a <= currentSave->GetMaxLevel())
		{
			enabledLevels.Add(true);
		}
		else
		{
			enabledLevels.Add(false);
		}
	}

	levelSelectionOverlay = SNew(SOverlay);
	for (int a = 2; a < 16; a++)
	{
		levelSelectionBoxes.Add(SNew(SBox));

		switch (a)
		{
		case 2:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorFont)
				.Text(FText::FromString(FString::FromInt(a + 1)))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1)));

			levelSelectionBoxes[a - 2]->SetContent(
				SNew(SButton)
				.OnPressed(this, &SSArcadeModeTitleScreen::PlayPressed_3)
				.OnReleased(this, &SSArcadeModeTitleScreen::PlayReleased_3)
				.OnHovered(this, &SSArcadeModeTitleScreen::PlayHovered_3)
				.OnUnhovered(this, &SSArcadeModeTitleScreen::PlayUnHovered_3)
				.ContentPadding(FMargin())
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				.IsEnabled(true)
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 3:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorFont)
				.Text(FText::FromString(FString::FromInt(a + 1)))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1)));

			levelSelectionBoxes[a - 2]->SetContent(
				SNew(SButton)
				.OnPressed(this, &SSArcadeModeTitleScreen::PlayPressed_4)
				.OnReleased(this, &SSArcadeModeTitleScreen::PlayReleased_4)
				.OnHovered(this, &SSArcadeModeTitleScreen::PlayHovered_4)
				.OnUnhovered(this, &SSArcadeModeTitleScreen::PlayUnHovered_4)
				.ContentPadding(FMargin())
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				.IsEnabled(enabledLevels[1])
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 4:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorFont)
				.Text(FText::FromString(FString::FromInt(a + 1)))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1)));

			levelSelectionBoxes[a - 2]->SetContent(
				SNew(SButton)
				.OnPressed(this, &SSArcadeModeTitleScreen::PlayPressed_5)
				.OnReleased(this, &SSArcadeModeTitleScreen::PlayReleased_5)
				.OnHovered(this, &SSArcadeModeTitleScreen::PlayHovered_5)
				.OnUnhovered(this, &SSArcadeModeTitleScreen::PlayUnHovered_5)
				.ContentPadding(FMargin())
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				.IsEnabled(enabledLevels[2])
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 5:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorFont)
				.Text(FText::FromString(FString::FromInt(a + 1)))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1)));

			levelSelectionBoxes[a - 2]->SetContent(
				SNew(SButton)
				.OnPressed(this, &SSArcadeModeTitleScreen::PlayPressed_6)
				.OnReleased(this, &SSArcadeModeTitleScreen::PlayReleased_6)
				.OnHovered(this, &SSArcadeModeTitleScreen::PlayHovered_6)
				.OnUnhovered(this, &SSArcadeModeTitleScreen::PlayUnHovered_6)
				.ContentPadding(FMargin())
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				.IsEnabled(enabledLevels[3])
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 6:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorFont)
				.Text(FText::FromString(FString::FromInt(a + 1)))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1)));

			levelSelectionBoxes[a - 2]->SetContent(
				SNew(SButton)
				.OnPressed(this, &SSArcadeModeTitleScreen::PlayPressed_7)
				.OnReleased(this, &SSArcadeModeTitleScreen::PlayReleased_7)
				.OnHovered(this, &SSArcadeModeTitleScreen::PlayHovered_7)
				.OnUnhovered(this, &SSArcadeModeTitleScreen::PlayUnHovered_7)
				.ContentPadding(FMargin())
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				.IsEnabled(enabledLevels[4])
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 7:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorFont)
				.Text(FText::FromString(FString::FromInt(a + 1)))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1)));

			levelSelectionBoxes[a - 2]->SetContent(
				SNew(SButton)
				.OnPressed(this, &SSArcadeModeTitleScreen::PlayPressed_8)
				.OnReleased(this, &SSArcadeModeTitleScreen::PlayReleased_8)
				.OnHovered(this, &SSArcadeModeTitleScreen::PlayHovered_8)
				.OnUnhovered(this, &SSArcadeModeTitleScreen::PlayUnHovered_8)
				.ContentPadding(FMargin())
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				.IsEnabled(enabledLevels[5])
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 8:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorFont)
				.Text(FText::FromString(FString::FromInt(a + 1)))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1)));

			levelSelectionBoxes[a - 2]->SetContent(
				SNew(SButton)
				.OnPressed(this, &SSArcadeModeTitleScreen::PlayPressed_9)
				.OnReleased(this, &SSArcadeModeTitleScreen::PlayReleased_9)
				.OnHovered(this, &SSArcadeModeTitleScreen::PlayHovered_9)
				.OnUnhovered(this, &SSArcadeModeTitleScreen::PlayUnHovered_9)
				.ContentPadding(FMargin())
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				.IsEnabled(enabledLevels[6])
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 9:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorFont)
				.Text(FText::FromString(FString::FromInt(a + 1)))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1)));

			levelSelectionBoxes[a - 2]->SetContent(
				SNew(SButton)
				.OnPressed(this, &SSArcadeModeTitleScreen::PlayPressed_10)
				.OnReleased(this, &SSArcadeModeTitleScreen::PlayReleased_10)
				.OnHovered(this, &SSArcadeModeTitleScreen::PlayHovered_10)
				.OnUnhovered(this, &SSArcadeModeTitleScreen::PlayUnHovered_10)
				.ContentPadding(FMargin())
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				.IsEnabled(enabledLevels[7])
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 10:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorFont)
				.Text(FText::FromString(FString::FromInt(a + 1)))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1)));

			levelSelectionBoxes[a - 2]->SetContent(
				SNew(SButton)
				.OnPressed(this, &SSArcadeModeTitleScreen::PlayPressed_11)
				.OnReleased(this, &SSArcadeModeTitleScreen::PlayReleased_11)
				.OnHovered(this, &SSArcadeModeTitleScreen::PlayHovered_11)
				.OnUnhovered(this, &SSArcadeModeTitleScreen::PlayUnHovered_11)
				.ContentPadding(FMargin())
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				.IsEnabled(enabledLevels[8])
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 11:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorFont)
				.Text(FText::FromString(FString::FromInt(a + 1)))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1)));

			levelSelectionBoxes[a - 2]->SetContent(
				SNew(SButton)
				.OnPressed(this, &SSArcadeModeTitleScreen::PlayPressed_12)
				.OnReleased(this, &SSArcadeModeTitleScreen::PlayReleased_12)
				.OnHovered(this, &SSArcadeModeTitleScreen::PlayHovered_12)
				.OnUnhovered(this, &SSArcadeModeTitleScreen::PlayUnHovered_12)
				.ContentPadding(FMargin())
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				.IsEnabled(enabledLevels[9])
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 12:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorFont)
				.Text(FText::FromString(FString::FromInt(a + 1)))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1)));

			levelSelectionBoxes[a - 2]->SetContent(
				SNew(SButton)
				.OnPressed(this, &SSArcadeModeTitleScreen::PlayPressed_13)
				.OnReleased(this, &SSArcadeModeTitleScreen::PlayReleased_13)
				.OnHovered(this, &SSArcadeModeTitleScreen::PlayHovered_13)
				.OnUnhovered(this, &SSArcadeModeTitleScreen::PlayUnHovered_13)
				.ContentPadding(FMargin())
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				.IsEnabled(enabledLevels[10])
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 13:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorFont)
				.Text(FText::FromString(FString::FromInt(a + 1)))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1)));

			levelSelectionBoxes[a - 2]->SetContent(
				SNew(SButton)
				.OnPressed(this, &SSArcadeModeTitleScreen::PlayPressed_14)
				.OnReleased(this, &SSArcadeModeTitleScreen::PlayReleased_14)
				.OnHovered(this, &SSArcadeModeTitleScreen::PlayHovered_14)
				.OnUnhovered(this, &SSArcadeModeTitleScreen::PlayUnHovered_14)
				.ContentPadding(FMargin())
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				.IsEnabled(enabledLevels[11])
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 14:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorFont)
				.Text(FText::FromString(FString::FromInt(a + 1)))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1)));

			levelSelectionBoxes[a-2]->SetContent(
				SNew(SButton)
				.OnPressed(this, &SSArcadeModeTitleScreen::PlayPressed_15)
				.OnReleased(this, &SSArcadeModeTitleScreen::PlayReleased_15)
				.OnHovered(this, &SSArcadeModeTitleScreen::PlayHovered_15)
				.OnUnhovered(this, &SSArcadeModeTitleScreen::PlayUnHovered_15)
				.ContentPadding(FMargin())
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				.IsEnabled(enabledLevels[12])
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 15:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorFont)
				.Text(FText::FromString(FString::FromInt(a + 1)))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1)));

			levelSelectionBoxes[a - 2]->SetContent(
				SNew(SButton)
				.OnPressed(this, &SSArcadeModeTitleScreen::PlayPressed_16)
				.OnReleased(this, &SSArcadeModeTitleScreen::PlayReleased_16)
				.OnHovered(this, &SSArcadeModeTitleScreen::PlayHovered_16)
				.OnUnhovered(this, &SSArcadeModeTitleScreen::PlayUnHovered_16)
				.ContentPadding(FMargin())
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				.IsEnabled(enabledLevels[13])//this will play into the save file stuff along with the options.. ? right
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		default:
			break;
		}
		levelSelectionMargins.Add(CalculateLevelSelectionButtonsPositions(adjustedViewportSize, a));
		
		levelSelectionBoxes[a - 2]->SetHAlign(HAlign_Fill);
		levelSelectionBoxes[a - 2]->SetVAlign(VAlign_Fill);
		levelSelectionBoxes[a - 2]->SetPadding(levelSelectionMargins[a-2]);

		levelSelectionOverlay->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				levelSelectionBoxes[a - 2].ToSharedRef()
			];
	}


	backText = SNew(STextBlock);
	backText->SetJustification(ETextJustify::Center);
	backText->SetColorAndOpacity(FColor::Orange);
	backText->SetFont(menuFont);
	backText->SetText(FText::FromString("Back"));
	backText->SetShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003));
	backText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, 1));

	firstFloorBackBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(backMargin)
		[
			SNew(SButton)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.OnPressed(this, &SSArcadeModeTitleScreen::OnBackFloorOnePressed)
			.OnReleased(this, &SSArcadeModeTitleScreen::OnBackFloorOneReleased)
			.OnHovered(this, &SSArcadeModeTitleScreen::OnBackFloorOneHovered)
			.OnUnhovered(this, &SSArcadeModeTitleScreen::OnBackFloorOneUnHovered)
			.ContentPadding(FMargin())
			.IsEnabled(true)
			.ButtonColorAndOpacity(FLinearColor::Transparent)
			.ButtonStyle(transparentButtonStyle)
			[
				backText.ToSharedRef()
			]
		];

	levelSelectionOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			firstFloorBackBox.ToSharedRef()
		];

	levelSelectionOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateTitlePosition(adjustedViewportSize))
		[
			SNew(STextBlock)
			.Justification(ETextJustify::Center)
			.ColorAndOpacity(FColor::Orange)
			.Font(subTitleFont)
			.Text(FText::FromString("Select Level"))
			.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
			.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
		];

	resultsOverlay = SNew(SOverlay);
	resultsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateTitlePosition(adjustedViewportSize))
		[
			SNew(STextBlock)
			.Justification(ETextJustify::Center)
			.ColorAndOpacity(FColor::Orange)
			.Font(subTitleFont)
			.Text(FText::FromString("Results"))
			.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
			.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
		];

	resultsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateHighscorePos(0, 9))
		[
			SNew(STextBlock)
			.Justification(ETextJustify::Center)
			.ColorAndOpacity(FColor::Orange)
			.Font(menuFont)//italic
			.Text(FText::FromString("Highscores"))
			.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
			.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
		];

	for (int a = 0; a < currentSave->GetHighscores().Num(); a++)
	{
		resultsOverlay->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateHighscorePos(a + 2, 4))
			[
				SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(menuFont)
				.Text(FText::FromString(FString::FromInt(a + 1) + ":   " + FString::FromInt(currentSave->GetHighscores()[a])))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
			];
	}

	resultsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateLastGamePos(0, 9))
		[
			SNew(STextBlock)
			.Justification(ETextJustify::Center)
			.ColorAndOpacity(FColor::Orange)
			.Font(menuFont)
			.Text(FText::FromString("Last Game"))
			.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
			.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
		];

	resultsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateLastGamePos(1, 2))
		[
			SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(menuFont)
				.Text(FText::FromString(FString::FromInt(currentSave->GetScoreThisGame())))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
		];

	//score = numMarblesCorrectlySorted * 1.2^levelOfDifficulty with 3 holes being 0 difficulty, 4 being 1 difficulty and so on.

	resultsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			firstFloorBackBox.ToSharedRef()
		];

	masterOverlay = SNew(SOverlay);

	if (displayResults)
	{
		masterOverlay->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				resultsOverlay.ToSharedRef()
			];
	}
	else
	{
		masterOverlay->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				mainMenuOverlay.ToSharedRef()
			];
	}

	ChildSlot
		[
			SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					frameColorOverlay.ToSharedRef()
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					backgroundOverlay.ToSharedRef()
				]

				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					masterOverlay.ToSharedRef()
				]
		];
}

void SSArcadeModeTitleScreen::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	audioTimer += InDeltaTime;

	if (audioCycleTracker < FMath::DivideAndRoundDown((int)audioTimer, 120))
	{
		audioCycleTracker += 1;

		switch (environmentAudio)
		{
		case 0:
			if (FMath::RandRange(0, 4) == 4)
			{
				windWithSheepAudioComponents[audioCycleTracker % 2]->Play();
			}
			else
			{
				windAudioComponents[audioCycleTracker % 2]->Play();
			}
			break;
		case 1:
			if (FMath::RandRange(0, 4) == 4)
			{
				windWithSheepAudioComponents[audioCycleTracker % 2]->Play();
			}
			else
			{
				windAudioComponents[audioCycleTracker % 2]->Play();
			}

			riverAudioComponents[audioCycleTracker % 2]->Play();
			break;
		case 2:
			if (FMath::RandRange(0, 4) == 4)
			{
				windWithSheepAudioComponents[audioCycleTracker % 2]->Play();
			}
			else
			{
				windAudioComponents[audioCycleTracker % 2]->Play();
			}

			waterfallAudioComponents[audioCycleTracker % 2]->Play();
			break;
		default:
			break;
		}
	}

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
}

void SSArcadeModeTitleScreen::OnPlayHovered()//the play button and all buttons are not aligned to the center vertically but to the top. this means when expaning the greater the extra space in the button the more the expansion biases upwards. the shadow offset also does have a small effect on the horizontal center alignment. meaning when the shadow offsets to the right during expansion the text equalizes to the left to some extent. To achieve a totally perfect "coming right at you" effect I would need to get a tighter grip on exactly how to size the buttons (vertically) perfectly relevant to screen size, as well as impliment some internal padding within the text or button to correct for the text equalization.
{
	if (shrinkingBoxes.Find(playBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(playBox);
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
		growingMargin = playMargin;
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
	growingBox.Add(playBox);
	growingTextBlock = playText;
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
	//UGameplayStatics::PlaySound2D(standardWorldContextObject, hoverGrow);
}

void SSArcadeModeTitleScreen::OnPlayUnHovered()
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

			growingMargin = GrownMargin(playMargin);
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
		shrinkingAdjustedMarginSizesX.Add((playMargin - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((playMargin - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((menuFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(playMargin);
		completedFonts.Add(menuFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}

void SSArcadeModeTitleScreen::OnPlayPressed()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	playText->SetColorAndOpacity(FColor::White);
}

void SSArcadeModeTitleScreen::OnPlayReleased()
{
	PlayChordToActiveNote();

	playText->SetColorAndOpacity(FColor::Orange);
	playBox->SetPadding(playMargin);
	playText->SetFont(menuFont);
	playText->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	playText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	masterOverlay->RemoveSlot(0);
	masterOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			levelSelectionOverlay.ToSharedRef()
		];

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
	else if (shrinkingBoxes.Find(playBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(playBox);

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

void SSArcadeModeTitleScreen::OnResultsHovered()
{
	if (shrinkingBoxes.Find(resultsBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(resultsBox);
		extentOfGrowth = menuFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
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
		growingMargin = resultsMargin;
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
	growingBox.Add(resultsBox);
	growingTextBlock = resultsText;
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}

void SSArcadeModeTitleScreen::OnResultsUnHovered()
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

			growingMargin = GrownMargin(resultsMargin);
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
		shrinkingAdjustedMarginSizesX.Add((resultsMargin - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((resultsMargin - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((menuFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(resultsMargin);
		completedFonts.Add(menuFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}

void SSArcadeModeTitleScreen::OnResultsPressed()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	resultsText->SetColorAndOpacity(FColor::White);
}

void SSArcadeModeTitleScreen::OnResultsReleased()
{
	PlayChordToActiveNote();

	resultsText->SetColorAndOpacity(FColor::Orange);
	resultsBox->SetPadding(resultsMargin);
	resultsText->SetFont(menuFont);
	resultsText->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	resultsText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	masterOverlay->RemoveSlot(0);
	masterOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			resultsOverlay.ToSharedRef()
		];

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
	else if (shrinkingBoxes.Find(resultsBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(resultsBox);

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

void SSArcadeModeTitleScreen::OnOptionsHovered()
{
	if (shrinkingBoxes.Find(optionsBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(optionsBox);
		extentOfGrowth = menuFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
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

void SSArcadeModeTitleScreen::OnOptionsUnHovered()
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

void SSArcadeModeTitleScreen::OnOptionsPressed()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	optionsText->SetColorAndOpacity(FColor::White);
}

void SSArcadeModeTitleScreen::OnOptionsReleased()
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

	masterOverlay->RemoveSlot(0);
	OwningHUD->DisplayOptionsMenu(false);//is there anywhere where positioning this kind of logic where I used to position it will cause a problem or is secretly already causeing a problem?
}

void SSArcadeModeTitleScreen::OnQuitHovered()
{
	if (shrinkingBoxes.Find(quitBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(quitBox);
		extentOfGrowth = menuFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
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
		growingMargin = quitMargin;
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
	growingBox.Add(quitBox);
	growingTextBlock = quitText;
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}

void SSArcadeModeTitleScreen::OnQuitUnHovered()
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

			growingMargin = GrownMargin(quitMargin);
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
		shrinkingAdjustedMarginSizesX.Add((quitMargin - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((quitMargin - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((menuFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(quitMargin);
		completedFonts.Add(menuFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}

void SSArcadeModeTitleScreen::OnQuitPressed()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	quitText->SetColorAndOpacity(FColor::White);
}

void SSArcadeModeTitleScreen::OnQuitReleased()
{
	PlayChordToActiveNote();

	quitText->SetColorAndOpacity(FColor::Orange);
	quitBox->SetPadding(quitMargin);
	quitText->SetFont(menuFont);
	quitText->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	quitText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	OwningHUD->HouseKeeping();
	OwningHUD->ResetRegenLevel();

	UKismetSystemLibrary::QuitGame(playerOnePlayerController, playerOnePlayerController, EQuitPreference::Quit, false);

	/*masterOverlay->RemoveSlot(0);
	masterOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			levelSelectionOverlay.ToSharedRef()
		];*/

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
	else if (shrinkingBoxes.Find(quitBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(quitBox);

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

void SSArcadeModeTitleScreen::OnBackFloorOnePressed()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	backText->SetColorAndOpacity(FColor::White);
}

void SSArcadeModeTitleScreen::OnBackFloorOneReleased()
{
	PlayChordToActiveNote();

	backText->SetColorAndOpacity(FColor::Orange);
	firstFloorBackBox->SetPadding(backMargin);
	backText->SetFont(menuFont);
	backText->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	backText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	masterOverlay->RemoveSlot(0);
	masterOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			mainMenuOverlay.ToSharedRef()
		];

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
	else if (shrinkingBoxes.Find(firstFloorBackBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(firstFloorBackBox);

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
void SSArcadeModeTitleScreen::OnBackFloorOneHovered()
{
	if (shrinkingBoxes.Find(firstFloorBackBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(firstFloorBackBox);
		extentOfGrowth = menuFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
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
		growingMargin = backMargin;
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
	growingBox.Add(firstFloorBackBox);
	growingTextBlock = backText;
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}

void SSArcadeModeTitleScreen::OnBackFloorOneUnHovered()
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

			growingMargin = GrownMargin(backMargin);
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
		shrinkingAdjustedMarginSizesX.Add((backMargin - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((backMargin - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((menuFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(backMargin);
		completedFonts.Add(menuFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}

void SSArcadeModeTitleScreen::PlayPressed_3()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	levelSelectionTexts[0]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_3()
{
	PlayChordToActiveNote();

	levelSelectionTexts[0]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[0]->SetPadding(levelSelectionMargins[0]);
	levelSelectionTexts[0]->SetFont(levelSelectorFont);
	levelSelectionTexts[0]->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	levelSelectionTexts[0]->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	levelSelectionTexts[0]->SetColorAndOpacity(FColor::Orange);

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
	else if (shrinkingBoxes.Find(levelSelectionBoxes[0]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[0]);

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
	OwningHUD->DisplayCurtains(3);
}
void SSArcadeModeTitleScreen::PlayHovered_3()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[0]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[0]);
		extentOfGrowth = levelSelectorFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
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

		growingFont = levelSelectorFont;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[0];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorFont.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[0]);
	growingTextBlock = levelSelectionTexts[0];
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SSArcadeModeTitleScreen::PlayUnHovered_3()
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

			growingMargin = GrownMargin(levelSelectionMargins[0]);
			growingFont.Size = levelSelectorFont.Size * multiplierOfPerimeterExpansion;
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
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[0] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[0] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(levelSelectionMargins[0]);
		completedFonts.Add(levelSelectorFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}

void SSArcadeModeTitleScreen::PlayPressed_4()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	levelSelectionTexts[1]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_4()
{
	PlayChordToActiveNote();

	levelSelectionTexts[1]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[1]->SetPadding(levelSelectionMargins[1]);
	levelSelectionTexts[1]->SetFont(levelSelectorFont);
	levelSelectionTexts[1]->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	levelSelectionTexts[1]->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	levelSelectionTexts[1]->SetColorAndOpacity(FColor::Orange);

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
	else if (shrinkingBoxes.Find(levelSelectionBoxes[1]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[1]);

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
	OwningHUD->DisplayCurtains(4);
}
void SSArcadeModeTitleScreen::PlayHovered_4()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[1]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[1]);
		extentOfGrowth = levelSelectorFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
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

		growingFont = levelSelectorFont;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[1];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorFont.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[1]);
	growingTextBlock = levelSelectionTexts[1];
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SSArcadeModeTitleScreen::PlayUnHovered_4()
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

			growingMargin = GrownMargin(levelSelectionMargins[1]);
			growingFont.Size = levelSelectorFont.Size * multiplierOfPerimeterExpansion;
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
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[1] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[1] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(levelSelectionMargins[1]);
		completedFonts.Add(levelSelectorFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}

void SSArcadeModeTitleScreen::PlayPressed_5()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	levelSelectionTexts[2]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_5()
{
	PlayChordToActiveNote();

	levelSelectionTexts[2]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[2]->SetPadding(levelSelectionMargins[2]);
	levelSelectionTexts[2]->SetFont(levelSelectorFont);
	levelSelectionTexts[2]->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	levelSelectionTexts[2]->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	levelSelectionTexts[2]->SetColorAndOpacity(FColor::Orange);

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
	else if (shrinkingBoxes.Find(levelSelectionBoxes[2]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[2]);

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
	OwningHUD->DisplayCurtains(5);
}
void SSArcadeModeTitleScreen::PlayHovered_5()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[2]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[2]);
		extentOfGrowth = levelSelectorFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
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

		growingFont = levelSelectorFont;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[2];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorFont.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[2]);
	growingTextBlock = levelSelectionTexts[2];
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SSArcadeModeTitleScreen::PlayUnHovered_5()
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

			growingMargin = GrownMargin(levelSelectionMargins[2]);
			growingFont.Size = levelSelectorFont.Size * multiplierOfPerimeterExpansion;
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
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[2] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[2] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(levelSelectionMargins[2]);
		completedFonts.Add(levelSelectorFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}

void SSArcadeModeTitleScreen::PlayPressed_6()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	levelSelectionTexts[3]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_6()
{
	PlayChordToActiveNote();

	levelSelectionTexts[3]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[3]->SetPadding(levelSelectionMargins[3]);
	levelSelectionTexts[3]->SetFont(levelSelectorFont);
	levelSelectionTexts[3]->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	levelSelectionTexts[3]->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	levelSelectionTexts[3]->SetColorAndOpacity(FColor::Orange);

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
	else if (shrinkingBoxes.Find(levelSelectionBoxes[3]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[3]);

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
	OwningHUD->DisplayCurtains(6);
}
void SSArcadeModeTitleScreen::PlayHovered_6()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[3]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[3]);
		extentOfGrowth = levelSelectorFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
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

		growingFont = levelSelectorFont;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[3];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorFont.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[3]);
	growingTextBlock = levelSelectionTexts[3];
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SSArcadeModeTitleScreen::PlayUnHovered_6()
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

			growingMargin = GrownMargin(levelSelectionMargins[3]);
			growingFont.Size = levelSelectorFont.Size * multiplierOfPerimeterExpansion;
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
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[3] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[3] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(levelSelectionMargins[3]);
		completedFonts.Add(levelSelectorFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}

void SSArcadeModeTitleScreen::PlayPressed_7()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	levelSelectionTexts[4]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_7()
{
	PlayChordToActiveNote();

	levelSelectionTexts[4]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[4]->SetPadding(levelSelectionMargins[4]);
	levelSelectionTexts[4]->SetFont(levelSelectorFont);
	levelSelectionTexts[4]->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	levelSelectionTexts[4]->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	levelSelectionTexts[4]->SetColorAndOpacity(FColor::Orange);

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
	else if (shrinkingBoxes.Find(levelSelectionBoxes[4]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[4]);

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
	OwningHUD->DisplayCurtains(7);
}
void SSArcadeModeTitleScreen::PlayHovered_7()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[4]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[4]);
		extentOfGrowth = levelSelectorFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
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

		growingFont = levelSelectorFont;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[4];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorFont.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[4]);
	growingTextBlock = levelSelectionTexts[4];
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SSArcadeModeTitleScreen::PlayUnHovered_7()
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

			growingMargin = GrownMargin(levelSelectionMargins[4]);
			growingFont.Size = levelSelectorFont.Size * multiplierOfPerimeterExpansion;
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
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[4] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[4] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(levelSelectionMargins[4]);
		completedFonts.Add(levelSelectorFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}

void SSArcadeModeTitleScreen::PlayPressed_8()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	levelSelectionTexts[5]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_8()
{
	PlayChordToActiveNote();

	levelSelectionTexts[5]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[5]->SetPadding(levelSelectionMargins[5]);
	levelSelectionTexts[5]->SetFont(levelSelectorFont);
	levelSelectionTexts[5]->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	levelSelectionTexts[5]->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	levelSelectionTexts[5]->SetColorAndOpacity(FColor::Orange);

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
	else if (shrinkingBoxes.Find(levelSelectionBoxes[5]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[5]);

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
	OwningHUD->DisplayCurtains(8);
}
void SSArcadeModeTitleScreen::PlayHovered_8()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[5]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[5]);
		extentOfGrowth = levelSelectorFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
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

		growingFont = levelSelectorFont;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[5];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorFont.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[5]);
	growingTextBlock = levelSelectionTexts[5];
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SSArcadeModeTitleScreen::PlayUnHovered_8()
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

			growingMargin = GrownMargin(levelSelectionMargins[5]);
			growingFont.Size = levelSelectorFont.Size * multiplierOfPerimeterExpansion;
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
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[5] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[5] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(levelSelectionMargins[5]);
		completedFonts.Add(levelSelectorFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}

void SSArcadeModeTitleScreen::PlayPressed_9()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	levelSelectionTexts[6]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_9()
{
	PlayChordToActiveNote();

	levelSelectionTexts[6]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[6]->SetPadding(levelSelectionMargins[6]);
	levelSelectionTexts[6]->SetFont(levelSelectorFont);
	levelSelectionTexts[6]->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	levelSelectionTexts[6]->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	levelSelectionTexts[6]->SetColorAndOpacity(FColor::Orange);

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
	else if (shrinkingBoxes.Find(levelSelectionBoxes[6]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[6]);

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
	OwningHUD->DisplayCurtains(9);
}
void SSArcadeModeTitleScreen::PlayHovered_9()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[6]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[6]);
		extentOfGrowth = levelSelectorFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
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

		growingFont = levelSelectorFont;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[6];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorFont.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[6]);
	growingTextBlock = levelSelectionTexts[6];
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SSArcadeModeTitleScreen::PlayUnHovered_9()
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

			growingMargin = GrownMargin(levelSelectionMargins[6]);
			growingFont.Size = levelSelectorFont.Size * multiplierOfPerimeterExpansion;
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
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[6] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[6] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(levelSelectionMargins[6]);
		completedFonts.Add(levelSelectorFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}

void SSArcadeModeTitleScreen::PlayPressed_10()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	levelSelectionTexts[7]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_10()
{
	PlayChordToActiveNote();

	levelSelectionTexts[7]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[7]->SetPadding(levelSelectionMargins[7]);
	levelSelectionTexts[7]->SetFont(levelSelectorFont);
	levelSelectionTexts[7]->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	levelSelectionTexts[7]->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	levelSelectionTexts[7]->SetColorAndOpacity(FColor::Orange);

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
	else if (shrinkingBoxes.Find(levelSelectionBoxes[7]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[7]);

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
	OwningHUD->DisplayCurtains(10);
}
void SSArcadeModeTitleScreen::PlayHovered_10()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[7]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[7]);
		extentOfGrowth = levelSelectorFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
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

		growingFont = levelSelectorFont;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[7];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorFont.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[7]);
	growingTextBlock = levelSelectionTexts[7];
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SSArcadeModeTitleScreen::PlayUnHovered_10()
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

			growingMargin = GrownMargin(levelSelectionMargins[7]);
			growingFont.Size = levelSelectorFont.Size * multiplierOfPerimeterExpansion;
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
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[7] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[7] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(levelSelectionMargins[7]);
		completedFonts.Add(levelSelectorFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}

void SSArcadeModeTitleScreen::PlayPressed_11()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	levelSelectionTexts[8]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_11()
{
	PlayChordToActiveNote();

	levelSelectionTexts[8]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[8]->SetPadding(levelSelectionMargins[8]);
	levelSelectionTexts[8]->SetFont(levelSelectorFont);
	levelSelectionTexts[8]->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	levelSelectionTexts[8]->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	levelSelectionTexts[8]->SetColorAndOpacity(FColor::Orange);

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
	else if (shrinkingBoxes.Find(levelSelectionBoxes[8]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[8]);

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
	OwningHUD->DisplayCurtains(11);
}
void SSArcadeModeTitleScreen::PlayHovered_11()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[8]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[8]);
		extentOfGrowth = levelSelectorFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
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

		growingFont = levelSelectorFont;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[8];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorFont.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[8]);
	growingTextBlock = levelSelectionTexts[8];
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SSArcadeModeTitleScreen::PlayUnHovered_11()
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

			growingMargin = GrownMargin(levelSelectionMargins[8]);
			growingFont.Size = levelSelectorFont.Size * multiplierOfPerimeterExpansion;
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
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[8] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[8] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(levelSelectionMargins[8]);
		completedFonts.Add(levelSelectorFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}

void SSArcadeModeTitleScreen::PlayPressed_12()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	levelSelectionTexts[9]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_12()
{
	PlayChordToActiveNote();

	levelSelectionTexts[9]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[9]->SetPadding(levelSelectionMargins[9]);
	levelSelectionTexts[9]->SetFont(levelSelectorFont);
	levelSelectionTexts[9]->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	levelSelectionTexts[9]->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	levelSelectionTexts[9]->SetColorAndOpacity(FColor::Orange);

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
	else if (shrinkingBoxes.Find(levelSelectionBoxes[9]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[9]);

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
	OwningHUD->DisplayCurtains(12);
}
void SSArcadeModeTitleScreen::PlayHovered_12()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[9]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[9]);
		extentOfGrowth = levelSelectorFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
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

		growingFont = levelSelectorFont;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[9];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorFont.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[9]);
	growingTextBlock = levelSelectionTexts[9];
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SSArcadeModeTitleScreen::PlayUnHovered_12()
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

			growingMargin = GrownMargin(levelSelectionMargins[9]);
			growingFont.Size = levelSelectorFont.Size * multiplierOfPerimeterExpansion;
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
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[9] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[9] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(levelSelectionMargins[9]);
		completedFonts.Add(levelSelectorFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}

void SSArcadeModeTitleScreen::PlayPressed_13()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	levelSelectionTexts[10]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_13()
{
	PlayChordToActiveNote();

	levelSelectionTexts[10]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[10]->SetPadding(levelSelectionMargins[10]);
	levelSelectionTexts[10]->SetFont(levelSelectorFont);
	levelSelectionTexts[10]->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	levelSelectionTexts[10]->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	levelSelectionTexts[10]->SetColorAndOpacity(FColor::Orange);

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
	else if (shrinkingBoxes.Find(levelSelectionBoxes[10]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[10]);

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
	OwningHUD->DisplayCurtains(13);
}
void SSArcadeModeTitleScreen::PlayHovered_13()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[10]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[10]);
		extentOfGrowth = levelSelectorFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
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

		growingFont = levelSelectorFont;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[10];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorFont.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[10]);
	growingTextBlock = levelSelectionTexts[10];
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SSArcadeModeTitleScreen::PlayUnHovered_13()
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

			growingMargin = GrownMargin(levelSelectionMargins[10]);
			growingFont.Size = levelSelectorFont.Size * multiplierOfPerimeterExpansion;
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
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[10] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[10] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(levelSelectionMargins[10]);
		completedFonts.Add(levelSelectorFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}

void SSArcadeModeTitleScreen::PlayPressed_14()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	levelSelectionTexts[11]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_14()
{
	PlayChordToActiveNote();

	levelSelectionTexts[11]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[11]->SetPadding(levelSelectionMargins[11]);
	levelSelectionTexts[11]->SetFont(levelSelectorFont);
	levelSelectionTexts[11]->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	levelSelectionTexts[11]->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	levelSelectionTexts[11]->SetColorAndOpacity(FColor::Orange);

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
	else if (shrinkingBoxes.Find(levelSelectionBoxes[11]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[11]);

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
	OwningHUD->DisplayCurtains(14);
}
void SSArcadeModeTitleScreen::PlayHovered_14()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[11]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[11]);
		extentOfGrowth = levelSelectorFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
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

		growingFont = levelSelectorFont;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[11];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorFont.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[11]);
	growingTextBlock = levelSelectionTexts[11];
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SSArcadeModeTitleScreen::PlayUnHovered_14()
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

			growingMargin = GrownMargin(levelSelectionMargins[11]);
			growingFont.Size = levelSelectorFont.Size * multiplierOfPerimeterExpansion;
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
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[11] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[11] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(levelSelectionMargins[11]);
		completedFonts.Add(levelSelectorFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}

void SSArcadeModeTitleScreen::PlayPressed_15()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	levelSelectionTexts[12]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_15()
{
	PlayChordToActiveNote();

	levelSelectionTexts[12]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[12]->SetPadding(levelSelectionMargins[12]);
	levelSelectionTexts[12]->SetFont(levelSelectorFont);
	levelSelectionTexts[12]->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	levelSelectionTexts[12]->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	levelSelectionTexts[12]->SetColorAndOpacity(FColor::Orange);

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
	else if (shrinkingBoxes.Find(levelSelectionBoxes[12]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[12]);

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
	OwningHUD->DisplayCurtains(15);
}
void SSArcadeModeTitleScreen::PlayHovered_15()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[12]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[12]);
		extentOfGrowth = levelSelectorFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
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

		growingFont = levelSelectorFont;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[12];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorFont.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[12]);
	growingTextBlock = levelSelectionTexts[12];
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SSArcadeModeTitleScreen::PlayUnHovered_15()
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

			growingMargin = GrownMargin(levelSelectionMargins[12]);
			growingFont.Size = levelSelectorFont.Size * multiplierOfPerimeterExpansion;
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
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[12] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[12] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(levelSelectionMargins[12]);
		completedFonts.Add(levelSelectorFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}

void SSArcadeModeTitleScreen::PlayPressed_16()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	levelSelectionTexts[13]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_16()
{
	PlayChordToActiveNote();

	levelSelectionTexts[13]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[13]->SetPadding(levelSelectionMargins[13]);
	levelSelectionTexts[13]->SetFont(levelSelectorFont);
	levelSelectionTexts[13]->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	levelSelectionTexts[13]->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	levelSelectionTexts[13]->SetColorAndOpacity(FColor::Orange);

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
	else if (shrinkingBoxes.Find(levelSelectionBoxes[13]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[13]);

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
	OwningHUD->DisplayCurtains(16);
}
void SSArcadeModeTitleScreen::PlayHovered_16()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[13]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[13]);
		extentOfGrowth = levelSelectorFont.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
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

		growingFont = levelSelectorFont;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[13];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorFont.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[13]);
	growingTextBlock = levelSelectionTexts[13];
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SSArcadeModeTitleScreen::PlayUnHovered_16()
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

			growingMargin = GrownMargin(levelSelectionMargins[13]);
			growingFont.Size = levelSelectorFont.Size * multiplierOfPerimeterExpansion;
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
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[13] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[13] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(levelSelectionMargins[13]);
		completedFonts.Add(levelSelectorFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}

void SSArcadeModeTitleScreen::ReturnToMenu()
{
	masterOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			mainMenuOverlay.ToSharedRef()
		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION