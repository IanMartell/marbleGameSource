// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "MyHUD.h"
#include "MyPlayerController.h"

AMyGameModeBase::AMyGameModeBase()
{
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("'/Game/Misc/BP_MyCharacter.BP_MyCharacter'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("'/Game/Misc/BP_MyPlayerController.BP_MyPlayerController'"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}*/

	//PlayerControllerClass = AMyPlayerController::StaticClass();
	HUDClass = AMyHUD::StaticClass();
}

