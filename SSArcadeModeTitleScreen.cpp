#include "SSArcadeModeTitleScreen.h"
#include "SlateOptMacros.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"

FMargin CalculateTitlePosition(FVector2D viewportSize)
{//your sub titles will use this same positioning but the a different text style
	float leftPad = viewportSize.X * 0.1;
	float topPad = viewportSize.Y * 0.1;
	float rightPad = viewportSize.X * 0.1;
	float bottomPad = viewportSize.Y * 0.75;

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

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSArcadeModeTitleScreen::Construct(const FArguments& InArgs)
{
	SetCanTick(true);
	bCanSupportFocus = true;

	OwningHUD = InArgs._OwningHUD;
	playerOnePlayerController = InArgs._playerOnePlayerController;
	gameFrameColor_SMUI = InArgs._gameFrameColor_SMUI;
	backgroundMaterials = InArgs._backgroundMaterials;
	backgroundIsLargeTile = InArgs._backgroundIsLargeTile;

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

	titleTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	titleTextStyle.Size = 0.06 * adjustedViewportSize.Y;
	titleText = FText::FromString("Mind Marbles");
	subTitleTextStyle = FCoreStyle::Get().GetFontStyle("Roboto");
	subTitleTextStyle.Size = 0.05 * adjustedViewportSize.Y;
	menuTextStyle = FCoreStyle::Get().GetFontStyle("Roboto");
	menuTextStyle.Size = 0.04 * adjustedViewportSize.Y;
	playTextStyle = menuTextStyle;
	levelSelectorTextStyle = FCoreStyle::Get().GetFontStyle("Roboto");
	levelSelectorTextStyle.Size = 0.04 * adjustedViewportSize.Y;
	standardShadowOffset = 0.003;
	standardOpacity = 1.0;
	grownOpacity = 0.6;
	multiplierOfOffset = 4;
	multiplierOfPerimeterExpansion = 1.225;

	//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, FString::SanitizeFloat(adjustedViewportSize.Y) + ", " + FString::SanitizeFloat(adjustedViewportSize.X));

	transparentButtonStyle = new FButtonStyle();
	transparentButtonStyle->SetNormalPadding(FMargin());

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
		.Font(menuTextStyle)
		.Text(FText::FromString("Play"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	playMargin = CalculateMenuTextPos(0, 4);

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


	mainMenuOverlay = SNew(SOverlay);
	mainMenuOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateTitlePosition(adjustedViewportSize))
		[
			SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(titleTextStyle)
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
		.Padding(CalculateMenuTextPos(1, 7))
		[
			SNew(SButton)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					SNew(STextBlock)
						.Justification(ETextJustify::Center)
						.ColorAndOpacity(FColor::Orange)
						.Font(menuTextStyle)
						.Text(FText::FromString("Results"))
						.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
						.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
				]
		];

	mainMenuOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateMenuTextPos(2, 7))
		[
			SNew(SButton)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					SNew(STextBlock)
						.Justification(ETextJustify::Center)
						.ColorAndOpacity(FColor::Orange)
						.Font(menuTextStyle)
						.Text(FText::FromString("Options"))
						.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
						.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
				]
		];

	mainMenuOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateMenuTextPos(3, 4))
		[
			SNew(SButton)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					SNew(STextBlock)
						.Justification(ETextJustify::Center)
						.ColorAndOpacity(FColor::Orange)
						.Font(menuTextStyle)
						.Text(FText::FromString("Quit"))
						.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
						.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
				]
		];

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
				.Font(levelSelectorTextStyle)
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
				.Font(levelSelectorTextStyle)
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
				.IsEnabled(true)
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 4:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorTextStyle)
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
				.IsEnabled(true)
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 5:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorTextStyle)
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
				.IsEnabled(true)
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 6:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorTextStyle)
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
				.IsEnabled(true)
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 7:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorTextStyle)
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
				.IsEnabled(true)
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 8:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorTextStyle)
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
				.IsEnabled(true)
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 9:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorTextStyle)
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
				.IsEnabled(true)
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 10:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorTextStyle)
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
				.IsEnabled(true)
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 11:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorTextStyle)
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
				.IsEnabled(true)
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 12:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorTextStyle)
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
				.IsEnabled(true)
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 13:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorTextStyle)
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
				.IsEnabled(true)
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 14:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorTextStyle)
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
				.IsEnabled(true)
				[
					levelSelectionTexts[a - 2].ToSharedRef()
				]);
			break;
		case 15:
			levelSelectionTexts.Add(SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(levelSelectorTextStyle)
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
				.IsEnabled(true)//this will play into the save file stuff along with the options.. ? right
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
	backText->SetFont(menuTextStyle);
	backText->SetText(FText::FromString("Back"));
	backText->SetShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003));
	backText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, 1));

	firstFloorBackButton = SNew(SButton)
		.ButtonColorAndOpacity(FLinearColor::Transparent)
		.OnPressed(this, &SSArcadeModeTitleScreen::OnBackFloorOnePressed)
		.OnReleased(this, &SSArcadeModeTitleScreen::OnBackFloorOneReleased);
	firstFloorBackButton->SetContentPadding(FMargin());
	firstFloorBackButton->SetEnabled(true);
	firstFloorBackButton->SetButtonStyle(transparentButtonStyle);
	firstFloorBackButton->SetContent(backText.ToSharedRef());

	levelSelectionOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateBackButtonPosition(adjustedViewportSize))
		[
			firstFloorBackButton.ToSharedRef()
		];

	masterOverlay = SNew(SOverlay);
	masterOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			mainMenuOverlay.ToSharedRef()
		];

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
		growingText.Size = growingFontSize;
		growingTextBlock->SetFont(growingText);
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
		extentOfGrowth = playTextStyle.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size; //am I going to need multiple extentOfGrowths? if it is only implimented in growing and not in shrinking then no: just the one should suffice
		growingOffset = shrinkingOffset[indexOfShrinkingSubject];
		growingMargin = shrinkingMargins[indexOfShrinkingSubject];
		growingText = shrinkingTexts[indexOfShrinkingSubject];
		growingLinearColor = shrinkingLinearColors[indexOfShrinkingSubject];
		growingOpacity = shrinkingOpacities[indexOfShrinkingSubject];

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
	}
	else
	{
		extentOfGrowth = multiplierOfPerimeterExpansion;

		growingText = playTextStyle;
		growingOffset = standardShadowOffset;
		growingMargin = playMargin;
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = playTextStyle.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(playBox);
	growingTextBlock = playText;
	growTime = 0;
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
			growingText.Size = playTextStyle.Size * multiplierOfPerimeterExpansion;
			growingOffset = standardShadowOffset * multiplierOfOffset;
			growingLinearColor = FLinearColor(0, 0, 0, grownOpacity);
			growingOpacity = grownOpacity;
		}

		shrinkingOpacities.Add(growingOpacity);
		shrinkingLinearColors.Add(growingLinearColor);
		startingShrinkingOpacities.Add(growingOpacity);
		adjustedShrinkingOpacities.Add((1 - growingOpacity) / 2);
		shrinkingOffset.Add(growingOffset);
		startingShrinkingOffset.Add(growingOffset);
		adjustedShrinkingOffset.Add((0.003 - growingOffset) / 2);
		shrinkingTextBlocks.Add(growingTextBlock);
		shrinkingTexts.Add(growingText);
		shrinkingMargins.Add(growingMargin);
		shrinkingMarginsStartingPoints.Add(growingMargin);
		shrinkingAdjustedMarginSizesX.Add((playMargin - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((playMargin - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((playTextStyle.Size - growingText.Size) / 2);
		shrinkingTimes.Add(0);
	}
}

void SSArcadeModeTitleScreen::OnPlayPressed()
{
	playText->SetColorAndOpacity(FColor::White);
}

void SSArcadeModeTitleScreen::OnPlayReleased()
{
	playText->SetColorAndOpacity(FColor::Orange);
	playBox->SetPadding(playMargin);
	playText->SetFont(playTextStyle);
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
		
	}
}

void SSArcadeModeTitleScreen::OnBackFloorOnePressed()
{
	backText->SetColorAndOpacity(FColor::White);
}

void SSArcadeModeTitleScreen::OnBackFloorOneReleased()
{
	backText->SetColorAndOpacity(FColor::Orange);
	masterOverlay->RemoveSlot(0);
	masterOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			mainMenuOverlay.ToSharedRef()
		];
}

