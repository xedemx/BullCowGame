#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bMyGameIsWon; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "drebin";
	
	MyMaxTries = MAX_TRIES;	
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bMyGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (false) //if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (false) //if the guess isn't all lowercase
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

	//if the guess length is wrong
		//return error
	//otherwise
		//return OK

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
