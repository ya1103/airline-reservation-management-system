#ifndef USERMANAGER_HPP
#define USERMANAGER_HPP

#include "User.hpp"


//This will class will manage all type of users during runtime
class UserManager: public std::enable_shared_from_this<UserManager>{
    private:
        std::vector<std::shared_ptr<User>> users; //list of shared pointers to users during runtime
    public:
        //logIn() function iterates through the list of users and search for a matching criteria
        //If found it returns a pointer to user, if not returns a nullptr
        std::shared_ptr<User> logIn(const std::string& emailInputByUser, const std::string& passwordAttemptByUser);
        
        //Creating new user only if email is unique, unless it returns false with message displaying failed process
        //User's role must be either: Passenger, BookingAgent or Administrator, unless it returns false with message displaying failed process
        bool createUser(const std::string& passedName, const std::string& passedRole,
                              const std::string& passedEmail, const std::string& password);

        //Deactivates User which will not allow him to relogin again instead of user deletion
        //If user id and role didn't match an existing one, then return false with message displaying failed process
        //Also if user is already deactivated, then return false with message displaying failed process
        bool deactivateUser(int id, const std::string& role);

        //Update user name only if id and role matches existing user, unless returns false with message displaying failed process
        bool updateUserName(int id, const std::string& role, std::string newName);
    };

#endif