void SSArcadeModeTitleScreen::PlayPressed_3()
{
	levelSelectionTexts[0]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_3()
{
	levelSelectionTexts[0]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[0]->SetPadding(levelSelectionMargins[0]);
	levelSelectionTexts[0]->SetFont(levelSelectorTextStyle);
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
	}
	OwningHUD->DisplayCurtains(3);
}
void SSArcadeModeTitleScreen::PlayHovered_3()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[0]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[0]);
		extentOfGrowth = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
		growingOffset = shrinkingOffset[indexOfShrinkingSubject];
		growingMargin = shrinkingMargins[indexOfShrinkingSubject];
		growingText = shrinkingTexts[indexOfShrinkingSubject];
		growingLinearColor = shrinkingLinearColors[indexOfShrinkingSubject];
		growingOpacity = shrinkingOpacities[indexOfShrinkingSubject];

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
	}
	else
	{
		extentOfGrowth = multiplierOfPerimeterExpansion;

		growingText = levelSelectorTextStyle;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[0];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorTextStyle.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[0]);
	growingTextBlock = levelSelectionTexts[0];
	growTime = 0;
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
			growingText.Size = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion;
			growingOffset = standardShadowOffset * multiplierOfOffset;
			growingLinearColor = FLinearColor(0, 0, 0, grownOpacity);
			growingOpacity = grownOpacity;
		}

		shrinkingOpacities.Add(growingOpacity);
		shrinkingLinearColors.Add(growingLinearColor);
		startingShrinkingOpacities.Add(growingOpacity);
		adjustedShrinkingOpacities.Add((1 - growingOpacity) / 2);
		shrinkingOffset.Add(growingOffset);
		startingShrinkingOffset.Add(growingOffset);
		adjustedShrinkingOffset.Add((0.003 - growingOffset) / 2);
		shrinkingTextBlocks.Add(growingTextBlock);
		shrinkingTexts.Add(growingText);
		shrinkingMargins.Add(growingMargin);
		shrinkingMarginsStartingPoints.Add(growingMargin);
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[0] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[0] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorTextStyle.Size - growingText.Size) / 2);
		shrinkingTimes.Add(0);
	}
}

