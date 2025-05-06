// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "mediaPlayer.h"
#include "MediaSource.h"
#include "BaseMediaSource.h"
#include "ImgMediaSource.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

AMyPlayerController::AMyPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_neon_VMUI(TEXT("'/Game/Movies/videoMaterialsForUI/neon_VMUI.neon_VMUI'"));
	if (tempVar_neon_VMUI.Object != NULL)
	{
		neon_VMUI = (UMaterial*)tempVar_neon_VMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMediaPlayer> tempVar_neon_MP(TEXT("'/Game/Movies/MediaPlayers/neon_MP.neon_MP'"));
	if (tempVar_neon_MP.Object != NULL)
	{
		neon_MP = (UMediaPlayer*)tempVar_neon_MP.Object;
	}
	static ConstructorHelpers::FObjectFinder<UImgMediaSource> tempVar_neon_IS(TEXT("'/Game/Movies/imageSources/neon_IS.neon_IS'"));
	if (tempVar_neon_IS.Object != NULL)
	{
		neon_IS = (UImgMediaSource*)tempVar_neon_IS.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_neonClicked_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/neonClicked_SMUI.neonClicked_SMUI'"));
	if (tempVar_neonClicked_SMUI.Object != NULL)
	{
		neonClicked_SMUI = (UMaterial*)tempVar_neonClicked_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_neonLit_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/neonLit_SMUI.neonLit_SMUI'"));
	if (tempVar_neonLit_SMUI.Object != NULL)
	{
		neonLit_SMUI = (UMaterial*)tempVar_neonLit_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_neonUnlit_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/neonUnlit_SMUI.neonUnlit_SMUI'"));
	if (tempVar_neonUnlit_SMUI.Object != NULL)
	{
		neonUnlit_SMUI = (UMaterial*)tempVar_neonUnlit_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_neonHoveredLit_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/neonHoveredLit_SMUI.neonHoveredLit_SMUI'"));
	if (tempVar_neonHoveredLit_SMUI.Object != NULL)
	{
		neonHoveredLit_SMUI = (UMaterial*)tempVar_neonHoveredLit_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_neonHoveredUnlit_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/neonHoveredUnlit_SMUI.neonHoveredUnlit_SMUI'"));
	if (tempVar_neonHoveredUnlit_SMUI.Object != NULL)
	{
		neonHoveredUnlit_SMUI = (UMaterial*)tempVar_neonHoveredUnlit_SMUI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_neonBarricade_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/neonBarricade_SMUI.neonBarricade_SMUI'"));
	if (tempVar_neonBarricade_SMUI.Object != NULL)
	{
		neonBarricade_SMUI = (UMaterial*)tempVar_neonBarricade_SMUI.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_focusCursor_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/focusCursor_SMUI.focusCursor_SMUI'"));
	if (tempVar_focusCursor_SMUI.Object != NULL)
	{
		focusCursor_SMUI = (UMaterial*)tempVar_focusCursor_SMUI.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> tempVar_logo_SMUI(TEXT("'/Game/Movies/spriteMaterialsForUI/logo_SMUI.logo_SMUI'"));
	if (tempVar_logo_SMUI.Object != NULL)
	{
		logo_SMUI = (UMaterial*)tempVar_logo_SMUI.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_neon(TEXT("'/Game/myAdditionsArcade/soundEffects/neon.neon'"));
	neon = (USoundBase*)tempVar_neon.Object;
	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_neonOnOne(TEXT("'/Game/myAdditionsArcade/soundEffects/neonOnOne.neonOnOne'"));
	neonOnOne = (USoundBase*)tempVar_neonOnOne.Object;
	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_neonOnTwo(TEXT("'/Game/myAdditionsArcade/soundEffects/neonCorrected.neonCorrected'"));
	neonOnTwo = (USoundBase*)tempVar_neonOnTwo.Object;
	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_neonOffOne(TEXT("'/Game/myAdditionsArcade/soundEffects/neonOffOne.neonOffOne'"));
	neonOffOne = (USoundBase*)tempVar_neonOffOne.Object;
	static ConstructorHelpers::FObjectFinder<USoundBase> tempVar_neonOffTwo(TEXT("'/Game/myAdditionsArcade/soundEffects/neonOffTwo.neonOffTwo'"));
	neonOffTwo = (USoundBase*)tempVar_neonOffTwo.Object;

	neonAudioComponent = CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass()));
	neonAudioComponent->SetVolumeMultiplier(0);
	neonAudioComponent->bAutoDestroy = false;
	neonAudioComponent->SetSound(neon);

	neonOnOneAudioComponent = CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass()));
	neonOnOneAudioComponent->SetVolumeMultiplier(0);
	neonOnOneAudioComponent->bAutoDestroy = false;
	neonOnOneAudioComponent->SetSound(neonOnOne);

	neonOnTwoAudioComponent = CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass()));
	neonOnTwoAudioComponent->SetVolumeMultiplier(0);
	//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, FString::SanitizeFloat(neonOnTwoAudioComponent->VolumeMultiplier));
	neonOnTwoAudioComponent->bAutoDestroy = false;
	neonOnTwoAudioComponent->SetSound(neonOnTwo);

	neonOffOneAudioComponent = CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass()));
	neonOffOneAudioComponent->SetVolumeMultiplier(0);
	neonOffOneAudioComponent->bAutoDestroy = false;
	neonOffOneAudioComponent->SetSound(neonOffOne);

	neonOffTwoAudioComponent = CreateDefaultSubobject<UAudioComponent>(MakeUniqueObjectName(UGameplayStatics::GetPlayerPawn(standardWorldContextObject, 0), UAudioComponent::StaticClass()));
	neonOffTwoAudioComponent->SetVolumeMultiplier(0);
	neonOffTwoAudioComponent->bAutoDestroy = false;
	neonOffTwoAudioComponent->SetSound(neonOffTwo);
}

void AMyPlayerController::CauseAchievement_Implementation(int achievement)
{

}
void AMyPlayerController::ResetAchievement_Implementation()
{

}

UMaterial* AMyPlayerController::GetNeon_VMUI()//If this doesn't work I could try creating variables in C++ whose values I set in blueprint and can access through c++
{
	return neon_VMUI;
}
UMediaPlayer* AMyPlayerController::GetNeon_MP()
{
	return neon_MP;
}
UImgMediaSource* AMyPlayerController::GetNeon_IS()
{
	return neon_IS;
}
UMaterial* AMyPlayerController::GetNeonClicked_SMUI()
{
	return neonClicked_SMUI;
}
UMaterial* AMyPlayerController::GetNeonHoveredLit_SMUI()
{
	return neonHoveredLit_SMUI;
}
UMaterial* AMyPlayerController::GetNeonHoveredUnlit_SMUI()
{
	return neonHoveredUnlit_SMUI;
}
UMaterial* AMyPlayerController::GetNeonLit_SMUI()
{
	return neonLit_SMUI;
}
UMaterial* AMyPlayerController::GetNeonUnlit_SMUI()
{
	return neonUnlit_SMUI;
}
UMaterial* AMyPlayerController::GetNeonBarricade_SMUI()
{
	return neonBarricade_SMUI;
}

UMaterial* AMyPlayerController::GetFocusCursor_SMUI()
{
	return focusCursor_SMUI;
}

UMaterial* AMyPlayerController::GetLogo_SMUI()
{
	return logo_SMUI;
}

USoundBase* AMyPlayerController::GetNeon()
{
	return neon;
}
USoundBase* AMyPlayerController::GetNeonOnOne()
{
	return neonOnOne;
}
USoundBase* AMyPlayerController::GetNeonOnTwo()
{
	return neonOnTwo;
}
USoundBase* AMyPlayerController::GetNeonOffOne()
{
	return neonOffOne;
}
USoundBase* AMyPlayerController::GetNeonOffTwo()
{
	return neonOffTwo;
}

UAudioComponent* AMyPlayerController::GetNeonAudioComponent()
{
	return neonAudioComponent;
}
UAudioComponent* AMyPlayerController::GetNeonOnOneAudioComponent()
{
	return neonOnOneAudioComponent;
}
UAudioComponent* AMyPlayerController::GetNeonOnTwoAudioComponent()
{
	return neonOnTwoAudioComponent;
}
UAudioComponent* AMyPlayerController::GetNeonOffOneAudioComponent()
{
	return neonOffOneAudioComponent;
}
UAudioComponent* AMyPlayerController::GetNeonOffTwoAudioComponent()
{
	return neonOffTwoAudioComponent;
}