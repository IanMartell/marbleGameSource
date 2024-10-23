// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h" // we include the engine because we need to get a pointer to the global engine to actually add something to the screen
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"
#include "Math/UnrealMathUtility.h"
#include "Components/AudioComponent.h"
#include "SaveGameOne.h"
#include "SCompanySplash.h"
#include "SOptions.h"
#include "SSArcadeModeTitleScreen.h"
#include "SCurtains.h"
#include "SCurtainsTwo.h"
#include "SPauseScreen.h"
#include "SResultsBlur.h"
#include "STestWidgetThree.h"
//#include "Engine/Classes/Materials/Material.h"

FVector2D GetGameViewportSize()
{
	FVector2D Result = FVector2D(1, 1);

	GEngine->GameViewport->GetViewportSize( /*out*/Result);

	return Result;
}

AMyHUD::AMyHUD()
{
	//do I really need these fucking if statements? maybe I should try to keep them its common convention
	//grass
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
		grass_IS_1 = (UImgMediaSource*)tempVarGrass_IS_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarGrass_VMUI_2(TEXT("'/Game/Movies/videoMaterialsForUI/grass_VMUI_2.grass_VMUI_2'"));
	if (tempVarGrass_VMUI_2.Object != NULL)
	{
		grass_VMUI_2 = (UMaterial*)tempVarGrass_VMUI_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarGrass_MP_2(TEXT("'/Game/Movies/mediaPlayers/grass_2_MP.grass_2_MP'"));
	if (tempVarGrass_MP_2.Object != NULL)
	{
		grass_MP_2 = (UMediaPlayer*)tempVarGrass_MP_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarGrass_IS_2(TEXT("'/Game/Movies/imageSources/grass_2_IS.grass_2_IS'"));
	if (tempVarGrass_IS_2.Object != NULL)
	{
		grass_IS_2 = (UImgMediaSource*)tempVarGrass_IS_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarGrass_VMUI_3(TEXT("'/Game/Movies/videoMaterialsForUI/grass_VMUI_3.grass_VMUI_3'"));
	if (tempVarGrass_VMUI_3.Object != NULL)
	{
		grass_VMUI_3 = (UMaterial*)tempVarGrass_VMUI_3.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarGrass_MP_3(TEXT("'/Game/Movies/mediaPlayers/grass_3_MP.grass_3_MP'"));
	if (tempVarGrass_MP_3.Object != NULL)
	{
		grass_MP_3 = (UMediaPlayer*)tempVarGrass_MP_3.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarGrass_IS_3(TEXT("'/Game/Movies/imageSources/grass_3_IS.grass_3_IS'"));
	if (tempVarGrass_IS_3.Object != NULL)
	{
		grass_IS_3 = (UImgMediaSource*)tempVarGrass_IS_3.Object;
	}
	//ponds
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarPondHorizontal_VMUI(TEXT("'/Game/Movies/videoMaterialsForUI/pondHorizontal_VMUI.pondHorizontal_VMUI'"));
	if (tempVarPondHorizontal_VMUI.Object != NULL)
	{
		pondHorizontal_VMUI = (UMaterial*)tempVarPondHorizontal_VMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarPondHorizontal_MP(TEXT("'/Game/Movies/mediaPlayers/pondHorizontal_MP.pondHorizontal_MP'"));
	if (tempVarPondHorizontal_MP.Object != NULL)
	{
		pondHorizontal_MP = (UMediaPlayer*)tempVarPondHorizontal_MP.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarPondHorizontal_IS(TEXT("'/Game/Movies/imageSources/pondHorizontal_IS.pondHorizontal_IS'"));
	if (tempVarPondHorizontal_IS.Object != NULL)
	{
		pondHorizontal_IS = (UImgMediaSource*)tempVarPondHorizontal_IS.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarPondVerticleFlowingLeft_VMUI(TEXT("'/Game/Movies/videoMaterialsForUI/pondVerticleFlowingLeft_VMUI.pondVerticleFlowingLeft_VMUI'"));
	if (tempVarPondVerticleFlowingLeft_VMUI.Object != NULL)
	{
		pondVerticleFlowingLeft_VMUI = (UMaterial*)tempVarPondVerticleFlowingLeft_VMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarPondVerticleFlowingLeft_MP(TEXT("'/Game/Movies/mediaPlayers/pondVerticleFlowingLeft_MP.pondVerticleFlowingLeft_MP'"));
	if (tempVarPondVerticleFlowingLeft_MP.Object != NULL)
	{
		pondVerticleFlowingLeft_MP = (UMediaPlayer*)tempVarPondVerticleFlowingLeft_MP.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarPondVerticleFlowingLeft_IS(TEXT("'/Game/Movies/imageSources/pondVerticleFlowingLeft_IS.pondVerticleFlowingLeft_IS'"));
	if (tempVarPondVerticleFlowingLeft_IS.Object != NULL)
	{
		pondVerticleFlowingLeft_IS = (UImgMediaSource*)tempVarPondVerticleFlowingLeft_IS.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarPondVerticleFlowingRight_VMUI(TEXT("'/Game/Movies/videoMaterialsForUI/pondVerticleFlowingRight_VMUI.pondVerticleFlowingRight_VMUI'"));
	if (tempVarPondVerticleFlowingRight_VMUI.Object != NULL)
	{
		pondVerticleFlowingRight_VMUI = (UMaterial*)tempVarPondVerticleFlowingRight_VMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarPondVerticleFlowingRight_MP(TEXT("'/Game/Movies/mediaPlayers/pondVerticleFlowingRight_MP.pondVerticleFlowingRight_MP'"));
	if (tempVarPondVerticleFlowingRight_MP.Object != NULL)
	{
		pondVerticleFlowingRight_MP = (UMediaPlayer*)tempVarPondVerticleFlowingRight_MP.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarPondVerticleFlowingRight_IS(TEXT("'/Game/Movies/imageSources/pondVerticleFlowingRight_IS.pondVerticleFlowingRight_IS'"));
	if (tempVarPondVerticleFlowingRight_IS.Object != NULL)
	{
		pondVerticleFlowingRight_IS = (UImgMediaSource*)tempVarPondVerticleFlowingRight_IS.Object;
	}
	//river flowing down
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarRiverFlowingDown_VMUI_1(TEXT("'/Game/Movies/videoMaterialsForUI/riverFlowingDown_VMUI_1.riverFlowingDown_VMUI_1'"));
	if (tempVarRiverFlowingDown_VMUI_1.Object != NULL)
	{
		riverFlowingDown_VMUI_1 = (UMaterial*)tempVarRiverFlowingDown_VMUI_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarRiverFlowingDown_MP_1(TEXT("'/Game/Movies/mediaPlayers/riverFlowingDown_MP_1.riverFlowingDown_MP_1'"));
	if (tempVarRiverFlowingDown_MP_1.Object != NULL)
	{
		riverFlowingDown_MP_1 = (UMediaPlayer*)tempVarRiverFlowingDown_MP_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarRiverFlowingDown_IS_1(TEXT("'/Game/Movies/imageSources/riverFlowingDown_IS_1.riverFlowingDown_IS_1'"));
	if (tempVarRiverFlowingDown_IS_1.Object != NULL)
	{
		riverFlowingDown_IS_1 = (UImgMediaSource*)tempVarRiverFlowingDown_IS_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarRiverFlowingDown_VMUI_2(TEXT("'/Game/Movies/videoMaterialsForUI/riverFlowingDown_VMUI_2.riverFlowingDown_VMUI_2'"));
	if (tempVarRiverFlowingDown_VMUI_2.Object != NULL)
	{
		riverFlowingDown_VMUI_2 = (UMaterial*)tempVarRiverFlowingDown_VMUI_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarRiverFlowingDown_MP_2(TEXT("'/Game/Movies/mediaPlayers/riverFlowingDown_MP_2.riverFlowingDown_MP_2'"));
	if (tempVarRiverFlowingDown_MP_2.Object != NULL)
	{
		riverFlowingDown_MP_2 = (UMediaPlayer*)tempVarRiverFlowingDown_MP_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarRiverFlowingDown_IS_2(TEXT("'/Game/Movies/imageSources/riverFlowingDown_IS_2.riverFlowingDown_IS_2'"));
	if (tempVarRiverFlowingDown_IS_2.Object != NULL)
	{
		riverFlowingDown_IS_2 = (UImgMediaSource*)tempVarRiverFlowingDown_IS_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarRiverFlowingDown_VMUI_3(TEXT("'/Game/Movies/videoMaterialsForUI/riverFlowingDown_VMUI_3.riverFlowingDown_VMUI_3'"));
	if (tempVarRiverFlowingDown_VMUI_3.Object != NULL)
	{
		riverFlowingDown_VMUI_3 = (UMaterial*)tempVarRiverFlowingDown_VMUI_3.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarRiverFlowingDown_MP_3(TEXT("'/Game/Movies/mediaPlayers/riverFlowingDown_MP_3.riverFlowingDown_MP_3'"));
	if (tempVarRiverFlowingDown_MP_3.Object != NULL)
	{
		riverFlowingDown_MP_3 = (UMediaPlayer*)tempVarRiverFlowingDown_MP_3.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarRiverFlowingDown_IS_3(TEXT("'/Game/Movies/imageSources/riverFlowingDown_IS_3.riverFlowingDown_IS_3'"));
	if (tempVarRiverFlowingDown_IS_3.Object != NULL)
	{
		riverFlowingDown_IS_3 = (UImgMediaSource*)tempVarRiverFlowingDown_IS_3.Object;
	}
	//river flowing left
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarRiverFlowingLeft_VMUI_1(TEXT("'/Game/Movies/videoMaterialsForUI/riverFlowingLeft_VMUI_1.riverFlowingLeft_VMUI_1'"));
	if (tempVarRiverFlowingLeft_VMUI_1.Object != NULL)
	{
		riverFlowingLeft_VMUI_1 = (UMaterial*)tempVarRiverFlowingLeft_VMUI_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarRiverFlowingLeft_MP_1(TEXT("'/Game/Movies/mediaPlayers/riverFlowingLeft_MP_1.riverFlowingLeft_MP_1'"));
	if (tempVarRiverFlowingLeft_MP_1.Object != NULL)
	{
		riverFlowingLeft_MP_1 = (UMediaPlayer*)tempVarRiverFlowingLeft_MP_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarRiverFlowingLeft_IS_1(TEXT("'/Game/Movies/imageSources/riverFlowingLeft_IS_1.riverFlowingLeft_IS_1'"));
	if (tempVarRiverFlowingLeft_IS_1.Object != NULL)
	{
		riverFlowingLeft_IS_1 = (UImgMediaSource*)tempVarRiverFlowingLeft_IS_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarRiverFlowingLeft_VMUI_2(TEXT("'/Game/Movies/videoMaterialsForUI/riverFlowingLeft_VMUI_2.riverFlowingLeft_VMUI_2'"));
	if (tempVarRiverFlowingLeft_VMUI_2.Object != NULL)
	{
		riverFlowingLeft_VMUI_2 = (UMaterial*)tempVarRiverFlowingLeft_VMUI_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarRiverFlowingLeft_MP_2(TEXT("'/Game/Movies/mediaPlayers/riverFlowingLeft_MP_2.riverFlowingLeft_MP_2'"));
	if (tempVarRiverFlowingLeft_MP_2.Object != NULL)
	{
		riverFlowingLeft_MP_2 = (UMediaPlayer*)tempVarRiverFlowingLeft_MP_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarRiverFlowingLeft_IS_2(TEXT("'/Game/Movies/imageSources/riverFlowingLeft_IS_2.riverFlowingLeft_IS_2'"));
	if (tempVarRiverFlowingLeft_IS_2.Object != NULL)
	{
		riverFlowingLeft_IS_2 = (UImgMediaSource*)tempVarRiverFlowingLeft_IS_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarRiverFlowingLeft_VMUI_3(TEXT("'/Game/Movies/videoMaterialsForUI/riverFlowingLeft_VMUI_3.riverFlowingLeft_VMUI_3'"));
	if (tempVarRiverFlowingLeft_VMUI_3.Object != NULL)
	{
		riverFlowingLeft_VMUI_3 = (UMaterial*)tempVarRiverFlowingLeft_VMUI_3.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarRiverFlowingLeft_MP_3(TEXT("'/Game/Movies/mediaPlayers/riverFlowingLeft_MP_3.riverFlowingLeft_MP_3'"));
	if (tempVarRiverFlowingLeft_MP_3.Object != NULL)
	{
		riverFlowingLeft_MP_3 = (UMediaPlayer*)tempVarRiverFlowingLeft_MP_3.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarRiverFlowingLeft_IS_3(TEXT("'/Game/Movies/imageSources/riverFlowingLeft_IS_3.riverFlowingLeft_IS_3'"));
	if (tempVarRiverFlowingLeft_IS_3.Object != NULL)
	{
		riverFlowingLeft_IS_3 = (UImgMediaSource*)tempVarRiverFlowingLeft_IS_3.Object;
	}
	//river flowing right
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarRiverFlowingRight_VMUI_1(TEXT("'/Game/Movies/videoMaterialsForUI/riverFlowingRight_VMUI_1.riverFlowingRight_VMUI_1'"));
	if (tempVarRiverFlowingRight_VMUI_1.Object != NULL)
	{
		riverFlowingRight_VMUI_1 = (UMaterial*)tempVarRiverFlowingRight_VMUI_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarRiverFlowingRight_MP_1(TEXT("'/Game/Movies/mediaPlayers/riverFlowingRight_MP_1.riverFlowingRight_MP_1'"));
	if (tempVarRiverFlowingRight_MP_1.Object != NULL)
	{
		riverFlowingRight_MP_1 = (UMediaPlayer*)tempVarRiverFlowingRight_MP_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarRiverFlowingRight_IS_1(TEXT("'/Game/Movies/imageSources/riverFlowingRight_IS_1.riverFlowingRight_IS_1'"));
	if (tempVarRiverFlowingRight_IS_1.Object != NULL)
	{
		riverFlowingRight_IS_1 = (UImgMediaSource*)tempVarRiverFlowingRight_IS_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarRiverFlowingRight_VMUI_2(TEXT("'/Game/Movies/videoMaterialsForUI/riverFlowingRight_VMUI_2.riverFlowingRight_VMUI_2'"));
	if (tempVarRiverFlowingRight_VMUI_2.Object != NULL)
	{
		riverFlowingRight_VMUI_2 = (UMaterial*)tempVarRiverFlowingRight_VMUI_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarRiverFlowingRight_MP_2(TEXT("'/Game/Movies/mediaPlayers/riverFlowingRight_MP_2.riverFlowingRight_MP_2'"));
	if (tempVarRiverFlowingRight_MP_2.Object != NULL)
	{
		riverFlowingRight_MP_2 = (UMediaPlayer*)tempVarRiverFlowingRight_MP_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarRiverFlowingRight_IS_2(TEXT("'/Game/Movies/imageSources/riverFlowingRight_IS_2.riverFlowingRight_IS_2'"));
	if (tempVarRiverFlowingRight_IS_2.Object != NULL)
	{
		riverFlowingRight_IS_2 = (UImgMediaSource*)tempVarRiverFlowingRight_IS_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarRiverFlowingRight_VMUI_3(TEXT("'/Game/Movies/videoMaterialsForUI/riverFlowingRight_VMUI_3.riverFlowingRight_VMUI_3'"));
	if (tempVarRiverFlowingRight_VMUI_3.Object != NULL)
	{
		riverFlowingRight_VMUI_3 = (UMaterial*)tempVarRiverFlowingRight_VMUI_3.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarRiverFlowingRight_MP_3(TEXT("'/Game/Movies/mediaPlayers/riverFlowingRight_MP_3.riverFlowingRight_MP_3'"));
	if (tempVarRiverFlowingRight_MP_3.Object != NULL)
	{
		riverFlowingRight_MP_3 = (UMediaPlayer*)tempVarRiverFlowingRight_MP_3.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarRiverFlowingRight_IS_3(TEXT("'/Game/Movies/imageSources/riverFlowingRight_IS_3.riverFlowingRight_IS_3'"));
	if (tempVarRiverFlowingRight_IS_3.Object != NULL)
	{
		riverFlowingRight_IS_3 = (UImgMediaSource*)tempVarRiverFlowingRight_IS_3.Object;
	}
	//trees
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarTree_VMUI_1(TEXT("'/Game/Movies/videoMaterialsForUI/tree_VMUI_1.tree_VMUI_1'"));
	if (tempVarTree_VMUI_1.Object != NULL)
	{
		tree_VMUI_1 = (UMaterial*)tempVarTree_VMUI_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarTree_MP_1(TEXT("'/Game/Movies/mediaPlayers/tree_MP_1.tree_MP_1'"));
	if (tempVarTree_MP_1.Object != NULL)
	{
		tree_MP_1 = (UMediaPlayer*)tempVarTree_MP_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarTree_IS_1(TEXT("'/Game/Movies/imageSources/tree_IS_1.tree_IS_1'"));
	if (tempVarTree_IS_1.Object != NULL)
	{
		tree_IS_1 = (UImgMediaSource*)tempVarTree_IS_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarTree_VMUI_2(TEXT("'/Game/Movies/videoMaterialsForUI/tree_VMUI_2.tree_VMUI_2'"));
	if (tempVarTree_VMUI_2.Object != NULL)
	{
		tree_VMUI_2 = (UMaterial*)tempVarTree_VMUI_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarTree_MP_2(TEXT("'/Game/Movies/mediaPlayers/tree_MP_2.tree_MP_2'"));
	if (tempVarTree_MP_2.Object != NULL)
	{
		tree_MP_2 = (UMediaPlayer*)tempVarTree_MP_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarTree_IS_2(TEXT("'/Game/Movies/imageSources/tree_IS_2.tree_IS_2'"));
	if (tempVarTree_IS_2.Object != NULL)
	{
		tree_IS_2 = (UImgMediaSource*)tempVarTree_IS_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarTree_VMUI_3(TEXT("'/Game/Movies/videoMaterialsForUI/tree_VMUI_3.tree_VMUI_3'"));
	if (tempVarTree_VMUI_3.Object != NULL)
	{
		tree_VMUI_3 = (UMaterial*)tempVarTree_VMUI_3.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarTree_MP_3(TEXT("'/Game/Movies/mediaPlayers/tree_MP_3.tree_MP_3'"));
	if (tempVarTree_MP_3.Object != NULL)
	{
		tree_MP_3 = (UMediaPlayer*)tempVarTree_MP_3.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarTree_IS_3(TEXT("'/Game/Movies/imageSources/tree_IS_3.tree_IS_3'"));
	if (tempVarTree_IS_3.Object != NULL)
	{
		tree_IS_3 = (UImgMediaSource*)tempVarTree_IS_3.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarTree_VMUI_4(TEXT("'/Game/Movies/videoMaterialsForUI/tree_VMUI_4.tree_VMUI_4'"));
	if (tempVarTree_VMUI_4.Object != NULL)
	{
		tree_VMUI_4 = (UMaterial*)tempVarTree_VMUI_4.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarTree_MP_4(TEXT("'/Game/Movies/mediaPlayers/tree_MP_4.tree_MP_4'"));
	if (tempVarTree_MP_4.Object != NULL)
	{
		tree_MP_4 = (UMediaPlayer*)tempVarTree_MP_4.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarTree_IS_4(TEXT("'/Game/Movies/imageSources/tree_IS_4.tree_IS_4'"));
	if (tempVarTree_IS_4.Object != NULL)
	{
		tree_IS_4 = (UImgMediaSource*)tempVarTree_IS_4.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarTree_VMUI_5(TEXT("'/Game/Movies/videoMaterialsForUI/tree_VMUI_5.tree_VMUI_5'"));
	if (tempVarTree_VMUI_5.Object != NULL)
	{
		tree_VMUI_5 = (UMaterial*)tempVarTree_VMUI_5.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarTree_MP_5(TEXT("'/Game/Movies/mediaPlayers/tree_MP_5.tree_MP_5'"));
	if (tempVarTree_MP_5.Object != NULL)
	{
		tree_MP_5 = (UMediaPlayer*)tempVarTree_MP_5.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarTree_IS_5(TEXT("'/Game/Movies/imageSources/tree_IS_5.tree_IS_5'"));
	if (tempVarTree_IS_5.Object != NULL)
	{
		tree_IS_5 = (UImgMediaSource*)tempVarTree_IS_5.Object;
	}
	//waterfall
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarWaterfall_VMUI(TEXT("'/Game/Movies/videoMaterialsForUI/waterfall_VMUI.waterfall_VMUI'"));
	if (tempVarWaterfall_VMUI.Object != NULL)
	{
		waterfall_VMUI = (UMaterial*)tempVarWaterfall_VMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempWaterfall_MP(TEXT("'/Game/Movies/mediaPlayers/waterfall_MP.waterfall_MP'"));
	if (tempWaterfall_MP.Object != NULL)
	{
		waterfall_MP = (UMediaPlayer*)tempWaterfall_MP.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarWaterfall_IS(TEXT("'/Game/Movies/imageSources/waterfall_IS.waterfall_IS'"));
	if (tempVarWaterfall_IS.Object != NULL)
	{
		waterfall_IS = (UImgMediaSource*)tempVarWaterfall_IS.Object;
	}
	//river turning
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarRiverTurning_VMUI_1(TEXT("'/Game/Movies/videoMaterialsForUI/waterTurningLeftLatToLon_VMUI.waterTurningLeftLatToLon_VMUI'"));
	if (tempVarRiverTurning_VMUI_1.Object != NULL)
	{
		riverTurning_VMUI_1 = (UMaterial*)tempVarRiverTurning_VMUI_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarRiverTurning_MP_1(TEXT("'/Game/Movies/mediaPlayers/waterTurningLeftLatToLon_MP.waterTurningLeftLatToLon_MP'"));
	if (tempVarRiverTurning_MP_1.Object != NULL)
	{
		riverTurning_MP_1 = (UMediaPlayer*)tempVarRiverTurning_MP_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarRiverTurning_IS_1(TEXT("'/Game/Movies/imageSources/waterTurningLeftLatToLon_IS.waterTurningLeftLatToLon_IS'"));
	if (tempVarRiverTurning_IS_1.Object != NULL)
	{
		riverTurning_IS_1 = (UImgMediaSource*)tempVarRiverTurning_IS_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarRiverTurning_VMUI_2(TEXT("'/Game/Movies/videoMaterialsForUI/waterTurningLeftLonToLat_VMUI.waterTurningLeftLonToLat_VMUI'"));
	if (tempVarRiverTurning_VMUI_2.Object != NULL)
	{
		riverTurning_VMUI_2 = (UMaterial*)tempVarRiverTurning_VMUI_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarRiverTurning_MP_2(TEXT("'/Game/Movies/mediaPlayers/waterTurningLeftLonToLat_MP.waterTurningLeftLonToLat_MP'"));
	if (tempVarRiverTurning_MP_2.Object != NULL)
	{
		riverTurning_MP_2 = (UMediaPlayer*)tempVarRiverTurning_MP_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarRiverTurning_IS_2(TEXT("'/Game/Movies/imageSources/waterTurningLeftLonToLat_IS.waterTurningLeftLonToLat_IS'"));
	if (tempVarRiverTurning_IS_2.Object != NULL)
	{
		riverTurning_IS_2 = (UImgMediaSource*)tempVarRiverTurning_IS_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarRiverTurning_VMUI_3(TEXT("'/Game/Movies/videoMaterialsForUI/waterTurningRightLatToLon_VMUI.waterTurningRightLatToLon_VMUI'"));
	if (tempVarRiverTurning_VMUI_3.Object != NULL)
	{
		riverTurning_VMUI_3 = (UMaterial*)tempVarRiverTurning_VMUI_3.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarRiverTurning_MP_3(TEXT("'/Game/Movies/mediaPlayers/waterTurningRightLatToLon_MP.waterTurningRightLatToLon_MP'"));
	if (tempVarRiverTurning_MP_3.Object != NULL)
	{
		riverTurning_MP_3 = (UMediaPlayer*)tempVarRiverTurning_MP_3.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarRiverTurning_IS_3(TEXT("'/Game/Movies/imageSources/waterTurningRightLatToLon_IS.waterTurningRightLatToLon_IS'"));
	if (tempVarRiverTurning_IS_3.Object != NULL)
	{
		riverTurning_IS_3 = (UImgMediaSource*)tempVarRiverTurning_IS_3.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarRiverTurning_VMUI_4(TEXT("'/Game/Movies/videoMaterialsForUI/waterTurningRightLonToLat_VMUI.waterTurningRightLonToLat_VMUI'"));
	if (tempVarRiverTurning_VMUI_4.Object != NULL)
	{
		riverTurning_VMUI_4 = (UMaterial*)tempVarRiverTurning_VMUI_4.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarRiverTurning_MP_4(TEXT("'/Game/Movies/mediaPlayers/waterTurningRightLonToLat_MP.waterTurningRightLonToLat_MP'"));
	if (tempVarRiverTurning_MP_4.Object != NULL)
	{
		riverTurning_MP_4 = (UMediaPlayer*)tempVarRiverTurning_MP_4.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarRiverTurning_IS_4(TEXT("'/Game/Movies/imageSources/waterTurningRightLonToLat_IS.waterTurningRightLonToLat_IS'"));
	if (tempVarRiverTurning_IS_4.Object != NULL)
	{
		riverTurning_IS_4 = (UImgMediaSource*)tempVarRiverTurning_IS_4.Object;
	}

	//mountains
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarMountain_VMUI_1(TEXT("'/Game/Movies/videoMaterialsForUI/mountain_VMUI_1.mountain_VMUI_1'"));
	if (tempVarMountain_VMUI_1.Object != NULL)
	{
		mountain_VMUI_1 = (UMaterial*)tempVarMountain_VMUI_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVarMountain_MP_1(TEXT("'/Game/Movies/mediaPlayers/mountain_MP_1.mountain_MP_1'"));
	if (tempVarMountain_MP_1.Object != NULL)
	{
		mountain_MP_1 = (UMediaPlayer*)tempVarMountain_MP_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVarMountain_IS_1(TEXT("'/Game/Movies/imageSources/mountain_IS_1.mountain_IS_1'"));
	if (tempVarMountain_IS_1.Object != NULL)
	{
		mountain_IS_1 = (UImgMediaSource*)tempVarMountain_IS_1.Object;
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
		holeFromDown_IS = (UImgMediaSource*)tempVar_holeFromDown_IS.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_holeFromLeft_IS(TEXT("'/Game/Movies/imageSources/holeFromLeft_IS.holeFromLeft_IS'"));
	if (tempVar_holeFromLeft_IS.Object != NULL)
	{
		holeFromLeft_IS = (UImgMediaSource*)tempVar_holeFromLeft_IS.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_holeFromRight_IS(TEXT("'/Game/Movies/imageSources/holeFromRight_IS.holeFromRight_IS'"));
	if (tempVar_holeFromRight_IS.Object != NULL)
	{
		holeFromRight_IS = (UImgMediaSource*)tempVar_holeFromRight_IS.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_holeFromUp_IS(TEXT("'/Game/Movies/imageSources/holeFromUp_IS.holeFromUp_IS'"));
	if (tempVar_holeFromUp_IS.Object != NULL)
	{
		holeFromUp_IS = (UImgMediaSource*)tempVar_holeFromUp_IS.Object;
	}

	//flags
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_flag_VMUI_1(TEXT("'/Game/Movies/videoMaterialsForUI/flag_VMUI_1.flag_VMUI_1'"));
	if (tempVar_flag_VMUI_1.Object != NULL)
	{
		flag_VMUI_1 = (UMaterial*)tempVar_flag_VMUI_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_flag_MP_1(TEXT("'/Game/Movies/mediaPlayers/flag_MP_1.flag_MP_1'"));
	if (tempVar_flag_MP_1.Object != NULL)
	{
		flag_MP_1 = (UMediaPlayer*)tempVar_flag_MP_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_flag_IS_1(TEXT("'/Game/Movies/imageSources/flag_IS_1.flag_IS_1'"));
	if (tempVar_flag_IS_1.Object != NULL)
	{
		flag_IS_1 = (UImgMediaSource*)tempVar_flag_IS_1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_flag_VMUI_2(TEXT("'/Game/Movies/videoMaterialsForUI/flag_VMUI_2.flag_VMUI_2'"));
	if (tempVar_flag_VMUI_2.Object != NULL)
	{
		flag_VMUI_2 = (UMaterial*)tempVar_flag_VMUI_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_flag_MP_2(TEXT("'/Game/Movies/mediaPlayers/flag_MP_2.flag_MP_2'"));
	if (tempVar_flag_MP_2.Object != NULL)
	{
		flag_MP_2 = (UMediaPlayer*)tempVar_flag_MP_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_flag_IS_2(TEXT("'/Game/Movies/imageSources/flag_IS_2.flag_IS_2'"));
	if (tempVar_flag_IS_2.Object != NULL)
	{
		flag_IS_2 = (UImgMediaSource*)tempVar_flag_IS_2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_flag_VMUI_3(TEXT("'/Game/Movies/videoMaterialsForUI/flag_VMUI_3.flag_VMUI_3'"));
	if (tempVar_flag_VMUI_3.Object != NULL)
	{
		flag_VMUI_3 = (UMaterial*)tempVar_flag_VMUI_3.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_flag_MP_3(TEXT("'/Game/Movies/mediaPlayers/flag_MP_3.flag_MP_3'"));
	if (tempVar_flag_MP_3.Object != NULL)
	{
		flag_MP_3 = (UMediaPlayer*)tempVar_flag_MP_3.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_flag_IS_3(TEXT("'/Game/Movies/imageSources/flag_IS_3.flag_IS_3'"));
	if (tempVar_flag_IS_3.Object != NULL)
	{
		flag_IS_3 = (UImgMediaSource*)tempVar_flag_IS_3.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_flag_VMUI_4(TEXT("'/Game/Movies/videoMaterialsForUI/flag_VMUI_4.flag_VMUI_4'"));
	if (tempVar_flag_VMUI_4.Object != NULL)
	{
		flag_VMUI_4 = (UMaterial*)tempVar_flag_VMUI_4.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_flag_MP_4(TEXT("'/Game/Movies/mediaPlayers/flag_MP_4.flag_MP_4'"));
	if (tempVar_flag_MP_4.Object != NULL)
	{
		flag_MP_4 = (UMediaPlayer*)tempVar_flag_MP_4.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_flag_IS_4(TEXT("'/Game/Movies/imageSources/flag_IS_4.flag_IS_4'"));
	if (tempVar_flag_IS_4.Object != NULL)
	{
		flag_IS_4 = (UImgMediaSource*)tempVar_flag_IS_4.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_flag_VMUI_5(TEXT("'/Game/Movies/videoMaterialsForUI/flag_VMUI_5.flag_VMUI_5'"));
	if (tempVar_flag_VMUI_5.Object != NULL)
	{
		flag_VMUI_5 = (UMaterial*)tempVar_flag_VMUI_5.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_flag_MP_5(TEXT("'/Game/Movies/mediaPlayers/flag_MP_5.flag_MP_5'"));
	if (tempVar_flag_MP_5.Object != NULL)
	{
		flag_MP_5 = (UMediaPlayer*)tempVar_flag_MP_5.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_flag_IS_5(TEXT("'/Game/Movies/imageSources/flag_IS_5.flag_IS_5'"));
	if (tempVar_flag_IS_5.Object != NULL)
	{
		flag_IS_5 = (UImgMediaSource*)tempVar_flag_IS_5.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_flag_VMUI_6(TEXT("'/Game/Movies/videoMaterialsForUI/flag_VMUI_6.flag_VMUI_6'"));
	if (tempVar_flag_VMUI_6.Object != NULL)
	{
		flag_VMUI_6 = (UMaterial*)tempVar_flag_VMUI_6.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_flag_MP_6(TEXT("'/Game/Movies/mediaPlayers/flag_MP_6.flag_MP_6'"));
	if (tempVar_flag_MP_6.Object != NULL)
	{
		flag_MP_6 = (UMediaPlayer*)tempVar_flag_MP_6.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_flag_IS_6(TEXT("'/Game/Movies/imageSources/flag_IS_6.flag_IS_6'"));
	if (tempVar_flag_IS_6.Object != NULL)
	{
		flag_IS_6 = (UImgMediaSource*)tempVar_flag_IS_6.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_flag_VMUI_7(TEXT("'/Game/Movies/videoMaterialsForUI/flag_VMUI_7.flag_VMUI_7'"));
	if (tempVar_flag_VMUI_7.Object != NULL)
	{
		flag_VMUI_7 = (UMaterial*)tempVar_flag_VMUI_7.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_flag_MP_7(TEXT("'/Game/Movies/mediaPlayers/flag_MP_7.flag_MP_7'"));
	if (tempVar_flag_MP_7.Object != NULL)
	{
		flag_MP_7 = (UMediaPlayer*)tempVar_flag_MP_7.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_flag_IS_7(TEXT("'/Game/Movies/imageSources/flag_IS_7.flag_IS_7'"));
	if (tempVar_flag_IS_7.Object != NULL)
	{
		flag_IS_7 = (UImgMediaSource*)tempVar_flag_IS_7.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_flag_VMUI_8(TEXT("'/Game/Movies/videoMaterialsForUI/flag_VMUI_8.flag_VMUI_8'"));
	if (tempVar_flag_VMUI_8.Object != NULL)
	{
		flag_VMUI_8 = (UMaterial*)tempVar_flag_VMUI_8.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_flag_MP_8(TEXT("'/Game/Movies/mediaPlayers/flag_MP_8.flag_MP_8'"));
	if (tempVar_flag_MP_8.Object != NULL)
	{
		flag_MP_8 = (UMediaPlayer*)tempVar_flag_MP_8.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_flag_IS_8(TEXT("'/Game/Movies/imageSources/flag_IS_8.flag_IS_8'"));
	if (tempVar_flag_IS_8.Object != NULL)
	{
		flag_IS_8 = (UImgMediaSource*)tempVar_flag_IS_8.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_flag_VMUI_9(TEXT("'/Game/Movies/videoMaterialsForUI/flag_VMUI_9.flag_VMUI_9'"));
	if (tempVar_flag_VMUI_9.Object != NULL)
	{
		flag_VMUI_9 = (UMaterial*)tempVar_flag_VMUI_9.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_flag_MP_9(TEXT("'/Game/Movies/mediaPlayers/flag_MP_9.flag_MP_9'"));
	if (tempVar_flag_MP_9.Object != NULL)
	{
		flag_MP_9 = (UMediaPlayer*)tempVar_flag_MP_9.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_flag_IS_9(TEXT("'/Game/Movies/imageSources/flag_IS_9.flag_IS_9'"));
	if (tempVar_flag_IS_9.Object != NULL)
	{
		flag_IS_9 = (UImgMediaSource*)tempVar_flag_IS_9.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_flag_VMUI_10(TEXT("'/Game/Movies/videoMaterialsForUI/flag_VMUI_10.flag_VMUI_10'"));
	if (tempVar_flag_VMUI_10.Object != NULL)
	{
		flag_VMUI_10 = (UMaterial*)tempVar_flag_VMUI_10.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_flag_MP_10(TEXT("'/Game/Movies/mediaPlayers/flag_MP_10.flag_MP_10'"));
	if (tempVar_flag_MP_10.Object != NULL)
	{
		flag_MP_10 = (UMediaPlayer*)tempVar_flag_MP_10.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_flag_IS_10(TEXT("'/Game/Movies/imageSources/flag_IS_10.flag_IS_10'"));
	if (tempVar_flag_IS_10.Object != NULL)
	{
		flag_IS_10 = (UImgMediaSource*)tempVar_flag_IS_10.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_flag_VMUI_11(TEXT("'/Game/Movies/videoMaterialsForUI/flag_VMUI_11.flag_VMUI_11'"));
	if (tempVar_flag_VMUI_11.Object != NULL)
	{
		flag_VMUI_11 = (UMaterial*)tempVar_flag_VMUI_11.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_flag_MP_11(TEXT("'/Game/Movies/mediaPlayers/flag_MP_11.flag_MP_11'"));
	if (tempVar_flag_MP_11.Object != NULL)
	{
		flag_MP_11 = (UMediaPlayer*)tempVar_flag_MP_11.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_flag_IS_11(TEXT("'/Game/Movies/imageSources/flag_IS_11.flag_IS_11'"));
	if (tempVar_flag_IS_11.Object != NULL)
	{
		flag_IS_11 = (UImgMediaSource*)tempVar_flag_IS_11.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_flag_VMUI_12(TEXT("'/Game/Movies/videoMaterialsForUI/flag_VMUI_12.flag_VMUI_12'"));
	if (tempVar_flag_VMUI_12.Object != NULL)
	{
		flag_VMUI_12 = (UMaterial*)tempVar_flag_VMUI_12.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_flag_MP_12(TEXT("'/Game/Movies/mediaPlayers/flag_MP_12.flag_MP_12'"));
	if (tempVar_flag_MP_12.Object != NULL)
	{
		flag_MP_12 = (UMediaPlayer*)tempVar_flag_MP_12.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_flag_IS_12(TEXT("'/Game/Movies/imageSources/flag_IS_12.flag_IS_12'"));
	if (tempVar_flag_IS_12.Object != NULL)
	{
		flag_IS_12 = (UImgMediaSource*)tempVar_flag_IS_12.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_flag_VMUI_13(TEXT("'/Game/Movies/videoMaterialsForUI/flag_VMUI_13.flag_VMUI_13'"));
	if (tempVar_flag_VMUI_13.Object != NULL)
	{
		flag_VMUI_13 = (UMaterial*)tempVar_flag_VMUI_13.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_flag_MP_13(TEXT("'/Game/Movies/mediaPlayers/flag_MP_13.flag_MP_13'"));
	if (tempVar_flag_MP_13.Object != NULL)
	{
		flag_MP_13 = (UMediaPlayer*)tempVar_flag_MP_13.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_flag_IS_13(TEXT("'/Game/Movies/imageSources/flag_IS_13.flag_IS_13'"));
	if (tempVar_flag_IS_13.Object != NULL)
	{
		flag_IS_13 = (UImgMediaSource*)tempVar_flag_IS_13.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_flag_VMUI_14(TEXT("'/Game/Movies/videoMaterialsForUI/flag_VMUI_14.flag_VMUI_14'"));
	if (tempVar_flag_VMUI_14.Object != NULL)
	{
		flag_VMUI_14 = (UMaterial*)tempVar_flag_VMUI_14.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_flag_MP_14(TEXT("'/Game/Movies/mediaPlayers/flag_MP_14.flag_MP_14'"));
	if (tempVar_flag_MP_14.Object != NULL)
	{
		flag_MP_14 = (UMediaPlayer*)tempVar_flag_MP_14.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_flag_IS_14(TEXT("'/Game/Movies/imageSources/flag_IS_14.flag_IS_14'"));
	if (tempVar_flag_IS_14.Object != NULL)
	{
		flag_IS_14 = (UImgMediaSource*)tempVar_flag_IS_14.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_flag_VMUI_15(TEXT("'/Game/Movies/videoMaterialsForUI/flag_VMUI_15.flag_VMUI_15'"));
	if (tempVar_flag_VMUI_15.Object != NULL)
	{
		flag_VMUI_15 = (UMaterial*)tempVar_flag_VMUI_15.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_flag_MP_15(TEXT("'/Game/Movies/mediaPlayers/flag_MP_15.flag_MP_15'"));
	if (tempVar_flag_MP_15.Object != NULL)
	{
		flag_MP_15 = (UMediaPlayer*)tempVar_flag_MP_15.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_flag_IS_15(TEXT("'/Game/Movies/imageSources/flag_IS_15.flag_IS_15'"));
	if (tempVar_flag_IS_15.Object != NULL)
	{
		flag_IS_15 = (UImgMediaSource*)tempVar_flag_IS_15.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_flag_VMUI_16(TEXT("'/Game/Movies/videoMaterialsForUI/flag_VMUI_16.flag_VMUI_16'"));
	if (tempVar_flag_VMUI_16.Object != NULL)
	{
		flag_VMUI_16 = (UMaterial*)tempVar_flag_VMUI_16.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_flag_MP_16(TEXT("'/Game/Movies/mediaPlayers/flag_MP_16.flag_MP_16'"));
	if (tempVar_flag_MP_16.Object != NULL)
	{
		flag_MP_16 = (UMediaPlayer*)tempVar_flag_MP_16.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_flag_IS_16(TEXT("'/Game/Movies/imageSources/flag_IS_16.flag_IS_16'"));
	if (tempVar_flag_IS_16.Object != NULL)
	{
		flag_IS_16 = (UImgMediaSource*)tempVar_flag_IS_16.Object;
	}

	//curtains
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_curtains_VMUI(TEXT("'/Game/Movies/videoMaterialsForUI/curtains_VMUI.curtains_VMUI'"));
	if (tempVar_curtains_VMUI.Object != NULL)
	{
		curtains_VMUI = (UMaterial*)tempVar_curtains_VMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_curtains_MP(TEXT("'/Game/Movies/mediaPlayers/curtains_MP.curtains_MP'"));
	if (tempVar_curtains_MP.Object != NULL)
	{
		curtains_MP = (UMediaPlayer*)tempVar_curtains_MP.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_curtains_IS(TEXT("'/Game/Movies/imageSources/curtains_IS.curtains_IS'"));
	if (tempVar_curtains_IS.Object != NULL)
	{
		curtains_IS = (UImgMediaSource*)tempVar_curtains_IS.Object;
	}

	//buttons or "intersections"
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromDownTurningRightZero_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromDown/one/buttonFromDownOneStraightStatic_SMUI.buttonFromDownOneStraightStatic_SMUI'"));
	if (tempVar_buttonFromDownTurningRightZero_SMUI.Object != NULL)
	{
		buttonFromDownTurningRightZero_SMUI = (UMaterial*)tempVar_buttonFromDownTurningRightZero_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromDownTurningRightOne_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromDown/one/buttonFromDownOneStraightClicked_SMUI.buttonFromDownOneStraightClicked_SMUI'"));
	if (tempVar_buttonFromDownTurningRightOne_SMUI.Object != NULL)
	{
		buttonFromDownTurningRightOne_SMUI = (UMaterial*)tempVar_buttonFromDownTurningRightOne_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromDownTurningRightTwo_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromDown/one/buttonFromDownOneTurningStatic_SMUI.buttonFromDownOneTurningStatic_SMUI'"));
	if (tempVar_buttonFromDownTurningRightTwo_SMUI.Object != NULL)
	{
		buttonFromDownTurningRightTwo_SMUI = (UMaterial*)tempVar_buttonFromDownTurningRightTwo_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromDownTurningRightThree_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromDown/one/buttonFromDownOneTurningClicked_SMUI.buttonFromDownOneTurningClicked_SMUI'"));
	if (tempVar_buttonFromDownTurningRightThree_SMUI.Object != NULL)
	{
		buttonFromDownTurningRightThree_SMUI = (UMaterial*)tempVar_buttonFromDownTurningRightThree_SMUI.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromDownTurningLeftZero_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromDown/zero/buttonFromDownZeroStraightStatic_SMUI.buttonFromDownZeroStraightStatic_SMUI'"));
	if (tempVar_buttonFromDownTurningLeftZero_SMUI.Object != NULL)
	{
		buttonFromDownTurningLeftZero_SMUI = (UMaterial*)tempVar_buttonFromDownTurningLeftZero_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromDownTurningLeftOne_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromDown/zero/buttonFromDownZeroStraightClicked_SMUI.buttonFromDownZeroStraightClicked_SMUI'"));
	if (tempVar_buttonFromDownTurningLeftOne_SMUI.Object != NULL)
	{
		buttonFromDownTurningLeftOne_SMUI = (UMaterial*)tempVar_buttonFromDownTurningLeftOne_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromDownTurningLeftTwo_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromDown/zero/buttonFromDownZeroTurningStatic_SMUI.buttonFromDownZeroTurningStatic_SMUI'"));
	if (tempVar_buttonFromDownTurningLeftTwo_SMUI.Object != NULL)
	{
		buttonFromDownTurningLeftTwo_SMUI = (UMaterial*)tempVar_buttonFromDownTurningLeftTwo_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromDownTurningLeftThree_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromDown/zero/buttonFromDownZeroTurningClicked_SMUI.buttonFromDownZeroTurningClicked_SMUI'"));
	if (tempVar_buttonFromDownTurningLeftThree_SMUI.Object != NULL)
	{
		buttonFromDownTurningLeftThree_SMUI = (UMaterial*)tempVar_buttonFromDownTurningLeftThree_SMUI.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromLeftTurningRightZero_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromLeft/one/buttonFromLeftOneStraightStatic_SMUI.buttonFromLeftOneStraightStatic_SMUI'"));
	if (tempVar_buttonFromLeftTurningRightZero_SMUI.Object != NULL)
	{
		buttonFromLeftTurningRightZero_SMUI = (UMaterial*)tempVar_buttonFromLeftTurningRightZero_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromLeftTurningRightOne_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromLeft/one/buttonFromLeftOneStraightClicked_SMUI.buttonFromLeftOneStraightClicked_SMUI'"));
	if (tempVar_buttonFromLeftTurningRightOne_SMUI.Object != NULL)
	{
		buttonFromLeftTurningRightOne_SMUI = (UMaterial*)tempVar_buttonFromLeftTurningRightOne_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromLeftTurningRightTwo_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromLeft/one/buttonFromLeftOneTurningStatic_SMUI.buttonFromLeftOneTurningStatic_SMUI'"));
	if (tempVar_buttonFromLeftTurningRightTwo_SMUI.Object != NULL)
	{
		buttonFromLeftTurningRightTwo_SMUI = (UMaterial*)tempVar_buttonFromLeftTurningRightTwo_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromLeftTurningRightThree_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromLeft/one/buttonFromLeftOneTurningClicked_SMUI.buttonFromLeftOneTurningClicked_SMUI'"));
	if (tempVar_buttonFromLeftTurningRightThree_SMUI.Object != NULL)
	{
		buttonFromLeftTurningRightThree_SMUI = (UMaterial*)tempVar_buttonFromLeftTurningRightThree_SMUI.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromLeftTurningLeftZero_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromLeft/zero/buttonFromLeftZeroStraightStatic_SMUI.buttonFromLeftZeroStraightStatic_SMUI'"));
	if (tempVar_buttonFromLeftTurningLeftZero_SMUI.Object != NULL)
	{
		buttonFromLeftTurningLeftZero_SMUI = (UMaterial*)tempVar_buttonFromLeftTurningLeftZero_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromLeftTurningLeftOne_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromLeft/zero/buttonFromLeftZeroStraightClicked_SMUI.buttonFromLeftZeroStraightClicked_SMUI'"));
	if (tempVar_buttonFromLeftTurningLeftOne_SMUI.Object != NULL)
	{
		buttonFromLeftTurningLeftOne_SMUI = (UMaterial*)tempVar_buttonFromLeftTurningLeftOne_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromLeftTurningLeftTwo_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromLeft/zero/buttonFromLeftZeroTurningStatic_SMUI.buttonFromLeftZeroTurningStatic_SMUI'"));
	if (tempVar_buttonFromLeftTurningLeftTwo_SMUI.Object != NULL)
	{
		buttonFromLeftTurningLeftTwo_SMUI = (UMaterial*)tempVar_buttonFromLeftTurningLeftTwo_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromLeftTurningLeftThree_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromLeft/zero/buttonFromLeftZeroTurningClicked_SMUI.buttonFromLeftZeroTurningClicked_SMUI'"));
	if (tempVar_buttonFromLeftTurningLeftThree_SMUI.Object != NULL)
	{
		buttonFromLeftTurningLeftThree_SMUI = (UMaterial*)tempVar_buttonFromLeftTurningLeftThree_SMUI.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromRightTurningRightZero_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromRight/one/buttonFromRightOneStraightStatic_SMUI.buttonFromRightOneStraightStatic_SMUI'"));
	if (tempVar_buttonFromRightTurningRightZero_SMUI.Object != NULL)
	{
		buttonFromRightTurningRightZero_SMUI = (UMaterial*)tempVar_buttonFromRightTurningRightZero_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromRightTurningRightOne_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromRight/one/buttonFromRightOneStraightClicked_SMUI.buttonFromRightOneStraightClicked_SMUI'"));
	if (tempVar_buttonFromRightTurningRightOne_SMUI.Object != NULL)
	{
		buttonFromRightTurningRightOne_SMUI = (UMaterial*)tempVar_buttonFromRightTurningRightOne_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromRightTurningRightTwo_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromRight/one/buttonFromRightOneTurningStatic_SMUI.buttonFromRightOneTurningStatic_SMUI'"));
	if (tempVar_buttonFromRightTurningRightTwo_SMUI.Object != NULL)
	{
		buttonFromRightTurningRightTwo_SMUI = (UMaterial*)tempVar_buttonFromRightTurningRightTwo_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromRightTurningRightThree_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromRight/one/buttonFromRightOneTurningClicked_SMUI.buttonFromRightOneTurningClicked_SMUI'"));
	if (tempVar_buttonFromRightTurningRightThree_SMUI.Object != NULL)
	{
		buttonFromRightTurningRightThree_SMUI = (UMaterial*)tempVar_buttonFromRightTurningRightThree_SMUI.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromRightTurningLeftZero_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromRight/zero/buttonFromRightZeroStraightStatic_SMUI.buttonFromRightZeroStraightStatic_SMUI'"));
	if (tempVar_buttonFromRightTurningLeftZero_SMUI.Object != NULL)
	{
		buttonFromRightTurningLeftZero_SMUI = (UMaterial*)tempVar_buttonFromRightTurningLeftZero_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromRightTurningLeftOne_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromRight/zero/buttonFromRightZeroStraightClicked_SMUI.buttonFromRightZeroStraightClicked_SMUI'"));
	if (tempVar_buttonFromRightTurningLeftOne_SMUI.Object != NULL)
	{
		buttonFromRightTurningLeftOne_SMUI = (UMaterial*)tempVar_buttonFromRightTurningLeftOne_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromRightTurningLeftTwo_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromRight/zero/buttonFromRightZeroTurningStatic_SMUI.buttonFromRightZeroTurningStatic_SMUI'"));
	if (tempVar_buttonFromRightTurningLeftTwo_SMUI.Object != NULL)
	{
		buttonFromRightTurningLeftTwo_SMUI = (UMaterial*)tempVar_buttonFromRightTurningLeftTwo_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromRightTurningLeftThree_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/fromRight/zero/buttonFromRightZeroTurningClicked_SMUI.buttonFromRightZeroTurningClicked_SMUI'"));
	if (tempVar_buttonFromRightTurningLeftThree_SMUI.Object != NULL)
	{
		buttonFromRightTurningLeftThree_SMUI = (UMaterial*)tempVar_buttonFromRightTurningLeftThree_SMUI.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromUpTurningRightZero_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/FromUp/one/buttonFromUpOneStraightStatic_SMUI.buttonFromUpOneStraightStatic_SMUI'"));
	if (tempVar_buttonFromUpTurningRightZero_SMUI.Object != NULL)
	{
		buttonFromUpTurningRightZero_SMUI = (UMaterial*)tempVar_buttonFromUpTurningRightZero_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromUpTurningRightOne_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/FromUp/one/buttonFromUpOneStraightClicked_SMUI.buttonFromUpOneStraightClicked_SMUI'"));
	if (tempVar_buttonFromUpTurningRightOne_SMUI.Object != NULL)
	{
		buttonFromUpTurningRightOne_SMUI = (UMaterial*)tempVar_buttonFromUpTurningRightOne_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromUpTurningRightTwo_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/FromUp/one/buttonFromUpOneTurningStatic_SMUI.buttonFromUpOneTurningStatic_SMUI'"));
	if (tempVar_buttonFromUpTurningRightTwo_SMUI.Object != NULL)
	{
		buttonFromUpTurningRightTwo_SMUI = (UMaterial*)tempVar_buttonFromUpTurningRightTwo_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromUpTurningRightThree_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/FromUp/one/buttonFromUpOneTurningClicked_SMUI.buttonFromUpOneTurningClicked_SMUI'"));
	if (tempVar_buttonFromUpTurningRightThree_SMUI.Object != NULL)
	{
		buttonFromUpTurningRightThree_SMUI = (UMaterial*)tempVar_buttonFromUpTurningRightThree_SMUI.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromUpTurningLeftZero_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/FromUp/zero/buttonFromUpZeroStraightStatic_SMUI.buttonFromUpZeroStraightStatic_SMUI'"));
	if (tempVar_buttonFromUpTurningLeftZero_SMUI.Object != NULL)
	{
		buttonFromUpTurningLeftZero_SMUI = (UMaterial*)tempVar_buttonFromUpTurningLeftZero_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromUpTurningLeftOne_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/FromUp/zero/buttonFromUpZeroStraightClicked_SMUI.buttonFromUpZeroStraightClicked_SMUI'"));
	if (tempVar_buttonFromUpTurningLeftOne_SMUI.Object != NULL)
	{
		buttonFromUpTurningLeftOne_SMUI = (UMaterial*)tempVar_buttonFromUpTurningLeftOne_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromUpTurningLeftTwo_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/FromUp/zero/buttonFromUpZeroTurningStatic_SMUI.buttonFromUpZeroTurningStatic_SMUI'"));
	if (tempVar_buttonFromUpTurningLeftTwo_SMUI.Object != NULL)
	{
		buttonFromUpTurningLeftTwo_SMUI = (UMaterial*)tempVar_buttonFromUpTurningLeftTwo_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_buttonFromUpTurningLeftThree_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/buttons/FromUp/zero/buttonFromUpZeroTurningClicked_SMUI.buttonFromUpZeroTurningClicked_SMUI'"));
	if (tempVar_buttonFromUpTurningLeftThree_SMUI.Object != NULL)
	{
		buttonFromUpTurningLeftThree_SMUI = (UMaterial*)tempVar_buttonFromUpTurningLeftThree_SMUI.Object;
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
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_marble_SMUI_8(TEXT("'/Game/Movies/spriteMaterialsForUI/marble_SMUI_8.marble_SMUI_8'"));
	if (tempVar_marble_SMUI_8.Object != NULL)
	{
		marble_SMUI_8 = (UMaterial*)tempVar_marble_SMUI_8.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_marble_SMUI_9(TEXT("'/Game/Movies/spriteMaterialsForUI/marble_SMUI_9.marble_SMUI_9'"));
	if (tempVar_marble_SMUI_9.Object != NULL)
	{
		marble_SMUI_9 = (UMaterial*)tempVar_marble_SMUI_9.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_marble_SMUI_10(TEXT("'/Game/Movies/spriteMaterialsForUI/marble_SMUI_10.marble_SMUI_10'"));
	if (tempVar_marble_SMUI_10.Object != NULL)
	{
		marble_SMUI_10 = (UMaterial*)tempVar_marble_SMUI_10.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_marble_SMUI_11(TEXT("'/Game/Movies/spriteMaterialsForUI/marble_SMUI_11.marble_SMUI_11'"));
	if (tempVar_marble_SMUI_11.Object != NULL)
	{
		marble_SMUI_11 = (UMaterial*)tempVar_marble_SMUI_11.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_marble_SMUI_12(TEXT("'/Game/Movies/spriteMaterialsForUI/marble_SMUI_12.marble_SMUI_12'"));
	if (tempVar_marble_SMUI_12.Object != NULL)
	{
		marble_SMUI_12 = (UMaterial*)tempVar_marble_SMUI_12.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_marble_SMUI_13(TEXT("'/Game/Movies/spriteMaterialsForUI/marble_SMUI_13.marble_SMUI_13'"));
	if (tempVar_marble_SMUI_13.Object != NULL)
	{
		marble_SMUI_13 = (UMaterial*)tempVar_marble_SMUI_13.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_marble_SMUI_14(TEXT("'/Game/Movies/spriteMaterialsForUI/marble_SMUI_14.marble_SMUI_14'"));
	if (tempVar_marble_SMUI_14.Object != NULL)
	{
		marble_SMUI_14 = (UMaterial*)tempVar_marble_SMUI_14.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_marble_SMUI_15(TEXT("'/Game/Movies/spriteMaterialsForUI/marble_SMUI_15.marble_SMUI_15'"));
	if (tempVar_marble_SMUI_15.Object != NULL)
	{
		marble_SMUI_15 = (UMaterial*)tempVar_marble_SMUI_15.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_marble_SMUI_16(TEXT("'/Game/Movies/spriteMaterialsForUI/marble_SMUI_16.marble_SMUI_16'"));
	if (tempVar_marble_SMUI_16.Object != NULL)
	{
		marble_SMUI_16 = (UMaterial*)tempVar_marble_SMUI_16.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_gameFrameColor_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/gameFrameColor_SMUI.gameFrameColor_SMUI'"));
	if (tempVar_gameFrameColor_SMUI.Object != NULL)
	{
		gameFrameColor_SMUI = (UMaterial*)tempVar_gameFrameColor_SMUI.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_bootAni_SMUI_1(TEXT("'/Game/Movies/spriteMaterialsForUI/bootAni_SMUI_1.bootAni_SMUI_1'"));
	if (tempVar_bootAni_SMUI_1.Object != NULL)
	{
		splashBootArr.Add((UMaterial*)tempVar_bootAni_SMUI_1.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_bootAni_SMUI_2(TEXT("'/Game/Movies/spriteMaterialsForUI/bootAni_SMUI_2.bootAni_SMUI_2'"));
	if (tempVar_bootAni_SMUI_2.Object != NULL)
	{
		splashBootArr.Add((UMaterial*)tempVar_bootAni_SMUI_2.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_bootAni_SMUI_3(TEXT("'/Game/Movies/spriteMaterialsForUI/bootAni_SMUI_3.bootAni_SMUI_3'"));
	if (tempVar_bootAni_SMUI_3.Object != NULL)
	{
		splashBootArr.Add((UMaterial*)tempVar_bootAni_SMUI_3.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_bootAni_SMUI_4(TEXT("'/Game/Movies/spriteMaterialsForUI/bootAni_SMUI_4.bootAni_SMUI_4'"));
	if (tempVar_bootAni_SMUI_4.Object != NULL)
	{
		splashBootArr.Add((UMaterial*)tempVar_bootAni_SMUI_4.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_goodUseSplashBoot_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashBoot_SMUI.goodUseSplashBoot_SMUI'"));
	if (tempVar_goodUseSplashBoot_SMUI.Object != NULL)
	{
		splashBootArr.Add((UMaterial*)tempVar_goodUseSplashBoot_SMUI.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_goodUseSplashBootNoGrass_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashBootNoGrass_SMUI.goodUseSplashBootNoGrass_SMUI'"));
	if (tempVar_goodUseSplashBootNoGrass_SMUI.Object != NULL)
	{
		goodUseSplashBootNoGrass_SMUI = (UMaterial*)tempVar_goodUseSplashBootNoGrass_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_goodUseSplashGrass_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashGrass_SMUI.goodUseSplashGrass_SMUI'"));
	if (tempVar_goodUseSplashGrass_SMUI.Object != NULL)
	{
		goodUseSplashGrass_SMUI = (UMaterial*)tempVar_goodUseSplashGrass_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_goodUseDigitalText_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseDigitalText_SMUI.goodUseDigitalText_SMUI'"));
	if (tempVar_goodUseDigitalText_SMUI.Object != NULL)
	{
		goodUseDigitalText_SMUI = (UMaterial*)tempVar_goodUseDigitalText_SMUI.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_splashGrass_SMUI_1(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashGrass_SMUI_1.goodUseSplashGrass_SMUI_1'"));
	if (tempVar_splashGrass_SMUI_1.Object != NULL)
	{
		splashGrassArr.Add((UMaterial*)tempVar_splashGrass_SMUI_1.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_splashGrass_SMUI_2(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashGrass_SMUI_2.goodUseSplashGrass_SMUI_2'"));
	if (tempVar_splashGrass_SMUI_2.Object != NULL)
	{
		splashGrassArr.Add((UMaterial*)tempVar_splashGrass_SMUI_2.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_splashGrass_SMUI_3(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashGrass_SMUI_3.goodUseSplashGrass_SMUI_3'"));
	if (tempVar_splashGrass_SMUI_3.Object != NULL)
	{
		splashGrassArr.Add((UMaterial*)tempVar_splashGrass_SMUI_3.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_splashGrass_SMUI_4(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashGrass_SMUI_4.goodUseSplashGrass_SMUI_4'"));
	if (tempVar_splashGrass_SMUI_4.Object != NULL)
	{
		splashGrassArr.Add((UMaterial*)tempVar_splashGrass_SMUI_4.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_splashGrass_SMUI_5(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashGrass_SMUI_5.goodUseSplashGrass_SMUI_5'"));
	if (tempVar_splashGrass_SMUI_5.Object != NULL)
	{
		splashGrassArr.Add((UMaterial*)tempVar_splashGrass_SMUI_5.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_splashGrass_SMUI_6(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashGrass_SMUI_6.goodUseSplashGrass_SMUI_6'"));
	if (tempVar_splashGrass_SMUI_6.Object != NULL)
	{
		splashGrassArr.Add((UMaterial*)tempVar_splashGrass_SMUI_6.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_splashGrass_SMUI_7(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashGrass_SMUI_7.goodUseSplashGrass_SMUI_7'"));
	if (tempVar_splashGrass_SMUI_7.Object != NULL)
	{
		splashGrassArr.Add((UMaterial*)tempVar_splashGrass_SMUI_7.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_splashGrass_SMUI_8(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashGrass_SMUI_8.goodUseSplashGrass_SMUI_8'"));
	if (tempVar_splashGrass_SMUI_8.Object != NULL)
	{
		splashGrassArr.Add((UMaterial*)tempVar_splashGrass_SMUI_8.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_splashGrass_SMUI_9(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashGrass_SMUI_9.goodUseSplashGrass_SMUI_9'"));
	if (tempVar_splashGrass_SMUI_9.Object != NULL)
	{
		splashGrassArr.Add((UMaterial*)tempVar_splashGrass_SMUI_9.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_splashGrass_SMUI_10(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashGrass_SMUI_10.goodUseSplashGrass_SMUI_10'"));
	if (tempVar_splashGrass_SMUI_10.Object != NULL)
	{
		splashGrassArr.Add((UMaterial*)tempVar_splashGrass_SMUI_10.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_splashGrass_SMUI_11(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashGrass_SMUI_11.goodUseSplashGrass_SMUI_11'"));
	if (tempVar_splashGrass_SMUI_11.Object != NULL)
	{
		splashGrassArr.Add((UMaterial*)tempVar_splashGrass_SMUI_11.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_splashGrass_SMUI_12(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashGrass_SMUI_12.goodUseSplashGrass_SMUI_12'"));
	if (tempVar_splashGrass_SMUI_12.Object != NULL)
	{
		splashGrassArr.Add((UMaterial*)tempVar_splashGrass_SMUI_12.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_splashGrass_SMUI_13(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashGrass_SMUI_13.goodUseSplashGrass_SMUI_13'"));
	if (tempVar_splashGrass_SMUI_13.Object != NULL)
	{
		splashGrassArr.Add((UMaterial*)tempVar_splashGrass_SMUI_13.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_splashGrass_SMUI_14(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashGrass_SMUI_14.goodUseSplashGrass_SMUI_14'"));
	if (tempVar_splashGrass_SMUI_14.Object != NULL)
	{
		splashGrassArr.Add((UMaterial*)tempVar_splashGrass_SMUI_14.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_splashGrass_SMUI_15(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashGrass_SMUI_15.goodUseSplashGrass_SMUI_15'"));
	if (tempVar_splashGrass_SMUI_15.Object != NULL)
	{
		splashGrassArr.Add((UMaterial*)tempVar_splashGrass_SMUI_15.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_splashGrass_SMUI_16(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashGrass_SMUI_16.goodUseSplashGrass_SMUI_16'"));
	if (tempVar_splashGrass_SMUI_16.Object != NULL)
	{
		splashGrassArr.Add((UMaterial*)tempVar_splashGrass_SMUI_16.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_splashGrass_SMUI_17(TEXT("'/Game/Movies/spriteMaterialsForUI/goodUseSplashGrass_SMUI.goodUseSplashGrass_SMUI'"));
	if (tempVar_splashGrass_SMUI_17.Object != NULL)
	{
		splashGrassArr.Add((UMaterial*)tempVar_splashGrass_SMUI_17.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_emptyImg_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/emptyImg_SMUI.emptyImg_SMUI'"));
	if (tempVar_emptyImg_SMUI.Object != NULL)
	{
		emptyImg_SMUI = (UMaterial*)tempVar_emptyImg_SMUI.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_black_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/black_SMUI.black_SMUI'"));
	if (tempVar_black_SMUI.Object != NULL)
	{
		black_SMUI = (UMaterial*)tempVar_black_SMUI.Object;
	}

	//now onto the sound effects, starting with intersection button sound effects. notice they do not impliment the isvalid conditional. will this be a problem?
	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_intersectionButtonPressed(TEXT("'/Game/myAdditionsArcade/soundEffects/intersectionDownClick.intersectionDownClick'"));
	intersectionButtonPressed = (USoundBase*)tempVar_intersectionButtonPressed.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_intersectionButtonReleased(TEXT("'/Game/myAdditionsArcade/soundEffects/intersectionUpClick.intersectionUpClick'"));
	intersectionButtonReleased = (USoundBase*)tempVar_intersectionButtonReleased.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrow.hoverGrow'"));
	hoverGrow = (USoundBase*)tempVar_hoverGrow.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrink.hoverShrink'"));
	hoverShrink = (USoundBase*)tempVar_hoverShrink.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_1(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowF3.hoverGrowF3'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_1.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_2(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowG3.hoverGrowG3'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_2.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_3(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowA3.hoverGrowA3'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_3.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_4(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowB3.hoverGrowB3'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_4.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_5(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowC4.hoverGrowC4'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_5.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_6(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowD4.hoverGrowD4'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_6.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_7(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowE4.hoverGrowE4'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_7.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_8(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowF4.hoverGrowF4'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_8.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_9(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowG4.hoverGrowG4'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_9.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_10(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowA4.hoverGrowA4'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_10.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_11(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowB4.hoverGrowB4'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_11.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_12(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowC5.hoverGrowC5'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_12.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_13(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowD5.hoverGrowD5'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_13.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_14(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowE5.hoverGrowE5'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_14.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_15(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowF5.hoverGrowF5'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_15.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_16(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowG5.hoverGrowG5'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_16.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_17(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowA5.hoverGrowA5'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_17.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_18(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowB5.hoverGrowB5'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_18.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_19(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowC6.hoverGrowC6'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_19.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_20(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowD6.hoverGrowD6'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_20.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_21(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowE6.hoverGrowE6'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_21.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_22(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowF6.hoverGrowF6'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_22.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverGrow_23(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverGrowA4flat.hoverGrowA4flat'"));
	hoverGrows.Add((USoundBase*)tempVar_hoverGrow_23.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_1(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkF3.hoverShrinkF3'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_1.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_2(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkG3.hoverShrinkG3'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_2.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_3(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkA3.hoverShrinkA3'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_3.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_4(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkB3.hoverShrinkB3'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_4.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_5(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkC4.hoverShrinkC4'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_5.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_6(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkD4.hoverShrinkD4'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_6.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_7(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkE4.hoverShrinkE4'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_7.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_8(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkF4.hoverShrinkF4'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_8.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_9(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkG4.hoverShrinkG4'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_9.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_10(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkA4.hoverShrinkA4'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_10.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_11(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkB4.hoverShrinkB4'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_11.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_12(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkC5.hoverShrinkC5'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_12.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_13(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkD5.hoverShrinkD5'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_13.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_14(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkE5.hoverShrinkE5'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_14.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_15(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkF5.hoverShrinkF5'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_15.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_16(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkG5.hoverShrinkG5'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_16.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_17(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkA5.hoverShrinkA5'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_17.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_18(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkB5.hoverShrinkB5'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_18.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_19(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkC6.hoverShrinkC6'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_19.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_20(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkD6.hoverShrinkD6'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_20.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_21(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkE6.hoverShrinkE6'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_21.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_22(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkF6.hoverShrinkF6'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_22.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_hoverShrink_23(TEXT("'/Game/myAdditionsArcade/soundEffects/hoverShrinkA4flat.hoverShrinkA4flat'"));
	hoverShrinks.Add((USoundBase*)tempVar_hoverShrink_23.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_curtainClosing(TEXT("'/Game/myAdditionsArcade/soundEffects/curtainsClosing.curtainsClosing'"));
	curtainClosing = (USoundBase*)tempVar_curtainClosing.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_curtainOpening(TEXT("'/Game/myAdditionsArcade/soundEffects/curtainsOpening.curtainsOpening'"));
	curtainOpening = (USoundBase*)tempVar_curtainOpening.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_rainstick(TEXT("'/Game/myAdditionsArcade/soundEffects/rainStick.rainStick'"));
	rainstick = (USoundBase*)tempVar_rainstick.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_wind(TEXT("'/Game/myAdditionsArcade/soundEffects/windOneAttemptTwo.windOneAttemptTwo'"));
	wind = (USoundBase*)tempVar_wind.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_windWithSheep(TEXT("'/Game/myAdditionsArcade/soundEffects/windWSheepAttemptTwo.windWSheepAttemptTwo'"));
	windWithSheep = (USoundBase*)tempVar_windWithSheep.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_river(TEXT("'/Game/myAdditionsArcade/soundEffects/river.river'"));
	river = (USoundBase*)tempVar_river.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_waterfall(TEXT("'/Game/myAdditionsArcade/soundEffects/waterfall.waterfall'"));
	waterfall = (USoundBase*)tempVar_waterfall.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_shovelingDirt(TEXT("'/Game/myAdditionsArcade/soundEffects/shovelingDirt.shovelingDirt'"));
	shovelingDirt = (USoundBase*)tempVar_shovelingDirt.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_miss(TEXT("'/Game/myAdditionsArcade/soundEffects/miss.miss'"));
	miss = (USoundBase*)tempVar_miss.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_scoring01(TEXT("'/Game/myAdditionsArcade/soundEffects/scoring01.scoring01'"));
	scoring.Add((USoundBase*)tempVar_scoring01.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_scoring02(TEXT("'/Game/myAdditionsArcade/soundEffects/scoring02.scoring02'"));
	scoring.Add((USoundBase*)tempVar_scoring02.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_scoring03(TEXT("'/Game/myAdditionsArcade/soundEffects/scoring03.scoring03'"));
	scoring.Add((USoundBase*)tempVar_scoring03.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_victory01(TEXT("'/Game/myAdditionsArcade/soundEffects/victory01.victory01'"));
	victory.Add((USoundBase*)tempVar_victory01.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_victory02(TEXT("'/Game/myAdditionsArcade/soundEffects/victory02.victory02'"));
	victory.Add((USoundBase*)tempVar_victory02.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_victory03(TEXT("'/Game/myAdditionsArcade/soundEffects/victory03.victory03'"));
	victory.Add((USoundBase*)tempVar_victory03.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_purpleLullaby_1(TEXT("'/Game/myAdditionsArcade/soundEffects/purpleLullabyC5.purpleLullabyC5'"));
	purpleLullaby.Add((USoundBase*)tempVar_purpleLullaby_1.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_purpleLullaby_2(TEXT("'/Game/myAdditionsArcade/soundEffects/purpleLullabyD5.purpleLullabyD5'"));
	purpleLullaby.Add((USoundBase*)tempVar_purpleLullaby_2.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_purpleLullaby_3(TEXT("'/Game/myAdditionsArcade/soundEffects/purpleLullabyE5.purpleLullabyE5'"));
	purpleLullaby.Add((USoundBase*)tempVar_purpleLullaby_3.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_purpleLullaby_4(TEXT("'/Game/myAdditionsArcade/soundEffects/purpleLullabyFSharp5.purpleLullabyFSharp5'"));
	purpleLullaby.Add((USoundBase*)tempVar_purpleLullaby_4.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_purpleLullaby_5(TEXT("'/Game/myAdditionsArcade/soundEffects/purpleLullabyG5.purpleLullabyG5'"));
	purpleLullaby.Add((USoundBase*)tempVar_purpleLullaby_5.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_purpleLullaby_6(TEXT("'/Game/myAdditionsArcade/soundEffects/purpleLullabyA5.purpleLullabyA5'"));
	purpleLullaby.Add((USoundBase*)tempVar_purpleLullaby_6.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_purpleLullaby_7(TEXT("'/Game/myAdditionsArcade/soundEffects/purpleLullabyB5.purpleLullabyB5'"));
	purpleLullaby.Add((USoundBase*)tempVar_purpleLullaby_7.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_purpleLullaby_8(TEXT("'/Game/myAdditionsArcade/soundEffects/purpleLullabyD6.purpleLullabyD6'"));
	purpleLullaby.Add((USoundBase*)tempVar_purpleLullaby_8.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_purpleLullaby_9(TEXT("'/Game/myAdditionsArcade/soundEffects/purpleLullabyC52.purpleLullabyC52'"));
	purpleLullabyTwo.Add((USoundBase*)tempVar_purpleLullaby_9.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_purpleLullaby_10(TEXT("'/Game/myAdditionsArcade/soundEffects/purpleLullabyD52.purpleLullabyD52'"));
	purpleLullabyTwo.Add((USoundBase*)tempVar_purpleLullaby_10.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_purpleLullaby_11(TEXT("'/Game/myAdditionsArcade/soundEffects/purpleLullabyE52.purpleLullabyE52'"));
	purpleLullabyTwo.Add((USoundBase*)tempVar_purpleLullaby_11.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_purpleLullaby_12(TEXT("'/Game/myAdditionsArcade/soundEffects/purpleLullabyFSharp52.purpleLullabyFSharp52'"));
	purpleLullabyTwo.Add((USoundBase*)tempVar_purpleLullaby_12.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_purpleLullaby_13(TEXT("'/Game/myAdditionsArcade/soundEffects/purpleLullabyG52.purpleLullabyG52'"));
	purpleLullabyTwo.Add((USoundBase*)tempVar_purpleLullaby_13.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_purpleLullaby_14(TEXT("'/Game/myAdditionsArcade/soundEffects/purpleLullabyA52.purpleLullabyA52'"));
	purpleLullabyTwo.Add((USoundBase*)tempVar_purpleLullaby_14.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_purpleLullaby_15(TEXT("'/Game/myAdditionsArcade/soundEffects/purpleLullabyB52.purpleLullabyB52'"));
	purpleLullabyTwo.Add((USoundBase*)tempVar_purpleLullaby_15.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_purpleLullaby_16(TEXT("'/Game/myAdditionsArcade/soundEffects/purpleLullabyD62.purpleLullabyD62'"));
	purpleLullabyTwo.Add((USoundBase*)tempVar_purpleLullaby_16.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_song_1(TEXT("'/Game/myAdditionsArcade/soundEffects/abundanceMixOne.abundanceMixOne'"));
	songs.Add((USoundBase*)tempVar_song_1.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_song_2(TEXT("'/Game/myAdditionsArcade/soundEffects/Alpha_Hydrae_-_Keratine__rust_and_a_clear_soul.Alpha_Hydrae_-_Keratine__rust_and_a_clear_soul'"));
	songs.Add((USoundBase*)tempVar_song_2.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_song_3(TEXT("'/Game/myAdditionsArcade/soundEffects/Kimiko_Ishizaka_-_Variatio_13_a_2_Clav_.Kimiko_Ishizaka_-_Variatio_13_a_2_Clav_'"));
	songs.Add((USoundBase*)tempVar_song_3.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_song_4(TEXT("'/Game/myAdditionsArcade/soundEffects/Kimiko_Ishizaka_-_Variatio_19_a_1_Clav_.Kimiko_Ishizaka_-_Variatio_19_a_1_Clav_'"));
	songs.Add((USoundBase*)tempVar_song_4.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_song_5(TEXT("'/Game/myAdditionsArcade/soundEffects/Kimiko_Ishizaka_-_Variatio_29_a_1_ovvero_2_Clav_.Kimiko_Ishizaka_-_Variatio_29_a_1_ovvero_2_Clav_'"));
	songs.Add((USoundBase*)tempVar_song_5.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_song_6(TEXT("'/Game/myAdditionsArcade/soundEffects/Josh_Woodward_-_Insomnia__No_Vocals_.Josh_Woodward_-_Insomnia__No_Vocals_'"));
	songs.Add((USoundBase*)tempVar_song_6.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_song_7(TEXT("'/Game/myAdditionsArcade/soundEffects/Kira_Daly_-_The_Bowsie_Sessions.Kira_Daly_-_The_Bowsie_Sessions'"));
	songs.Add((USoundBase*)tempVar_song_7.Object);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_song_8(TEXT("'/Game/myAdditionsArcade/soundEffects/Kira_Daly_-_The_Circle_-_GTV__Album__Lemonade_Lakes_.Kira_Daly_-_The_Circle_-_GTV__Album__Lemonade_Lakes_'"));
	songs.Add((USoundBase*)tempVar_song_8.Object);

	for (int a = 0; a < hoverGrows.Num(); a++)
	{
		hoverGrowAudioComponents.Add(CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass())));
		hoverGrowAudioComponents[a]->bAutoDestroy = false;
		hoverGrowAudioComponents[a]->SetSound(hoverGrows[a]);

		hoverShrinkAudioComponents.Add(CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass())));
		hoverShrinkAudioComponents[a]->bAutoDestroy = false;
		hoverShrinkAudioComponents[a]->SetSound(hoverShrinks[a]);
	}

	for (int a = 0; a < 2; a++)
	{
		windAudioComponents.Add(CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass())));
		windAudioComponents[a]->bAutoDestroy = false;
		windAudioComponents[a]->SetSound(wind);

		windWithSheepAudioComponents.Add(CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass())));
		windWithSheepAudioComponents[a]->bAutoDestroy = false;
		windWithSheepAudioComponents[a]->SetSound(windWithSheep);

		riverAudioComponents.Add(CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass())));
		riverAudioComponents[a]->bAutoDestroy = false;
		riverAudioComponents[a]->SetSound(river);

		waterfallAudioComponents.Add(CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass())));
		waterfallAudioComponents[a]->bAutoDestroy = false;
		waterfallAudioComponents[a]->SetSound(waterfall);
	}

	for (int a = 0; a < 8; a++)
	{
		purpleLullabyAudioComponents.Add(CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass())));
		purpleLullabyAudioComponents[a]->bAutoDestroy = false;
		purpleLullabyAudioComponents[a]->SetSound(purpleLullaby[a]);

		purpleLullabyTwoAudioComponents.Add(CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass())));
		purpleLullabyTwoAudioComponents[a]->bAutoDestroy = false;
		purpleLullabyTwoAudioComponents[a]->SetSound(purpleLullabyTwo[a]);
	}

	intersectionDownAudioComponent = CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass()));
	intersectionDownAudioComponent->bAutoDestroy = false;
	intersectionDownAudioComponent->SetSound(intersectionButtonPressed);

	intersectionUpAudioComponent = CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass()));
	intersectionUpAudioComponent->bAutoDestroy = false;
	intersectionUpAudioComponent->SetSound(intersectionButtonReleased);

	curtainClosingAudioComponent = CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass()));
	curtainClosingAudioComponent->bAutoDestroy = false;
	curtainClosingAudioComponent->SetSound(curtainClosing);

	curtainOpeningAudioComponent = CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass()));
	curtainOpeningAudioComponent->bAutoDestroy = false;
	curtainOpeningAudioComponent->SetSound(curtainOpening);

	rainstickAudioComponent = CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass()));
	rainstickAudioComponent->bAutoDestroy = false;
	rainstickAudioComponent->SetSound(rainstick);

	shovelingDirtAudioComponent = CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass()));
	shovelingDirtAudioComponent->bAutoDestroy = false;
	shovelingDirtAudioComponent->SetSound(shovelingDirt);

	missAudioComponent = CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass()));
	missAudioComponent->bAutoDestroy = false;
	missAudioComponent->SetSound(miss);

	for (int a = 0; a < 3; a++)
	{
		scoringAudioComponents.Add(CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass())));
		scoringAudioComponents[a]->bAutoDestroy = false;
		scoringAudioComponents[a]->SetSound(scoring[a]);

		victoryAudioComponents.Add(CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass())));
		victoryAudioComponents[a]->bAutoDestroy = false;
		victoryAudioComponents[a]->SetSound(victory[a]);
	}

	for (int a = 0; a < 8; a++)
	{
		songAudioComponents.Add(CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass())));
		songAudioComponents[a]->bAutoDestroy = false;
		songAudioComponents[a]->SetSound(songs[a]);
	}
}

void AMyHUD::PreLoadCurtains()
{
	curtains_MP->OpenSource(curtains_IS);
}

void AMyHUD::SaveGame(int maxLevel, TArray <int> highscores, int highscoreDataOne, int highscoreDataTwo, int scoreThisGame)
{
	USaveGameOne* saveFile = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));
	saveFile->SetMaxLevel(maxLevel);
	saveFile->SetHighscores(highscores);
	saveFile->SetHighscoreDataOne(highscoreDataOne);
	saveFile->SetHighscoreDataTwo(highscoreDataTwo);
	saveFile->SetScoreThisGame(scoreThisGame);
	UGameplayStatics::SaveGameToSlot(saveFile, TEXT("saveGameOne"), 0);
}

void AMyHUD::CommitKey(int keyToReplace, FKey newKey)
{
	USaveGameOne* saveFile = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));

	switch (keyToReplace)
	{
	case 0:
		saveFile->SetPauseKey(newKey);
		
		if (inGame)
		{
			gameSlateWidget->currentSave = saveFile;//theoretically this should not need to be done because current save is a pointer but there were some unexpected errors that warrant this
		}

		optionsMenuSlateWidget->currentSave = saveFile;
		break;
	case 1:
		saveFile->SetPauseMouse(newKey);

		if (inGame)
		{
			gameSlateWidget->currentSave = saveFile;
		}

		optionsMenuSlateWidget->currentSave = saveFile;
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

	UGameplayStatics::SaveGameToSlot(saveFile, TEXT("saveGameOne"), 0);
}

void AMyHUD::UpdateSongArr()
{
	USaveGameOne* saveFile = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));

	if (saveFile->GetSongIndexArr().Num() < 2)
	{
		newSongIndexArr.Empty();
		TArray<int> freshArr;

		for (int a = 0; a < 8; a++)
		{
			if (saveFile->GetSongCycles()[a] != 2)
			{
				freshArr.Add(a);
			}
		}

		int freshArrLength = freshArr.Num();//will this keep beig reset every loop? it really shouldnt
		for (int a = 0; a < freshArrLength; a++)
		{
			int songIndexIndex = FMath::RandRange(0, freshArr.Num() - 1);
			newSongIndexArr.Add(freshArr[songIndexIndex]);
			freshArr.RemoveAt(songIndexIndex);
		}

		saveFile->SetSongIndexArr(newSongIndexArr);
	}
	else
	{
		TArray<int> integerArr = saveFile->GetSongIndexArr();
		integerArr.RemoveAt(integerArr.Num() - 1);
		saveFile->SetSongIndexArr(integerArr);
	}

	UGameplayStatics::SaveGameToSlot(saveFile, TEXT("saveGameOne"), 0);
}

void AMyHUD::ToggleSong(int songToToggle)
{
	USaveGameOne* saveFile = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));

	TArray<int> tempSongCycles = saveFile->GetSongCycles();
	TArray<int> tempSongIndexArr = saveFile->GetSongIndexArr();

	if (tempSongCycles[songToToggle])
	{
		tempSongCycles[songToToggle] = 0;
		songCycles[songToToggle] = 0;

		tempSongIndexArr.Insert(songToToggle, FMath::RandRange(0, tempSongIndexArr.Num() - 1));//does this work? prolly
	}
	else
	{
		tempSongCycles[songToToggle] = 2;
		songCycles[songToToggle] = 2;

		tempSongIndexArr.RemoveSingle(songToToggle);
	}

	saveFile->SetSongCycles(tempSongCycles);
	saveFile->SetSongIndexArr(tempSongIndexArr);

	UGameplayStatics::SaveGameToSlot(saveFile, TEXT("saveGameOne"), 0);
}

void AMyHUD::CommitMaster(int newVol)/*so the only math i havent vetted is how the masterCoefficient is going to interact with the subCoefficients.when masters 50 will changing sfx from 100 to 50 halve the volume by ear similarly enough to how setting master as 50 from 100 did ? should do, needs testing

if your different catagories of sound effects are being played at different decibals, which they are, you will need different masterCoefficient calculations one for each catagory. if each individual sound effect is beign played at different decibals you will need a unique masterCoefficient calculation for each sound effect as well as different subCoefficient calculations. which I am not going to do, but remember this for the next game(s) SOLVED actually I did make unique coefficient pairs for each sound effect it was the only way

do I want it to be that when masterVol is 50 the subCatagoryVol creates inaudability at 1 or like I currently have it (that is basically just somewhere in the middle) then what about vice versa? would it be possible to make the masterCoefficients and the subCoefficients work toward a designated destination simultaneously?? that sounds fun SOLVED yes this was done

now when I adjust each coefficient pair I will also need to adjust the destination coefficients.. maybe I only need one destination coefficient SOLVED

you need to check if the playgame function in the gameSlateWidget works once youve finished with all this shit EDIT it 99% does I was experiencing a concerning problem here but it turned out to just be a clerical error*/
{
	USaveGameOne* saveFile = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));
	saveFile->SetMaster(newVol);
	UGameplayStatics::SaveGameToSlot(saveFile, TEXT("saveGameOne"), 0);

	double w = ((double)100 - (double)newVol) / (double)50;
	double g = 1;
	double h = 1;
	double i = 1;

	if (newVol == 0)
	{
		g = 0;
		h = 0;
		i = 0;
	}
	else if (saveFile->GetMusic() == 0)
	{
		g = 0;
	}
	else if (saveFile->GetAtmosphere() == 0)
	{
		h = 0;
	}
	else if (saveFile->GetSFX() == 0)
	{
		i = 0;
	}

	masterCoefficientM = (double)pow((double)10, (double)-1 * (double)w);
	masterCoefficientAOne = (double)pow((double)10, (double)-2.6 * (double)w);
	masterCoefficientATwo = (double)pow((double)10, (double)-0.8 * (double)w);
	masterCoefficientAThree = (double)pow((double)10, (double)-1 * (double)w);
	masterCoefficientSOne = (double)pow((double)10, (double)-1.25 * (double)w);
	masterCoefficientSTwo = (double)pow((double)10, (double)-1.6 * (double)w);
	masterCoefficientSThree = (double)pow((double)10, (double)-1.9 * (double)w);
	masterCoefficientSFour = (double)pow((double)10, (double)-1.3 * (double)w);
	masterCoefficientSFive = (double)pow((double)10, (double)-0.9 * (double)w);
	masterCoefficientSSix = (double)pow((double)10, (double)-0.8 * (double)w);
	masterCoefficientSSeven = (double)pow((double)10, (double)-1.0 * (double)w);
	masterCoefficientSEight = (double)pow((double)10, (double)-1.2 * (double)w);
	masterCoefficientP = (double)pow((double)10, (double)-1.25 * (double)w);

	//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "ping: " + FString::SanitizeFloat(FMath::Clamp(((double)1.0 * (double)masterCoefficientP) * (double)h, (double)0.001, (double)1.0)) + "purpleLullaby: " + FString::SanitizeFloat(FMath::Clamp((double)((double)((double)1.0 * (double)sfxCoefficientOne) - (double)((double)((double)((double)1.0 * (double)sfxCoefficientOne) - ((double)1.0 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientP))) * (double)i, (double)0.001, (double)1.0)));

	songOneAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.6 * (double)musicCoefficient) - (double)((double)((double)((double)0.6 * (double)musicCoefficient) - ((double)0.6 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientM))) * (double)g, (double)0.001, (double)0.6));
	songTwoAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.6 * (double)musicCoefficient) - (double)((double)((double)((double)0.6 * (double)musicCoefficient) - ((double)0.6 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientM))) * (double)g, (double)0.001, (double)0.6));
	songThreeAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.2 * (double)musicCoefficient) - (double)((double)((double)((double)0.2 * (double)musicCoefficient) - ((double)0.2 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientM))) * (double)g, (double)0.001, (double)0.2));
	songFourAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.0 * (double)musicCoefficient) - (double)((double)((double)((double)1.0 * (double)musicCoefficient) - ((double)1.0 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientM))) * (double)g, (double)0.001, (double)1.0));
	songFiveAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.0 * (double)musicCoefficient) - (double)((double)((double)((double)1.0 * (double)musicCoefficient) - ((double)1.0 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientM))) * (double)g, (double)0.001, (double)1.0));
	songSixAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.5 * (double)musicCoefficient) - (double)((double)((double)((double)0.5 * (double)musicCoefficient) - ((double)0.5 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientM))) * (double)g, (double)0.001, (double)0.5));
	songSevenAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.8 * (double)musicCoefficient) - (double)((double)((double)((double)0.8 * (double)musicCoefficient) - ((double)0.8 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientM))) * (double)g, (double)0.001, (double)0.8));
	songEightAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.2 * (double)musicCoefficient) - (double)((double)((double)((double)0.2 * (double)musicCoefficient) - ((double)0.2 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientM))) * (double)g, (double)0.001, (double)0.2));

	for (int a = 0; a < purpleLullabyAudioComponents.Num(); a++)
	{
		purpleLullabyAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.0 * (double)sfxCoefficientOne) - (double)((double)((double)((double)1.0 * (double)sfxCoefficientOne) - ((double)1.0 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientSOne))) * (double)i, (double)0.001, (double)1.0));
	}

	for (int a = 0; a < hoverGrowAudioComponents.Num(); a++)
	{
		hoverGrowAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)7.6 * (double)sfxCoefficientTwo) - (double)((double)((double)((double)7.6 * (double)sfxCoefficientTwo) - ((double)7.6 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientSTwo))) * (double)i, (double)0.001, (double)7.6));
		hoverShrinkAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)7.6 * (double)sfxCoefficientTwo) - (double)((double)((double)((double)7.6 * (double)sfxCoefficientTwo) - ((double)7.6 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientSTwo))) * (double)i, (double)0.001, (double)7.6));
	}

	intersectionDownAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)90.0 * (double)sfxCoefficientThree) - (double)((double)((double)((double)90.0 * (double)sfxCoefficientThree) - ((double)90.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)masterCoefficientSThree))) * (double)i, (double)0.001, (double)90.0));
	intersectionUpAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)80.0 * (double)sfxCoefficientThree) - (double)((double)((double)((double)80.0 * (double)sfxCoefficientThree) - ((double)80.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)masterCoefficientSThree))) * (double)i, (double)0.001, (double)80.0));

	shovelingDirtAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.8 * (double)sfxCoefficientFour) - (double)((double)((double)((double)0.8 * (double)sfxCoefficientFour) - ((double)0.8 * (double)destinationCoefficient)) * (double)((double)1 - (double)masterCoefficientSFour))) * (double)i, (double)0.001, (double)0.8));

	curtainClosingAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)4.0 * (double)sfxCoefficientFive) - (double)((double)((double)((double)4.0 * (double)sfxCoefficientFive) - ((double)4.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)masterCoefficientSFive))) * (double)i, (double)0.001, (double)4.0));
	curtainOpeningAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)4.0 * (double)sfxCoefficientFive) - (double)((double)((double)((double)4.0 * (double)sfxCoefficientFive) - ((double)4.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)masterCoefficientSFive))) * (double)i, (double)0.001, (double)4.0));

	missAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.6 * (double)sfxCoefficientSix) - (double)((double)((double)((double)1.6 * (double)sfxCoefficientSix) - ((double)1.6 * (double)destinationCoefficientThree)) * (double)((double)1 - (double)masterCoefficientSSix))) * (double)i, (double)0.001, (double)1.6));

	for (int a = 0; a < 3; a++)
	{
		scoringAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)3.0 * (double)sfxCoefficientSeven) - (double)((double)((double)((double)3.0 * (double)sfxCoefficientSeven) - ((double)3.0 * (double)destinationCoefficientThree)) * (double)((double)1 - (double)masterCoefficientSSeven))) * (double)i, (double)0.001, (double)3.0));

		victoryAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.6 * (double)sfxCoefficientEight) - (double)((double)((double)((double)1.6 * (double)sfxCoefficientEight) - ((double)1.6 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientSEight))) * (double)i, (double)0.001, (double)1.6));
	}

	if (inGame)
	{
		for (int a = 0; a < 2; a++)
		{
			windAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.0 * (double)atmosphereCoefficientOne) - (double)((double)((double)((double)1.0 * (double)atmosphereCoefficientOne) - ((double)1.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)masterCoefficientAOne))) * (double)h, (double)0.001, (double)1.0));
			riverAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.16 * (double)atmosphereCoefficientTwo) - (double)((double)((double)((double)0.16 * (double)atmosphereCoefficientTwo) - ((double)0.16 * (double)destinationCoefficientThree)) * (double)((double)1 - (double)masterCoefficientATwo))) * (double)h, (double)0.001, (double)0.16));
			waterfallAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.4 * (double)atmosphereCoefficientThree) - (double)((double)((double)((double)0.4 * (double)atmosphereCoefficientThree) - ((double)0.4 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientAThree))) * (double)h, (double)0.001, (double)0.4));
		}
	}
	else
	{
		for (int a = 0; a < 2; a++)
		{
			windAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)2.0 * (double)atmosphereCoefficientOne) - (double)((double)((double)((double)2.0 * (double)atmosphereCoefficientOne) - ((double)2.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)masterCoefficientAOne))) * (double)h, (double)0.001, (double)2.0));
			windWithSheepAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)2.0 * (double)atmosphereCoefficientOne) - (double)((double)((double)((double)2.0 * (double)atmosphereCoefficientOne) - ((double)2.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)masterCoefficientAOne))) * (double)h, (double)0.001, (double)2.0));

			riverAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.33 * (double)atmosphereCoefficientTwo) - (double)((double)((double)((double)0.33 * (double)atmosphereCoefficientTwo) - ((double)0.33 * (double)destinationCoefficientThree)) * (double)((double)1 - (double)masterCoefficientATwo))) * (double)h, (double)0.001, (double)0.33));
			waterfallAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.8 * (double)atmosphereCoefficientThree) - (double)((double)((double)((double)0.8 * (double)atmosphereCoefficientThree) - ((double)0.8 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientAThree))) * (double)h, (double)0.001, (double)0.8));
		}
	}

	int p = FMath::RandRange(0, 3);
	for (int a = 0; a < 3; a++)
	{
		purpleLullabyTwoAudioComponents[chordIndexes[p][a]]->Stop();
		purpleLullabyTwoAudioComponents[chordIndexes[p][a]]->SetVolumeMultiplier(FMath::Clamp((double)1.0 * (double)masterCoefficientP, (double)0.001, (double)1.0));
		purpleLullabyTwoAudioComponents[chordIndexes[p][a]]->Play();
	}
}
void AMyHUD::CommitMusic(int newVol)
{
	USaveGameOne* saveFile = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));
	saveFile->SetMusic(newVol);
	UGameplayStatics::SaveGameToSlot(saveFile, TEXT("saveGameOne"), 0);
	double x = ((double)100 - (double)newVol) / (double)50;
	double g = 1;

	if (newVol == 0 || saveFile->GetMaster() == 0)
	{
		g = 0;
	}

	musicCoefficient = (double)pow((double)10, (double)-1 * (double)x);
	pingCoefficient = (double)pow((double)10, (double)-1.25 * (double)x);

	songOneAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.6 * (double)masterCoefficientM) - (double)((double)((double)((double)0.6 * (double)masterCoefficientM) - ((double)0.6 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)musicCoefficient))) * (double)g, (double)0.001, (double)0.6));
	songTwoAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.6 * (double)masterCoefficientM) - (double)((double)((double)((double)0.6 * (double)masterCoefficientM) - ((double)0.6 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)musicCoefficient))) * (double)g, (double)0.001, (double)0.6));
	songThreeAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.2 * (double)masterCoefficientM) - (double)((double)((double)((double)0.2 * (double)masterCoefficientM) - ((double)0.2 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)musicCoefficient))) * (double)g, (double)0.001, (double)0.2));
	songFourAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.0 * (double)masterCoefficientM) - (double)((double)((double)((double)1.0 * (double)masterCoefficientM) - ((double)1.0 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)musicCoefficient))) * (double)g, (double)0.001, (double)1.0));
	songFiveAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.0 * (double)masterCoefficientM) - (double)((double)((double)((double)1.0 * (double)masterCoefficientM) - ((double)1.0 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)musicCoefficient))) * (double)g, (double)0.001, (double)1.0));
	songSixAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.5 * (double)masterCoefficientM) - (double)((double)((double)((double)0.5 * (double)masterCoefficientM) - ((double)0.5 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)musicCoefficient))) * (double)g, (double)0.001, (double)0.5));
	songSevenAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.8 * (double)masterCoefficientM) - (double)((double)((double)((double)0.8 * (double)masterCoefficientM) - ((double)0.8 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)musicCoefficient))) * (double)g, (double)0.001, (double)0.8));
	songEightAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.2 * (double)masterCoefficientM) - (double)((double)((double)((double)0.2 * (double)masterCoefficientM) - ((double)0.2 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)musicCoefficient))) * (double)g, (double)0.001, (double)0.2));

	int p = FMath::RandRange(0, 3);
	for (int a = 0; a < 3; a++)
	{
		purpleLullabyTwoAudioComponents[chordIndexes[p][a]]->Stop();
		purpleLullabyTwoAudioComponents[chordIndexes[p][a]]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.0 * (double)masterCoefficientP) - (double)((double)((double)((double)1.0 * (double)masterCoefficientP) - ((double)1.0 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)pingCoefficient))) * (double)g, (double)0.001, (double)1.0));
		purpleLullabyTwoAudioComponents[chordIndexes[p][a]]->Play();
	}
}
void AMyHUD::CommitAtmosphere(int newVol)
{
	USaveGameOne* saveFile = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));
	saveFile->SetAtmosphere(newVol);
	UGameplayStatics::SaveGameToSlot(saveFile, TEXT("saveGameOne"), 0);

	double y = (double)((double)100 - (double)newVol) / (double)50;
	double h = 1;

	if (newVol == 0 || saveFile->GetMaster() == 0)
	{
		h = 0;
	}

	atmosphereCoefficientOne = (double)pow((double)10, (double)-2.6 * (double)y);
	atmosphereCoefficientTwo = (double)pow((double)10, (double)-0.8 * (double)y);
	atmosphereCoefficientThree = (double)pow((double)10, (double)-1.0 * (double)y);
	pingCoefficient = (double)pow((double)10, (double)-1.25 * (double)y);

	if (inGame)
	{
		for (int a = 0; a < 2; a++)
		{
			windAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.0 * (double)masterCoefficientAOne) - (double)((double)((double)((double)1.0 * (double)masterCoefficientAOne) - ((double)1.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)atmosphereCoefficientOne))) * (double)h, (double)0.001, (double)1.0));
			riverAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.16 * (double)masterCoefficientATwo) - (double)((double)((double)((double)0.16 * (double)masterCoefficientATwo) - ((double)0.16 * (double)destinationCoefficientThree)) * (double)((double)1 - (double)atmosphereCoefficientTwo))) * (double)h, (double)0.001, (double)0.16));
			waterfallAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.4 * (double)masterCoefficientAThree) - (double)((double)((double)((double)0.4 * (double)masterCoefficientAThree) - ((double)0.4 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)atmosphereCoefficientThree))) * (double)h, (double)0.001, (double)0.4));
		}
	}
	else
	{
		for (int a = 0; a < 2; a++)
		{
			windAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)2.0 * (double)masterCoefficientAOne) - (double)((double)((double)((double)2.0 * (double)masterCoefficientAOne) - ((double)2.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)atmosphereCoefficientOne))) * (double)h, (double)0.001, (double)2.0));
			windWithSheepAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)2.0 * (double)masterCoefficientAOne) - (double)((double)((double)((double)2.0 * (double)masterCoefficientAOne) - ((double)2.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)atmosphereCoefficientOne))) * (double)h, (double)0.001, (double)2.0));

			riverAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.33 * (double)masterCoefficientATwo) - (double)((double)((double)((double)0.33 * (double)masterCoefficientATwo) - ((double)0.33 * (double)destinationCoefficientThree)) * (double)((double)1 - (double)atmosphereCoefficientTwo))) * (double)h, (double)0.001, (double)0.33));
			waterfallAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.8 * (double)masterCoefficientAThree) - (double)((double)((double)((double)0.8 * (double)masterCoefficientAThree) - ((double)0.8 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)atmosphereCoefficientThree))) * (double)h, (double)0.001, (double)0.8));
		}
	}

	int p = FMath::RandRange(0, 3);
	for (int a = 0; a < 3; a++)
	{
		purpleLullabyTwoAudioComponents[chordIndexes[p][a]]->Stop();
		purpleLullabyTwoAudioComponents[chordIndexes[p][a]]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.0 * (double)masterCoefficientP) - (double)((double)((double)((double)1.0 * (double)masterCoefficientP) - ((double)1.0 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)pingCoefficient))) * (double)h, (double)0.001, (double)1.0));
		purpleLullabyTwoAudioComponents[chordIndexes[p][a]]->Play();
	}
}
void AMyHUD::CommitSFX(int newVol)
{
	USaveGameOne* saveFile = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));
	saveFile->SetSFX(newVol);
	UGameplayStatics::SaveGameToSlot(saveFile, TEXT("saveGameOne"), 0);
	double z = ((double)100 - (double)newVol) / (double)50;
	double i = 1;

	if (newVol == 0 || saveFile->GetMaster() == 0)
	{
		i = 0;
	}

	sfxCoefficientOne = (double)pow((double)10, (double)-1.25 * (double)z);
	sfxCoefficientTwo = (double)pow((double)10, (double)-1.6 * (double)z);
	sfxCoefficientThree = (double)pow((double)10, (double)-1.9 * (double)z);
	sfxCoefficientFour = (double)pow((double)10, (double)-1.3 * (double)z);
	sfxCoefficientFive = (double)pow((double)10, (double)-0.9 * (double)z);
	sfxCoefficientSix = (double)pow((double)10, (double)-0.8 * (double)z);
	sfxCoefficientSeven = (double)pow((double)10, (double)-1.0 * (double)z);
	sfxCoefficientEight = (double)pow((double)10, (double)-1.2 * (double)z);
	pingCoefficient = (double)pow((double)10, (double)-1.25 * (double)z);

	for (int a = 0; a < hoverGrowAudioComponents.Num(); a++)
	{
		hoverGrowAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)7.6 * (double)masterCoefficientSTwo) - (double)((double)((double)((double)7.6 * (double)masterCoefficientSTwo) - ((double)7.6 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)sfxCoefficientTwo))) * (double)i, (double)0.001, (double)7.6));
		hoverShrinkAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)7.6 * (double)masterCoefficientSTwo) - (double)((double)((double)((double)7.6 * (double)masterCoefficientSTwo) - ((double)7.6 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)sfxCoefficientTwo))) * (double)i, (double)0.001, (double)7.6));
	}

	for (int a = 0; a < purpleLullabyAudioComponents.Num(); a++)
	{
		purpleLullabyAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.0 * (double)masterCoefficientSOne) - (double)((double)((double)((double)1.0 * (double)masterCoefficientSOne) - ((double)1.0 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)sfxCoefficientOne))) * (double)i, (double)0.001, (double)1.0));
	}

	intersectionDownAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)90.0 * (double)masterCoefficientSThree) - (double)((double)((double)((double)90.0 * (double)masterCoefficientSThree) - ((double)90.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)sfxCoefficientThree))) * (double)i, (double)0.001, (double)90.0));
	intersectionUpAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)80.0 * (double)masterCoefficientSThree) - (double)((double)((double)((double)80.0 * (double)masterCoefficientSThree) - ((double)80.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)sfxCoefficientThree))) * (double)i, (double)0.001, (double)80.0));

	shovelingDirtAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.8 * (double)masterCoefficientSFour) - (double)((double)((double)((double)0.8 * (double)masterCoefficientSFour) - ((double)0.8 * (double)destinationCoefficient)) * (double)((double)1 - (double)sfxCoefficientFour))) * (double)i, (double)0.001, (double)0.8));

	curtainClosingAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)4.0 * (double)masterCoefficientSFive) - (double)((double)((double)((double)4.0 * (double)masterCoefficientSFive) - ((double)4.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)sfxCoefficientFive))) * (double)i, (double)0.001, (double)4.0));
	curtainOpeningAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)4.0 * (double)masterCoefficientSFive) - (double)((double)((double)((double)4.0 * (double)masterCoefficientSFive) - ((double)4.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)sfxCoefficientFive))) * (double)i, (double)0.001, (double)4.0));

	missAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.6 * (double)masterCoefficientSSix) - (double)((double)((double)((double)1.6 * (double)masterCoefficientSSix) - ((double)1.6 * (double)destinationCoefficientThree)) * (double)((double)1 - (double)sfxCoefficientSix))) * (double)i, (double)0.001, (double)1.6));

	for (int a = 0; a < 3; a++)
	{
		scoringAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)3.0 * (double)sfxCoefficientSeven) - (double)((double)((double)((double)3.0 * (double)sfxCoefficientSeven) - ((double)3.0 * (double)destinationCoefficientThree)) * (double)((double)1 - (double)masterCoefficientSSeven))) * (double)i, (double)0.001, (double)3.0));

		victoryAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.6 * (double)masterCoefficientSEight) - (double)((double)((double)((double)1.6 * (double)masterCoefficientSEight) - ((double)1.6 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)sfxCoefficientEight))) * (double)i, (double)0.001, (double)1.6));
	}

	int p = FMath::RandRange(0, 3);
	for (int a = 0; a < 3; a++)
	{
		purpleLullabyTwoAudioComponents[chordIndexes[p][a]]->Stop();
		purpleLullabyTwoAudioComponents[chordIndexes[p][a]]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.0 * (double)masterCoefficientP) - (double)((double)((double)((double)1.0 * (double)masterCoefficientP) - ((double)1.0 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)pingCoefficient))) * (double)i, (double)0.001, (double)1.0));
		purpleLullabyTwoAudioComponents[chordIndexes[p][a]]->Play();
	}
}


void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	missAudioComponent->Stop();

	for (int a = 0; a < 3; a++)
	{
		scoringAudioComponents[a]->Stop();
		victoryAudioComponents[a]->Stop();
	}

	for (int a = 0; a < hoverGrows.Num(); a++)
	{
		hoverGrowAudioComponents[a]->Stop();
		hoverShrinkAudioComponents[a]->Stop();
	}

	for (int a = 0; a < 2; a++)
	{
		windAudioComponents[a]->Stop();
		windWithSheepAudioComponents[a]->Stop();

		riverAudioComponents[a]->Stop();

		waterfallAudioComponents[a]->Stop();
	}

	for (int a = 0; a < 8; a++)
	{
		purpleLullabyAudioComponents[a]->Stop();
		purpleLullabyTwoAudioComponents[a]->Stop();
	}

	intersectionDownAudioComponent->Stop();
	intersectionUpAudioComponent->Stop();

	curtainClosingAudioComponent->Stop();
	curtainOpeningAudioComponent->Stop();

	rainstickAudioComponent->Stop();

	shovelingDirtAudioComponent->Stop();

	for (int a = 0; a < 8; a++)
	{
		songAudioComponents[a]->Stop();
	}

	songOneAudioComponent = songAudioComponents[0];
	songTwoAudioComponent = songAudioComponents[1];
	songThreeAudioComponent = songAudioComponents[2];
	songFourAudioComponent = songAudioComponents[3];
	songFiveAudioComponent = songAudioComponents[4];
	songSixAudioComponent = songAudioComponents[5];
	songSevenAudioComponent = songAudioComponents[6];
	songEightAudioComponent = songAudioComponents[7];

	if (UGameplayStatics::LoadGameFromSlot("saveGameOne", 0) == nullptr)//to create a save redundency Ill just create a new slotname
	{
		newSongIndexArr.Empty();
		TArray<int> freshArr = { 0, 1, 2, 3, 4, 5, 6, 7 };
		for (int a = 0; a < 8; a++)
		{
			int songIndexIndex = FMath::RandRange(0, freshArr.Num() - 1);
			newSongIndexArr.Add(freshArr[songIndexIndex]);
			freshArr.RemoveAt(songIndexIndex);
		}

		USaveGameOne* LoadGameInstance = Cast<USaveGameOne>(UGameplayStatics::CreateSaveGameObject(USaveGameOne::StaticClass()));
		LoadGameInstance->SetMaxLevel(0);
		LoadGameInstance->SetHighscores({ 0, 0, 0 });
		LoadGameInstance->SetHighscoreDataOne(0);
		LoadGameInstance->SetHighscoreDataTwo(0);
		LoadGameInstance->SetScoreThisGame(0);
		LoadGameInstance->SetMaster(100);
		LoadGameInstance->SetMusic(100);
		LoadGameInstance->SetAtmosphere(100);
		LoadGameInstance->SetSFX(100);
		LoadGameInstance->SetPauseKey(EKeys::Escape);
		LoadGameInstance->SetPauseMouse(EKeys::MiddleMouseButton);
		LoadGameInstance->SetSelectKey(EKeys::LeftMouseButton);
		LoadGameInstance->SetMoveKey(EKeys::Mouse2D);
		LoadGameInstance->SetPauseController(EKeys::Gamepad_FaceButton_Right);
		LoadGameInstance->SetSelectController(EKeys::Gamepad_Special_Right);
		LoadGameInstance->SetMoveController(EKeys::Gamepad_Left2D);
		LoadGameInstance->SetSongIndexArr(newSongIndexArr);
		LoadGameInstance->SetSongCycles({ 0, 0, 0, 0, 0, 0, 0, 0 });
		UGameplayStatics::SaveGameToSlot(LoadGameInstance, TEXT("saveGameOne"), 0);
	}

	/*newSongIndexArr.Empty();
	TArray<int> freshArr = { 0, 1, 2, 3, 4, 5, 6, 7 };
	for (int a = 0; a < 8; a++)
	{
		int songIndexIndex = FMath::RandRange(0, freshArr.Num() - 1);
		newSongIndexArr.Add(freshArr[songIndexIndex]);
		freshArr.RemoveAt(songIndexIndex);
	}

	USaveGameOne* adjustedSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));
	adjustedSave->SetMaxLevel(8);
	adjustedSave->SetHighscores({ 0, 0, 0 });
	adjustedSave->SetHighscoreDataOne(0);
	adjustedSave->SetHighscoreDataTwo(0);
	adjustedSave->SetScoreThisGame(0);
	adjustedSave->SetMaster(100);
	adjustedSave->SetMusic(100);
	adjustedSave->SetAtmosphere(100);
	adjustedSave->SetSFX(100);
	adjustedSave->SetPauseKey(EKeys::Escape);// I should add a "reset to default bindings" option in the controls options menu
	adjustedSave->SetPauseMouse(EKeys::MiddleMouseButton);
	adjustedSave->SetSelectKey(EKeys::LeftMouseButton);
	adjustedSave->SetMoveKey(EKeys::Mouse2D);
	adjustedSave->SetPauseController(EKeys::Gamepad_FaceButton_Right);
	adjustedSave->SetSelectController(EKeys::Gamepad_Special_Right);
	adjustedSave->SetMoveController(EKeys::Gamepad_Left2D);
	adjustedSave->SetSongIndexArr(newSongIndexArr);
	adjustedSave->SetSongCycles({ 0, 0, 0, 0, 0, 0, 0, 0 });
	UGameplayStatics::SaveGameToSlot(adjustedSave, TEXT("saveGameOne"), 0);*/
	//adjustedSave = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(adjustedSave->SaveSlotName, 0));//is this gonna be a problem? do I need to get the actual default adjustedSave->SaveSlotName and the actual adjustedSave->UserIndex?

	USaveGameOne* referenceInstance = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));

	songCycles = referenceInstance->GetSongCycles();

	double w = (double)((double)100 - (double)referenceInstance->GetMaster()) / (double)50;
	double x = (double)((double)100 - (double)referenceInstance->GetMusic()) / (double)50;
	double y = (double)((double)100 - (double)referenceInstance->GetAtmosphere()) / (double)50;
	double z = (double)((double)100 - (double)referenceInstance->GetSFX()) / (double)50;

	masterCoefficientM = (double)pow((double)10, (double)-1 * (double)w);
	musicCoefficient = (double)pow((double)10, (double)-1 * (double)x);

	masterCoefficientAOne = (double)pow((double)10, (double)-2.6 * (double)w);;
	atmosphereCoefficientOne = (double)pow((double)10, (double)-2.6 * (double)y);
	masterCoefficientATwo = (double)pow((double)10, (double)-0.8 * (double)w);
	atmosphereCoefficientTwo = (double)pow((double)10, (double)-0.8 * (double)y);
	masterCoefficientAThree = (double)pow((double)10, (double)-1 * (double)w);
	atmosphereCoefficientThree = (double)pow((double)10, (double)-1 * (double)y);//now for every song with significantly varying amplitude I will need to create new coefficients thats probably insomnia (songThree) and kimiko has some sharp amplitude but her songs also have some subtle notes 

	masterCoefficientSOne = (double)pow((double)10, (double)-1.25 * (double)w);
	sfxCoefficientOne = (double)pow((double)10, (double)-1.25 * (double)z);
	masterCoefficientSTwo = (double)pow((double)10, (double)-1.6 * (double)w);
	sfxCoefficientTwo = (double)pow((double)10, (double)-1.6 * (double)z);
	masterCoefficientSThree = (double)pow((double)10, (double)-1.9 * (double)w);
	sfxCoefficientThree = (double)pow((double)10, (double)-1.9 * (double)z);
	masterCoefficientSFour = (double)pow((double)10, (double)-1.3 * (double)w);
	sfxCoefficientFour = (double)pow((double)10, (double)-1.3 * (double)z);
	masterCoefficientSFive = (double)pow((double)10, (double)-0.9 * (double)w);
	sfxCoefficientFive = (double)pow((double)10, (double)-0.9 * (double)z);
	masterCoefficientSSix = (double)pow((double)10, (double)-0.8 * (double)w);
	sfxCoefficientSix = (double)pow((double)10, (double)-0.8 * (double)z);
	masterCoefficientSSeven = (double)pow((double)10, (double)-1.0 * (double)w);
	sfxCoefficientSeven = (double)pow((double)10, (double)-1.0 * (double)z);
	masterCoefficientSEight = (double)pow((double)10, (double)-1.2 * (double)w);
	sfxCoefficientEight = (double)pow((double)10, (double)-1.2 * (double)z);

	masterCoefficientP = (double)pow((double)10, (double)-1.25 * (double)w);

	destinationCoefficient = (double)pow((double)10, (double)-4);
	destinationCoefficientTwo = (double)pow((double)10, (double)-3/*(double)-x*/);//this needs to be the same as the atmosphereCoefficient accept replace x with what x would be if newVol, or saveFile->get..(), was 0
	destinationCoefficientThree = (double)pow((double)10, (double)-2);//all the volumes will need to be set here just after this because Im centralizing volume control here and removing volume control within the sub files. But then I will need to alter volume to adjust for whether in game or in menu from this master file. write this first after work

	double g = 1;
	double i = 1;

	if (referenceInstance->GetMaster() == 0)
	{
		g = 0.001;
		i = 0.001;
	}
	else if (referenceInstance->GetMusic() == 0)
	{
		g = 0.001;
	}
	else if (referenceInstance->GetSFX() == 0)
	{
		i = 0.001;
	}

	songOneAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.6 * (double)musicCoefficient) - (double)((double)((double)((double)0.6 * (double)musicCoefficient) - ((double)0.6 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientM))) * (double)g, (double)0.001, (double)0.6));
	songTwoAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.6 * (double)musicCoefficient) - (double)((double)((double)((double)0.6 * (double)musicCoefficient) - ((double)0.6 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientM))) * (double)g, (double)0.001, (double)0.6));
	songThreeAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.2 * (double)musicCoefficient) - (double)((double)((double)((double)0.2 * (double)musicCoefficient) - ((double)0.2 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientM))) * (double)g, (double)0.001, (double)0.2));
	songFourAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.0 * (double)musicCoefficient) - (double)((double)((double)((double)1.0 * (double)musicCoefficient) - ((double)1.0 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientM))) * (double)g, (double)0.001, (double)1.0));
	songFiveAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.0 * (double)musicCoefficient) - (double)((double)((double)((double)1.0 * (double)musicCoefficient) - ((double)1.0 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientM))) * (double)g, (double)0.001, (double)1.0));
	songSixAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.5 * (double)musicCoefficient) - (double)((double)((double)((double)0.5 * (double)musicCoefficient) - ((double)0.5 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientM))) * (double)g, (double)0.001, (double)0.5));
	songSevenAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.8 * (double)musicCoefficient) - (double)((double)((double)((double)0.8 * (double)musicCoefficient) - ((double)0.8 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientM))) * (double)g, (double)0.001, (double)0.8));
	songEightAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.2 * (double)musicCoefficient) - (double)((double)((double)((double)0.2 * (double)musicCoefficient) - ((double)0.2 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientM))) * (double)g, (double)0.001, (double)0.2));

	for (int a = 0; a < purpleLullabyAudioComponents.Num(); a++)
	{
		purpleLullabyAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.0 * (double)sfxCoefficientOne) - (double)((double)((double)((double)1.0 * (double)sfxCoefficientOne) - ((double)1.0 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientSOne))) * (double)i, (double)0.001, (double)1.0));
	}

	for (int a = 0; a < hoverGrowAudioComponents.Num(); a++)
	{
		hoverGrowAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)7.6 * (double)sfxCoefficientTwo) - (double)((double)((double)((double)7.6 * (double)sfxCoefficientTwo) - ((double)7.6 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientSTwo))) * (double)i, (double)0.001, (double)7.6));
		hoverShrinkAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)7.6 * (double)sfxCoefficientTwo) - (double)((double)((double)((double)7.6 * (double)sfxCoefficientTwo) - ((double)7.6 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientSTwo))) * (double)i, (double)0.001, (double)7.6));
	}

	intersectionDownAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)90.0 * (double)sfxCoefficientThree) - (double)((double)((double)((double)90.0 * (double)sfxCoefficientThree) - ((double)90.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)masterCoefficientSThree))) * (double)i, (double)0.001, (double)90.0));
	intersectionUpAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)80.0 * (double)sfxCoefficientThree) - (double)((double)((double)((double)80.0 * (double)sfxCoefficientThree) - ((double)80.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)masterCoefficientSThree))) * (double)i, (double)0.001, (double)80.0));

	shovelingDirtAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.8 * (double)sfxCoefficientFour) - (double)((double)((double)((double)0.8 * (double)sfxCoefficientFour) - ((double)0.8 * (double)destinationCoefficient)) * (double)((double)1 - (double)masterCoefficientSFour))) * (double)i, (double)0.001, (double)0.8));

	curtainClosingAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)4.0 * (double)sfxCoefficientFive) - (double)((double)((double)((double)4.0 * (double)sfxCoefficientFive) - ((double)4.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)masterCoefficientSFive))) * (double)i, (double)0.001, (double)4.0));
	curtainOpeningAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)4.0 * (double)sfxCoefficientFive) - (double)((double)((double)((double)4.0 * (double)sfxCoefficientFive) - ((double)4.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)masterCoefficientSFive))) * (double)i, (double)0.001, (double)4.0));

	missAudioComponent->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.6 * (double)sfxCoefficientSix) - (double)((double)((double)((double)1.6 * (double)sfxCoefficientSix) - ((double)1.6 * (double)destinationCoefficientThree)) * (double)((double)1 - (double)masterCoefficientSSix))) * (double)i, (double)0.001, (double)1.6));

	for (int a = 0; a < 3; a++)
	{
		scoringAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)3.0 * (double)sfxCoefficientSeven) - (double)((double)((double)((double)3.0 * (double)sfxCoefficientSeven) - ((double)3.0 * (double)destinationCoefficientThree)) * (double)((double)1 - (double)masterCoefficientSSeven))) * (double)i, (double)0.001, (double)3.0));

		victoryAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.6 * (double)sfxCoefficientEight) - (double)((double)((double)((double)1.6 * (double)sfxCoefficientEight) - ((double)1.6 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientSEight))) * (double)i, (double)0.001, (double)1.6));
	}

	inGame = false;
	newMaxLevel = false;
	songPlaying = false;
	songPlayingIndex = 0;

	if (GEngine && GEngine->GameViewport)
	{
		playerOnePlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		standardWorldContextObject = GetWorld();//do I actually need this?! its being used before its being initialized wtf?

		/*UGameUserSettings* MyGameSettings = GEngine->GetGameUserSettings();
		MyGameSettings->SetFullscreenMode(EWindowMode::Fullscreen);
		MyGameSettings->ApplySettings(true);*/

		splashScreenSlateWidget = SNew(SCompanySplash)
			.OwningHUD(this)
			.goodUseSplashBootNoGrass_SMUI(goodUseSplashBootNoGrass_SMUI)
			.goodUseSplashGrass_SMUI(goodUseSplashGrass_SMUI)
			.goodUseDigitalText_SMUI(goodUseDigitalText_SMUI)
			.splashGrassArr(splashGrassArr)
			.splashBootArr(splashBootArr)
			.black_SMUI(black_SMUI)
			.shovelingDirtAudioComponent(shovelingDirtAudioComponent);

		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(slateWidgetContainerSeven, SWeakWidget).PossiblyNullContent(splashScreenSlateWidget.ToSharedRef()));

		FInputModeUIOnly splashScreenInputMode = FInputModeUIOnly();//Im getting an error in the unreal engine log. do I need to set canSupportFocus within the widget before calling this? whichever one of these is causing the error I might as well just comment it out for the time being
		splashScreenInputMode.SetWidgetToFocus(splashScreenSlateWidget);
		splashScreenInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		//mainMenuInputMode.SetHideCursorDuringCapture(false);
		playerOnePlayerController->SetInputMode(splashScreenInputMode);
		playerOnePlayerController->SetShowMouseCursor(true);
		FSlateApplication::Get().SetKeyboardFocus(splashScreenSlateWidget);
	}
}

