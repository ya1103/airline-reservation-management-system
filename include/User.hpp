#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <memory>
#include <vector>

//Forward declaration
class AirlineOperations;

//User is an abstract class which will be used as an interface in our program
class User{
    protected:   
        std::string id;
        std::string name;
        std::string role;
        std::string email;
        std::string password;
        bool loggedIn = false; 

        //reference to FlightManager which manages all flights
        //static as it belongs to the class and same for all derived objects
        //initialized to nullptr
        inline static std::shared_ptr<AirlineOperations> airlineOperationsReference = nullptr;
    public:

        //Parameterized constructor
        User(const std::string& passedName, const std::string& passedRole, const std::string& passedEmail, const std::string& password)
            :  id("N/A"), name(passedName) , role(passedRole), email(passedEmail), password(password){}
        
        static void setFlightsReference(std::shared_ptr<AirlineOperations>);

        virtual void showMenu() = 0; //Pure virtual function, as user is an abstract class this will support polymorphism
        
        void logOut() {loggedIn = false;}
        void logIn() {loggedIn = true;}
    
        
};

#endif
