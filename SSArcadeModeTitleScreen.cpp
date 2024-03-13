#include "SSArcadeModeTitleScreen.h"
#include "SlateOptMacros.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"

FMargin CalculateTitlePosition(FVector2D viewportSize)
{//your sub titles will use this same positioning but the a different text style
	float leftPad = viewportSize.X * 0.1;
	float topPad = viewportSize.Y * 0.1;
	float rightPad = viewportSize.X * 0.4;
	float bottomPad = viewportSize.Y * 0.75;

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

FMargin CalculateMenuTextPosition(FVector2D viewportSize, int textIndex)
{
	float leftPad = viewportSize.X * 0.25;
	float topPad = viewportSize.Y * (0.35 + textIndex);
	float rightPad = viewportSize.X * 0.45;
	float bottomPad = viewportSize.Y * (0.575 - textIndex);

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
	float sizeX = (adjustedSizeX * sin(9.428 * (growTime - 0.167))) + adjustedSizeX;
	float sizeY = (adjustedSizeY * sin(9.428 * (growTime - 0.167))) + adjustedSizeY;
	newMargin.Left += sizeX;
	newMargin.Top += sizeY;
	newMargin.Right += sizeX;
	newMargin.Bottom += sizeY;

	return newMargin;
}

FMargin SSArcadeModeTitleScreen::ShrinkMargin(FMargin inMargin, int marginIndex)
{
	FMargin newMargin = inMargin;
	float sizeX = (shrinkingAdjustedMarginSizesX[marginIndex] * sin(9.428 * (shrinkingTimes[marginIndex] - 0.167))) + shrinkingAdjustedMarginSizesX[marginIndex];
	float sizeY = (shrinkingAdjustedMarginSizesY[marginIndex] * sin(9.428 * (shrinkingTimes[marginIndex] - 0.167))) + shrinkingAdjustedMarginSizesY[marginIndex];
	newMargin.Left += sizeX;
	newMargin.Top += sizeY;
	newMargin.Right += sizeX;
	newMargin.Bottom += sizeY;

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
	playTextStyleProxy = playTextStyle;
	levelSelectorTextStyle = FCoreStyle::Get().GetFontStyle("Roboto");
	levelSelectorTextStyle.Size = 0.04 * adjustedViewportSize.Y;

	//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, FString::SanitizeFloat(adjustedViewportSize.Y));

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
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::Orange)
		.Font(menuTextStyle)
		.Text(FText::FromString("Play"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1));

	playMargin = CalculateMenuTextPosition(adjustedViewportSize, 0);
	playMarginProxy = playMargin;

	playBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(playMargin)
		[
			SNew(SButton)
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
		.Padding(CalculateMenuTextPosition(adjustedViewportSize, 1))
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
				.ShadowColorAndOpacity(FLinearColor(0,0,0,1))
			]
		];

	mainMenuOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateMenuTextPosition(adjustedViewportSize, 2))
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
				.ShadowColorAndOpacity(FLinearColor(0,0,0,1))
			]
		];

	mainMenuOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateMenuTextPosition(adjustedViewportSize, 3))
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
				.ShadowColorAndOpacity(FLinearColor(0,0,0,1))
			]
		];

	levelSelectionOverlay = SNew(SOverlay);
	for (int a = 2; a < 16; a++)
	{
		levelSelectionOverlay->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateLevelSelectionButtonsPositions(adjustedViewportSize, a))
			[
				SNew(SButton)
				.ContentPadding(FMargin())
				.IsEnabled(true)//this will play into the save file stuff along with the options.. ? right
				[
					SNew(STextBlock)//STextBlock supports "shadow" functionality. if this shadows your text and not the block you can create a dark shadow to emphasize the characters against the light background
					.Justification(ETextJustify::Center)
					.ColorAndOpacity(FColor::Orange)
					.Font(levelSelectorTextStyle)
					.Text(FText::FromString(FString::FromInt(a + 1)))//this might not work Im not sure FString converts to string
				]
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
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				frameColorOverlay.ToSharedRef()
			]

			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				backgroundOverlay.ToSharedRef()
			]

			+SOverlay::Slot()
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
		*shrinkingMargins[a] = ShrinkMargin(shrinkingMarginsStartingPoints[a], a);
		shrinkingFontSizes[a] = shrinkingFontSizesStartingPoints[a] + ((shrinkingAdjustedFontSizes[a] * sin(9.428 * (shrinkingTimes[a] - 0.167))) + shrinkingAdjustedFontSizes[a]);

		shrinkingBoxes[a]->SetPadding(*shrinkingMargins[a]);
		shrinkingTexts[a]->Size = shrinkingFontSizes[a];
		shrinkingTextBlocks[a]->SetFont(*shrinkingTexts[a]);

		if (shrinkingTimes[a] + InDeltaTime >= 0.33)
		{
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
		*growingMargin = GrowMargin(startingMargin);
		growingFontSize = startingFontSize + ((adjustedStartingFontSize * sin(9.428 * (growTime - 0.167))) + adjustedStartingFontSize);

		growingBox[0]->SetPadding(*growingMargin);
		growingText->Size = growingFontSize;
		growingTextBlock->SetFont(*growingText);

		if (growTime + InDeltaTime >= 0.33)
		{
			grownBox.Add(growingBox[0]);

			growingBox.RemoveAt(0);
		}
	}
}