/*RELEASE NOTES*/
/*
can you exit the game by pressing esc in the wrong place in the packaged version?
*/

void AMyHUD::DestroySplash()
{
	GEngine->GameViewport->RemoveViewportWidgetContent(slateWidgetContainerSeven.ToSharedRef());
	shovelingDirtAudioComponent->Stop();

	GenerateMainMenuBackground();

	//PreLoadCurtains();

	mainMenuSlateWidget = SNew(SSArcadeModeTitleScreen)
		.OwningHUD(this)
		.playerOnePlayerController(playerOnePlayerController)
		.standardWorldContextObject(standardWorldContextObject)
		.backgroundMaterials(backgroundMaterials)
		.backgroundIsLargeTile(backgroundIsLargeTile)
		.displayResults(false)
		.gameFrameColor_SMUI(gameFrameColor_SMUI)
		.hoverGrowAudioComponents(hoverGrowAudioComponents)
		.hoverShrinkAudioComponents(hoverShrinkAudioComponents)
		.windAudioComponents(windAudioComponents)
		.windWithSheepAudioComponents(windWithSheepAudioComponents)
		.riverAudioComponents(riverAudioComponents)
		.waterfallAudioComponents(waterfallAudioComponents)
		.purpleLullabyAudioComponents(purpleLullabyAudioComponents)
		.environmentAudio(environmentAudio);

	GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(slateWidgetContainerThree, SWeakWidget).PossiblyNullContent(mainMenuSlateWidget.ToSharedRef()));

	//FSlateApplication::SetUserFocus(0, loadingSlateWidget);

	//FInputModeGameAndUI mainMenuInputMode = FInputModeGameAndUI();
	FInputModeUIOnly mainMenuInputMode = FInputModeUIOnly();//Im getting an error in the unreal engine log. do I need to set canSupportFocus within the widget before calling this?
	mainMenuInputMode.SetWidgetToFocus(mainMenuSlateWidget);
	mainMenuInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	//mainMenuInputMode.SetHideCursorDuringCapture(false);
	playerOnePlayerController->SetInputMode(mainMenuInputMode);
	playerOnePlayerController->SetShowMouseCursor(true);
	FSlateApplication::Get().SetKeyboardFocus(mainMenuSlateWidget);

	USaveGameOne* referenceInstance = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));
	double h = 1;

	if (referenceInstance->GetMaster() == 0 || referenceInstance->GetAtmosphere() == 0)
	{
		h = 0.001;
	}

	for (int a = 0; a < 2; a++)
	{
		windAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)2.0 * (double)atmosphereCoefficientOne) - (double)((double)((double)((double)2.0 * (double)atmosphereCoefficientOne) - ((double)2.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)masterCoefficientAOne))) * (double)h, (double)0.001, (double)2.0));
		windWithSheepAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)2.0 * (double)atmosphereCoefficientOne) - (double)((double)((double)((double)2.0 * (double)atmosphereCoefficientOne) - ((double)2.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)masterCoefficientAOne))) * (double)h, (double)0.001, (double)2.0));

		riverAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.33 * (double)atmosphereCoefficientTwo) - (double)((double)((double)((double)0.33 * (double)atmosphereCoefficientTwo) - ((double)0.33 * (double)destinationCoefficientThree)) * (double)((double)1 - (double)masterCoefficientATwo))) * (double)h, (double)0.001, (double)0.33));
		waterfallAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.8 * (double)atmosphereCoefficientThree) - (double)((double)((double)((double)0.8 * (double)atmosphereCoefficientThree) - ((double)0.8 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientAThree))) * (double)h, (double)0.001, (double)0.8));
	}
}

