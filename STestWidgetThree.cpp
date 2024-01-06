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
	int32 tileIndex = tileCoords.Y * 15 + tileCoords.X;
	float fOne = viewportX - viewportY;
	float fTwo = fOne / 2;
	float leftPad = fTwo + (viewportY / 15) * tileCoords.X;
	float topPad = (viewportY / 15) * tileCoords.Y;
	float rightPad = fTwo + (viewportY / 15) * (15 - (tileCoords.X + 1));
	float bottomPad = viewportY - (viewportY / 15) * (tileCoords.Y + 1);

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
	tileIsIntersection = InArgs._tileIsIntersection;
	playerOnePlayerController = InArgs._playerOnePlayerController;
	grass_VMUI_1 = InArgs._grass_VMUI_1;
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

	landscapeStuff = { holeFromDown_SB, holeFromLeft_SB, holeFromRight_SB, holeFromUp_SB };
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

	b = 0;
	deleteMe = 0;

	testFMargin = FMargin(485.0f* 1.85185f, 537.6f* 1.85185f, 1022.6f* 1.85185f, 0.0f);

	/*static ConstructorHelpers::FObjectFinder<UMaterial> tempVar(TEXT("'/Game/Movies/videoMaterialsForUI/grass_VMUI_1.grass_VMUI_1'"));

	if (tempVar.Object != NULL)
	{
		grass_VMUI_1 = (UMaterial*)tempVar.Object;
	}//the issue appears to be this is not the appropriate kind of constructor for using ConstructorHelpers. next I will try to create either the slatebrush or SImage as a class in another file and instantiating them here*/

	//grass_VMUI_1 = tempVar.UMaterialInterface;
	//const FSlateBrush* largeGrassSB = new FSlateBrush(grass_VMUI);

	//UObject grassBrush = (UObject)materialPath;

	//largeGrassSB->SetResourceObject(grassBrush);
	//
	//largeGrassSB->SetResourceObject(grass_VMUI.Object);
	
	//largeGrass = SNew(SLargeGrassImage)

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

			/*+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(0, 13), adjustedViewportSize))
			[
				SNew(SBox)
				//.OnClicked(this, &STestWidgetThree::OnClicked)
				[
					SNew(SImage)
					.Image(grass_SB_1)

				]

			]*/
			

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(0, 0), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[0]])//the landscape arr index equates to the index of the SOverlay slot
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(1, 0), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[1]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(2, 0), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[2]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(3, 0), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[3]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(4, 0), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[4]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(5, 0), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[5]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(6, 0), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[6]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(7, 0), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[7]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(8, 0), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[8]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(9, 0), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[9]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(10, 0), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[10]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(11, 0), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[11]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(12, 0), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[12]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(13, 0), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[13]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(14, 0), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[14]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(0, 1), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[15]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(1, 1), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[16]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(2, 1), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[17]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(3, 1), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[18]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(4, 1), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[19]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(5, 1), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[20]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(6, 1), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[21]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(7, 1), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[22]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(8, 1), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[23]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(9, 1), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[24]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(10, 1), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[25]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(11, 1), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[26]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(12, 1), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[27]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(13, 1), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[28]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(14, 1), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[29]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(0, 2), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[30]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(1, 2), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[31]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(2, 2), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[32]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(3, 2), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[33]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(4, 2), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[34]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(5, 2), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[35]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(6, 2), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[36]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(7, 2), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[37]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(8, 2), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[38]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(9, 2), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[39]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(10, 2), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[40]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(11, 2), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[41]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(12, 2), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[42]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(13, 2), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[43]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(14, 2), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[44]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(0, 3), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[45]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(1, 3), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[46]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(2, 3), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[47]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(3, 3), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[48]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(4, 3), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[49]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(5, 3), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[50]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(6, 3), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[51]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(7, 3), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[52]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(8, 3), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[53]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(9, 3), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[54]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(10, 3), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[55]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(11, 3), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[56]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(12, 3), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[57]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(13, 3), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[58]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(14, 3), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[59]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(0, 4), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[60]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(1, 4), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[61]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(2, 4), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[62]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(3, 4), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[63]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(4, 4), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[64]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(5, 4), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[65]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(6, 4), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[66]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(7, 4), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[67]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(8, 4), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[68]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(9, 4), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[69]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(10, 4), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[70]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(11, 4), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[71]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(12, 4), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[72]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(13, 4), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[73]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(14, 4), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[74]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(0, 5), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[75]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(1, 5), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[76]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(2, 5), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[77]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(3, 5), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[78]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(4, 5), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[79]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(5, 5), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[80]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(6, 5), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[81]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(7, 5), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[82]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(8, 5), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[83]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(9, 5), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[84]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(10, 5), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[85]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(11, 5), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[86]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(12, 5), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[87]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(13, 5), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[88]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(14, 5), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[89]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(0, 6), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[90]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(1, 6), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[91]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(2, 6), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[92]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(3, 6), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[93]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(4, 6), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[94]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(5, 6), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[95]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(6, 6), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[96]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(7, 6), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[97]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(8, 6), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[98]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(9, 6), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[99]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(10, 6), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[100]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(11, 6), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[101]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(12, 6), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[102]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(13, 6), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[103]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(14, 6), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[104]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(0, 7), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[105]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(1, 7), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[106]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(2, 7), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[107]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(3, 7), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[108]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(4, 7), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[109]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(5, 7), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[110]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(6, 7), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[111]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(7, 7), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[112]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(8, 7), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[113]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(9, 7), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[114]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(10, 7), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[115]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(11, 7), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[116]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(12, 7), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[117]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(13, 7), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[118]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(14, 7), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[119]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(0, 8), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[120]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(1, 8), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[121]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(2, 8), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[122]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(3, 8), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[123]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(4, 8), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[124]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(5, 8), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[125]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(6, 8), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[126]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(7, 8), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[127]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(8, 8), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[128]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(9, 8), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[129]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(10, 8), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[130]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(11, 8), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[131]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(12, 8), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[132]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(13, 8), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[133]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(14, 8), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[134]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(0, 9), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[135]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(1, 9), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[136]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(2, 9), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[137]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(3, 9), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[138]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(4, 9), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[139]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(5, 9), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[140]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(6, 9), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[141]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(7, 9), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[142]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(8, 9), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[143]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(9, 9), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[144]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(10, 9), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[145]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(11, 9), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[146]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(12, 9), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[147]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(13, 9), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[148]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(14, 9), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[149]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(0, 10), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[150]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(1, 10), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[151]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(2, 10), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[152]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(3, 10), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[153]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(4, 10), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[154]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(5, 10), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[155]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(6, 10), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[156]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(7, 10), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[157]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(8, 10), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[158]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(9, 10), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[159]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(10, 10), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[160]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(11, 10), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[161]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(12, 10), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[162]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(13, 10), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[163]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(14, 10), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[164]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(0, 11), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[165]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(1, 11), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[166]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(2, 11), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[167]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(3, 11), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[168]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(4, 11), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[169]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(5, 11), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[170]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(6, 11), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[171]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(7, 11), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[172]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(8, 11), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[173]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(9, 11), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[174]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(10, 11), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[175]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(11, 11), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[176]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(12, 11), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[177]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(13, 11), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[178]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(14, 11), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[179]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(0, 12), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[180]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(1, 12), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[181]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(2, 12), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[182]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(3, 12), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[183]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(4, 12), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[184]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(5, 12), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[185]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(6, 12), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[186]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(7, 12), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[187]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(8, 12), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[188]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(9, 12), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[189]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(10, 12), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[190]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(11, 12), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[191]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(12, 12), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[192]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(13, 12), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[193]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(14, 12), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[194]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(0, 13), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[195]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(1, 13), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[196]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(2, 13), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[197]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(3, 13), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[198]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(4, 13), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[199]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(5, 13), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[200]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(6, 13), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[201]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(7, 13), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[202]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(8, 13), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[203]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(9, 13), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[204]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(10, 13), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[205]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(11, 13), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[206]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(12, 13), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[207]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(13, 13), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[208]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(14, 13), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[209]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(0, 14), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[210]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(1, 14), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[211]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(2, 14), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[212]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(3, 14), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[213]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(4, 14), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[214]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(5, 14), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[215]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(6, 14), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[216]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(7, 14), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[217]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(8, 14), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[218]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(9, 14), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[219]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(10, 14), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[220]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(11, 14), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[221]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(12, 14), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[222]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(13, 14), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[223]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(14, 14), adjustedViewportSize))
			[
				SNew(SImage)
				.Image(landscapeStuff[landscapeArr[224]])
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			//.Padding(CalculateTilePosition(FVector2D(14, 14), adjustedViewportSize))
			[
				marbleOverlay.ToSharedRef()
			]

			/* + SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(0, 0), adjustedViewportSize))
			[
				SNew(SButton)
				.ContentPadding(FMargin())
				.ButtonStyle(masterButtonStyle)
				.OnPressed(this, &STestWidgetThree::OnIntersectionPressed)
				.OnReleased(this, &STestWidgetThree::OnIntersectionReleased)//OnClicked only takes FReply functions, OnReleased and OnPressed only take void functions
				.ButtonColorAndOpacity(FLinearColor::Transparent)
				.IsEnabled(tileIsIntersection[0])///weerrks so now can I nest the rail stuff in buttons?
				[
					SNew(SImage)
					.Image(trackStuff[trackArr[0]])
				]

			]*///before I get back to the test hud stuff I want to figure out how it is Im going to make the marble move

			/* + SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CalculateTilePosition(FVector2D(0, 0), adjustedViewportSize))
			[
				SNew(SWindow::MakeCursorDecorator())
				[
					SNew(SImage)
					.Image(marble_SB_1)
				]

			]*/

		];

	/*for (allTrack)
	{
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(CalculateTilePosition(FVector2D(1, 2), adjustedViewportSize))
				[
					SNew(SBox)
					//.OnClicked(this, &STestWidgetThree::OnClicked)

					[
						SNew(SImage)
						.Image(grass_1_SB)
					]

				]
	}*/

			/* + SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(contentPadding)
			[
				SNew(SVerticalBox)

				//title text
				+ SVerticalBox::Slot()
				[
					SNew(STextBlock)
					.Font(TitleTextStyle)
					.Text(titleText)
					.Justification(ETextJustify::Center)
				]

				//play button
				+ SVerticalBox::Slot()
				.Padding(buttonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &STestWidgetThree::OnPlayClicked)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(playText)
						.Justification(ETextJustify::Center)
					]
				]

				//settings button
				+ SVerticalBox::Slot()
				.Padding(buttonPadding)
				[
					SNew(SImage)
					.Image(grass_1_SB)
					/*.
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(settingsText)
						.Justification(ETextJustify::Center)
					]
				]

				//quit button
				+ SVerticalBox::Slot()
				.Padding(buttonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &STestWidgetThree::OnQuitClicked)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(quitText)
						.Justification(ETextJustify::Center)
					]
				]
			]
		];*/
	//myGeometry = GetPaintSpaceGeometry();

	//viewportX = GSystemResolution.ResX;//viewportSize.Component(0);
	//viewportY = myGeometry.GetAbsoluteSize().Component(1);
/*
	if (GEngine) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 200.0, FColor::Blue, FString::SanitizeFloat(CalculateTilePosition(FVector2D(1, 1), adjustedViewportSize).Right));
	}
	
	marbleWindowStyle = FWindowStyle();
	marbleWindowStyle.SetBackgroundBrush(*emptyImg_SB);
	windowOne = SNew(SWindow)
		.Type(EWindowType::CursorDecorator)
		.bDragAnywhere();

	marbleOne->SetImage(marble_SB_1);
	windowOne->SetContent(marbleOne.ToSharedRef());
	windowOne->SetWindowBackground(constEmptyImg_SB);
	FSlateApplication::Get().AddWindow(windowOne.ToSharedRef(), true);*/
	// no more undoing necessary

	GEngine->AddOnScreenDebugMessage(-1, 200.0, FColor::Blue, (FString)"working");
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
		OwningHUD->HouseKeeping();//now this only works if all of WipeAss is completed before quit game is run. but it should be

		//windowOne.Get()->DestroyWindowImmediately();
		//delete marbleOne.Get();

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
