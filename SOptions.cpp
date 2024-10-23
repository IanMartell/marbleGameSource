// Fill out your copyright notice in the Description page of Project Settings.


#include "SOptions.h"
#include "SlateOptMacros.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "Components/AudioComponent.h"
#include "Widgets/Input/SEditableText.h"
#include "Widgets/SToolTip.h"
#include "Widgets/Input/SCheckBox.h"
#include "InputCoreTypes.h"
#include "GameFramework/GameUserSettings.h"

FMargin SOptions::CalculateTitlePosition(FVector2D funcViewportSize)
{//your sub titles will use this same positioning but the a different text style
	float leftPad = funcViewportSize.X * 0.1;
	float topPad = funcViewportSize.Y * 0.1;
	float rightPad = funcViewportSize.X * 0.1;
	float bottomPad = funcViewportSize.Y * 0.75;

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

FMargin SOptions::CalculateMenuTextPos(int textIndex, int numberOfLetters)
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

FMargin SOptions::CalculateBackButtonPosition(FVector2D paramViewportSize)
{
	float leftPad = paramViewportSize.X * 0.1;
	float topPad = paramViewportSize.Y * 0.75;
	float rightPad = paramViewportSize.X * 0.75;
	float bottomPad = paramViewportSize.Y * 0.175;

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

FMargin SOptions::CalculateLeftColumnPos(int textIndex, int numberOfLetters)
{
	float fOne = ((adjustedViewportSize.X - adjustedViewportSize.Y) / 2) + (adjustedViewportSize.Y * 0.25);
	//float fThree = ((adjustedViewportSize.X - adjustedViewportSize.Y) / 2) + ((adjustedViewportSize.Y / 10) * 5);
	float fTwo = FMath::DivideAndRoundUp(numberOfLetters, 5);
	float leftPad = fOne - ((adjustedViewportSize.Y / 10) * fTwo);
	float topPad = adjustedViewportSize.Y * (0.35 + (0.1 * textIndex));
	float rightPad = adjustedViewportSize.X - (leftPad + ((adjustedViewportSize.Y / 5) * fTwo));
	float bottomPad = adjustedViewportSize.Y * (0.575 - (0.1 * textIndex));

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

FMargin SOptions::CalculateRightColumnPos(int textIndex, int numberOfLetters)
{
	float fOne = ((adjustedViewportSize.X - adjustedViewportSize.Y) / 2) + (adjustedViewportSize.Y * 0.75);
	//float fThree = ((adjustedViewportSize.X - adjustedViewportSize.Y) / 2) + ((adjustedViewportSize.Y / 10) * 5);
	float fTwo = FMath::DivideAndRoundUp(numberOfLetters, 5);
	float leftPad = fOne - ((adjustedViewportSize.Y / 10) * fTwo);
	float topPad = adjustedViewportSize.Y * (0.35 + (0.1 * textIndex));
	float rightPad = adjustedViewportSize.X - (leftPad + ((adjustedViewportSize.Y / 5) * fTwo));
	float bottomPad = adjustedViewportSize.Y * (0.575 - (0.1 * textIndex));

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

FMargin SOptions::CalculateMiddleColumnPos(int textIndex)
{
	float fOne = ((adjustedViewportSize.X - adjustedViewportSize.Y) / 2) + (adjustedViewportSize.Y * 0.05);
	float leftPad = fOne;
	float topPad = adjustedViewportSize.Y * (0.1 + (0.1 * textIndex));
	float rightPad = fOne;
	float bottomPad = adjustedViewportSize.Y * (.82 - (0.1 * textIndex));

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

FMargin SOptions::TwinButtonsCenter(int verticleIndex, int buttonIndex)
{
	float fOne = ((adjustedViewportSize.X - adjustedViewportSize.Y) / 2) + (adjustedViewportSize.Y * 0.4);
	float leftPad = fOne + (adjustedViewportSize.Y * (buttonIndex * 0.125));
	float topPad = adjustedViewportSize.Y * (0.35 + (0.1 * verticleIndex));
	float rightPad = fOne + (adjustedViewportSize.Y * (((buttonIndex + 1) % 2) * 0.125));
	float bottomPad = adjustedViewportSize.Y * (0.575 - (0.1 * verticleIndex));

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

FMargin SOptions::CalculateCheckBoxPos(int textIndex)
{
	float fOne = (adjustedViewportSize.X - adjustedViewportSize.Y) / 2;
	float leftPad = fOne + (adjustedViewportSize.Y * 0.675);
	float topPad = adjustedViewportSize.Y * (0.35 + (0.1 * textIndex));
	float rightPad = fOne + (adjustedViewportSize.Y * 0.25);
	float bottomPad = adjustedViewportSize.Y * (0.575 - (0.1 * textIndex));

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

FMargin SOptions::GrowMargin(FMargin inMargin)
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

FMargin SOptions::ShrinkMargin(FMargin inMargin, int marginIndex)
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

FMargin SOptions::GrownMargin(FMargin inMargin)
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


float SOptions::CalculateGrownMarginX(FMargin inMargin)
{
	float sizeX = adjustedViewportSize.X - (inMargin.Left + inMargin.Right);
	float newSizeX = ((sizeX - (extentOfGrowth * sizeX)) / 2) / 2;

	return newSizeX;
}

float SOptions::CalculateGrownMarginY(FMargin inMargin)
{
	float sizeY = adjustedViewportSize.Y - (inMargin.Top + inMargin.Bottom);
	float newSizeY = ((sizeY - (extentOfGrowth * sizeY)) / 2) / 2;

	return newSizeY;
}

void SOptions::PlayChordToActiveNote()
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
void SOptions::Construct(const FArguments& InArgs)
{
	SetCanTick(true);
	bCanSupportFocus = true;
	currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));
	makeSave = false;

	OwningHUD = InArgs._OwningHUD;
	playerOnePlayerController = InArgs._playerOnePlayerController;
	standardWorldContextObject = InArgs._standardWorldContextObject;
	hoverGrowAudioComponents = InArgs._hoverGrowAudioComponents;
	hoverShrinkAudioComponents = InArgs._hoverShrinkAudioComponents;
	purpleLullabyAudioComponents = InArgs._purpleLullabyAudioComponents;
	songAudioComponents = InArgs._songAudioComponents;
	gameFrameColor_SMUI = InArgs._gameFrameColor_SMUI;
	songPlayingIndex = InArgs._songPlayingIndex;
	songCycles = InArgs._songCycles;

	gameFrameColor_SB = new FSlateBrush();
	gameFrameColor_SB->SetResourceObject(gameFrameColor_SMUI);

	GEngine->GameViewport->GetViewportSize(viewportSize);
	int32 X = FGenericPlatformMath::FloorToInt(viewportSize.X);
	int32 Y = FGenericPlatformMath::FloorToInt(viewportSize.Y);
	DPIScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(X, Y));
	adjustedViewportSize = (1 / DPIScale) * viewportSize;

	titleFont = FCoreStyle::Get().GetFontStyle("EmbossedText");
	titleFont.Size = 0.06 * adjustedViewportSize.Y;
	subTitleFont = FCoreStyle::Get().GetFontStyle("Roboto");
	subTitleFont.Size = 0.05 * adjustedViewportSize.Y;
	menuFont = FCoreStyle::Get().GetFontStyle("Roboto");
	menuFont.Size = 0.04 * adjustedViewportSize.Y;
	textFont = FCoreStyle::Get().GetFontStyle("Roboto");
	textFont.Size = 0.02 * adjustedViewportSize.Y;

	standardShadowOffset = 0.003;
	standardOpacity = 1.0;
	grownOpacity = 0.6;
	multiplierOfOffset = 4;
	multiplierOfPerimeterExpansion = 1.225;

	audioMargin = CalculateMenuTextPos(0, 4);
	graphicsMargin = CalculateMenuTextPos(1, 7);
	controlsMargin = CalculateMenuTextPos(2, 7);
	creditsMargin = CalculateMenuTextPos(3, 7);
	backMargin = CalculateBackButtonPosition(adjustedViewportSize);

	transparentButtonStyle = new FButtonStyle();
	transparentButtonStyle->SetNormalPadding(FMargin());

	songTextColors = { FColor::Orange, FColor::Red, FColor::Silver };

	if (!songAudioComponents[songPlayingIndex]->IsPlaying() && songCycles[songPlayingIndex] == 1)
	{
		songCycles[songPlayingIndex] = 0;
		OwningHUD->songCycles[songPlayingIndex] = 0;
	}

	childrensCornerNotes = { 8, 11, 12, 13, 8, 11, 13, 12, 7, 11, 12, 14, 9, 10, 14, 13, 8, 11, 13, 15, 10, 11, 15, 14, 9, 11, 14, 16, 9, 14, 16, 15, 11, 13, 15, 18, 13, 15, 18, 19, 13, 15, 19, 18, 13, 15, 18, 17, 13, 15, 17, 16, 13, 15, 16, 15, 11, 13, 15, 14, 11, 13, 14, 13, 10, 11, 13, 12, 9, 11, 12, 15, 10, 13, 15, 16, 11, 13, 16, 13, 9, 11, 13, 12, 9, 11, 12, 11, 8, 9, 11, 10, 7, 8, 10, 0, 4, 5, 6, 7, 9, 11, 12, 13, 12, 11, 9, 7, 6, 5, 4, 0, 4, 5, 6, 7, 9, 11, 12, 13, 12, 11, 9, 7, 6, 5, 4, 0, 4, 5, 6, 7, 22, 11, 12, 13, 12, 11, 9, 7, 6, 5, 4, 0, 4, 5, 6, 7, 22, 11, 12, 13, 12, 11, 10, 7, 6, 5, 4 };
	childrensCornerIndex = -1;

	audioCycleTracker = 0;

	replaceKey = false;
	keyToReplace = -1;

	audioText = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::Orange)
		.Font(menuFont)
		.Text(FText::FromString("Audio"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	audioBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(audioMargin)
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SOptions::OnAudioPressed)
				.OnReleased(this, &SOptions::OnAudioReleased)
				.OnHovered(this, &SOptions::OnAudioHovered)
				.OnUnhovered(this, &SOptions::OnAudioUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					audioText.ToSharedRef()
				]
		];

	graphicsText = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::Orange)
		.Font(menuFont)
		.Text(FText::FromString("Graphics"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	graphicsBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(graphicsMargin)
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SOptions::OnGraphicsPressed)
				.OnReleased(this, &SOptions::OnGraphicsReleased)
				.OnHovered(this, &SOptions::OnGraphicsHovered)
				.OnUnhovered(this, &SOptions::OnGraphicsUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					graphicsText.ToSharedRef()
				]
		];

	controlsText = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::Orange)
		.Font(menuFont)
		.Text(FText::FromString("Controls"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	controlsBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(controlsMargin)
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SOptions::OnControlsPressed)
				.OnReleased(this, &SOptions::OnControlsReleased)
				.OnHovered(this, &SOptions::OnControlsHovered)
				.OnUnhovered(this, &SOptions::OnControlsUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					controlsText.ToSharedRef()
				]
		];

	creditsText = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::Orange)
		.Font(menuFont)
		.Text(FText::FromString("Songs"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	creditsBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(creditsMargin)
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SOptions::OnCreditsPressed)
				.OnReleased(this, &SOptions::OnCreditsReleased)
				.OnHovered(this, &SOptions::OnCreditsHovered)
				.OnUnhovered(this, &SOptions::OnCreditsUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					creditsText.ToSharedRef()
				]
		];


	mainOptionsOverlay = SNew(SOverlay);
	mainOptionsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateTitlePosition(adjustedViewportSize))
		[
			SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(subTitleFont)
				.Text(FText::FromString("Options"))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
		];

	backText = SNew(STextBlock);
	backText->SetJustification(ETextJustify::Center);
	backText->SetColorAndOpacity(FColor::Orange);
	backText->SetFont(menuFont);
	backText->SetText(FText::FromString("Back"));
	backText->SetShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003));
	backText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, 1));

	toMenuBackBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(backMargin)
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SOptions::OnBackToMenuPressed)
				.OnReleased(this, &SOptions::OnBackToMenuReleased)
				.OnHovered(this, &SOptions::OnBackToMenuHovered)
				.OnUnhovered(this, &SOptions::OnBackToMenuUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					backText.ToSharedRef()
				]
		];

	mainOptionsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			audioBox.ToSharedRef()
		];

	mainOptionsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			graphicsBox.ToSharedRef()
		];

	mainOptionsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			controlsBox.ToSharedRef()
		];
	//when new controls are bound check if inGame and if so have STestWidgetThree reload the save file
	//by figuring out how to rebind the "click" button on your mouse you may find some insight on how to rebind "click" to a gamepad. If thats the case you will then only need to figure out how to bind the cursor to a joystick.
	//when it comes to the options interface for rebindings just stack the keyboard bindings on top of the controller bindings. Then just do a check to make sure whatever binding your swapping to is a key/mouse binding if your switching keyboard bindings and the same for controller bindings
	// I just noticed the space key seems to affect buttons!! is this a development?
	// you can do a little more hunting but it appears for mouse cursor controls your only going to ever be able to bind them to the mouse. However it does appear there are ways to traverse the SButtons using a keyboard. if true would this also work for a controller? maybe there arent good ways to use SButtons without a mouse but youd think there would be
	//I dont need to support non mouse interaction, I just need to make sure if a mouse isn't present: there aren't any glitches, the consumer is informed a mouse/track pad is required, and its as easy as possible to connect a mouse/trackpad from there. 
	//I will also need to confirm the game works automatically with a track pad as it would a mouse, it should but double check
	//I should continue to support a keyboard key as a pause key but I should also a mouse button as a pause trigger so the game can be played entirely with a mouse
	//I will also need to double check how a gamepad interacts with this game. maybe do this last so you can backup and upload before leaving your apt again.

	mainOptionsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			creditsBox.ToSharedRef()
		];

	mainOptionsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			toMenuBackBox.ToSharedRef()
		];

	firstFloorBackBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(backMargin)
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SOptions::OnBackFloorOnePressed)
				.OnReleased(this, &SOptions::OnBackFloorOneReleased)
				.OnHovered(this, &SOptions::OnBackFloorOneHovered)
				.OnUnhovered(this, &SOptions::OnBackFloorOneUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					backText.ToSharedRef()
				]
		];

	masterTextBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateLeftColumnPos(0, 1))
		[
			SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(menuFont)
				.Text(FText::FromString("Master"))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
		];

	masterBackgroundBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateRightColumnPos(0, 1))
		[
			SNew(SImage)
				.Image(gameFrameColor_SB)
		];

	masterEditableTextBox = SNew(SEditableText)
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FLinearColor::White)
		.Font(menuFont)
		.SelectAllTextWhenFocused(true)
		.Text(FText::FromString(FString::FromInt(currentSave->GetMaster())))
		.OnTextCommitted(FOnTextCommitted::CreateSP(this, &SOptions::OnMasterCommitted));

	masterInteractiveBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateRightColumnPos(0, 1))
		[
			masterEditableTextBox.ToSharedRef()
		];

	musicTextBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateLeftColumnPos(1, 1))
		[
			SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(menuFont)
				.Text(FText::FromString("Music"))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
		];

	musicBackgroundBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateRightColumnPos(1, 1))
		[
			SNew(SImage)
				.Image(gameFrameColor_SB)
		];

	musicEditableTextBox = SNew(SEditableText)
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FLinearColor::White)
		.Font(menuFont)
		.SelectAllTextWhenFocused(true)
		.Text(FText::FromString(FString::FromInt(currentSave->GetMusic())))
		.OnTextCommitted(FOnTextCommitted::CreateSP(this, &SOptions::OnMusicCommitted));

	musicInteractiveBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateRightColumnPos(1, 1))
		[
			musicEditableTextBox.ToSharedRef()
		];

	atmosphereTextBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateLeftColumnPos(2, 6))
		[
			SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(menuFont)
				.Text(FText::FromString("Atmosphere"))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
		];

	atmosphereBackgroundBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateRightColumnPos(2, 1))
		[
			SNew(SImage)
				.Image(gameFrameColor_SB)
		];

	atmosphereEditableTextBox = SNew(SEditableText)
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FLinearColor::White)
		.Font(menuFont)
		.SelectAllTextWhenFocused(true)
		.Text(FText::FromString(FString::FromInt(currentSave->GetAtmosphere())))
		.OnTextCommitted(FOnTextCommitted::CreateSP(this, &SOptions::OnAtmosphereCommitted));

	atmosphereInteractiveBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateRightColumnPos(2, 1))
		[
			atmosphereEditableTextBox.ToSharedRef()
		];

	sfxTextBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateLeftColumnPos(3, 1))
		[
			SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(menuFont)
				.Text(FText::FromString("SFX"))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
		];

	sfxBackgroundBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateRightColumnPos(3, 1))
		[
			SNew(SImage)
				.Image(gameFrameColor_SB)
		];

	sfxEditableTextBox = SNew(SEditableText)
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FLinearColor::White)
		.Font(menuFont)
		.SelectAllTextWhenFocused(true)
		.Text(FText::FromString(FString::FromInt(currentSave->GetSFX())))
		.OnTextCommitted(FOnTextCommitted::CreateSP(this, &SOptions::OnSFXCommitted));

	sfxInteractiveBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateRightColumnPos(3, 1))
		[
			sfxEditableTextBox.ToSharedRef()
		];

	audioOverlay = SNew(SOverlay);

	audioOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			masterTextBox.ToSharedRef()
		];
	audioOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			masterBackgroundBox.ToSharedRef()
		];
	audioOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			masterInteractiveBox.ToSharedRef()
		];

	audioOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			musicTextBox.ToSharedRef()
		];
	audioOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			musicBackgroundBox.ToSharedRef()
		];
	audioOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			musicInteractiveBox.ToSharedRef()
		];

	audioOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			atmosphereTextBox.ToSharedRef()
		];
	audioOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			atmosphereBackgroundBox.ToSharedRef()
		];
	audioOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			atmosphereInteractiveBox.ToSharedRef()
		];

	audioOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			sfxTextBox.ToSharedRef()
		];
	audioOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			sfxBackgroundBox.ToSharedRef()
		];
	audioOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			sfxInteractiveBox.ToSharedRef()
		];

	audioOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			firstFloorBackBox.ToSharedRef()
		];

	keyboardBindingsTextBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateLeftColumnPos(-3, 15))
		[
			SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(subTitleFont)
				.Text(FText::FromString("Keyboard Bindings"))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
		];

	pause1TextBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateLeftColumnPos(-2, 1))
		[
			SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(menuFont)
				.Text(FText::FromString("Pause 1"))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
		];

	pauseKeyBackground = SNew(SImage)
		.Image(gameFrameColor_SB);

	pauseKeyBackgroundBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateRightColumnPos(-2, 6))
		[
			pauseKeyBackground.ToSharedRef()
		];

	pauseKeyText = SNew(STextBlock)
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::Orange)
		.Font(menuFont)
		.Text(currentSave->GetPauseKey().GetDisplayName())//if this doesnt work I can create a struct to store the name of the key along with the EKey
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1));

	pauseKeyButton = SNew(SButton)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.OnPressed(this, &SOptions::OnPauseBindingResetPressed)
		.OnReleased(this, &SOptions::OnPauseBindingResetReleased)
		.ContentPadding(FMargin())
		.IsEnabled(true)
		.ButtonColorAndOpacity(FLinearColor::Transparent)
		.ButtonStyle(transparentButtonStyle)
		[
			pauseKeyText.ToSharedRef()
		];

	pauseKeyBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateRightColumnPos(-2, 6))
		[
			pauseKeyButton.ToSharedRef()
		];

	pause2TextBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateLeftColumnPos(-1, 1))
		[
			SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(menuFont)
				.Text(FText::FromString("Pause 2"))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
		];

	pauseMouseBackground = SNew(SImage)
		.Image(gameFrameColor_SB);

	pauseMouseBackgroundBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateRightColumnPos(-1, 6))
		[
			pauseMouseBackground.ToSharedRef()
		];

	pauseMouseText = SNew(STextBlock)
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::Orange)
		.Font(menuFont)
		.Text(currentSave->GetPauseMouse().GetDisplayName())//if this doesnt work I can create a struct to store the name of the key along with the EKey
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1));

	pauseMouseButton = SNew(SButton)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.OnPressed(this, &SOptions::OnPauseMouseBindingResetPressed)
		.OnReleased(this, &SOptions::OnPauseMouseBindingResetReleased)
		.ContentPadding(FMargin())
		.IsEnabled(true)
		.ButtonColorAndOpacity(FLinearColor::Transparent)
		.ButtonStyle(transparentButtonStyle)
		[
			pauseMouseText.ToSharedRef()
		];

	pauseMouseBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateRightColumnPos(-1, 11))
		[
			pauseMouseButton.ToSharedRef()
		];

	controlsOverlay = SNew(SOverlay);

	controlsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			keyboardBindingsTextBox.ToSharedRef()
		];

	controlsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			pause1TextBox.ToSharedRef()
		];

	controlsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			pauseKeyBackgroundBox.ToSharedRef()
		];

	controlsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			pauseKeyBox.ToSharedRef()
		];

	controlsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			pause2TextBox.ToSharedRef()
		];

	controlsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			pauseMouseBackgroundBox.ToSharedRef()
		];

	controlsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			pauseMouseBox.ToSharedRef()
		];

	controlsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			firstFloorBackBox.ToSharedRef()
		];

	creditTextOne = SNew(STextBlock)
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(songTextColors[songCycles[0]])
		.Font(textFont)
		.Text(FText::FromString("Abundance Of Love by Mike Berger"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1));

	creditBoxOne = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateMiddleColumnPos(0))
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SOptions::OnSongCreditOnePressed)
				.OnReleased(this, &SOptions::OnSongCreditOneReleased)
				.OnHovered(this, &SOptions::OnSongCreditOneHovered)
				.OnUnhovered(this, &SOptions::OnSongCreditOneUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					creditTextOne.ToSharedRef()
				]
		];

	songListToolTip = SNew(SToolTip)
		[
			SNew(STextBlock)
				.Text(FText::FromString("orange means enabled, red means playing, grey means disabled"))
				.Font(textFont)
				.ColorAndOpacity(FColor::Silver)
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		];

	creditBoxOne->SetToolTip(songListToolTip);
	
	creditTextTwo = SNew(STextBlock)
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(songTextColors[songCycles[1]])
		.Font(textFont)
		.Text(FText::FromString("Karatine by Alpha Hydrae | License: CC0"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1));

	creditBoxTwo = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateMiddleColumnPos(1))
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SOptions::OnSongCreditTwoPressed)
				.OnReleased(this, &SOptions::OnSongCreditTwoReleased)
				.OnHovered(this, &SOptions::OnSongCreditTwoHovered)
				.OnUnhovered(this, &SOptions::OnSongCreditTwoUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					creditTextTwo.ToSharedRef()
				]
		];

	creditBoxTwo->SetToolTip(songListToolTip);

	creditTextThree = SNew(STextBlock)
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(songTextColors[songCycles[2]])
		.Font(textFont)
		.Text(FText::FromString("Variatio 13 by Kimiko Ishizaka | License: CC0"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1));

	creditBoxThree = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateMiddleColumnPos(2))
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SOptions::OnSongCreditThreePressed)
				.OnReleased(this, &SOptions::OnSongCreditThreeReleased)
				.OnHovered(this, &SOptions::OnSongCreditThreeHovered)
				.OnUnhovered(this, &SOptions::OnSongCreditThreeUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					creditTextThree.ToSharedRef()
				]
		];

	creditBoxThree->SetToolTip(songListToolTip);

	creditTextFour = SNew(STextBlock)
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(songTextColors[songCycles[3]])
		.Font(textFont)
		.Text(FText::FromString("Variatio 19 by Kimiko Ishizaka | License: CC0"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1));

	creditBoxFour = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateMiddleColumnPos(3))
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SOptions::OnSongCreditFourPressed)
				.OnReleased(this, &SOptions::OnSongCreditFourReleased)
				.OnHovered(this, &SOptions::OnSongCreditFourHovered)
				.OnUnhovered(this, &SOptions::OnSongCreditFourUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					creditTextFour.ToSharedRef()
				]
		];

	creditBoxFour->SetToolTip(songListToolTip);

	creditTextFive = SNew(STextBlock)
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(songTextColors[songCycles[4]])
		.Font(textFont)
		.Text(FText::FromString("Variatio 29 by Kimiko Ishizaka | License: CC0"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1));

	creditBoxFive = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateMiddleColumnPos(4))
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SOptions::OnSongCreditFivePressed)
				.OnReleased(this, &SOptions::OnSongCreditFiveReleased)
				.OnHovered(this, &SOptions::OnSongCreditFiveHovered)
				.OnUnhovered(this, &SOptions::OnSongCreditFiveUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					creditTextFive.ToSharedRef()
				]
		];

	creditBoxFive->SetToolTip(songListToolTip);

	creditTextSix = SNew(STextBlock)
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(songTextColors[songCycles[5]])
		.Font(textFont)
		.Text(FText::FromString("Insomnia by Josh Woodward | license: CC BY at freemusicarchive.org"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1));

	creditBoxSix = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateMiddleColumnPos(5))
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SOptions::OnSongCreditSixPressed)
				.OnReleased(this, &SOptions::OnSongCreditSixReleased)
				.OnHovered(this, &SOptions::OnSongCreditSixHovered)
				.OnUnhovered(this, &SOptions::OnSongCreditSixUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					creditTextSix.ToSharedRef()
				]
		];

	creditBoxSix->SetToolTip(songListToolTip);

	creditTextSeven = SNew(STextBlock)
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(songTextColors[songCycles[6]])
		.Font(textFont)
		.Text(FText::FromString("Bowsie Sessions by Kira Daily | license: CC BY at freemusicarchive.org"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1));

	creditBoxSeven = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateMiddleColumnPos(6))
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SOptions::OnSongCreditSevenPressed)
				.OnReleased(this, &SOptions::OnSongCreditSevenReleased)
				.OnHovered(this, &SOptions::OnSongCreditSevenHovered)
				.OnUnhovered(this, &SOptions::OnSongCreditSevenUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					creditTextSeven.ToSharedRef()
				]
		];

	creditBoxSeven->SetToolTip(songListToolTip);

	creditTextEight = SNew(STextBlock)
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(songTextColors[songCycles[7]])
		.Font(textFont)
		.Text(FText::FromString("The Circle by Kira Daily | license: CC BY at freemusicarchive.org"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1));

	creditBoxEight = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateMiddleColumnPos(7))
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SOptions::OnSongCreditEightPressed)
				.OnReleased(this, &SOptions::OnSongCreditEightReleased)
				.OnHovered(this, &SOptions::OnSongCreditEightHovered)
				.OnUnhovered(this, &SOptions::OnSongCreditEightUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					creditTextEight.ToSharedRef()
				]
		];

	creditBoxEight->SetToolTip(songListToolTip);

	creditsOverlay = SNew(SOverlay);

	creditsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			creditBoxOne.ToSharedRef()
		];

	creditsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			creditBoxTwo.ToSharedRef()
		];

	creditsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			creditBoxThree.ToSharedRef()
		];

	creditsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			creditBoxFour.ToSharedRef()
		];

	creditsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			creditBoxFive.ToSharedRef()
		];

	creditsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			creditBoxSix.ToSharedRef()
		];

	creditsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			creditBoxSeven.ToSharedRef()
		];

	creditsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			creditBoxEight.ToSharedRef()
		];

	creditsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			firstFloorBackBox.ToSharedRef()
		];

	vsyncBoxOne = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateLeftColumnPos(-2, 1))
		[
			SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(menuFont)
				.Text(FText::FromString("VSync"))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
		];

	vsyncCheckBox = SNew(SCheckBox)
		.HAlign(HAlign_Fill)
		.Padding(FMargin())
		.Type(ESlateCheckBoxType::ToggleButton)
		.OnCheckStateChanged(this, &SOptions::OnVSyncChecked);

	if (UGameUserSettings::GetGameUserSettings()->IsVSyncEnabled())
	{
		vsyncCheckBox->SetIsChecked(ECheckBoxState::Checked);
	}

	vsyncBoxTwo = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateCheckBoxPos(-2))
		[
			vsyncCheckBox.ToSharedRef()
		];

	VSyncCheckBoxBackground = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateCheckBoxPos(-2))
		[
			SNew(SImage)
				.Image(gameFrameColor_SB)
		];

	gammaBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateLeftColumnPos(-1, 1))
		[
			SNew(STextBlock)
				.Justification(ETextJustify::Center)
				.ColorAndOpacity(FColor::Orange)
				.Font(menuFont)
				.Text(FText::FromString("Gamma"))
				.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
				.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1))
		];

	gammaTextOne = SNew(STextBlock)
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::Orange)
		.Font(menuFont)
		.Text(FText::FromString("<-"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1));

	gammaOptionBoxOne = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(TwinButtonsCenter(-1, 0))
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SOptions::OnGammaOnePressed)
				.OnReleased(this, &SOptions::OnGammaOneReleased)
				.OnHovered(this, &SOptions::OnGammaOneHovered)
				.OnUnhovered(this, &SOptions::OnGammaOneUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					gammaTextOne.ToSharedRef()
				]
		];

	gammaTextTwo = SNew(STextBlock)
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::Orange)
		.Font(menuFont)
		.Text(FText::FromString("->"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1));

	gammaOptionBoxTwo = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(TwinButtonsCenter(-1, 1))
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SOptions::OnGammaTwoPressed)
				.OnReleased(this, &SOptions::OnGammaTwoReleased)
				.OnHovered(this, &SOptions::OnGammaTwoHovered)
				.OnUnhovered(this, &SOptions::OnGammaTwoUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					gammaTextTwo.ToSharedRef()
				]
		];

	gammaResetText = SNew(STextBlock)
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::Orange)
		.Font(menuFont)
		.Text(FText::FromString("Reset"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, 1));

	gammaResetBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateRightColumnPos(-1, 1))
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SOptions::OnResetGammaPressed)
				.OnReleased(this, &SOptions::OnResetGammaReleased)
				.OnHovered(this, &SOptions::OnResetGammaHovered)
				.OnUnhovered(this, &SOptions::OnResetGammaUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					gammaResetText.ToSharedRef()
				]
		];

	graphicsOverlay = SNew(SOverlay);

	graphicsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			vsyncBoxOne.ToSharedRef()
		];

	graphicsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			VSyncCheckBoxBackground.ToSharedRef()
		];

	graphicsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			vsyncBoxTwo.ToSharedRef()
		];

	graphicsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			gammaBox.ToSharedRef()
		];

	graphicsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			gammaOptionBoxOne.ToSharedRef()
		];

	graphicsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			gammaOptionBoxTwo.ToSharedRef()
		];

	graphicsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			gammaResetBox.ToSharedRef()
		];

	graphicsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			firstFloorBackBox.ToSharedRef()
		];

	masterOverlay = SNew(SOverlay);

	masterOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			mainOptionsOverlay.ToSharedRef()
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

