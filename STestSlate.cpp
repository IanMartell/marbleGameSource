
#include "STestSlate.h"
#include "TestHud.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "GameFramework/GameUserSettings.h"

#define LOCTEXT_NAMESPACE "TestSlate"

void STestSlate::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;

	OwningHUD = InArgs._OwningHUD;

	const FMargin contentPadding = FMargin(166.f, 100.f);
	const FMargin buttonPadding = FMargin(10.f);

	const FText titleText = LOCTEXT("GameTitle", "Marble Game");
	const FText playText = LOCTEXT("PlayGame", "Play");
	const FText settingsText = LOCTEXT("Settings", "Settings");
	const FText quitText = LOCTEXT("QuitGame", "Quit");

	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	ButtonTextStyle.Size = 40.f;

	FSlateFontInfo TitleTextStyle = ButtonTextStyle;
	TitleTextStyle.Size = 60.f;

	ChildSlot
		[
			SNew(SOverlay) 
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.ColorAndOpacity(FColor::Yellow)
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(contentPadding)
			[
				SNew(SVerticalBox)

				//title text
				+ SVerticalBox::Slot()
				[
					SNew(STextBlock)
					.Font(TitleTextStyle)
					.Text(titleText)
					.Justification(ETextJustify::Center)
				]

				//play button
				+ SVerticalBox::Slot()
				.Padding(buttonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &STestSlate::OnPlayClicked)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(playText)
						.Justification(ETextJustify::Center)
					]
				]

				//settings button
				+ SVerticalBox::Slot()
				.Padding(buttonPadding)
				[
					SNew(SButton)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(settingsText)
						.Justification(ETextJustify::Center)
					]
				]

				//quit button
				+ SVerticalBox::Slot()
				.Padding(buttonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &STestSlate::OnQuitClicked)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(quitText)
						.Justification(ETextJustify::Center)
					]
				]
			]
		];
}

FReply STestSlate::OnPlayClicked() const
{
	UGameUserSettings* myGameSettings = GEngine->GetGameUserSettings();

	GEngine->AddOnScreenDebugMessage(-1, 200.0, FColor::Red, "working");

	return FReply::Handled();
}

FReply STestSlate::OnQuitClicked() const
{
	if (OwningHUD.IsValid())
	{
		if (APlayerController* PC = OwningHUD->PlayerOwner)
		{
			PC->ConsoleCommand("Quit");
		}
	}

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE