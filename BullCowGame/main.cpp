/* This is the console executable, that makes use of the BullCow class 
This acts as the view in a MVC pattern, and is responsible for all
user interactions. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal Engine friendly
using FText = std::string;
using int32 = int;


// function prototpyes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

int main() 
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);

	return 0; // exit the application
}
// introduce the game
void PrintIntro()
{
	// using the string literal to avoid having to use the escape character
	// this is done with placing R in front of the string
	std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << R"(          .=     ,        =.                                                       )" << std::endl;
	std::cout << R"(  _  _   /'/    )\,/,/(_   \ \                                                     )" << std::endl;
	std::cout << R"(   `//-.|  (  ,\\)\//\)\/_  ) |                                                    )" << std::endl;
	std::cout << R"(   //___\   `\\\/\\/\/\\///'  /                     /  '///\\/\/\\/\\\`   \___//   )" << std::endl;
	std::cout << R"(,-"~`-._ `"- - '_   `"""`  _ \`'"~-,_           _ˎ-~"'`\ _  `"""`   _'--"` _.-`~"-ˎ)" << std::endl;
	std::cout << R"(\       `-.  '_`.      .'_` \ ,-"~`/           /`~"-ˎ \ `_'.      .`_'  .-`       \)" << std::endl;
	std::cout << R"( `.__.-'`/   (-\        /-) |-.__,'             'ˎ__.-| (-/        \-)   /`'-.__.` )" << std::endl;
	std::cout << R"(   ||   |     \O)  /^\ (O/  |          BULLS          |  /O) \^/  (O\     |   ||   )" << std::endl;
	std::cout << R"(   `\\  |         /   `\    /            &            /    \`   /         |  \\`   )" << std::endl;
	std::cout << R"(     \\  \       /      `\ /             COWS          / \`      /       \  \\     )" << std::endl;
	std::cout << R"(      `\\ `-.  /' .---.--.\                             \.--.---. '/  .-` \\`      )" << std::endl;
	std::cout << R"(        `\\/`~(, '()      ('                           ')      ()' ˎ)~`/\\`        )" << std::endl;
	std::cout << R"(         /(O) \\   _,.-.,_)                             (_ˎ.-.ˎ_   \\ (O)/         )" << std::endl;
	std::cout << R"(        //  \\ `\'`      /                               /      `'\` \\  //        )" << std::endl;
	std::cout << R"(       / |  ||   `""""~"`                                 `"~""""`   ||  | /       )" << std::endl;
	std::cout << R"(     /'  |__||                                                       ||__|  '/     )" << std::endl;
	std::cout << R"(           `o                                                          o`          )" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
	}

	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{

		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

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
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well Done - You Win!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}
