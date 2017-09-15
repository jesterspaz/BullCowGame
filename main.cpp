/* This is the console exeuctable, that makes use of the BullCowClass
This acts as the view in a MVC pattern, 
and is responsible for all user interaction.
For game logic see the FBullCowGame class.
*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FString = std::string;
using int32 = int;

//prototypes
void PrintIntro();
void PlayGame();
FString GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;//instantiate a new game

int32 main()
{
	bool bPlayAgain = false;
	do 
	{
		PrintIntro();
		PlayGame();
	} while( AskToPlayAgain() != 0);

	return 0;//exit application
}

//introduce the game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	return;
}

void PlayGame()
{
	BCGame.Reset();//also handles member variable inits
	int32 MaxTries = BCGame.GetMaxTries();

	//loop asking for guesses while game is NOT won
	//and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) 
	{
		FString Guess = GetValidGuess(); 

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << std::endl;
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n";
		std::cout << std::endl;
	}

	//TODO: Summarize Game
	PrintGameSummary();

}
// loop continuously until user inputs a valid guess
FString GetValidGuess() 
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	FString Guess = "";

	do {
		std::cout << "Try " << CurrentTry << ". " << "Enter your guess: ";
		
		std::getline(std::cin, Guess); //store input into Guess
	
		// returns proper enum from guess.
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
			case EGuessStatus::Wrong_Length:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
				break;

			case EGuessStatus::Not_Isogram:
				std::cout << "Please enter a word without repeating letters.\n\n";
				break;

			case EGuessStatus::Not_Lowercase:
				std::cout << "Please enter all lower case letters.\n\n";
				break;

			default:
				// assume the guess is valid now.
				break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until we get no errors

	return Guess;
	std::cout << std::endl;
	CurrentTry++;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again?(y/n) ";
	FString Response = "";
	std::getline(std::cin, Response);

	//response[0] is the first letter in the string array
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "You Win!" << std::endl;
	}
	else if( BCGame.GetCurrentTry() > BCGame.GetMaxTries() ){
		std::cout << "You Lose!" << std::endl;
	}
}
