// Fill out your copyright notice in the Description page of Project Settings.


#include "SCurtains.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SCurtains::Construct(const FArguments& InArgs)
{
	SetCanTick(true);

	OwningHUD = InArgs._OwningHUD;
	curtains_VMUI = InArgs._curtains_VMUI;
	x = InArgs._x;

	curtains_SB = new FSlateBrush();
	curtains_SB->SetResourceObject(curtains_VMUI);

	canLoad = true;
	timeToLoadStage = 0;
	
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

void SCurtains::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	timeToLoadStage += InDeltaTime;

	if (timeToLoadStage > 0.125 && canLoad)
	{
		OwningHUD->MasterGenerateLevel(x);
		canLoad = false;
	}

	if (timeToLoadStage > 0.442)
	{
		OwningHUD->HideCurtains();
	}
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
