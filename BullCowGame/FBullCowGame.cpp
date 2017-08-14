#include "FBullCowGame.h"
#include <map>
#define TMap std::map  //to conform with Unreal coding standards

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bMyGameIsWon; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "games";
	
	MyMaxTries = MAX_TRIES;	
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bMyGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
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
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
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
					BullCowCount.Bulls++; // inc bulls
				}
				else
				{//not in the same place
					BullCowCount.Cows++; // inc cows
				}
			}
		}
	}

	if (BullCowCount.Bulls == WorldLength)
	{
		bMyGameIsWon = true;
	}
	else
	{
		bMyGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; 		//setup map

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

bool FBullCowGame::IsLowercase(FString Word) const
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
