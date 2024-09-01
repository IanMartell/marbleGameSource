// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "Materials/MaterialInterface.h"
#include "Engine/Classes/Materials/Material.h"
#include "Styling/SlateBrush.h"
#include "SlateBrushStor.generated.h"

UCLASS()
class MARBLEGAMEBLUEPRINT_API ASlateBrushStor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlateBrushStor();

	UMaterial* grass_VMUI_1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