void AMyHUD::GenerateMainMenuBackground()
{//wait a sec, for this Ill need to generate a mini river.. oh damnit
	backgroundMaterials = { pondHorizontal_VMUI, emptyImg_SMUI, emptyImg_SMUI, emptyImg_SMUI, emptyImg_SMUI, emptyImg_SMUI, emptyImg_SMUI, emptyImg_SMUI, emptyImg_SMUI };

	int randomNum = FMath::RandRange(0, 33);
	TArray <int> indexOfNonRiverSpaces;

	if (randomNum == 7 || randomNum == 8 || randomNum == 9 || randomNum == 10 || randomNum == 24 || randomNum == 33)
	{
		switch (randomNum)
		{
		case 7:
			environmentAudio = 1;
			backgroundMaterials[0] = pondHorizontal_VMUI;
			pondHorizontal_MP->OpenSource(pondHorizontal_IS);
			mediaPlayersToClose.Add(pondHorizontal_MP);
			break;
		case 8:
			environmentAudio = 1;
			backgroundMaterials[0] = pondVerticleFlowingLeft_VMUI;
			pondVerticleFlowingLeft_MP->OpenSource(pondVerticleFlowingLeft_IS);
			mediaPlayersToClose.Add(pondVerticleFlowingLeft_MP);
			break;
		case 9:
			environmentAudio = 1;
			backgroundMaterials[0] = pondVerticleFlowingRight_VMUI;
			pondVerticleFlowingRight_MP->OpenSource(pondVerticleFlowingRight_IS);
			mediaPlayersToClose.Add(pondVerticleFlowingRight_MP);
			break;
		case 10:
			environmentAudio = 2;
			backgroundMaterials[0] = waterfall_VMUI;
			waterfall_MP->OpenSource(waterfall_IS);
			mediaPlayersToClose.Add(waterfall_MP);
			break;
		case 24:
			environmentAudio = 0;
			backgroundMaterials[0] = tree_VMUI_5;
			tree_MP_5->OpenSource(tree_IS_5);
			mediaPlayersToClose.Add(tree_MP_5);
			break;
		case 33:
			environmentAudio = 0;
			backgroundMaterials[0] = mountain_VMUI_1;
			mountain_MP_1->OpenSource(mountain_IS_1);
			mediaPlayersToClose.Add(mountain_MP_1);
			break;
		}

		backgroundIsLargeTile = true;
		return;
	}
	else if (FMath::RandRange(0, 19) > 9)
	{// a mini river is made
		environmentAudio = 1;
		int dirOfRiver;
		int riverStartingPos;
		int startingSegment = FMath::RandRange(1, 3);
		FVector2D newRiverPos;
		FVector2D convertedRiverPos;
		int indexFormatByRiverDir;
		TArray <int> viableRiverStartingPositions = { 1, 2, 3 };

		switch (FMath::RandRange(0, 2))
		{
		case 0:
			dirOfRiver = 2;
			riverStartingPos = viableRiverStartingPositions[FMath::RandRange(0, 2)];
			newRiverPos = FVector2D(0, riverStartingPos);
			indexFormatByRiverDir = 16;

			break;
		case 1:
			dirOfRiver = 3;
			riverStartingPos = viableRiverStartingPositions[FMath::RandRange(0, 2)];
			newRiverPos = FVector2D(riverStartingPos, 4);
			indexFormatByRiverDir = 10;
			break;
		case 2:
			dirOfRiver = 4;
			riverStartingPos = viableRiverStartingPositions[FMath::RandRange(0, 2)];
			newRiverPos = FVector2D(4, riverStartingPos);
			indexFormatByRiverDir = 13;
			break;
		default:
			break;
		}

		while (true)
		{
			for (int a = startingSegment; a <= 3; a++)
			{
				newRiverPos += FVector2D(1 * ((dirOfRiver - 3) * -1), -1 * (dirOfRiver % 2));
				if (newRiverPos.Y < 1 || newRiverPos.X > 3 || newRiverPos.X < 1)
				{
					break;
				}

				convertedRiverPos.X = newRiverPos.X - 1;
				convertedRiverPos.Y = 3 - newRiverPos.Y;
				backgroundArr[convertedRiverPos.Y * 3 + convertedRiverPos.X] = indexFormatByRiverDir + a;
			}
			if (newRiverPos.Y < 1 || newRiverPos.X > 3 || newRiverPos.X < 1)
			{
				break;
			}

			startingSegment = 1;

			switch (dirOfRiver)
			{
			case 2:
				if (newRiverPos.X + 1 > 3)
				{
					break;
				}

				newRiverPos.X += 1;

				convertedRiverPos.X = newRiverPos.X - 1;
				convertedRiverPos.Y = 3 - newRiverPos.Y;
				backgroundArr[convertedRiverPos.Y * 3 + convertedRiverPos.X] = 27;

				dirOfRiver = 3;
				indexFormatByRiverDir = 10;
				startingSegment = 2;

				break;
			case 3:
				if (newRiverPos.Y - 1 < 1)
				{
					break;
				}
				newRiverPos.Y -= 1;

				convertedRiverPos.X = newRiverPos.X - 1;
				convertedRiverPos.Y = 3 - newRiverPos.Y;

				if (FMath::RandRange(0, 19) > 9)
				{// turning towards 2
					backgroundArr[convertedRiverPos.Y * 3 + convertedRiverPos.X] = 26;
					dirOfRiver = 2;
					indexFormatByRiverDir = 16;
				}
				else
				{// turning towards 4
					backgroundArr[convertedRiverPos.Y * 3 + convertedRiverPos.X] = 28;
					dirOfRiver = 4;
					indexFormatByRiverDir = 13;
				}
				startingSegment = 2;

				break;
			case 4:
				if (newRiverPos.X - 1 < 1)
				{
					break;
				}
				newRiverPos.X -= 1;

				convertedRiverPos.X = newRiverPos.X - 1;
				convertedRiverPos.Y = 3 - newRiverPos.Y;
				backgroundArr[convertedRiverPos.Y * 3 + convertedRiverPos.X] = 25;

				dirOfRiver = 3;
				indexFormatByRiverDir = 10;
				startingSegment = 2;

				break;
			}
		}

		for (int a = 0; a < backgroundArr.Num(); a++)
		{
			if (backgroundArr[a] == 0)
			{
				indexOfNonRiverSpaces.Add(a);
			}
			else
			{
				switch (backgroundArr[a])
				{
				case 11:
					backgroundMaterials[a] = riverFlowingDown_VMUI_1;
					if (!(mediaPlayersToClose.Find(riverFlowingDown_MP_1) + 1))
					{
						riverFlowingDown_MP_1->OpenSource(riverFlowingDown_IS_1);
						mediaPlayersToClose.Add(riverFlowingDown_MP_1);
					}
					break;
				case 12:
					backgroundMaterials[a] = riverFlowingDown_VMUI_2;
					if (!(mediaPlayersToClose.Find(riverFlowingDown_MP_2) + 1))
					{
						riverFlowingDown_MP_2->OpenSource(riverFlowingDown_IS_2);
						mediaPlayersToClose.Add(riverFlowingDown_MP_2);
					}
					break;
				case 13:
					backgroundMaterials[a] = riverFlowingDown_VMUI_3;
					if (!(mediaPlayersToClose.Find(riverFlowingDown_MP_3) + 1))
					{
						riverFlowingDown_MP_3->OpenSource(riverFlowingDown_IS_3);
						mediaPlayersToClose.Add(riverFlowingDown_MP_3);
					}
					break;
				case 14:
					backgroundMaterials[a] = riverFlowingLeft_VMUI_1;
					if (!(mediaPlayersToClose.Find(riverFlowingLeft_MP_1) + 1))
					{
						riverFlowingLeft_MP_1->OpenSource(riverFlowingLeft_IS_1);
						mediaPlayersToClose.Add(riverFlowingLeft_MP_1);
					}
					break;
				case 15:
					backgroundMaterials[a] = riverFlowingLeft_VMUI_2;
					if (!(mediaPlayersToClose.Find(riverFlowingLeft_MP_2) + 1))
					{
						riverFlowingLeft_MP_2->OpenSource(riverFlowingLeft_IS_2);
						mediaPlayersToClose.Add(riverFlowingLeft_MP_2);
					}
					break;
				case 16:
					backgroundMaterials[a] = riverFlowingLeft_VMUI_3;
					if (!(mediaPlayersToClose.Find(riverFlowingLeft_MP_3) + 1))
					{
						riverFlowingLeft_MP_3->OpenSource(riverFlowingLeft_IS_3);
						mediaPlayersToClose.Add(riverFlowingLeft_MP_3);
					}
					break;
				case 17:
					backgroundMaterials[a] = riverFlowingRight_VMUI_1;
					if (!(mediaPlayersToClose.Find(riverFlowingRight_MP_1) + 1))
					{
						riverFlowingRight_MP_1->OpenSource(riverFlowingRight_IS_1);
						mediaPlayersToClose.Add(riverFlowingRight_MP_1);
					}
					break;
				case 18:
					backgroundMaterials[a] = riverFlowingRight_VMUI_2;
					if (!(mediaPlayersToClose.Find(riverFlowingRight_MP_2) + 1))
					{
						riverFlowingRight_MP_2->OpenSource(riverFlowingRight_IS_2);
						mediaPlayersToClose.Add(riverFlowingRight_MP_2);
					}
					break;
				case 19:
					backgroundMaterials[a] = riverFlowingRight_VMUI_3;
					if (!(mediaPlayersToClose.Find(riverFlowingRight_MP_3) + 1))
					{
						riverFlowingRight_MP_3->OpenSource(riverFlowingRight_IS_3);
						mediaPlayersToClose.Add(riverFlowingRight_MP_3);
					}
					break;
				case 25:
					backgroundMaterials[a] = riverTurning_VMUI_1;
					if (!(mediaPlayersToClose.Find(riverTurning_MP_1) + 1))
					{
						riverTurning_MP_1->OpenSource(riverTurning_IS_1);
						mediaPlayersToClose.Add(riverTurning_MP_1);
					}
					break;
				case 26:
					backgroundMaterials[a] = riverTurning_VMUI_2;
					if (!(mediaPlayersToClose.Find(riverTurning_MP_2) + 1))
					{
						riverTurning_MP_2->OpenSource(riverTurning_IS_2);
						mediaPlayersToClose.Add(riverTurning_MP_2);
					}
					break;
				case 27:
					backgroundMaterials[a] = riverTurning_VMUI_3;
					if (!(mediaPlayersToClose.Find(riverTurning_MP_3) + 1))
					{
						riverTurning_MP_3->OpenSource(riverTurning_IS_3);
						mediaPlayersToClose.Add(riverTurning_MP_3);
					}
					break;
				case 28:
					backgroundMaterials[a] = riverTurning_VMUI_4;
					if (!(mediaPlayersToClose.Find(riverTurning_MP_4) + 1))
					{
						riverTurning_MP_4->OpenSource(riverTurning_IS_4);
						mediaPlayersToClose.Add(riverTurning_MP_4);
					}
					break;
				default:
					break;
				}
			}
		}
	}
	else
	{
		environmentAudio = 0;
		indexOfNonRiverSpaces = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	}

	for (int a = 0; a < indexOfNonRiverSpaces.Num(); a++)
	{
		switch (FMath::RandRange(0, 6))
		{
		case 0:
			backgroundMaterials[indexOfNonRiverSpaces[a]] = tree_VMUI_1;
			if (!(mediaPlayersToClose.Find(tree_MP_1) + 1))
			{
				tree_MP_1->OpenSource(tree_IS_1);
				mediaPlayersToClose.Add(tree_MP_1);
			}
			break;
		case 1:
			backgroundMaterials[indexOfNonRiverSpaces[a]] = tree_VMUI_2;
			if (!(mediaPlayersToClose.Find(tree_MP_2) + 1))
			{
				tree_MP_2->OpenSource(tree_IS_2);
				mediaPlayersToClose.Add(tree_MP_2);
			}
			break;
		case 2:
			backgroundMaterials[indexOfNonRiverSpaces[a]] = tree_VMUI_3;
			if (!(mediaPlayersToClose.Find(tree_MP_3) + 1))
			{
				tree_MP_3->OpenSource(tree_IS_3);
				mediaPlayersToClose.Add(tree_MP_3);
			}
			break;
		case 3:
			backgroundMaterials[indexOfNonRiverSpaces[a]] = tree_VMUI_4;
			if (!(mediaPlayersToClose.Find(tree_MP_4) + 1))
			{
				tree_MP_4->OpenSource(tree_IS_4);
				mediaPlayersToClose.Add(tree_MP_4);
			}
			break;
		case 4:
			backgroundMaterials[indexOfNonRiverSpaces[a]] = grass_VMUI_1;
			if (!(mediaPlayersToClose.Find(grass_MP_1) + 1))
			{
				grass_MP_1->OpenSource(grass_IS_1);
				mediaPlayersToClose.Add(grass_MP_1);
			}
			break;
		case 5:
			backgroundMaterials[indexOfNonRiverSpaces[a]] = grass_VMUI_2;
			if (!(mediaPlayersToClose.Find(grass_MP_2) + 1))
			{
				grass_MP_2->OpenSource(grass_IS_2);
				mediaPlayersToClose.Add(grass_MP_2);
			}
			break;
		case 6:
			backgroundMaterials[indexOfNonRiverSpaces[a]] = grass_VMUI_3;
			if (!(mediaPlayersToClose.Find(grass_MP_3) + 1))
			{
				grass_MP_3->OpenSource(grass_IS_3);
				mediaPlayersToClose.Add(grass_MP_3);
			}
			break;
		default:
			break;
		}
	}
	backgroundIsLargeTile = false;
}

