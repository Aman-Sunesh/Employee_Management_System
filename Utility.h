#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <limits>
#include <string>
#include <type_traits>

// Declare the template function in the header file
template <typename T>
bool isInvalidInput(T& input);

// If necessary, declare specializations in the header
template <>
bool isInvalidInput<std::string>(std::string& input);

#include "Utility.tpp" // Include the implementation at the end of the header

#endif // UTILITY_H