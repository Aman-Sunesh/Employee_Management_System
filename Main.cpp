#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <limits>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include <time.h>

using namespace std;

#include "User.h"
#include "UserManager.h"
#include "Utility.h"

inline void clearScreen() 
{
    // ANSI escape code to clear screen
    cout << "\x1B[2J\x1B[H";
}

int main()
{
	srand(static_cast<unsigned int>(time(nullptr))); // Initialize random seed

	// Get the current time
    auto currentTime = chrono::system_clock::to_time_t(chrono::system_clock::now());

    // Convert the time to a string in the desired format
    tm* localTime = localtime(&currentTime);

    // Manually adjust the hours to fix the issue
    localTime->tm_hour += 4;  // Adjust for a 4-hour time difference (modify according to your local timezone)

    // Ensure that the adjusted hours are within the valid range (0-23)
    if (localTime->tm_hour >= 24) 
	{
        localTime->tm_hour -= 24;
    }

    // Convert the adjusted time back to a string
    char timeString[100];
    strftime(timeString, sizeof(timeString), "%a %b %e, %Y %T", localTime);

	// Create a new instance of UserManager
	UserManager* u;
	u = new UserManager();

	// Register a default user with the UserManager
	u->registerUser("Default","NYU","@pass","Administrator"); 

	do
	{
		cout << endl;
		cout << "--------------------------------------------------------------" << endl;
		cout << "|                COURSE MANAGEMENT SYSTEM                    |" << endl;
		cout << "|                " << timeString << "                   | " << endl;
		cout << "|------------------------------------------------------------|" << endl;
		cout << "|                                                            |" <<endl;
		cout << "| 1. Login                                                   |" << endl;
		cout << "| 2. Logout                                                  |" << endl;
		cout << "|------------------------------------------------------------|" << endl;

		int choice;

		do{
			cout << "Enter your choice(1-2): ";

			if (isInvalidInput(choice)) // If the input is invalid, isInvalidInput will handle the error message
			{
				continue; // Skip the rest of the loop and prompt the user again
			}

			if (choice < 1 || choice > 2) // Check if the choice is outside the valid range
			{
				cout << "Error! Invalid Choice. Please enter a number between 1 and 2." << endl;
			}
		
		}while(choice < 1 || choice > 2);

		cin.clear(); // Clear error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the rest of the line

		cout << endl;
		clearScreen();

		switch (choice)
		{
			case 1:
			{
				u->loginUser(u); // Login User
				break;
			}

			case 2:
			{
				cout <<"Logged out successfully!!!" << endl;
				exit(-1); // Exit the program
				break;
			}

			default:
				cout << "Invalid Input!" << endl;
				break;

		}

	} while(true);

	delete u; // Delete the UserManager Instance

	return 0;
}