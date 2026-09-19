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
        
        void createUser(const std::string& name, const std::string& role, const std::string& email, const std::string& password);
    };

#endif
