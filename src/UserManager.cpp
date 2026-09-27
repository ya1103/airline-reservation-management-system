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
        newUser = std::make_shared<BookingAgent>(passedName, passedEmail, password, shared_from_this());
    } else if (passedRole == "Passenger") {
        newUser = std::make_shared<Passenger>(passedName, passedEmail, password);
    } else {
        std::cout << "Invalid role, must be Administrator, BookingAgent, or Passenger. Please try again!\n";
        return false;
    }

    //Assign user safely
    users.push_back(newUser);
    std::cout << "\nUser created successfully!\n";
    return true;
}

bool UserManager::deactivateUser(int id, const std::string& role)
{
    auto it = std::find_if(users.begin(), users.end(),
        [&](const auto& u) { return (u->getID() == id) && (u->getRole() == role); });

    if (it == users.end()) {
        std::cout << "No user found with the entered ID and role, please try again!\n";
        return false;
    }

    if (!((*it)->getIsActive())) {
        std::cout << "This user is already deactivated.\n";
        return false;
    }

    //Deactivate safely
    (*it)->deactivate();
    std::cout << "User deactivated successfully!\n";
    return true;
    
}

bool UserManager::updateUserName(int id, const std::string& role, std::string newName){
    
    //Find target user
    auto it = std::find_if(users.begin(), users.end(),
            [&](const auto& u) { return (u->getID() == id) && (u->getRole() == role); });

    //Check if user found not an invalid iterator
    if (it == users.end()) {
        std::cout << "No user found with the entered ID and role, please try again!\n";
        return false;
    }

    //Check if user is active or not
    if(!(*it)->getIsActive())
    {
        std::cout << "User is inactive! Please activate user first!\n";
        return false;
    }

    //Assign name safely
    (*it)->setName(std::move(newName));
    std::cout << "Name updated successfully!\n";
    (*it)->printUserInfo();
    return true;

}

std::shared_ptr<Passenger> UserManager::findPassengerByID(int id)
{
    for (const auto& user : users) {
    if (user->getID() == id && user->getRole() == "Passenger" && user->getIsActive()) {
            return std::dynamic_pointer_cast<Passenger>(user);
        }
    }
    return nullptr;
}

std::shared_ptr<User> UserManager::logIn(const std::string& emailInputByUser, const std::string& passwordAttemptByUser)
{
    auto userIterator = std::find_if(users.begin(), users.end(), 
                        [&](const auto& u){return u->getEmail() == emailInputByUser 
                            && u->checkPassword(passwordAttemptByUser)
                            && u->getIsActive();
                        });
    
    //Check if a user found with given criteria
    if(userIterator == users.end())
    {
        std::cout << "No user found with given email or password! Please try again.\n";
        return nullptr;
    }

    //If safe check passed, then return the shared pointer of user and flip internal status to be logged in
    (*userIterator)->logIn();
    return *userIterator;
}