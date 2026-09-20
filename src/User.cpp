#include "User.hpp"
#include <iostream>

//Virtual function, to print info of derived objects, might be overriden by derived classes
void User::printUserInfo() const{
    std::cout << "ID: " << id << "\n"
            << "Name: " << name << "\n"
            << "Role: " << role << "\n";
} 