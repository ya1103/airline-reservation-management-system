#ifndef ADMINISTRATOR_HPP
#define ADMINISTRATOR_HPP

#include <memory>
#include "User.hpp"

//Forward declaration
class UserManager;

class Administrator: public User{
    private:
        std::weak_ptr<UserManager> allUsersReference;
    public:
        //Parameterized constructor
        Administrator(const std::string& passedName, const std::string& passedRole, const std::string& passedEmail, const std::string& password, std::shared_ptr<UserManager> usersReference)
            :  User(passedName, passedRole, passedEmail, password), allUsersReference(usersReference){}

        //Function which creates user based on criteria
        //User's role must be either: Passenger, BookingAgent or Administrator
        //If passed argument is neither of them it should print error message and abort creation
        //If all arguments are valid, print successfull message
        void createUser(const std::string& passedName, const std::string& passedRole, const std::string& passedEmail, const std::string& password);

        //Function which deletes user by id (currently implemented by email)
        //If id not found print error message and abort process
        //If user found print successfull message 
        void deleteUser(const std::string& userEmail);

        //Function which updates user data
        //It should not affect user's id, role, email or password
        //Name and role can only be altered
        void updateUser(const std::string& newName);
};

#endif