FReply SOptions::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& InMouseEvent)
{//when I calculate the pause mouse in the saveFile creation in the hud i will not need to double check if the users mouse even has that button. just set it to scroll wheel by default then give them the ability to change it in the settings
	if (replaceKey)
	{
		currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));
		FKey inButton = InMouseEvent.GetEffectingButton();

		switch (keyToReplace)
		{
		case 0:
			pauseKeyText->SetText(currentSave->GetPauseKey().GetDisplayName());
			break;
		case 1:
			if (inButton.IsBindableToActions() && !inButton.IsGamepadKey() && !inButton.IsModifierKey() && inButton.IsMouseButton() && inButton != EKeys::Mouse2D && inButton.IsValid() && inButton != currentSave->GetSelectKey())
			{
				pauseMouseText->SetText(inButton.GetDisplayName());
				OwningHUD->CommitKey(1, inButton);
			}
			else
			{
				pauseMouseText->SetText(currentSave->GetPauseMouse().GetDisplayName());
			}
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		default:
			break;
		}

		replaceKey = false;
	}

	return FReply::Handled();
}

FReply SOptions::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (replaceKey)
	{
		currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));
		FKey inKey = InKeyEvent.GetKey();

		switch (keyToReplace)
		{
		case 0:
			if (inKey.IsBindableToActions() && !inKey.IsGamepadKey() && !inKey.IsModifierKey() && !inKey.IsMouseButton() && !inKey.IsAxis1D() && !inKey.IsAxis2D() && !inKey.IsAxis3D() && inKey.IsValid() && !inKey.IsDeprecated() && inKey != EKeys::F1 && inKey != EKeys::F2 && inKey != EKeys::F3 && inKey != EKeys::F4 && inKey != EKeys::F5 && inKey != EKeys::F6 && inKey != EKeys::F7 && inKey != EKeys::F8 && inKey != EKeys::F9 && inKey != EKeys::F10 && inKey != EKeys::F11 && inKey != EKeys::F12 && inKey != EKeys::Tilde)//I need to make sure I cannot bind pause functionality to a movement key or movement functionality to a potential pause key. also double check mouse buttons are catagorized as mouse buttons
			{//Some keys/buttons do have pre-designated functionality. check to make sure the inKey is not a key which is already in use like f11 or tildae
				//also f10 does not work to open the options in game. maybe i should just eliminate all f keys from the possibilities. what else needs eliminated?
				pauseKeyText->SetText(inKey.GetDisplayName());
				OwningHUD->CommitKey(0, inKey);
			}
			else {
				pauseKeyText->SetText(currentSave->GetPauseKey().GetDisplayName());//there is a crash where some keys appear to being recorded as null !!!SOLVE NOW!!!
			}//so it appears sometimes unexpectedly currentSave->GetPauseKey() returns none, it seems to have been solved by re-initializing current in the replace key scope
			break;
		case 1:
			pauseMouseText->SetText(currentSave->GetPauseMouse().GetDisplayName());
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		default:
			break;
		}

		replaceKey = false;
	}

	return FReply::Handled();
}

