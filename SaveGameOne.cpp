// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameOne.h"

USaveGameOne::USaveGameOne()
{

}

TArray<int> USaveGameOne::GetHighscores()
{
	return highscores;
}

int USaveGameOne::GetHighscoreDataOne()
{
	return highscoreDataOne;
}

int USaveGameOne::GetHighscoreDataTwo()
{
	return highscoreDataTwo;
}

int USaveGameOne::GetMaxLevel()
{
	return maxLevel;
}

int USaveGameOne::GetScoreThisGame()
{
	return scoreThisGame;
}

void USaveGameOne::SetHighscores(TArray<int> newHighscores)
{
	highscores = newHighscores;
}

void USaveGameOne::SetHighscoreDataOne(int newHighscoreData)
{
	highscoreDataOne = newHighscoreData;
}

void USaveGameOne::SetHighscoreDataTwo(int newHighscoreData)
{
	highscoreDataTwo = newHighscoreData;
}

void USaveGameOne::SetMaxLevel(int newMaxLevel)
{
	maxLevel = newMaxLevel;
}

void USaveGameOne::SetScoreThisGame(int score)
{
	scoreThisGame = score;
}
