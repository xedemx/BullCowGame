/*This is the console executable that uses the BullGoatGame class.
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullGoatGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullGoatGame.h"

using FText = std::string; //to conform with Unreal coding standards
using int32 = int; //to conform with Unreal coding standards

//function prototypes
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullGoatGame BGGame; //instantiate a new game, which we reuse every time a new turn is started


//the entry point for our application
int main()
{
	bool bPlayAgain = false;
	do 
	{//plays a single game until completion
		BGGame.Reset();
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);	//for future: allow playing until player wants to quit


	return 0; //exit the app
}


void PrintIntro()
{
	//constexpr int32 WORD_LENGTH = 9;
	int32 WordLength = BGGame.GetHiddenWordLength();
	//std::cout << BGGame.GetHiddenWord();
	std::cout << std::endl;
	std::cout << "***************************************************************************";
	std::cout << std::endl;
	std::cout << "**  Welcome to Bulls and Goats, a fun word game with hint of suspense :) **";
	std::cout << std::endl;
	std::cout << "***************************************************************************";
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "    ,           ,                         _))                    " << std::endl;
	std::cout << "   /             \\      BULLS            > *\\     _~           " << std::endl;
	std::cout << "  ((__-^^-,-^^-__))                       `;'\\\\__-' \\_        " << std::endl;
	std::cout << "   `-_---' `---_-'                           | )  _ \\ \\        " << std::endl;
	std::cout << "    <__|o` 'o|__>            &              / / ``   w w         " << std::endl;
	std::cout << "       \\  `  /                            w w                   " << std::endl;
	std::cout << "        ): :(                    GOATS                           " << std::endl;
	std::cout << "        :o_o:                                                    " << std::endl;
	std::cout << "        ' - '                                                    " << std::endl;

	std::cout << std::endl;
	std::cout << "*************************************************************************";
	std::cout << std::endl;
	std::cout << "Can you guess the [" << WordLength << "] letter isogram I'm thinking of?" ;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "INSTRUCTIONS";
	std::cout << std::endl;
	std::cout << "- An isogram is a word without repeating letters.";
	std::cout << std::endl;
	std::cout << "- Bulls indicate a correct letter at the correct space";
	std::cout << std::endl;
	std::cout << "- Goats indicate a correct letter at the wrong space";
	std::cout << std::endl;
	std::cout << "- Guess the word before your tries run out!";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "GOOD LUCK!";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "*************************************************************************";
	std::cout << std::endl;
	
	return;
}


void PlayGame()
{

	//std::cout << BGGame.GetHiddenWord();
	int32 MaxTries = BGGame.GetMaxTries();

	//loop asking for guesses while the game is NOT won and still tries remaining
	while(!BGGame.IsGameWon() && BGGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 

		//submit valid guess to the game and receive counts
		FBullGoatCount BullGoatCount = BGGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = [" << BullGoatCount.Bulls;
		std::cout << "], Goats = [" << BullGoatCount.Goats << "]";
		std::cout << std::endl;
		std::cout << std::endl;
	}

	PrintGameSummary();

	return;
}


//loop until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	int32 MaxTries = BGGame.GetMaxTries();
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{ 
		int32 CurrentTry = BGGame.GetCurrentTry();
		//get a guess from the player
		std::cout << "Try " << CurrentTry << " of " << MaxTries << ". Enter your guess: ";
		getline(std::cin, Guess);

		//check status and give feedback
		Status = BGGame.CheckGuessValidity(Guess);
		switch (Status)
		{
			case EGuessStatus::Wrong_Length:
			{
				std::cout << "Please enter a " << BGGame.GetHiddenWordLength() << " letter word.";
				std::cout << std::endl;
				std::cout << std::endl;
				break;
			}
			case EGuessStatus::Not_Isogram:
			{
				std::cout << "Please enter a word without repeating letters.";
				std::cout << std::endl;
				std::cout << std::endl;
				break;
			}
			case EGuessStatus::Not_LowerCase:
			{
				std::cout << "Please enter only lowercase letters.";
				std::cout << std::endl;
				std::cout << std::endl;
				break;
			}
			default:
			{// the guess is valid
				break; 
			}
		}

	} while (Status != EGuessStatus::OK); // keep looping until we get no errors

	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)?";
	FText Response = "";
	getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BGGame.IsGameWon())
	{
		std::cout << "CONGRATULATIONS! YOU HAVE WON!";
		std::cout << std::endl;
		std::cout << std::endl;
	}
	else
	{
		std::cout << "BETTER LUCK NEXT TIME, BUT STAY POSITIVE :)";
		std::cout << std::endl;
		std::cout << std::endl;
	}

	return;

}
