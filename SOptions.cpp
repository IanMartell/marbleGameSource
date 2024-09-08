// Fill out your copyright notice in the Description page of Project Settings.


#include "SOptions.h"
#include "SlateOptMacros.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "Components/AudioComponent.h"
#include "Widgets/Input/SSlider.h"
#include "Widgets/Input/SEditableText.h"

UE_DISABLE_OPTIMIZATION
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
	float fOne = ((adjustedViewportSize.X - adjustedViewportSize.Y) / 2) + (adjustedViewportSize.Y * 0.3);
	float fThree = ((adjustedViewportSize.X - adjustedViewportSize.Y) / 2) + ((adjustedViewportSize.Y / 10) * 5);
	float fTwo = FMath::DivideAndRoundUp(numberOfLetters, 5);
	float leftPad = fOne - ((adjustedViewportSize.Y / 10) * fTwo);
	float topPad = adjustedViewportSize.Y * (0.35 + (0.1 * textIndex));
	float rightPad = adjustedViewportSize.X - (leftPad + ((adjustedViewportSize.Y / 5) * fTwo));
	float bottomPad = adjustedViewportSize.Y * (0.575 - (0.1 * textIndex));

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

FMargin SOptions::CalculateRightColumnPos(int textIndex, int numberOfLetters)
{
	float fOne = ((adjustedViewportSize.X - adjustedViewportSize.Y) / 2) + (adjustedViewportSize.Y * 0.7);
	float fThree = ((adjustedViewportSize.X - adjustedViewportSize.Y) / 2) + ((adjustedViewportSize.Y / 10) * 5);
	float fTwo = FMath::DivideAndRoundUp(numberOfLetters, 5);
	float leftPad = fOne - ((adjustedViewportSize.Y / 10) * fTwo);
	float topPad = adjustedViewportSize.Y * (0.35 + (0.1 * textIndex));
	float rightPad = adjustedViewportSize.X - (leftPad + ((adjustedViewportSize.Y / 5) * fTwo));
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
	gameFrameColor_SMUI = InArgs._gameFrameColor_SMUI;

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

	standardShadowOffset = 0.003;
	standardOpacity = 1.0;
	grownOpacity = 0.6;
	multiplierOfOffset = 4;
	multiplierOfPerimeterExpansion = 1.225;

	audioMargin = CalculateMenuTextPos(0, 4);
	graphicsMargin = CalculateMenuTextPos(1, 7);
	controlsMargin = CalculateMenuTextPos(2, 7);
	accessabilityMargin = CalculateMenuTextPos(3, 7);
	backMargin = CalculateBackButtonPosition(adjustedViewportSize);

	transparentButtonStyle = new FButtonStyle();
	transparentButtonStyle->SetNormalPadding(FMargin());

	childrensCornerNotes = { 8, 11, 12, 13, 8, 11, 13, 12, 7, 11, 12, 14, 9, 10, 14, 13, 8, 11, 13, 15, 10, 11, 15, 14, 9, 11, 14, 16, 9, 14, 16, 15, 11, 13, 15, 18, 13, 15, 18, 19, 13, 15, 19, 18, 13, 15, 18, 17, 13, 15, 17, 16, 13, 15, 16, 15, 11, 13, 15, 14, 11, 13, 14, 13, 10, 11, 13, 12, 9, 11, 12, 15, 10, 13, 15, 16, 11, 13, 16, 13, 9, 11, 13, 12, 9, 11, 12, 11, 8, 9, 11, 10, 7, 8, 10, 0, 4, 5, 6, 7, 9, 11, 12, 13, 12, 11, 9, 7, 6, 5, 4, 0, 4, 5, 6, 7, 9, 11, 12, 13, 12, 11, 9, 7, 6, 5, 4, 0, 4, 5, 6, 7, 22, 11, 12, 13, 12, 11, 9, 7, 6, 5, 4, 0, 4, 5, 6, 7, 22, 11, 12, 13, 12, 11, 10, 7, 6, 5, 4 };
	childrensCornerIndex = -1;

	audioCycleTracker = 0;

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

	accessabilityText = SNew(STextBlock)
		.Margin(FMargin())
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FColor::Orange)
		.Font(menuFont)
		.Text(FText::FromString("Accessability"))
		.ShadowOffset(FVector2D(adjustedViewportSize.Y * 0.003, adjustedViewportSize.Y * 0.003))
		.ShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

	accessabilityBox = SNew(SBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(accessabilityMargin)
		[
			SNew(SButton)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.OnPressed(this, &SOptions::OnAccessabilityPressed)
				.OnReleased(this, &SOptions::OnAccessabilityReleased)
				.OnHovered(this, &SOptions::OnAccessabilityHovered)
				.OnUnhovered(this, &SOptions::OnAccessabilityUnHovered)
				.ContentPadding(FMargin())
				.IsEnabled(true)
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.ButtonStyle(transparentButtonStyle)
				[
					accessabilityText.ToSharedRef()
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

	mainOptionsOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			accessabilityBox.ToSharedRef()
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

void SOptions::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
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

void SOptions::OnAccessabilityHovered()
{
	if (shrinkingBoxes.Find(accessabilityBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(accessabilityBox);
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
		growingMargin = accessabilityMargin;
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
	growingBox.Add(accessabilityBox);
	growingTextBlock = accessabilityText;
	growTime = 0;

	childrensCornerIndex = (childrensCornerIndex + 1) % 159;
	hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Play();
}
void SOptions::OnAccessabilityUnHovered()
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

			growingMargin = GrownMargin(accessabilityMargin);
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
		shrinkingAdjustedMarginSizesX.Add((accessabilityMargin - growingMargin).Left / 2);
		shrinkingAdjustedMarginSizesY.Add((accessabilityMargin - growingMargin).Top / 2);
		shrinkingFontSizes.Add(growingFontSize);
		shrinkingFontSizesStartingPoints.Add(growingFontSize);
		shrinkingAdjustedFontSizes.Add((menuFont.Size - growingFont.Size) / 2);
		shrinkingTimes.Add(0);
		completedMargins.Add(accessabilityMargin);
		completedFonts.Add(menuFont);
		completedOffsets.Add(standardShadowOffset);

		hoverGrowAudioComponents[childrensCornerNotes[childrensCornerIndex]]->Stop();
	}
}
void SOptions::OnAccessabilityPressed()
{
	activeNoteIndex = FMath::RandRange(0, 7);
	purpleLullabyAudioComponents[activeNoteIndex]->Play();

	accessabilityText->SetColorAndOpacity(FColor::White);
}
void SOptions::OnAccessabilityReleased()
{
	PlayChordToActiveNote();

	accessabilityText->SetColorAndOpacity(FColor::Orange);
	accessabilityBox->SetPadding(accessabilityMargin);
	accessabilityText->SetFont(menuFont);
	accessabilityText->SetShadowOffset(FVector2D(standardShadowOffset * adjustedViewportSize.Y, standardShadowOffset * adjustedViewportSize.Y));
	accessabilityText->SetShadowColorAndOpacity(FLinearColor(0, 0, 0, standardOpacity));

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
	else if (shrinkingBoxes.Find(accessabilityBox) + 1)
	{
		indexOfShrinkingSubject = shrinkingBoxes.Find(accessabilityBox);

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
