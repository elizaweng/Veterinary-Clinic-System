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

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////


// input the integer number and display the error message with non-integer number
int inputInt(void)
{
	int value = 0;
	char newline = 'x';
	do
	{
		scanf("%d%c", &value, &newline);
		if (newline != '\n')
		{
			clearInputBuffer();
			printf("Error! Input a whole number: ");
		}
	} while (newline != '\n');

	return value;
}

// use inputInt function to check the positive integer number and display the error message with non-positive-integer number  (returns inputInt function) 
int inputIntPositive(void)
{
	int value = 0;

	do
	{
		value = inputInt();
		if (value <= 0)
		{
			printf("ERROR! Value must be > 0: ");
		}
	} while (value <= 0);

	return value;
}

// use inputInt function to check the length of a C-String character array within the range and display the error message (returns inputInt function) 
int inputIntRange(int lower, int upper)
{
	int value;
	do
	{
		value = inputInt();
		if (value < lower || value > upper)
		{
			printf("ERROR! Value must be between %d and %d inclusive: ", lower, upper);
		}
	} while (value < lower || value > upper);
	return value;
}

// intput a aplphabet: only allow certain aplphabet in a c-string character array and display the error message(returns character array)
char inputCharOption(const char* charOption)
{
	int i;
	int flag = 1;
	char inputChar;
	char newline;

	while (flag == 1)
	{
		scanf("%c%c", &inputChar, &newline);

		if (newline == '\n')
		{
			for (i = 0; charOption[i] != '\0'; i++)
			{
				if (inputChar == charOption[i])
				{
					flag = 0;
				}
			}
		}
		else
		{
			printf("ERROR: Character must be one of [%s]: ", charOption);
		}
	}

	return inputChar;
}

// input the cString: check the length of cSting within the range and display error message
void inputCString(char* cString, int minLength, int maxLength)
{
	int flag = 1;
	char name[20 + 1] = { 0 };
	while (flag)
	{
		scanf("%20[^\n]", name);				//protects the array bondaries
		clearInputBuffer();
		if (minLength == maxLength)				//specific length
		{

			if (strlen(name) == minLength && strlen(name) == maxLength)
			{
				strcpy(cString, name);
				flag = 0;
			}
			else
			{
				printf("ERROR: String length must be exactly %d chars: ", maxLength);
			}
		}
		else									//minLength != maxLength
		{
			if (strlen(name) < minLength)
			{
				printf("ERROR: String length must be between %d and %d chars: ", minLength, maxLength);
			}
			else if (strlen(name) > maxLength)
			{
				printf("ERROR: String length must be no more than %d chars: ", maxLength);
			}
			else
			{
				strcpy(cString, name);
				flag = 0;
			}
		}
	}
}

// display the matched the 10 numbers and unmatched format 
void displayFormattedPhone(const char* phoneNum)
{
	int i = 0;
	int nondigit = 0;

	if (phoneNum != NULL)
	{
		while (phoneNum[i] != '\0')
		{
			if (phoneNum[i] < '0' || phoneNum[i] >'9')
			{
				nondigit++;
			}
			i++;
		}
		if (i != 10 || nondigit != 0)
		{
			printf("(___)___-____");
		}
		else
		{
			printf("(%c%c%c)%c%c%c-%c%c%c%c", phoneNum[0], phoneNum[1],
				phoneNum[2], phoneNum[3], phoneNum[4], phoneNum[5], phoneNum[6], phoneNum[7],
				phoneNum[8], phoneNum[9]);
		}
	}
	else
	{
		printf("(___)___-____");
	}
}

// input the phone number cString: check the length of cSting within the range and display error message
void inputPhoneNumString(char* cString, int length)
{
	int flag = 1;
	char phoneNum[20 + 1] = { 0 };

	do
	{
		scanf("%[^\n]", phoneNum);
		clearInputBuffer();

		if (strlen(phoneNum) == length)
		{
			strcpy(cString, phoneNum);
			flag = 0;
		}
		else
		{
			printf("Invalid 10-digit number! Number: ");
		}
	} while (flag);
}




//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

