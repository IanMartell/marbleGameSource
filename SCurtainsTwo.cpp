// Fill out your copyright notice in the Description page of Project Settings.


#include "SCurtainsTwo.h"
#include "Components/AudioComponent.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SCurtainsTwo::Construct(const FArguments& InArgs)
{
	SetCanTick(true);

	OwningHUD = InArgs._OwningHUD;
	curtains_VMUI = InArgs._curtains_VMUI;
	curtainOpeningAudioComponent = InArgs._curtainOpeningAudioComponent;

	curtains_SB = new FSlateBrush();
	curtains_SB->SetResourceObject(curtains_VMUI);

	canLoad = true;
	timeToLoadStage = 0;

	curtainOpeningAudioComponent->SetVolumeMultiplier(1.0);
	canPlaySoundEffect = true;

	curtainOverlay = SNew(SOverlay);
	curtainOverlay->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SImage)
				.Image(curtains_SB)
		];

	ChildSlot
		[
			SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					curtainOverlay.ToSharedRef()
				]
		];

}

void SCurtainsTwo::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	timeToLoadStage += InDeltaTime;

	if (timeToLoadStage > 0.333 && canLoad)
	{
		OwningHUD->ReturnToMainMenu();
		canLoad = false;
		//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "1");
	}

	if (timeToLoadStage > 0.666 && canPlaySoundEffect)
	{
		curtainOpeningAudioComponent->Play();
		canPlaySoundEffect = false;
		//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "2");
	}

	if (timeToLoadStage > 1)
	{
		OwningHUD->HideCurtains(false);
		//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "3");
	}
	//GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, FString::SanitizeFloat(timeToLoadStage));
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
