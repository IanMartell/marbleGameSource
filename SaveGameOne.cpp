// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameOne.h"

USaveGameOne::USaveGameOne()
{

}

//Getters

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

double USaveGameOne::GetMaster()
{
	return masterVolume;
}
double USaveGameOne::GetMusic()
{
	return musicVolume;
}
double USaveGameOne::GetAtmosphere()
{
	return atmosphereVolume;
}
double USaveGameOne::GetSFX()
{
	return sfxVolume;
}

//Setters

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

void USaveGameOne::SetMaster(double newVol)
{
	masterVolume = newVol;
}
void USaveGameOne::SetMusic(double newVol)
{
	musicVolume = newVol;
}
void USaveGameOne::SetAtmosphere(double newVol)
{
	atmosphereVolume = newVol;
}
void USaveGameOne::SetSFX(double newVol)
{
	sfxVolume = newVol;
}