void SSArcadeModeTitleScreen::PlayPressed_4()
{
	levelSelectionTexts[1]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_4()
{
	levelSelectionTexts[1]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[1]->SetPadding(levelSelectionMargins[1]);
	levelSelectionTexts[1]->SetFont(levelSelectorTextStyle);
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
	}
	OwningHUD->DisplayCurtains(4);
}
void SSArcadeModeTitleScreen::PlayHovered_4()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[1]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[1]);
		extentOfGrowth = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
		growingOffset = shrinkingOffset[indexOfShrinkingSubject];
		growingMargin = shrinkingMargins[indexOfShrinkingSubject];
		growingText = shrinkingTexts[indexOfShrinkingSubject];
		growingLinearColor = shrinkingLinearColors[indexOfShrinkingSubject];
		growingOpacity = shrinkingOpacities[indexOfShrinkingSubject];

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
	}
	else
	{
		extentOfGrowth = multiplierOfPerimeterExpansion;

		growingText = levelSelectorTextStyle;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[1];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorTextStyle.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[1]);
	growingTextBlock = levelSelectionTexts[1];
	growTime = 0;
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
			growingText.Size = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion;
			growingOffset = standardShadowOffset * multiplierOfOffset;
			growingLinearColor = FLinearColor(0, 0, 0, grownOpacity);
			growingOpacity = grownOpacity;
		}

		shrinkingOpacities.Add(growingOpacity);
		shrinkingLinearColors.Add(growingLinearColor);
		startingShrinkingOpacities.Add(growingOpacity);
		adjustedShrinkingOpacities.Add((1 - growingOpacity) / 2);
		shrinkingOffset.Add(growingOffset);
		startingShrinkingOffset.Add(growingOffset);
		adjustedShrinkingOffset.Add((0.003 - growingOffset) / 2);
		shrinkingTextBlocks.Add(growingTextBlock);
		shrinkingTexts.Add(growingText);
		shrinkingMargins.Add(growingMargin);
		shrinkingMarginsStartingPoints.Add(growingMargin);
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[1] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[1] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorTextStyle.Size - growingText.Size) / 2);
		shrinkingTimes.Add(0);
	}
}

void SSArcadeModeTitleScreen::PlayPressed_5()
{
	levelSelectionTexts[2]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_5()
{
	levelSelectionTexts[2]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[2]->SetPadding(levelSelectionMargins[2]);
	levelSelectionTexts[2]->SetFont(levelSelectorTextStyle);
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
	}
	OwningHUD->DisplayCurtains(5);
}
void SSArcadeModeTitleScreen::PlayHovered_5()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[2]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[2]);
		extentOfGrowth = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
		growingOffset = shrinkingOffset[indexOfShrinkingSubject];
		growingMargin = shrinkingMargins[indexOfShrinkingSubject];
		growingText = shrinkingTexts[indexOfShrinkingSubject];
		growingLinearColor = shrinkingLinearColors[indexOfShrinkingSubject];
		growingOpacity = shrinkingOpacities[indexOfShrinkingSubject];

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
	}
	else
	{
		extentOfGrowth = multiplierOfPerimeterExpansion;

		growingText = levelSelectorTextStyle;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[2];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorTextStyle.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[2]);
	growingTextBlock = levelSelectionTexts[2];
	growTime = 0;
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
			growingText.Size = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion;
			growingOffset = standardShadowOffset * multiplierOfOffset;
			growingLinearColor = FLinearColor(0, 0, 0, grownOpacity);
			growingOpacity = grownOpacity;
		}

		shrinkingOpacities.Add(growingOpacity);
		shrinkingLinearColors.Add(growingLinearColor);
		startingShrinkingOpacities.Add(growingOpacity);
		adjustedShrinkingOpacities.Add((1 - growingOpacity) / 2);
		shrinkingOffset.Add(growingOffset);
		startingShrinkingOffset.Add(growingOffset);
		adjustedShrinkingOffset.Add((0.003 - growingOffset) / 2);
		shrinkingTextBlocks.Add(growingTextBlock);
		shrinkingTexts.Add(growingText);
		shrinkingMargins.Add(growingMargin);
		shrinkingMarginsStartingPoints.Add(growingMargin);
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[2] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[2] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorTextStyle.Size - growingText.Size) / 2);
		shrinkingTimes.Add(0);
	}
}

