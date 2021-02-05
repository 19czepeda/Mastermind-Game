//
//  main.cpp
//  Mastermind Game
//
//  Created by Marco Pretell on 4/11/20.
//  Copyright © 2020 Marco Pretell. All rights reserved.
//

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <stdlib.h>
#include <time.h>

//------------------------------------ Declarations ----------------------------------------------


void instructions();

void setAnswerKey();

std::vector<std::string> guessPrompt();

std::vector<int> primeConversion(std::vector<std::string> stringGuessVector);

void winStatement();

void winExit();

void score(int perfect, int almost);

void clearData();

void fullRound();

void dispAns();


//---------------------------------- Global Variables --------------------------------------------


std::vector<int> answerKey; // setAnswerKey()
double multiple;

int roundNum; // which round player is on

std::vector<std::string> stringGuessVector(4, " "); // guessPrompt(), param for primeConversion

std::vector<int> intGuessVector(4, 0); // primeConversion


int perfect = 0;
int almost = 0;

bool repeatRound = false;


//---------------------------------------- Main -------------------------------------------------


int main() {
    
    // Introduction Prompt
    std::cout << "Welcome to Mastermind!\n";
    instructions();
    // Create answer key
    setAnswerKey();
    roundNum = 1;
    
    while(1 == 1) {
        fullRound();
    }

}

//------------------------------------- Definitions ---------------------------------------------

// Displays instruction set
void instructions() {
    std::cout << "Try to guess the hidden color combination.  The combination is made of 4 colors selected from 6 possible colors (red, orange, yellow, green, blue, purple).  Colors can be repeated.  After each guess, the number of correct colors in the correct places and correct colors in the wrong places will be displayed.  This information is then used to improve the next guess.  You then keep guessing until all 4 colors are correct.  The less guesses, the better!\nExample:\nIf the answer key is: [red yellow green blue], the guess of [red yellow green purple] would result in 3 perfects and the guess of [blue green yellow red] would result 4 right color wrong places.  In the situation where a player guesses [red red green blue] they would recieve 1 perfect but 0 right color wrong places as there is only one red in the solution and it was perfectly guessed.\nNote: Should you accidentaly enter the wrong number, type any gibberish into the prompt and after all four positions are guessed the round will restart.\n";
}


// Sets random answer key
void setAnswerKey() {
    // sets seed for random variables
    srand((unsigned) time(0));
    
    // fill answer key vector with random integers
    for (int i = 0; i < 4; ++i) {
        int r = rand() % 6;
        switch (r) {
            case 0: answerKey.push_back(2); break;
            case 1: answerKey.push_back(3); break;
            case 2: answerKey.push_back(5); break;
            case 3: answerKey.push_back(7); break;
            case 4: answerKey.push_back(11); break;
            default: answerKey.push_back(13); break;
        }
        // std::cout << answerKey[i] << ' '; // delete at end!!! ---------------------------------------------------------------
    }
    // std::cout << "\n"; // delete at end!!! ---------------------------------------------------------------
    
    /* answerKey.push_back(2);
    answerKey.push_back(3);
    answerKey.push_back(3);
    answerKey.push_back(2); */
}


// Prompts user for guess and stores it as a string type vector
std::vector<std::string> guessPrompt() {
    for (int i = 0; i < 4; ++i) {
        std::string stringGuess;
        std::cout << "Position " << i + 1 << ": ";
        std::cin >> stringGuess;
        stringGuessVector.push_back(stringGuess);
    }
    return stringGuessVector;
}


// Converts guessed strings into corresponding primes
std::vector<int> primeConversion(std::vector<std::string> stringGuessVector) {
    for (int i = 0; i < 4; ++i) {
        int intGuess;
        if (stringGuessVector[i] == "red") {intGuess = 2;}
        else if (stringGuessVector[i] == "orange") {intGuess = 3;}
        else if (stringGuessVector[i] == "yellow") {intGuess = 5;}
        else if (stringGuessVector[i] == "green") {intGuess = 7;}
        else if (stringGuessVector[i] == "blue") {intGuess = 11;}
        else if (stringGuessVector[i] == "purple") {intGuess = 13;}
        else if (stringGuessVector[i] == "Ans") {dispAns();}
        else {
            std::cout << "\nGuess for positon " << i + 1 << " not recognized.  Enter only the 6 colors of the rainbow in all lowercase.";
            repeatRound = true;
        }
        intGuessVector.push_back(intGuess);
    }
    return intGuessVector;
}


