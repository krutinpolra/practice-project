/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : KRUTIN BHARATBHAI POLRA
Student ID#: 135416220
Email      : kbpolra@myseneca.ca
Section    : NFF

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

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

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//
// recieves user input of an int
int inputInt(void)
{
	int input = 0, flag = 0;

	char newLine = 'x';

	do {

		scanf("%d%c", &input, &newLine);


		if (newLine != '\n') {
			clearInputBuffer();
			printf("Error! Input a whole number: ");
		}
		else {
			flag = 1;
		}

	} while (!flag);

	return input;
}

// Perform the same operations as inputInt but validates the value entered is greater than 0
int inputIntPositive(void)
{
	int input = 0, flag = 0;

	do {

		input = inputInt();

		if (input <= 0) {

			printf("ERROR! Value must be > 0: ");
		}
		else {
			flag = 1;
		}

	} while (!flag);

	return input;
}

// validates that the value entered is within the two provided arguments
int inputIntRange(const int lowerLimit, const int upperLimit)
{
	int input = 0, flag = 0;
	do {

		input = inputInt();

		if (input < lowerLimit || input > upperLimit) {

			printf("ERROR! Value must be between %d and %d inclusive: ", lowerLimit, upperLimit);
		}
		else {
			flag = 1;
		}

	} while (!flag);

	return input;
}

// recieves user input of a char
char inputCharOption(const char validChars[])
{
	int i, flag;

	char userChar, newLine = 'x';

	do {

		flag = 0;

		scanf(" %c%c", &userChar, &newLine);

		if (newLine != '\n') {
			clearInputBuffer();
		}

		for (i = 0; validChars[i] != '\0'; i++) {

			if (userChar == validChars[i] && newLine == '\n') {
				flag = 1;
			}
		}

		if (!flag) {
			printf("ERROR: Character must be one of [%s]: ", validChars);

		}

	} while (!flag);

	return userChar;
}

// obtains user input for a C string value with a length
void inputCString(char str[], int minChar, int maxChar)
{
	char string[1000 + 1] = { 0 };

	int len = 0, flag = 0;


	do {

		len = 0;

		scanf("%1000[^\n]", string);

		clearInputBuffer();

		len = strlen(string);

		//validate input is len long

		if (minChar == maxChar && len != minChar) {
			printf("ERROR: String length must be exactly %d chars: ",
				minChar);
		}

		else if (len > maxChar) {
			printf("ERROR: String length must be no more than %d chars: ",
				maxChar);
		}
		else if (len < minChar) {
			printf("ERROR: String length must be between %d and %d chars: ",
				minChar, maxChar);
		}
		else {
			flag = 1;
		}

	} while (!flag);

	strcpy(str, string);


}
// obtains user input for a C string phone number
void inputNumberString(char str[], int numLen)
{
	char string[1000 + 1] = { 0 };

	int len = 0, flag = 0, onlyDigit = 1, i;


	do {


		if (len) {
			printf("Number: ");
		}
		scanf("%1000[^\n]", string);

		clearInputBuffer();

		len = strlen(string);

		for (i = 0; str[i] != '\0'; i++) {

			if (str[i] < '0' || str[i] > '9') {

				onlyDigit = 0;

			}
		}

		if (onlyDigit && len != numLen) {
			printf("Invalid 10-digit number! ");
		}
		else if (!onlyDigit) {
			printf("Invalid entry! ");
		}
		else {
			flag = 1;
		}
	} while (!flag);

	strcpy(str, string);

	putchar('\n');
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// displays an array of 10 character digits as a formatted phone number

void displayFormattedPhone(const char* str)
{
	int len = 0, onlyDigit = 1, i;
	if (str != NULL) {

		len = strlen(str);

		for (i = 0; str[i] != '\0'; i++) {

			if (str[i] < '0' || str[i] > '9') {

				onlyDigit = 0;

			}
		}

		if (len != 10 || onlyDigit == 0) {
			printf("(___)___-____");
		}
		else {
			printf("(%.3s)%.3s-%.4s", &str[0], &str[3], &str[6]);
		}
	}
	else {
		printf("(___)___-____");
	}

}