void AMyHUD::DisplayOptionsMenu(bool cameFromGame)
{
	fromGame = cameFromGame;

	optionsMenuSlateWidget = SNew(SOptions)
		.OwningHUD(this)
		.playerOnePlayerController(playerOnePlayerController)
		.standardWorldContextObject(standardWorldContextObject)
		.hoverGrowAudioComponents(hoverGrowAudioComponents)
		.hoverShrinkAudioComponents(hoverShrinkAudioComponents)
		.purpleLullabyAudioComponents(purpleLullabyAudioComponents)
		.songAudioComponents(songAudioComponents)
		.gameFrameColor_SMUI(gameFrameColor_SMUI)
		.songPlayingIndex(songPlayingIndex)
		.songCycles(songCycles);

	GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(slateWidgetContainerNine, SWeakWidget).PossiblyNullContent(optionsMenuSlateWidget.ToSharedRef()));

	FInputModeUIOnly optionsInputMode = FInputModeUIOnly();//Im getting an error in the unreal engine log. do I need to set canSupportFocus within the widget before calling this?
	optionsInputMode.SetWidgetToFocus(optionsMenuSlateWidget);
	optionsInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	//mainMenuInputMode.SetHideCursorDuringCapture(false);
	playerOnePlayerController->SetInputMode(optionsInputMode);
	playerOnePlayerController->SetShowMouseCursor(true);
	FSlateApplication::Get().SetKeyboardFocus(optionsMenuSlateWidget);
}

void AMyHUD::DestroyOptionsMenu()
{
	GEngine->GameViewport->RemoveViewportWidgetContent(slateWidgetContainerNine.ToSharedRef());

	if (fromGame)
	{
		pauseScreenSlateWidget->ReturnToLanding();

		FInputModeUIOnly pauseScreenInputMode = FInputModeUIOnly();
		pauseScreenInputMode.SetWidgetToFocus(pauseScreenSlateWidget);
		pauseScreenInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		//mainMenuInputMode.SetHideCursorDuringCapture(false);
		playerOnePlayerController->SetInputMode(pauseScreenInputMode);
		playerOnePlayerController->SetShowMouseCursor(true);
		FSlateApplication::Get().SetKeyboardFocus(pauseScreenSlateWidget);
	}
	else
	{
		mainMenuSlateWidget->ReturnToMenu();

		FInputModeUIOnly mainMenuInputMode = FInputModeUIOnly();
		mainMenuInputMode.SetWidgetToFocus(mainMenuSlateWidget);
		mainMenuInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		playerOnePlayerController->SetInputMode(mainMenuInputMode);
		playerOnePlayerController->SetShowMouseCursor(true);
		FSlateApplication::Get().SetKeyboardFocus(mainMenuSlateWidget);
	}
}

void AMyHUD::DisplayPauseScreen()// if there is a faulty asset file path in the constructor this might find it
{
	for (int a = 0; a < numberOfHoles; a++)
	{
		switch (a)
		{
		case 0:
			flag_MP_1->Pause();
			break;
		case 1:
			flag_MP_2->Pause();
			break;
		case 2:
			flag_MP_3->Pause();
			break;
		case 3:
			flag_MP_4->Pause();
			break;
		case 4:
			flag_MP_5->Pause();
			break;
		case 5:
			flag_MP_6->Pause();
			break;
		case 6:
			flag_MP_7->Pause();
			break;
		case 7:
			flag_MP_8->Pause();
			break;
		case 8:
			flag_MP_9->Pause();
			break;
		case 9:
			flag_MP_10->Pause();
			break;
		case 10:
			flag_MP_11->Pause();
			break;
		case 11:
			flag_MP_12->Pause();
			break;
		case 12:
			flag_MP_13->Pause();
			break;
		case 13:
			flag_MP_14->Pause();
			break;
		case 14:
			flag_MP_15->Pause();
			break;
		case 15:
			flag_MP_16->Pause();
			break;
		default:
			break;
		}
	}

	for (int a = 0; a < activeMediaPlayers.Num(); a++)
	{
		if (activeMediaPlayers[a])
		{
			switch (a)
			{
			case 0:
				grass_MP_1->Pause();
				break;
			case 1:
				holeFromDown_MP->Pause();
				break;
			case 2:
				holeFromLeft_MP->Pause();
				break;
			case 3:
				holeFromRight_MP->Pause();
				break;
			case 4:
				holeFromUp_MP->Pause();
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				pondHorizontal_MP->Pause();
				break;
			case 8:
				pondVerticleFlowingLeft_MP->Pause();
				break;
			case 9:
				pondVerticleFlowingRight_MP->Pause();
				break;
			case 10:
				waterfall_MP->Pause();
				break;
			case 11:
				riverFlowingDown_MP_1->Pause();
				break;
			case 12:
				riverFlowingDown_MP_2->Pause();
				break;
			case 13:
				riverFlowingDown_MP_3->Pause();
				break;
			case 14:
				riverFlowingLeft_MP_1->Pause();
				break;
			case 15:
				riverFlowingLeft_MP_2->Pause();
				break;
			case 16:
				riverFlowingLeft_MP_3->Pause();
				break;
			case 17:
				riverFlowingRight_MP_1->Pause();
				break;
			case 18:
				riverFlowingRight_MP_2->Pause();
				break;
			case 19:
				riverFlowingRight_MP_3->Pause();
				break;
			case 20:
				tree_MP_1->Pause();
				break;
			case 21:
				tree_MP_2->Pause();
				break;
			case 22:
				tree_MP_3->Pause();
				break;
			case 23:
				tree_MP_4->Pause();
				break;
			case 24:
				tree_MP_5->Pause();
				break;
			case 25:
				riverTurning_MP_1->Pause();
				break;
			case 26:
				riverTurning_MP_2->Pause();
				break;
			case 27:
				riverTurning_MP_3->Pause();
				break;
			case 28:
				riverTurning_MP_4->Pause();
				break;
			case 29:
				break;
			case 30:
				grass_MP_1->Pause();
				break;
			case 31:
				grass_MP_2->Pause();
				break;
			case 32:
				grass_MP_3->Pause();
				break;
			case 33:
				mountain_MP_1->Pause();
				break;
			default:
				break;
			}
		}
	}

	pauseScreenSlateWidget = SNew(SPauseScreen)
		.OwningHUD(this)
		.hoverGrowAudioComponents(hoverGrowAudioComponents)
		.hoverShrinkAudioComponents(hoverShrinkAudioComponents)
		.purpleLullabyAudioComponents(purpleLullabyAudioComponents);

	GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(slateWidgetContainerEight, SWeakWidget).PossiblyNullContent(pauseScreenSlateWidget.ToSharedRef()));

	FInputModeUIOnly pauseScreenInputMode = FInputModeUIOnly();
	pauseScreenInputMode.SetWidgetToFocus(pauseScreenSlateWidget);
	pauseScreenInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	//mainMenuInputMode.SetHideCursorDuringCapture(false);
	playerOnePlayerController->SetInputMode(pauseScreenInputMode);
	playerOnePlayerController->SetShowMouseCursor(true);
	FSlateApplication::Get().SetKeyboardFocus(pauseScreenSlateWidget);
}

void AMyHUD::PrepDestroyPauseScreen()
{
	pauseScreenSlateWidget->destroyPauseScreen = true;
}

void AMyHUD::DestroyPauseScreen()
{
	GEngine->GameViewport->RemoveViewportWidgetContent(slateWidgetContainerEight.ToSharedRef());

	gameSlateWidget->PlayGame();

	FInputModeUIOnly gameInWidgetInputMode = FInputModeUIOnly();
	gameInWidgetInputMode.SetWidgetToFocus(gameSlateWidget);
	gameInWidgetInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	playerOnePlayerController->SetInputMode(gameInWidgetInputMode);
	playerOnePlayerController->SetShowMouseCursor(true);
	FSlateApplication::Get().SetKeyboardFocus(gameSlateWidget);

	for (int a = 0; a < numberOfHoles; a++)
	{
		switch (a)
		{
		case 0:
			flag_MP_1->Play();
			break;
		case 1:
			flag_MP_2->Play();
			break;
		case 2:
			flag_MP_3->Play();
			break;
		case 3:
			flag_MP_4->Play();
			break;
		case 4:
			flag_MP_5->Play();
			break;
		case 5:
			flag_MP_6->Play();
			break;
		case 6:
			flag_MP_7->Play();
			break;
		case 7:
			flag_MP_8->Play();
			break;
		case 8:
			flag_MP_9->Play();
			break;
		case 9:
			flag_MP_10->Play();
			break;
		case 10:
			flag_MP_11->Play();
			break;
		case 11:
			flag_MP_12->Play();
			break;
		case 12:
			flag_MP_13->Play();
			break;
		case 13:
			flag_MP_14->Play();
			break;
		case 14:
			flag_MP_15->Play();
			break;
		case 15:
			flag_MP_16->Play();
			break;
		default:
			break;
		}
	}

	for (int a = 0; a < activeMediaPlayers.Num(); a++)
	{
		if (activeMediaPlayers[a])
		{
			switch (a)
			{
			case 0:
				grass_MP_1->Play();
				break;
			case 1:
				holeFromDown_MP->Play();
				break;
			case 2:
				holeFromLeft_MP->Play();
				break;
			case 3:
				holeFromRight_MP->Play();
				break;
			case 4:
				holeFromUp_MP->Play();
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				pondHorizontal_MP->Play();
				break;
			case 8:
				pondVerticleFlowingLeft_MP->Play();
				break;
			case 9:
				pondVerticleFlowingRight_MP->Play();
				break;
			case 10:
				waterfall_MP->Play();
				break;
			case 11:
				riverFlowingDown_MP_1->Play();
				break;
			case 12:
				riverFlowingDown_MP_2->Play();
				break;
			case 13:
				riverFlowingDown_MP_3->Play();
				break;
			case 14:
				riverFlowingLeft_MP_1->Play();
				break;
			case 15:
				riverFlowingLeft_MP_2->Play();
				break;
			case 16:
				riverFlowingLeft_MP_3->Play();
				break;
			case 17:
				riverFlowingRight_MP_1->Play();
				break;
			case 18:
				riverFlowingRight_MP_2->Play();
				break;
			case 19:
				riverFlowingRight_MP_3->Play();
				break;
			case 20:
				tree_MP_1->Play();
				break;
			case 21:
				tree_MP_2->Play();
				break;
			case 22:
				tree_MP_3->Play();
				break;
			case 23:
				tree_MP_4->Play();
				break;
			case 24:
				tree_MP_5->Play();
				break;
			case 25:
				riverTurning_MP_1->Play();
				break;
			case 26:
				riverTurning_MP_2->Play();
				break;
			case 27:
				riverTurning_MP_3->Play();
				break;
			case 28:
				riverTurning_MP_4->Play();
				break;
			case 29:
				break;
			case 30:
				grass_MP_1->Play();
				break;
			case 31:
				grass_MP_2->Play();
				break;
			case 32:
				grass_MP_3->Play();
				break;
			case 33:
				mountain_MP_1->Play();
				break;
			default:
				break;
			}
		}
	}
}

