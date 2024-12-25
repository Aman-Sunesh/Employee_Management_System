#include "generateAccount.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

// Initializing member variables
vector<string> generateAccount::IDList = {};
vector<string> generateAccount::passwordList = {};

// Function to generate a unique netID
string generateAccount::generateNetID() {
    string letters = "abcdefghijklmnopqrstuvwxyz";
    string digits = "0123456789";
    string netID;

    do {
        netID = "";
        // Generate netID by concatenating random characters
        netID += letters[rand() % 26];
        netID += letters[rand() % 26];
        netID += digits[rand() % 10];
        netID += digits[rand() % 10];
        netID += digits[rand() % 10];
    } while (find(IDList.begin(), IDList.end(), netID) != IDList.end()); // Check if netID is already in use

    IDList.push_back(netID); // Add netID to the IDList vector
    return netID; // Return generated netID
}

// Function to generate a unique password
string generateAccount::generatePassword() {
    string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*";
    string password;
    const int passwordLength = 8;

    do {
        password = "";

        // Generate password by randomly selecting characters from chars string
        for (int i = 0; i < passwordLength; i++) {
            password += chars[rand() % chars.length()];
        }
    } while (find(passwordList.begin(), passwordList.end(), password) != passwordList.end()); // Check if password is already in use

    passwordList.push_back(password); // Add password to the passwordList vector
    return password; // Return generated password
}