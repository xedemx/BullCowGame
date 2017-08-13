#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "drebin";
	
	MyMaxTries = MAX_TRIES;	
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;

	return;
}

bool FBullCowGame::IsGameWon() const
{
	return false;
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
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	//increment the turn number
	MyCurrentTry++;
	//setup a return variable
	FBullCowCount BullCowCount;

	//loop through all letters in the guess
	int32 HiddenWorldLength = MyHiddenWord.length();

	//compare letters against the hidden word
	for (int32 MHWChar = 0; MHWChar < HiddenWorldLength; MHWChar++)
	{
		for (int32 GChar = 0; GChar < HiddenWorldLength; GChar++)
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

	return BullCowCount;
}