void SSArcadeModeTitleScreen::PlayPressed_6()
{
	levelSelectionTexts[3]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_6()
{
	levelSelectionTexts[3]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[3]->SetPadding(levelSelectionMargins[3]);
	levelSelectionTexts[3]->SetFont(levelSelectorTextStyle);
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
	}
	OwningHUD->DisplayCurtains(6);
}
void SSArcadeModeTitleScreen::PlayHovered_6()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[3]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[3]);
		extentOfGrowth = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
		growingOffset = shrinkingOffset[indexOfShrinkingSubject];
		growingMargin = shrinkingMargins[indexOfShrinkingSubject];
		growingText = shrinkingTexts[indexOfShrinkingSubject];
		growingLinearColor = shrinkingLinearColors[indexOfShrinkingSubject];
		growingOpacity = shrinkingOpacities[indexOfShrinkingSubject];

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
	}
	else
	{
		extentOfGrowth = multiplierOfPerimeterExpansion;

		growingText = levelSelectorTextStyle;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[3];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorTextStyle.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[3]);
	growingTextBlock = levelSelectionTexts[3];
	growTime = 0;
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
			growingText.Size = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion;
			growingOffset = standardShadowOffset * multiplierOfOffset;
			growingLinearColor = FLinearColor(0, 0, 0, grownOpacity);
			growingOpacity = grownOpacity;
		}

		shrinkingOpacities.Add(growingOpacity);
		shrinkingLinearColors.Add(growingLinearColor);
		startingShrinkingOpacities.Add(growingOpacity);
		adjustedShrinkingOpacities.Add((1 - growingOpacity) / 2);
		shrinkingOffset.Add(growingOffset);
		startingShrinkingOffset.Add(growingOffset);
		adjustedShrinkingOffset.Add((0.003 - growingOffset) / 2);
		shrinkingTextBlocks.Add(growingTextBlock);
		shrinkingTexts.Add(growingText);
		shrinkingMargins.Add(growingMargin);
		shrinkingMarginsStartingPoints.Add(growingMargin);
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[3] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[3] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorTextStyle.Size - growingText.Size) / 2);
		shrinkingTimes.Add(0);
	}
}

void SSArcadeModeTitleScreen::PlayPressed_7()
{
	levelSelectionTexts[4]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_7()
{
	levelSelectionTexts[4]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[4]->SetPadding(levelSelectionMargins[4]);
	levelSelectionTexts[4]->SetFont(levelSelectorTextStyle);
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
	}
	OwningHUD->DisplayCurtains(7);
}
void SSArcadeModeTitleScreen::PlayHovered_7()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[4]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[4]);
		extentOfGrowth = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
		growingOffset = shrinkingOffset[indexOfShrinkingSubject];
		growingMargin = shrinkingMargins[indexOfShrinkingSubject];
		growingText = shrinkingTexts[indexOfShrinkingSubject];
		growingLinearColor = shrinkingLinearColors[indexOfShrinkingSubject];
		growingOpacity = shrinkingOpacities[indexOfShrinkingSubject];

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
	}
	else
	{
		extentOfGrowth = multiplierOfPerimeterExpansion;

		growingText = levelSelectorTextStyle;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[4];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorTextStyle.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[4]);
	growingTextBlock = levelSelectionTexts[4];
	growTime = 0;
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
			growingText.Size = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion;
			growingOffset = standardShadowOffset * multiplierOfOffset;
			growingLinearColor = FLinearColor(0, 0, 0, grownOpacity);
			growingOpacity = grownOpacity;
		}

		shrinkingOpacities.Add(growingOpacity);
		shrinkingLinearColors.Add(growingLinearColor);
		startingShrinkingOpacities.Add(growingOpacity);
		adjustedShrinkingOpacities.Add((1 - growingOpacity) / 2);
		shrinkingOffset.Add(growingOffset);
		startingShrinkingOffset.Add(growingOffset);
		adjustedShrinkingOffset.Add((0.003 - growingOffset) / 2);
		shrinkingTextBlocks.Add(growingTextBlock);
		shrinkingTexts.Add(growingText);
		shrinkingMargins.Add(growingMargin);
		shrinkingMarginsStartingPoints.Add(growingMargin);
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[4] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[4] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorTextStyle.Size - growingText.Size) / 2);
		shrinkingTimes.Add(0);
	}
}

