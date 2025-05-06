// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FIVEPOINTFOURREBUILD_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CategoryOne")
	void CauseAchievement(int achievement);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CategoryOne")
	void ResetAchievement();

	UFUNCTION(BlueprintCallable, Category = "CategoryOne") UMaterial* GetNeon_VMUI();
	UFUNCTION(BlueprintCallable, Category = "CategoryOne") UMediaPlayer* GetNeon_MP();
	UFUNCTION(BlueprintCallable, Category = "CategoryOne") UImgMediaSource* GetNeon_IS();
	UFUNCTION(BlueprintCallable, Category = "CategoryOne") UMaterial* GetNeonClicked_SMUI();
	UFUNCTION(BlueprintCallable, Category = "CategoryOne") UMaterial* GetNeonHoveredLit_SMUI();
	UFUNCTION(BlueprintCallable, Category = "CategoryOne") UMaterial* GetNeonHoveredUnlit_SMUI();
	UFUNCTION(BlueprintCallable, Category = "CategoryOne") UMaterial* GetNeonLit_SMUI();
	UFUNCTION(BlueprintCallable, Category = "CategoryOne") UMaterial* GetNeonUnlit_SMUI();
	UFUNCTION(BlueprintCallable, Category = "CategoryOne") UMaterial* GetNeonBarricade_SMUI();
	UFUNCTION(BlueprintCallable, Category = "CategoryOne") UMaterial* GetFocusCursor_SMUI();
	UFUNCTION(BlueprintCallable, Category = "CategoryOne") UMaterial* GetLogo_SMUI();

	UFUNCTION(BlueprintCallable, Category = "CategoryOne") USoundBase* GetNeon();
	UFUNCTION(BlueprintCallable, Category = "CategoryOne") USoundBase* GetNeonOnOne();
	UFUNCTION(BlueprintCallable, Category = "CategoryOne") USoundBase* GetNeonOnTwo();
	UFUNCTION(BlueprintCallable, Category = "CategoryOne") USoundBase* GetNeonOffOne();
	UFUNCTION(BlueprintCallable, Category = "CategoryOne") USoundBase* GetNeonOffTwo();

	UFUNCTION(BlueprintCallable, Category = "CategoryOne") UAudioComponent* GetNeonAudioComponent();
	UFUNCTION(BlueprintCallable, Category = "CategoryOne") UAudioComponent* GetNeonOnOneAudioComponent();
	UFUNCTION(BlueprintCallable, Category = "CategoryOne") UAudioComponent* GetNeonOnTwoAudioComponent();
	UFUNCTION(BlueprintCallable, Category = "CategoryOne") UAudioComponent* GetNeonOffOneAudioComponent();
	UFUNCTION(BlueprintCallable, Category = "CategoryOne") UAudioComponent* GetNeonOffTwoAudioComponent();


	UPROPERTY() UMaterial* neon_VMUI;
	UPROPERTY() UMediaPlayer* neon_MP;
	UPROPERTY() UImgMediaSource* neon_IS;

	UPROPERTY() UMaterial* neonClicked_SMUI;
	UPROPERTY() UMaterial* neonLit_SMUI;
	UPROPERTY() UMaterial* neonUnlit_SMUI;
	UPROPERTY() UMaterial* neonHoveredLit_SMUI;
	UPROPERTY() UMaterial* neonHoveredUnlit_SMUI;
	UPROPERTY() UMaterial* neonBarricade_SMUI;
	UPROPERTY() UMaterial* focusCursor_SMUI;

	UPROPERTY() UMaterial* logo_SMUI;

	UPROPERTY() UObject* standardWorldContextObject;

	UPROPERTY() USoundBase* neon;
	UPROPERTY() USoundBase* neonOffOne;
	UPROPERTY() USoundBase* neonOffTwo;
	UPROPERTY() USoundBase* neonOnOne;
	UPROPERTY() USoundBase* neonOnTwo;

	UPROPERTY() UAudioComponent* neonAudioComponent;
	UPROPERTY() UAudioComponent* neonOffOneAudioComponent;
	UPROPERTY() UAudioComponent* neonOffTwoAudioComponent;
	UPROPERTY() UAudioComponent* neonOnOneAudioComponent;
	UPROPERTY() UAudioComponent* neonOnTwoAudioComponent;
};