void AMyHUD::DisplayCurtains(int integerOne, bool goingToGame, bool displayResults)
{
	curtainClosingAudioComponent->SetVolumeMultiplier(1.0);
	curtainClosingAudioComponent->Play();

	if (goingToGame)
	{
		curtains_MP->OpenSource(curtains_IS);

		holesToGenerate = integerOne;

		curtainsSlateWidget = SNew(SCurtains)
			.OwningHUD(this)
			.curtains_VMUI(curtains_VMUI)
			.x(holesToGenerate)
			.curtainOpeningAudioComponent(curtainOpeningAudioComponent);

		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(slateWidgetContainerTwo, SWeakWidget));
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(slateWidgetContainerFour, SWeakWidget).PossiblyNullContent(curtainsSlateWidget.ToSharedRef()));
	}
	else
	{
		curtains_MP->OpenSource(curtains_IS);

		curtainsTwoSlateWidget = SNew(SCurtainsTwo)
			.OwningHUD(this)
			.curtains_VMUI(curtains_VMUI)
			.curtainOpeningAudioComponent(curtainOpeningAudioComponent);

		goToResults = displayResults;

		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(slateWidgetContainerThree, SWeakWidget));

		if (goToResults)
		{
			GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(slateWidgetContainerSix, SWeakWidget));
			//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "slateWidgetContainerSix added to hud");
		}
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(slateWidgetContainerFive, SWeakWidget).PossiblyNullContent(curtainsTwoSlateWidget.ToSharedRef()));
	}
}

void AMyHUD::ReturnToMainMenu()
{
	HouseKeeping();
	ResetRegenLevel();
	GenerateMainMenuBackground();

	GEngine->GameViewport->RemoveViewportWidgetContent(slateWidgetContainerTwo.ToSharedRef());

	mainMenuSlateWidget = SNew(SSArcadeModeTitleScreen)
		.OwningHUD(this)
		.playerOnePlayerController(playerOnePlayerController)
		.standardWorldContextObject(standardWorldContextObject)
		.backgroundMaterials(backgroundMaterials)
		.backgroundIsLargeTile(backgroundIsLargeTile)
		.displayResults(goToResults)
		.gameFrameColor_SMUI(gameFrameColor_SMUI)
		.hoverGrowAudioComponents(hoverGrowAudioComponents)
		.hoverShrinkAudioComponents(hoverShrinkAudioComponents)
		.windAudioComponents(windAudioComponents)
		.windWithSheepAudioComponents(windWithSheepAudioComponents)
		.riverAudioComponents(riverAudioComponents)
		.waterfallAudioComponents(waterfallAudioComponents)
		.purpleLullabyAudioComponents(purpleLullabyAudioComponents)
		.environmentAudio(environmentAudio);

	slateWidgetContainerThree->SetContent(mainMenuSlateWidget.ToSharedRef());

	if (goToResults)
	{
		resultsBlurSlateWidget = SNew(SResultsBlur)
			.OwningHUD(this)
			.rainstickAudioComponent(rainstickAudioComponent)
			.victoryAudioComponents(victoryAudioComponents)
			.newMaxLevel(newMaxLevel);
		//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "SResultsBlur initialized");

		slateWidgetContainerSix->SetContent(resultsBlurSlateWidget.ToSharedRef());
	}

	inGame = false;

	USaveGameOne* referenceInstance = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));
	double h = 1;

	if (referenceInstance->GetMaster() == 0 || referenceInstance->GetAtmosphere() == 0)
	{
		h = 0.001;
	}

	for (int a = 0; a < 2; a++)
	{
		windAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)2.0 * (double)atmosphereCoefficientOne) - (double)((double)((double)((double)2.0 * (double)atmosphereCoefficientOne) - ((double)2.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)masterCoefficientAOne))) * (double)h, (double)0.001, (double)2.0));
		windWithSheepAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)2.0 * (double)atmosphereCoefficientOne) - (double)((double)((double)((double)2.0 * (double)atmosphereCoefficientOne) - ((double)2.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)masterCoefficientAOne))) * (double)h, (double)0.001, (double)2.0));

		riverAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.33 * (double)atmosphereCoefficientTwo) - (double)((double)((double)((double)0.33 * (double)atmosphereCoefficientTwo) - ((double)0.33 * (double)destinationCoefficientThree)) * (double)((double)1 - (double)masterCoefficientATwo))) * (double)h, (double)0.001, (double)0.33));
		waterfallAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.8 * (double)atmosphereCoefficientThree) - (double)((double)((double)((double)0.8 * (double)atmosphereCoefficientThree) - ((double)0.8 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientAThree))) * (double)h, (double)0.001, (double)0.8));
	}
}

void AMyHUD::RemoveResultsBlur()
{
	GEngine->GameViewport->RemoveViewportWidgetContent(slateWidgetContainerSix.ToSharedRef());

	FInputModeUIOnly mainMenuInputMode = FInputModeUIOnly();
	mainMenuInputMode.SetWidgetToFocus(mainMenuSlateWidget);
	mainMenuInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	//mainMenuInputMode.SetHideCursorDuringCapture(false);
	playerOnePlayerController->SetInputMode(mainMenuInputMode);
	playerOnePlayerController->SetShowMouseCursor(true);
	FSlateApplication::Get().SetKeyboardFocus(mainMenuSlateWidget);
}

void AMyHUD::HideCurtains(bool toGame)
{
	if (toGame)
	{
		curtains_MP->Close();

		GEngine->GameViewport->RemoveViewportWidgetContent(slateWidgetContainerFour.ToSharedRef());
	}
	else
	{
		curtains_MP->Close();

		GEngine->GameViewport->RemoveViewportWidgetContent(slateWidgetContainerFive.ToSharedRef());

		if (goToResults)
		{
			FInputModeUIOnly resultsInputMode = FInputModeUIOnly();
			resultsInputMode.SetWidgetToFocus(resultsBlurSlateWidget);
			resultsInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			//mainMenuInputMode.SetHideCursorDuringCapture(false);
			playerOnePlayerController->SetInputMode(resultsInputMode);
			playerOnePlayerController->SetShowMouseCursor(true);
			FSlateApplication::Get().SetKeyboardFocus(resultsBlurSlateWidget);
		}
		else
		{
			FInputModeUIOnly mainMenuInputMode = FInputModeUIOnly();
			mainMenuInputMode.SetWidgetToFocus(mainMenuSlateWidget);
			mainMenuInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			//mainMenuInputMode.SetHideCursorDuringCapture(false);
			playerOnePlayerController->SetInputMode(mainMenuInputMode);
			playerOnePlayerController->SetShowMouseCursor(true);
			FSlateApplication::Get().SetKeyboardFocus(mainMenuSlateWidget);
		}
	}
}

void AMyHUD::MasterGenerateLevel(int numHoles)
{
	for (int a = 0; a < mediaPlayersToClose.Num(); a++)
	{
		mediaPlayersToClose[a]->Close();
	}
	mediaPlayersToClose.Empty();

	if (!inGame)
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(slateWidgetContainerThree.ToSharedRef());//does this destroy the menu, or only hide it. we are about to find out
		//delete loadingSlateWidget.Get(); this doesnt work, it throughs an acception access violation to address 0x0000000 supposedly RemoveViewportWidgetContent takes care of this
	}
	else
	{
		//GEngine->GameViewport->RemoveViewportWidgetContent(slateWidgetContainerTwo.ToSharedRef());//somehow removing slateWidget container 3 here was actually working fyi
		HouseKeeping();
		ResetRegenLevel();
	}

	inGame = true;

	for (int a = 0; a < 2; a++)
	{
		windAudioComponents[a]->Stop();
		windWithSheepAudioComponents[a]->Stop();
		riverAudioComponents[a]->Stop();
		waterfallAudioComponents[a]->Stop();
	}

	numberOfHoles = numHoles;

	GenerateLevel();

	for (int regenIndex = 0; regenIndex < regenerateLevel.Num(); regenIndex++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "REGENERATION TRIGGERED " + FString::FromInt(regenIndex) + " TIME(S)");
		HouseKeeping();

		if (regenIndex > 15)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "INFINITE LOOP TRIGGERED");
			return;
		}

		GenerateLevel();
	}
}

//the cherno says variables created at runtime do get garbage collected when the scope is breached, but javidx9 says pointers initiliazed at runtime certainly don't. so do I need to collect my own garbage?

