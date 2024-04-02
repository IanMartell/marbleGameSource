// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameOne.generated.h"
/**
 * 
 */
UCLASS()
class USaveGameOne : public USaveGame
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

public:
	TArray<int> GetHighscores();
	int GetHighscoreDataOne();
	int GetHighscoreDataTwo();
	int GetMaxLevel();
	int GetScoreThisGame();

	void SetHighscores(TArray<int> newHighscores);
	void SetHighscoreDataOne(int newHighscoreData);
	void SetHighscoreDataTwo(int newHighscoreData);
	void SetMaxLevel(int newMaxLevel);
	void SetScoreThisGame(int score);
};
