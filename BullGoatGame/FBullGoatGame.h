/*
The game logic (no view code or direct user interaction).
The game is a simple word guess based on Mastermind.
*/
#pragma once
#include <string>

using FString = std::string; //to conform with Unreal coding standards
using int32 = int; //to conform with Unreal coding standards


struct FBullGoatCount
{
	int32 Bulls = 0;
	int32 Goats = 0;
};

//possible status list for the user guesses
enum class EGuessStatus 
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_LowerCase
};


class FBullGoatGame
{
public:
	FBullGoatGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString GetHiddenWord() const; //for debugging purposes only

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullGoatCount SubmitValidGuess(FString);


private:
	//see constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bMyGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};