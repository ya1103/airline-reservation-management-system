#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <memory>
#include <vector>

//User is an abstract class which will be used as an interface in our program
class User{
    protected:   
        int id;
        std::string name;
        std::string role;
        std::string email;
        std::string passwordHash; //encrypted password for better security
        bool loggedIn = false; 
    public:
        virtual void showMenu() = 0; //Pure virtual function, as user is an abstract class this will support polymorphism
        void logOut();
    
        
};

#endif