void SOptions::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{//what if the mouse cursor teleports from one button to the next and onHovered gets called on the next button before onUnHovered gets called on the first? I think it will be okay ultimately because of the implementation of completedMargins and completedOffsets but this is unconfirmed and even if it does work it would look funny
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

void SOptions::OnAudioHovered()
{
	if (shrinkingBoxes.Find(audioBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(audioBox);
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
		growingMargin = audioMargin;
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
	growingBox.Add(audioBox);
	growingTextBlock = audioText;
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SOptions::OnAudioUnHovered()
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

			growingMargin = GrownMargin(audioMargin);
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
		shrinkingAdjustedMarginSizesX.Add((audioMargin - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((audioMargin - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((menuFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(audioMargin);
		completedFonts.Add(menuFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}
void SOptions::OnAudioPressed()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	audioText->SetColorAndOpacity(FColor::White);
}
void SOptions::OnAudioReleased()
{
	PlayChordToActiveNote();

	audioText->SetColorAndOpacity(FColor::Orange);
	audioBox->SetPadding(audioMargin);
	audioText->SetFont(menuFont);
	audioText->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	audioText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	masterOverlay->RemoveSlot(0);
	masterOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			audioOverlay.ToSharedRef()
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
	else if (shrinkingBoxes.Find(audioBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(audioBox);

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

void SOptions::OnGraphicsHovered()
{
	if (shrinkingBoxes.Find(graphicsBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(graphicsBox);
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
		growingMargin = graphicsMargin;
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
	growingBox.Add(graphicsBox);
	growingTextBlock = graphicsText;
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SOptions::OnGraphicsUnHovered()
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

			growingMargin = GrownMargin(graphicsMargin);
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
		shrinkingAdjustedMarginSizesX.Add((graphicsMargin - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((graphicsMargin - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((menuFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(graphicsMargin);
		completedFonts.Add(menuFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}
void SOptions::OnGraphicsPressed()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	graphicsText->SetColorAndOpacity(FColor::White);
}
void SOptions::OnGraphicsReleased()
{
	PlayChordToActiveNote();

	graphicsText->SetColorAndOpacity(FColor::Orange);
	graphicsBox->SetPadding(graphicsMargin);
	graphicsText->SetFont(menuFont);
	graphicsText->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	graphicsText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	masterOverlay->RemoveSlot(0);
	masterOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			graphicsOverlay.ToSharedRef()
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
	else if (shrinkingBoxes.Find(graphicsBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(graphicsBox);

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

void SOptions::OnControlsHovered()
{
	if (shrinkingBoxes.Find(controlsBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(controlsBox);
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
		growingMargin = controlsMargin;
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
	growingBox.Add(controlsBox);
	growingTextBlock = controlsText;
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SOptions::OnControlsUnHovered()
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

			growingMargin = GrownMargin(controlsMargin);
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
		shrinkingAdjustedMarginSizesX.Add((controlsMargin - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((controlsMargin - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((menuFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(controlsMargin);
		completedFonts.Add(menuFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}
void SOptions::OnControlsPressed()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	controlsText->SetColorAndOpacity(FColor::White);
}
void SOptions::OnControlsReleased()
{
	PlayChordToActiveNote();

	controlsText->SetColorAndOpacity(FColor::Orange);
	controlsBox->SetPadding(controlsMargin);
	controlsText->SetFont(menuFont);
	controlsText->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	controlsText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	masterOverlay->RemoveSlot(0);
	masterOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			controlsOverlay.ToSharedRef()
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
	else if (shrinkingBoxes.Find(controlsBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(controlsBox);

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

void SOptions::OnCreditsHovered()
{
	if (shrinkingBoxes.Find(creditsBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(creditsBox);
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
		growingMargin = creditsMargin;
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
	growingBox.Add(creditsBox);
	growingTextBlock = creditsText;
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SOptions::OnCreditsUnHovered()
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

			growingMargin = GrownMargin(creditsMargin);
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
		shrinkingAdjustedMarginSizesX.Add((creditsMargin - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((creditsMargin - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((menuFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(creditsMargin);
		completedFonts.Add(menuFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}
void SOptions::OnCreditsPressed()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	creditsText->SetColorAndOpacity(FColor::White);
}
void SOptions::OnCreditsReleased()
{
	PlayChordToActiveNote();

	creditsText->SetColorAndOpacity(FColor::Orange);
	creditsBox->SetPadding(creditsMargin);
	creditsText->SetFont(menuFont);
	creditsText->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	creditsText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	masterOverlay->RemoveSlot(0);
	masterOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			creditsOverlay.ToSharedRef()
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
	else if (shrinkingBoxes.Find(creditsBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(creditsBox);

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

void SOptions::OnBackFloorOneHovered()
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
void SOptions::OnBackFloorOneUnHovered()
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
void SOptions::OnBackFloorOnePressed()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	backText->SetColorAndOpacity(FColor::White);
}
void SOptions::OnBackFloorOneReleased()
{
	if (replaceKey)
	{
		currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));

		switch (keyToReplace)
		{
		case 0:
			pauseKeyText->SetText(currentSave->GetPauseKey().GetDisplayName());
			break;
		case 1:
			pauseMouseText->SetText(currentSave->GetPauseMouse().GetDisplayName());
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			break;
		}

		replaceKey = false;
	}

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
			mainOptionsOverlay.ToSharedRef()
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

void SOptions::OnBackToMenuHovered()
{
	if (shrinkingBoxes.Find(toMenuBackBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(toMenuBackBox);
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
	growingBox.Add(toMenuBackBox);
	growingTextBlock = backText;
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SOptions::OnBackToMenuUnHovered()
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
void SOptions::OnBackToMenuPressed()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	backText->SetColorAndOpacity(FColor::White);
}
void SOptions::OnBackToMenuReleased()
{
	PlayChordToActiveNote();

	backText->SetColorAndOpacity(FColor::Orange);
	toMenuBackBox->SetPadding(backMargin);
	backText->SetFont(menuFont);
	backText->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	backText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

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
	else if (shrinkingBoxes.Find(toMenuBackBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(toMenuBackBox);

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

	OwningHUD->DestroyOptionsMenu();
}

void SOptions::OnPauseBindingResetPressed()
{
	if (replaceKey)
	{
		currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));

		switch (keyToReplace)
		{
		case 0:
			pauseKeyText->SetText(currentSave->GetPauseKey().GetDisplayName());
			break;
		case 1:
			pauseMouseText->SetText(currentSave->GetPauseMouse().GetDisplayName());
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		default:
			break;
		}
	}
	replaceKey = false;

	pauseKeyBackground->SetColorAndOpacity(FSlateColor(FColor().FromHex("7f7f7f")));
}
void SOptions::OnPauseBindingResetReleased()
{
	pauseKeyBackground->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	pauseKeyText->SetText(FText::FromString("press any key"));
	replaceKey = true;
	keyToReplace = 0;
}

void SOptions::OnPauseMouseBindingResetPressed()
{
	if (replaceKey)
	{
		currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));

		switch (keyToReplace)
		{
		case 0:
			pauseKeyText->SetText(currentSave->GetPauseKey().GetDisplayName());
			break;
		case 1:
			pauseMouseText->SetText(currentSave->GetPauseMouse().GetDisplayName());
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		default:
			break;
		}
	}
	replaceKey = false;

	pauseMouseBackground->SetColorAndOpacity(FSlateColor(FColor().FromHex("7f7f7f")));
}
void SOptions::OnPauseMouseBindingResetReleased()
{
	pauseMouseBackground->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	pauseMouseText->SetText(FText::FromString("press any key"));
	replaceKey = true;
	keyToReplace = 1;
}

void SOptions::OnSongCreditOneHovered()
{
	creditTextOne->SetColorAndOpacity(FColor::Yellow);
}
void SOptions::OnSongCreditOneUnHovered()
{
	creditTextOne->SetColorAndOpacity(songTextColors[songCycles[0]]);
}
void SOptions::OnSongCreditOnePressed()
{
	creditTextOne->SetColorAndOpacity(FColor::White);

	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();
}
void SOptions::OnSongCreditOneReleased()
{
	int i = 0;
	songCycles[i] = (songCycles[i] + 1) % 3;

	switch (songCycles[i])
	{
	case 0:
		OwningHUD->ToggleSong(i);

		creditTextOne->SetColorAndOpacity(songTextColors[0]);
		break;
	case 1:
		songAudioComponents[songPlayingIndex]->Stop();

		songPlayingIndex = i;
		OwningHUD->songPlaying = true;
		OwningHUD->songPlayingIndex = songPlayingIndex;
		OwningHUD->songCycles[i] = 1;
		songAudioComponents[i]->Play();

		creditTextOne->SetColorAndOpacity(songTextColors[1]);
		break;
	case 2:
		OwningHUD->ToggleSong(i);
		OwningHUD->songPlaying = false;
		songAudioComponents[i]->Stop();

		creditTextOne->SetColorAndOpacity(songTextColors[2]);
		break;
	default:
		break;
	}

	PlayChordToActiveNote();
}

void SOptions::OnSongCreditTwoHovered()
{
	creditTextTwo->SetColorAndOpacity(FColor::Yellow);
}
void SOptions::OnSongCreditTwoUnHovered()
{
	creditTextTwo->SetColorAndOpacity(songTextColors[songCycles[1]]);
}
void SOptions::OnSongCreditTwoPressed()
{
	creditTextTwo->SetColorAndOpacity(FColor::White);

	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();
}
void SOptions::OnSongCreditTwoReleased()
{
	int i = 1;
	songCycles[i] = (songCycles[i] + 1) % 3;

	switch (songCycles[i])
	{
	case 0:
		OwningHUD->ToggleSong(i);

		creditTextTwo->SetColorAndOpacity(songTextColors[0]);
		break;
	case 1:
		songAudioComponents[songPlayingIndex]->Stop();

		songPlayingIndex = i;
		OwningHUD->songPlaying = true;
		OwningHUD->songPlayingIndex = songPlayingIndex;
		OwningHUD->songCycles[i] = 1;
		songAudioComponents[i]->Play();

		creditTextTwo->SetColorAndOpacity(songTextColors[1]);
		break;
	case 2:
		OwningHUD->ToggleSong(i);
		OwningHUD->songPlaying = false;
		songAudioComponents[i]->Stop();

		creditTextTwo->SetColorAndOpacity(songTextColors[2]);
		break;
	default:
		break;
	}

	PlayChordToActiveNote();
}

void SOptions::OnSongCreditThreeHovered()
{
	creditTextThree->SetColorAndOpacity(FColor::Yellow);
}
void SOptions::OnSongCreditThreeUnHovered()
{
	creditTextThree->SetColorAndOpacity(songTextColors[songCycles[2]]);
}
void SOptions::OnSongCreditThreePressed()
{
	creditTextThree->SetColorAndOpacity(FColor::White);

	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();
}
void SOptions::OnSongCreditThreeReleased()
{
	int i = 2;
	songCycles[i] = (songCycles[i] + 1) % 3;

	switch (songCycles[i])
	{
	case 0:
		OwningHUD->ToggleSong(i);

		creditTextThree->SetColorAndOpacity(songTextColors[0]);
		break;
	case 1:
		songAudioComponents[songPlayingIndex]->Stop();

		songPlayingIndex = i;
		OwningHUD->songPlaying = true;
		OwningHUD->songPlayingIndex = songPlayingIndex;
		OwningHUD->songCycles[i] = 1;
		songAudioComponents[i]->Play();

		creditTextThree->SetColorAndOpacity(songTextColors[1]);
		break;
	case 2:
		OwningHUD->ToggleSong(i);
		OwningHUD->songPlaying = false;
		songAudioComponents[i]->Stop();

		creditTextThree->SetColorAndOpacity(songTextColors[2]);
		break;
	default:
		break;
	}

	PlayChordToActiveNote();
}

void SOptions::OnSongCreditFourHovered()
{
	creditTextFour->SetColorAndOpacity(FColor::Yellow);
}
void SOptions::OnSongCreditFourUnHovered()
{
	creditTextFour->SetColorAndOpacity(songTextColors[songCycles[3]]);
}
void SOptions::OnSongCreditFourPressed()
{
	creditTextFour->SetColorAndOpacity(FColor::White);

	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();
}
void SOptions::OnSongCreditFourReleased()
{
	int i = 3;
	songCycles[i] = (songCycles[i] + 1) % 3;

	switch (songCycles[i])
	{
	case 0:
		OwningHUD->ToggleSong(i);

		creditTextFour->SetColorAndOpacity(songTextColors[0]);
		break;
	case 1:
		songAudioComponents[songPlayingIndex]->Stop();

		songPlayingIndex = i;
		OwningHUD->songPlaying = true;
		OwningHUD->songPlayingIndex = songPlayingIndex;
		OwningHUD->songCycles[i] = 1;
		songAudioComponents[i]->Play();

		creditTextFour->SetColorAndOpacity(songTextColors[1]);
		break;
	case 2:
		OwningHUD->ToggleSong(i);
		OwningHUD->songPlaying = false;
		songAudioComponents[i]->Stop();

		creditTextFour->SetColorAndOpacity(songTextColors[2]);
		break;
	default:
		break;
	}

	PlayChordToActiveNote();
}

void SOptions::OnSongCreditFiveHovered()
{
	creditTextFive->SetColorAndOpacity(FColor::Yellow);
}
void SOptions::OnSongCreditFiveUnHovered()
{
	creditTextFive->SetColorAndOpacity(songTextColors[songCycles[4]]);
}
void SOptions::OnSongCreditFivePressed()
{
	creditTextFive->SetColorAndOpacity(FColor::White);

	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();
}
void SOptions::OnSongCreditFiveReleased()
{
	int i = 4;
	songCycles[i] = (songCycles[i] + 1) % 3;

	switch (songCycles[i])
	{
	case 0:
		OwningHUD->ToggleSong(i);

		creditTextFive->SetColorAndOpacity(songTextColors[0]);
		break;
	case 1:
		songAudioComponents[songPlayingIndex]->Stop();

		songPlayingIndex = i;
		OwningHUD->songPlaying = true;
		OwningHUD->songPlayingIndex = songPlayingIndex;
		OwningHUD->songCycles[i] = 1;
		songAudioComponents[i]->Play();

		creditTextFive->SetColorAndOpacity(songTextColors[1]);
		break;
	case 2:
		OwningHUD->ToggleSong(i);
		OwningHUD->songPlaying = false;
		songAudioComponents[i]->Stop();

		creditTextFive->SetColorAndOpacity(songTextColors[2]);
		break;
	default:
		break;
	}

	PlayChordToActiveNote();
}

void SOptions::OnSongCreditSixHovered()
{
	creditTextSix->SetColorAndOpacity(FColor::Yellow);
}
void SOptions::OnSongCreditSixUnHovered()
{
	creditTextSix->SetColorAndOpacity(songTextColors[songCycles[5]]);
}
void SOptions::OnSongCreditSixPressed()
{
	creditTextSix->SetColorAndOpacity(FColor::White);

	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();
}
void SOptions::OnSongCreditSixReleased()
{
	int i = 5;
	songCycles[i] = (songCycles[i] + 1) % 3;

	switch (songCycles[i])
	{
	case 0:
		OwningHUD->ToggleSong(i);

		creditTextSix->SetColorAndOpacity(songTextColors[0]);
		break;
	case 1:
		songAudioComponents[songPlayingIndex]->Stop();

		songPlayingIndex = i;
		OwningHUD->songPlaying = true;
		OwningHUD->songPlayingIndex = songPlayingIndex;
		OwningHUD->songCycles[i] = 1;
		songAudioComponents[i]->Play();

		creditTextSix->SetColorAndOpacity(songTextColors[1]);
		break;
	case 2:
		OwningHUD->ToggleSong(i);
		OwningHUD->songPlaying = false;
		songAudioComponents[i]->Stop();

		creditTextSix->SetColorAndOpacity(songTextColors[2]);
		break;
	default:
		break;
	}

	PlayChordToActiveNote();
}

void SOptions::OnSongCreditSevenHovered()
{
	creditTextSeven->SetColorAndOpacity(FColor::Yellow);
}
void SOptions::OnSongCreditSevenUnHovered()
{
	creditTextSeven->SetColorAndOpacity(songTextColors[songCycles[6]]);
}
void SOptions::OnSongCreditSevenPressed()
{
	creditTextSeven->SetColorAndOpacity(FColor::White);

	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();
}
void SOptions::OnSongCreditSevenReleased()
{
	int i = 6;
	songCycles[i] = (songCycles[i] + 1) % 3;

	switch (songCycles[i])
	{
	case 0:
		OwningHUD->ToggleSong(i);

		creditTextSeven->SetColorAndOpacity(songTextColors[0]);
		break;
	case 1:
		songAudioComponents[songPlayingIndex]->Stop();

		songPlayingIndex = i;
		OwningHUD->songPlaying = true;
		OwningHUD->songPlayingIndex = songPlayingIndex;
		OwningHUD->songCycles[i] = 1;
		songAudioComponents[i]->Play();

		creditTextSeven->SetColorAndOpacity(songTextColors[1]);
		break;
	case 2:
		OwningHUD->ToggleSong(i);
		OwningHUD->songPlaying = false;
		songAudioComponents[i]->Stop();

		creditTextSeven->SetColorAndOpacity(songTextColors[2]);
		break;
	default:
		break;
	}

	PlayChordToActiveNote();
}

void SOptions::OnSongCreditEightHovered()
{
	creditTextEight->SetColorAndOpacity(FColor::Yellow);
}
void SOptions::OnSongCreditEightUnHovered()
{
	creditTextEight->SetColorAndOpacity(songTextColors[songCycles[7]]);
}
void SOptions::OnSongCreditEightPressed()
{
	creditTextEight->SetColorAndOpacity(FColor::White);

	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();
}
void SOptions::OnSongCreditEightReleased()
{
	int i = 7;
	songCycles[i] = (songCycles[i] + 1) % 3;

	switch (songCycles[i])
	{
	case 0:
		OwningHUD->ToggleSong(i);

		creditTextEight->SetColorAndOpacity(songTextColors[0]);
		break;
	case 1:
		songAudioComponents[songPlayingIndex]->Stop();

		songPlayingIndex = i;
		OwningHUD->songPlaying = true;
		OwningHUD->songPlayingIndex = songPlayingIndex;
		OwningHUD->songCycles[i] = 1;
		songAudioComponents[i]->Play();

		creditTextEight->SetColorAndOpacity(songTextColors[1]);
		break;
	case 2:
		OwningHUD->ToggleSong(i);
		OwningHUD->songPlaying = false;
		songAudioComponents[i]->Stop();

		creditTextEight->SetColorAndOpacity(songTextColors[2]);
		break;
	default:
		break;
	}

	PlayChordToActiveNote();
}

void SOptions::OnVSyncChecked(ECheckBoxState InState)
{
	GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "runs");
	if (InState == ECheckBoxState::Checked)
	{
		UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();
		Settings->SetVSyncEnabled(true);
		Settings->ApplySettings(true);
	}
	else if (InState == ECheckBoxState::Unchecked)
	{
		UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();
		Settings->SetVSyncEnabled(false);
		Settings->ApplySettings(true);
	}
}

void SOptions::OnGammaOneHovered()
{
	gammaTextOne->SetColorAndOpacity(FColor::Yellow);
}
void SOptions::OnGammaOneUnHovered()
{
	gammaTextOne->SetColorAndOpacity(FColor::Orange);
}
void SOptions::OnGammaOnePressed()
{
	gammaTextOne->SetColorAndOpacity(FColor::White);
}
void SOptions::OnGammaOneReleased()
{
	currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));

	float currentGamma = currentSave->GetGamma();
	currentGamma -= 0.2;

	if (GEngine)
	{
		if (standardWorldContextObject->GetWorld() != NULL)
		{
			GEngine->Exec(standardWorldContextObject->GetWorld(), *(FString)("gamma " + FString::SanitizeFloat(currentGamma)));
		}
	}

	currentSave->SetGamma(currentGamma);
	UGameplayStatics::SaveGameToSlot(currentSave, TEXT("saveGameOne"), 0);

	gammaTextOne->SetColorAndOpacity(FColor::Orange);
}

void SOptions::OnGammaTwoHovered()
{
	gammaTextTwo->SetColorAndOpacity(FColor::Yellow);
}
void SOptions::OnGammaTwoUnHovered()
{
	gammaTextTwo->SetColorAndOpacity(FColor::Orange);
}
void SOptions::OnGammaTwoPressed()
{
	gammaTextTwo->SetColorAndOpacity(FColor::White);
}
void SOptions::OnGammaTwoReleased()
{
	currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));

	float currentGamma = currentSave->GetGamma();
	currentGamma += 0.2;

	if (GEngine)
	{
		if (standardWorldContextObject->GetWorld() != NULL)
		{
			GEngine->Exec(standardWorldContextObject->GetWorld(), *(FString)("gamma " + FString::SanitizeFloat(currentGamma)));
		}
	}

	currentSave->SetGamma(currentGamma);
	UGameplayStatics::SaveGameToSlot(currentSave, TEXT("saveGameOne"), 0);

	gammaTextTwo->SetColorAndOpacity(FColor::Orange);
}

void SOptions::OnResetGammaHovered()
{
	gammaResetText->SetColorAndOpacity(FColor::Yellow);
}
void SOptions::OnResetGammaUnHovered()
{
	gammaResetText->SetColorAndOpacity(FColor::Orange);
}
void SOptions::OnResetGammaPressed()
{
	gammaResetText->SetColorAndOpacity(FColor::White);
}
void SOptions::OnResetGammaReleased()
{
	currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));

	float currentGamma = 2.2;

	if (GEngine)
	{
		if (standardWorldContextObject->GetWorld() != NULL)
		{
			GEngine->Exec(standardWorldContextObject->GetWorld(), *(FString)("gamma " + FString::SanitizeFloat(currentGamma)));
		}
	}

	currentSave->SetGamma(currentGamma);
	UGameplayStatics::SaveGameToSlot(currentSave, TEXT("saveGameOne"), 0);

	gammaResetText->SetColorAndOpacity(FColor::Orange);
}

void SOptions::OnMasterCommitted(const FText& InText, const ETextCommit::Type InTextAction)
{
	bool textIsValid = false;
	int newVolume;
	currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));
	//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "runs");
	//for some reason these functions run twice for every commit, who can say.

	for (int a = 0; a < 101; a++)
	{
		if (InText.EqualTo(FText::FromString(FString::FromInt(a))))
		{
			textIsValid = true;
			newVolume = a;
			break;
		}
	}
	if (textIsValid)
	{
		OwningHUD->CommitMaster(newVolume);
		makeSave = true;
	}
	else
	{
		masterEditableTextBox->SetText(FText::FromString(FString::FromInt(currentSave->GetMaster())));
	}
}
void SOptions::OnMusicCommitted(const FText& InText, const ETextCommit::Type InTextAction)
{
	bool textIsValid = false;
	int newVolume;
	currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));

	for (int a = 0; a < 101; a++)
	{
		if (InText.EqualTo(FText::FromString(FString::FromInt(a))))
		{
			textIsValid = true;
			newVolume = a;
			break;
		}
	}
	if (textIsValid)
	{
		OwningHUD->CommitMusic(newVolume);
		makeSave = true;
	}
	else
	{
		musicEditableTextBox->SetText(FText::FromString(FString::FromInt(currentSave->GetMusic())));
	}
}
void SOptions::OnAtmosphereCommitted(const FText& InText, const ETextCommit::Type InTextAction)
{
	bool textIsValid = false;
	int newVolume;
	currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));

	for (int a = 0; a < 101; a++)
	{
		if (InText.EqualTo(FText::FromString(FString::FromInt(a))))
		{
			textIsValid = true;
			newVolume = a;
			break;
		}
	}
	if (textIsValid)
	{
		OwningHUD->CommitAtmosphere(newVolume);
		makeSave = true;
	}
	else
	{
		atmosphereEditableTextBox->SetText(FText::FromString(FString::FromInt(currentSave->GetAtmosphere())));
	}
}
void SOptions::OnSFXCommitted(const FText& InText, const ETextCommit::Type InTextAction)
{
	bool textIsValid = false;
	int newVolume;
	currentSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));

	for (int a = 0; a < 101; a++)
	{
		if (InText.EqualTo(FText::FromString(FString::FromInt(a))))
		{
			textIsValid = true;
			newVolume = a;
			break;
		}
	}
	if (textIsValid)
	{
		OwningHUD->CommitSFX(newVolume);
		makeSave = true;
	}
	else
	{
		sfxEditableTextBox->SetText(FText::FromString(FString::FromInt(currentSave->GetSFX())));
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