void AMyHUD::GenerateHolePositions() //this function appears to function as expected, however as it stands a first of a pair can spawn in the back row, right next to the second of the pair in the first row
{
	int firstIndexOfCurrentPortionOfViableHolePositionsTempVar;
	int firstIndexOfCurrentPortionOfViableHolePositions = 0;
	int indexOfPreviousEvenHolePosition = 1;
	FVector2D centerOfRotation = FVector2D(8, 8);
	negativeOneZeroOrOne = FMath::RandRange(-1, 1);

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

	for (int a = 1; a < numberOfHoles + 1; a++)
	{
		int evenHoleRowCorrectionFigure = pow(2 - (indexOfPreviousEvenHolePosition % 2), (a - 1) % 2);

		firstIndexOfCurrentPortionOfViableHolePositionsTempVar = (arrOfViableHoleCoordinates.Num() / 2 / numberOfHoles * a + FMath::RoundHalfFromZero(((float)((arrOfViableHoleCoordinates.Num() / 2) % numberOfHoles) / (float)numberOfHoles) * a)) * 2;

		int currentHolePositionCoordinateIndex = (FMath::RandRange(0, ((firstIndexOfCurrentPortionOfViableHolePositionsTempVar - firstIndexOfCurrentPortionOfViableHolePositions) / evenHoleRowCorrectionFigure) - 1) * evenHoleRowCorrectionFigure) + firstIndexOfCurrentPortionOfViableHolePositions;

		test.Add(currentHolePositionCoordinateIndex);

		holePositions.Add(arrOfViableHoleCoordinates[currentHolePositionCoordinateIndex]);

		firstIndexOfCurrentPortionOfViableHolePositions = firstIndexOfCurrentPortionOfViableHolePositionsTempVar;

		if ((a - 1) % 2 == 0)
		{
			indexOfPreviousEvenHolePosition = currentHolePositionCoordinateIndex;
		}
	}

	if (negativeOneZeroOrOne != 0)
	{
		holeCoordinateOrientation = 0;

		// elsewhere switches based on integers need to be consecutive this switch statement might glitch out
		switch (negativeOneZeroOrOne)
		{
		case -1:
			for (int a = 0; a < holePositions.Num(); a++)
			{
				FVector2D adjustedHolePosition = holePositions[a] - centerOfRotation;

				holePositions[a] = FVector2D(adjustedHolePosition.Y + centerOfRotation.X, -1 * adjustedHolePosition.X + centerOfRotation.Y);
			}

			break;
		case 1:
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
	/*   nested TArray example
	nestedTArr.Add({ 1, 2, 3 });
	nestedTArr.Add({ 4, 5, 6 });
	nestedTArr[0].Add(7);*/
}

void AMyHUD::GenerateTrackShape()
{
	int cumulativeGroupingCoverage = 0;
	int countOfLoopsOne = 0;
	TArray<FVector2D> vector2DStorArrOne;
	TArray<int> intStorArrOne;
	int currentGroupSize;
	int unpairedHoleOrIntersectionDir = 0;
	FVector2D unpairedHoleOrIntersectionPos = FVector2D(0, 0);
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
	FVector2D currentFirstOfPairHoleOrIntersectionPosition;//X being first
	int currentTurnDistance;
	int previousTurnDistance;
	FVector2D currentIntersectionPos;
	TArray<int> pairStartsOnSameSide;
	TArray<int> intersectionDirStorArr;
	TArray<int> intersectionOrientationStorArr;// 0 for right, 1 for left, 2 for straight
	TArray<int> intersectionAjustmentWeights;// 1 for first of pair, 2 for second of pair, 0 for neither
	FVector2D firstOfPairIntersectionPos;
	FVector2D secondOfPairIntersectionPos;
	int firstOfPairIntersectionDir;
	int secondOfPairIntersectionDir;
	bool oneLastThing = false;
	int topLevelIndex;

	// grouping holes in sets of 2, 4, or 8
	while (numberOfHoles > cumulativeGroupingCoverage)
	{
		switch (FMath::RandRange((int32)0, (int32)2))
		{
		case 0:
			listOfHolePositionGroupings.Add(2);
			cumulativeGroupingCoverage += 2;
			break;
		case 1:
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
		for (int b = 0; b < listOfHolePositionGroupings[a]; b++)
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
	if (numberOfHoles > 12)
	{
		switch (negativeOneZeroOrOne)
		{
		case -1:
			arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[0][0][0] = 1;
			arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[0][listOfHolePositionGroupings.Num() - 1][listOfHolePositionGroupings[listOfHolePositionGroupings.Num() - 1] - 1] = 3;
			break;
		case 0:
			arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[0][0][0] = 4;
			arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[0][listOfHolePositionGroupings.Num() - 1][listOfHolePositionGroupings[listOfHolePositionGroupings.Num() - 1] - 1] = 2;
			break;
		case 1:
			arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[0][0][0] = 3;
			arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[0][listOfHolePositionGroupings.Num() - 1][listOfHolePositionGroupings[listOfHolePositionGroupings.Num() - 1] - 1] = 1;
			break;
		default:
			break;
		}
	}
	countOfLoopsOne = 0;

	// This is where the master loop containing the all of the remaining sub processes for laying out the track is declared and initialized. Once this is done looping and the resulting data has been packaged, the track is ready for assembly.
	// make sure to write code to continue laying out straight track if there is any distance remaining after all the turns are layed
	//so I think once this completes I will promote all the results into the same group on the 4th level and run the level stuff loop one last time. if it works out like this you can change the permanent storage to only have 1 group for the fourth level and beyond. this would restrict you to a maximum of 16 holes but thats probably enough
	// so I still need to promote the foundational groups to the final group in the fourth level, run all of this for said final group, then lay out the track from the completed structure to a designated track starting point
	for (int currentGroupIndex = 0; currentGroupIndex < listOfHolePositionGroupings.Num(); currentGroupIndex++)
	{
		currentGroupSize = listOfHolePositionGroupings[currentGroupIndex];

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
				differenceInPairPositionClampedX = FMath::Clamp(FMath::RoundToZero((float)differenceInPairPositionAbsolute.X / 2), 0, 2);
				differenceInPairPositionClampedY = FMath::Clamp(FMath::RoundToZero((float)differenceInPairPositionAbsolute.Y / 2), 0, 2);
				//this needs to be altered to take into consideration if firstOfPairIsAboveSecond and if firstOfPairIsEvenWithOrLeftOfSecond. if the pair starts on the same side and firstOfPairIsAboveSecond the verticleDistance must equal the differenceInPairPositionAbsolute unmodified. if the pair starts on different sides and firstOfPairIsEvenWithOrLeftOfSecond horizontalDistance must equal the differenceInPairPositionAbsolute + 1, if the pair starts on different sides and firstOfPairIsAboveSecond verticleDistance must equal the differenceInPairPositionAbsolute + 1

				currentFirstOfPairIsAboveSecond = firstOfPairIsAboveSecondArr[a - 1];
				currentFirstOfPairIsEvenWithOrLeftOfSecond = firstOfPairIsEvenWithOrLeftOfSecondArr[a - 1];

				if (currentFirstOfPairHoleDir == intersectionDirStorArr[a * 2 - 1])
				{
					pairStartsOnSameSide.Add(1);

					if (differenceInPairPositionClampedX <= differenceInPairPositionClampedY)
					{//do I need to add logic to force the quantity of turns to be > 2 past a certain quantity of distance? maybe only past a certain quantity of holes 
						availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Add(FMath::RandRange(firstOfPairIsEvenWithOrLeftOfSecondArr[a - 1], differenceInPairPositionClampedX) * 2 + 2);
					}
					else
					{
						availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Add(FMath::RandRange(firstOfPairIsEvenWithOrLeftOfSecondArr[a - 1], differenceInPairPositionClampedY) * 2 + 2);
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
					{//do I need to add logic to force the quantity of turns to be > 2 past a certain quantity of distance?
						availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Add(FMath::RandRange(FMath::Clamp(firstOfPairIsAboveSecondArr[a - 1] + firstOfPairIsEvenWithOrLeftOfSecondArr[a - 1], 0, 1), differenceInPairPositionClampedX) * 2 + 1);// I just took off a * 2 from the end of the first argument of the RandRange 01/17/24
					}
					else
					{
						availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Add(FMath::RandRange(FMath::Clamp(firstOfPairIsAboveSecondArr[a - 1] + firstOfPairIsEvenWithOrLeftOfSecondArr[a - 1], 0, 1), differenceInPairPositionClampedY) * 2 + 1);
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
				//for pairs starting on different sides have you decided how to determine which direction their intersection will face? yes they will take the direction of whichever side they are closest to unless firstOfPairIsAboveSecond or firstOfPairIsEvenWithOrLeftOfSecond
			}

			horizontalAndVerticleDistancesBetweenHolesOrIntersections[0] = horizontalDistancesBetweenHolesOrIntersections;
			horizontalAndVerticleDistancesBetweenHolesOrIntersections[1] = verticleDistancesBetweenHolesOrIntersections;

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
						whichOfEachPairsTurnsBecomesTheIntersection.Add(FMath::RandRange(1, 2));//maybe this should take into consideration whether the resulting intersection will be the first or second of its pair 
					}
					else
					{
						//Im excluding the first turn from the possibilities when theres more than one turn because that could be an issue - wait what?! how? fuck it Im just gonna pretend like I didnt see this
						//minus when intersectionAdjustmentWeights = 2, plus when intersectionAdjustmentWeights = 1
						//this works for both if weights and if not
						whichOfEachPairsTurnsBecomesTheIntersection.Add((currentATPPBOCLCG * (1 - (intersectionAjustmentWeights[a] % 2))) + (intersectionAjustmentWeights[a] % 2) + (-1 + ((intersectionAjustmentWeights[a] % 2) * 2)) * FMath::RandRange(0, FMath::DivideAndRoundDown(currentATPPBOCLCG - 2, 2)) * 2);
					}
				}
				else
				{// pairs starting on the same side
					if (firstOfPairIsAboveSecondArr[a])
					{
						whichOfEachPairsTurnsBecomesTheIntersection.Add(FMath::RandRange(1, currentATPPBOCLCG / 3));
					}
					else if (firstOfPairIsEvenWithOrLeftOfSecondArr[a])
					{
						whichOfEachPairsTurnsBecomesTheIntersection.Add(currentATPPBOCLCG - FMath::RandRange(0, 1));
					}
					else
					{
						if (intersectionAjustmentWeights[a] == 1)
						{// do I need to add logic to force the intersection deeper into the sequence of turns if there are 6 here? 
							whichOfEachPairsTurnsBecomesTheIntersection.Add(1 + FMath::RandRange(0, FMath::Clamp((currentATPPBOCLCG / 2) - 1, 0, 2)) * 2);
						}
						else
						{
							whichOfEachPairsTurnsBecomesTheIntersection.Add(currentATPPBOCLCG - FMath::RandRange(0, FMath::Clamp((currentATPPBOCLCG / 2) - 1, 0, 1)));
						}
					}
				}
			}//so Ive got 3 things to do! delete this when your done. FIRST! solve the problem where intersections can be placed so close to eachother. SECOND! solve the problem where there can be remaining verticle distance when pairStartsOnSameSide, firstOfPairIsRightOfAndEvenWithOrBelowSecond, and firstOfPairGetsAdjustment. THIRD! solve the problem where I have noticed when pairStartsOnDifferentSides the logic needs to be handled as if first of pair is above second when first of pair is level with second which is not the case for when pairStartsOnSameSide


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
					turnDistancesFromFirstOfPairStorArr.Add((relevantHorizontalAndVerticleDistances[a % 2] / amountOfTurnsPerDistance[a % 2]) * FMath::RoundHalfFromZero((float)a / 2.0f) + FMath::RoundHalfFromZero(((float)(relevantHorizontalAndVerticleDistances[a % 2] % amountOfTurnsPerDistance[a % 2]) / (float)amountOfTurnsPerDistance[a % 2]) * FMath::RoundHalfFromZero((float)a / 2.0f)));
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
				currentIntersectionPos = firstOfPairHoleOrIntersectionPosStorArr[currentPairIndex];
				//so now all I have to do today is finish this code section, and change the firstOfPairIsAboveSecond and firstOfPairIsEvenWithOrLeftOfSecond calculation to on this level after this. can you interweave adjusting the intersection position? come to think of it that will need to occur before calculating firstOfPairIsAboveSecond and firstOfPairIsEvenWithOrLeftOfSecond

				currentTurnDistance = turnDistancesFromFirstOfPairStorArr[whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] - 1];

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
				//Ive noticed in a particular case in my photos the intersection position was incorrect. I had not expected that at all, could errors here actually be occuring frequently?

				switch (firstOfPairHoleDirStorArr[currentPairIndex])
				{
				case 1:
					if (firstOfPairIsAboveSecondArr[currentPairIndex])//you still need to adjust how horizontal and verticle distances are calculated to account for if firstOfPairIsAboveSecond or if firstOfPairIsEvenWithOrLeftOfSecond
					{
						if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
						{
							currentIntersectionPos.X -= previousTurnDistance;
							currentIntersectionPos.Y -= currentTurnDistance;
						}
						else
						{
							currentIntersectionPos.X -= currentTurnDistance;
							currentIntersectionPos.Y -= previousTurnDistance;
						}

						vector2DStorArrOne.Add(currentIntersectionPos);
					}
					else if (firstOfPairIsEvenWithOrLeftOfSecondArr[currentPairIndex])
					{
						if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
						{
							currentIntersectionPos.X += previousTurnDistance;
							currentIntersectionPos.Y += currentTurnDistance;
						}
						else
						{
							currentIntersectionPos.X += currentTurnDistance;
							currentIntersectionPos.Y += previousTurnDistance;
						}

						vector2DStorArrOne.Add(currentIntersectionPos);
					}
					else
					{
						if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
						{
							currentIntersectionPos.X -= previousTurnDistance;
							currentIntersectionPos.Y += currentTurnDistance;
						}
						else
						{
							currentIntersectionPos.X -= currentTurnDistance;
							currentIntersectionPos.Y += previousTurnDistance;
						}

						vector2DStorArrOne.Add(currentIntersectionPos);
					}

					break;
				case 2:
					if (firstOfPairIsAboveSecondArr[currentPairIndex])
					{
						if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
						{
							currentIntersectionPos.X -= currentTurnDistance;
							currentIntersectionPos.Y += previousTurnDistance;
						}
						else
						{
							currentIntersectionPos.X -= previousTurnDistance;
							currentIntersectionPos.Y += currentTurnDistance;
						}

						vector2DStorArrOne.Add(currentIntersectionPos);
					}
					else if (firstOfPairIsEvenWithOrLeftOfSecondArr[currentPairIndex])
					{
						if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
						{
							currentIntersectionPos.X += currentTurnDistance;
							currentIntersectionPos.Y -= previousTurnDistance;
						}
						else
						{
							currentIntersectionPos.X += previousTurnDistance;
							currentIntersectionPos.Y -= currentTurnDistance;
						}

						vector2DStorArrOne.Add(currentIntersectionPos);
					}
					else
					{
						if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
						{
							currentIntersectionPos.X += currentTurnDistance;
							currentIntersectionPos.Y += previousTurnDistance;
						}
						else
						{
							currentIntersectionPos.X += previousTurnDistance;
							currentIntersectionPos.Y += currentTurnDistance;
						}

						vector2DStorArrOne.Add(currentIntersectionPos);
					}

					break;
				case 3:
					if (firstOfPairIsAboveSecondArr[currentPairIndex])
					{
						if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
						{
							currentIntersectionPos.X += previousTurnDistance;
							currentIntersectionPos.Y += currentTurnDistance;
						}
						else
						{
							currentIntersectionPos.X += currentTurnDistance;
							currentIntersectionPos.Y += previousTurnDistance;
						}

						vector2DStorArrOne.Add(currentIntersectionPos);
					}
					else if (firstOfPairIsEvenWithOrLeftOfSecondArr[currentPairIndex])
					{
						if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
						{
							currentIntersectionPos.X -= previousTurnDistance;
							currentIntersectionPos.Y -= currentTurnDistance;
						}
						else
						{
							currentIntersectionPos.X -= currentTurnDistance;
							currentIntersectionPos.Y -= previousTurnDistance;
						}

						vector2DStorArrOne.Add(currentIntersectionPos);
					}
					else
					{
						if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
						{
							currentIntersectionPos.X += previousTurnDistance;
							currentIntersectionPos.Y -= currentTurnDistance;
						}
						else
						{
							currentIntersectionPos.X += currentTurnDistance;
							currentIntersectionPos.Y -= previousTurnDistance;
						}

						vector2DStorArrOne.Add(currentIntersectionPos);
					}

					break;
				case 4:
					if (firstOfPairIsAboveSecondArr[currentPairIndex])
					{
						if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
						{
							currentIntersectionPos.X += currentTurnDistance;
							currentIntersectionPos.Y -= previousTurnDistance;
						}
						else
						{
							currentIntersectionPos.X += previousTurnDistance;
							currentIntersectionPos.Y -= currentTurnDistance;
						}

						vector2DStorArrOne.Add(currentIntersectionPos);
					}
					else if (firstOfPairIsEvenWithOrLeftOfSecondArr[currentPairIndex])
					{
						if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
						{
							currentIntersectionPos.X -= currentTurnDistance;
							currentIntersectionPos.Y += previousTurnDistance;
						}
						else
						{
							currentIntersectionPos.X -= previousTurnDistance;
							currentIntersectionPos.Y += currentTurnDistance;
						}

						vector2DStorArrOne.Add(currentIntersectionPos);
					}
					else
					{
						if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
						{
							currentIntersectionPos.X -= currentTurnDistance;
							currentIntersectionPos.Y -= previousTurnDistance;
						}
						else
						{
							currentIntersectionPos.X -= previousTurnDistance;
							currentIntersectionPos.Y -= currentTurnDistance;
						}

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
					case 1:
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
					case 2:
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
					case 3:
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
					case 4:
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
				case 1:
					vector2DStorArrOne.Add(FVector2D(unpairedHoleOrIntersectionPos.X, unpairedHoleOrIntersectionPos.Y + 1));
					break;
				case 2:
					vector2DStorArrOne.Add(FVector2D(unpairedHoleOrIntersectionPos.X + 1, unpairedHoleOrIntersectionPos.Y));
					break;
				case 3:
					vector2DStorArrOne.Add(FVector2D(unpairedHoleOrIntersectionPos.X, unpairedHoleOrIntersectionPos.Y - 1));
					break;
				case 4:
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

				firstOfPairIsAboveSecondAllPairs[currentLevelIndex][currentGroupIndex].Add(0);
				firstOfPairIsEvenWithOrLeftOfSecondAllPairs[currentLevelIndex][currentGroupIndex].Add(0);//just after the intersectionadjustments block if there is an unpaired intersection on the next level the level a 0 is added to the adjustment weights array

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

			//currently intersections can still be sandwiched together because im not checking which side of the pair needs the adjustment most MAYBE SOLVED further testing required
			// I have noticed when pairStartsOnDifferentSides the logic needs to be handled as if first of pair is above second when first of pair is level with second which is not the case for when pairStartsOnSameSide MAYBE SOLVED further testing required
			//for all first of pair starts on different side then second in this section should I add logic to make the adjustment go to the intersection closest to its side when one intersection is considerably closer to the middle? this would need to include a check to make sure horizontal distance is greater than 1

			if (vector2DStorArrOne.Num() > 1)
			{
				for (int currentPair = 1; currentPair <= vector2DStorArrOne.Num() / 2; currentPair++)
				{//go through and change the below variables from arrays to single variables if it turns out you aren't using modulo to divine the appropriate index anywhere
					firstOfPairIntersectionPos = vector2DStorArrOne[currentPair * 2 - 2];
					secondOfPairIntersectionPos = vector2DStorArrOne[currentPair * 2 - 1];
					firstOfPairIntersectionDir = intersectionDirStorArr[currentPair * 2 - 2];
					secondOfPairIntersectionDir = intersectionDirStorArr[currentPair * 2 - 1];
					differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
					differenceInPairPositionAbsolute = differenceInPairPosition.GetAbs();

					if (abs(firstOfPairIntersectionDir - secondOfPairIntersectionDir) == 2)
					{//this runs when the current pair of intersections aren't just on different sides but on opposite sides. this currently only works with intersections, I have not written the solution to this problem for holes
						intersectionDirStorArr[currentPair * 2 - 2] = FMath::Clamp((firstOfPairIntersectionDir + 1) % 5, 1, 4);
						intersectionAjustmentWeights.Add(3);

						switch (firstOfPairIntersectionDir)
						{
						case 1:
							firstOfPairIntersectionPos.Y += 1;
							vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
							differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;

							if (differenceInPairPosition.X > -1)
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
						case 2:
							firstOfPairIntersectionPos.X += 1;
							vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
							differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;

							if (differenceInPairPosition.Y < 1)
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
						case 3:
							firstOfPairIntersectionPos.Y -= 1;
							vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
							differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;

							if (differenceInPairPosition.X < 1)
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
						case 4:
							firstOfPairIntersectionPos.X -= 1;
							vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
							differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;

							if (differenceInPairPosition.Y > -1)
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
							if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
							{
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
									secondOfPairIntersectionPos.Y += extentOfAdjustment;

									vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
									intersectionAjustmentWeights.Add(2);
								}
								else
								{
									if (FMath::RandRange(0, 1) && differenceInPairPosition.Y > -2)
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
							}
							else
							{
								if (differenceInPairPosition.Y > -1)
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
									secondOfPairIntersectionPos.X += extentOfAdjustment;

									vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
									intersectionAjustmentWeights.Add(2);
								}
								else
								{
									if (differenceInPairPositionAbsolute.X < 2 || differenceInPairPositionAbsolute.Y < 2)
									{
										if (differenceInPairPosition.Y < -1)
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
									else
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
											firstOfPairIntersectionPos.Y += extentOfAdjustment;
											vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
											intersectionAjustmentWeights.Add(1);
											differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
										}
									}

									if (differenceInPairPosition.Y > -1)
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
							}

							break;
						case 2:
							if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
							{
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
									secondOfPairIntersectionPos.X += extentOfAdjustment;
									vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
									intersectionAjustmentWeights.Add(2);
								}
								else
								{
									if (FMath::RandRange(0, 1) && differenceInPairPosition.X > -2)
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
							}
							else
							{
								if (differenceInPairPosition.X > -1)
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
									secondOfPairIntersectionPos.Y -= extentOfAdjustment;
									vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
									intersectionAjustmentWeights.Add(2);
								}
								else
								{
									if (differenceInPairPositionAbsolute.X < 2 || differenceInPairPositionAbsolute.Y < 2)
									{
										if (differenceInPairPosition.X < -1)
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
									else
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
											firstOfPairIntersectionPos.X += extentOfAdjustment;
											vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
											intersectionAjustmentWeights.Add(1);
											differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
										}
									}
								}

								if (differenceInPairPosition.X > -1)
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
							if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
							{
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
									secondOfPairIntersectionPos.Y -= extentOfAdjustment;
									vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
									intersectionAjustmentWeights.Add(2);
								}
								else
								{
									if (FMath::RandRange(0, 1) && differenceInPairPosition.Y < 2)
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
							}
							else
							{
								if (differenceInPairPosition.Y < 1)
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
									secondOfPairIntersectionPos.X -= extentOfAdjustment;
									vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
									intersectionAjustmentWeights.Add(2);
								}
								else
								{
									if (differenceInPairPositionAbsolute.X < 2 || differenceInPairPositionAbsolute.Y < 2)
									{
										if (differenceInPairPosition.Y > 1)
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
									else
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
											firstOfPairIntersectionPos.Y -= extentOfAdjustment;
											vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
											intersectionAjustmentWeights.Add(1);
											differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
										}
									}
								}

								if (differenceInPairPosition.Y < 1)
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
							if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
							{
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
									secondOfPairIntersectionPos.X -= extentOfAdjustment;
									vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
									intersectionAjustmentWeights.Add(2);
								}
								else
								{
									if (FMath::RandRange(0, 1) && differenceInPairPosition.X < 2)
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
							}
							else
							{
								if (differenceInPairPosition.X < 1)
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
									secondOfPairIntersectionPos.Y += extentOfAdjustment;
									vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
									intersectionAjustmentWeights.Add(2);
								}
								else
								{
									if (differenceInPairPositionAbsolute.X < 2 || differenceInPairPositionAbsolute.Y < 2)
									{
										if (differenceInPairPosition.X > 1)
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
									else
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
											firstOfPairIntersectionPos.X -= extentOfAdjustment;
											vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
											intersectionAjustmentWeights.Add(1);
											differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
										}
									}
								}

								if (differenceInPairPosition.X < 1)
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

			adjustmentsAppliedToEachIntersection[currentLevelIndex + 1][currentGroupIndex] = intersectionAjustmentWeights;
			firstOfPairIsAboveSecondAllPairs[currentLevelIndex + 1][currentGroupIndex] = firstOfPairIsAboveSecondArr;
			firstOfPairIsEvenWithOrLeftOfSecondAllPairs[currentLevelIndex + 1][currentGroupIndex] = firstOfPairIsEvenWithOrLeftOfSecondArr;


			// this is the pile of arrays and misc which needs to get reset between every level
			horizontalAndVerticleDistancesBetweenHolesOrIntersections[0].Empty();
			horizontalAndVerticleDistancesBetweenHolesOrIntersections[1].Empty();

			horizontalDistancesBetweenHolesOrIntersections.Empty();
			verticleDistancesBetweenHolesOrIntersections.Empty();

			availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Empty();

			whichOfEachPairsTurnsBecomesTheIntersection.Empty();

			firstOfPairHoleOrIntersectionPosStorArr.Empty();
			firstOfPairHoleDirStorArr.Empty();

			pairStartsOnSameSide.Empty();

			intersectionOrientationStorArr.Empty();
		}
	}

	//here all of the resulting intersections from the foundational groupings are being reorganized into one final group on the 4th level
	vector2DStorArrOne.Empty();
	intersectionDirStorArr.Empty();

	for (int currentGroupIndex = 0; currentGroupIndex < listOfHolePositionGroupings.Num(); currentGroupIndex++)
	{
		topLevelIndex = FMath::Clamp(FMath::RoundHalfFromZero((float)listOfHolePositionGroupings[currentGroupIndex] / 2.0f), 1, 3);
		vector2DStorArrOne.Add(holeAndIntersectionPositions[topLevelIndex][currentGroupIndex][0]);
		intersectionDirStorArr.Add(arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[topLevelIndex][currentGroupIndex][0]);
	}
	holeAndIntersectionPositions[4][0] = vector2DStorArrOne;
	arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[4][0] = intersectionDirStorArr;
	currentGroupSize = vector2DStorArrOne.Num();

	//final group of intersections gets adjusted, and firstOfPairIsAboveSecond and firstOfPairIsEvenWithOrLeftOfSecond are calculated
	intersectionAjustmentWeights.Empty();
	firstOfPairIsAboveSecondArr.Empty();
	firstOfPairIsEvenWithOrLeftOfSecondArr.Empty();

	if (vector2DStorArrOne.Num() > 1)
	{
		for (int currentPair = 1; currentPair <= vector2DStorArrOne.Num() / 2; currentPair++)
		{//go through and change the below variables from arrays to single variables if it turns out you aren't using modulo to divine the appropriate index anywhere
			firstOfPairIntersectionPos = vector2DStorArrOne[currentPair * 2 - 2];
			secondOfPairIntersectionPos = vector2DStorArrOne[currentPair * 2 - 1];
			firstOfPairIntersectionDir = intersectionDirStorArr[currentPair * 2 - 2];
			secondOfPairIntersectionDir = intersectionDirStorArr[currentPair * 2 - 1];
			differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
			differenceInPairPositionAbsolute = differenceInPairPosition.GetAbs();

			if (abs(firstOfPairIntersectionDir - secondOfPairIntersectionDir) == 2)
			{//this runs when the current pair of intersections aren't just on different sides but on opposite sides. this currently only works with intersections, I have not written the solution to this problem for holes
				intersectionDirStorArr[currentPair * 2 - 2] = FMath::Clamp((firstOfPairIntersectionDir + 1) % 5, 1, 4);
				intersectionAjustmentWeights.Add(3);

				switch (firstOfPairIntersectionDir)
				{
				case 1:
					firstOfPairIntersectionPos.Y += 1;
					vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
					differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;

					if (differenceInPairPosition.X > -1)
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
				case 2:
					firstOfPairIntersectionPos.X += 1;
					vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
					differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;

					if (differenceInPairPosition.Y < 1)
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
				case 3:
					firstOfPairIntersectionPos.Y -= 1;
					vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
					differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;

					if (differenceInPairPosition.X < 1)
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
				case 4:
					firstOfPairIntersectionPos.X -= 1;
					vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
					differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;

					if (differenceInPairPosition.Y > -1)
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
					if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
					{
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
							secondOfPairIntersectionPos.Y += extentOfAdjustment;

							vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
							intersectionAjustmentWeights.Add(2);
						}
						else
						{
							if (FMath::RandRange(0, 1) && differenceInPairPosition.Y > -2)
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
					}
					else
					{
						if (differenceInPairPosition.Y > -1)
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
							secondOfPairIntersectionPos.X += extentOfAdjustment;

							vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
							intersectionAjustmentWeights.Add(2);
						}
						else
						{
							if (differenceInPairPositionAbsolute.X < 2 || differenceInPairPositionAbsolute.Y < 2)
							{
								if (differenceInPairPosition.Y < -1)
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
							else
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
									firstOfPairIntersectionPos.Y += extentOfAdjustment;
									vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
									intersectionAjustmentWeights.Add(1);
									differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
								}
							}

							if (differenceInPairPosition.Y > -1)
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
					}

					break;
				case 2:
					if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
					{
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
							secondOfPairIntersectionPos.X += extentOfAdjustment;
							vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
							intersectionAjustmentWeights.Add(2);
						}
						else
						{
							if (FMath::RandRange(0, 1) && differenceInPairPosition.X > -2)
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
					}
					else
					{
						if (differenceInPairPosition.X > -1)
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
							secondOfPairIntersectionPos.Y -= extentOfAdjustment;
							vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
							intersectionAjustmentWeights.Add(2);
						}
						else
						{
							if (differenceInPairPositionAbsolute.X < 2 || differenceInPairPositionAbsolute.Y < 2)
							{
								if (differenceInPairPosition.X < -1)
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
							else
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
									firstOfPairIntersectionPos.X += extentOfAdjustment;
									vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
									intersectionAjustmentWeights.Add(1);
									differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
								}
							}

							if (differenceInPairPosition.X > -1)
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
					}

					break;
				case 3:
					if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
					{
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
							secondOfPairIntersectionPos.Y -= extentOfAdjustment;
							vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
							intersectionAjustmentWeights.Add(2);
						}
						else
						{
							if (FMath::RandRange(0, 1) && differenceInPairPosition.Y < 2)
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
					}
					else
					{
						if (differenceInPairPosition.Y < 1)
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
							secondOfPairIntersectionPos.X -= extentOfAdjustment;
							vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
							intersectionAjustmentWeights.Add(2);
						}
						else
						{
							if (differenceInPairPositionAbsolute.X < 2 || differenceInPairPositionAbsolute.Y < 2)
							{
								if (differenceInPairPosition.Y > 1)
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
							else
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
									firstOfPairIntersectionPos.Y -= extentOfAdjustment;
									vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
									intersectionAjustmentWeights.Add(1);
									differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
								}
							}

							if (differenceInPairPosition.Y < 1)
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
					}

					break;
				case 4:
					if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
					{
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
							secondOfPairIntersectionPos.X -= extentOfAdjustment;
							vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
							intersectionAjustmentWeights.Add(2);
						}
						else
						{
							if (FMath::RandRange(0, 1) && differenceInPairPosition.X < 2)
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
					}
					else
					{
						if (differenceInPairPosition.X < 1)
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
							secondOfPairIntersectionPos.Y += extentOfAdjustment;
							vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
							intersectionAjustmentWeights.Add(2);
						}
						else
						{
							if (differenceInPairPositionAbsolute.X < 2 || differenceInPairPositionAbsolute.Y < 2)
							{
								if (differenceInPairPosition.X > 1)
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
							else
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
									firstOfPairIntersectionPos.X -= extentOfAdjustment;
									vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
									intersectionAjustmentWeights.Add(1);
									differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
								}
							}

							if (differenceInPairPosition.X < 1)
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
	}

	adjustmentsAppliedToEachIntersection[4][0] = intersectionAjustmentWeights;//does the level here need to be 5 or 4? I think 4 is correct
	firstOfPairIsAboveSecondAllPairs[4][0] = firstOfPairIsAboveSecondArr;
	firstOfPairIsEvenWithOrLeftOfSecondAllPairs[4][0] = firstOfPairIsEvenWithOrLeftOfSecondArr;

	if (currentGroupSize == 1)
	{
		currentGroupSize = 0;
	}

	for (int currentLevelIndex = 4; currentLevelIndex <= FMath::Clamp(FMath::RoundHalfFromZero((float)currentGroupSize / 2.0f), 0, 3) + 3; currentLevelIndex++)
	{
		if (intersectionDirStorArr.Num() % 2 == 1)
		{
			unpairedHoleOrIntersectionDir = intersectionDirStorArr[intersectionDirStorArr.Num() - 1];
			unpairedHoleOrIntersectionPos = vector2DStorArrOne[vector2DStorArrOne.Num() - 1];
		}

		//amount of turns for each pair as well as horizontal and verticle distance between pairs are determined
		for (int a = 1; a <= intersectionDirStorArr.Num() / 2; a++)//this won't run if there is only one element in the current group
		{
			currentFirstOfPairHoleDir = intersectionDirStorArr[a * 2 - 2];
			firstOfPairHoleDirStorArr.Add(currentFirstOfPairHoleDir);
			firstOfPairHoleOrIntersectionPosStorArr.Add(vector2DStorArrOne[a * 2 - 2]);

			differenceInPairPosition = firstOfPairHoleOrIntersectionPosStorArr[a - 1] - vector2DStorArrOne[a * 2 - 1];
			differenceInPairPositionAbsolute = differenceInPairPosition.GetAbs();
			differenceInPairPositionClampedX = FMath::Clamp(FMath::RoundToZero((float)differenceInPairPositionAbsolute.X / 2), 0, 2);
			differenceInPairPositionClampedY = FMath::Clamp(FMath::RoundToZero((float)differenceInPairPositionAbsolute.Y / 2), 0, 2);

			currentFirstOfPairIsAboveSecond = firstOfPairIsAboveSecondArr[a - 1];
			currentFirstOfPairIsEvenWithOrLeftOfSecond = firstOfPairIsEvenWithOrLeftOfSecondArr[a - 1];

			if (currentFirstOfPairHoleDir == intersectionDirStorArr[a * 2 - 1])
			{
				pairStartsOnSameSide.Add(1);

				if (differenceInPairPositionClampedX <= differenceInPairPositionClampedY)
				{//do I need to add logic to force the quantity of turns to be > 2 past a certain quantity of distance? maybe only past a certain quantity of holes 
					availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Add(FMath::RandRange(firstOfPairIsEvenWithOrLeftOfSecondArr[a - 1], differenceInPairPositionClampedX) * 2 + 2);
				}
				else
				{
					availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Add(FMath::RandRange(firstOfPairIsEvenWithOrLeftOfSecondArr[a - 1], differenceInPairPositionClampedY) * 2 + 2);
				}

				if (currentFirstOfPairIsAboveSecond)
				{
					switch (currentFirstOfPairHoleDir % 2)
					{
					case 0:
						horizontalDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.Y);
						verticleDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.X - 1);
						break;
					case 1:
						horizontalDistancesBetweenHolesOrIntersections.Add(differenceInPairPositionAbsolute.X);
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
			{
				pairStartsOnSameSide.Add(0);

				if (differenceInPairPositionClampedX <= differenceInPairPositionClampedY)
				{//do I need to add logic to force the quantity of turns to be > 2 past a certain quantity of distance?
					availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Add(FMath::RandRange(FMath::Clamp(firstOfPairIsAboveSecondArr[a - 1] + firstOfPairIsEvenWithOrLeftOfSecondArr[a - 1], 0, 1), differenceInPairPositionClampedX) * 2 + 1);
				}
				else
				{
					availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Add(FMath::RandRange(FMath::Clamp(firstOfPairIsAboveSecondArr[a - 1] + firstOfPairIsEvenWithOrLeftOfSecondArr[a - 1], 0, 1), differenceInPairPositionClampedY) * 2 + 1);
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
		}

		horizontalAndVerticleDistancesBetweenHolesOrIntersections[0] = horizontalDistancesBetweenHolesOrIntersections;
		horizontalAndVerticleDistancesBetweenHolesOrIntersections[1] = verticleDistancesBetweenHolesOrIntersections;

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
					whichOfEachPairsTurnsBecomesTheIntersection.Add(FMath::RandRange(1, 2));//maybe this should take into consideration whether the resulting intersection will be the first or second of its pair 
				}
				else
				{
					//Im excluding the first turn from the possibilities when theres more than one turn because that could be an issue - wait what?! how? fuck it Im just gonna pretend like I didnt see this
					//minus when intersectionAdjustmentWeights = 2, plus when intersectionAdjustmentWeights = 1
					//this works for both if weights and if not
					whichOfEachPairsTurnsBecomesTheIntersection.Add((currentATPPBOCLCG * (1 - (intersectionAjustmentWeights[a] % 2))) + (intersectionAjustmentWeights[a] % 2) + (-1 + ((intersectionAjustmentWeights[a] % 2) * 2)) * FMath::RandRange(0, FMath::DivideAndRoundDown(currentATPPBOCLCG - 2, 2)) * 2);
				}
			}
			else
			{// pairs starting on the same side
				if (firstOfPairIsAboveSecondArr[a])
				{
					whichOfEachPairsTurnsBecomesTheIntersection.Add(FMath::RandRange(1, currentATPPBOCLCG / 3));
				}
				else if (firstOfPairIsEvenWithOrLeftOfSecondArr[a])
				{
					whichOfEachPairsTurnsBecomesTheIntersection.Add(currentATPPBOCLCG - FMath::RandRange(0, 1));
				}
				else
				{
					if (intersectionAjustmentWeights[a] == 1)
					{// do I need to add logic to force the intersection deeper into the sequence of turns if there are 6 here? 
						whichOfEachPairsTurnsBecomesTheIntersection.Add(1 + FMath::RandRange(0, FMath::Clamp((currentATPPBOCLCG / 2) - 1, 0, 2)) * 2);
					}
					else
					{
						whichOfEachPairsTurnsBecomesTheIntersection.Add(currentATPPBOCLCG - FMath::RandRange(0, FMath::Clamp((currentATPPBOCLCG / 2) - 1, 0, 1)));
					}
				}
			}
		}//so Ive got 3 things to do! delete this when your done. FIRST! solve the problem where intersections can be placed so close to eachother. SECOND! solve the problem where there can be remaining verticle distance when pairStartsOnSameSide, firstOfPairIsRightOfAndEvenWithOrBelowSecond, and firstOfPairGetsAdjustment. THIRD! solve the problem where I have noticed when pairStartsOnDifferentSides the logic needs to be handled as if first of pair is above second when first of pair is level with second which is not the case for when pairStartsOnSameSide


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
				turnDistancesFromFirstOfPairStorArr.Add((relevantHorizontalAndVerticleDistances[a % 2] / amountOfTurnsPerDistance[a % 2]) * FMath::RoundHalfFromZero((float)a / 2.0f) + FMath::RoundHalfFromZero(((float)(relevantHorizontalAndVerticleDistances[a % 2] % amountOfTurnsPerDistance[a % 2]) / (float)amountOfTurnsPerDistance[a % 2]) * FMath::RoundHalfFromZero((float)a / 2.0f)));
			}

			if (oneLastThing)
			{
				turnDistancesFromFirstOfPairStorArr.Add(relevantHorizontalAndVerticleDistances[0] - 1);
				oneLastThing = false;
			}

			turnAndIntersectionDistancesPerPair[currentLevelIndex][0][currentPair] = turnDistancesFromFirstOfPairStorArr;
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

					directionsOfTurns[currentLevelIndex][0][currentPair] = turnDirectionsStorArr;

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

					directionsOfTurns[currentLevelIndex][0][currentPair] = turnDirectionsStorArr;

					turnDirectionsStorArr.Empty();
				}
				else
				{
					for (int b = 0; b < currentATPPBOCLCG; b++)
					{
						turnDirectionsStorArr.Add(oneZeroAlternatingArr[b]);
					}

					turnDirectionsStorArr[whichOfEachPairsTurnsBecomesTheIntersection[currentPair] - 1] = 2;//is this - 1 correct? I think so..

					directionsOfTurns[currentLevelIndex][0][currentPair] = turnDirectionsStorArr;

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

					directionsOfTurns[currentLevelIndex][0][currentPair] = turnDirectionsStorArr;

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

					directionsOfTurns[currentLevelIndex][0][currentPair] = turnDirectionsStorArr;

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

					directionsOfTurns[currentLevelIndex][0][currentPair] = turnDirectionsStorArr;

					turnDirectionsStorArr.Empty();
				}
			}
		}

		// determining the intersection location. I will also need to rework the first section of this master loop and at the very least determine firstOfPairIsAboveSecond and firstOfPairIsEvenWithOrLeftOfSecond here. As apart of determining intersection Position I will also need to "reposition" the intersections of all future pairs which you will weight to recieve an in intersection in close proximity
		vector2DStorArrOne.Empty();

		for (int currentPairIndex = 0; currentPairIndex < availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Num(); currentPairIndex++)
		{
			turnDistancesFromFirstOfPairStorArr = turnAndIntersectionDistancesPerPair[currentLevelIndex][0][currentPairIndex];
			currentIntersectionPos = firstOfPairHoleOrIntersectionPosStorArr[currentPairIndex];

			currentTurnDistance = turnDistancesFromFirstOfPairStorArr[whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] - 1];

			if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] != 1)
			{
				previousTurnDistance = turnDistancesFromFirstOfPairStorArr[whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] - 2];//this should be a minus 2 
			}
			else
			{
				previousTurnDistance = 0;
			}

			switch (firstOfPairHoleDirStorArr[currentPairIndex])
			{
			case 1:
				if (firstOfPairIsAboveSecondArr[currentPairIndex])
				{
					if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
					{
						currentIntersectionPos.X -= previousTurnDistance;
						currentIntersectionPos.Y -= currentTurnDistance;
					}
					else
					{
						currentIntersectionPos.X -= currentTurnDistance;
						currentIntersectionPos.Y -= previousTurnDistance;
					}

					vector2DStorArrOne.Add(currentIntersectionPos);
				}
				else if (firstOfPairIsEvenWithOrLeftOfSecondArr[currentPairIndex])
				{
					if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
					{
						currentIntersectionPos.X += previousTurnDistance;
						currentIntersectionPos.Y += currentTurnDistance;
					}
					else
					{
						currentIntersectionPos.X += currentTurnDistance;
						currentIntersectionPos.Y += previousTurnDistance;
					}

					vector2DStorArrOne.Add(currentIntersectionPos);
				}
				else
				{
					if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
					{
						currentIntersectionPos.X -= previousTurnDistance;
						currentIntersectionPos.Y += currentTurnDistance;
					}
					else
					{
						currentIntersectionPos.X -= currentTurnDistance;
						currentIntersectionPos.Y += previousTurnDistance;
					}

					vector2DStorArrOne.Add(currentIntersectionPos);
				}

				break;
			case 2:
				if (firstOfPairIsAboveSecondArr[currentPairIndex])
				{
					if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
					{
						currentIntersectionPos.X -= currentTurnDistance;
						currentIntersectionPos.Y += previousTurnDistance;
					}
					else
					{
						currentIntersectionPos.X -= previousTurnDistance;
						currentIntersectionPos.Y += currentTurnDistance;
					}

					vector2DStorArrOne.Add(currentIntersectionPos);
				}
				else if (firstOfPairIsEvenWithOrLeftOfSecondArr[currentPairIndex])
				{
					if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
					{
						currentIntersectionPos.X += currentTurnDistance;
						currentIntersectionPos.Y -= previousTurnDistance;
					}
					else
					{
						currentIntersectionPos.X += previousTurnDistance;
						currentIntersectionPos.Y -= currentTurnDistance;
					}

					vector2DStorArrOne.Add(currentIntersectionPos);
				}
				else
				{
					if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
					{
						currentIntersectionPos.X += currentTurnDistance;
						currentIntersectionPos.Y += previousTurnDistance;
					}
					else
					{
						currentIntersectionPos.X += previousTurnDistance;
						currentIntersectionPos.Y += currentTurnDistance;
					}

					vector2DStorArrOne.Add(currentIntersectionPos);
				}

				break;
			case 3:
				if (firstOfPairIsAboveSecondArr[currentPairIndex])
				{
					if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
					{
						currentIntersectionPos.X += previousTurnDistance;
						currentIntersectionPos.Y += currentTurnDistance;
					}
					else
					{
						currentIntersectionPos.X += currentTurnDistance;
						currentIntersectionPos.Y += previousTurnDistance;
					}

					vector2DStorArrOne.Add(currentIntersectionPos);
				}
				else if (firstOfPairIsEvenWithOrLeftOfSecondArr[currentPairIndex])
				{
					if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
					{
						currentIntersectionPos.X -= previousTurnDistance;
						currentIntersectionPos.Y -= currentTurnDistance;
					}
					else
					{
						currentIntersectionPos.X -= currentTurnDistance;
						currentIntersectionPos.Y -= previousTurnDistance;
					}

					vector2DStorArrOne.Add(currentIntersectionPos);
				}
				else
				{
					if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
					{
						currentIntersectionPos.X += previousTurnDistance;
						currentIntersectionPos.Y -= currentTurnDistance;
					}
					else
					{
						currentIntersectionPos.X += currentTurnDistance;
						currentIntersectionPos.Y -= previousTurnDistance;
					}

					vector2DStorArrOne.Add(currentIntersectionPos);
				}

				break;
			case 4:
				if (firstOfPairIsAboveSecondArr[currentPairIndex])
				{
					if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
					{
						currentIntersectionPos.X += currentTurnDistance;
						currentIntersectionPos.Y -= previousTurnDistance;
					}
					else
					{
						currentIntersectionPos.X += previousTurnDistance;
						currentIntersectionPos.Y -= currentTurnDistance;
					}

					vector2DStorArrOne.Add(currentIntersectionPos);
				}
				else if (firstOfPairIsEvenWithOrLeftOfSecondArr[currentPairIndex])
				{
					if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
					{
						currentIntersectionPos.X -= currentTurnDistance;
						currentIntersectionPos.Y += previousTurnDistance;
					}
					else
					{
						currentIntersectionPos.X -= previousTurnDistance;
						currentIntersectionPos.Y += currentTurnDistance;
					}

					vector2DStorArrOne.Add(currentIntersectionPos);
				}
				else
				{
					if (whichOfEachPairsTurnsBecomesTheIntersection[currentPairIndex] % 2 == 1)
					{
						currentIntersectionPos.X -= currentTurnDistance;
						currentIntersectionPos.Y -= previousTurnDistance;
					}
					else
					{
						currentIntersectionPos.X -= previousTurnDistance;
						currentIntersectionPos.Y -= currentTurnDistance;
					}

					vector2DStorArrOne.Add(currentIntersectionPos);
				}

				break;
			default:
				break;
			}
		}
		turnDistancesFromFirstOfPairStorArr.Empty();
		intersectionDirStorArr.Empty();

		//calculating newly generated intersection's directions and orientations
		for (int currentIntersection = 0; currentIntersection < vector2DStorArrOne.Num(); currentIntersection++)
		{
			currentFirstOfPairIsAboveSecond = firstOfPairIsAboveSecondArr[currentIntersection];
			currentFirstOfPairIsEvenWithOrLeftOfSecond = firstOfPairIsEvenWithOrLeftOfSecondArr[currentIntersection];

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
				switch (firstOfPairHoleDirStorArr[currentIntersection])
				{
				case 1:
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
				case 2:
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
				case 3:
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
				case 4:
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
		{
			turnAndIntersectionDistancesPerPair[currentLevelIndex][0][availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Num()] = { 1 };
			directionsOfTurns[currentLevelIndex][0][availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Num()] = { 2 };

			switch (unpairedHoleOrIntersectionDir)
			{
			case 1:
				vector2DStorArrOne.Add(FVector2D(unpairedHoleOrIntersectionPos.X, unpairedHoleOrIntersectionPos.Y + 1));
				break;
			case 2:
				vector2DStorArrOne.Add(FVector2D(unpairedHoleOrIntersectionPos.X + 1, unpairedHoleOrIntersectionPos.Y));
				break;
			case 3:
				vector2DStorArrOne.Add(FVector2D(unpairedHoleOrIntersectionPos.X, unpairedHoleOrIntersectionPos.Y - 1));
				break;
			case 4:
				vector2DStorArrOne.Add(FVector2D(unpairedHoleOrIntersectionPos.X - 1, unpairedHoleOrIntersectionPos.Y));
				break;
			default:
				break;
			}

			intersectionDirStorArr.Add(unpairedHoleOrIntersectionDir);
			intersectionOrientationStorArr.Add(2);

			unpairedHoleOrIntersectionPos = FVector2D(0, 0);
			unpairedHoleOrIntersectionDir = 0;

			firstOfPairIsAboveSecondAllPairs[currentLevelIndex][0].Add(0);
			firstOfPairIsEvenWithOrLeftOfSecondAllPairs[currentLevelIndex][0].Add(0);
		}

		holeAndIntersectionPositions[currentLevelIndex + 1][0] = vector2DStorArrOne;
		arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[currentLevelIndex + 1][0] = intersectionDirStorArr;
		intersectionOrientationsPerGroupPerLevel[currentLevelIndex + 1][0] = intersectionOrientationStorArr;

		//select intersection position are adjusted and firstOfPairIsAboveSecond and firstOfPairIsEvenWithOrLeftOfSecond are written. It's likely adjustingIntersectionPos will cause problems but i will need to run the code a lot to find these issues. To achieve the adjustment I am not adjusting any vector2D's in permanent storage, but tracking which of all intersections are being ajdusted, and then in temporary storage I am adjusting the vector2DStorArrOne for the purpose of calculating the proceeding track and intersections. all of this means when I build the level I will have to inlcude a distinct functionality to extend an appropriately sized portion of track from any intersection bearing a weight
		intersectionAjustmentWeights.Empty();
		firstOfPairIsAboveSecondArr.Empty();
		firstOfPairIsEvenWithOrLeftOfSecondArr.Empty();

		if (vector2DStorArrOne.Num() > 1)
		{
			for (int currentPair = 1; currentPair <= vector2DStorArrOne.Num() / 2; currentPair++)
			{
				firstOfPairIntersectionPos = vector2DStorArrOne[currentPair * 2 - 2];
				secondOfPairIntersectionPos = vector2DStorArrOne[currentPair * 2 - 1];
				firstOfPairIntersectionDir = intersectionDirStorArr[currentPair * 2 - 2];
				secondOfPairIntersectionDir = intersectionDirStorArr[currentPair * 2 - 1];
				differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
				differenceInPairPositionAbsolute = differenceInPairPosition.GetAbs();

				if (abs(firstOfPairIntersectionDir - secondOfPairIntersectionDir) == 2)
				{//this runs when the current pair of intersections aren't just on different sides but on opposite sides. this currently only works with intersections, I have not written the solution to this problem for holes
					intersectionDirStorArr[currentPair * 2 - 2] = FMath::Clamp((firstOfPairIntersectionDir + 1) % 5, 1, 4);
					intersectionAjustmentWeights.Add(3);

					switch (firstOfPairIntersectionDir)
					{
					case 1:
						firstOfPairIntersectionPos.Y += 1;
						vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
						differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;

						if (differenceInPairPosition.X > -1)
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
					case 2:
						firstOfPairIntersectionPos.X += 1;
						vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
						differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;

						if (differenceInPairPosition.Y < 1)
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
					case 3:
						firstOfPairIntersectionPos.Y -= 1;
						vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
						differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;

						if (differenceInPairPosition.X < 1)
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
					case 4:
						firstOfPairIntersectionPos.X -= 1;
						vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
						differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;

						if (differenceInPairPosition.Y > -1)
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
						if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
						{
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
								secondOfPairIntersectionPos.Y += extentOfAdjustment;

								vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
								intersectionAjustmentWeights.Add(2);
							}
							else
							{
								if (FMath::RandRange(0, 1) && differenceInPairPosition.Y > -2)
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
						}
						else
						{
							if (differenceInPairPosition.Y > -1)
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
								secondOfPairIntersectionPos.X += extentOfAdjustment;

								vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
								intersectionAjustmentWeights.Add(2);
							}
							else
							{
								if (differenceInPairPositionAbsolute.X < 2 || differenceInPairPositionAbsolute.Y < 2)
								{
									if (differenceInPairPosition.Y < -1)
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
								else
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
										firstOfPairIntersectionPos.Y += extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(1);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
								}

								if (differenceInPairPosition.Y > -1)
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
						}

						break;
					case 2:
						if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
						{
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
								secondOfPairIntersectionPos.X += extentOfAdjustment;
								vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
								intersectionAjustmentWeights.Add(2);
							}
							else
							{
								if (FMath::RandRange(0, 1) && differenceInPairPosition.X > -2)
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
						}
						else
						{
							if (differenceInPairPosition.X > -1)
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
								secondOfPairIntersectionPos.Y -= extentOfAdjustment;
								vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
								intersectionAjustmentWeights.Add(2);
							}
							else
							{
								if (differenceInPairPositionAbsolute.X < 2 || differenceInPairPositionAbsolute.Y < 2)
								{
									if (differenceInPairPosition.X < -1)
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
								else
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
										firstOfPairIntersectionPos.X += extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(1);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
								}
							}

							if (differenceInPairPosition.X > -1)
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
						if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
						{
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
								secondOfPairIntersectionPos.Y -= extentOfAdjustment;
								vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
								intersectionAjustmentWeights.Add(2);
							}
							else
							{
								if (FMath::RandRange(0, 1) && differenceInPairPosition.Y < 2)
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
						}
						else
						{
							if (differenceInPairPosition.Y < 1)
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
								secondOfPairIntersectionPos.X -= extentOfAdjustment;
								vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
								intersectionAjustmentWeights.Add(2);
							}
							else
							{
								if (differenceInPairPositionAbsolute.X < 2 || differenceInPairPositionAbsolute.Y < 2)
								{
									if (differenceInPairPosition.Y > 1)
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
								else
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
										firstOfPairIntersectionPos.Y -= extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(1);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
								}
							}

							if (differenceInPairPosition.Y < 1)
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
						if (firstOfPairIntersectionDir == secondOfPairIntersectionDir)
						{
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
								secondOfPairIntersectionPos.X -= extentOfAdjustment;
								vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
								intersectionAjustmentWeights.Add(2);
							}
							else
							{
								if (FMath::RandRange(0, 1) && differenceInPairPosition.X < 2)
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
						}
						else
						{
							if (differenceInPairPosition.X < 1)
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
								secondOfPairIntersectionPos.Y += extentOfAdjustment;
								vector2DStorArrOne[currentPair * 2 - 1] = secondOfPairIntersectionPos;
								intersectionAjustmentWeights.Add(2);
							}
							else
							{
								if (differenceInPairPositionAbsolute.X < 2 || differenceInPairPositionAbsolute.Y < 2)
								{
									if (differenceInPairPosition.X > 1)
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
								else
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
										firstOfPairIntersectionPos.X -= extentOfAdjustment;
										vector2DStorArrOne[currentPair * 2 - 2] = firstOfPairIntersectionPos;
										intersectionAjustmentWeights.Add(1);
										differenceInPairPosition = firstOfPairIntersectionPos - secondOfPairIntersectionPos;
									}
								}
							}

							if (differenceInPairPosition.X < 1)
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

		adjustmentsAppliedToEachIntersection[currentLevelIndex + 1][0] = intersectionAjustmentWeights;
		firstOfPairIsAboveSecondAllPairs[currentLevelIndex + 1][0] = firstOfPairIsAboveSecondArr;
		firstOfPairIsEvenWithOrLeftOfSecondAllPairs[currentLevelIndex + 1][0] = firstOfPairIsEvenWithOrLeftOfSecondArr;


		// this is the pile of arrays and misc which needs to get reset between every level
		horizontalAndVerticleDistancesBetweenHolesOrIntersections[0].Empty();
		horizontalAndVerticleDistancesBetweenHolesOrIntersections[1].Empty();

		horizontalDistancesBetweenHolesOrIntersections.Empty();
		verticleDistancesBetweenHolesOrIntersections.Empty();

		availableTurnsPerPairBlockOfCurrentLevelCurrentGrouping.Empty();

		whichOfEachPairsTurnsBecomesTheIntersection.Empty();

		firstOfPairHoleOrIntersectionPosStorArr.Empty();
		firstOfPairHoleDirStorArr.Empty();

		pairStartsOnSameSide.Empty();

		intersectionOrientationStorArr.Empty();
	}
}

void AMyHUD::BuildLevel()
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
			 //***to correct for unforseen or downright tricky track overlap I could implement a regeneration array: an array of 225 bools which correspond to the tiles of the track board. when a piece of track is layed down check if theres already track there. if true regenerate everything, if false set to true *** this may be brunt but it will be an adequate solution as long as overlapping track is at least relatively uncommon; I envision overlapping trapping becoming increasingly common with increase in hole count.
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
	int topLevelIndex;
	int finalGroupingActive = 0;
	int adjustmentAppliedToCurrentIntersectionPair;

	//there can be remaining verticle distance when pairStartsOnSameSide, firstOfPairIsRightOfAndEvenWithOrBelowSecond, and firstOfPairGetsAdjustment. I still need to fix this
	//I just noticed when their facing opposite sides and the second of pair gets adjustment the adjustment goes verticle not horizontal. try to get a picture you didnt at first glance

	for (int currentGroupIndex = 0; currentGroupIndex <= listOfHolePositionGroupings.Num(); currentGroupIndex++)
	{
		if (currentGroupIndex == listOfHolePositionGroupings.Num())
		{
			currentGroupSize = listOfHolePositionGroupings.Num();
			currentGroupIndex = 0;
			finalGroupingActive = 1;

			if (currentGroupSize == 1)
			{
				currentGroupSize = 0;
			}
		}
		else
		{
			currentGroupSize = listOfHolePositionGroupings[currentGroupIndex];
		}

		intersectionAdjustmentTrackerArr = { 0, 0, 0, 0, 0, 0, 0, 0 };

		for (int currentLevelIndex = 0 + (4 * finalGroupingActive); currentLevelIndex <= FMath::Clamp(FMath::RoundHalfFromZero((float)currentGroupSize / 2.0f), 0, 3) - 1 + (4 * finalGroupingActive); currentLevelIndex++)
		{//since I will be determining the hole positions 
			topLevelIndex = currentLevelIndex;

			if (currentLevelIndex == 4)
			{
				for (int currentFirstOfPairIndex = 0; currentFirstOfPairIndex < holeAndIntersectionPositions[4][0].Num(); currentFirstOfPairIndex += 2)
				{
					adjustmentAppliedToCurrentIntersectionPair = adjustmentsAppliedToEachIntersection[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex / 2];

					if (adjustmentAppliedToCurrentIntersectionPair != 0)
					{
						if (adjustmentAppliedToCurrentIntersectionPair % 2 == 1)
						{
							currentFirstOfPairPosition = holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex];
							currentFirstOfPairDir = arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex];

							switch (currentFirstOfPairDir)
							{
							case 1:
								if (adjustmentAppliedToCurrentIntersectionPair == 3)
								{
									intersectionAdjustmentTrackerArr[currentFirstOfPairIndex] = 2;

									switch (currentFirstOfPairDir)
									{//this would need to have a case 3 if it's possible for this to occur twice in a row
									case 1:
										newTrackPos = currentFirstOfPairPosition + FVector2D(0, 1);

										convertedTrackPos.X = newTrackPos.X - 1;
										convertedTrackPos.Y = 15 - newTrackPos.Y;
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
										tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

										break;
									case 2:// I dont think this case can actually occur because if culminatingIntersectionDir == 2 adjustmentAppliedToCulminatingIntersection cannot equal 3
										newTrackPos = currentFirstOfPairPosition + FVector2D(1, 0);

										convertedTrackPos.X = newTrackPos.X - 1;
										convertedTrackPos.Y = 15 - newTrackPos.Y;
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;
										tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

										break;
									default:
										break;
									}
								}
								else
								{
									intersectionAdjustmentTrackerArr[currentFirstOfPairIndex] = 1;

									for (int a = 1; a <= extentOfAdjustment; a++)
									{
										newTrackPos = currentFirstOfPairPosition + FVector2D(a * (1 - (currentFirstOfPairDir % 2)), a * (currentFirstOfPairDir % 2));

										convertedTrackPos.X = newTrackPos.X - 1;
										convertedTrackPos.Y = 15 - newTrackPos.Y;
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2 - (currentFirstOfPairDir % 2);
										tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

									}
								}

								break;
							case 2:
								if (adjustmentAppliedToCurrentIntersectionPair == 3)
								{
									intersectionAdjustmentTrackerArr[currentFirstOfPairIndex] = 2;

									switch (currentFirstOfPairDir)
									{
									case 2:
										newTrackPos = currentFirstOfPairPosition + FVector2D(1, 0);

										convertedTrackPos.X = newTrackPos.X - 1;
										convertedTrackPos.Y = 15 - newTrackPos.Y;
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;
										tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

										break;
									case 3:
										newTrackPos = currentFirstOfPairPosition - FVector2D(0, 1);

										convertedTrackPos.X = newTrackPos.X - 1;
										convertedTrackPos.Y = 15 - newTrackPos.Y;
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;
										tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

										break;
									default:
										break;
									}
								}
								else
								{
									intersectionAdjustmentTrackerArr[currentFirstOfPairIndex] = 1;

									for (int a = 1; a <= extentOfAdjustment; a++)
									{
										newTrackPos = currentFirstOfPairPosition + FVector2D(a * (1 - (currentFirstOfPairDir % 2)), a * (currentFirstOfPairDir % 2) * -1);

										convertedTrackPos.X = newTrackPos.X - 1;
										convertedTrackPos.Y = 15 - newTrackPos.Y;
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2 - (currentFirstOfPairDir % 2);
										tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

									}
								}

								break;
							case 3:
								if (adjustmentAppliedToCurrentIntersectionPair == 3)
								{
									intersectionAdjustmentTrackerArr[currentFirstOfPairIndex] = 2;

									switch (currentFirstOfPairDir)
									{
									case 3:
										newTrackPos = currentFirstOfPairPosition - FVector2D(0, 1);

										convertedTrackPos.X = newTrackPos.X - 1;
										convertedTrackPos.Y = 15 - newTrackPos.Y;
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;
										tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

										break;
									case 4:
										newTrackPos = currentFirstOfPairPosition - FVector2D(1, 0);

										convertedTrackPos.X = newTrackPos.X - 1;
										convertedTrackPos.Y = 15 - newTrackPos.Y;
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
										tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

										break;
									default:
										break;
									}
								}
								else
								{
									intersectionAdjustmentTrackerArr[currentFirstOfPairIndex] = 1;

									for (int a = 1; a <= extentOfAdjustment; a++)
									{
										newTrackPos = currentFirstOfPairPosition + FVector2D(a * (-1 + (currentFirstOfPairDir % 2)), a * (currentFirstOfPairDir % 2) * -1);//does this -1 work here as written?

										convertedTrackPos.X = newTrackPos.X - 1;
										convertedTrackPos.Y = 15 - newTrackPos.Y;
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2 - (currentFirstOfPairDir % 2);
										tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

									}
								}

								break;
							case 4:
								if (adjustmentAppliedToCurrentIntersectionPair == 3)
								{
									intersectionAdjustmentTrackerArr[currentFirstOfPairIndex] = 2;

									switch (currentFirstOfPairDir)
									{
									case 4:
										newTrackPos = currentFirstOfPairPosition - FVector2D(1, 0);

										convertedTrackPos.X = newTrackPos.X - 1;
										convertedTrackPos.Y = 15 - newTrackPos.Y;
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
										tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

										break;
									case 1:
										newTrackPos = currentFirstOfPairPosition + FVector2D(0, 1);

										convertedTrackPos.X = newTrackPos.X - 1;
										convertedTrackPos.Y = 15 - newTrackPos.Y;
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
										tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

										break;
									default:
										break;
									}
								}
								else
								{
									intersectionAdjustmentTrackerArr[currentFirstOfPairIndex] = 1;

									for (int a = 1; a <= extentOfAdjustment; a++)
									{
										newTrackPos = currentFirstOfPairPosition + FVector2D(a * (-1 + (currentFirstOfPairDir % 2)), a * (currentFirstOfPairDir % 2));//does this -1 work here as written?

										convertedTrackPos.X = newTrackPos.X - 1;
										convertedTrackPos.Y = 15 - newTrackPos.Y;
										trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2 - (currentFirstOfPairDir % 2);
										tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

									}
								}

								break;
							default:
								break;
							}
						}
						else
						{
							currentFirstOfPairPosition = holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex + 1];
							currentFirstOfPairDir = arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex + 1];

							switch (currentFirstOfPairDir)
							{
							case 1:
								intersectionAdjustmentTrackerArr[currentFirstOfPairIndex + 1] = 1;

								for (int a = 1; a <= extentOfAdjustment; a++)
								{
									newTrackPos = currentFirstOfPairPosition + FVector2D(a * (1 - (currentFirstOfPairDir % 2)), a * (currentFirstOfPairDir % 2));

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2 - (currentFirstOfPairDir % 2);
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								}

								break;
							case 2:
								intersectionAdjustmentTrackerArr[currentFirstOfPairIndex + 1] = 1;

								for (int a = 1; a <= extentOfAdjustment; a++)
								{
									newTrackPos = currentFirstOfPairPosition + FVector2D(a * (1 - (currentFirstOfPairDir % 2)), a * (currentFirstOfPairDir % 2) * -1);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2 - (currentFirstOfPairDir % 2);
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								}

								break;
							case 3:
								intersectionAdjustmentTrackerArr[currentFirstOfPairIndex + 1] = 1;

								for (int a = 1; a <= extentOfAdjustment; a++)
								{
									newTrackPos = currentFirstOfPairPosition + FVector2D(a * (-1 + (currentFirstOfPairDir % 2)), a * (currentFirstOfPairDir % 2) * -1);//does this -1 work here as written?

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2 - (currentFirstOfPairDir % 2);
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								}


								break;
							case 4:
								intersectionAdjustmentTrackerArr[currentFirstOfPairIndex + 1] = 1;

								for (int a = 1; a <= extentOfAdjustment; a++)
								{
									newTrackPos = currentFirstOfPairPosition + FVector2D(a * (-1 + (currentFirstOfPairDir % 2)), a * (currentFirstOfPairDir % 2));//does this -1 work here as written?

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2 - (currentFirstOfPairDir % 2);
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								}

								break;
							default:
								break;
							}
						}
					}
				}
			}

			for (int currentFirstOfPairIndex = 0; currentFirstOfPairIndex < holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex].Num(); currentFirstOfPairIndex += 2)
			{
				//what would happen if there were 7 holes in terms of how the adjustment is handled? I need to check in the intersection adjustment section of the generate track function. currently I think everything would run properly. if the 7nth hole's "promoted" intersection got an adjustment it should just run as if the promoted intersection were a standard intersection

				currentFirstOfPairPosition = holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex];
				currentFirstOfPairDir = arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex];
				currentPairTurnDistances = turnAndIntersectionDistancesPerPair[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex / 2];
				currentPairTurnDirections = directionsOfTurns[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex / 2];

				previousTurnOrIntersectionPosition = currentFirstOfPairPosition;

				//could the array index error be the result of what these "culminating" variables are set to, or how their values are used when a hole or intersection is either unpaired or exists on the top level? remember the error only occurs when currentGroupSize > 4 and the error is always "attempted to access index 1 from arr of size 1"
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
				case 1:
					if (currentIntersectionAdjustmentTracker)
					{// I will need to check if adjustment is for intersections of pair facing opposite directions both here and below where intersection adjustment track is layed
						if (currentIntersectionAdjustmentTracker == 2)
						{ // this will mean there is in adjustment to intersections of pair facing opposite directions
							previousTurnOrIntersectionPosition.X -= 1;
						}
						else
						{
							previousTurnOrIntersectionPosition.Y += extentOfAdjustment;
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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 1, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;//intersectiondir: 1, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;//intersectiondir: 2, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;//intersectiondir: 2, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								previousTurnOrIntersectionPosition = newTrackPos;

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition - FVector2D(a, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//is this really the best way to do this??//:>:P
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 1, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;//intersectiondir: 1, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;//intersectiondir: 2, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;//intersectiondir: 2, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								if (currentIntersectionAdjustmentTracker == 1 && currentPairTurnDistances.Num() == 2)//this proves its possible for there to be remaining verticle distance when pairStartsOnSameSide, firstOfPairIsRightOfAndEvenWithOrBelowSecond, and firstOfPairGetsAdjustment
								{
									secondOfPairPos = holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex + 1];
									differenceInPairPos = culminatingIntersectionPos - secondOfPairPos;

									if (differenceInPairPos.Y > 1)
									{
										for (int a = 1; a < differenceInPairPos.Y; a++)
										{
											newTrackPos = secondOfPairPos + FVector2D(0, a);

											convertedTrackPos.X = newTrackPos.X - 1;
											convertedTrackPos.Y = 15 - newTrackPos.Y;
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
										}
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 1, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;//intersectiondir: 1, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;//intersectiondir: 2, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;//intersectiondir: 2, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								previousTurnOrIntersectionPosition = newTrackPos;

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition + FVector2D(a, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//is this really the best way to do this??//:>:P
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 1, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;//intersectiondir: 1, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;//intersectiondir: 2, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;//intersectiondir: 2, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								previousTurnOrIntersectionPosition = newTrackPos;

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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
								}

								newTrackPos = previousTurnOrIntersectionPosition + FVector2D(0, correctedCurrentTurnDist);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 1, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;//intersectiondir: 1, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;//intersectiondir: 2, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;//intersectiondir: 2, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
										//Ive discovered there can also be remaining verticle distance when pairStartsOnSameSide, firstOfPairIsRightOfAndEvenWithOrBelowSecond, and firstOfPairGetsAdjustment
									{
										if (currentFirstOfPairIndex < holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex].Num() - 1)
										{
											secondOfPairDir = arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex + 1];
											secondOfPairPos = holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex + 1];
											differenceInPairPos = culminatingIntersectionPos - secondOfPairPos;//im changing this from currentFirstOfPairPosition minus second to culminatingIntersectionPos minus second 
											if (currentIntersectionAdjustmentTracker == 0 && currentLevelIndex > 0)
											{
												differenceInPairPos.X -= extentOfAdjustment;
												secondOfPairPos.X += extentOfAdjustment;
											}

											//if (secondOfPairDir != currentFirstOfPairDir)// I probably dont need to check this because if current pair turn distances is odd second of pair dir shouldnt equal first 
											//{
											if (/*currentFirstOfPairDir == currentFirstOfPairDirCorrectedForAdjustment &&*/ differenceInPairPos.X > 1)
											{
												for (int a = 1; a < differenceInPairPos.X; a++)
												{
													newTrackPos = secondOfPairPos + FVector2D(a, 0);

													convertedTrackPos.X = newTrackPos.X - 1;
													convertedTrackPos.Y = 15 - newTrackPos.Y;
													trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
													tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
												}
											}
											/*else if (currentFirstOfPairDir != currentFirstOfPairDirCorrectedForAdjustment && differenceInPairPos.Y < -1)
											{
												for (int a = -1; a > differenceInPairPos.Y; a--)
												{
													newTrackPos = secondOfPairPos + FVector2D(0, a);

													convertedTrackPos.X = newTrackPos.X - 1;
													convertedTrackPos.Y = 15 - newTrackPos.Y;
													trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
												}
											}*/
											//}
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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 1, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;//intersectiondir: 1, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;//intersectiondir: 2, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;//intersectiondir: 2, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								previousTurnOrIntersectionPosition = newTrackPos;

								break;
							default:
								break;
							}
						}
					}

					//here, if the current culminating intersection gets an adjustment, we lay the track to span the adjustment now
					if (adjustmentAppliedToCulminatingIntersectionPair != 0 && adjustmentAppliedToCulminatingIntersectionPair % 2 == 1 - ((currentFirstOfPairIndex / 2) % 2))//can this be in this scope or does it need to move up into the next? I think it can..
					{// this means: if current culminating intersection does get adjustment

						if (adjustmentAppliedToCulminatingIntersectionPair == 3)
						{
							intersectionAdjustmentTrackerArr[currentFirstOfPairIndex / 2] = 2;

							switch (culminatingIntersectionDir)
							{//this would need to have a case 3 if it's possible for this to occur twice in a row
							case 1:
								newTrackPos = culminatingIntersectionPos + FVector2D(0, 1);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;
								trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
								break;
							case 2:// I dont think this case can actually occur because if culminatingIntersectionDir == 2 adjustmentAppliedToCulminatingIntersection cannot equal 3
								newTrackPos = culminatingIntersectionPos + FVector2D(1, 0);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;
								trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
							}
						}
					}
					else
					{
						intersectionAdjustmentTrackerArr[currentFirstOfPairIndex / 2] = 0;
					}

					break;
				case 2:
					if (currentIntersectionAdjustmentTracker)
					{
						if (currentIntersectionAdjustmentTracker == 2)
						{ // this will mean there is in adjustment to intersections of pair facing opposite directions
							previousTurnOrIntersectionPosition.Y += 1;
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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;//intersectiondir: 2, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;//intersectiondir: 2, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//intersectiondir: 3, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 0;//intersectiondir: 3, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								previousTurnOrIntersectionPosition = newTrackPos;

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition + FVector2D(0, a);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//is this really the best way to do this??//:>:P
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;//intersectiondir: 2, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;//intersectiondir: 2, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//intersectiondir: 3, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 0;//intersectiondir: 3, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								if (currentIntersectionAdjustmentTracker == 1 && currentPairTurnDistances.Num() == 2)
								{
									secondOfPairPos = holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex + 1];
									differenceInPairPos = culminatingIntersectionPos - secondOfPairPos;

									if (differenceInPairPos.X > 1)
									{
										for (int a = 1; a < differenceInPairPos.X; a++)
										{
											newTrackPos = secondOfPairPos + FVector2D(a, 0);

											convertedTrackPos.X = newTrackPos.X - 1;
											convertedTrackPos.Y = 15 - newTrackPos.Y;
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
										}
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;//intersectiondir: 2, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;//intersectiondir: 2, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//intersectiondir: 3, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 0;//intersectiondir: 3, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								previousTurnOrIntersectionPosition = newTrackPos;

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition - FVector2D(0, a);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//is this really the best way to do this??//:>:P
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;//intersectiondir: 2, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;//intersectiondir: 2, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//intersectiondir: 3, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 0;//intersectiondir: 3, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								previousTurnOrIntersectionPosition = newTrackPos;

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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
								}

								newTrackPos = previousTurnOrIntersectionPosition + FVector2D(correctedCurrentTurnDist, 0);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;//intersectiondir: 2, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;//intersectiondir: 2, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//intersectiondir: 3, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 0;//intersectiondir: 3, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											if (currentIntersectionAdjustmentTracker == 0 && currentLevelIndex > 0)
											{
												differenceInPairPos.Y += extentOfAdjustment;
												secondOfPairPos.Y -= extentOfAdjustment;
											}

											if (differenceInPairPos.Y < -1)
											{
												for (int a = -1; a > differenceInPairPos.Y; a--)
												{
													newTrackPos = secondOfPairPos + FVector2D(0, a);

													convertedTrackPos.X = newTrackPos.X - 1;
													convertedTrackPos.Y = 15 - newTrackPos.Y;
													trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
													tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;//intersectiondir: 2, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;//intersectiondir: 2, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//intersectiondir: 3, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 0;//intersectiondir: 3, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								previousTurnOrIntersectionPosition = newTrackPos;

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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

									break;
								case 3:
									newTrackPos = culminatingIntersectionPos - FVector2D(0, 1);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
								}
							}
						}
						else
						{
							intersectionAdjustmentTrackerArr[currentFirstOfPairIndex / 2] = 0;
						}
					}
					else
					{
						intersectionAdjustmentTrackerArr[currentFirstOfPairIndex / 2] = 0;
					}

					break;
				case 3:
					if (currentIntersectionAdjustmentTracker)
					{
						if (currentIntersectionAdjustmentTracker == 2)
						{ // this will mean there is in adjustment to intersections of pair facing opposite directions
							previousTurnOrIntersectionPosition.X += 1;
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
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//intersectiondir: 3, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 0;//intersectiondir: 3, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;//intersectiondir: 4, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//intersectiondir: 4, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								previousTurnOrIntersectionPosition = newTrackPos;

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition + FVector2D(a, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//is this really the best way to do this??//:>:P
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//intersectiondir: 3, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 0;//intersectiondir: 3, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;//intersectiondir: 4, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//intersectiondir: 4, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								if (currentIntersectionAdjustmentTracker == 1 && currentPairTurnDistances.Num() == 2)
								{
									secondOfPairPos = holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex + 1];
									differenceInPairPos = culminatingIntersectionPos - secondOfPairPos;

									if (differenceInPairPos.Y < -1)
									{
										for (int a = -1; a > differenceInPairPos.Y; a--)
										{
											newTrackPos = secondOfPairPos + FVector2D(0, a);

											convertedTrackPos.X = newTrackPos.X - 1;
											convertedTrackPos.Y = 15 - newTrackPos.Y;
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
											tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
										}
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//intersectiondir: 3, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 0;//intersectiondir: 3, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;//intersectiondir: 4, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//intersectiondir: 4, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								previousTurnOrIntersectionPosition = newTrackPos;

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition - FVector2D(a, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//is this really the best way to do this??//:>:P
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//intersectiondir: 3, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 0;//intersectiondir: 3, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;//intersectiondir: 4, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//intersectiondir: 4, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								previousTurnOrIntersectionPosition = newTrackPos;

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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
								}

								newTrackPos = previousTurnOrIntersectionPosition - FVector2D(0, correctedCurrentTurnDist);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//intersectiondir: 3, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 0;//intersectiondir: 3, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;//intersectiondir: 4, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//intersectiondir: 4, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											if (currentIntersectionAdjustmentTracker == 0 && currentLevelIndex > 0)
											{
												differenceInPairPos.X += extentOfAdjustment;
												secondOfPairPos.X -= extentOfAdjustment;
											}

											if (differenceInPairPos.X < -1)
											{
												for (int a = -1; a > differenceInPairPos.X; a--)
												{
													newTrackPos = secondOfPairPos + FVector2D(a, 0);

													convertedTrackPos.X = newTrackPos.X - 1;
													convertedTrackPos.Y = 15 - newTrackPos.Y;
													trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
													tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//intersectiondir: 3, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 0;//intersectiondir: 3, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;//intersectiondir: 4, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//intersectiondir: 4, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								previousTurnOrIntersectionPosition = newTrackPos;

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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

									break;
								case 4:
									newTrackPos = culminatingIntersectionPos - FVector2D(1, 0);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
								}
							}
						}
						else
						{
							intersectionAdjustmentTrackerArr[currentFirstOfPairIndex / 2] = 0;
						}

					}
					else
					{
						intersectionAdjustmentTrackerArr[currentFirstOfPairIndex / 2] = 0;
					}

					break;
				case 4:
					if (currentIntersectionAdjustmentTracker)
					{
						if (currentIntersectionAdjustmentTracker == 2)
						{ // this will mean there is in adjustment to intersections of pair facing opposite directions
							previousTurnOrIntersectionPosition.Y -= 1;
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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;//intersectiondir: 4, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//intersectiondir: 4, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 1, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;//intersectiondir: 1, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								previousTurnOrIntersectionPosition = newTrackPos;

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition - FVector2D(0, a);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//is this really the best way to do this??//:>:P
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;//intersectiondir: 4, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//intersectiondir: 4, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 1, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;//intersectiondir: 1, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								if (currentIntersectionAdjustmentTracker == 1 && currentPairTurnDistances.Num() == 2)
								{
									secondOfPairPos = holeAndIntersectionPositions[currentLevelIndex][currentGroupIndex][currentFirstOfPairIndex + 1];
									differenceInPairPos = culminatingIntersectionPos - secondOfPairPos;

									if (differenceInPairPos.X < -1)
									{
										for (int a = -1; a > differenceInPairPos.X; a--)
										{
											newTrackPos = secondOfPairPos + FVector2D(a, 0);

											convertedTrackPos.X = newTrackPos.X - 1;
											convertedTrackPos.Y = 15 - newTrackPos.Y;
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
											tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
										}
									}
								}

								previousTurnOrIntersectionPosition = newTrackPos;

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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;//intersectiondir: 4, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//intersectiondir: 4, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 1, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;//intersectiondir: 1, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								previousTurnOrIntersectionPosition = newTrackPos;

								break;
							case 1:
								for (int a = 1; a < correctedCurrentTurnDist; a++)//this is laying down the track between turns or intersections
								{
									newTrackPos = previousTurnOrIntersectionPosition + FVector2D(0, a);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;//is this really the best way to do this??//:>:P
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;//intersectiondir: 4, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//intersectiondir: 4, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 1, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;//intersectiondir: 1, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								previousTurnOrIntersectionPosition = newTrackPos;

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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
								}

								newTrackPos = previousTurnOrIntersectionPosition - FVector2D(correctedCurrentTurnDist, 0);

								convertedTrackPos.X = newTrackPos.X - 1;
								convertedTrackPos.Y = 15 - newTrackPos.Y;

								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;//intersectiondir: 4, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//intersectiondir: 4, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 1, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;//intersectiondir: 1, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											if (currentIntersectionAdjustmentTracker == 0 && currentLevelIndex > 0)
											{
												differenceInPairPos.Y -= extentOfAdjustment;
												secondOfPairPos.Y += extentOfAdjustment;
											}

											if (differenceInPairPos.Y > 1)
											{
												for (int a = 1; a < differenceInPairPos.Y; a++)
												{
													newTrackPos = secondOfPairPos + FVector2D(0, a);

													convertedTrackPos.X = newTrackPos.X - 1;
													convertedTrackPos.Y = 15 - newTrackPos.Y;
													trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
													tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;//intersectiondir: 4, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;//intersectiondir: 4, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 7;//intersectiondir: 1, intersectionOrientation: 0;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
											break;
										case 1:
											trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;//intersectiondir: 1, intersectionOrientation: 1;
											tileIsIntersection[convertedTrackPos.Y * 15 + convertedTrackPos.X] = true;
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
								tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

								previousTurnOrIntersectionPosition = newTrackPos;

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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

									break;
								case 1:
									newTrackPos = culminatingIntersectionPos + FVector2D(0, 1);

									convertedTrackPos.X = newTrackPos.X - 1;
									convertedTrackPos.Y = 15 - newTrackPos.Y;
									trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

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
									tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
								}
							}
						}
						else
						{
							intersectionAdjustmentTrackerArr[currentFirstOfPairIndex / 2] = 0;
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
		topLevelIndex++;

		if (finalGroupingActive)
		{
			currentGroupIndex = listOfHolePositionGroupings.Num() + 1;
		}
	}

	//setting track between the final intersection and the edge of the board
	FVector2d finalIntersectionPos;
	int finalIntersectionDir;
	int distanceToEdgeOfBoard;
	int endOfSides = 8 + FMath::Clamp((numberOfHoles - 4) / 2, 0, 6);
	bool canAddFlare = false;
	int directionOfFlare;
	int numHolesCoefficientOne = FMath::Clamp(FMath::DivideAndRoundDown((numberOfHoles - 8), 2), 0, 4);
	int numHolesCoefficientTwo = FMath::Clamp(FMath::DivideAndRoundDown((numberOfHoles - 8), 2), 0, 3);
	int extentOfFlare = FMath::RandRange(1 + numHolesCoefficientOne, 3 + numHolesCoefficientTwo);
	int remainingDistanceAfterFlare;

	//now I need to impliment putting the flare on the furthest most tiles for any hole count greater than 12, test my alterations, then if they work delete the extraneous extent of flare code and other trash
	//I could possibly get rid of a lot of repitition in this area by rearranging finalIntersectionDir conditional stuff
	//extentOfFlare alterations need tested to see if they are working as expected (less looking for glitchyness more functionality)

	if (listOfHolePositionGroupings.Num() == 1)//do I even need this conditional?
	{
		finalIntersectionPos = holeAndIntersectionPositions[4][0][0];
		finalIntersectionDir = arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[4][0][0];
	}
	else
	{
		finalIntersectionPos = holeAndIntersectionPositions[FMath::Clamp(FMath::RoundHalfFromZero((float)listOfHolePositionGroupings.Num() / 2.0f), 1, 3) + 4][0][0];
		finalIntersectionDir = arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[FMath::Clamp(FMath::RoundHalfFromZero((float)listOfHolePositionGroupings.Num() / 2.0f), 1, 3) + 4][0][0];
	}

	//if (15 - endOfSides > 2 && 14 > finalIntersectionPos.X && finalIntersectionPos.X > 2 && 14 > finalIntersectionPos.Y && finalIntersectionPos.Y > 2)
	//{
	if (numberOfHoles < 9)
	{
		float flareCoefficient = (float)((float)((float)0.5 * (float)sin((float)3.14 * ((float)((float)numberOfHoles / (float)9) - (float)0.5))) + (float)0.5) * (float)100; // I know this looks silly, its to create an exponential increase in probability so the lower number of holes probably wont but still might get flare and the higher number probably will but still might not

		if (FMath::RandRange(1, 100) < flareCoefficient)
		{
			canAddFlare = true;
		}
	}
	else
	{
		canAddFlare = true;
	}
	//}

	switch (negativeOneZeroOrOne)
	{
	case -1:
		switch (finalIntersectionDir)
		{
		case 1:
			finalIntersectionPos.Y += 1;
			newTrackPos = finalIntersectionPos;

			convertedTrackPos.X = newTrackPos.X - 1;
			convertedTrackPos.Y = 15 - newTrackPos.Y;
			trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
			tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

			break;
		case 2:
			newTrackPos = finalIntersectionPos;

			break;
		case 3:
			finalIntersectionPos.Y -= 1;
			newTrackPos = finalIntersectionPos;

			convertedTrackPos.X = newTrackPos.X - 1;
			convertedTrackPos.Y = 15 - newTrackPos.Y;
			trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
			tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

			break;
		}

		distanceToEdgeOfBoard = 15 - finalIntersectionPos.X;

		if (canAddFlare)
		{
			if (numberOfHoles < 11)
			{
				if (FMath::RandRange(0, 19) > 9)
				{
					if (newTrackPos.Y < 12)
					{
						directionOfFlare = 1;
					}
					else
					{
						directionOfFlare = 3;
					}
				}
				else
				{
					if (newTrackPos.Y > 4)
					{
						directionOfFlare = 3;
					}
					else
					{
						directionOfFlare = 1;
					}
				}
			}
			else
			{
				if (15 - finalIntersectionPos.Y > finalIntersectionPos.Y)
				{
					directionOfFlare = 1;
				}
				else
				{
					directionOfFlare = 3;
				}
			}

			if (numberOfHoles < 14)
			{
				//why is end of sides coming into play here? because doesnt turn for the flair prematurely potentially causing an avoidable overlap
				if (endOfSides >= newTrackPos.X)
				{
					distanceToEdgeOfBoard = endOfSides - newTrackPos.X + 1 + FMath::RandRange(0, 12 - endOfSides);
					remainingDistanceAfterFlare = 14 - (distanceToEdgeOfBoard + newTrackPos.X);
				}
				else
				{
					distanceToEdgeOfBoard = FMath::RandRange(0, (int)(13 - newTrackPos.X));
					remainingDistanceAfterFlare = 14 - (distanceToEdgeOfBoard + newTrackPos.X);
				}
			}
			else
			{
				//is it possible for finalIntersectionPos to be too close to the side and cause a glitch? I dont think so
				distanceToEdgeOfBoard = 14 - newTrackPos.X;
				remainingDistanceAfterFlare = 0;
			}
		}

		for (int a = 1; a <= distanceToEdgeOfBoard; a++)
		{
			newTrackPos = finalIntersectionPos + FVector2D(a, 0);

			convertedTrackPos.X = newTrackPos.X - 1;
			convertedTrackPos.Y = 15 - newTrackPos.Y;
			trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
			tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
		}

		if (canAddFlare)
		{
			switch (directionOfFlare)
			{
			case 1:
				newTrackPos.X += 1;

				convertedTrackPos.X = newTrackPos.X - 1;
				convertedTrackPos.Y = 15 - newTrackPos.Y;
				trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;
				tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

				for (int a = 1; a <= extentOfFlare; a++)
				{
					newTrackPos.Y += 1;

					convertedTrackPos.X = newTrackPos.X - 1;
					convertedTrackPos.Y = 15 - newTrackPos.Y;
					trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
					tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
				}

				newTrackPos.Y += 1;

				convertedTrackPos.X = newTrackPos.X - 1;
				convertedTrackPos.Y = 15 - newTrackPos.Y;
				trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
				tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

				for (int a = 1; a <= remainingDistanceAfterFlare; a++)
				{
					newTrackPos.X += 1;

					convertedTrackPos.X = newTrackPos.X - 1;
					convertedTrackPos.Y = 15 - newTrackPos.Y;
					trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
					tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
				}
				break;
			case 3:
				newTrackPos.X += 1;

				convertedTrackPos.X = newTrackPos.X - 1;
				convertedTrackPos.Y = 15 - newTrackPos.Y;
				trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;
				tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

				for (int a = 1; a <= extentOfFlare; a++)
				{
					newTrackPos.Y -= 1;

					convertedTrackPos.X = newTrackPos.X - 1;
					convertedTrackPos.Y = 15 - newTrackPos.Y;
					trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
					tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
				}

				newTrackPos.Y -= 1;

				convertedTrackPos.X = newTrackPos.X - 1;
				convertedTrackPos.Y = 15 - newTrackPos.Y;
				trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
				tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

				for (int a = 1; a <= remainingDistanceAfterFlare; a++)
				{
					newTrackPos.X += 1;

					convertedTrackPos.X = newTrackPos.X - 1;
					convertedTrackPos.Y = 15 - newTrackPos.Y;
					trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
					tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
				}
				break;
			default:
				break;
			}
		}

		startingPos = convertedTrackPos;
		startingDir = 4;

		break;
	case 0:
		switch (finalIntersectionDir)
		{
		case 1:
			newTrackPos = finalIntersectionPos;

			break;
		case 2:
			finalIntersectionPos.X += 1;
			newTrackPos = finalIntersectionPos;


			convertedTrackPos.X = newTrackPos.X - 1;
			convertedTrackPos.Y = 15 - newTrackPos.Y;
			trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;
			tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

			break;
		case 4:
			finalIntersectionPos.X -= 1;
			newTrackPos = finalIntersectionPos;

			convertedTrackPos.X = newTrackPos.X - 1;
			convertedTrackPos.Y = 15 - newTrackPos.Y;
			trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
			tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

			break;
		}

		distanceToEdgeOfBoard = 15 - finalIntersectionPos.Y;

		if (canAddFlare)
		{
			if (numberOfHoles < 11)
			{
				if (FMath::RandRange(0, 19) > 9)
				{
					if (newTrackPos.X > 4)
					{
						directionOfFlare = 4;
					}
					else
					{
						directionOfFlare = 2;
					}
				}
				else
				{
					if (newTrackPos.X < 12)
					{
						directionOfFlare = 2;
					}
					else
					{
						directionOfFlare = 4;
					}
				}
			}
			else
			{
				if (15 - finalIntersectionPos.X > finalIntersectionPos.X)
				{
					directionOfFlare = 2;
				}
				else
				{
					directionOfFlare = 4;
				}
			}

			if (numberOfHoles < 14)
			{
				if (endOfSides >= newTrackPos.Y)
				{
					distanceToEdgeOfBoard = endOfSides - newTrackPos.Y + 1 + FMath::RandRange(0, 12 - endOfSides);
					remainingDistanceAfterFlare = 14 - (distanceToEdgeOfBoard + newTrackPos.Y);
				}
				else
				{
					distanceToEdgeOfBoard = FMath::RandRange(0, (int)(13 - newTrackPos.Y));
					remainingDistanceAfterFlare = 14 - (distanceToEdgeOfBoard + newTrackPos.Y);
				}

			}
			else
			{
				distanceToEdgeOfBoard = 14 - newTrackPos.Y;
				remainingDistanceAfterFlare = 0;
			}
		}

		for (int a = 1; a <= distanceToEdgeOfBoard; a++)
		{
			newTrackPos = finalIntersectionPos + FVector2D(0, a);

			convertedTrackPos.X = newTrackPos.X - 1;
			convertedTrackPos.Y = 15 - newTrackPos.Y;
			trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
			tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
		}

		if (canAddFlare)
		{
			switch (directionOfFlare)
			{
			case 2:
				newTrackPos.Y += 1;

				convertedTrackPos.X = newTrackPos.X - 1;
				convertedTrackPos.Y = 15 - newTrackPos.Y;
				trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
				tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

				for (int a = 1; a <= extentOfFlare; a++)
				{
					newTrackPos.X += 1;

					convertedTrackPos.X = newTrackPos.X - 1;
					convertedTrackPos.Y = 15 - newTrackPos.Y;
					trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
					tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
				}

				newTrackPos.X += 1;

				convertedTrackPos.X = newTrackPos.X - 1;
				convertedTrackPos.Y = 15 - newTrackPos.Y;
				trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;
				tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

				for (int a = 1; a <= remainingDistanceAfterFlare; a++)
				{
					newTrackPos.Y += 1;

					convertedTrackPos.X = newTrackPos.X - 1;
					convertedTrackPos.Y = 15 - newTrackPos.Y;
					trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
					tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
				}
				break;
			case 4:
				newTrackPos.Y += 1;

				convertedTrackPos.X = newTrackPos.X - 1;
				convertedTrackPos.Y = 15 - newTrackPos.Y;
				trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;
				tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

				for (int a = 1; a <= extentOfFlare; a++)
				{
					newTrackPos.X -= 1;

					convertedTrackPos.X = newTrackPos.X - 1;
					convertedTrackPos.Y = 15 - newTrackPos.Y;
					trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
					tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
				}

				newTrackPos.X -= 1;

				convertedTrackPos.X = newTrackPos.X - 1;
				convertedTrackPos.Y = 15 - newTrackPos.Y;
				trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
				tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

				for (int a = 1; a <= remainingDistanceAfterFlare; a++)
				{
					newTrackPos.Y += 1;

					convertedTrackPos.X = newTrackPos.X - 1;
					convertedTrackPos.Y = 15 - newTrackPos.Y;
					trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
					tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
				}
				break;
			default:
				break;
			}
		}

		startingPos = convertedTrackPos;
		startingDir = 3;

		break;
	case 1:
		switch (finalIntersectionDir)
		{
		case 1:
			finalIntersectionPos.Y += 1;
			newTrackPos = finalIntersectionPos;

			convertedTrackPos.X = newTrackPos.X - 1;
			convertedTrackPos.Y = 15 - newTrackPos.Y;
			trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;
			tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

			break;
		case 3:
			finalIntersectionPos.Y -= 1;
			newTrackPos = finalIntersectionPos;

			convertedTrackPos.X = newTrackPos.X - 1;
			convertedTrackPos.Y = 15 - newTrackPos.Y;
			trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;
			tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

			break;
		case 4:
			newTrackPos = finalIntersectionPos;

			break;
		}

		distanceToEdgeOfBoard = finalIntersectionPos.X - 1;

		if (canAddFlare)
		{
			if (numberOfHoles < 11)
			{
				if (FMath::RandRange(0, 19) > 9)
				{
					if (newTrackPos.Y > 4)
					{
						directionOfFlare = 3;
					}
					else
					{
						directionOfFlare = 1;
					}
				}
				else
				{
					if (newTrackPos.Y < 12)
					{
						directionOfFlare = 1;
					}
					else
					{
						directionOfFlare = 3;
					}
				}
			}
			else
			{
				if (15 - finalIntersectionPos.Y > finalIntersectionPos.Y)
				{
					directionOfFlare = 1;
				}
				else
				{
					directionOfFlare = 3;
				}
			}

			if (numberOfHoles < 14)
			{
				if (endOfSides >= 16 - newTrackPos.X)
				{
					distanceToEdgeOfBoard = endOfSides - (16 - newTrackPos.X) + 1 + FMath::RandRange(0, 12 - endOfSides);
					remainingDistanceAfterFlare = 14 - (distanceToEdgeOfBoard + (16 - newTrackPos.X));
				}
				else
				{
					distanceToEdgeOfBoard = FMath::RandRange(0, (int)(13 - (16 - newTrackPos.X)));
					remainingDistanceAfterFlare = 14 - (distanceToEdgeOfBoard + (16 - newTrackPos.X));
				}

			}
			else
			{
				distanceToEdgeOfBoard = newTrackPos.X - 2;
				remainingDistanceAfterFlare = 0;
			}
		}

		for (int a = 1; a <= distanceToEdgeOfBoard; a++)
		{
			newTrackPos = finalIntersectionPos - FVector2D(a, 0);

			convertedTrackPos.X = newTrackPos.X - 1;
			convertedTrackPos.Y = 15 - newTrackPos.Y;
			trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
			tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
		}

		if (canAddFlare)
		{
			switch (directionOfFlare)
			{
			case 1:
				newTrackPos.X -= 1;

				convertedTrackPos.X = newTrackPos.X - 1;
				convertedTrackPos.Y = 15 - newTrackPos.Y;
				trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
				tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

				for (int a = 1; a <= extentOfFlare; a++)
				{
					newTrackPos.Y += 1;

					convertedTrackPos.X = newTrackPos.X - 1;
					convertedTrackPos.Y = 15 - newTrackPos.Y;
					trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
					tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
				}

				newTrackPos.Y += 1;

				convertedTrackPos.X = newTrackPos.X - 1;
				convertedTrackPos.Y = 15 - newTrackPos.Y;
				trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 5;
				tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

				for (int a = 1; a <= remainingDistanceAfterFlare; a++)
				{
					newTrackPos.X -= 1;

					convertedTrackPos.X = newTrackPos.X - 1;
					convertedTrackPos.Y = 15 - newTrackPos.Y;
					trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
					tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
				}
				break;
			case 3:
				newTrackPos.X -= 1;

				convertedTrackPos.X = newTrackPos.X - 1;
				convertedTrackPos.Y = 15 - newTrackPos.Y;
				trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
				tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

				for (int a = 1; a <= extentOfFlare; a++)
				{
					newTrackPos.Y -= 1;

					convertedTrackPos.X = newTrackPos.X - 1;
					convertedTrackPos.Y = 15 - newTrackPos.Y;
					trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
					tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
				}

				newTrackPos.Y -= 1;

				convertedTrackPos.X = newTrackPos.X - 1;
				convertedTrackPos.Y = 15 - newTrackPos.Y;
				trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 6;
				tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;

				for (int a = 1; a <= remainingDistanceAfterFlare; a++)
				{
					newTrackPos.X -= 1;

					convertedTrackPos.X = newTrackPos.X - 1;
					convertedTrackPos.Y = 15 - newTrackPos.Y;
					trackArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
					tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
				}
				break;
			default:
				break;
			}
		}

		startingPos = convertedTrackPos;
		startingDir = 2;

		break;
	default:
		break;
	}


	//LANDSCAPE DATA

	//placing the holes
	int currentHoleDir;

	for (int currentGroupIndex = 0; currentGroupIndex < listOfHolePositionGroupings.Num(); currentGroupIndex++)
	{
		currentGroupSize = listOfHolePositionGroupings[currentGroupIndex];

		for (int currentHoleIndex = 0; currentHoleIndex < currentGroupSize; currentHoleIndex++)
		{
			newTrackPos = holeAndIntersectionPositions[0][currentGroupIndex][currentHoleIndex];

			convertedTrackPos.X = newTrackPos.X - 1;
			convertedTrackPos.Y = 15 - newTrackPos.Y;

			convertedHolePositions.Add(convertedTrackPos);

			currentHoleDir = arrOfTrackDirectionsLeadingAwayFromEachHoleOrIntersection[0][currentGroupIndex][currentHoleIndex];

			switch (currentHoleDir)
			{
			case 1:
				landscapeArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 4;
				tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
				break;
			case 2:
				landscapeArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 3;
				tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
				break;
			case 3:
				landscapeArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 1;
				tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
				break;
			case 4:
				landscapeArr[convertedTrackPos.Y * 15 + convertedTrackPos.X] = 2;
				tileIsTrack[convertedTrackPos.Y * 15 + convertedTrackPos.X] += 1;
				break;
			default:
				break;
			}
		}
	}

	//shaping the river
	int dirOfRiver;
	int riverStartingPos;
	int x = 0;
	int y = 8;
	int startingSegment = FMath::RandRange(1, 3);
	FVector2D newRiverPos;
	FVector2D convertedRiverPos;
	int indexFormatByRiverDir;
	int pondMetric;
	TArray<TArray< int> > pondStruct =
	{
		{ 10, 7 },
		{ 8 },
		{ 9 }
	};
	int pondIndex;
	FVector2D newPondPos;
	int canAddPond = 1;
	FVector2D relevantPos;
	bool pondAdded = true;
	bool canTurn;
	bool canMakeRiver = true;
	TArray <int> holePositionsRelevantVerts;
	TArray <int> vertsToRemove;
	TArray <int> viableStartingPositionsRiverDirTwo = { 8, 9, 10, 11, 12, 13 };
	TArray <int> viableStartingPositionsRiverDirThree = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

	switch (FMath::RandRange(0, 2))
	{
	case 0:
		dirOfRiver = 2;

		for (FVector2D b : holePositions)
		{
			holePositionsRelevantVerts.Add(b.Y);
		}

		for (int b : viableStartingPositionsRiverDirTwo)
		{
			if (holePositionsRelevantVerts.Find(b) + 1)
			{
				vertsToRemove.Add(b);
			}
		}

		for (int b : vertsToRemove)
		{
			viableStartingPositionsRiverDirTwo.Remove(b);
		}

		if (viableStartingPositionsRiverDirTwo.Num())
		{
			riverStartingPos = viableStartingPositionsRiverDirTwo[FMath::RandRange(0, viableStartingPositionsRiverDirTwo.Num() - 1)];
		}
		else
		{
			canMakeRiver = false;
		}

		newRiverPos = FVector2D(0, riverStartingPos);

		indexFormatByRiverDir = 16;//abs((dirOfRiver * 3 - 10) / 2) * 3 + 10;//will this abs actually work? 

		break;
	case 1:
		dirOfRiver = 3;

		for (FVector2D b : holePositions)
		{
			holePositionsRelevantVerts.Add(b.X);
		}

		for (int b : viableStartingPositionsRiverDirThree)
		{
			if (holePositionsRelevantVerts.Find(b) + 1)
			{
				vertsToRemove.Add(b);
			}
		}

		for (int b : vertsToRemove)
		{
			viableStartingPositionsRiverDirThree.Remove(b);
		}

		if (viableStartingPositionsRiverDirThree.Num())
		{
			riverStartingPos = viableStartingPositionsRiverDirThree[FMath::RandRange(0, viableStartingPositionsRiverDirThree.Num() - 1)];
		}
		else
		{
			canMakeRiver = false;
		}

		newRiverPos = FVector2D(riverStartingPos, 16);

		indexFormatByRiverDir = 10;
		break;
	case 2:
		dirOfRiver = 4;

		for (FVector2D b : holePositions)
		{
			holePositionsRelevantVerts.Add(b.Y);
		}

		for (int b : viableStartingPositionsRiverDirTwo)
		{
			if (holePositionsRelevantVerts.Find(b) + 1)
			{
				vertsToRemove.Add(b);
			}
		}

		for (int b : vertsToRemove)
		{
			viableStartingPositionsRiverDirTwo.Remove(b);
		}

		if (viableStartingPositionsRiverDirTwo.Num())
		{
			riverStartingPos = viableStartingPositionsRiverDirTwo[FMath::RandRange(0, viableStartingPositionsRiverDirTwo.Num() - 1)];
		}
		else
		{
			canMakeRiver = false;
		}

		newRiverPos = FVector2D(16, riverStartingPos);

		indexFormatByRiverDir = 13;

		break;
	default:
		break;
	}

	while (canMakeRiver)
	{
		for (int a = startingSegment; a <= 3; a++)
		{
			newRiverPos += FVector2D(1 * ((dirOfRiver - 3) * -1), -1 * (dirOfRiver % 2));
			if (newRiverPos.Y < 1 || newRiverPos.X > 15 || newRiverPos.X < 1)
			{
				break;
			}

			convertedRiverPos.X = newRiverPos.X - 1;
			convertedRiverPos.Y = 15 - newRiverPos.Y;
			landscapeArr[convertedRiverPos.Y * 15 + convertedRiverPos.X] = indexFormatByRiverDir + a;
		}
		if (newRiverPos.Y < 1 || newRiverPos.X > 15 || newRiverPos.X < 1)
		{
			break; //is this break here going to be enough or should I impliment canMakeRiver = false
		}
		startingSegment = 1;

		switch (dirOfRiver)
		{
		case 2:
			if (newRiverPos.X + 1 > 13 || newRiverPos.Y - 1 < 1)
			{
				canAddPond -= canAddPond;
				break;//does this break the switch or just the conditional?
			}
			newPondPos = newRiverPos + FVector2D(1, 1);
			break;
		case 3:
			if (newRiverPos.Y - 1 < 3 || newRiverPos.X - 1 < 1 || newRiverPos.X - 1 > 13)
			{
				canAddPond -= canAddPond;
				break;
			}
			newPondPos = newRiverPos + FVector2D(-1, -1);
			break;
		case 4:
			if (newRiverPos.X - 3 < 1 || newRiverPos.Y - 1 < 1)
			{
				canAddPond -= canAddPond;
				break;
			}
			newPondPos = newRiverPos + FVector2D(-3, 1);
			break;
		default:
			break;
		}

		for (int b = 0; b < 3; b++)
		{
			for (int c = 0; c < 3; c++)
			{
				relevantPos = newPondPos + FVector2D(b, -c);

				if (holePositions.Find(relevantPos) + 1)
				{
					canAddPond -= canAddPond;
				}
			}
		}

		if (FMath::RandRange(0, 6) > 0 && canAddPond)
		{// a pond or waterfall occurs
			pondMetric = indexFormatByRiverDir / 3 - 3;

			if (pondStruct[pondMetric].Num())
			{
				pondIndex = FMath::RandRange(0, pondStruct[pondMetric].Num() - 1);

				convertedRiverPos.X = newPondPos.X - 1;
				convertedRiverPos.Y = 15 - newPondPos.Y;
				pondPositionArr.Add(convertedRiverPos);
				pondSpecifierArr.Add(pondStruct[pondMetric][pondIndex]);
				pondStruct[pondMetric].RemoveAt(pondIndex);

				newRiverPos += 3 * FVector2D(1 * ((dirOfRiver - 3) * -1), -1 * (dirOfRiver % 2));
				x += 1;
			}
		}
		canAddPond = 1;

		switch (dirOfRiver)
		{
		case 2:
			if (newRiverPos.X + 1 > 15)
			{
				break;
			}

			for (FVector2D b : holePositions)
			{
				if (b.X == newRiverPos.X + 1)
				{
					canTurn = false;
				}
			}

			if (FMath::RandRange(x, 40) > 5 && canTurn)
			{// a turn occurs
				newRiverPos.X += 1;

				convertedRiverPos.X = newRiverPos.X - 1;
				convertedRiverPos.Y = 15 - newRiverPos.Y;
				landscapeArr[convertedRiverPos.Y * 15 + convertedRiverPos.X] = 27;

				dirOfRiver = 3;
				indexFormatByRiverDir = 10;
				x = -1;
				startingSegment = 2;
			}
			break;
		case 3:
			if (newRiverPos.Y - 1 < 1)
			{
				break;
			}

			for (FVector2D b : holePositions)
			{
				if (b.Y == newRiverPos.Y - 1)
				{
					canTurn = false;
				}
			}

			if (FMath::RandRange(x, 40) > 5 && canTurn)
			{// a turn occurs
				newRiverPos.Y -= 1;

				convertedRiverPos.X = newRiverPos.X - 1;
				convertedRiverPos.Y = 15 - newRiverPos.Y;

				if (FMath::RandRange(0, 19) > 9)
				{// turning towards 2
					landscapeArr[convertedRiverPos.Y * 15 + convertedRiverPos.X] = 26;
					dirOfRiver = 2;
					indexFormatByRiverDir = 16;
				}
				else
				{// turning towards 4
					landscapeArr[convertedRiverPos.Y * 15 + convertedRiverPos.X] = 28;
					dirOfRiver = 4;
					indexFormatByRiverDir = 13;
				}
				x = -1;
				startingSegment = 2;
			}
			break;
		case 4:
			if (newRiverPos.X - 1 < 1)
			{
				break;
			}

			for (FVector2D b : holePositions)
			{
				if (b.X == newRiverPos.X - 1)
				{
					canTurn = false;
				}
			}

			if (FMath::RandRange(x, 40) > 5 && canTurn)
			{// a turn occurs
				newRiverPos.X -= 1;

				convertedRiverPos.X = newRiverPos.X - 1;
				convertedRiverPos.Y = 15 - newRiverPos.Y;
				landscapeArr[convertedRiverPos.Y * 15 + convertedRiverPos.X] = 25;

				dirOfRiver = 3;
				indexFormatByRiverDir = 10;
				x = -1;
				startingSegment = 2;
			}
			break;
		}
		canTurn = true;
		x += 1;
	}

	for (FVector2D a : pondPositionArr)
	{
		for (int b = 0; b < 3; b++)
		{
			for (int c = 0; c < 3; c++)
			{
				relevantPos = a + FVector2D(b, c);
				landscapeArr[relevantPos.Y * 15 + relevantPos.X] = 29;
			}
		}
	}

	// all other landscape stuff besides river and hole positions
	FVector2D convertedTilePos;
	bool canAddLargeTile;

	switch (FMath::RandRange(0, 2))
	{
	case 0:
		//thin tree cover, possible mountain
		for (int a = 0; a < 225; a++)
		{
			if (landscapeArr[a] == 0)
			{
				if (tileIsTrack[a])
				{
					landscapeArr[a] = 29 + FMath::RandRange(1, 3);
				}
				else
				{
					if (FMath::RandRange(0, 11) > 7)
					{
						landscapeArr[a] = 20 + FMath::RandRange(0, 3);
					}
					else
					{
						convertedTilePos.X = a % 15;
						convertedTilePos.Y = a / 15;

						if (convertedTilePos.X < 13 && convertedTilePos.Y < 13 && a < 89)
						{
							for (int b = 0; b < 3; b++)
							{
								for (int c = 0; c < 3; c++)
								{
									relevantPos = convertedTilePos + FVector2D(c, b);

									if (landscapeArr[relevantPos.Y * 15 + relevantPos.X] || tileIsTrack[relevantPos.Y * 15 + relevantPos.X])
									{
										canAddLargeTile = false;
									}
								}
							}
						}
						else
						{
							canAddLargeTile = false;
						}

						if (canAddLargeTile && FMath::RandRange(0, 40) < numberOfHoles)
						{
							for (int b = 0; b < 3; b++)
							{
								for (int c = 0; c < 3; c++)
								{
									relevantPos = convertedTilePos + FVector2D(c, b);

									landscapeArr[relevantPos.Y * 15 + relevantPos.X] = 29;
								}
							}

							pondPositionArr.Add(convertedTilePos);
							pondSpecifierArr.Add(33);
						}
						else
						{
							landscapeArr[a] = 29 + FMath::RandRange(1, 3);
						}
						canAddLargeTile = true;
					}
				}
			}
		}
		break;
	case 1:
		//thick tree cover, no mountains
		for (int a = 0; a < 225; a++)
		{
			if (landscapeArr[a] == 0)
			{
				if (tileIsTrack[a])
				{
					landscapeArr[a] = 29 + FMath::RandRange(1, 3);
				}
				else
				{
					if (FMath::RandRange(0, 11) > 3)
					{
						convertedTilePos.X = a % 15;
						convertedTilePos.Y = a / 15;
						if (convertedTilePos.X < 13 && convertedTilePos.Y < 13)
						{
							for (int b = 0; b < 3; b++)
							{
								for (int c = 0; c < 3; c++)
								{
									relevantPos = convertedTilePos + FVector2D(c, b);

									if (landscapeArr[relevantPos.Y * 15 + relevantPos.X] || tileIsTrack[relevantPos.Y * 15 + relevantPos.X])
									{
										canAddLargeTile = false;
									}
								}
							}
						}
						else
						{
							canAddLargeTile = false;
						}

						if (canAddLargeTile && FMath::RandRange(0, 32) < numberOfHoles)
						{
							for (int b = 0; b < 3; b++)
							{
								for (int c = 0; c < 3; c++)
								{
									relevantPos = convertedTilePos + FVector2D(c, b);

									landscapeArr[relevantPos.Y * 15 + relevantPos.X] = 29;
								}
							}

							pondPositionArr.Add(convertedTilePos);
							pondSpecifierArr.Add(24);
						}
						else
						{
							landscapeArr[a] = 20 + FMath::RandRange(0, 3);
						}

						canAddLargeTile = true;
					}
					else
					{
						landscapeArr[a] = 29 + FMath::RandRange(1, 3);
					}
				}
			}
		}
		break;
	case 2:
		//gradient of thin to thick tree cover
		switch (FMath::RandRange(0, 1))
		{
		case 0:
			//gradient dir 2, thin to thick
			for (int a = 0; a < 225; a++)
			{
				if (landscapeArr[a] == 0)
				{
					if (tileIsTrack[a])
					{
						landscapeArr[a] = 29 + FMath::RandRange(1, 3);
					}
					else
					{
						if (FMath::RandRange(0, 24) < (a % 15) + 4)
						{
							convertedTilePos.X = a % 15;
							convertedTilePos.Y = a / 15;
							if (convertedTilePos.X < 13 && convertedTilePos.Y < 13 && a % 15 > 8)
							{
								for (int b = 0; b < 3; b++)
								{
									for (int c = 0; c < 3; c++)
									{
										relevantPos = convertedTilePos + FVector2D(c, b);

										if (landscapeArr[relevantPos.Y * 15 + relevantPos.X] || tileIsTrack[relevantPos.Y * 15 + relevantPos.X])
										{
											canAddLargeTile = false;
										}
									}
								}
							}
							else
							{
								canAddLargeTile = false;
							}

							if (canAddLargeTile && FMath::RandRange(0, 32) < numberOfHoles)
							{
								for (int b = 0; b < 3; b++)
								{
									for (int c = 0; c < 3; c++)
									{
										relevantPos = convertedTilePos + FVector2D(c, b);

										landscapeArr[relevantPos.Y * 15 + relevantPos.X] = 29;
									}
								}

								pondPositionArr.Add(convertedTilePos);
								pondSpecifierArr.Add(24);
							}
							else
							{
								landscapeArr[a] = 20 + FMath::RandRange(0, 3);
							}

							canAddLargeTile = true;
						}
						else
						{
							convertedTilePos.X = a % 15;
							convertedTilePos.Y = a / 15;

							if (convertedTilePos.X < 13 && convertedTilePos.Y < 13 && a < 89 && a % 15 < 9)
							{
								for (int b = 0; b < 3; b++)
								{
									for (int c = 0; c < 3; c++)
									{
										relevantPos = convertedTilePos + FVector2D(c, b);

										if (landscapeArr[relevantPos.Y * 15 + relevantPos.X] || tileIsTrack[relevantPos.Y * 15 + relevantPos.X])
										{
											canAddLargeTile = false;
										}
									}
								}
							}
							else
							{
								canAddLargeTile = false;
							}

							if (canAddLargeTile && FMath::RandRange(0, 24) < numberOfHoles)
							{
								for (int b = 0; b < 3; b++)
								{
									for (int c = 0; c < 3; c++)
									{
										relevantPos = convertedTilePos + FVector2D(c, b);

										landscapeArr[relevantPos.Y * 15 + relevantPos.X] = 29;
									}
								}

								pondPositionArr.Add(convertedTilePos);
								pondSpecifierArr.Add(33);
							}
							else
							{
								landscapeArr[a] = 29 + FMath::RandRange(1, 3);
							}
							canAddLargeTile = true;
						}
					}
				}
			}
			break;
		case 1:
			//gradient dir 4, thin to thick
			for (int a = 0; a < 225; a++)
			{
				if (landscapeArr[a] == 0)
				{
					if (tileIsTrack[a])
					{
						landscapeArr[a] = 29 + FMath::RandRange(1, 3);
					}
					else
					{
						if (FMath::RandRange(0, 24) > (a % 15) + 4)
						{
							convertedTilePos.X = a % 15;
							convertedTilePos.Y = a / 15;
							if (convertedTilePos.X < 13 && convertedTilePos.Y < 13 && a % 15 < 8)
							{
								for (int b = 0; b < 3; b++)
								{
									for (int c = 0; c < 3; c++)
									{
										relevantPos = convertedTilePos + FVector2D(c, b);

										if (landscapeArr[relevantPos.Y * 15 + relevantPos.X] || tileIsTrack[relevantPos.Y * 15 + relevantPos.X])
										{
											canAddLargeTile = false;
										}
									}
								}
							}
							else
							{
								canAddLargeTile = false;
							}

							if (canAddLargeTile && FMath::RandRange(0, 32) < numberOfHoles)
							{
								for (int b = 0; b < 3; b++)
								{
									for (int c = 0; c < 3; c++)
									{
										relevantPos = convertedTilePos + FVector2D(c, b);

										landscapeArr[relevantPos.Y * 15 + relevantPos.X] = 29;
									}
								}

								pondPositionArr.Add(convertedTilePos);
								pondSpecifierArr.Add(24);
							}
							else
							{
								landscapeArr[a] = 20 + FMath::RandRange(0, 3);
							}

							canAddLargeTile = true;
						}
						else
						{
							convertedTilePos.X = a % 15;
							convertedTilePos.Y = a / 15;

							if (convertedTilePos.X < 13 && convertedTilePos.Y < 13 && a < 89 && a % 15 > 7)
							{
								for (int b = 0; b < 3; b++)
								{
									for (int c = 0; c < 3; c++)
									{
										relevantPos = convertedTilePos + FVector2D(c, b);

										if (landscapeArr[relevantPos.Y * 15 + relevantPos.X] || tileIsTrack[relevantPos.Y * 15 + relevantPos.X])
										{
											canAddLargeTile = false;
										}
									}
								}
							}
							else
							{
								canAddLargeTile = false;
							}

							if (canAddLargeTile && FMath::RandRange(0, 24) < numberOfHoles)
							{
								for (int b = 0; b < 3; b++)
								{
									for (int c = 0; c < 3; c++)
									{
										relevantPos = convertedTilePos + FVector2D(c, b);

										landscapeArr[relevantPos.Y * 15 + relevantPos.X] = 29;
									}
								}

								pondPositionArr.Add(convertedTilePos);
								pondSpecifierArr.Add(33);
							}
							else
							{
								landscapeArr[a] = 29 + FMath::RandRange(1, 3);
							}
							canAddLargeTile = true;
						}
					}
				}
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	for (int a : landscapeArr)
	{
		switch (a)
		{
		case 0:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				grass_MP_1->OpenSource(grass_IS_1);
			}
			break;
		case 1:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				holeFromDown_MP->OpenSource(holeFromDown_IS);
			}
			break;
		case 2:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				holeFromLeft_MP->OpenSource(holeFromLeft_IS);
			}
			break;
		case 3:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				holeFromRight_MP->OpenSource(holeFromRight_IS);
			}
			break;
		case 4:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				holeFromUp_MP->OpenSource(holeFromUp_IS);
			}
			break;
		case 5:
			break;
		case 6:
			break;
		case 11:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				riverFlowingDown_MP_1->OpenSource(riverFlowingDown_IS_1);
			}
			break;
		case 12:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				riverFlowingDown_MP_2->OpenSource(riverFlowingDown_IS_2);
			}
			break;
		case 13:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				riverFlowingDown_MP_3->OpenSource(riverFlowingDown_IS_3);
			}
			break;
		case 14:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				riverFlowingLeft_MP_1->OpenSource(riverFlowingLeft_IS_1);
			}
			break;
		case 15:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				riverFlowingLeft_MP_2->OpenSource(riverFlowingLeft_IS_2);
			}
			break;
		case 16:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				riverFlowingLeft_MP_3->OpenSource(riverFlowingLeft_IS_3);
			}
			break;
		case 17:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				riverFlowingRight_MP_1->OpenSource(riverFlowingRight_IS_1);
			}
			break;
		case 18:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				riverFlowingRight_MP_2->OpenSource(riverFlowingRight_IS_2);
			}
			break;
		case 19:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				riverFlowingRight_MP_3->OpenSource(riverFlowingRight_IS_3);
			}
			break;
		case 20:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				tree_MP_1->OpenSource(tree_IS_1);
			}
			break;
		case 21:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				tree_MP_2->OpenSource(tree_IS_2);
			}
			break;
		case 22:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				tree_MP_3->OpenSource(tree_IS_3);
			}
			break;
		case 23:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				tree_MP_4->OpenSource(tree_IS_4);
			}
			break;
		case 25:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				riverTurning_MP_1->OpenSource(riverTurning_IS_1);
			}
			break;
		case 26:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				riverTurning_MP_2->OpenSource(riverTurning_IS_2);
			}
			break;
		case 27:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				riverTurning_MP_3->OpenSource(riverTurning_IS_3);
			}
			break;
		case 28:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				riverTurning_MP_4->OpenSource(riverTurning_IS_4);
			}
			break;
		case 29:
			break;
		case 30:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				grass_MP_1->OpenSource(grass_IS_1);
			}
			break;
		case 31:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				grass_MP_2->OpenSource(grass_IS_2);
			}
			break;
		case 32:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				grass_MP_3->OpenSource(grass_IS_3);
			}
			break;
		default:
			break;
		}
	}

	environmentAudio = 0;

	for (int a : pondSpecifierArr)
	{
		switch (a)
		{
		case 7:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				pondHorizontal_MP->OpenSource(pondHorizontal_IS);
			}
			break;
		case 8:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				pondVerticleFlowingLeft_MP->OpenSource(pondVerticleFlowingLeft_IS);
			}
			break;
		case 9:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				pondVerticleFlowingRight_MP->OpenSource(pondVerticleFlowingRight_IS);
			}
			break;
		case 10:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				environmentAudio = 1;
				waterfall_MP->OpenSource(waterfall_IS);
			}
			break;
		case 24:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				tree_MP_5->OpenSource(tree_IS_5);
			}
			break;
		case 33:
			if (activeMediaPlayers[a] == false)
			{
				activeMediaPlayers[a] = true;
				mountain_MP_1->OpenSource(mountain_IS_1);
			}
			break;
		default:
			break;
		}
	}

	for (int a = 0; a < numberOfHoles; a++)
	{
		switch (a)
		{
		case 0:
			flag_MP_1->OpenSource(flag_IS_1);
			break;
		case 1:
			flag_MP_2->OpenSource(flag_IS_2);
			break;
		case 2:
			flag_MP_3->OpenSource(flag_IS_3);
			break;
		case 3:
			flag_MP_4->OpenSource(flag_IS_4);
			break;
		case 4:
			flag_MP_5->OpenSource(flag_IS_5);
			break;
		case 5:
			flag_MP_6->OpenSource(flag_IS_6);
			break;
		case 6:
			flag_MP_7->OpenSource(flag_IS_7);
			break;
		case 7:
			flag_MP_8->OpenSource(flag_IS_8);
			break;
		case 8:
			flag_MP_9->OpenSource(flag_IS_9);
			break;
		case 9:
			flag_MP_10->OpenSource(flag_IS_10);
			break;
		case 10:
			flag_MP_11->OpenSource(flag_IS_11);
			break;
		case 11:
			flag_MP_12->OpenSource(flag_IS_12);
			break;
		case 12:
			flag_MP_13->OpenSource(flag_IS_13);
			break;
		case 13:
			flag_MP_14->OpenSource(flag_IS_14);
			break;
		case 14:
			flag_MP_15->OpenSource(flag_IS_15);
			break;
		case 15:
			flag_MP_16->OpenSource(flag_IS_16);
			break;
		default:
			break;
		}
	}

	if (finalIntersectionPos.Y > 14 || finalIntersectionPos.X < 2 || finalIntersectionPos.X > 14)
	{
		regenerateLevel.Add(1);
		return;
	}
	else
	{
		for (int a : tileIsTrack)
		{
			if (a > 1)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "REGENERATION TRIGGERED ");
				regenerateLevel.Add(1);
				return;
			}
		}
	}


	if (GEngine && GEngine->GameViewport)
	{
		gameSlateWidget = SNew(STestWidgetThree)
			.OwningHUD(this)
			.standardWorldContextObject(standardWorldContextObject)
			.landscapeArr(landscapeArr)
			.trackArr(trackArr)
			.pondSpecifierArr(pondSpecifierArr)
			.pondPositionArr(pondPositionArr)
			.tileIsIntersection(tileIsIntersection)
			.playerOnePlayerController(playerOnePlayerController)
			.startingPos(startingPos)
			.startingDir(startingDir)
			.holePositions(convertedHolePositions)
			.grass_VMUI_1(grass_VMUI_1)
			.grass_VMUI_2(grass_VMUI_2)
			.grass_VMUI_3(grass_VMUI_3)
			.pondHorizontal_VMUI(pondHorizontal_VMUI)
			.pondVerticleFlowingLeft_VMUI(pondVerticleFlowingLeft_VMUI)
			.pondVerticleFlowingRight_VMUI(pondVerticleFlowingRight_VMUI)
			.riverFlowingDown_VMUI_1(riverFlowingDown_VMUI_1)
			.riverFlowingDown_VMUI_2(riverFlowingDown_VMUI_2)
			.riverFlowingDown_VMUI_3(riverFlowingDown_VMUI_3)
			.riverFlowingLeft_VMUI_1(riverFlowingLeft_VMUI_1)
			.riverFlowingLeft_VMUI_2(riverFlowingLeft_VMUI_2)
			.riverFlowingLeft_VMUI_3(riverFlowingLeft_VMUI_3)
			.riverFlowingRight_VMUI_1(riverFlowingRight_VMUI_1)
			.riverFlowingRight_VMUI_2(riverFlowingRight_VMUI_2)
			.riverFlowingRight_VMUI_3(riverFlowingRight_VMUI_3)
			.tree_VMUI_1(tree_VMUI_1)
			.tree_VMUI_2(tree_VMUI_2)
			.tree_VMUI_3(tree_VMUI_3)
			.tree_VMUI_4(tree_VMUI_4)
			.tree_VMUI_5(tree_VMUI_5)
			.waterfall_VMUI(waterfall_VMUI)
			.riverTurning_VMUI_1(riverTurning_VMUI_1)
			.riverTurning_VMUI_2(riverTurning_VMUI_2)
			.riverTurning_VMUI_3(riverTurning_VMUI_3)
			.riverTurning_VMUI_4(riverTurning_VMUI_4)
			.mountain_VMUI_1(mountain_VMUI_1)
			.holeFromDown_VMUI(holeFromDown_VMUI)
			.holeFromLeft_VMUI(holeFromLeft_VMUI)
			.holeFromRight_VMUI(holeFromRight_VMUI)
			.holeFromUp_VMUI(holeFromUp_VMUI)
			.flag_VMUI_1(flag_VMUI_1)
			.flag_VMUI_2(flag_VMUI_2)
			.flag_VMUI_3(flag_VMUI_3)
			.flag_VMUI_4(flag_VMUI_4)
			.flag_VMUI_5(flag_VMUI_5)
			.flag_VMUI_6(flag_VMUI_6)
			.flag_VMUI_7(flag_VMUI_7)
			.flag_VMUI_8(flag_VMUI_8)
			.flag_VMUI_9(flag_VMUI_9)
			.flag_VMUI_10(flag_VMUI_10)
			.flag_VMUI_11(flag_VMUI_11)
			.flag_VMUI_12(flag_VMUI_12)
			.flag_VMUI_13(flag_VMUI_13)
			.flag_VMUI_14(flag_VMUI_14)
			.flag_VMUI_15(flag_VMUI_15)
			.flag_VMUI_16(flag_VMUI_16)
			.buttonFromDownTurningRightZero_SMUI(buttonFromDownTurningRightZero_SMUI)
			.buttonFromDownTurningRightOne_SMUI(buttonFromDownTurningRightOne_SMUI)
			.buttonFromDownTurningRightTwo_SMUI(buttonFromDownTurningRightTwo_SMUI)
			.buttonFromDownTurningRightThree_SMUI(buttonFromDownTurningRightThree_SMUI)
			.buttonFromDownTurningLeftZero_SMUI(buttonFromDownTurningLeftZero_SMUI)
			.buttonFromDownTurningLeftOne_SMUI(buttonFromDownTurningLeftOne_SMUI)
			.buttonFromDownTurningLeftTwo_SMUI(buttonFromDownTurningLeftTwo_SMUI)
			.buttonFromDownTurningLeftThree_SMUI(buttonFromDownTurningLeftThree_SMUI)
			.buttonFromLeftTurningRightZero_SMUI(buttonFromLeftTurningRightZero_SMUI)
			.buttonFromLeftTurningRightOne_SMUI(buttonFromLeftTurningRightOne_SMUI)
			.buttonFromLeftTurningRightTwo_SMUI(buttonFromLeftTurningRightTwo_SMUI)
			.buttonFromLeftTurningRightThree_SMUI(buttonFromLeftTurningRightThree_SMUI)
			.buttonFromLeftTurningLeftZero_SMUI(buttonFromLeftTurningLeftZero_SMUI)
			.buttonFromLeftTurningLeftOne_SMUI(buttonFromLeftTurningLeftOne_SMUI)
			.buttonFromLeftTurningLeftTwo_SMUI(buttonFromLeftTurningLeftTwo_SMUI)
			.buttonFromLeftTurningLeftThree_SMUI(buttonFromLeftTurningLeftThree_SMUI)
			.buttonFromRightTurningRightZero_SMUI(buttonFromRightTurningRightZero_SMUI)
			.buttonFromRightTurningRightOne_SMUI(buttonFromRightTurningRightOne_SMUI)
			.buttonFromRightTurningRightTwo_SMUI(buttonFromRightTurningRightTwo_SMUI)
			.buttonFromRightTurningRightThree_SMUI(buttonFromRightTurningRightThree_SMUI)
			.buttonFromRightTurningLeftZero_SMUI(buttonFromRightTurningLeftZero_SMUI)
			.buttonFromRightTurningLeftOne_SMUI(buttonFromRightTurningLeftOne_SMUI)
			.buttonFromRightTurningLeftTwo_SMUI(buttonFromRightTurningLeftTwo_SMUI)
			.buttonFromRightTurningLeftThree_SMUI(buttonFromRightTurningLeftThree_SMUI)
			.buttonFromUpTurningRightZero_SMUI(buttonFromUpTurningRightZero_SMUI)
			.buttonFromUpTurningRightOne_SMUI(buttonFromUpTurningRightOne_SMUI)
			.buttonFromUpTurningRightTwo_SMUI(buttonFromUpTurningRightTwo_SMUI)
			.buttonFromUpTurningRightThree_SMUI(buttonFromUpTurningRightThree_SMUI)
			.buttonFromUpTurningLeftZero_SMUI(buttonFromUpTurningLeftZero_SMUI)
			.buttonFromUpTurningLeftOne_SMUI(buttonFromUpTurningLeftOne_SMUI)
			.buttonFromUpTurningLeftTwo_SMUI(buttonFromUpTurningLeftTwo_SMUI)
			.buttonFromUpTurningLeftThree_SMUI(buttonFromUpTurningLeftThree_SMUI)
			.verticleRail_SMUI(verticleRail_SMUI)
			.horizontalRail_SMUI(horizontalRail_SMUI)
			.railTurningOne_SMUI(railTurningOne_SMUI)
			.railTurningTwo_SMUI(railTurningTwo_SMUI)
			.railTurningThree_SMUI(railTurningThree_SMUI)
			.railTurningFour_SMUI(railTurningFour_SMUI)
			.emptyImg_SMUI(emptyImg_SMUI)
			.gameFrameColor_SMUI(gameFrameColor_SMUI)
			.marble_SMUI_1(marble_SMUI_1)
			.marble_SMUI_2(marble_SMUI_2)
			.marble_SMUI_3(marble_SMUI_3)
			.marble_SMUI_4(marble_SMUI_4)
			.marble_SMUI_5(marble_SMUI_5)
			.marble_SMUI_6(marble_SMUI_6)
			.marble_SMUI_7(marble_SMUI_7)
			.marble_SMUI_8(marble_SMUI_8)
			.marble_SMUI_9(marble_SMUI_9)
			.marble_SMUI_10(marble_SMUI_10)
			.marble_SMUI_11(marble_SMUI_11)
			.marble_SMUI_12(marble_SMUI_12)
			.marble_SMUI_13(marble_SMUI_13)
			.marble_SMUI_14(marble_SMUI_14)
			.marble_SMUI_15(marble_SMUI_15)
			.marble_SMUI_16(marble_SMUI_16)
			.intersectionDownAudioComponent(intersectionDownAudioComponent)
			.intersectionUpAudioComponent(intersectionUpAudioComponent)
			.windAudioComponents(windAudioComponents)
			.riverAudioComponents(riverAudioComponents)
			.waterfallAudioComponents(waterfallAudioComponents)
			.scoringAudioComponents(scoringAudioComponents)
			.missAudioComponent(missAudioComponent)
			.songAudioComponents(songAudioComponents)
			.environmentAudio(environmentAudio)
			.songPlaying(songPlaying)
			.songPlayingIndex(songPlayingIndex);

		slateWidgetContainerTwo->SetContent(gameSlateWidget.ToSharedRef());

		FInputModeUIOnly gameInWidgetInputMode = FInputModeUIOnly();
		gameInWidgetInputMode.SetWidgetToFocus(gameSlateWidget);
		gameInWidgetInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		playerOnePlayerController->SetInputMode(gameInWidgetInputMode);
		playerOnePlayerController->SetShowMouseCursor(true);
		FSlateApplication::Get().SetKeyboardFocus(gameSlateWidget);
	}

	USaveGameOne* referenceInstance = Cast<USaveGameOne>(UGameplayStatics::LoadGameFromSlot(TEXT("saveGameOne"), 0));
	double h = 1;

	if (referenceInstance->GetMaster() == 0 || referenceInstance->GetAtmosphere() == 0)
	{
		h = 0.001;
	}

	for (int a = 0; a < 2; a++)
	{
		windAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)1.0 * (double)atmosphereCoefficientOne) - (double)((double)((double)((double)1.0 * (double)atmosphereCoefficientOne) - ((double)1.0 * (double)destinationCoefficient)) * (double)((double)1 - (double)masterCoefficientAOne))) * (double)h, (double)0.001, (double)1.0));
		riverAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.16 * (double)atmosphereCoefficientTwo) - (double)((double)((double)((double)0.16 * (double)atmosphereCoefficientTwo) - ((double)0.16 * (double)destinationCoefficientThree)) * (double)((double)1 - (double)masterCoefficientATwo))) * (double)h, (double)0.001, (double)0.16));
		waterfallAudioComponents[a]->SetVolumeMultiplier(FMath::Clamp((double)((double)((double)0.4 * (double)atmosphereCoefficientThree) - (double)((double)((double)((double)0.4 * (double)atmosphereCoefficientThree) - ((double)0.4 * (double)destinationCoefficientTwo)) * (double)((double)1 - (double)masterCoefficientAThree))) * (double)h, (double)0.001, (double)0.4));
	}
}

