// Fill out your copyright notice in the Description page of Project Settings.

#include "STestWidgetThree.h"
#include <string>
#include "UObject/ConstructorHelpers.h"
#include "Math/Vector2D.h"
#include "Layout/Geometry.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"

#define LOCTEXT_NAMESPACE "TestSlate"

const FMargin CalculateTilePosition(FVector2D tileCoords, FVector2D adjustedViewportSize)//this has been adjusted to respond to 1D arr coordinates
{//this will only work if screenSize.X >= screenSize.Y
	float viewportX = adjustedViewportSize.X;
	float viewportY = adjustedViewportSize.Y;
	float fOne = (viewportX - viewportY) / 2;
	float leftPad = fOne + (viewportY / 15) * tileCoords.X;
	float topPad = (viewportY / 15) * tileCoords.Y;
	float rightPad = fOne + (viewportY / 15) * (15 - (tileCoords.X + 1));
	float bottomPad = viewportY - (viewportY / 15) * (tileCoords.Y + 1);

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

const FMargin CalculateLargeTilePosition(FVector2D tileCoords, FVector2D adjustedViewportSize)
{
	float viewportX = adjustedViewportSize.X;
	float viewportY = adjustedViewportSize.Y;
	float fOne = (viewportX - viewportY) / 2;
	float leftPad = fOne + (viewportY / 15) * tileCoords.X;
	float topPad = (viewportY / 15) * tileCoords.Y;
	float rightPad = fOne + (viewportY / 15) * (15 - (tileCoords.X + 3));
	float bottomPad = viewportY - (viewportY / 15) * (tileCoords.Y + 3);

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

//you could change the size of the background tiles without changing the size of the track tiles because they are being calculated seperately. just moving down to 12 x 12 would have a big impact on performance
void STestWidgetThree::Construct(const FArguments& InArgs)//at some point I will need to write a destructor considering all the 'new' keywords used here
{
	SetCanTick(true);
	bCanSupportFocus = true;

	OwningHUD = InArgs._OwningHUD;
	landscapeArr = InArgs._landscapeArr;
	trackArr = InArgs._trackArr;
	pondSpecifierArr = InArgs._pondSpecifierArr;
	pondPositionArr = InArgs._pondPositionArr;
	tileIsIntersection = InArgs._tileIsIntersection;
	playerOnePlayerController = InArgs._playerOnePlayerController;
	grass_VMUI_1 = InArgs._grass_VMUI_1;
	grass_VMUI_2 = InArgs._grass_VMUI_2;
	grass_VMUI_3 = InArgs._grass_VMUI_3;
	pondHorizontal_VMUI = InArgs._pondHorizontal_VMUI;
	pondVerticleFlowingLeft_VMUI = InArgs._pondVerticleFlowingLeft_VMUI;
	pondVerticleFlowingRight_VMUI = InArgs._pondVerticleFlowingRight_VMUI;
	riverFlowingDown_VMUI_1 = InArgs._riverFlowingDown_VMUI_1;
	riverFlowingDown_VMUI_2 = InArgs._riverFlowingDown_VMUI_2;
	riverFlowingDown_VMUI_3 = InArgs._riverFlowingDown_VMUI_3;
	riverFlowingLeft_VMUI_1 = InArgs._riverFlowingLeft_VMUI_1;
	riverFlowingLeft_VMUI_2 = InArgs._riverFlowingLeft_VMUI_2;
	riverFlowingLeft_VMUI_3 = InArgs._riverFlowingLeft_VMUI_3;
	riverFlowingRight_VMUI_1 = InArgs._riverFlowingRight_VMUI_1;
	riverFlowingRight_VMUI_2 = InArgs._riverFlowingRight_VMUI_2;
	riverFlowingRight_VMUI_3 = InArgs._riverFlowingRight_VMUI_3;
	tree_VMUI_1 = InArgs._tree_VMUI_1;
	tree_VMUI_2 = InArgs._tree_VMUI_2;
	tree_VMUI_3 = InArgs._tree_VMUI_3;
	tree_VMUI_4 = InArgs._tree_VMUI_4;
	tree_VMUI_5 = InArgs._tree_VMUI_5;
	waterfall_VMUI = InArgs._waterfall_VMUI;
	riverTurning_VMUI_1 = InArgs._riverTurning_VMUI_1;
	riverTurning_VMUI_2 = InArgs._riverTurning_VMUI_2;
	riverTurning_VMUI_3 = InArgs._riverTurning_VMUI_3;
	riverTurning_VMUI_4 = InArgs._riverTurning_VMUI_4;
	holeFromDown_VMUI = InArgs._holeFromDown_VMUI;
	holeFromLeft_VMUI = InArgs._holeFromLeft_VMUI;
	holeFromRight_VMUI = InArgs._holeFromRight_VMUI;
	holeFromUp_VMUI = InArgs._holeFromUp_VMUI;
	buttonFromDownTurningRightZero_SMUI = InArgs._buttonFromDownTurningRightZero_SMUI;
	buttonFromDownTurningLeftZero_SMUI = InArgs._buttonFromDownTurningLeftZero_SMUI;
	buttonFromLeftTurningRightZero_SMUI = InArgs._buttonFromLeftTurningRightZero_SMUI;
	buttonFromLeftTurningLeftZero_SMUI = InArgs._buttonFromLeftTurningLeftZero_SMUI;
	buttonFromRightTurningRightZero_SMUI = InArgs._buttonFromRightTurningRightZero_SMUI;
	buttonFromRightTurningLeftZero_SMUI = InArgs._buttonFromRightTurningLeftZero_SMUI;
	buttonFromUpTurningRightZero_SMUI = InArgs._buttonFromUpTurningRightZero_SMUI;
	buttonFromUpTurningLeftZero_SMUI = InArgs._buttonFromUpTurningLeftZero_SMUI;
	verticleRail_SMUI = InArgs._verticleRail_SMUI;
	horizontalRail_SMUI = InArgs._horizontalRail_SMUI;
	railTurningOne_SMUI = InArgs._railTurningOne_SMUI;
	railTurningTwo_SMUI = InArgs._railTurningTwo_SMUI;
	railTurningThree_SMUI = InArgs._railTurningThree_SMUI;
	railTurningFour_SMUI = InArgs._railTurningFour_SMUI;
	emptyImg_SMUI = InArgs._emptyImg_SMUI;
	marble_SMUI_1 = InArgs._marble_SMUI_1;
	marble_SMUI_2 = InArgs._marble_SMUI_2;
	marble_SMUI_3 = InArgs._marble_SMUI_3;
	marble_SMUI_4 = InArgs._marble_SMUI_4;
	marble_SMUI_5 = InArgs._marble_SMUI_5;
	marble_SMUI_6 = InArgs._marble_SMUI_6;
	marble_SMUI_7 = InArgs._marble_SMUI_7;

	grass_SB_1 = new FSlateBrush();
	grass_SB_1->SetResourceObject(grass_VMUI_1);
	grass_SB_2 = new FSlateBrush();
	grass_SB_2->SetResourceObject(grass_VMUI_2);
	grass_SB_3 = new FSlateBrush();
	grass_SB_3->SetResourceObject(grass_VMUI_3);
	pondHorizontal_SB = new FSlateBrush();
	pondHorizontal_SB->SetResourceObject(pondHorizontal_VMUI);
	pondVerticleFlowingLeft_SB = new FSlateBrush();
	pondVerticleFlowingLeft_SB->SetResourceObject(pondVerticleFlowingLeft_VMUI);
	pondVerticleFlowingRight_SB = new FSlateBrush();
	pondVerticleFlowingRight_SB->SetResourceObject(pondVerticleFlowingRight_VMUI);
	riverFlowingDown_SB_1 = new FSlateBrush();
	riverFlowingDown_SB_1->SetResourceObject(riverFlowingDown_VMUI_1);
	riverFlowingDown_SB_2 = new FSlateBrush();
	riverFlowingDown_SB_2->SetResourceObject(riverFlowingDown_VMUI_2);
	riverFlowingDown_SB_3 = new FSlateBrush();
	riverFlowingDown_SB_3->SetResourceObject(riverFlowingDown_VMUI_3);
	riverFlowingLeft_SB_1 = new FSlateBrush();
	riverFlowingLeft_SB_1->SetResourceObject(riverFlowingLeft_VMUI_1);
	riverFlowingLeft_SB_2 = new FSlateBrush();
	riverFlowingLeft_SB_2->SetResourceObject(riverFlowingLeft_VMUI_2);
	riverFlowingLeft_SB_3 = new FSlateBrush();
	riverFlowingLeft_SB_3->SetResourceObject(riverFlowingLeft_VMUI_3);
	riverFlowingRight_SB_1 = new FSlateBrush();
	riverFlowingRight_SB_1->SetResourceObject(riverFlowingRight_VMUI_1);
	riverFlowingRight_SB_2 = new FSlateBrush();
	riverFlowingRight_SB_2->SetResourceObject(riverFlowingRight_VMUI_2);
	riverFlowingRight_SB_3 = new FSlateBrush();
	riverFlowingRight_SB_3->SetResourceObject(riverFlowingRight_VMUI_3);
	tree_SB_1 = new FSlateBrush();
	tree_SB_1->SetResourceObject(tree_VMUI_1);
	tree_SB_2 = new FSlateBrush();
	tree_SB_2->SetResourceObject(tree_VMUI_2);
	tree_SB_3 = new FSlateBrush();
	tree_SB_3->SetResourceObject(tree_VMUI_3);
	tree_SB_4 = new FSlateBrush();
	tree_SB_4->SetResourceObject(tree_VMUI_4);
	tree_SB_5 = new FSlateBrush();
	tree_SB_5->SetResourceObject(tree_VMUI_5);
	waterfall_SB = new FSlateBrush();
	waterfall_SB->SetResourceObject(waterfall_VMUI);
	riverTurning_SB_1 = new FSlateBrush();
	riverTurning_SB_1->SetResourceObject(riverTurning_VMUI_1);
	riverTurning_SB_2 = new FSlateBrush();
	riverTurning_SB_2->SetResourceObject(riverTurning_VMUI_2);
	riverTurning_SB_3 = new FSlateBrush();
	riverTurning_SB_3->SetResourceObject(riverTurning_VMUI_3);
	riverTurning_SB_4 = new FSlateBrush();
	riverTurning_SB_4->SetResourceObject(riverTurning_VMUI_4);
	
	holeFromDown_SB = new FSlateBrush();
	holeFromLeft_SB = new FSlateBrush();
	holeFromRight_SB = new FSlateBrush();
	holeFromUp_SB = new FSlateBrush();
	holeFromDown_SB->SetResourceObject(holeFromDown_VMUI);
	holeFromLeft_SB->SetResourceObject(holeFromLeft_VMUI);
	holeFromRight_SB->SetResourceObject(holeFromRight_VMUI);
	holeFromUp_SB->SetResourceObject(holeFromUp_VMUI);

	buttonFromDownTurningRightZero_SB = new FSlateBrush();
	buttonFromDownTurningLeftZero_SB = new FSlateBrush();
	buttonFromLeftTurningRightZero_SB = new FSlateBrush();
	buttonFromLeftTurningLeftZero_SB = new FSlateBrush();
	buttonFromRightTurningRightZero_SB = new FSlateBrush();
	buttonFromRightTurningLeftZero_SB = new FSlateBrush();
	buttonFromUpTurningRightZero_SB = new FSlateBrush();
	buttonFromUpTurningLeftZero_SB = new FSlateBrush();
	buttonFromDownTurningRightZero_SB->SetResourceObject(buttonFromDownTurningRightZero_SMUI);
	buttonFromDownTurningLeftZero_SB->SetResourceObject(buttonFromDownTurningLeftZero_SMUI);
	buttonFromLeftTurningRightZero_SB->SetResourceObject(buttonFromLeftTurningRightZero_SMUI);
	buttonFromLeftTurningLeftZero_SB->SetResourceObject(buttonFromLeftTurningLeftZero_SMUI);
	buttonFromRightTurningRightZero_SB->SetResourceObject(buttonFromRightTurningRightZero_SMUI);
	buttonFromRightTurningLeftZero_SB->SetResourceObject(buttonFromRightTurningLeftZero_SMUI);
	buttonFromUpTurningRightZero_SB->SetResourceObject(buttonFromUpTurningRightZero_SMUI);
	buttonFromUpTurningLeftZero_SB->SetResourceObject(buttonFromUpTurningLeftZero_SMUI);

	verticleRail_SB = new FSlateBrush();
	horizontalRail_SB = new FSlateBrush();
	railTurningOne_SB = new FSlateBrush();
	railTurningTwo_SB = new FSlateBrush();
	railTurningThree_SB = new FSlateBrush();
	railTurningFour_SB = new FSlateBrush();
	verticleRail_SB->SetResourceObject(verticleRail_SMUI);
	horizontalRail_SB->SetResourceObject(horizontalRail_SMUI);
	railTurningOne_SB->SetResourceObject(railTurningOne_SMUI);
	railTurningTwo_SB->SetResourceObject(railTurningTwo_SMUI);
	railTurningThree_SB->SetResourceObject(railTurningThree_SMUI);
	railTurningFour_SB->SetResourceObject(railTurningFour_SMUI);

	marble_SB_1 = new FSlateBrush();
	marble_SB_2 = new FSlateBrush();
	marble_SB_3 = new FSlateBrush();
	marble_SB_4 = new FSlateBrush();
	marble_SB_5 = new FSlateBrush();
	marble_SB_6 = new FSlateBrush();
	marble_SB_7 = new FSlateBrush();
	marble_SB_1->SetResourceObject(marble_SMUI_1);
	marble_SB_2->SetResourceObject(marble_SMUI_2);
	marble_SB_3->SetResourceObject(marble_SMUI_3);
	marble_SB_4->SetResourceObject(marble_SMUI_4);
	marble_SB_5->SetResourceObject(marble_SMUI_5);
	marble_SB_6->SetResourceObject(marble_SMUI_6);
	marble_SB_7->SetResourceObject(marble_SMUI_7);

	emptyImg_SB = new FSlateBrush();
	emptyImg_SB->SetResourceObject(emptyImg_SMUI);

	landscapeStuff = { grass_SB_1, holeFromDown_SB, holeFromLeft_SB, holeFromRight_SB, holeFromUp_SB, grass_SB_2, grass_SB_3, pondHorizontal_SB, pondVerticleFlowingLeft_SB, pondVerticleFlowingRight_SB, waterfall_SB, riverFlowingDown_SB_1, riverFlowingDown_SB_2, riverFlowingDown_SB_3, riverFlowingLeft_SB_1, riverFlowingLeft_SB_2, riverFlowingLeft_SB_3, riverFlowingRight_SB_1, riverFlowingRight_SB_2, riverFlowingRight_SB_3, tree_SB_1, tree_SB_2, tree_SB_3, tree_SB_4, tree_SB_5, riverTurning_SB_1, riverTurning_SB_2, riverTurning_SB_3, riverTurning_SB_4, emptyImg_SB };
	trackStuff = { emptyImg_SB, verticleRail_SB, horizontalRail_SB, railTurningOne_SB, railTurningTwo_SB, railTurningThree_SB, railTurningFour_SB, buttonFromDownTurningRightZero_SB, buttonFromDownTurningLeftZero_SB, buttonFromLeftTurningRightZero_SB, buttonFromLeftTurningLeftZero_SB, buttonFromRightTurningRightZero_SB, buttonFromRightTurningLeftZero_SB, buttonFromUpTurningRightZero_SB, buttonFromUpTurningLeftZero_SB};//the first element for this arr is an empty image ALSO I should change this to an array of fully assembled widget structures with the intersection having their logic built in

	GEngine->GameViewport->GetViewportSize(viewportSize);
	int32 X = FGenericPlatformMath::FloorToInt(viewportSize.X);
	int32 Y = FGenericPlatformMath::FloorToInt(viewportSize.Y);
	DPIScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(X, Y));
	adjustedViewportSize = (1 / DPIScale) * viewportSize;

	const FMargin contentPadding = FMargin(166.f, 100.f);
	const FMargin rowPadding_15 = FMargin(420.0f, 1008.0f, 1428.0f, 0.0f);
	const FMargin buttonPadding = FMargin(10.f);

	const FText titleText = LOCTEXT("GameTitle", "Marble Game");
	const FText playText = LOCTEXT("PlayGame", "Play");
	const FText settingsText = LOCTEXT("Settings", "Settings");
	const FText quitText = LOCTEXT("QuitGame", "Quit");

	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 40.f;

	FSlateFontInfo TitleTextStyle = ButtonTextStyle;
	TitleTextStyle.Size = 60.f;

	masterButtonStyle = new FButtonStyle();
	masterButtonStyle->SetNormalPadding(FMargin());

	//now that the track is built you can control the marbles movement merely by left turns, right turns or straight track. from the marbles starting direction a left turn will incriment the marble direction counter clockwise and a right turn clockwise 

	marbleOneBox = SNew(SBox)
		.Padding(CalculateTilePosition(FVector2D(0, 0), adjustedViewportSize))
		[
			SNew(SImage)
			.Image(marble_SB_1)
		];

	marbleOverlay = SNew(SOverlay);
	marbleOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			marbleOneBox.ToSharedRef()
		];

	largeTilesOverlay = SNew(SOverlay);
	for (int a = 0; a < pondPositionArr.Num(); a++)
	{
		largeTilesOverlay->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateLargeTilePosition(pondPositionArr[a], adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[pondSpecifierArr[a]])
			];
	}

	landscapeOverlay = SNew(SOverlay);
	for (int a = 0; a < 225; a++)
	{
		landscapeOverlay->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[a]])
			];
	}

	trackOverlay = SNew(SOverlay);
	for (int a = 0; a < 225; a++)
	{
		trackOverlay->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(a % 15, FMath::DivideAndRoundDown(a, 15)), adjustedViewportSize))
			[
				SNew(SButton)
				.ContentPadding(FMargin())
				.ButtonStyle(masterButtonStyle)
				.OnPressed(this, &STestWidgetThree::OnIntersectionPressed)
				.OnReleased(this, &STestWidgetThree::OnIntersectionReleased)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.IsEnabled(tileIsIntersection[a])///weerrks so now can I nest the rail stuff in buttons?
				[
					SNew(SImage)
					.Image(trackStuff[trackArr[a]])
				]
			];
	}

	b = 0;
	deleteMe = 0;

	testFMargin = FMargin(485.0f* 1.85185f, 537.6f* 1.85185f, 1022.6f* 1.85185f, 0.0f);

	ChildSlot //so it appears I cannot write code to systematically build only as much widget as necessary and will instead need to list out 225 landscape SImages and 225 track SImages and fill them as needed. but hold on, there is still some testing to be done, what if I store the initial SOverlay so I can reference it directly. ( this will mean potentially creating a new SOverlay sub class? no nvm I will just need to check through the childSlot logic to see if theres a way to display an already existing SOverlay, or to assign the SNew(SOverlay to an identity
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.ColorAndOpacity(FColor::Orange)
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				largeTilesOverlay.ToSharedRef()
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				landscapeOverlay.ToSharedRef()
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			//.Padding(CalculateTilePosition(FVector2D(14, 14), adjustedViewportSize))
			[
				marbleOverlay.ToSharedRef()
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				trackOverlay.ToSharedRef()
			]

		];
}