void SSArcadeModeTitleScreen::PlayPressed_8()
{
	levelSelectionTexts[5]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_8()
{
	levelSelectionTexts[5]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[5]->SetPadding(levelSelectionMargins[5]);
	levelSelectionTexts[5]->SetFont(levelSelectorTextStyle);
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
	}
	OwningHUD->DisplayCurtains(8);
}
void SSArcadeModeTitleScreen::PlayHovered_8()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[5]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[5]);
		extentOfGrowth = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
		growingOffset = shrinkingOffset[indexOfShrinkingSubject];
		growingMargin = shrinkingMargins[indexOfShrinkingSubject];
		growingText = shrinkingTexts[indexOfShrinkingSubject];
		growingLinearColor = shrinkingLinearColors[indexOfShrinkingSubject];
		growingOpacity = shrinkingOpacities[indexOfShrinkingSubject];

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
	}
	else
	{
		extentOfGrowth = multiplierOfPerimeterExpansion;

		growingText = levelSelectorTextStyle;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[5];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorTextStyle.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[5]);
	growingTextBlock = levelSelectionTexts[5];
	growTime = 0;
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
			growingText.Size = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion;
			growingOffset = standardShadowOffset * multiplierOfOffset;
			growingLinearColor = FLinearColor(0, 0, 0, grownOpacity);
			growingOpacity = grownOpacity;
		}

		shrinkingOpacities.Add(growingOpacity);
		shrinkingLinearColors.Add(growingLinearColor);
		startingShrinkingOpacities.Add(growingOpacity);
		adjustedShrinkingOpacities.Add((1 - growingOpacity) / 2);
		shrinkingOffset.Add(growingOffset);
		startingShrinkingOffset.Add(growingOffset);
		adjustedShrinkingOffset.Add((0.003 - growingOffset) / 2);
		shrinkingTextBlocks.Add(growingTextBlock);
		shrinkingTexts.Add(growingText);
		shrinkingMargins.Add(growingMargin);
		shrinkingMarginsStartingPoints.Add(growingMargin);
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[5] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[5] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorTextStyle.Size - growingText.Size) / 2);
		shrinkingTimes.Add(0);
	}
}

void SSArcadeModeTitleScreen::PlayPressed_9()
{
	levelSelectionTexts[6]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_9()
{
	levelSelectionTexts[6]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[6]->SetPadding(levelSelectionMargins[6]);
	levelSelectionTexts[6]->SetFont(levelSelectorTextStyle);
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
	}
	OwningHUD->DisplayCurtains(9);
}
void SSArcadeModeTitleScreen::PlayHovered_9()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[6]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[6]);
		extentOfGrowth = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
		growingOffset = shrinkingOffset[indexOfShrinkingSubject];
		growingMargin = shrinkingMargins[indexOfShrinkingSubject];
		growingText = shrinkingTexts[indexOfShrinkingSubject];
		growingLinearColor = shrinkingLinearColors[indexOfShrinkingSubject];
		growingOpacity = shrinkingOpacities[indexOfShrinkingSubject];

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
	}
	else
	{
		extentOfGrowth = multiplierOfPerimeterExpansion;

		growingText = levelSelectorTextStyle;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[6];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorTextStyle.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[6]);
	growingTextBlock = levelSelectionTexts[6];
	growTime = 0;
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
			growingText.Size = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion;
			growingOffset = standardShadowOffset * multiplierOfOffset;
			growingLinearColor = FLinearColor(0, 0, 0, grownOpacity);
			growingOpacity = grownOpacity;
		}

		shrinkingOpacities.Add(growingOpacity);
		shrinkingLinearColors.Add(growingLinearColor);
		startingShrinkingOpacities.Add(growingOpacity);
		adjustedShrinkingOpacities.Add((1 - growingOpacity) / 2);
		shrinkingOffset.Add(growingOffset);
		startingShrinkingOffset.Add(growingOffset);
		adjustedShrinkingOffset.Add((0.003 - growingOffset) / 2);
		shrinkingTextBlocks.Add(growingTextBlock);
		shrinkingTexts.Add(growingText);
		shrinkingMargins.Add(growingMargin);
		shrinkingMarginsStartingPoints.Add(growingMargin);
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[6] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[6] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorTextStyle.Size - growingText.Size) / 2);
		shrinkingTimes.Add(0);
	}
}

void SSArcadeModeTitleScreen::PlayPressed_10()
{
	levelSelectionTexts[7]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_10()
{
	levelSelectionTexts[7]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[7]->SetPadding(levelSelectionMargins[7]);
	levelSelectionTexts[7]->SetFont(levelSelectorTextStyle);
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
	}
	OwningHUD->DisplayCurtains(10);
}
void SSArcadeModeTitleScreen::PlayHovered_10()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[7]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[7]);
		extentOfGrowth = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
		growingOffset = shrinkingOffset[indexOfShrinkingSubject];
		growingMargin = shrinkingMargins[indexOfShrinkingSubject];
		growingText = shrinkingTexts[indexOfShrinkingSubject];
		growingLinearColor = shrinkingLinearColors[indexOfShrinkingSubject];
		growingOpacity = shrinkingOpacities[indexOfShrinkingSubject];

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
	}
	else
	{
		extentOfGrowth = multiplierOfPerimeterExpansion;

		growingText = levelSelectorTextStyle;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[7];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorTextStyle.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[7]);
	growingTextBlock = levelSelectionTexts[7];
	growTime = 0;
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
			growingText.Size = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion;
			growingOffset = standardShadowOffset * multiplierOfOffset;
			growingLinearColor = FLinearColor(0, 0, 0, grownOpacity);
			growingOpacity = grownOpacity;
		}

		shrinkingOpacities.Add(growingOpacity);
		shrinkingLinearColors.Add(growingLinearColor);
		startingShrinkingOpacities.Add(growingOpacity);
		adjustedShrinkingOpacities.Add((1 - growingOpacity) / 2);
		shrinkingOffset.Add(growingOffset);
		startingShrinkingOffset.Add(growingOffset);
		adjustedShrinkingOffset.Add((0.003 - growingOffset) / 2);
		shrinkingTextBlocks.Add(growingTextBlock);
		shrinkingTexts.Add(growingText);
		shrinkingMargins.Add(growingMargin);
		shrinkingMarginsStartingPoints.Add(growingMargin);
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[7] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[7] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorTextStyle.Size - growingText.Size) / 2);
		shrinkingTimes.Add(0);
	}
}