void SSArcadeModeTitleScreen::OnPlayHovered()
{
	if (shrinkingBoxes.Find(playBox) + 1)//now make the shadow expand and shift
	{
		extentOfGrowth = playTextStyle.Size * 1.225 / playTextStyleProxy.Size;
		startingMargin = playMarginProxy;
		startingFontSize = playTextStyleProxy.Size;

		indexOfShrinkingSubject = shrinkingBoxes.Find(playBox);

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
		extentOfGrowth = 1.225;
		startingMargin = playMargin;
		startingFontSize = playTextStyle.Size;
	}
	growingMargin = &playMarginProxy;
	adjustedSizeX = CalculateGrownMarginX(startingMargin);
	adjustedSizeY = CalculateGrownMarginY(startingMargin);
	adjustedStartingFontSize = ((startingFontSize * extentOfGrowth) - startingFontSize) / 2;
	growingBox.Add(playBox);
	growingText = &playTextStyleProxy;
	growingTextBlock = playText;
	growTime = 0;
}

void SSArcadeModeTitleScreen::OnPlayUnHovered()
{
	if (growingBox.Num() > 0)
	{
		shrinkingBoxes.Add(growingBox[0]);

		growingBox.RemoveAt(0);
	}
	else
	{
		shrinkingBoxes.Add(grownBox[0]);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, FString::SanitizeFloat((playMargin - *growingMargin).Left) + ", " + FString::SanitizeFloat((playMargin - *growingMargin).Top) + ", " + FString::SanitizeFloat((playMargin - *growingMargin).Right) + ", " + FString::SanitizeFloat((playMargin - *growingMargin).Bottom));
	shrinkingTextBlocks.Add(growingTextBlock);
	shrinkingTexts.Add(growingText);
	shrinkingMargins.Add(growingMargin);
	shrinkingMarginsStartingPoints.Add(*growingMargin);
	shrinkingAdjustedMarginSizesX.Add((playMargin - *growingMargin).Left / 2);
	shrinkingAdjustedMarginSizesY.Add((playMargin - *growingMargin).Top / 2);
	shrinkingFontSizes.Add(growingFontSize);
	shrinkingFontSizesStartingPoints.Add(growingFontSize);
	shrinkingAdjustedFontSizes.Add((playTextStyle.Size - playTextStyleProxy.Size) / 2);
	shrinkingTimes.Add(0);
}

void SSArcadeModeTitleScreen::OnPlayPressed()
{
	playText->SetColorAndOpacity(FColor::White);
}

void SSArcadeModeTitleScreen::OnPlayReleased()
{
	playText->SetColorAndOpacity(FColor::Orange);
	masterOverlay->RemoveSlot(0);
	masterOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			levelSelectionOverlay.ToSharedRef()
		];
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

END_SLATE_FUNCTION_BUILD_OPTIMIZATION