// Exits the program
void winExit() {
    std::atexit(winStatement);
    exit(0);
}


// Displays win statement upon exit
void winStatement() {
    if (roundNum == 1) {
        std::cout << "\n\nYou won in " << roundNum << " round!\n\n\n";
        }
    else {
        std::cout << "\n\nYou won in " << roundNum << " rounds!\n\n\n";
    }
}


// Checks for number of right color right position (if 4 executes win winExit() )
int checkPerfect(std::vector<int> answerKey, std::vector<int> intGuessVector) {
    for (int i = 0; i < 4; ++i) {
        if (answerKey[i] == intGuessVector[i]) {
            perfect ++;
            multiple = multiple / intGuessVector[i];
        }
    }
    if (perfect == 4) {
        winExit();
    }
    return perfect;
}


// Checks number of right color wrong places excluding perfects (uses prime factorization)
int checkAlmost(std::vector<int> answerKey, std::vector<int> intGuessVector) {
    for (int i = 0; i < 4; ++i) {
        // std::cout << "\n" << multiple << " " << intGuessVector[i] << " " << multiple / intGuessVector[i] << " " <<(round(multiple / intGuessVector[i])) << " " << almost; // ---------------------------------------------------------------
        if ((round(multiple / intGuessVector[i]) == (multiple / intGuessVector[i])) && (answerKey[i] != intGuessVector[i])) {
            almost ++;
            multiple = multiple / intGuessVector[i];
        }
        // std::cout << "\n" << multiple << " " << intGuessVector[i] << " " << multiple / intGuessVector[i] << " " <<(round(multiple / intGuessVector[i])) << " " << almost; // ---------------------------------------------------------------
    }
    return almost;
}


// Reports the score for round
void score(int perfect, int almost) {
    std::cout << "...\n";
    std::cout << "Right color right place: " << perfect << "\n";
    std::cout << "Right color wrong place: " << almost << "\n";
}


// Clear data between rounds
void clearData() {
    perfect = 0;
    almost = 0;
    multiple = answerKey[0] * answerKey[1] * answerKey[2] * answerKey[3];
    repeatRound = false;
    for (int i = 0; i < 4; ++i) {
        stringGuessVector.pop_back();
        intGuessVector.pop_back();
    }
}


// Combines upper functions into repeating loop for each round
void fullRound() {
    // Clear data between rounds
    clearData();
    
    // Prompt guess
    std::cout << "\n----- Guesses for round " << roundNum << ": -----\n";
    guessPrompt();
    // for (int i = 0; i < 4; ++i) {std::cout << stringGuessVector[i] << ' ';} //------------------------------------------------------------
    
    // Convert guess to primes
    primeConversion(stringGuessVector);
    // for (int i = 0; i < 4; ++i) {std::cout << intGuessVector[i] << ' ';} //------------------------------------------------------------
    
    if (repeatRound == true) {std::cout << "\n\nPlease try again\n";}
    else {
        // Check for perfect
        checkPerfect(answerKey,intGuessVector);
        
        // Check for almost
        checkAlmost(answerKey,intGuessVector);
        
        // reports success
        score(perfect, almost);
        
        roundNum ++;
    }
}

void dispAns() {
    std::cout << "\nanswerKey: ";
    for (int i = 0; i < 4; ++i) {
        std::cout << answerKey[i] << ' '; // delete at end!!! ---------------------------------------------------------------
    }
    std::cout << "\n"; // delete at end!!! ---------------------------------------------------------------
}

// for (int i = 0; i < 4; ++i) {std::cout << stringGuessVector[i] << ' ';}
