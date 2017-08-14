#pragma once
#include "FBullGoatGame.h"
#include <map>
#include <time.h> //for random seed when selecting random hidden word
#define TMap std::map  //to conform with Unreal coding standards

FBullGoatGame::FBullGoatGame() { Reset(); } //default constructor

int32 FBullGoatGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullGoatGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
FString FBullGoatGame::GetHiddenWord() const { return MyHiddenWord; } //for debugging purposes only
bool FBullGoatGame::IsGameWon() const { return bMyGameIsWon; }

int32 FBullGoatGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,6},{4,10},{5,14},{6,20} }; //create map to adjust difficulty(i.e. the max tries) based on word length
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullGoatGame::Reset()
{
	constexpr int32 MAX_TRIES = 3;
	const FString HIDDEN_WORDS[] = { "games","fun","joy","play" }; // words MUST be isograms
	srand(time(NULL)); //initialize random seed
	
	MyMaxTries = MAX_TRIES;	
	MyHiddenWord = HIDDEN_WORDS[rand() % 4]; //select word "randomly"
	MyCurrentTry = 1;
	bMyGameIsWon = false;

	return;
}

EGuessStatus FBullGoatGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) //if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) //if the guess isn't all lowercase
	{
		return EGuessStatus::Not_LowerCase;
	}
	else if (Guess.length() != GetHiddenWordLength()) //if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		EGuessStatus::OK;
	}

	return EGuessStatus::OK; 
}

//receives a VALID guess increments turn and returns count
FBullGoatCount FBullGoatGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullGoatCount BullGoatCount;
	int32 WorldLength = GetHiddenWordLength(); //assuming same length as guess
	
	//loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WorldLength; MHWChar++)
	{	//compare letters against the guess
		for (int32 GChar = 0; GChar < WorldLength; GChar++)
		{
			//if the letter is the same 
			if (MyHiddenWord[MHWChar] == Guess[GChar])
			{
				if (MHWChar == GChar)
				{//and are in the same place
					BullGoatCount.Bulls++; // inc bulls
				}
				else
				{//not in the same place
					BullGoatCount.Goats++; // inc goats
				}
			}
		}
	}

	if (BullGoatCount.Bulls == WorldLength)
	{
		bMyGameIsWon = true;
	}
	else
	{
		bMyGameIsWon = false;
	}

	return BullGoatCount;
}

bool FBullGoatGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; //setup map

	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter])
		{//letter is in the map it is not an isogram
			return false;
		}
		else
		{//add the letter to the map 
			LetterSeen[Letter] = true;
		}
	}

	return true; // can get here if \0 is entered
}

bool FBullGoatGame::IsLowercase(FString Word) const
{
	if(Word.length() < 1)
	{
		return false;
	}

	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}

	return true;
}
