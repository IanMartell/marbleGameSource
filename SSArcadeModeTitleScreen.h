
#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "TestHud.h"

/**
 *
 */
class SSArcadeModeTitleScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSArcadeModeTitleScreen) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class ATestHud>, OwningHUD)

	SLATE_ARGUMENT(APlayerController*, playerOnePlayerController)

	SLATE_ARGUMENT(TArray<UMaterial*>, backgroundMaterials)

	SLATE_ARGUMENT(bool, backgroundIsLargeTile)

	SLATE_ARGUMENT(UMaterial*, gameFrameColor_SMUI)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

	void OnPlayPressed();
	void OnPlayReleased();
	void OnPlayHovered();
	void OnPlayUnHovered();

	void OnBackFloorOneReleased();
	void OnBackFloorOnePressed();

	void PlayThree();
	void PlayFour();
	void PlayFive();
	void PlaySix();
	void PlaySeven();
	void PlayEight();
	void PlayNine();
	void PlayTen();
	void PlayEleven();
	void PlayTwelve();
	void PlayThirteen();
	void PlayFourteen();
	void PlayFifteen();
	void PlaySixteen();

	float CalculateGrownMarginX(FMargin inMargin);
	float CalculateGrownMarginY(FMargin inMargin);
	FMargin GrowMargin(FMargin inMargin);
	FMargin ShrinkMargin(FMargin inMargin, int marginIndex);

	TWeakObjectPtr<class ATestHud> OwningHUD;
	APlayerController* playerOnePlayerController;

	TArray<UMaterial*> backgroundMaterials;
	TArray<FSlateBrush*> backgroundStuff;
	bool backgroundIsLargeTile;

	UMaterial* gameFrameColor_SMUI;

	FSlateBrush* gameFrameColor_SB;
	FSlateBrush* background_SB_1;
	FSlateBrush* background_SB_2;
	FSlateBrush* background_SB_3;
	FSlateBrush* background_SB_4;
	FSlateBrush* background_SB_5;
	FSlateBrush* background_SB_6;
	FSlateBrush* background_SB_7;
	FSlateBrush* background_SB_8;
	FSlateBrush* background_SB_9;


	TSharedPtr< class SOverlay> backgroundOverlay;
	TSharedPtr< class SOverlay> frameColorOverlay;
	TSharedPtr< class SOverlay> masterOverlay;
	TSharedPtr< class SOverlay> levelSelectionOverlay;
	TSharedPtr< class SOverlay> mainMenuOverlay;

	FVector2D viewportSize;
	FVector2D adjustedViewportSize;
	float DPIScale;

	FSlateFontInfo titleTextStyle;
	FSlateFontInfo subTitleTextStyle;
	FSlateFontInfo menuTextStyle;
	FSlateFontInfo playTextStyle;
	FSlateFontInfo playTextStyleProxy;
	FSlateFontInfo levelSelectorTextStyle;
	FText titleText;

	TSharedPtr<class SBox> playBox;
	TSharedPtr<class SButton> firstFloorBackButton;

	TSharedPtr<class STextBlock> playText;
	TSharedPtr<class STextBlock> backText;

	FButtonStyle* transparentButtonStyle;

	FMargin playMargin;
	FMargin playMarginProxy;
	TArray<TSharedPtr<class SBox>> shrinkingBoxes;
	TArray<TSharedPtr<class STextBlock>> shrinkingTextBlocks;
	TArray<FSlateFontInfo*> shrinkingTexts;
	TArray<float> shrinkingTimes;
	TArray<FMargin*> shrinkingMargins;
	TArray<FMargin> shrinkingMarginsStartingPoints;
	TArray<float> shrinkingAdjustedMarginSizesX;
	TArray<float> shrinkingAdjustedMarginSizesY;
	TArray<float> shrinkingFontSizes;
	TArray<float> shrinkingFontSizesStartingPoints;
	TArray<float> shrinkingAdjustedFontSizes;
	TArray<TSharedPtr<class SBox>> grownBox;
	TArray<float> shrinkTargets;
	TArray<TSharedPtr<class SBox>> growingBox;
	FSlateFontInfo* growingText;
	TSharedPtr<class STextBlock> growingTextBlock;
	FMargin* growingMargin;
	float growingFontSize;
	float startingFontSize;
	FMargin startingMargin;
	float adjustedSizeX;
	float adjustedSizeY;
	float adjustedStartingFontSize;
	FMargin adjustedStartingFMargin;
	float growTime;
	float extentOfGrowth;
	int indexOfShrinkingSubject;
};