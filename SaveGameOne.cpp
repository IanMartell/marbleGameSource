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

FKey USaveGameOne::GetPauseKey()
{
	return pauseKey;
}
FKey USaveGameOne::GetPauseMouse()
{
	return pauseMouse;
}
FKey USaveGameOne::GetSelectKey()
{
	return selectKey;
}
FKey USaveGameOne::GetMoveKey()
{
	return moveKey;
}
FKey USaveGameOne::GetPauseController()
{
	return pauseController;
}
FKey USaveGameOne::GetSelectController()
{
	return selectController;
}
FKey USaveGameOne::GetMoveController()
{
	return moveController;
}

TArray<int> USaveGameOne::GetSongIndexArr()
{
	return songIndexArr;
}
TArray<int> USaveGameOne::GetSongCycles()
{
	return songCycles;
}

float USaveGameOne::GetGamma()
{
	return gamma;
}

bool USaveGameOne::GetHardModeOn()
{
	return hardModeOn;
}

bool USaveGameOne::GetAutoCursorOn()
{
	return autoCursorOn;
}

/*bool USaveGameOne::GetTestBool()
{
	return testBool;
}
int USaveGameOne::GetTestInt()
{
	return testInt;
}
FString USaveGameOne::GetTestString()
{
	return testString;
}*/

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

void USaveGameOne::SetPauseKey(FKey newKey)
{
	pauseKey = newKey;
}
void USaveGameOne::SetPauseMouse(FKey newKey)
{
	pauseMouse = newKey;
}
void USaveGameOne::SetSelectKey(FKey newKey)
{
	selectKey = newKey;
}
void USaveGameOne::SetMoveKey(FKey newKey)
{
	moveKey = newKey;
}
void USaveGameOne::SetPauseController(FKey newKey)
{
	pauseController = newKey;
}
void USaveGameOne::SetSelectController(FKey newKey)
{
	selectController = newKey;
}
void USaveGameOne::SetMoveController(FKey newKey)
{
	moveController = newKey;
}

void USaveGameOne::SetSongIndexArr(TArray<int> newArr)
{
	songIndexArr = newArr;
}
void USaveGameOne::SetSongCycles(TArray<int> newArr)
{
	songCycles = newArr;
}

void USaveGameOne::SetGamma(float newGamma)
{
	gamma = newGamma;
}

void USaveGameOne::SetHardModeOn(bool newBool)
{
	hardModeOn = newBool;
}

void USaveGameOne::SetAutoCursorOn(bool newBool)
{
	autoCursorOn = newBool;
}
