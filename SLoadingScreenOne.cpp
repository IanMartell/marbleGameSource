// Fill out your copyright notice in the Description page of Project Settings.


#include "SLoadingScreenOne.h"//these headers provided by unreal engine do not match the headers provided in the youtube tutorial on generating a widget from an empty class
#include "SlateOptMacros.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"

const FMargin CalculateTitlePosition(FVector2D viewportSize)
{
	float leftPad = viewportSize.X * 0.4;
	float topPad = viewportSize.Y * 0.1;
	float rightPad = viewportSize.X * 0.4;
	float bottomPad = viewportSize.Y * 0.8;

	return FMargin(leftPad, topPad, rightPad, bottomPad);
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#define LOCTEXT_NAMESPACE "TestSlate"
void SLoadingScreenOne::Construct(const FArguments& InArgs)
{
	deleteMe = 0;
	SetCanTick(true);
	bCanSupportFocus = true;

	OwningHUD = InArgs._OwningHUD;
	playerOnePlayerController = InArgs._playerOnePlayerController;

	GEngine->GameViewport->GetViewportSize(viewportSize);
	int32 X = FGenericPlatformMath::FloorToInt(viewportSize.X);
	int32 Y = FGenericPlatformMath::FloorToInt(viewportSize.Y);
	DPIScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(X, Y));
	adjustedViewportSize = (1 / DPIScale) * viewportSize;

	FSlateFontInfo titleTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	titleTextStyle.Size = 0.07 * adjustedViewportSize.Y;
	const FText titleText = LOCTEXT("GameTitle", "LOADING");

	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 200.0, FColor::Blue, adjustedViewportSize.ToString());
	}*/
	
	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.ColorAndOpacity(FColor::Orange)
		]		

		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateTitlePosition(adjustedViewportSize))
		[
			SNew(SImage)
			.ColorAndOpacity(FColor::Black)
		]
			
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(CalculateTitlePosition(adjustedViewportSize))
		[
			SNew(STextBlock)
			.Font(titleTextStyle)
			.Text(titleText)
			.Justification(ETextJustify::Center)
			.ColorAndOpacity(FColor::Yellow)
			.ShadowColorAndOpacity(FColor::Black)
		]
	];

}

FReply SLoadingScreenOne::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Q)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2000.0, FColor::Blue, "ganked");
	}

	if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		OwningHUD->HouseKeeping();//now this only works if all of WipeAss is completed before quit game is run. but it should be

		UKismetSystemLibrary::QuitGame(playerOnePlayerController, playerOnePlayerController, EQuitPreference::Quit, false);
	}

	return FReply::Handled();
}

void SLoadingScreenOne::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	if (!deleteMe)
	{
		deleteMe++;


	}
}

#undef LOCTEXT_NAMESPACE
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