void SSArcadeModeTitleScreen::PlayPressed_11()
{
	levelSelectionTexts[8]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_11()
{
	levelSelectionTexts[8]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[8]->SetPadding(levelSelectionMargins[8]);
	levelSelectionTexts[8]->SetFont(levelSelectorTextStyle);
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
	}
	OwningHUD->DisplayCurtains(11);
}
void SSArcadeModeTitleScreen::PlayHovered_11()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[8]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[8]);
		extentOfGrowth = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
		growingOffset = shrinkingOffset[indexOfShrinkingSubject];
		growingMargin = shrinkingMargins[indexOfShrinkingSubject];
		growingText = shrinkingTexts[indexOfShrinkingSubject];
		growingLinearColor = shrinkingLinearColors[indexOfShrinkingSubject];
		growingOpacity = shrinkingOpacities[indexOfShrinkingSubject];

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
	}
	else
	{
		extentOfGrowth = multiplierOfPerimeterExpansion;

		growingText = levelSelectorTextStyle;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[8];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorTextStyle.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[8]);
	growingTextBlock = levelSelectionTexts[8];
	growTime = 0;
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
			growingText.Size = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion;
			growingOffset = standardShadowOffset * multiplierOfOffset;
			growingLinearColor = FLinearColor(0, 0, 0, grownOpacity);
			growingOpacity = grownOpacity;
		}

		shrinkingOpacities.Add(growingOpacity);
		shrinkingLinearColors.Add(growingLinearColor);
		startingShrinkingOpacities.Add(growingOpacity);
		adjustedShrinkingOpacities.Add((1 - growingOpacity) / 2);
		shrinkingOffset.Add(growingOffset);
		startingShrinkingOffset.Add(growingOffset);
		adjustedShrinkingOffset.Add((0.003 - growingOffset) / 2);
		shrinkingTextBlocks.Add(growingTextBlock);
		shrinkingTexts.Add(growingText);
		shrinkingMargins.Add(growingMargin);
		shrinkingMarginsStartingPoints.Add(growingMargin);
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[8] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[8] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorTextStyle.Size - growingText.Size) / 2);
		shrinkingTimes.Add(0);
	}
}

void SSArcadeModeTitleScreen::PlayPressed_12()
{
	levelSelectionTexts[9]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_12()
{
	levelSelectionTexts[9]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[9]->SetPadding(levelSelectionMargins[9]);
	levelSelectionTexts[9]->SetFont(levelSelectorTextStyle);
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
	}
	OwningHUD->DisplayCurtains(12);
}
void SSArcadeModeTitleScreen::PlayHovered_12()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[9]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[9]);
		extentOfGrowth = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
		growingOffset = shrinkingOffset[indexOfShrinkingSubject];
		growingMargin = shrinkingMargins[indexOfShrinkingSubject];
		growingText = shrinkingTexts[indexOfShrinkingSubject];
		growingLinearColor = shrinkingLinearColors[indexOfShrinkingSubject];
		growingOpacity = shrinkingOpacities[indexOfShrinkingSubject];

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
	}
	else
	{
		extentOfGrowth = multiplierOfPerimeterExpansion;

		growingText = levelSelectorTextStyle;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[9];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorTextStyle.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[9]);
	growingTextBlock = levelSelectionTexts[9];
	growTime = 0;
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
			growingText.Size = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion;
			growingOffset = standardShadowOffset * multiplierOfOffset;
			growingLinearColor = FLinearColor(0, 0, 0, grownOpacity);
			growingOpacity = grownOpacity;
		}

		shrinkingOpacities.Add(growingOpacity);
		shrinkingLinearColors.Add(growingLinearColor);
		startingShrinkingOpacities.Add(growingOpacity);
		adjustedShrinkingOpacities.Add((1 - growingOpacity) / 2);
		shrinkingOffset.Add(growingOffset);
		startingShrinkingOffset.Add(growingOffset);
		adjustedShrinkingOffset.Add((0.003 - growingOffset) / 2);
		shrinkingTextBlocks.Add(growingTextBlock);
		shrinkingTexts.Add(growingText);
		shrinkingMargins.Add(growingMargin);
		shrinkingMarginsStartingPoints.Add(growingMargin);
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[9] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[9] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorTextStyle.Size - growingText.Size) / 2);
		shrinkingTimes.Add(0);
	}
}

