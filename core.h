/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  :Yi-Hsuan Weng
Student ID#:106800204
Email      :yhweng1@myseneca.ca
Section    :NAA

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #2 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// input the integer number and display the error message with non-integer number
int inputInt(void);
// use inputInt function to check the positive integer number and display the error message with non-positive-integer number  (returns inputInt function) 
int inputIntPositive(void);
// use inputInt function to check the length of a C-String character array within the range and display the error message (returns inputInt function) 
int inputIntRange(int min, int max);
// intput a aplphabet: only allow certain aplphabet in a c-string character array and display the error message(returns character array)
char inputCharOption(const char* charOption);
// input the cString: check the length of cSting within the range and display error message
void inputCString(char* cString, int minLength, int maxLength);
// display the matched the 10 numbers and unmatched format 
void displayFormattedPhone(const char* phoneNum);
// input the phone number cString: check the length of cSting within the range and display error message
void inputPhoneNumString(char* cString, int length);


// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
