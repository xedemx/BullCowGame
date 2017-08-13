#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;	

	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;

	return;
}

bool FBullCowGame::IsGameWon() const
{
	return false;
}

bool FBullCowGame::CheckGuessValidity(FString)
{
	return false;
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