void SSArcadeModeTitleScreen::PlayPressed_13()
{
	levelSelectionTexts[10]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_13()
{
	levelSelectionTexts[10]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[10]->SetPadding(levelSelectionMargins[10]);
	levelSelectionTexts[10]->SetFont(levelSelectorTextStyle);
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
	}
	OwningHUD->DisplayCurtains(13);
}
void SSArcadeModeTitleScreen::PlayHovered_13()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[10]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[10]);
		extentOfGrowth = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
		growingOffset = shrinkingOffset[indexOfShrinkingSubject];
		growingMargin = shrinkingMargins[indexOfShrinkingSubject];
		growingText = shrinkingTexts[indexOfShrinkingSubject];
		growingLinearColor = shrinkingLinearColors[indexOfShrinkingSubject];
		growingOpacity = shrinkingOpacities[indexOfShrinkingSubject];

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
	}
	else
	{
		extentOfGrowth = multiplierOfPerimeterExpansion;

		growingText = levelSelectorTextStyle;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[10];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorTextStyle.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[10]);
	growingTextBlock = levelSelectionTexts[10];
	growTime = 0;
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
			growingText.Size = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion;
			growingOffset = standardShadowOffset * multiplierOfOffset;
			growingLinearColor = FLinearColor(0, 0, 0, grownOpacity);
			growingOpacity = grownOpacity;
		}

		shrinkingOpacities.Add(growingOpacity);
		shrinkingLinearColors.Add(growingLinearColor);
		startingShrinkingOpacities.Add(growingOpacity);
		adjustedShrinkingOpacities.Add((1 - growingOpacity) / 2);
		shrinkingOffset.Add(growingOffset);
		startingShrinkingOffset.Add(growingOffset);
		adjustedShrinkingOffset.Add((0.003 - growingOffset) / 2);
		shrinkingTextBlocks.Add(growingTextBlock);
		shrinkingTexts.Add(growingText);
		shrinkingMargins.Add(growingMargin);
		shrinkingMarginsStartingPoints.Add(growingMargin);
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[10] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[10] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorTextStyle.Size - growingText.Size) / 2);
		shrinkingTimes.Add(0);
	}
}

void SSArcadeModeTitleScreen::PlayPressed_14()
{
	levelSelectionTexts[11]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_14()
{
	levelSelectionTexts[11]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[11]->SetPadding(levelSelectionMargins[11]);
	levelSelectionTexts[11]->SetFont(levelSelectorTextStyle);
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
	}
	OwningHUD->DisplayCurtains(14);
}
void SSArcadeModeTitleScreen::PlayHovered_14()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[11]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[11]);
		extentOfGrowth = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
		growingOffset = shrinkingOffset[indexOfShrinkingSubject];
		growingMargin = shrinkingMargins[indexOfShrinkingSubject];
		growingText = shrinkingTexts[indexOfShrinkingSubject];
		growingLinearColor = shrinkingLinearColors[indexOfShrinkingSubject];
		growingOpacity = shrinkingOpacities[indexOfShrinkingSubject];

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
	}
	else
	{
		extentOfGrowth = multiplierOfPerimeterExpansion;

		growingText = levelSelectorTextStyle;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[11];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorTextStyle.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[11]);
	growingTextBlock = levelSelectionTexts[11];
	growTime = 0;
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
			growingText.Size = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion;
			growingOffset = standardShadowOffset * multiplierOfOffset;
			growingLinearColor = FLinearColor(0, 0, 0, grownOpacity);
			growingOpacity = grownOpacity;
		}

		shrinkingOpacities.Add(growingOpacity);
		shrinkingLinearColors.Add(growingLinearColor);
		startingShrinkingOpacities.Add(growingOpacity);
		adjustedShrinkingOpacities.Add((1 - growingOpacity) / 2);
		shrinkingOffset.Add(growingOffset);
		startingShrinkingOffset.Add(growingOffset);
		adjustedShrinkingOffset.Add((0.003 - growingOffset) / 2);
		shrinkingTextBlocks.Add(growingTextBlock);
		shrinkingTexts.Add(growingText);
		shrinkingMargins.Add(growingMargin);
		shrinkingMarginsStartingPoints.Add(growingMargin);
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[11] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[11] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorTextStyle.Size - growingText.Size) / 2);
		shrinkingTimes.Add(0);
	}
}

