/*This is the console executable that uses the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.

*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; //instantiate a new game


//the entry point for our application
int main()
{
	//std::cout << BCGame.GetCurrentTry();
	bool bPlayAgain = false;
	do 
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0; //exit the app
}


// introduce the game
void PrintIntro()
{
	constexpr int32 WORD_LENGTH = 9;
	std::cout << "Welcome to Bulls and Cows, a fun word game with intense action!";
	std::cout << std::endl;
	std::cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of?" << std::endl;
	std::cout << std::endl;
	
	return;
}


void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << MaxTries;
	std::cout << std::endl;

	//loop for the number of turns asking for guesses
	//TODO change from FOR to WHILE loop once we are validating tries
	for (int32 i = 1; i <= MaxTries; i++)
	{
		FText Guess = GetGuess(); //TODO validate guesses in loop

		//submit valid guess to the game
		//print number of bulls and cows

		std::cout << "Your guess is: " << Guess;
		std::cout << std::endl;
		std::cout << std::endl;

	}
	//TODO summarize game

	return;
}


//get a guess from the player and repeat the guess back to them
FText GetGuess()
{
	FText Guess = "";
	int32 CurrentTry = BCGame.GetCurrentTry();
	std::cout << "Try " << CurrentTry << ". Please enter your guess: ";
	getline(std::cin, Guess);

	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again(y/n)?";
	FText Response = "";
	getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}
