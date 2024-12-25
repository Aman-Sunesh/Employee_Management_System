#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <limits>
#include <cstdlib>
#include <time.h>
#include <vector>

#include "User.h"
#include "UserManager.h"
#include "Utility.h"

using namespace std;

// Function to read a single character without echoing
inline char getch() {
    char ch;
    struct termios oldt, newt;

    // Save current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable buffering and echoing
    newt.c_lflag &= ~(ICANON | ECHO);

    // Apply the new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Read a single character
    cin.get(ch);

    // Restore the old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}


inline void clearScreen() {
    // ANSI escape code to clear screen
    cout << "\x1B[2J\x1B[H";
}

// Function to perform user login
User* login(vector<User*>& userList)
{
    string netID = "";
    string pass = "";
    int index;
    bool flag = false;
    char ch;

    cout << "--------------------------------------------------------------" << endl;
    cout << "|                COURSE MANAGEMENT SYSTEM                    |" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << endl;


    // Prompt user to enter netID until valid input is received
    do {
        cout << "Enter netID:";
    } while (isInvalidInput(netID));

    cout << "Enter Password:";
    ch = getch();

    // Masking the password input
    while (ch != '\n')
    {
        pass.push_back(ch);
        cout << '*';
        ch = getch();
    }

    cout << pass;

    // Clear screen using clearScreen() function
    clearScreen();

    // Search for the user in the userList
    for (int i = 0; i < userList.size(); i++)
    {
        if (userList[i]->getNetID() == netID && userList[i]->getPassword() == pass)
        {
            // Display loading message
            cout << "\n\n\n\t\t\t\t\tLOADING \n\t\t\t\t\t";

            // Search for the user in the userList
            for (int i = 1; i < 8; i++)
            {
                this_thread::sleep_for(chrono::milliseconds(375));
                cout << "...";
                cout.flush(); // Flush the output to ensure it is displayed immediately
            }

            cout << "\n\n\n\t\t\t\t\tAccess Granted!! \n\n\n";

            flag = true;
            index = i;
            break;

        }
    }

    // Handle login result
    if (flag == true)
    {
        // Pause using cin.get()
        cout << "Press Enter to continue...";
        cin.get();

        // Clear screen using clearScreen() function
        clearScreen();

        // Return pointer to the logged-in user
        return userList[index];
    }

    else
    {
        cout << "\nAccess Aborted...\n";
        cout << endl;

        // Pause using cin.get()
        cout << "Press Enter to continue...";
        cin.get();

        // Clear screen using clearScreen() function
        clearScreen();

        // Return nullptr to indicate login failure
        return nullptr;
    }
}