void SSArcadeModeTitleScreen::PlayPressed_15()
{
	levelSelectionTexts[12]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_15()
{
	levelSelectionTexts[12]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[12]->SetPadding(levelSelectionMargins[12]);
	levelSelectionTexts[12]->SetFont(levelSelectorTextStyle);
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
	}
	OwningHUD->DisplayCurtains(15);
}
void SSArcadeModeTitleScreen::PlayHovered_15()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[12]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[12]);
		extentOfGrowth = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
		growingOffset = shrinkingOffset[indexOfShrinkingSubject];
		growingMargin = shrinkingMargins[indexOfShrinkingSubject];
		growingText = shrinkingTexts[indexOfShrinkingSubject];
		growingLinearColor = shrinkingLinearColors[indexOfShrinkingSubject];
		growingOpacity = shrinkingOpacities[indexOfShrinkingSubject];

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
	}
	else
	{
		extentOfGrowth = multiplierOfPerimeterExpansion;

		growingText = levelSelectorTextStyle;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[12];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorTextStyle.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[12]);
	growingTextBlock = levelSelectionTexts[12];
	growTime = 0;
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
			growingText.Size = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion;
			growingOffset = standardShadowOffset * multiplierOfOffset;
			growingLinearColor = FLinearColor(0, 0, 0, grownOpacity);
			growingOpacity = grownOpacity;
		}

		shrinkingOpacities.Add(growingOpacity);
		shrinkingLinearColors.Add(growingLinearColor);
		startingShrinkingOpacities.Add(growingOpacity);
		adjustedShrinkingOpacities.Add((1 - growingOpacity) / 2);
		shrinkingOffset.Add(growingOffset);
		startingShrinkingOffset.Add(growingOffset);
		adjustedShrinkingOffset.Add((0.003 - growingOffset) / 2);
		shrinkingTextBlocks.Add(growingTextBlock);
		shrinkingTexts.Add(growingText);
		shrinkingMargins.Add(growingMargin);
		shrinkingMarginsStartingPoints.Add(growingMargin);
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[12] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[12] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorTextStyle.Size - growingText.Size) / 2);
		shrinkingTimes.Add(0);
	}
}

void SSArcadeModeTitleScreen::PlayPressed_16()
{
	levelSelectionTexts[13]->SetColorAndOpacity(FColor::White);
}
void SSArcadeModeTitleScreen::PlayReleased_16()
{
	levelSelectionTexts[13]->SetColorAndOpacity(FColor::Orange);
	levelSelectionBoxes[13]->SetPadding(levelSelectionMargins[13]);
	levelSelectionTexts[13]->SetFont(levelSelectorTextStyle);
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
	}
	OwningHUD->DisplayCurtains(16);
}
void SSArcadeModeTitleScreen::PlayHovered_16()
{
	if (shrinkingBoxes.Find(levelSelectionBoxes[13]) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(levelSelectionBoxes[13]);
		extentOfGrowth = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion / shrinkingTexts[indexOfShrinkingSubject].Size;
		growingOffset = shrinkingOffset[indexOfShrinkingSubject];
		growingMargin = shrinkingMargins[indexOfShrinkingSubject];
		growingText = shrinkingTexts[indexOfShrinkingSubject];
		growingLinearColor = shrinkingLinearColors[indexOfShrinkingSubject];
		growingOpacity = shrinkingOpacities[indexOfShrinkingSubject];

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
	}
	else
	{
		extentOfGrowth = multiplierOfPerimeterExpansion;

		growingText = levelSelectorTextStyle;
		growingOffset = standardShadowOffset;
		growingMargin = levelSelectionMargins[13];
		growingLinearColor = FLinearColor(0, 0, 0, standardOpacity);
		growingOpacity = standardOpacity;
	}

	startingOpacity = growingOpacity;
	adjustedGrowingOpacity = (grownOpacity - startingOpacity) / 2;
	startingMargin = growingMargin;
	startingFontSize = levelSelectorTextStyle.Size;
	startingShadowOffset = growingOffset;
	adjustedGrowingOffset = ((multiplierOfOffset * standardShadowOffset) - growingOffset) / 2;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(levelSelectionBoxes[13]);
	growingTextBlock = levelSelectionTexts[13];
	growTime = 0;
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
			growingText.Size = levelSelectorTextStyle.Size * multiplierOfPerimeterExpansion;
			growingOffset = standardShadowOffset * multiplierOfOffset;
			growingLinearColor = FLinearColor(0, 0, 0, grownOpacity);
			growingOpacity = grownOpacity;
		}

		shrinkingOpacities.Add(growingOpacity);
		shrinkingLinearColors.Add(growingLinearColor);
		startingShrinkingOpacities.Add(growingOpacity);
		adjustedShrinkingOpacities.Add((1 - growingOpacity) / 2);
		shrinkingOffset.Add(growingOffset);
		startingShrinkingOffset.Add(growingOffset);
		adjustedShrinkingOffset.Add((0.003 - growingOffset) / 2);
		shrinkingTextBlocks.Add(growingTextBlock);
		shrinkingTexts.Add(growingText);
		shrinkingMargins.Add(growingMargin);
		shrinkingMarginsStartingPoints.Add(growingMargin);
		shrinkingAdjustedMarginSizesX.Add((levelSelectionMargins[13] - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((levelSelectionMargins[13] - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((levelSelectorTextStyle.Size - growingText.Size) / 2);
		shrinkingTimes.Add(0);
	}
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION