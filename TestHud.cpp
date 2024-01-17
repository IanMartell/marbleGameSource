// Fill out your copyright notice in the Description page of Project Settings.

#include "TestHud.h"
#include "STestWidgetThree.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h" // we include the engine because we need to get a pointer to the global engine to actually add something to the screen
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"
#include "Engine/Classes/Materials/Material.h"
#include "SLoadingScreenOne.h"
#include "Math/UnrealMathUtility.h"
#include<array>
//#include "Engine/World.h"

FVector2D GetGameViewportSize()
{
	FVector2D Result = FVector2D(1, 1);

	GEngine->GameViewport->GetViewportSize( /*out*/Result);

	return Result;
}

ATestHud::ATestHud()
{
	//do I really need these fucking if statements? maybe I should try to keep them its common convention
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarGrass_VMUI_1(TEXT("'/Game/Movies/videoMaterialsForUI/grass_VMUI_1.grass_VMUI_1'"));
	if (tempVarGrass_VMUI_1.Object != NULL)
	{
		grass_VMUI_1 = (UMaterial*)tempVarGrass_VMUI_1.Object;//why does this work but the next line doest? 
		//grass_VMUI_1 = &tempVarGrass_VMUI_1.Object; //error a value of type TObjectPtr<UMaterial>* cannot be assigned to entity of type UMaterial*
		//well because a cast tells the engine how to interpret the following data. in this case this achieves punning[sic] into the appropriate context
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarGrass_MP_1(TEXT("'/Game/Movies/mediaPlayers/grass_1_MP.grass_1_MP'"));
	if (tempVarGrass_MP_1.Object != NULL)
	{
		grass_MP_1 = (UMediaPlayer*)tempVarGrass_MP_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarGrass_IS_1(TEXT("'/Game/Movies/imageSources/grass_1_IS.grass_1_IS'"));
	if (tempVarGrass_IS_1.Object != NULL)
	{
		grass_MP_1->OpenSource((UImgMediaSource*)tempVarGrass_IS_1.Object);
	}

	//holes
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_holeFromDown_VMUI(TEXT("'/Game/Movies/videoMaterialsForUI/holeFromDown_VMUI.holeFromDown_VMUI'"));
	if (tempVar_holeFromDown_VMUI.Object != NULL)
	{
		holeFromDown_VMUI = (UMaterial*)tempVar_holeFromDown_VMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_holeFromLeft_VMUI(TEXT("'/Game/Movies/videoMaterialsForUI/holeFromLeft_VMUI.holeFromLeft_VMUI'"));
	if (tempVar_holeFromLeft_VMUI.Object != NULL)
	{
		holeFromLeft_VMUI = (UMaterial*)tempVar_holeFromLeft_VMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_holeFromRight_VMUI(TEXT("'/Game/Movies/videoMaterialsForUI/holeFromRight_VMUI.holeFromRight_VMUI'"));
	if (tempVar_holeFromRight_VMUI.Object != NULL)
	{
		holeFromRight_VMUI = (UMaterial*)tempVar_holeFromRight_VMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_holeFromUp_VMUI(TEXT("'/Game/Movies/videoMaterialsForUI/holeFromUp_VMUI.holeFromUp_VMUI'"));
	if (tempVar_holeFromUp_VMUI.Object != NULL)
	{
		holeFromUp_VMUI = (UMaterial*)tempVar_holeFromUp_VMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_holeFromDown_MP(TEXT("'/Game/Movies/mediaPlayers/holeFromDown_MP.holeFromDown_MP'"));
	if (tempVar_holeFromDown_MP.Object != NULL)
	{
		holeFromDown_MP = (UMediaPlayer*)tempVar_holeFromDown_MP.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_holeFromLeft_MP(TEXT("'/Game/Movies/mediaPlayers/HoleFromLeft_MP.HoleFromLeft_MP'"));
	if (tempVar_holeFromLeft_MP.Object != NULL)
	{
		holeFromLeft_MP = (UMediaPlayer*)tempVar_holeFromLeft_MP.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_holeFromRight_MP(TEXT("'/Game/Movies/mediaPlayers/holeFromRight_MP.holeFromRight_MP'"));
	if (tempVar_holeFromRight_MP.Object != NULL)
	{
		holeFromRight_MP = (UMediaPlayer*)tempVar_holeFromRight_MP.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_holeFromUp_MP(TEXT("'/Game/Movies/mediaPlayers/holeFromUp_MP.holeFromUp_MP'"));
	if (tempVar_holeFromUp_MP.Object != NULL)
	{
		holeFromUp_MP = (UMediaPlayer*)tempVar_holeFromUp_MP.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_holeFromDown_IS(TEXT("'/Game/Movies/imageSources/holeFromDown_IS.holeFromDown_IS'"));
	if (tempVar_holeFromDown_IS.Object != NULL)
	{
		holeFromDown_MP->OpenSource((UImgMediaSource*)tempVar_holeFromDown_IS.Object);
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_holeFromLeft_IS(TEXT("'/Game/Movies/imageSources/holeFromLeft_IS.holeFromLeft_IS'"));
	if (tempVar_holeFromLeft_IS.Object != NULL)
	{
		holeFromLeft_MP->OpenSource((UImgMediaSource*)tempVar_holeFromLeft_IS.Object);
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_holeFromRight_IS(TEXT("'/Game/Movies/imageSources/holeFromRight_IS.holeFromRight_IS'"));
	if (tempVar_holeFromRight_IS.Object != NULL)
	{
		holeFromRight_MP->OpenSource((UImgMediaSource*)tempVar_holeFromRight_IS.Object);
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_holeFromUp_IS(TEXT("'/Game/Movies/imageSources/holeFromUp_IS.holeFromUp_IS'"));
	if (tempVar_holeFromUp_IS.Object != NULL)
	{
		holeFromUp_MP->OpenSource((UImgMediaSource*)tempVar_holeFromUp_IS.Object);
	}


	//buttons or "intersections"
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromDownTurningRightZero_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromDown/one/buttonFromDownOneStraightStatic_SMUI.buttonFromDownOneStraightStatic_SMUI'"));
	if (tempVar_buttonFromDownTurningRightZero_SMUI.Object != NULL)
	{
		buttonFromDownTurningRightZero_SMUI = (UMaterial*)tempVar_buttonFromDownTurningRightZero_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromDownTurningLeftZero_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromDown/zero/buttonFromDownZeroStraightStatic_SMUI.buttonFromDownZeroStraightStatic_SMUI'"));
	if (tempVar_buttonFromDownTurningLeftZero_SMUI.Object != NULL)
	{
		buttonFromDownTurningLeftZero_SMUI = (UMaterial*)tempVar_buttonFromDownTurningLeftZero_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromLeftTurningRightZero_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromLeft/one/buttonFromLeftOneStraightStatic_SMUI.buttonFromLeftOneStraightStatic_SMUI'"));
	if (tempVar_buttonFromLeftTurningRightZero_SMUI.Object != NULL)
	{
		buttonFromLeftTurningRightZero_SMUI = (UMaterial*)tempVar_buttonFromLeftTurningRightZero_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromLeftTurningLeftZero_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromLeft/zero/buttonFromLeftZeroStraightStatic_SMUI.buttonFromLeftZeroStraightStatic_SMUI'"));
	if (tempVar_buttonFromLeftTurningLeftZero_SMUI.Object != NULL)
	{
		buttonFromLeftTurningLeftZero_SMUI = (UMaterial*)tempVar_buttonFromLeftTurningLeftZero_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromRightTurningRightZero_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromRight/one/buttonFromRightOneStraightStatic_SMUI.buttonFromRightOneStraightStatic_SMUI'"));
	if (tempVar_buttonFromRightTurningRightZero_SMUI.Object != NULL)
	{
		buttonFromRightTurningRightZero_SMUI = (UMaterial*)tempVar_buttonFromRightTurningRightZero_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromRightTurningLeftZero_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromRight/zero/buttonFromRightZeroStraightStatic_SMUI.buttonFromRightZeroStraightStatic_SMUI'"));
	if (tempVar_buttonFromRightTurningLeftZero_SMUI.Object != NULL)
	{
		buttonFromRightTurningLeftZero_SMUI = (UMaterial*)tempVar_buttonFromRightTurningLeftZero_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromUpTurningRightZero_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/FromUp/one/buttonFromUpOneStraightStatic_SMUI.buttonFromUpOneStraightStatic_SMUI'"));
	if (tempVar_buttonFromUpTurningRightZero_SMUI.Object != NULL)
	{
		buttonFromUpTurningRightZero_SMUI = (UMaterial*)tempVar_buttonFromUpTurningRightZero_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromUpTurningLeftZero_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/FromUp/zero/buttonFromUpZeroStraightStatic_SMUI.buttonFromUpZeroStraightStatic_SMUI'"));
	if (tempVar_buttonFromUpTurningLeftZero_SMUI.Object != NULL)
	{
		buttonFromUpTurningLeftZero_SMUI = (UMaterial*)tempVar_buttonFromUpTurningLeftZero_SMUI.Object;
	}

	//straight rail
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_verticleRail_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/verticleRail_SMUI.verticleRail_SMUI'"));
	if (tempVar_verticleRail_SMUI.Object != NULL)
	{
		verticleRail_SMUI = (UMaterial*)tempVar_verticleRail_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_horizontalRail_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/horizontalRail_SMUI.horizontalRail_SMUI'"));
	if (tempVar_horizontalRail_SMUI.Object != NULL)
	{
		horizontalRail_SMUI = (UMaterial*)tempVar_horizontalRail_SMUI.Object;
	}

	//turningRail
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_railTurningOne_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/railTurningOne_SMUI.railTurningOne_SMUI'"));
	if (tempVar_railTurningOne_SMUI.Object != NULL)
	{
		railTurningOne_SMUI = (UMaterial*)tempVar_railTurningOne_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_railTurningTwo_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/railTurningTwo_SMUI.railTurningTwo_SMUI'"));
	if (tempVar_railTurningTwo_SMUI.Object != NULL)
	{
		railTurningTwo_SMUI = (UMaterial*)tempVar_railTurningTwo_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_railTurningThree_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/railTurningThree_SMUI.railTurningThree_SMUI'"));
	if (tempVar_railTurningThree_SMUI.Object != NULL)
	{
		railTurningThree_SMUI = (UMaterial*)tempVar_railTurningThree_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_railTurningFour_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/railTurningFour_SMUI.railTurningFour_SMUI'"));
	if (tempVar_railTurningFour_SMUI.Object != NULL)
	{
		railTurningFour_SMUI = (UMaterial*)tempVar_railTurningFour_SMUI.Object;
	}

	//marbles
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_marble_SMUI_1(TEXT("'/Game/Movies/spriteMaterialsForUI/marble_SMUI_1.marble_SMUI_1'"));
	if (tempVar_marble_SMUI_1.Object != NULL)
	{
		marble_SMUI_1 = (UMaterial*)tempVar_marble_SMUI_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_marble_SMUI_2(TEXT("'/Game/Movies/spriteMaterialsForUI/marble_SMUI_2.marble_SMUI_2'"));
	if (tempVar_marble_SMUI_2.Object != NULL)
	{
		marble_SMUI_2 = (UMaterial*)tempVar_marble_SMUI_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_marble_SMUI_3(TEXT("'/Game/Movies/spriteMaterialsForUI/marble_SMUI_3.marble_SMUI_3'"));
	if (tempVar_marble_SMUI_3.Object != NULL)
	{
		marble_SMUI_3 = (UMaterial*)tempVar_marble_SMUI_3.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_marble_SMUI_4(TEXT("'/Game/Movies/spriteMaterialsForUI/marble_SMUI_4.marble_SMUI_4'"));
	if (tempVar_marble_SMUI_4.Object != NULL)
	{
		marble_SMUI_4 = (UMaterial*)tempVar_marble_SMUI_4.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_marble_SMUI_5(TEXT("'/Game/Movies/spriteMaterialsForUI/marble_SMUI_5.marble_SMUI_5'"));
	if (tempVar_marble_SMUI_5.Object != NULL)
	{
		marble_SMUI_5 = (UMaterial*)tempVar_marble_SMUI_5.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_marble_SMUI_6(TEXT("'/Game/Movies/spriteMaterialsForUI/marble_SMUI_6.marble_SMUI_6'"));
	if (tempVar_marble_SMUI_6.Object != NULL)
	{
		marble_SMUI_6 = (UMaterial*)tempVar_marble_SMUI_6.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_marble_SMUI_7(TEXT("'/Game/Movies/spriteMaterialsForUI/marble_SMUI_7.marble_SMUI_7'"));
	if (tempVar_marble_SMUI_7.Object != NULL)
	{
		marble_SMUI_7 = (UMaterial*)tempVar_marble_SMUI_7.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_emptyImg_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/emptyImg_SMUI.emptyImg_SMUI'"));
	if (tempVar_emptyImg_SMUI.Object != NULL)
	{
		emptyImg_SMUI = (UMaterial*)tempVar_emptyImg_SMUI.Object;
	}
}

void ATestHud::BeginPlay() // Ive got to put all of the code in this begin play for testing, but once everything is ironed out everything will be recompartmentalized for flow control
{
	Super::BeginPlay();

	if (GEngine && GEngine->GameViewport)
	{
		playerOnePlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		loadingSlateWidget = SNew(SLoadingScreenOne)
			.OwningHUD(this)
			.playerOnePlayerController(playerOnePlayerController);
			//.grass_VMUI_1(grass_VMUI_1);

		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(slateWidgetContainerOne, SWeakWidget).PossiblyNullContent(loadingSlateWidget.ToSharedRef()));
		
		//FSlateApplication::SetUserFocus(0, loadingSlateWidget);

		//FInputModeGameAndUI loadingScreenInputMode = FInputModeGameAndUI();
		FInputModeUIOnly loadingScreenInputMode = FInputModeUIOnly();
		loadingScreenInputMode.SetWidgetToFocus(loadingSlateWidget);
		loadingScreenInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		//loadingScreenInputMode.SetHideCursorDuringCapture(false);
		playerOnePlayerController->SetInputMode(loadingScreenInputMode);
		playerOnePlayerController->SetShowMouseCursor(true);
		FSlateApplication::Get().SetKeyboardFocus(loadingSlateWidget);

		//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, GetGameViewportSize().ToString());
	}

	GenerateLevel();
}

//the cherno says variables created at runtime do get garbage collected when the scope is breached, but javidx9 says pointers initiliazed at runtime certainly don't. so do I need to collect my own garbage?

void ATestHud::GenerateHolePositions() //this function appears to function as expected, however as it stands a first of a pair can spawn in the back row, right next to the second of the pair in the first row
{
	int firstIndexOfCurrentPortionOfViableHolePositionsTempVar;
	int firstIndexOfCurrentPortionOfViableHolePositions = 0;
	int indexOfPreviousEvenHolePosition = 1;
	FVector2D centerOfRotation = FVector2D(8, 8);
	int negativeOneZeroOrOne = FMath::RandRange(-1, 1);

	for (int a = 0; a < 12; a++)
	{
		for (int b = 0; b < 2; b++)
		{
			if ((15 - a) < FMath::Clamp((numberOfHoles - 4) / 2, 0, 6) + 9)
			{
				arrOfViableHoleCoordinates.Add(FVector2D(b + 14, 15 - a));
			}
			
		}
	}

	arrOfViableHoleCoordinates.Append(arrOfViableHoleCoordinatesBase);

	for (int a = 0; a < 13; a++)
	{
		for (int b = 0; b < 2; b++)
		{
			if ((4 + a) < FMath::Clamp((numberOfHoles - 4) / 2, 0, 6) + 9)
			{
				arrOfViableHoleCoordinates.Add(FVector2D(2 - b, a + 4));
			}

		}
	}

	/*for (FVector2D a : arrOfViableHoleCoordinates)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, a.ToString());
	}*/

	for (int a = 1; a < numberOfHoles + 1; a++)
	{
		int evenHoleRowCorrectionFigure = pow(2 - (indexOfPreviousEvenHolePosition % 2), (a - 1) % 2);

		firstIndexOfCurrentPortionOfViableHolePositionsTempVar = (arrOfViableHoleCoordinates.Num() / 2 / numberOfHoles * a + FMath::RoundHalfFromZero(((float)((arrOfViableHoleCoordinates.Num() / 2) % numberOfHoles) / (float)numberOfHoles) * a)) * 2;
		
		GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, FString::FromInt(firstIndexOfCurrentPortionOfViableHolePositionsTempVar));
		

		int currentHolePositionCoordinateIndex = (FMath::RandRange(0, ( ( firstIndexOfCurrentPortionOfViableHolePositionsTempVar - firstIndexOfCurrentPortionOfViableHolePositions ) / evenHoleRowCorrectionFigure ) - 1) * evenHoleRowCorrectionFigure) + firstIndexOfCurrentPortionOfViableHolePositions;

		test.Add(currentHolePositionCoordinateIndex);

		holePositions.Add(arrOfViableHoleCoordinates[currentHolePositionCoordinateIndex]);

		firstIndexOfCurrentPortionOfViableHolePositions = firstIndexOfCurrentPortionOfViableHolePositionsTempVar;

		if ((a - 1) % 2 == 0)
		{
			indexOfPreviousEvenHolePosition = currentHolePositionCoordinateIndex;
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, (FString)"------------");

	for (int a = 0; a < holePositions.Num(); a++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, holePositions[a].ToString() + "  " + FString::FromInt(test[a]));
	}

	GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, (FString)"------------");

	if (negativeOneZeroOrOne != 0)
	{
		holeCoordinateOrientation = 0;

		// elsewhere switches based on integers need to be consecutive this switch statement might glitch out
		switch (negativeOneZeroOrOne)
		{
		case -1 :
			for (int a = 0; a < holePositions.Num(); a++)
			{
				FVector2D adjustedHolePosition = holePositions[a] - centerOfRotation;

				holePositions[a] = FVector2D(adjustedHolePosition.Y + centerOfRotation.X, -1 * adjustedHolePosition.X + centerOfRotation.Y);
			}

			break;
		case 1 :
			for (int a = 0; a < holePositions.Num(); a++)
			{
				FVector2D adjustedHolePosition = holePositions[a] - centerOfRotation;

				holePositions[a] = FVector2D(-1 * adjustedHolePosition.Y + centerOfRotation.X, adjustedHolePosition.X + centerOfRotation.Y);
			}

			break;
		default:
			break;
		}
	}
	else
	{
		holeCoordinateOrientation = 1;
	}

	GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "hole orientation format: " + FString::FromInt(negativeOneZeroOrOne));

	for (FVector2D a : holePositions)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, a.ToString());
	}

	//I think this function works but needs more testing
	//I also need to test if integers always round to floor in c++ but thats a much more complex problem here in c++ than in the bluieprint visual scripting interface so maybe later
	
	/*   nested TArray example
	nestedTArr.Add({ 1, 2, 3 });
	nestedTArr.Add({ 4, 5, 6 });
	nestedTArr[0].Add(7);*/
}

void ATestHud::GenerateTrackShape()
{
	int cumulativeGroupingCoverage = 0;
	int countOfLoopsOne = 0;
	TArray<FVector2D> vector2DStorArrOne;
	TArray<int> intStorArrOne;
	int currentGroupSize;
	int unpairedHoleOrIntersectionDir = 0;
	FVector2D unpairedHoleOrIntersectionPos = FVector2D( 0, 0 );
	int currentFirstOfPairHoleDir;
	TArray<int> firstOfPairHoleDirStorArr;
	TArray<FVector2D> firstOfPairHoleOrIntersectionPosStorArr;
	FVector2D differenceInPairPosition;
	FVector2D differenceInPairPositionAbsolute;
	int differenceInPairPositionClampedX;
	int differenceInPairPositionClampedY;
	TArray<int> availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping;
	int currentATPPBOCLCG;
	TArray<int> verticleDistancesBetweenHolesOrIntersections;
	TArray<int> horizontalDistancesBetweenHolesOrIntersections;
	TArray<int> firstOfPairIsAboveSecondArr; //this array and firstOfPairIsEvenWithOrLeftOfSecondArr will need to have as many zeros as there are pairs for the first level of each group
	int currentFirstOfPairIsAboveSecond;
	TArray<int> firstOfPairIsEvenWithOrLeftOfSecondArr;
	int currentFirstOfPairIsEvenWithOrLeftOfSecond;
	TArray<TArray<int> > horizontalAndVerticleDistancesBetweenHolesOrIntersections = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
	TArray<int> relevantHorizontalAndVerticleDistances = { 0, 0 };
	TArray<int> whichOfEachPairsTurnsBecomesTheIntersection;
	TArray<int> turnDistancesFromFirstOfPairStorArr;
	TArray<int> amountOfTurnsPerDistance = { 0, 0 };
	TArray<int> turnDirectionsStorArr;// 0 for right, 1 for left, 2 for intersection, 3 for straight track
	TArray<int> oneZeroAlternatingArr = { 1, 0, 1, 0, 1 };
	TArray<int> zeroOneAlternatingArr = { 0, 1, 0, 1, 0 };
	TArray<int> currentFirstOfPairHoleOrIntersectionPositionXAndY = { 0, 0 };//X being first
	int currentTurnDistance;
	int previousTurnDistance;
	FVector2D currentIntersectionPos;
	int currentAxisTracker;
	int previousAxisTracker;
	TArray<int> currentIntersectionPosArrFormat = { 0, 0 };
	TArray<int> pairStartsOnSameSide;
	TArray<int> intersectionDirStorArr;
	TArray<int> intersectionOrientationStorArr;// 0 for right, 1 for left, 2 for straight
	TArray<int> intersectionAjustmentWeights;// 1 for first of pair, 2 for second of pair, 0 for neither
	FVector2D firstOfPairIntersectionPos;
	FVector2D secondOfPairIntersectionPos;
	int firstOfPairIntersectionDir;
	int secondOfPairIntersectionDir;
	bool oneLastThing = false;
	//int whichOfPairGetsAdjustmentTracker;
	//int priorGroupTopLevelAdjustment;

	// grouping holes in sets of 2, 4, or 8
	while (numberOfHoles > cumulativeGroupingCoverage)
	{
		switch (FMath::RandRange((int32)0, (int32)2))
		{
		case 0 :
			listOfHolePositionGroupings.Add(2);
			cumulativeGroupingCoverage += 2;
			break;
		case 1 :
			listOfHolePositionGroupings.Add(4);
			cumulativeGroupingCoverage += 4;
			break;
		case 2:
			listOfHolePositionGroupings.Add(8);
			cumulativeGroupingCoverage += 8;
			break;
		default:
			break;
		}
	}

	//cutting down the last grouping in the listOfHolePositionGroupings so the cummulative coverage is the same as the number of holes
	listOfHolePositionGroupings[listOfHolePositionGroupings.Num() - 1] = listOfHolePositionGroupings[listOfHolePositionGroupings.Num() - 1] - (cumulativeGroupingCoverage - numberOfHoles);

	//designating direction of the track leading away from the holes (its always toward the center) while grouping these designations to correspond with the holePositionGroupings, and reorganizing holePositions into holeAndIntersectionPositions while grouping them to correspond with holePositionGroupings. this is where the multi dimensional TArrays begin
	for (int a = 0; a < listOfHolePositionGroupings.Num(); a++)
	{
		for (int b = 1; b < listOfHolePositionGroupings[a] + 1; b++)
		{
			vector2DStorArrOne.Add(holePositions[countOfLoopsOne]);

			if (holePositions[countOfLoopsOne].X > holePositions[countOfLoopsOne].Y)
			{
				if (16 - holePositions[countOfLoopsOne].X > holePositions[countOfLoopsOne].Y)
				{
					intStorArrOne.Add(1);
				}
				else
				{
					intStorArrOne.Add(4);
				}
			}
			else
			{
				if (holePositions[countOfLoopsOne].X > 16 - holePositions[countOfLoopsOne].Y)
				{
					intStorArrOne.Add(3);
				}
				else
				{
					intStorArrOne.Add(2);
				}
			}

			countOfLoopsOne++;
		}
		arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[0][a] = intStorArrOne;

		holeAndIntersectionPositions[0][a] = vector2DStorArrOne;

		intStorArrOne.Empty();
		vector2DStorArrOne.Empty();

	}
	countOfLoopsOne = 0;

	GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, (FString)"------------");

	for (int a = 0; a < listOfHolePositionGroupings.Num(); a++)
	{
		for (int b = 0; b < holeAndIntersectionPositions[0][a].Num(); b++)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, holeAndIntersectionPositions[0][a][b].ToString() + " | direction of hole: " + FString::FromInt(arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[0][a][b]) + "  " + " | current grouping: " + FString::FromInt(a));
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, (FString)"------------");
	 
	// This is where the master loop containing the all of the remaining sub processes for laying out the track is declared and initialized. Once this is done looping and the resulting data has been packaged, the track is ready for assembly.
	// make sure to write code to continue laying out straight track if there is any distance remaining after all the turns are layed
	//so I think once this completes I will promote all the results into the same group on the 4th level and run the level stuff loop one last time. if it works out like this you can change the permanent storage to only have 1 group for the fourth level and beyond. this would restrict you to a maximum of 16 holes but thats probably enough
	// so I still need to promote the foundational groups to the final group in the fourth level, run all of this for said final group, then lay out the track from the completed structure to a designated track starting point
	for (int currentGroupIndex = 0; currentGroupIndex < listOfHolePositionGroupings.Num(); currentGroupIndex++)
	{
		currentGroupSize = listOfHolePositionGroupings[currentGroupIndex];

		GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, (FString)"------------");

		GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "current group size: " + FString::FromInt(currentGroupSize) + "  | number of levels calculated: " + FString::FromInt(FMath::Clamp(FMath::RoundHalfFromZero((float)currentGroupSize / 2.0f), 1, 3)) + "  |  current group index: " + FString::FromInt(currentGroupIndex));

		for (int currentLevelIndex = 0; currentLevelIndex <= FMath::Clamp(FMath::RoundHalfFromZero((float)currentGroupSize / 2.0f), 1, 3) - 1; currentLevelIndex++)
		{
			if (currentLevelIndex == 0)
			{
				firstOfPairIsAboveSecondArr.Empty();
				firstOfPairIsEvenWithOrLeftOfSecondArr.Empty();
				intersectionAjustmentWeights.Empty();

				for (int a = 0; a < currentGroupSize / 2; a++)
				{
					firstOfPairIsAboveSecondArr.Add(0);
					firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
					intersectionAjustmentWeights.Add(0);
				}

				//do I need to permanently store intersection adjustment weights here?
				firstOfPairIsAboveSecondAllPairs[0][currentGroupIndex] = firstOfPairIsAboveSecondArr;
				firstOfPairIsEvenWithOrLeftOfSecondAllPairs[0][currentGroupIndex] = firstOfPairIsEvenWithOrLeftOfSecondArr;

				vector2DStorArrOne = holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex];
				intersectionDirStorArr = arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[currentLevelIndex][currentGroupIndex];
			}
			
			if (intersectionDirStorArr.Num() % 2 == 1)
			{
				unpairedHoleOrIntersectionDir = intersectionDirStorArr[intersectionDirStorArr.Num() - 1];
				unpairedHoleOrIntersectionPos = vector2DStorArrOne[vector2DStorArrOne.Num() - 1];
			}
			GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "--");
			GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "current level index: " + FString::FromInt(currentLevelIndex));

			// designating the amount of turns to the next intersection per pair of holes or intersections, getting the distance between the holes or intersections and then getting the horizontal and verticle distance between the holes or intersections. Then checking if the first hole or intersection of a pair is "above" the other.

			// *** you are currently checking if first of pair is above second of pair, you should add a check to see if first of pair is right of second of pair, or directly bellow/ left of second of pair. you should also space all intersections (not including "bottom level" intersections) to be at least 3 squares from the last (or four if numberOfHoles <= 8?) ***

			// *** to space the intersections you can alter one of the pairs starting position. Which of the pairs starting position (if any at all) gets altered can be determined by the horizontal and verticle distances (if you also consider prior alterations as apart of the current alteration calculation maybe you can create a self balancing scheme). But this will still leave chance for sub optimal spacing or even overlap to occur. could you check for errors like this somehow, and in their event attempt to regenerate? ***
			//I can space the intersections at the very end of these level loops that way it isnt applied to the bottom level and is fully executed for the following level

			// *** to force the pairs to work toward the middle I could flip the which of each pair is first and which is second for every pair at index > quantityOfPairs/2, however I dont actually think this would have any impact at all on gameplay

			// *** what are you doing for any case where there is verticle or horizontal distance still left between the last turn and the second hole of the pair? this occurs when firstOfPairIsAboveSecond and amountOfTurnsPerPair is 2, and when..

			//am I using absolute value properly when determining horizontal and verticle distance?
			 
			for (int a = 1; a <= intersectionDirStorArr.Num() / 2; a++)//this won't run if there is only one element in the current group
			{
				currentFirstOfPairHoleDir = intersectionDirStorArr[a * 2 - 2];
				firstOfPairHoleDirStorArr.Add(currentFirstOfPairHoleDir);
				firstOfPairHoleOrIntersectionPosStorArr.Add(vector2DStorArrOne[a * 2 - 2]);

				//this will need to be recalculated to use the vector2DStorArr

				differenceInPairPosition = firstOfPairHoleOrIntersectionPosStorArr[a - 1] - vector2DStorArrOne[a * 2 - 1];
				differenceInPairPositionAbsolute = differenceInPairPosition.GetAbs();
				differenceInPairPositionClampedX = FMath::Clamp( FMath::RoundToZero((float)differenceInPairPositionAbsolute.X / 2), 0, 2);
				differenceInPairPositionClampedY = FMath::Clamp( FMath::RoundToZero((float)differenceInPairPositionAbsolute.Y / 2), 0, 2);
				//this needs to be altered to take into consideration if firstOfPairIsAboveSecond and if firstOfPairIsEvenWithOrLeftOfSecond. if the pair starts on the same side and firstOfPairIsAboveSecond the verticleDistance must equal the differenceInPairPositionAbsolute unmodified. if the pair starts on different sides and firstOfPairIsEvenWithOrLeftOfSecond horizontalDistance must equal the differenceInPairPositionAbsolute + 1, if the pair starts on different sides and firstOfPairIsAboveSecond verticleDistance must equal the differenceInPairPositionAbsolute + 1

				currentFirstOfPairIsAboveSecond = firstOfPairIsAboveSecondArr[a - 1];
				currentFirstOfPairIsEvenWithOrLeftOfSecond = firstOfPairIsEvenWithOrLeftOfSecondArr[a - 1];

				if (currentFirstOfPairHoleDir == intersectionDirStorArr[a * 2 - 1])
				{
					pairStartsOnSameSide.Add(1);

					if (differenceInPairPositionClampedX <= differenceInPairPositionClampedY)
					{
						availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Add(FMath::RandRange(0, differenceInPairPositionClampedX) * 2 + 2);
					}
					else
					{
						availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Add(FMath::RandRange(0, differenceInPairPositionClampedY) * 2 + 2);
					}

					if (currentFirstOfPairIsAboveSecond)
					{
						switch (currentFirstOfPairHoleDir % 2)
						{// remember for both pairStartsOnSameSide and pairStartsOnDiffSides when determining future intersection pos you alter the firstOfPairHoleOrIntersectionPos temporarily to complete that calculation CORRECTION: I am changing this, but this means when laying out the track I will need to lay for the difference between the current section of the current orientation of distance and the previous of the current.
						case 0:
							horizontalDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.Y);
							verticleDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.X - 1);
							break;
						case 1:
							horizontalDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.X);//do I need to roundHalfFromZero here or will it translate properly every time here. this could be a good chance to practice writing an error message generator
							verticleDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.Y - 1);
							break;
						default:
							break;
						}
					}
					else if (currentFirstOfPairIsEvenWithOrLeftOfSecond)
					{
						switch (currentFirstOfPairHoleDir % 2)
						{
						case 0:
							horizontalDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.Y + 1);
							verticleDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.X + 1);
							break;
						case 1:
							horizontalDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.X + 1);
							verticleDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.Y + 1);
							break;
						default:
							break;
						}
					}
					else
					{
						switch (currentFirstOfPairHoleDir % 2)
						{
						case 0:
							horizontalDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.Y);
							verticleDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.X + 1);
							break;
						case 1:
							horizontalDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.X);
							verticleDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.Y + 1);
							break;
						default:
							break;
						}
					}
				}
				else
				{// in the case of if a pair starts on different sides and the first of the pair is above the second the pair will need to have at least three turns. the same is true if the first of the pair is evenWithOrLeftOfSecond
					pairStartsOnSameSide.Add(0);

					if (differenceInPairPositionClampedX <= differenceInPairPositionClampedY)
					{
						availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Add(FMath::RandRange( FMath::Clamp(firstOfPairIsAboveSecondArr[a -1] + firstOfPairIsEvenWithOrLeftOfSecondArr[a - 1], 0, 1), differenceInPairPositionClampedX) * 2 + 1);// I just took off a * 2 from the end of the first argument of the RandRange 01/17/24
					}
					else
					{
						availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Add(FMath::RandRange( FMath::Clamp(firstOfPairIsAboveSecondArr[a - 1] + firstOfPairIsEvenWithOrLeftOfSecondArr[a - 1], 0, 1), differenceInPairPositionClampedY) * 2 + 1);
					}

					if (currentFirstOfPairIsAboveSecond)
					{
						switch (currentFirstOfPairHoleDir % 2)
						{
						case 0:
							horizontalDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.Y - 1);
							verticleDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.X); //just changed this from +1 to + nothing 01/17/24 
							break;
						case 1:
							horizontalDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.X - 1);
							verticleDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.Y); //just changed this from +1 to + nothing 01/17/24 
							break;
						default:
							break;
						}
					}
					else if (currentFirstOfPairIsEvenWithOrLeftOfSecond)
					{
						switch (currentFirstOfPairHoleDir % 2)
						{
						case 0:
							horizontalDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.Y + 1);
							verticleDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.X);
							break;
						case 1:
							horizontalDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.X + 1);
							verticleDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.Y);
							break;
						default:
							break;
						}
					}
					else
					{
						switch (currentFirstOfPairHoleDir % 2)
						{
						case 0:
							horizontalDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.Y - 1);
							verticleDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.X);
							break;
						case 1:
							horizontalDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.X - 1);
							verticleDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.Y);
							break;
						default:
							break;
						}
					}
				}

				if ( currentLevelIndex == 0)
				{
					GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "pair " + FString::FromInt(a-1) + " | turns: " + FString::FromInt(availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping[a - 1]) + " | difference in pair position: " + differenceInPairPosition.ToString() + " | horizontal distance: " + FString::FromInt(horizontalDistancesBetweenHolesOrIntersections[horizontalDistancesBetweenHolesOrIntersections.Num() - 1]) + ", verticle distance: " + FString::FromInt(verticleDistancesBetweenHolesOrIntersections[verticleDistancesBetweenHolesOrIntersections.Num() - 1]));
				}
				//for pairs starting on different sides have you decided how to determine which direction their intersection will face? yes they will take the direction of whichever side they are closest to unless firstOfPairIsAboveSecond or firstOfPairIsEvenWithOrLeftOfSecond
			}

			horizontalAndVerticleDistancesBetweenHolesOrIntersections[0] = horizontalDistancesBetweenHolesOrIntersections;
			horizontalAndVerticleDistancesBetweenHolesOrIntersections[1] = verticleDistancesBetweenHolesOrIntersections;
			
			if (currentGroupIndex == listOfHolePositionGroupings.Num() - 1 && currentLevelIndex == 0)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, (FString)"size of this group and level's availableTurnsArr: " + FString::FromInt(availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Num()) + " | FMath randrange test: " + FString::FromInt(FMath::RandRange(3, 1)));
			}
			GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "size of availableTurnsPerPairBlock : " + FString::FromInt(availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Num()) + " | first value of availableTurnsPerPairBlock : " + FString::FromInt(availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping[0]) + " | size of pair orientation arrs firstOfPairAboveSecond first: " + FString::FromInt(firstOfPairIsAboveSecondArr.Num()) + " " + FString::FromInt(firstOfPairIsEvenWithOrLeftOfSecondArr.Num()) + " | length of horizontal and verticle distance arrays: " + FString::FromInt(horizontalAndVerticleDistancesBetweenHolesOrIntersections[0].Num()) + " " + FString::FromInt(horizontalAndVerticleDistancesBetweenHolesOrIntersections[1].Num()));

			//using the availableTurnsPerPair list to assign which of the turns given to each pair becomes the intersection. for pairs of holes that start on the same side of the grid for the even indexed holes if the even indexed hole is below the odd indexed hole the intersection will be placed at the last turn or any odd indexed turn. for cases in which the even indexed hole is above the odd the intersection will be placed at the first turn or any even indexed turn. for pairs of holes starting on different sides of the track the intersection can be placed at any left turn but it should alternate based on where the last turn was placed?..
			//I will need to generate new logic for if firstOfpair is left of second, for if firstOfPair is even with second, and also for both of those things if first of pair is above second
			//I still need to adjust the if pairs start on same side condition to include the possibility of firstOfPairIsEvenWithOrLeftOfSecond
			//I still need to account for the intersection adjustment weights when calculating which of turns becomes intersection when firstOfPair is not above second, and firstOfPair is not left of second.
			for (int a = 0; a < availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Num(); a++)
			{
				currentATPPBOCLCG = availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping[a];

				if (currentATPPBOCLCG % 2)
				{//pairs starting on different sides
					if (firstOfPairIsEvenWithOrLeftOfSecondArr[a])
					{
						whichOfEachPairsTurnsBecomesTheIntersection.Add(currentATPPBOCLCG - FMath::RandRange(0, FMath::DivideAndRoundDown(currentATPPBOCLCG - 2, 2)));
					}
					else if (firstOfPairIsAboveSecondArr[a])//this gets treated just like if the pair started on the same side ACCEPT if pairs start on same side AND first of pair is above second the resulting intersection would have to take the direction of the first of the pair.
					{
						whichOfEachPairsTurnsBecomesTheIntersection.Add(FMath::RandRange( 1, 2 ));//maybe this should take into consideration whether the resulting intersection will be the first or second of its pair 
					}
					else
					{
						//Im excluding the first turn from the possibilities when theres more than one turn because that could be an issue - wait what?! how? fuck it Im just gonna pretend like I didnt see this
						//minus when intersectionAdjustmentWeights = 2, plus when intersectionAdjustmentWeights = 1
						//this works for both if weights and if not
						whichOfEachPairsTurnsBecomesTheIntersection.Add((currentATPPBOCLCG* (1 - (intersectionAjustmentWeights[a] % 2))) + (intersectionAjustmentWeights[a] % 2) + (-1 + ((intersectionAjustmentWeights[a] % 2) * 2)) * FMath::RandRange(0, FMath::DivideAndRoundDown(currentATPPBOCLCG - 2, 2)) * 2);
					}
				}
				else
				{// pairs starting on the same side
					if (firstOfPairIsAboveSecondArr[a])
					{
						whichOfEachPairsTurnsBecomesTheIntersection.Add(FMath::RandRange(1, currentATPPBOCLCG / 2) * 2);
						whichOfEachPairsTurnsBecomesTheIntersection[a] = whichOfEachPairsTurnsBecomesTheIntersection[a] - FMath::RandRange(0, 3 - whichOfEachPairsTurnsBecomesTheIntersection[a]);
					}
					else if (firstOfPairIsEvenWithOrLeftOfSecondArr[a])
					{
						whichOfEachPairsTurnsBecomesTheIntersection.Add(currentATPPBOCLCG - FMath::RandRange(0, 1));
					}
					else 
					{
						whichOfEachPairsTurnsBecomesTheIntersection.Add((currentATPPBOCLCG* (1 - (intersectionAjustmentWeights[a] % 2))) + (intersectionAjustmentWeights[a] % 2) + (-1 + ((intersectionAjustmentWeights[a] % 2) * 2)) * FMath::RandRange(0, 1));//does this rand range need to only be zero unless #ofTurns > 2? no, Im certain
					}
				}
			}
			

			//determining how far along the total quantity of verticle or horizontal distance a turn is placed given a pair's verticle and lateral positioning relevant to each other
			for (int currentPair = 0; currentPair < availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Num(); currentPair++)
			{
				currentATPPBOCLCG = availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping[currentPair];
				currentFirstOfPairIsAboveSecond = firstOfPairIsAboveSecondArr[currentPair];
				currentFirstOfPairIsEvenWithOrLeftOfSecond = firstOfPairIsEvenWithOrLeftOfSecondArr[currentPair];

				if (currentFirstOfPairIsAboveSecond)
				{
					turnDistancesFromFirstOfPairStorArr.Add(-1);//okay SO this will be zero, but this means when I actually place the track I will need to write a condition for if firstOfPairIsAboveSecond which alters first of pairs intersection position just like in the determining intersection postion section
				}

				if (currentFirstOfPairIsEvenWithOrLeftOfSecond && pairStartsOnSameSide[currentPair])
				{
					currentATPPBOCLCG -= 1;
					oneLastThing = true;
				}

				relevantHorizontalAndVerticleDistances[0] = horizontalAndVerticleDistancesBetweenHolesOrIntersections[0][currentPair];
				relevantHorizontalAndVerticleDistances[1] = horizontalAndVerticleDistancesBetweenHolesOrIntersections[1][currentPair];

				amountOfTurnsPerDistance[1] = FMath::DivideAndRoundDown(currentATPPBOCLCG, 2) + (currentATPPBOCLCG % 2);
				amountOfTurnsPerDistance[0] = FMath::DivideAndRoundDown(currentATPPBOCLCG, 2);

				//this approach will actually cause a problem if a pair starts on different sides and first of pair is above second. in this case the last horizontal turn would overshoot? actually nevermind it wouldn't i dont think
				for (int a = 1 + currentFirstOfPairIsAboveSecond; a <= currentATPPBOCLCG; a++)
				{
					turnDistancesFromFirstOfPairStorArr.Add((relevantHorizontalAndVerticleDistances[a % 2] / amountOfTurnsPerDistance[a % 2])* FMath::RoundHalfFromZero((float)a / 2.0f) + FMath::RoundHalfFromZero(((float)(relevantHorizontalAndVerticleDistances[a % 2] % amountOfTurnsPerDistance[a % 2]) / (float)amountOfTurnsPerDistance[a % 2]) * FMath::RoundHalfFromZero((float)a / 2.0f)));
				}

				if (oneLastThing)
				{
					turnDistancesFromFirstOfPairStorArr.Add(relevantHorizontalAndVerticleDistances[0] - 1);
					oneLastThing = false;
				}

				turnAndIntersectionDistancesPerPair[currentLevelIndex][currentGroupIndex][currentPair] = turnDistancesFromFirstOfPairStorArr;
				turnDistancesFromFirstOfPairStorArr.Empty();
			}

			// sets the appropriate turn directions for each turn for the track between each pair of holes or intersections. 0 for right, 1 for left. and then a 2 for the intersection?.. and a 3 for straight track
			//still need to determine turn direction if pair starts on same side and firstOfPairIsEvenWithOrLeftOfSecond
			for (int currentPair = 0; currentPair < availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Num(); currentPair++)
			{
				currentATPPBOCLCG = availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping[currentPair];
				
				if (currentATPPBOCLCG % 2)
				{//pairs starting on different sides
					if (firstOfPairIsEvenWithOrLeftOfSecondArr[currentPair])
					{
						for (int b = 0; b < currentATPPBOCLCG - 1; b++)
						{
							turnDirectionsStorArr.Add(zeroOneAlternatingArr[b]);
						}

						turnDirectionsStorArr.Add(1);

						turnDirectionsStorArr[whichOfEachPairsTurnsBecomesTheIntersection[currentPair] - 1] = 2;//is this - 1 correct? I think so..

						directionsOfTurns[currentLevelIndex][currentGroupIndex][currentPair] = turnDirectionsStorArr;

						turnDirectionsStorArr.Empty();
					}
					else if (firstOfPairIsAboveSecondArr[currentPair])
					{
						turnDirectionsStorArr.Add(1);

						for (int b = 0; b < currentATPPBOCLCG - 1; b++)
						{
							turnDirectionsStorArr.Add(oneZeroAlternatingArr[b]);
						}

						turnDirectionsStorArr[whichOfEachPairsTurnsBecomesTheIntersection[currentPair] - 1] = 2;//is this - 1 correct? I think so..

						directionsOfTurns[currentLevelIndex][currentGroupIndex][currentPair] = turnDirectionsStorArr;

						turnDirectionsStorArr.Empty();
					}
					else
					{
						for (int b = 0; b < currentATPPBOCLCG; b++)
						{
							turnDirectionsStorArr.Add(oneZeroAlternatingArr[b]);
						}

						turnDirectionsStorArr[whichOfEachPairsTurnsBecomesTheIntersection[currentPair] - 1] = 2;//is this - 1 correct? I think so..

						directionsOfTurns[currentLevelIndex][currentGroupIndex][currentPair] = turnDirectionsStorArr;

						turnDirectionsStorArr.Empty();
					}
				}
				else
				{//pairs starting on the same side
					if (firstOfPairIsAboveSecondArr[currentPair])
					{
						turnDirectionsStorArr.Add(1);

						for (int b = 0; b < currentATPPBOCLCG - 1; b++)
						{
							turnDirectionsStorArr.Add(oneZeroAlternatingArr[b]);
						}

						turnDirectionsStorArr[whichOfEachPairsTurnsBecomesTheIntersection[currentPair] - 1] = 2;//is this - 1 correct? I think so..

						directionsOfTurns[currentLevelIndex][currentGroupIndex][currentPair] = turnDirectionsStorArr;

						turnDirectionsStorArr.Empty();
					}
					else if (firstOfPairIsEvenWithOrLeftOfSecondArr[currentPair])
					{
						for (int b = 0; b < currentATPPBOCLCG - 3; b++)
						{
							turnDirectionsStorArr.Add(zeroOneAlternatingArr[b]);
						}
						turnDirectionsStorArr.Append({ 1, 1, 1 });

						turnDirectionsStorArr[whichOfEachPairsTurnsBecomesTheIntersection[currentPair] - 1] = 2;//is this - 1 correct? I think so..

						directionsOfTurns[currentLevelIndex][currentGroupIndex][currentPair] = turnDirectionsStorArr;

						turnDirectionsStorArr.Empty();
					}
					else
					{
						for (int b = 0; b < currentATPPBOCLCG - 1; b++)
						{
							turnDirectionsStorArr.Add(oneZeroAlternatingArr[b]);
						}

						turnDirectionsStorArr.Add(1);

						turnDirectionsStorArr[whichOfEachPairsTurnsBecomesTheIntersection[currentPair] - 1] = 2;//is this - 1 correct? I think so..

						directionsOfTurns[currentLevelIndex][currentGroupIndex][currentPair] = turnDirectionsStorArr;

						turnDirectionsStorArr.Empty();
					} 
				}
			}

			// determining the intersection location. I will also need to rework the first section of this master loop and at the very least determine firstOfPairIsAboveSecond and firstOfPairIsEvenWithOrLeftOfSecond here. As apart of determining intersection Position I will also need to "reposition" the intersections of all future pairs which you will weight to recieve an in intersection in close proximity
			vector2DStorArrOne.Empty();

			for (int currentPairIndex = 0; currentPairIndex < availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Num(); currentPairIndex++)//Im not sure if this needs to run every pair or every holeOrIntersection, I think its pair
			{
				turnDistancesFromFirstOfPairStorArr = turnAndIntersectionDistancesPerPair[currentLevelIndex][currentGroupIndex][currentPairIndex];
				currentFirstOfPairHoleOrIntersectionPositionXAndY[0] = firstOfPairHoleOrIntersectionPosStorArr[currentPairIndex].X;
				currentFirstOfPairHoleOrIntersectionPositionXAndY[1] = firstOfPairHoleOrIntersectionPosStorArr[currentPairIndex].Y;

				/*if (firstOfPairIsAboveSecondArr[currentPair])
				{
					switch (firstOfPairHoleDirStorArr[currentPair])
					{
					case 1 :
						currentFirstOfPairHoleOrIntersectionPositionXAndY[0] = firstOfPairHoleOrIntersectionPosStorArr[currentPair].X;
						currentFirstOfPairHoleOrIntersectionPositionXAndY[1] = firstOfPairHoleOrIntersectionPosStorArr[currentPair].Y + 1;
						break;
					case 2 : 
						currentFirstOfPairHoleOrIntersectionPositionXAndY[0] = firstOfPairHoleOrIntersectionPosStorArr[currentPair].X + 1;
						currentFirstOfPairHoleOrIntersectionPositionXAndY[1] = firstOfPairHoleOrIntersectionPosStorArr[currentPair].Y;
						break;
					case 3 :
						currentFirstOfPairHoleOrIntersectionPositionXAndY[0] = firstOfPairHoleOrIntersectionPosStorArr[currentPair].X;
						currentFirstOfPairHoleOrIntersectionPositionXAndY[1] = firstOfPairHoleOrIntersectionPosStorArr[currentPair].Y - 1;
						break;
					case 4 :
						currentFirstOfPairHoleOrIntersectionPositionXAndY[0] = firstOfPairHoleOrIntersectionPosStorArr[currentPair].X - 1;
						currentFirstOfPairHoleOrIntersectionPositionXAndY[1] = firstOfPairHoleOrIntersectionPosStorArr[currentPair].Y;
						break;
					default:
						break;
					}
				}
				else
				{
					currentFirstOfPairHoleOrIntersectionPositionXAndY[0] = firstOfPairHoleOrIntersectionPosStorArr[currentPair].X;
					currentFirstOfPairHoleOrIntersectionPositionXAndY[1] = firstOfPairHoleOrIntersectionPosStorArr[currentPair].Y;
				}*/
				//so now all I have to do today is finish this code section, and change the firstOfPairIsAboveSecond and firstOfPairIsEvenWithOrLeftOfSecond calculation to on this level after this. can you interweave adjusting the intersection position? come to think of it that will need to occur before calculating firstOfPairIsAboveSecond and firstOfPairIsEvenWithOrLeftOfSecond

				currentTurnDistance = turnDistancesFromFirstOfPairStorArr[whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] - 1];
				currentAxisTracker = whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex];
				previousAxisTracker = currentAxisTracker + 1;// I just switched previousAxisTracker = current - 1 to + 1 because -1 mod 2 = -1
				if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] != 1)
				{
					previousTurnDistance = turnDistancesFromFirstOfPairStorArr[whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] - 2];//this should be a minus 2 
				}
				else
				{
					previousTurnDistance = 0;

				}

				//cases where firstOfPairIsAboveSecond are more complicated. I have settled on setting the first turn from the firstOfPair to be -1 which should function properly now. however when I build the level I will need to pay special attention to this
				//new problem: how is intersection position being solved when pair starts on the same side and firstOfPairIsEvenWithOrLeftOfOdd? currently I am calculating to differenceInPairPositionAbsolute.Y + 1 and differenceInPairPositionAbsolute.X + 1, and due to a technique being applied in the above code covering turnAndIntersectionDistances I should be able to find the intersectionPos when thePairStartsOnTheSameSide and firstOfPairIsEvenWithOrLeftOfSecond just the same as how it is found otherwise. due to this same technique I should be able to lay the track or determine intersectionPos or turnDistance for any turn including the last just using the position of the firstOfPair

				switch (firstOfPairHoleDirStorArr[currentPairIndex])
				{
				case 1 :
					if (firstOfPairIsAboveSecondArr[currentPairIndex])//you still need to adjust how horizontal and verticle distances are calculated to account for if firstOfPairIsAboveSecond or if firstOfPairIsEvenWithOrLeftOfSecond
					{
						currentIntersectionPosArrFormat[currentAxisTracker % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[currentAxisTracker % 2] - currentTurnDistance;

						currentIntersectionPosArrFormat[previousAxisTracker % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[previousAxisTracker % 2] - previousTurnDistance;

						currentIntersectionPos.X = currentIntersectionPosArrFormat[0];
						currentIntersectionPos.Y = currentIntersectionPosArrFormat[1];
						vector2DStorArrOne.Add(currentIntersectionPos);
					}
					else if (firstOfPairIsEvenWithOrLeftOfSecondArr[currentPairIndex])
					{
						currentIntersectionPosArrFormat[currentAxisTracker % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[currentAxisTracker % 2] + currentTurnDistance;

						currentIntersectionPosArrFormat[previousAxisTracker % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[previousAxisTracker % 2] + previousTurnDistance;

						currentIntersectionPos.X = currentIntersectionPosArrFormat[0];
						currentIntersectionPos.Y = currentIntersectionPosArrFormat[1];
						vector2DStorArrOne.Add(currentIntersectionPos);
					}
					else
					{
						currentIntersectionPosArrFormat[currentAxisTracker % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[currentAxisTracker % 2] + (-1 + ((currentAxisTracker % 2) * 2)) * currentTurnDistance;//you have encountered an unexpected issue. if the currentIntersection is on verticle distance you need to add the currentTurnDistance. if the currentIntersection is on horizontal distance you need to subtract the currentTurnDistance. to solve this include (-1 * (currentIntersection % 2)) *
						currentIntersectionPosArrFormat[previousAxisTracker % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[previousAxisTracker % 2] + (-1 + ((previousAxisTracker % 2) * 2)) * previousTurnDistance;

						currentIntersectionPos.X = currentIntersectionPosArrFormat[0];
						currentIntersectionPos.Y = currentIntersectionPosArrFormat[1];
						vector2DStorArrOne.Add(currentIntersectionPos);
					}

					break;
				case 2 : 
					if (firstOfPairIsAboveSecondArr[currentPairIndex])
					{
						currentIntersectionPosArrFormat[currentAxisTracker % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[(currentAxisTracker - 1) % 2] + (1 - ((currentAxisTracker % 2) * 2)) * currentTurnDistance;

						currentIntersectionPosArrFormat[previousAxisTracker % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[(previousAxisTracker - 1) % 2] + (1 - ((previousAxisTracker % 2) * 2)) * currentTurnDistance;

						currentIntersectionPos.X = currentIntersectionPosArrFormat[0];
						currentIntersectionPos.Y = currentIntersectionPosArrFormat[1];
						vector2DStorArrOne.Add(currentIntersectionPos);
					}
					else if (firstOfPairIsEvenWithOrLeftOfSecondArr[currentPairIndex])
					{
						currentIntersectionPosArrFormat[(currentAxisTracker - 1) % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[(currentAxisTracker - 1) % 2] + (-1 + ((currentAxisTracker % 2) * 2)) * currentTurnDistance;

						currentIntersectionPosArrFormat[(previousAxisTracker - 1) % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[(previousAxisTracker - 1) % 2] + (-1 + ((previousAxisTracker % 2) * 2)) * currentTurnDistance;

						currentIntersectionPos.X = currentIntersectionPosArrFormat[0];
						currentIntersectionPos.Y = currentIntersectionPosArrFormat[1];
						vector2DStorArrOne.Add(currentIntersectionPos);
					}
					else
					{
						currentIntersectionPosArrFormat[(currentAxisTracker - 1) % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[(currentAxisTracker - 1) % 2] + currentTurnDistance;

						currentIntersectionPosArrFormat[(previousAxisTracker - 1) % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[(previousAxisTracker - 1) % 2] + previousTurnDistance;

						currentIntersectionPos.X = currentIntersectionPosArrFormat[0];
						currentIntersectionPos.Y = currentIntersectionPosArrFormat[1];
						vector2DStorArrOne.Add(currentIntersectionPos);
					}

					break;
				case 3 :
					if (firstOfPairIsAboveSecondArr[currentPairIndex])
					{
						currentIntersectionPosArrFormat[currentAxisTracker % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[currentAxisTracker % 2] + currentTurnDistance;

						currentIntersectionPosArrFormat[previousAxisTracker % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[previousAxisTracker % 2] + previousTurnDistance;

						currentIntersectionPos.X = currentIntersectionPosArrFormat[0];
						currentIntersectionPos.Y = currentIntersectionPosArrFormat[1];
						vector2DStorArrOne.Add(currentIntersectionPos);
					}
					else if (firstOfPairIsEvenWithOrLeftOfSecondArr[currentPairIndex])
					{
						currentIntersectionPosArrFormat[currentAxisTracker % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[currentAxisTracker % 2] - currentTurnDistance;

						currentIntersectionPosArrFormat[previousAxisTracker % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[previousAxisTracker % 2] - previousTurnDistance;

						currentIntersectionPos.X = currentIntersectionPosArrFormat[0];
						currentIntersectionPos.Y = currentIntersectionPosArrFormat[1];
						vector2DStorArrOne.Add(currentIntersectionPos);
					}
					else
					{
						currentIntersectionPosArrFormat[currentAxisTracker % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[currentAxisTracker % 2] + (1 - ((currentAxisTracker % 2) * 2)) * currentTurnDistance;

						currentIntersectionPosArrFormat[previousAxisTracker % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[previousAxisTracker % 2] + (1 - ((previousAxisTracker % 2) * 2)) * previousTurnDistance;

						currentIntersectionPos.X = currentIntersectionPosArrFormat[0];
						currentIntersectionPos.Y = currentIntersectionPosArrFormat[1];
						vector2DStorArrOne.Add(currentIntersectionPos);
					}

					break;
				case 4 :
					if (firstOfPairIsAboveSecondArr[currentPairIndex])
					{
						currentIntersectionPosArrFormat[(currentAxisTracker - 1) % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[(currentAxisTracker - 1) % 2] + (-1 + ((currentAxisTracker % 2) * 2)) * currentTurnDistance;

						currentIntersectionPosArrFormat[(previousAxisTracker - 1) % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[(previousAxisTracker - 1) % 2] + (-1 + ((previousAxisTracker % 2) * 2)) * currentTurnDistance;

						currentIntersectionPos.X = currentIntersectionPosArrFormat[0];
						currentIntersectionPos.Y = currentIntersectionPosArrFormat[1];
						vector2DStorArrOne.Add(currentIntersectionPos);
					}
					else if (firstOfPairIsEvenWithOrLeftOfSecondArr[currentPairIndex])
					{
						currentIntersectionPosArrFormat[currentAxisTracker % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[(currentAxisTracker - 1) % 2] + (1 - ((currentAxisTracker % 2) * 2)) * currentTurnDistance;

						currentIntersectionPosArrFormat[previousAxisTracker % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[(previousAxisTracker - 1) % 2] + (1 - ((previousAxisTracker % 2) * 2)) * currentTurnDistance;

						currentIntersectionPos.X = currentIntersectionPosArrFormat[0];
						currentIntersectionPos.Y = currentIntersectionPosArrFormat[1];
						vector2DStorArrOne.Add(currentIntersectionPos);
					}
					else
					{
						currentIntersectionPosArrFormat[(currentAxisTracker - 1) % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[(currentAxisTracker - 1) % 2] - currentTurnDistance;

						currentIntersectionPosArrFormat[(previousAxisTracker - 1) % 2] = currentFirstOfPairHoleOrIntersectionPositionXAndY[(previousAxisTracker - 1) % 2] - previousTurnDistance;

						currentIntersectionPos.X = currentIntersectionPosArrFormat[0];
						currentIntersectionPos.Y = currentIntersectionPosArrFormat[1];
						vector2DStorArrOne.Add(currentIntersectionPos);
					}

					break;
				default:
					break;
				}
			}
			turnDistancesFromFirstOfPairStorArr.Empty();
			intersectionDirStorArr.Empty();

			//Ive noticed an issue where the firstIntersectionOfAPair and the second can actually face not just different directions but opposite directions. just after unpaired holes or intersections are promoted and stuff is permantly stored to counteract this I could do a intersectionDirectionCorrectionAdjustment to the first of pair where I put turning track right in front of the fresh firstOfPairIntersection, and adjust the vector2D by one tile in the appropriate direction. this could be done as apart of the intersectionAdjustmentWeights so to organize both intersectionDirectionCorrectionAdjustments and standard adjustments into one array. it would be important to not have a intersectionDirectionCorrectionAdjustment and a standard adjustment on the same pair. but then for the arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection obviously i would need to store the intersections actual direction for building the level, so for this function: generating the track, I would need to use a directions proxy arr, like how vector2DStorArrOne is a proxy arr for hole and intersection positions. doing this would also be very important for intersection pair relevant positioning. all of this seems like alot to do for such a rare possibility but it is probably close to if not the best solution and therefore a necessity. do this before checking how 5 > group size > 2 or groupsize > 4 is failing.

			//calculating newly generated intersection's directions and orientations
			for (int currentIntersection = 0; currentIntersection < vector2DStorArrOne.Num(); currentIntersection++)
			{
				currentFirstOfPairIsAboveSecond = firstOfPairIsAboveSecondArr[currentIntersection];
				currentFirstOfPairIsEvenWithOrLeftOfSecond = firstOfPairIsEvenWithOrLeftOfSecondArr[currentIntersection];

				GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "currentIntersection of culminatingIntersections: " + FString::FromInt(currentIntersection));

				if (pairStartsOnSameSide[currentIntersection])
				{
					intersectionDirStorArr.Add(firstOfPairHoleDirStorArr[currentIntersection]);

					if (whichOfEachPairsTurnsBecomesTheIntersection[currentIntersection] % 2)
					{
						intersectionOrientationStorArr.Add(1);
					}
					else
					{
						intersectionOrientationStorArr.Add(0);
					}
				}
				else
				{
					switch (firstOfPairHoleDirStorArr[currentIntersection])//are the 16s in this switch statement correct? I think so
					{
					case 1 :
						if (currentFirstOfPairIsEvenWithOrLeftOfSecond)
						{
							if (whichOfEachPairsTurnsBecomesTheIntersection[currentIntersection] == availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping[currentIntersection])
							{
								if (vector2DStorArrOne[currentIntersection].X <= vector2DStorArrOne[currentIntersection].Y)
								{
									intersectionDirStorArr.Add(2);
									intersectionOrientationStorArr.Add(0);
								}
								else
								{
									intersectionDirStorArr.Add(1);
									intersectionOrientationStorArr.Add(1);
								}
							}
							else
							{
								intersectionDirStorArr.Add(2);
								intersectionOrientationStorArr.Add(1);
							}

						}
						else if (currentFirstOfPairIsAboveSecond)
						{
							if (whichOfEachPairsTurnsBecomesTheIntersection[currentIntersection] == 1)
							{
								intersectionDirStorArr.Add(1);
								intersectionOrientationStorArr.Add(1);
							}
							else
							{
								intersectionDirStorArr.Add(1);
								intersectionOrientationStorArr.Add(0);
							}
						}
						else
						{
							if (vector2DStorArrOne[currentIntersection].X <= vector2DStorArrOne[currentIntersection].Y)
							{
								intersectionDirStorArr.Add(2);
								intersectionOrientationStorArr.Add(0);
							}
							else
							{
								intersectionDirStorArr.Add(1);
								intersectionOrientationStorArr.Add(1);
							}
						}
						break;
					case 2 :
						if (currentFirstOfPairIsEvenWithOrLeftOfSecond)
						{
							if (whichOfEachPairsTurnsBecomesTheIntersection[currentIntersection] == availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping[currentIntersection])
							{
								if (16 - vector2DStorArrOne[currentIntersection].Y <= vector2DStorArrOne[currentIntersection].X)
								{
									intersectionDirStorArr.Add(3);
									intersectionOrientationStorArr.Add(0);
								}
								else
								{
									intersectionDirStorArr.Add(2);
									intersectionOrientationStorArr.Add(1);
								}
							}
							else
							{
								intersectionDirStorArr.Add(3);
								intersectionOrientationStorArr.Add(1);
							}

						}
						else if (currentFirstOfPairIsAboveSecond)
						{
							if (whichOfEachPairsTurnsBecomesTheIntersection[currentIntersection] == 1)
							{
								intersectionDirStorArr.Add(2);
								intersectionOrientationStorArr.Add(1);
							}
							else
							{
								intersectionDirStorArr.Add(2);
								intersectionOrientationStorArr.Add(0);
							}
						}
						else
						{
							if (16 - vector2DStorArrOne[currentIntersection].Y <= vector2DStorArrOne[currentIntersection].X)
							{
								intersectionDirStorArr.Add(3);
								intersectionOrientationStorArr.Add(0);
							}
							else
							{
								intersectionDirStorArr.Add(2);
								intersectionOrientationStorArr.Add(1);
							}
						}
						break;
					case 3 :
						if (currentFirstOfPairIsEvenWithOrLeftOfSecond)
						{
							if (whichOfEachPairsTurnsBecomesTheIntersection[currentIntersection] == availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping[currentIntersection])
							{
								if (16 - vector2DStorArrOne[currentIntersection].X <= 16 - vector2DStorArrOne[currentIntersection].Y)
								{
									intersectionDirStorArr.Add(4);
									intersectionOrientationStorArr.Add(0);
								}
								else
								{
									intersectionDirStorArr.Add(3);
									intersectionOrientationStorArr.Add(1);
								}
							}
							else
							{
								intersectionDirStorArr.Add(4);
								intersectionOrientationStorArr.Add(1);
							}

						}
						else if (currentFirstOfPairIsAboveSecond)
						{
							if (whichOfEachPairsTurnsBecomesTheIntersection[currentIntersection] == 1)
							{
								intersectionDirStorArr.Add(3);
								intersectionOrientationStorArr.Add(1);
							}
							else
							{
								intersectionDirStorArr.Add(3);
								intersectionOrientationStorArr.Add(0);
							}
						}
						else
						{
							if (16 - vector2DStorArrOne[currentIntersection].X <= 16 - vector2DStorArrOne[currentIntersection].Y)
							{
								intersectionDirStorArr.Add(4);
								intersectionOrientationStorArr.Add(0);
							}
							else
							{
								intersectionDirStorArr.Add(3);
								intersectionOrientationStorArr.Add(1);
							}
						}
						break;
					case 4 :
						if (currentFirstOfPairIsEvenWithOrLeftOfSecond)
						{
							if (whichOfEachPairsTurnsBecomesTheIntersection[currentIntersection] == availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping[currentIntersection])
							{
								if (vector2DStorArrOne[currentIntersection].Y <= 16 - vector2DStorArrOne[currentIntersection].X)
								{
									intersectionDirStorArr.Add(1);
									intersectionOrientationStorArr.Add(0);
								}
								else
								{
									intersectionDirStorArr.Add(4);
									intersectionOrientationStorArr.Add(1);
								}
							}
							else
							{
								intersectionDirStorArr.Add(1);
								intersectionOrientationStorArr.Add(1);
							}

						}
						else if (currentFirstOfPairIsAboveSecond)
						{
							if (whichOfEachPairsTurnsBecomesTheIntersection[currentIntersection] == 1)
							{
								intersectionDirStorArr.Add(4);
								intersectionOrientationStorArr.Add(1);
							}
							else
							{
								intersectionDirStorArr.Add(4);
								intersectionOrientationStorArr.Add(0);
							}
						}
						else
						{
							if (vector2DStorArrOne[currentIntersection].Y <= 16 - vector2DStorArrOne[currentIntersection].X)
							{
								intersectionDirStorArr.Add(1);
								intersectionOrientationStorArr.Add(0);
							}
							else
							{
								intersectionDirStorArr.Add(4);
								intersectionOrientationStorArr.Add(1);
							}
						}
						break;
					default: 
						break;
					}
				}
			}

			//promoting any unpaired holes or intersections into the next level
			if (unpairedHoleOrIntersectionDir != 0)
			{//if I switch putting intersectionDirStorArr and intersectionPosStorArr into permanent storage until after this I might be able to increase efficiency slightly
				turnAndIntersectionDistancesPerPair[currentLevelIndex][currentGroupIndex][availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Num()] = { 1 };
				directionsOfTurns[currentLevelIndex][currentGroupIndex][availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Num()] = { 2 };//Im setting this to 2 instead of 3 and using intersection orientation to discern whether the intersection is actually straight track

				switch (unpairedHoleOrIntersectionDir)
				{
				case 1 :
					vector2DStorArrOne.Add(FVector2D(unpairedHoleOrIntersectionPos.X, unpairedHoleOrIntersectionPos.Y + 1));
					break;
				case 2 :
					vector2DStorArrOne.Add(FVector2D(unpairedHoleOrIntersectionPos.X + 1, unpairedHoleOrIntersectionPos.Y));
					break;
				case 3 :
					vector2DStorArrOne.Add(FVector2D(unpairedHoleOrIntersectionPos.X, unpairedHoleOrIntersectionPos.Y - 1));
					break;
				case 4 :
					vector2DStorArrOne.Add(FVector2D(unpairedHoleOrIntersectionPos.X - 1, unpairedHoleOrIntersectionPos.Y));
					break;
				default:
					break;
				}

				intersectionDirStorArr.Add(unpairedHoleOrIntersectionDir);
				intersectionOrientationStorArr.Add(2);

				//should I wait until later to promote the unpairedDir?

				unpairedHoleOrIntersectionPos = FVector2D(0, 0);
				unpairedHoleOrIntersectionDir = 0;

				//will this intersectionOrientation need to be set to 2 for straight track? or will enough be handled by directionOfTurns it wont matter?
				//make sure this unpaired hole does not get an adjustment in the following code bracket. it shouldnt but just watch out
			}

			// this is where everything gets placed into permanent storage. remember this needs to get moved above the intersection adjustment section
			holeAndIntersectionPositions[currentLevelIndex + 1][currentGroupIndex] = vector2DStorArrOne;
			arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[currentLevelIndex + 1][currentGroupIndex] = intersectionDirStorArr;
			intersectionOrientationsPerGroupPerLevel[currentLevelIndex + 1][currentGroupIndex] = intersectionOrientationStorArr;

			//select intersection position are adjusted and firstOfPairIsAboveSecond and firstOfPairIsEvenWithOrLeftOfSecond are written. It's likely adjustingIntersectionPos will cause problems but i will need to run the code a lot to find these issues. To achieve the adjustment I am not adjusting any vector2D's in permanent storage, but tracking which of all intersections are being ajdusted, and then in temporary storage I am adjusting the vector2DStorArrOne for the purpose of calculating the proceeding track and intersections. all of this means when I build the level I will have to inlcude a distinct functionality to extend an appropriately sized portion of track from any intersection bearing a weight
			intersectionAjustmentWeights.Empty();
			firstOfPairIsAboveSecondArr.Empty();
			firstOfPairIsEvenWithOrLeftOfSecondArr.Empty();

			if (vector2DStorArrOne.Num() > 1)
			{
				for (int currentPair = 1; currentPair <= vector2DStorArrOne.Num()/2; currentPair++)
				{//go through and change the below variables from arrays to single variables if it turns out you aren't using modulo to divine the appropriate index anywhere
					firstOfPairIntersectionPos = vector2DStorArrOne[currentPair * 2 - 2];
					secondOfPairIntersectionPos = vector2DStorArrOne[currentPair * 2 - 1];
					firstOfPairIntersectionDir = intersectionDirStorArr[currentPair * 2 - 2];
					secondOfPairIntersectionDir = intersectionDirStorArr[currentPair * 2 - 1];
					differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;

					if (abs(firstOfPairIntersectionDir - secondOfPairIntersectionDir) == 2)
					{//this runs when the current pair of intersections aren't just on different sides but on opposite sides. this currently only works with intersections, I have not written the solution to this problem for holes
						intersectionDirStorArr[currentPair * 2 - 2] = FMath::Clamp((firstOfPairIntersectionDir + 1) % 5, 1, 4);
						intersectionAjustmentWeights.Add(3);

						switch (firstOfPairIntersectionDir)
						{
						case 1 :
							firstOfPairIntersectionPos.Y += 1;
							vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
							differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;

							if (differenceInPairPosition.X > 0)
							{
								firstOfPairIsAboveSecondArr.Add(1);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
							}
							else if (differenceInPairPosition.Y > -1)
							{
								firstOfPairIsAboveSecondArr.Add(0);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(1);
							}
							else
							{
								firstOfPairIsAboveSecondArr.Add(0);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
							}
							break;
						case 2 :
							firstOfPairIntersectionPos.X += 1;
							vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
							differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;

							if (differenceInPairPosition.Y < 0)
							{
								firstOfPairIsAboveSecondArr.Add(1);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
							}
							else if (differenceInPairPosition.X > -1)
							{
								firstOfPairIsAboveSecondArr.Add(0);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(1);
							}
							else
							{
								firstOfPairIsAboveSecondArr.Add(0);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
							}
							break;
						case 3 :
							firstOfPairIntersectionPos.Y -= 1;
							vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
							differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;

							if (differenceInPairPosition.X < 0)
							{
								firstOfPairIsAboveSecondArr.Add(1);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
							}
							else if (differenceInPairPosition.Y < 1)
							{
								firstOfPairIsAboveSecondArr.Add(0);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(1);
							}
							else
							{
								firstOfPairIsAboveSecondArr.Add(0);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
							}
							break;
						case 4 :
							firstOfPairIntersectionPos.X -= 1;
							vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
							differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;

							if (differenceInPairPosition.Y > 0)
							{
								firstOfPairIsAboveSecondArr.Add(1);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
							}
							else if (differenceInPairPosition.X < 1)
							{
								firstOfPairIsAboveSecondArr.Add(0);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(1);
							}
							else
							{
								firstOfPairIsAboveSecondArr.Add(0);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
							}
							break;
						default:
							break;
						}
					}
					else
					{
						switch (firstOfPairIntersectionDir)
						{
						case 1:
							if (differenceInPairPosition.Y > 0)
							{
								firstOfPairIsAboveSecondArr.Add(1);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
								firstOfPairIntersectionPos.Y += extentOfAdjustment;
								vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
								intersectionAjustmentWeights.Add(1);
							}
							else if (differenceInPairPosition.X < 1)
							{
								firstOfPairIsAboveSecondArr.Add(0);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(1);
								if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
								{
									secondOfPairIntersectionPos.Y += extentOfAdjustment;
								}
								else
								{
									secondOfPairIntersectionPos.X += extentOfAdjustment;
								}
								vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
								intersectionAjustmentWeights.Add(2);
							}
							else
							{
								if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
								{
									if (FMath::RandRange(0, 1))
									{//second of pair gets adjustment
										secondOfPairIntersectionPos.Y += extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(2);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
									else
									{// first of pair gets adjustment
										firstOfPairIntersectionPos.Y += extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(1);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
								}
								else
								{
									if (differenceInPairPosition.Y < -1 && FMath::RandRange(0, 1))
									{//second of pair gets adjustment
										secondOfPairIntersectionPos.X += extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(2);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
									else if (differenceInPairPosition.X > 1)
									{// first of pair gets adjustment
										firstOfPairIntersectionPos.Y += extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(1);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
									else
									{//no adjustments are made. This logic is a necessity but this case should be avoided at all costs
										intersectionAjustmentWeights.Add(0);
									}
								}

								if (differenceInPairPosition.Y > 0)
								{
									firstOfPairIsAboveSecondArr.Add(1);
									firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
								}
								else if (differenceInPairPosition.X < 1)
								{
									firstOfPairIsAboveSecondArr.Add(0);
									firstOfPairIsEvenWithOrLeftOfSecondArr.Add(1);
								}
								else
								{
									firstOfPairIsAboveSecondArr.Add(0);
									firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
								}
							}

							break;
						case 2:
							if (differenceInPairPosition.X > 0)
							{
								firstOfPairIsAboveSecondArr.Add(1);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
								firstOfPairIntersectionPos.X += extentOfAdjustment;
								vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
								intersectionAjustmentWeights.Add(1);
							}
							else if (differenceInPairPosition.Y > -1)
							{
								firstOfPairIsAboveSecondArr.Add(0);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(1);
								if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
								{
									secondOfPairIntersectionPos.X += extentOfAdjustment;
								}
								else
								{
									secondOfPairIntersectionPos.Y -= extentOfAdjustment;
								}
								vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
								intersectionAjustmentWeights.Add(2);
							}
							else
							{
								if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
								{
									if (FMath::RandRange(0, 1))
									{//second of pair gets adjustment
										secondOfPairIntersectionPos.X += extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(2);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
									else
									{// first of pair gets adjustment
										firstOfPairIntersectionPos.X += extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(1);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
								}
								else
								{
									if (differenceInPairPosition.X < -1 && FMath::RandRange(0, 1))
									{//second of pair gets adjustment
										secondOfPairIntersectionPos.Y -= extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(2);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
									else if (differenceInPairPosition.Y < -1)
									{// first of pair gets adjustment
										firstOfPairIntersectionPos.X += extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(1);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
									else
									{//no adjustments are made. This logic is a necessity but this case should be avoided at all costs
										intersectionAjustmentWeights.Add(0);
									}
								}

								if (differenceInPairPosition.X > 0)
								{
									firstOfPairIsAboveSecondArr.Add(1);
									firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
								}
								else if (differenceInPairPosition.Y > -1)
								{
									firstOfPairIsAboveSecondArr.Add(0);
									firstOfPairIsEvenWithOrLeftOfSecondArr.Add(1);
								}
								else
								{
									firstOfPairIsAboveSecondArr.Add(0);
									firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
								}
							}

							break;
						case 3:
							if (differenceInPairPosition.Y < 0)
							{
								firstOfPairIsAboveSecondArr.Add(1);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
								firstOfPairIntersectionPos.Y -= extentOfAdjustment;
								vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
								intersectionAjustmentWeights.Add(1);
							}
							else if (differenceInPairPosition.X > -1)
							{
								firstOfPairIsAboveSecondArr.Add(0);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(1);
								if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
								{
									secondOfPairIntersectionPos.Y -= extentOfAdjustment;
								}
								else
								{
									secondOfPairIntersectionPos.X -= extentOfAdjustment;
								}
								vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
								intersectionAjustmentWeights.Add(2);
							}
							else
							{
								if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
								{
									if (FMath::RandRange(0, 1))
									{//second of pair gets adjustment
										secondOfPairIntersectionPos.Y -= extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(2);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
									else
									{// first of pair gets adjustment
										firstOfPairIntersectionPos.Y -= extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(1);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
								}
								else
								{
									if (differenceInPairPosition.Y > 1 && FMath::RandRange(0, 1))
									{//second of pair gets adjustment
										secondOfPairIntersectionPos.X -= extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(2);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
									else if (differenceInPairPosition.X < -1)
									{// first of pair gets adjustment
										firstOfPairIntersectionPos.Y -= extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(1);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
									else
									{//no adjustments are made. This logic is a necessity but this case should be avoided at all costs
										intersectionAjustmentWeights.Add(0);
									}
								}

								if (differenceInPairPosition.Y < 0)
								{
									firstOfPairIsAboveSecondArr.Add(1);
									firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
								}
								else if (differenceInPairPosition.X > -1)
								{
									firstOfPairIsAboveSecondArr.Add(0);
									firstOfPairIsEvenWithOrLeftOfSecondArr.Add(1);
								}
								else
								{
									firstOfPairIsAboveSecondArr.Add(0);
									firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
								}
							}

							break;
						case 4:
							if (differenceInPairPosition.X < 0)
							{
								firstOfPairIsAboveSecondArr.Add(1);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
								firstOfPairIntersectionPos.X -= extentOfAdjustment;
								vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
								intersectionAjustmentWeights.Add(1);
							}
							else if (differenceInPairPosition.Y < 1)
							{
								firstOfPairIsAboveSecondArr.Add(0);
								firstOfPairIsEvenWithOrLeftOfSecondArr.Add(1);
								if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
								{
									secondOfPairIntersectionPos.X -= extentOfAdjustment;
								}
								else
								{
									secondOfPairIntersectionPos.Y += extentOfAdjustment;
								}
								vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
								intersectionAjustmentWeights.Add(2);
							}
							else
							{
								if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
								{
									if (FMath::RandRange(0, 1))
									{//second of pair gets adjustment
										secondOfPairIntersectionPos.X -= extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(2);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
									else
									{// first of pair gets adjustment
										firstOfPairIntersectionPos.X -= extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(1);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
								}
								else
								{
									if (differenceInPairPosition.X > 1 && FMath::RandRange(0, 1))
									{//second of pair gets adjustment
										secondOfPairIntersectionPos.Y += extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(2);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
									else if (differenceInPairPosition.Y > 1)
									{// first of pair gets adjustment
										firstOfPairIntersectionPos.X -= extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(1);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
									else
									{//no adjustments are made. This logic is a necessity but this case should be avoided at all costs
										intersectionAjustmentWeights.Add(0);
									}
								}

								if (differenceInPairPosition.X < 0)
								{
									firstOfPairIsAboveSecondArr.Add(1);
									firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
								}
								else if (differenceInPairPosition.Y < 1)
								{
									firstOfPairIsAboveSecondArr.Add(0);
									firstOfPairIsEvenWithOrLeftOfSecondArr.Add(1);
								}
								else
								{
									firstOfPairIsAboveSecondArr.Add(0);
									firstOfPairIsEvenWithOrLeftOfSecondArr.Add(0);
								}
							}

							break;
						default:
							break;
						}
					}
				}
			} 
			
			if (vector2DStorArrOne.Num() % 2 == 1)
			{
				intersectionAjustmentWeights.Add(0);
			}//just added this lets hope it works
			GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "size of vector2DStorArr: " + FString::FromInt(vector2DStorArrOne.Num()) + "size of intersectionAdjustmentWeights: " + FString::FromInt(intersectionAjustmentWeights.Num()));
			/*
			else
			{//what I am doing here means I will need to calculate a vector2DStorArr before the first level of the final grouping
			//CHANGE ALL THIS, dont do any adjustments on final intersections of holePositionGroupings until just before the final grouping. that way you can compile every position and calculate adjustments as you have above
				if (currentGroupIndex % 2 == 0 && currentGroupIndex == listOfHolePositionGroupings.Num() - 1)
				{
					//intersectionAjustmentWeights.Add(0);
					//priorGroupTopLevelAdjustment = 0;
					adjustmentsAppliedToEachIntersection[currentLevelIndex + 1][currentGroupIndex] = { 0 }; //this intersection will become an unpaired intersection in the 4th Level
				}
				else if (currentGroupIndex % 2)
				{//this condition applies to the second of pair
					if (priorGroupTopLevelAdjustment == 0)
					{
						adjustmentsAppliedToEachIntersection[currentLevelIndex + 1][currentGroupIndex] = { 1 };
						//priorGroupTopLevelAdjustment = 1;
					}
					else
					{
						adjustmentsAppliedToEachIntersection[currentLevelIndex + 1][currentGroupIndex] = { 0 };
					}
				}
				else
				{// this condition applies to the first of pair
					if (FMath::RandRange(0, 19) > 9)
					{
						adjustmentsAppliedToEachIntersection[currentLevelIndex + 1][currentGroupIndex] = { 1 };
						priorGroupTopLevelAdjustment = 1;
					}
					else
					{
						adjustmentsAppliedToEachIntersection[currentLevelIndex + 1][currentGroupIndex] = { 0 };
						priorGroupTopLevelAdjustment = 0;
					}
				}
			}*/

			adjustmentsAppliedToEachIntersection[currentLevelIndex + 1][currentGroupIndex] = intersectionAjustmentWeights;
			firstOfPairIsAboveSecondAllPairs[currentLevelIndex + 1][currentGroupIndex] = firstOfPairIsAboveSecondArr;
			firstOfPairIsEvenWithOrLeftOfSecondAllPairs[currentLevelIndex + 1][currentGroupIndex] = firstOfPairIsEvenWithOrLeftOfSecondArr;
			

			// this is the pile of arrays and misc which needs to get reset between every level
			horizontalAndVerticleDistancesBetweenHolesOrIntersections[0].Empty();
			horizontalAndVerticleDistancesBetweenHolesOrIntersections[1].Empty();

			horizontalDistancesBetweenHolesOrIntersections.Empty();
			verticleDistancesBetweenHolesOrIntersections.Empty();

			//firstOfPairIsAboveSecondArr.Empty();
			//firstOfPairIsEvenWithOrLeftOfSecondArr.Empty();

			availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Empty();

			whichOfEachPairsTurnsBecomesTheIntersection.Empty();

			firstOfPairHoleOrIntersectionPosStorArr.Empty();
			firstOfPairHoleDirStorArr.Empty();

			pairStartsOnSameSide.Empty();

			intersectionOrientationStorArr.Empty();
		}
	}
}

void ATestHud::BuildLevel()
{
	//So Im translating the landscape data into a 1 dimension list (which includes the hole positions), then Im translating all the track data to a 1 dimensional list (and making sure to mark the intersections to active the buttons bellow them), then Im creating the gameSlateWidget and passing the completed 1 dimensional lists into it as arguments

	//the 1D lists will work as follows:
	/*
	     0   1   2   3   4   5   6   7   8   9   10  11  12  13  14
	     -   -   -   -   -   -   -   -   -   -   -   -   -   -   -
	0 |  0   1   2   3   4   5   6   7   8   9   10  11  12  13  14
	1 |  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29
	2 |  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44
	3 |  45  46  47  48  49  50  51  52  53  54  55  56  57  58  59
	4 |  60  61  62  63  64  65  66  67  68  69  70  71  72  73  74
	5 |  75  76  77  78  79  80  81  82  83  84  85  86  87  88  89
	6 |  90  91  92  93  94  95  96  97  98  99  100 101 102 103 104
	7 |  105 106 107 108 109 110 111 112 113 114 115 116 117 118 119
	8 |  120 121 122 123 124 125 126 127 128 129 130 131 132 133 134
	9 |  135 136 137 138 139 140 141 142 143 144 145 146 147 148 149
	10|  150 151 152 153 154 155 156 157 158 159 160 161 162 163 164
	11|  165 166 167 168 169 170 171 172 173 174 175 176 177 178 179
	12|  180 181 182 183 184 185 186 187 188 189 190 191 192 193 194
	13|  195 196 197 198 199 200 201 202 203 204 205 206 207 208 209
	14|  210 211 212 213 214 215 216 217 218 219 220 221 222 223 224

	currently my coordinates will need to be translated into these coordinates before being applied to the 1D list
	conversion from previous format to current: x2 = x1 - 1 |  y2 = 15 - y1  
	conversion from current format to corresponding index: index = y * width + x  | e.g. : (4, 12) = 12 * 15 + 4 = 184

	the 1D lists will be lists of integers where each value will correspond to the index of the desired sprite/sprite animation stored in a seperate data structure
			 */
	//TRACK DATA
	int currentGroupSize;
	FVector2D currentFirstOfPairPosition;
	int currentFirstOfPairDir;
	FVector2D previousTurnOrIntersectionPosition;
	TArray<int> currentPairTurnDistances;
	TArray<int> currentPairTurnDirections;
	FVector2D newTrackPos;
	FVector2D convertedTrackPos;
	int culminatingIntersectionDir;
	int adjustmentAppliedToCulminatingIntersectionPair;
	FVector2D culminatingIntersectionPos;
	int culminatingIntersectionOrientation;
	int correctedCurrentTurnDist;
	int secondOfPairDir;
	FVector2D secondOfPairPos;
	FVector2D differenceInPairPos;
	TArray<int> intersectionAdjustmentTrackerArr;
	int currentFirstOfPairDirCorrectedForAdjustment;
	int currentIntersectionAdjustmentTracker;

	GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "------------");

	for (int currentGroupIndex = 0; currentGroupIndex < listOfHolePositionGroupings.Num(); currentGroupIndex++)
	{
		currentGroupSize = listOfHolePositionGroupings[currentGroupIndex];
		intersectionAdjustmentTrackerArr = { 0, 0, 0, 0, 0, 0, 0, 0 };
		GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "current group index: " + FString::FromInt(currentGroupIndex));

		for (int currentLevelIndex = 0; currentLevelIndex <= FMath::Clamp(FMath::RoundHalfFromZero((float)currentGroupSize / 2.0f), 1, 3) - 1; currentLevelIndex++)
		{//since I will be determining the hole positions 
			GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "current level index: " + FString::FromInt(currentLevelIndex));
			for (int currentFirstOfPairIndex = 0; currentFirstOfPairIndex < holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex].Num(); currentFirstOfPairIndex += 2)
			{
				//what would happen if there were 7 holes in terms of how the adjustment is handled? I need to check in the intersection adjustment section of the generate track function. currently I think everything would run properly. if the 7nth hole's "promoted" intersection got an adjustment it should just run as if the promoted intersection were a standard intersection

				GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "index " + FString::FromInt(currentFirstOfPairIndex) + " of holeAndIntersectionPositions: " + holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex].ToString() + " | quantity of turn distances for current pair: " + FString::FromInt(turnAndIntersectionDistancesPerPair[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex / 2].Num()) + " | quantity of turn directions for current pair: " + FString::FromInt(directionsOfTurns[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex / 2].Num()));

				currentFirstOfPairPosition = holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex];
				currentFirstOfPairDir = arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex];
				currentPairTurnDistances = turnAndIntersectionDistancesPerPair[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex / 2];
				currentPairTurnDirections = directionsOfTurns[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex / 2];

				for (int a = 0; a < directionsOfTurns[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex / 2].Num(); a++)
				{
					GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "turn direction and distance at index " + FString::FromInt(a) + ": " + FString::FromInt(directionsOfTurns[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex / 2][a]) + ", " + FString::FromInt(turnAndIntersectionDistancesPerPair[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex / 2][a]));
				}

				previousTurnOrIntersectionPosition = currentFirstOfPairPosition;
				culminatingIntersectionDir = arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[currentLevelIndex + 1][currentGroupIndex][currentFirstOfPairIndex / 2];
				culminatingIntersectionOrientation = intersectionOrientationsPerGroupPerLevel[currentLevelIndex + 1][currentGroupIndex][currentFirstOfPairIndex / 2];
				culminatingIntersectionPos = holeAndIntersectionPositions[currentLevelIndex + 1][currentGroupIndex][currentFirstOfPairIndex / 2];
				adjustmentAppliedToCulminatingIntersectionPair = adjustmentsAppliedToEachIntersection[currentLevelIndex + 1][currentGroupIndex][(currentFirstOfPairIndex / 2) / 2];// is this working properly?
				currentIntersectionAdjustmentTracker = intersectionAdjustmentTrackerArr[currentFirstOfPairIndex];

				if (currentIntersectionAdjustmentTracker == 2)
				{
					currentFirstOfPairDirCorrectedForAdjustment = FMath::Clamp((currentFirstOfPairDir + 1) % 5, 1, 4);
				}
				else
				{
					currentFirstOfPairDirCorrectedForAdjustment = currentFirstOfPairDir;
				}

				switch (currentFirstOfPairDirCorrectedForAdjustment)
				{
				case 1 :
					if (currentIntersectionAdjustmentTracker)
					{// I will need to check if adjustment is for intersections of pair facing opposite directions both here and below where intersection adjustment track is layed
						if (currentIntersectionAdjustmentTracker == 2)
						{ // this will mean there is in adjustment to intersections of pair facing opposite directions
							previousTurnOrIntersectionPosition.Y += 1;
						}
						else
						{
							previousTurnOrIntersectionPosition.Y += extentOfAdjustment;
							GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "is adjusting one axis of a vector2D changing it into an int: " + previousTurnOrIntersectionPosition.ToString());
						}
					}

					if (firstOfPairIsAboveSecondAllPairs[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex / 2])
					{
						for (int currentTurnIndex = 0; currentTurnIndex < currentPairTurnDistances.Num(); currentTurnIndex++)
						{
							correctedCurrentTurnDist = currentPairTurnDistances[currentTurnIndex] - currentPairTurnDistances[FMath::Clamp(currentTurnIndex - 2, 0, 6)] * FMath::Clamp(currentTurnIndex - 1, 0, 1);

							switch (currentTurnIndex % 2)//here 0 is verticle and 1 is horizontal
							{
							case 0:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition - FVector2D(0, a);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
								}

								newTrackPos = previousTurnOrIntersectionPosition - FVector2D(0, correctedCurrentTurnDist);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5; //remember when firstOfPairIsAboveSecond the first verticle turn is facing a different direction then all of the rest
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;
								}
								else // if (currentPairTurnDirections[currentTurnIndex] == 2)
								{
									switch (culminatingIntersectionDir)
									{
									case 1:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 14;//intersectiondir: 1, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 13;//intersectiondir: 1, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									case 2:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 12;//intersectiondir: 2, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 11;//intersectiondir: 2, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition - FVector2D(a, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//is this really the best way to do this??//:>:P
								}

								newTrackPos = previousTurnOrIntersectionPosition - FVector2D(correctedCurrentTurnDist, 0);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;
									GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "firstOfPairIsAboveSecond and currentRelevantDistance is horizontal and right turn made");
								}
								else
								{
									switch (culminatingIntersectionDir)
									{
									case 1:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 14;//intersectiondir: 1, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 13;//intersectiondir: 1, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									case 2:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 12;//intersectiondir: 2, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 11;//intersectiondir: 2, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}
								break;
							default:
								break;
							}
						}
					}
					else if (firstOfPairIsEvenWithOrLeftOfSecondAllPairs[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex / 2])
					{//remember when inevitably firstOfPairIsEvenWithOrLeftOfSecond and pairStartsOnSameSide you must either change how this is calculated to work off of firstOfPairPosition or change how intersectionPosition is calculated in generateTrackShape to work off previousTurnOrIntersectionPosition. just change the stuff here and leave the stuff above. ACTually I think in adding correctedTurnDist I solved this problem
						for (int currentTurnIndex = 0; currentTurnIndex < currentPairTurnDistances.Num(); currentTurnIndex++)
						{
							correctedCurrentTurnDist = currentPairTurnDistances[currentTurnIndex] - currentPairTurnDistances[FMath::Clamp(currentTurnIndex - 2, 0, 6)] * FMath::Clamp(currentTurnIndex - 1, 0, 1);

							switch (currentTurnIndex % 2)//here 0 is verticle and 1 is horizontal
							{
							case 0:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition + FVector2D(0, a);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
								}

								newTrackPos = previousTurnOrIntersectionPosition + FVector2D(0, correctedCurrentTurnDist);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5; //
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
								}
								else // if (currentPairTurnDirections[currentTurnIndex] == 2)
								{
									switch (culminatingIntersectionDir)
									{
									case 1:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 14;//intersectiondir: 1, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 13;//intersectiondir: 1, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									case 2:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 12;//intersectiondir: 2, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 11;//intersectiondir: 2, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition + FVector2D(a, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//is this really the best way to do this??//:>:P
								}

								newTrackPos = previousTurnOrIntersectionPosition + FVector2D(correctedCurrentTurnDist, 0);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									if (currentTurnIndex == currentPairTurnDistances.Num() - 1)
									{
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
									}
									else
									{
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;
									}
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;
									GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "firstOfPairIsEvenWithOrLeftOfSecond and currentRelevantDistance is horizontal and right turn made");
								}
								else
								{
									switch (culminatingIntersectionDir)
									{
									case 1:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 14;//intersectiondir: 1, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 13;//intersectiondir: 1, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									case 2:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 12;//intersectiondir: 2, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 11;//intersectiondir: 2, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}
								break;
							default:
								break;
							}
						}
					}
					else
					{
						for (int currentTurnIndex = 0; currentTurnIndex < currentPairTurnDistances.Num(); currentTurnIndex++)
						{
							correctedCurrentTurnDist = currentPairTurnDistances[currentTurnIndex] - currentPairTurnDistances[FMath::Clamp(currentTurnIndex - 2, 0, 6)] * FMath::Clamp(currentTurnIndex - 1, 0, 1);

							switch (currentTurnIndex % 2)//here 0 is verticle and 1 is horizontal
							{
							case 0:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition + FVector2D(0, a);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
								}

								newTrackPos = previousTurnOrIntersectionPosition + FVector2D(0, correctedCurrentTurnDist);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5; //
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
									GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "firstOfPairIsRightOfAndBelowSecond and currentRelevantDistance is verticle and right turn made");
								}
								else // if (currentPairTurnDirections[currentTurnIndex] == 2)
								{
									switch (culminatingIntersectionDir)
									{
									case 1:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 14;//intersectiondir: 1, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 13;//intersectiondir: 1, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									case 2:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 12;//intersectiondir: 2, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 11;//intersectiondir: 2, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}

									if (currentPairTurnDistances.Num() == 1)//this proves its possible for there to be remaining horizontal distance when pairStartsOnDifferentSides and firstOfPairIsRightOfAndEvenWithOrBelowSecond
									{
										if (currentFirstOfPairIndex < holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex].Num() - 1)
										{
											secondOfPairDir = arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex + 1];
											secondOfPairPos = holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex + 1];
											differenceInPairPos = culminatingIntersectionPos - secondOfPairPos;//im changing this from currentFirstOfPairPosition minus second to culminatingIntersectionPos minus second 

											if (secondOfPairDir != currentFirstOfPairDir)
											{
												if (currentFirstOfPairDir == currentFirstOfPairDirCorrectedForAdjustment && differenceInPairPos.X > 1)
												{
													for (int a = 1; a < differenceInPairPos.X; a++)
													{
														newTrackPos = secondOfPairPos + FVector2D(a, 0);

														convertedTrackPos.X = newTrackPos.X - 1;
														convertedTrackPos.Y = 15 - newTrackPos.Y;
														trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
													}
												}
												else if (currentFirstOfPairDir != currentFirstOfPairDirCorrectedForAdjustment && differenceInPairPos.Y < -1)
												{
													for (int a = -1; a > differenceInPairPos.Y; a--)
													{
														newTrackPos = secondOfPairPos + FVector2D(0, a);

														convertedTrackPos.X = newTrackPos.X - 1;
														convertedTrackPos.Y = 15 - newTrackPos.Y;
														trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
													}
												}
											}
										}
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition - FVector2D(a, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//is this really the best way to do this??//:>:P
								}

								newTrackPos = previousTurnOrIntersectionPosition - FVector2D(correctedCurrentTurnDist, 0);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4; //
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
								}
								else
								{
									switch (culminatingIntersectionDir)
									{
									case 1:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 14;//intersectiondir: 1, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 13;//intersectiondir: 1, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									case 2:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 12;//intersectiondir: 2, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 11;//intersectiondir: 2, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}
								break;
							default:
								break;
							}
						}
					}

					//here, if the current culminating intersection gets an adjustment, we lay the track to span the adjustment now
					if (adjustmentAppliedToCulminatingIntersectionPair != 0)//can this be in this scope or does it need to move up into the next? I think it can..
					{
						if (adjustmentAppliedToCulminatingIntersectionPair % 2 == 1 - ((currentFirstOfPairIndex / 2) % 2))
						{// this means: if current culminating intersection does get adjustment
							if (adjustmentAppliedToCulminatingIntersectionPair == 3)
							{
								intersectionAdjustmentTrackerArr[currentFirstOfPairIndex / 2] = 2;

								switch (culminatingIntersectionDir)
								{//this would need to have a case 3 if it's possible for this to occur twice in a row
								case 1 :
									newTrackPos = culminatingIntersectionPos + FVector2D(0, 1);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
									break;
								case 2 :
									newTrackPos = culminatingIntersectionPos + FVector2D(1, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;
									break;
								default:
									break;
								}
							}
							else
							{
								intersectionAdjustmentTrackerArr[currentFirstOfPairIndex / 2] = 1;

								for (int a = 1; a <= extentOfAdjustment; a++)
								{
									newTrackPos = culminatingIntersectionPos + FVector2D(a * (1 - (culminatingIntersectionDir % 2)), a * (culminatingIntersectionDir % 2));

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2 - (culminatingIntersectionDir % 2);
								}
							}
						}
					}
					else
					{
						intersectionAdjustmentTrackerArr[currentFirstOfPairIndex / 2] = 0;
					}

					break;
				case 2 :
					if (currentIntersectionAdjustmentTracker)
					{
						if (currentIntersectionAdjustmentTracker == 2)
						{ // this will mean there is in adjustment to intersections of pair facing opposite directions
							previousTurnOrIntersectionPosition.X += 1;
						}
						else
						{
							previousTurnOrIntersectionPosition.X += extentOfAdjustment;
						}
					}

					if (firstOfPairIsAboveSecondAllPairs[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex / 2])
					{
						for (int currentTurnIndex = 0; currentTurnIndex < currentPairTurnDistances.Num(); currentTurnIndex++)
						{
							correctedCurrentTurnDist = currentPairTurnDistances[currentTurnIndex] - currentPairTurnDistances[FMath::Clamp(currentTurnIndex - 2, 0, 6)] * FMath::Clamp(currentTurnIndex - 1, 0, 1);

							switch (currentTurnIndex % 2)//here 0 is verticle and 1 is horizontal
							{
							case 0:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition - FVector2D(a, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
								}

								newTrackPos = previousTurnOrIntersectionPosition - FVector2D(correctedCurrentTurnDist, 0);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6; //remember when firstOfPairIsAboveSecond the first verticle turn is facing a different direction then all of the rest
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
								}
								else // if (currentPairTurnDirections[currentTurnIndex] == 2)
								{
									switch (culminatingIntersectionDir)
									{
									case 2:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 12;//intersectiondir: 2, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 11;//intersectiondir: 2, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									case 3:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 8;//intersectiondir: 3, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 3, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition + FVector2D(0, a);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//is this really the best way to do this??//:>:P
								}

								newTrackPos = previousTurnOrIntersectionPosition + FVector2D(0, correctedCurrentTurnDist);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5; 
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
									GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "firstOfPairIsAboveSecond and currentRelevantDistance is horizontal and right turn made");
								}
								else
								{
									switch (culminatingIntersectionDir)
									{
									case 2:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 12;//intersectiondir: 2, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 11;//intersectiondir: 2, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									case 3:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 8;//intersectiondir: 3, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 3, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}
								break;
							default:
								break;
							}
						}
					}
					else if (firstOfPairIsEvenWithOrLeftOfSecondAllPairs[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex / 2])
					{//remember when inevitably firstOfPairIsEvenWithOrLeftOfSecond and pairStartsOnSameSide you must either change how this is calculated to work off of firstOfPairPosition or change how intersectionPosition is calculated in generateTrackShape to work off previousTurnOrIntersectionPosition. just change the stuff here and leave the stuff above. ACTually I think in adding correctedTurnDist I solved this problem
						for (int currentTurnIndex = 0; currentTurnIndex < currentPairTurnDistances.Num(); currentTurnIndex++)
						{
							correctedCurrentTurnDist = currentPairTurnDistances[currentTurnIndex] - currentPairTurnDistances[FMath::Clamp(currentTurnIndex - 2, 0, 6)] * FMath::Clamp(currentTurnIndex - 1, 0, 1);

							switch (currentTurnIndex % 2)//here 0 is verticle and 1 is horizontal
							{
							case 0:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition + FVector2D(a, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
								}

								newTrackPos = previousTurnOrIntersectionPosition + FVector2D(correctedCurrentTurnDist, 0);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6; //
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;
								}
								else // if (currentPairTurnDirections[currentTurnIndex] == 2)
								{
									switch (culminatingIntersectionDir)
									{
									case 2:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 12;//intersectiondir: 2, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 11;//intersectiondir: 2, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									case 3:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 8;//intersectiondir: 3, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 3, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition - FVector2D(0, a);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//is this really the best way to do this??//:>:P
								}

								newTrackPos = previousTurnOrIntersectionPosition - FVector2D(0, correctedCurrentTurnDist);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									if (currentTurnIndex == currentPairTurnDistances.Num() - 1)
									{
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;
									}
									else
									{
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
									}
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;
									GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "firstOfPairIsEvenWithOrLeftOfSecond and currentRelevantDistance is horizontal and right turn made");
								}
								else
								{
									switch (culminatingIntersectionDir)
									{
									case 2:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 12;//intersectiondir: 2, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 11;//intersectiondir: 2, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									case 3:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 8;//intersectiondir: 3, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 3, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}
								break;
							default:
								break;
							}
						}
					}
					else
					{
						for (int currentTurnIndex = 0; currentTurnIndex < currentPairTurnDistances.Num(); currentTurnIndex++)
						{
							correctedCurrentTurnDist = currentPairTurnDistances[currentTurnIndex] - currentPairTurnDistances[FMath::Clamp(currentTurnIndex - 2, 0, 6)] * FMath::Clamp(currentTurnIndex - 1, 0, 1);

							switch (currentTurnIndex % 2)//here 0 is verticle and 1 is horizontal
							{
							case 0:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition + FVector2D(a, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
								}

								newTrackPos = previousTurnOrIntersectionPosition + FVector2D(correctedCurrentTurnDist, 0);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6; //
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;
									GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "firstOfPairIsRightOfAndBelowSecond and currentRelevantDistance is verticle and right turn made");
								}
								else // if (currentPairTurnDirections[currentTurnIndex] == 2)
								{
									switch (culminatingIntersectionDir)
									{
									case 2:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 12;//intersectiondir: 2, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 11;//intersectiondir: 2, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									case 3:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 8;//intersectiondir: 3, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 3, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}

									if (currentPairTurnDistances.Num() == 1)//this proves its possible for there to be remaining horizontal distance when pairStartsOnDifferentSides and firstOfPairIsRightOfAndEvenWithOrBelowSecond
									{
										if (currentFirstOfPairIndex < holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex].Num() - 1)
										{
											secondOfPairDir = arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex + 1];
											secondOfPairPos = holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex + 1];
											differenceInPairPos = culminatingIntersectionPos - secondOfPairPos;//im changing this from currentFirstOfPairPosition minus second to culminatingIntersectionPos minus second 

											if (secondOfPairDir != currentFirstOfPairDir)
											{
												if (currentFirstOfPairDir == currentFirstOfPairDirCorrectedForAdjustment && differenceInPairPos.Y < -1)
												{
													for (int a = -1; a > differenceInPairPos.Y; a--)
													{
														newTrackPos = secondOfPairPos + FVector2D(0, a);

														convertedTrackPos.X = newTrackPos.X - 1;
														convertedTrackPos.Y = 15 - newTrackPos.Y;
														trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
													}
												}
												else if (currentFirstOfPairDir != currentFirstOfPairDirCorrectedForAdjustment && differenceInPairPos.X < -1)
												{
													for (int a = -1; a > differenceInPairPos.X; a--)
													{
														newTrackPos = secondOfPairPos + FVector2D(a, 0);

														convertedTrackPos.X = newTrackPos.X - 1;
														convertedTrackPos.Y = 15 - newTrackPos.Y;
														trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
													}
												}
											}
										}
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition + FVector2D(0, a);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//is this really the best way to do this??//:>:P
								}

								newTrackPos = previousTurnOrIntersectionPosition + FVector2D(0, correctedCurrentTurnDist);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5; //
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
								}
								else
								{
									switch (culminatingIntersectionDir)
									{
									case 2:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 12;//intersectiondir: 2, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 11;//intersectiondir: 2, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									case 3:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 8;//intersectiondir: 3, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 3, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}
								break;
							default:
								break;
							}
						}
					}

					//here, if the current culminating intersection gets an adjustment, we lay the track to span the adjustment now
					if (adjustmentAppliedToCulminatingIntersectionPair != 0)//can this be in this scope or does it need to move up into the next? I think it can..
					{
						if (adjustmentAppliedToCulminatingIntersectionPair % 2 == 1 - ((currentFirstOfPairIndex / 2) % 2))
						{// this means: if current culminating intersection does get adjustment

							if (adjustmentAppliedToCulminatingIntersectionPair == 3)
							{
								intersectionAdjustmentTrackerArr[currentFirstOfPairIndex / 2] = 2;

								switch (culminatingIntersectionDir)
								{
								case 2:
									newTrackPos = culminatingIntersectionPos + FVector2D(1, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;
									break;
								case 3:
									newTrackPos = culminatingIntersectionPos - FVector2D(0, 1);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;
									break;
								default:
									break;
								}
							}
							else
							{
								intersectionAdjustmentTrackerArr[currentFirstOfPairIndex / 2] = 1;

								for (int a = 1; a <= extentOfAdjustment; a++)
								{
									newTrackPos = culminatingIntersectionPos + FVector2D(a * (1 - (culminatingIntersectionDir % 2)), a * (culminatingIntersectionDir % 2) * -1);//does this -1 work here as written?

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2 - (culminatingIntersectionDir % 2);
								}
							}
						}
					}
					else
					{
						intersectionAdjustmentTrackerArr[currentFirstOfPairIndex / 2] = 0;
					}

					break;
				case 3 :
					if (currentIntersectionAdjustmentTracker)
					{
						if (currentIntersectionAdjustmentTracker == 2)
						{ // this will mean there is in adjustment to intersections of pair facing opposite directions
							previousTurnOrIntersectionPosition.Y -= 1;
						}
						else
						{
							previousTurnOrIntersectionPosition.Y -= extentOfAdjustment;
						}
					}

					if (firstOfPairIsAboveSecondAllPairs[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex / 2])
					{
						for (int currentTurnIndex = 0; currentTurnIndex < currentPairTurnDistances.Num(); currentTurnIndex++)
						{
							correctedCurrentTurnDist = currentPairTurnDistances[currentTurnIndex] - currentPairTurnDistances[FMath::Clamp(currentTurnIndex - 2, 0, 6)] * FMath::Clamp(currentTurnIndex - 1, 0, 1);

							switch (currentTurnIndex % 2)//here 0 is verticle and 1 is horizontal
							{
							case 0:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition + FVector2D(0, a);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
								}

								newTrackPos = previousTurnOrIntersectionPosition + FVector2D(0, correctedCurrentTurnDist);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3; //remember when firstOfPairIsAboveSecond the first verticle turn is facing a different direction then all of the rest
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
								}
								else // if (currentPairTurnDirections[currentTurnIndex] == 2)
								{
									switch (culminatingIntersectionDir)
									{
									case 3:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 8;//intersectiondir: 3, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 3, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									case 4:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 10;//intersectiondir: 4, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 9;//intersectiondir: 4, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition + FVector2D(a, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//is this really the best way to do this??//:>:P
								}

								newTrackPos = previousTurnOrIntersectionPosition + FVector2D(correctedCurrentTurnDist, 0);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;
									GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "firstOfPairIsAboveSecond and currentRelevantDistance is horizontal and right turn made");
								}
								else
								{
									switch (culminatingIntersectionDir)
									{
									case 3:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 8;//intersectiondir: 3, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 3, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									case 4:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 10;//intersectiondir: 4, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 9;//intersectiondir: 4, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}
								break;
							default:
								break;
							}
						}
					}
					else if (firstOfPairIsEvenWithOrLeftOfSecondAllPairs[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex / 2])
					{//remember when inevitably firstOfPairIsEvenWithOrLeftOfSecond and pairStartsOnSameSide you must either change how this is calculated to work off of firstOfPairPosition or change how intersectionPosition is calculated in generateTrackShape to work off previousTurnOrIntersectionPosition. just change the stuff here and leave the stuff above. ACTually I think in adding correctedTurnDist I solved this problem
						for (int currentTurnIndex = 0; currentTurnIndex < currentPairTurnDistances.Num(); currentTurnIndex++)
						{
							correctedCurrentTurnDist = currentPairTurnDistances[currentTurnIndex] - currentPairTurnDistances[FMath::Clamp(currentTurnIndex - 2, 0, 6)] * FMath::Clamp(currentTurnIndex - 1, 0, 1);

							switch (currentTurnIndex % 2)//here 0 is verticle and 1 is horizontal
							{
							case 0:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition - FVector2D(0, a);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
								}

								newTrackPos = previousTurnOrIntersectionPosition - FVector2D(0, correctedCurrentTurnDist);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3; //
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;
								}
								else // if (currentPairTurnDirections[currentTurnIndex] == 2)
								{
									switch (culminatingIntersectionDir)
									{
									case 3:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 8;//intersectiondir: 3, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 3, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									case 4:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 10;//intersectiondir: 4, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 9;//intersectiondir: 4, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition - FVector2D(a, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//is this really the best way to do this??//:>:P
								}

								newTrackPos = previousTurnOrIntersectionPosition - FVector2D(correctedCurrentTurnDist, 0);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									if (currentTurnIndex == currentPairTurnDistances.Num() - 1)
									{
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;
									}
									else
									{
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
									}
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
									GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "firstOfPairIsEvenWithOrLeftOfSecond and currentRelevantDistance is horizontal and right turn made");
								}
								else
								{
									switch (culminatingIntersectionDir)
									{
									case 3:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 8;//intersectiondir: 3, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 3, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									case 4:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 10;//intersectiondir: 4, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 9;//intersectiondir: 4, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}
								break;
							default:
								break;
							}
						}
					}
					else
					{
						for (int currentTurnIndex = 0; currentTurnIndex < currentPairTurnDistances.Num(); currentTurnIndex++)
						{
							correctedCurrentTurnDist = currentPairTurnDistances[currentTurnIndex] - currentPairTurnDistances[FMath::Clamp(currentTurnIndex - 2, 0, 6)] * FMath::Clamp(currentTurnIndex - 1, 0, 1);

							switch (currentTurnIndex % 2)//here 0 is verticle and 1 is horizontal
							{
							case 0:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition - FVector2D(0, a);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
								}

								newTrackPos = previousTurnOrIntersectionPosition - FVector2D(0, correctedCurrentTurnDist);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3; //
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;
									GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "firstOfPairIsRightOfAndBelowSecond and currentRelevantDistance is verticle and right turn made");
								}
								else // if (currentPairTurnDirections[currentTurnIndex] == 2)
								{
									switch (culminatingIntersectionDir)
									{
									case 3:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 8;//intersectiondir: 3, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 3, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									case 4:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 10;//intersectiondir: 4, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 9;//intersectiondir: 4, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}

									if (currentPairTurnDistances.Num() == 1)//this proves its possible for there to be remaining horizontal distance when pairStartsOnDifferentSides and firstOfPairIsRightOfAndEvenWithOrBelowSecond
									{
										if (currentFirstOfPairIndex < holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex].Num() - 1)
										{
											secondOfPairDir = arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex + 1];
											secondOfPairPos = holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex + 1];
											differenceInPairPos = culminatingIntersectionPos - secondOfPairPos;//im changing this from currentFirstOfPairPosition minus second to culminatingIntersectionPos minus second 

											if (secondOfPairDir != currentFirstOfPairDir)
											{
												if (currentFirstOfPairDir == currentFirstOfPairDirCorrectedForAdjustment && differenceInPairPos.X < -1)
												{
													for (int a = -1; a > differenceInPairPos.X; a--)
													{
														newTrackPos = secondOfPairPos + FVector2D(a, 0);

														convertedTrackPos.X = newTrackPos.X - 1;
														convertedTrackPos.Y = 15 - newTrackPos.Y;
														trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
													}
												}
												else if (currentFirstOfPairDir != currentFirstOfPairDirCorrectedForAdjustment && differenceInPairPos.Y > 1)
												{
													for (int a = 1; a < differenceInPairPos.Y; a++)
													{
														newTrackPos = secondOfPairPos + FVector2D(0, a);

														convertedTrackPos.X = newTrackPos.X - 1;
														convertedTrackPos.Y = 15 - newTrackPos.Y;
														trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
													}
												}
											}
										}
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition + FVector2D(a, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//is this really the best way to do this??//:>:P
								}

								newTrackPos = previousTurnOrIntersectionPosition + FVector2D(correctedCurrentTurnDist, 0);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6; //
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;
								}
								else
								{
									switch (culminatingIntersectionDir)
									{
									case 3:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 8;//intersectiondir: 3, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 3, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									case 4:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 10;//intersectiondir: 4, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 9;//intersectiondir: 4, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}
								break;
							default:
								break;
							}
						}
					}

					//here, if the current culminating intersection gets an adjustment, we lay the track to span the adjustment now
					if (adjustmentAppliedToCulminatingIntersectionPair != 0)//can this be in this scope or does it need to move up into the next? I think it can..
					{
						if (adjustmentAppliedToCulminatingIntersectionPair % 2 == 1 - ((currentFirstOfPairIndex / 2) % 2))
						{// this means: if current culminating intersection does get adjustment
							if (adjustmentAppliedToCulminatingIntersectionPair == 3)
							{
								intersectionAdjustmentTrackerArr[currentFirstOfPairIndex / 2] = 2;

								switch (culminatingIntersectionDir)
								{
								case 3:
									newTrackPos = culminatingIntersectionPos - FVector2D(0, 1);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;
									break;
								case 4:
									newTrackPos = culminatingIntersectionPos - FVector2D(1, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
									break;
								default:
									break;
								}
							}
							else
							{
								intersectionAdjustmentTrackerArr[currentFirstOfPairIndex / 2] = 1;

								for (int a = 1; a <= extentOfAdjustment; a++)
								{
									newTrackPos = culminatingIntersectionPos + FVector2D(a * (-1 + (culminatingIntersectionDir % 2)), a * (culminatingIntersectionDir % 2) * -1);//does this -1 work here as written?

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2 - (culminatingIntersectionDir % 2);
								}
							}
						}
						
					}
					else
					{
						intersectionAdjustmentTrackerArr[currentFirstOfPairIndex / 2] = 0;
					}

					break;
				case 4 :
					if (currentIntersectionAdjustmentTracker)
					{
						if (currentIntersectionAdjustmentTracker == 2)
						{ // this will mean there is in adjustment to intersections of pair facing opposite directions
							previousTurnOrIntersectionPosition.X -= 1;
						}
						else
						{
							previousTurnOrIntersectionPosition.X -= extentOfAdjustment;
						}
					}

					if (firstOfPairIsAboveSecondAllPairs[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex / 2])
					{
						for (int currentTurnIndex = 0; currentTurnIndex < currentPairTurnDistances.Num(); currentTurnIndex++)
						{
							correctedCurrentTurnDist = currentPairTurnDistances[currentTurnIndex] - currentPairTurnDistances[FMath::Clamp(currentTurnIndex - 2, 0, 6)] * FMath::Clamp(currentTurnIndex - 1, 0, 1);

							switch (currentTurnIndex % 2)//here 0 is verticle and 1 is horizontal
							{
							case 0:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition + FVector2D(a, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
								}

								newTrackPos = previousTurnOrIntersectionPosition + FVector2D(correctedCurrentTurnDist, 0);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4; //remember when firstOfPairIsAboveSecond the first verticle turn is facing a different direction then all of the rest
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;
								}
								else // if (currentPairTurnDirections[currentTurnIndex] == 2)
								{
									switch (culminatingIntersectionDir)
									{
									case 4:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 10;//intersectiondir: 4, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 9;//intersectiondir: 4, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									case 1:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 14;//intersectiondir: 1, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 13;//intersectiondir: 1, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition - FVector2D(0, a);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//is this really the best way to do this??//:>:P
								}

								newTrackPos = previousTurnOrIntersectionPosition - FVector2D(0, correctedCurrentTurnDist);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;
									GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "firstOfPairIsAboveSecond and currentRelevantDistance is horizontal and right turn made");
								}
								else
								{
									switch (culminatingIntersectionDir)
									{
									case 4:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 10;//intersectiondir: 4, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 9;//intersectiondir: 4, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									case 1:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 14;//intersectiondir: 1, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 13;//intersectiondir: 1, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}
								break;
							default:
								break;
							}
						}
					}
					else if (firstOfPairIsEvenWithOrLeftOfSecondAllPairs[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex / 2])
					{//remember when inevitably firstOfPairIsEvenWithOrLeftOfSecond and pairStartsOnSameSide you must either change how this is calculated to work off of firstOfPairPosition or change how intersectionPosition is calculated in generateTrackShape to work off previousTurnOrIntersectionPosition. just change the stuff here and leave the stuff above. ACTually I think in adding correctedTurnDist I solved this problem
						for (int currentTurnIndex = 0; currentTurnIndex < currentPairTurnDistances.Num(); currentTurnIndex++)
						{
							correctedCurrentTurnDist = currentPairTurnDistances[currentTurnIndex] - currentPairTurnDistances[FMath::Clamp(currentTurnIndex - 2, 0, 6)] * FMath::Clamp(currentTurnIndex - 1, 0, 1);

							switch (currentTurnIndex % 2)//here 0 is verticle and 1 is horizontal
							{
							case 0:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition - FVector2D(a, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
								}

								newTrackPos = previousTurnOrIntersectionPosition - FVector2D(correctedCurrentTurnDist, 0);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4; //
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
								}
								else // if (currentPairTurnDirections[currentTurnIndex] == 2)
								{
									switch (culminatingIntersectionDir)
									{
									case 4:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 10;//intersectiondir: 4, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 9;//intersectiondir: 4, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									case 1:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 14;//intersectiondir: 1, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 13;//intersectiondir: 1, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition + FVector2D(0, a);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//is this really the best way to do this??//:>:P
								}

								newTrackPos = previousTurnOrIntersectionPosition + FVector2D(0, correctedCurrentTurnDist);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									if (currentTurnIndex == currentPairTurnDistances.Num() - 1)
									{
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
									}
									else
									{
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;
									}
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
									GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "firstOfPairIsEvenWithOrLeftOfSecond and currentRelevantDistance is horizontal and right turn made");
								}
								else
								{
									switch (culminatingIntersectionDir)
									{
									case 4:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 10;//intersectiondir: 4, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 9;//intersectiondir: 4, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									case 1:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 14;//intersectiondir: 1, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 13;//intersectiondir: 1, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}
								break;
							default:
								break;
							}
						}
					}
					else
					{
						for (int currentTurnIndex = 0; currentTurnIndex < currentPairTurnDistances.Num(); currentTurnIndex++)
						{
							correctedCurrentTurnDist = currentPairTurnDistances[currentTurnIndex] - currentPairTurnDistances[FMath::Clamp(currentTurnIndex - 2, 0, 6)] * FMath::Clamp(currentTurnIndex - 1, 0, 1);

							switch (currentTurnIndex % 2)//here 0 is verticle and 1 is horizontal
							{
							case 0:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition - FVector2D(a, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
								}

								newTrackPos = previousTurnOrIntersectionPosition - FVector2D(correctedCurrentTurnDist, 0);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4; //
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
									GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "firstOfPairIsRightOfAndBelowSecond and currentRelevantDistance is verticle and right turn made");
								}
								else // if (currentPairTurnDirections[currentTurnIndex] == 2)
								{
									switch (culminatingIntersectionDir)
									{
									case 4:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 10;//intersectiondir: 4, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 9;//intersectiondir: 4, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									case 1:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 14;//intersectiondir: 1, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 13;//intersectiondir: 1, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}

									if (currentPairTurnDistances.Num() == 1)//this proves its possible for there to be remaining horizontal distance when pairStartsOnDifferentSides and firstOfPairIsRightOfAndEvenWithOrBelowSecond
									{
										if (currentFirstOfPairIndex < holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex].Num() - 1)
										{
											secondOfPairDir = arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex + 1];
											secondOfPairPos = holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex + 1];
											differenceInPairPos = culminatingIntersectionPos - secondOfPairPos;//im changing this from currentFirstOfPairPosition minus second to culminatingIntersectionPos minus second 

											if (secondOfPairDir != currentFirstOfPairDir)
											{
												if (currentFirstOfPairDir == currentFirstOfPairDirCorrectedForAdjustment && differenceInPairPos.Y > 1)
												{
													for (int a = 1; a < differenceInPairPos.Y; a++)
													{
														newTrackPos = secondOfPairPos + FVector2D(0, a);

														convertedTrackPos.X = newTrackPos.X - 1;
														convertedTrackPos.Y = 15 - newTrackPos.Y;
														trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
													}
												}
												else if (currentFirstOfPairDir == currentFirstOfPairDirCorrectedForAdjustment && differenceInPairPos.X > 1)
												{
													for (int a = 1; a < differenceInPairPos.X; a++)
													{
														newTrackPos = secondOfPairPos + FVector2D(a, 0);

														convertedTrackPos.X = newTrackPos.X - 1;
														convertedTrackPos.Y = 15 - newTrackPos.Y;
														trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
													}
												}
											}
										}
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition - FVector2D(0, a);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//is this really the best way to do this??//:>:P
								}

								newTrackPos = previousTurnOrIntersectionPosition - FVector2D(0, correctedCurrentTurnDist);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								if (currentPairTurnDirections[currentTurnIndex] == 1)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3; //
								}
								else if (currentPairTurnDirections[currentTurnIndex] == 0)
								{
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;
								}
								else
								{
									switch (culminatingIntersectionDir)
									{
									case 4:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 10;//intersectiondir: 4, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 9;//intersectiondir: 4, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											break;
										default:
											break;
										}
										break;
									case 1:
										switch (culminatingIntersectionOrientation)
										{
										case 0:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 14;//intersectiondir: 1, intersectionOrientation: 0;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 13;//intersectiondir: 1, intersectionOrientation: 1;
											break;
										case 2:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											break;
										default:
											break;
										}
										break;
									default:
										break;
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

								if (currentTurnIndex == currentPairTurnDistances.Num() - 1)// actually is it even possible for there to be remaining horizontal or verticle distance with how turn distance is calculated? I dont think so..
								{

								}
								break;
							default:
								break;
							}
						}
					}

					//here, if the current culminating intersection gets an adjustment, we lay the track to span the adjustment now
					if (adjustmentAppliedToCulminatingIntersectionPair != 0)//can this be in this scope or does it need to move up into the next? I think it can..
					{
						if (adjustmentAppliedToCulminatingIntersectionPair % 2 == 1 - ((currentFirstOfPairIndex / 2) % 2))
						{// this means: if current culminating intersection does get adjustment
							if (adjustmentAppliedToCulminatingIntersectionPair == 3)
							{
								intersectionAdjustmentTrackerArr[currentFirstOfPairIndex / 2] = 2;

								switch (culminatingIntersectionDir)
								{
								case 4:
									newTrackPos = culminatingIntersectionPos - FVector2D(1, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
									break;
								case 1:
									newTrackPos = culminatingIntersectionPos + FVector2D(0, 1);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
									break;
								default:
									break;
								}
							}
							else
							{
								intersectionAdjustmentTrackerArr[currentFirstOfPairIndex / 2] = 1;

								for (int a = 1; a <= extentOfAdjustment; a++)
								{
									newTrackPos = culminatingIntersectionPos + FVector2D(a * (-1 + (culminatingIntersectionDir % 2)), a * (culminatingIntersectionDir % 2));//does this -1 work here as written?

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2 - (culminatingIntersectionDir % 2);
								}
							}
						}
					}
					else
					{
						intersectionAdjustmentTrackerArr[currentFirstOfPairIndex / 2] = 0;
					}

					break;
				default:
					break;
				}
			}
		}
	}

	//LANDSCAPE DATA
	int currentHoleDir;

	for (int currentGroupIndex = 0; currentGroupIndex < listOfHolePositionGroupings.Num(); currentGroupIndex++)
	{
		currentGroupSize = listOfHolePositionGroupings[currentGroupIndex];

		for (int currentHoleIndex = 0; currentHoleIndex < currentGroupSize; currentHoleIndex++)
		{
			newTrackPos = holeAndIntersectionPositions[0][currentGroupIndex][currentHoleIndex];

			convertedTrackPos.X = newTrackPos.X - 1;
			convertedTrackPos.Y = 15 - newTrackPos.Y;

			currentHoleDir = arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[0][currentGroupIndex][currentHoleIndex];

			switch (currentHoleDir)
			{
			case 1 :
				landscapeArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
				break;
			case 2 :
				landscapeArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
				break;
			case 3 :
				landscapeArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
				break;
			case 4 :
				landscapeArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
				break;
			default:
				break;
			}
		}
	}

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(slateWidgetContainerOne.ToSharedRef());
		//delete loadingSlateWidget.Get(); this doesnt work, it throughs an acception access violation to address 0x0000000 supposedly RemoveViewportWidgetContent takes care of this

		gameSlateWidget = SNew(STestWidgetThree)
			.OwningHUD(this)
			.landscapeArr(landscapeArr)
			.trackArr(trackArr)
			.tileIsIntersection(tileIsIntersection)
			.playerOnePlayerController(playerOnePlayerController)
			.grass_VMUI_1(grass_VMUI_1)
			.holeFromDown_VMUI(holeFromDown_VMUI)
			.holeFromLeft_VMUI(holeFromLeft_VMUI)
			.holeFromRight_VMUI(holeFromRight_VMUI)
			.holeFromUp_VMUI(holeFromUp_VMUI)
			.buttonFromDownTurningRightZero_SMUI(buttonFromDownTurningRightZero_SMUI)
			.buttonFromDownTurningLeftZero_SMUI(buttonFromDownTurningLeftZero_SMUI)
			.buttonFromLeftTurningRightZero_SMUI(buttonFromLeftTurningRightZero_SMUI)
			.buttonFromLeftTurningLeftZero_SMUI(buttonFromLeftTurningLeftZero_SMUI)
			.buttonFromRightTurningRightZero_SMUI(buttonFromRightTurningRightZero_SMUI)
			.buttonFromRightTurningLeftZero_SMUI(buttonFromRightTurningLeftZero_SMUI)
			.buttonFromUpTurningRightZero_SMUI(buttonFromUpTurningRightZero_SMUI)
			.buttonFromUpTurningLeftZero_SMUI(buttonFromUpTurningLeftZero_SMUI)
			.verticleRail_SMUI(verticleRail_SMUI)
			.horizontalRail_SMUI(horizontalRail_SMUI)
			.railTurningOne_SMUI(railTurningOne_SMUI)
			.railTurningTwo_SMUI(railTurningTwo_SMUI)
			.railTurningThree_SMUI(railTurningThree_SMUI)
			.railTurningFour_SMUI(railTurningFour_SMUI)
			.emptyImg_SMUI(emptyImg_SMUI)
			.marble_SMUI_1(marble_SMUI_1)
			.marble_SMUI_2(marble_SMUI_2)
			.marble_SMUI_3(marble_SMUI_3)
			.marble_SMUI_4(marble_SMUI_4)
			.marble_SMUI_5(marble_SMUI_5)
			.marble_SMUI_6(marble_SMUI_6)
			.marble_SMUI_7(marble_SMUI_7);

		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(slateWidgetContainerTwo, SWeakWidget).PossiblyNullContent(gameSlateWidget.ToSharedRef()));

		FInputModeUIOnly gameInWidgetInputMode = FInputModeUIOnly();
		gameInWidgetInputMode.SetWidgetToFocus(loadingSlateWidget);
		gameInWidgetInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		playerOnePlayerController->SetInputMode(gameInWidgetInputMode);
		playerOnePlayerController->SetShowMouseCursor(true);
		FSlateApplication::Get().SetKeyboardFocus(gameSlateWidget);
	}
}

void ATestHud::GenerateLevel()
{
	GenerateHolePositions();

	GenerateTrackShape();

	BuildLevel();
}

void ATestHud::HouseKeeping()
{
	arrOfViableHoleCoordinates.Empty();
	holePositions.Empty();
	test.Empty();
	listOfHolePositionGroupings.Empty();

	holeAndIntersectionPositions =
	{
		{
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) }
		},
		{
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) }
		},
		{
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) }
		},
		{
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) }
		},
		{
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) }
		},
		{
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) }
		},
		{
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) }
		},
		{
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) },
			{ FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0), FVector2D(0, 0) }
		}
	};

	arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection =
	{
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0 }
		}
	};

	adjustmentsAppliedToEachIntersection =
	{
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	};

	intersectionOrientationsPerGroupPerLevel =
	{// 0 for right, 1 for left, 2 for straight, all comming from the previous hole or intersection
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	};

	firstOfPairIsAboveSecondAllPairs =
	{
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	};

	firstOfPairIsEvenWithOrLeftOfSecondAllPairs =
	{
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	};

	turnAndIntersectionDistancesPerPair =
	{
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		}
	};

	directionsOfTurns =
	{
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		},
		{
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			},
			{
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0 },
			}
		}
	};

	landscapeArr = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	trackArr = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	tileIsIntersection = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
}