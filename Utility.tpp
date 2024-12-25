#include "Utility.h"

#include <iostream>
#include <limits>
#include <string>
#include <type_traits>


using namespace std;

// General template for non-string types
template <typename T>
inline bool isInvalidInput(T& input) {
    cin >> input;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error! Invalid Input! Please enter a valid input of the expected type." << endl;
        cout << endl;

        return true; // Invalid input
    }
    return false; // Valid input
}

// Specialization for std::string
template <>
inline bool isInvalidInput<string>(string& input) {
    getline(cin, input);
    return false; // Valid input
}