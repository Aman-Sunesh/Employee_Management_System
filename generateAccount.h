#ifndef GENERATEACCOUNT_H
#define GENERATEACCOUNT_H

#include <string>
#include <vector>

using namespace std;

class generateAccount
{
private:
    static vector<std::string> IDList;
    static vector<std::string> passwordList;

public:
    generateAccount();

    // Function to generate a unique NetID
    static string generateNetID();

    // Function to generate a random password
    static string generatePassword();
};

#endif // GENERATEACCOUNT_H