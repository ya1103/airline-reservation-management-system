#include "UserManager.hpp"
#include "User.hpp"
#include "Administrator.hpp"
#include "BookingAgent.hpp"
#include "Passenger.hpp"
#include "stdexcept"
#include <algorithm>
#include <iostream>

bool UserManager::createUser(const std::string& passedName, const std::string& passedRole,
                              const std::string& passedEmail, const std::string& password) {

    //Run a check on all users objects to see if there is a user with existing email already
    //Email cannot be a duplicate, if duplicate email found an exception will be thrown
    bool isEmailDuplicate = std::any_of(users.begin(), users.end(), 
                                    [&](const auto& eachUser){
                                        return eachUser->getEmail() == passedEmail;
                                    });
    if(isEmailDuplicate)
    {
        std::cout << "Email already registered, please try again!\n";
        return false;
    }

    std::shared_ptr<User> newUser;
    //Check role before creating new user
    if (passedRole == "Administrator") {
        newUser = std::make_shared<Administrator>(passedName, passedEmail, password, shared_from_this());
    } else if (passedRole == "BookingAgent") {
        newUser = std::make_shared<BookingAgent>(passedName, passedEmail, password);
    } else if (passedRole == "Passenger") {
        newUser = std::make_shared<Passenger>(passedName, passedEmail, password);
    } else {
        std::cout << "Invalid role, must be Administrator, BookingAgent, or Passenger. Please try again!\n";
        return false;
    }

    //Assign user safely
    users.push_back(newUser);
    std::cout << "User created successfully!\n";
    return true;
}