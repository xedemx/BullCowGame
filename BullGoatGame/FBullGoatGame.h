#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//two integers initialized to zero
struct FBullGoatCount
{
	int32 Bulls = 0;
	int32 Goats = 0;
};

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

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullGoatCount SubmitValidGuess(FString);


//^^ please try and ignore his and focus on the interface above ^^
private:
	//see constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bMyGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};