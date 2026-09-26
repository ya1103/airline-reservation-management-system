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
        int id;
        std::string name;
        std::string role;
        std::string email;
        std::string password;
        bool loggedIn = false; 
        bool isActive = true; //by default on new user accounts are active

        //Declare friendship
        friend class UserManager;

        //Setter to name, where UserManager only can use this setter
        void setName(std::string newName) {name = std::move(newName);};

        //reference to FlightManager which manages all flights
        //static as it belongs to the class and same for all derived objects
        //initialized to nullptr
        inline static std::shared_ptr<AirlineOperations> airlineOperationsReference = nullptr;
    public:

        //Parameterized constructor
        User(int passedID, const std::string& passedName, const std::string& passedRole, const std::string& passedEmail, const std::string& password, bool isActiveStatus = true)
            :  id(passedID), name(passedName) , role(passedRole), email(passedEmail), password(password), isActive(isActiveStatus){}

        //Email getter
        const std::string& getEmail() const{return email;}

        //ID getter
        int getID() const {return id;}

        //Role getter
        const std::string& getRole() const {return role;}

        //Active status getter
        bool getIsActive() const {return isActive;}

        //Deactivate user
        void deactivate() {isActive = false;}

        //Active user
        void activate() {isActive = true;}
        
        static void setFlightsReference(std::shared_ptr<AirlineOperations>);

        static std::shared_ptr<AirlineOperations> getAirlineOperations(void) {return airlineOperationsReference;}

        virtual ~User() = default; //Forces calling derived objects destructors implementing RTTI
        virtual void showMenu() = 0; //Pure virtual function, as user is an abstract class this will support polymorphism
        virtual void printUserInfo() const; //Virtual function, to print info of derived objects, might be overriden by derived classes



        void logOut() {loggedIn = false;}
        void logIn() {loggedIn = true;}
    
        
};

#endif
