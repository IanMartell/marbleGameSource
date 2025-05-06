// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyHUD.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class FIVEPOINTFOURREBUILD_API SLoadingSplash : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLoadingSplash) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwningHUD)

	SLATE_ARGUMENT(UMaterial*, black_SMUI)

	SLATE_ARGUMENT(UMaterial*, logo_SMUI)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);
	void SetOperateFour(bool inBool);

	UPROPERTY() TWeakObjectPtr<class AMyHUD> OwningHUD;

	UPROPERTY() TSharedPtr< class SOverlay> overlay;


	UPROPERTY() TSharedPtr< class SImage> logoImg;
	UPROPERTY() TSharedPtr< class SBox> boxOne;
	UPROPERTY() TSharedPtr< class SImage> fade;
	UPROPERTY() FLinearColor fadeLinearColor;
	UPROPERTY() float fadeTimer;

	UPROPERTY() FVector2D viewportSize;
	UPROPERTY() FVector2D adjustedViewportSize;
	UPROPERTY() float DPIScale;

	UPROPERTY() UMaterial* black_SMUI;
	UPROPERTY() UMaterial* logo_SMUI;

	UPROPERTY() FSlateBrush* black_SB;
	UPROPERTY() FSlateBrush* logo_SB;

	UPROPERTY() bool operate;
	UPROPERTY() int operateTimer;

	UPROPERTY() bool operateTwo;
	UPROPERTY() bool operateThree;
	UPROPERTY() bool operateFour;
	UPROPERTY() int operateTimerTwo;

	UPROPERTY() float globalFOne;
};
