// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "MyHUD.h"
#include "MyPlayerController.h"

AMyGameModeBase::AMyGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("'/Game/Misc/PlayerCharacter.PlayerCharacter'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = AMyPlayerController::StaticClass();
	HUDClass = AMyHUD::StaticClass();
}

