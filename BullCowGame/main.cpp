#include <iostream>
#include <string>
#include "FBullCowGame.h"

void PrintIntro();
void PlayGame();
std::string GetGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; //instantiate a new game

//test comment

//The entry point for our application
int main()
{
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


// Introduce the game
void PrintIntro()
{
	constexpr int WORD_LENGTH = 9;
	std::cout << "Welcome to Bulls and Cows, the word game of your lifetime!";
	std::cout << std::endl;
	std::cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of?" << std::endl;
	std::cout << std::endl;
	
	return;
}


void PlayGame()
{

	int MaxTries = BCGame.GetMaxTries();
	std::cout << MaxTries;
	std::cout << std::endl;

	//Loop for the number of turns asking for guesses
	for (int i = 1; i <= MaxTries; i++)
	{
		std::string Guess = GetGuess();
		std::cout << "Your guess is: " << Guess;
		std::cout << std::endl;
		std::cout << std::endl;

	}

	return;
}


//Get a guess from the player and repeat the guess back to them
std::string GetGuess()
{
	std::string Guess = "";
	int CurrentTry = BCGame.GetCurrentTry();
	std::cout << "Try " << CurrentTry << ". Please enter your guess: ";
	getline(std::cin, Guess);

	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again(y/n)?";
	std::string Response = "";
	getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}