FReply STestWidgetThree::OnClicked() const
{
	UGameUserSettings* myGameSettings = GEngine->GetGameUserSettings();

	FGeometry testGeometry = GetPaintSpaceGeometry();
	float y = testGeometry.GetAbsoluteSize().Component(1);

	GEngine->AddOnScreenDebugMessage(-1, 200.0, FColor::Blue, FString::SanitizeFloat(y));

	return FReply::Handled();
}

FReply STestWidgetThree::OnQuitClicked() const
{
	if (OwningHUD.IsValid())
	{
		if (APlayerController* PC = OwningHUD->PlayerOwner)
		{
			PC->ConsoleCommand("Quit");
		}
	}

	return FReply::Handled();
}

void STestWidgetThree::OnIntersectionPressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 200.0, FColor::Blue, "pressed");
}

void STestWidgetThree::OnIntersectionReleased()
{
	GEngine->AddOnScreenDebugMessage(-1, 200.0, FColor::Blue, "released");
}

FReply STestWidgetThree::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Q)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "q");
	}

	if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		OwningHUD->HouseKeeping();
		OwningHUD->ResetRegenLevel();

		UKismetSystemLibrary::QuitGame(playerOnePlayerController, playerOnePlayerController, EQuitPreference::Quit, false);
	}

	return FReply::Handled();
}

void STestWidgetThree::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	if (deleteMe > 29)
	{
		deleteMe = 0;

		marbleOneBox->SetPadding(CalculateTilePosition(FVector2D(b, 0), adjustedViewportSize));
		b++;
	}
	else
	{
		deleteMe++;
	}
}

#undef LOCTEXT_NAMESPACE
