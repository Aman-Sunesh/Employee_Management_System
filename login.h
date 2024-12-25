#ifndef LOGIN_H
#define LOGIN_H

#include <vector>
#include "User.h" // Assuming User is a class you've defined

// Function declarations
char getch();
void clearScreen();
User* login(std::vector<User*>& userList);

#endif // LOGIN_H