void AMyHUD::GenerateLevel()
{
	GenerateHolePositions();

	GenerateTrackShape();

	BuildLevel();
}

void AMyHUD::SetFocusToGame()
{
	FInputModeUIOnly gameInWidgetInputMode = FInputModeUIOnly();
	gameInWidgetInputMode.SetWidgetToFocus(gameSlateWidget);
	gameInWidgetInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	playerOnePlayerController->SetInputMode(gameInWidgetInputMode);
	playerOnePlayerController->SetShowMouseCursor(true);
	FSlateApplication::Get().SetKeyboardFocus(gameSlateWidget);
}

void AMyHUD::HouseKeeping()
{
	grass_MP_1->Close();
	grass_MP_2->Close();
	grass_MP_3->Close();
	pondHorizontal_MP->Close();
	pondVerticleFlowingLeft_MP->Close();
	pondVerticleFlowingRight_MP->Close();
	riverFlowingDown_MP_1->Close();
	riverFlowingDown_MP_2->Close();
	riverFlowingDown_MP_3->Close();
	riverFlowingLeft_MP_1->Close();
	riverFlowingLeft_MP_2->Close();
	riverFlowingLeft_MP_3->Close();
	riverFlowingRight_MP_1->Close();
	riverFlowingRight_MP_2->Close();
	riverFlowingRight_MP_3->Close();
	tree_MP_1->Close();
	tree_MP_2->Close();
	tree_MP_3->Close();
	tree_MP_4->Close();
	tree_MP_5->Close();
	waterfall_MP->Close();
	riverTurning_MP_1->Close();
	riverTurning_MP_2->Close();
	riverTurning_MP_3->Close();
	riverTurning_MP_4->Close();
	mountain_MP_1->Close();

	holeFromDown_MP->Close();
	holeFromLeft_MP->Close();
	holeFromRight_MP->Close();
	holeFromUp_MP->Close();

	flag_MP_1->Close();
	flag_MP_2->Close();
	flag_MP_3->Close();
	flag_MP_4->Close();
	flag_MP_5->Close();
	flag_MP_6->Close();
	flag_MP_7->Close();
	flag_MP_8->Close();
	flag_MP_9->Close();
	flag_MP_10->Close();
	flag_MP_11->Close();
	flag_MP_12->Close();
	flag_MP_13->Close();
	flag_MP_14->Close();
	flag_MP_15->Close();
	flag_MP_16->Close();

	arrOfViableHoleCoordinates.Empty();
	holePositions.Empty();
	convertedHolePositions.Empty();
	test.Empty();
	listOfHolePositionGroupings.Empty();
	negativeOneZeroOrOne = 0;
	extentOfAdjustment = 2 - FMath::Clamp(numberOfHoles - 8, 0, 1);;
	pondPositionArr.Empty();
	pondSpecifierArr.Empty();
	largeTreeOrMountainPosArr.Empty();
	activeMediaPlayers = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

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

	tileIsTrack = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	backgroundArr = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
}

void AMyHUD::ResetRegenLevel()
{
	regenerateLevel.Empty();
}