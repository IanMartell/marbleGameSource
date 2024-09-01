// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateBrushStor.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ASlateBrushStor::ASlateBrushStor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UMaterial> tempVarGrass_VMUI_1(TEXT("'/Game/Movies/videoMaterialsForUI/grass_VMUI_1.grass_VMUI_1'"));

	if (tempVarGrass_VMUI_1.Object != NULL)
	{
		grass_VMUI_1 = (UMaterial*)tempVarGrass_VMUI_1.Object;//why does this work but the next line doest? 
		//grass_VMUI_1 = &tempVarGrass_VMUI_1.Object; //error a value of type TObjectPtr<UMaterial>* cannot be assigned to entity of type UMaterial*
		//well because a cast tells the engine how to interpret the following data. in this case this achieves punning[sic] into the appropriate context
	}

	FSlateBrush* grass_1_SB = new FSlateBrush();

	grass_1_SB->SetResourceObject(grass_VMUI_1);
}

// Called when the game starts or when spawned
void ASlateBrushStor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlateBrushStor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

