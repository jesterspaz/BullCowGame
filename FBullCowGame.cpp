#include "stdafx.h"
#include "FBullCowGame.h"

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "plant";
	
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;
	MyCurrentTry = 1;
}

int32 FBullCowGame::GetGuesses() const { return 0; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; };



//recieves a valid guess, increments turn, and returns count.
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;

	// setup return variable
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();// assume same length as guess

	// loop through all letters in hidden word concurrently
	
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++){
		// loop through all letters in guess
		for (int32 GChar = 0; GChar < WordLength; GChar++){
			//if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]){
				//if they are in the same place
				if (MHWChar == GChar) { 
					BullCowCount.Bulls++;
				}
				else { 
					BullCowCount.Cows++; 
				}
			}
		}
	}
		
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter strings as isograms
	if (Word.length() <= 1) { return true; }

	//setup map
	TMap<char, bool> LetterSeen;

	for (auto Letter : Word)//for all letters of the word
	{
		Letter = tolower(Letter);//handle mixed case.

		if (LetterSeen[Letter]) {//the letter is in the map
			return false;
		} 
		else {
			// add letter to the map
			LetterSeen[Letter] = true;
		}

		return true; // for example; in cases where /0 is entered.
	}
}
bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)//for all letters of the word
	{
		if ( !islower( Letter ) ) { //a letter is lowercase
			return false;
		}
		else {
			// letter is upper case
			return true;
		}
	}
}
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram( Guess )) //if the guess isnt an isogram 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if ( !IsLowercase( Guess )) // if the guess isnt all lower case 
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if ( Guess.length() != GetHiddenWordLength() ) // if guess length is wrong 
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}

}
