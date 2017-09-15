#pragma once

//never use namespace in headers
#include <string>
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

// init Bulls, and Cows to zero.
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame 
{
public:
	
	FBullCowGame(); //constructor

	void Reset(); //TODO make a more rich return value.

	int32 GetGuesses() const;
	int32 GetCurrentTry() const;
	int32 GetMaxTries() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const;
	
	// count bulls and cows and increases try number, assuming valid guess
	FBullCowCount SubmitValidGuess(FString Guess);



private:
	//see constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram( FString ) const;
	bool IsLowercase( FString ) const;
};