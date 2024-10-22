// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameOne.generated.h"

/**
 * 
 */
UCLASS()
class FIVEPOINTFOURREBUILD_API USaveGameOne : public USaveGame
{
	GENERATED_BODY()
public:
	USaveGameOne();
	//FString SaveSlotName;
	//int UserIndex;
protected:
	UPROPERTY(SaveGame) TArray <int> highscores;
	UPROPERTY(SaveGame) int highscoreDataOne;
	UPROPERTY(SaveGame) int highscoreDataTwo;
	UPROPERTY(SaveGame) int maxLevel;
	UPROPERTY(SaveGame) int scoreThisGame;//then from here you may also include options data but the system may automatically save that
	UPROPERTY(SaveGame) double masterVolume;
	UPROPERTY(SaveGame) double musicVolume;
	UPROPERTY(SaveGame) double atmosphereVolume;
	UPROPERTY(SaveGame) double sfxVolume;
	UPROPERTY(SaveGame) FKey pauseKey;
	UPROPERTY(SaveGame) FKey pauseMouse;
	UPROPERTY(SaveGame) FKey selectKey;
	UPROPERTY(SaveGame) FKey moveKey;
	UPROPERTY(SaveGame) FKey pauseController;
	UPROPERTY(SaveGame) FKey selectController;
	UPROPERTY(SaveGame) FKey moveController;
	UPROPERTY(SaveGame) TArray<int> songIndexArr;

public:
	TArray<int> GetHighscores();
	int GetHighscoreDataOne();
	int GetHighscoreDataTwo();
	int GetMaxLevel();
	int GetScoreThisGame();
	double GetMaster();
	double GetMusic();
	double GetAtmosphere();
	double GetSFX();
	FKey GetPauseKey();
	FKey GetPauseMouse();
	FKey GetSelectKey();
	FKey GetMoveKey();
	FKey GetPauseController();
	FKey GetSelectController();
	FKey GetMoveController();
	TArray<int> GetSongIndexArr();

	void SetHighscores(TArray<int> newHighscores);
	void SetHighscoreDataOne(int newHighscoreData);
	void SetHighscoreDataTwo(int newHighscoreData);
	void SetMaxLevel(int newMaxLevel);
	void SetScoreThisGame(int score);
	void SetMaster(double newVol);
	void SetMusic(double newVol);
	void SetAtmosphere(double newVol);
	void SetSFX(double newVol);
	void SetPauseKey(FKey newKey);
	void SetPauseMouse(FKey newKey);
	void SetSelectKey(FKey newKey);
	void SetMoveKey(FKey newKey);
	void SetPauseController(FKey newKey);
	void SetSelectController(FKey newKey);
	void SetMoveController(FKey newKey);
	void SetSongIndexArr(TArray<int> newArr);
};
