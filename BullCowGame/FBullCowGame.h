#pragma once
#include <string>


class FBullCowGame
{
public:
	FBullCowGame(); //constructor

	int GetMaxTries() const;
	int GetCurrentTry() const;
	bool IsGameWon() const;

	void Reset(); //TODO make a more rich return value
	bool CheckGuessValidity(std::string);
	//TODO provide a method for counting bulls and cows and increasing try number



//^^ please try and ignore his and focus on the interface above ^^
private:
	//see constructor for initialization
	int MyCurrentTry;
	int MyMaxTries;

};