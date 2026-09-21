#ifndef ADMINISTRATOR_HPP
#define ADMINISTRATOR_HPP

#include <memory>
#include "User.hpp"

//Forward declaration
class UserManager;

class Administrator: public User{
    private:
        std::weak_ptr<UserManager> allUsersReference;
        inline static int nextID = 1000;
    public:        
        //Parameterized constructor ONLY for rebuilding existing admins from memory on program startup
        //Should not be used for creation of new admins
        Administrator(int passedID, const std::string& passedName, const std::string& passedEmail, const std::string& password, std::shared_ptr<UserManager> usersReference)
            :  User(passedID, passedName, "Administrator", passedEmail, password), allUsersReference(usersReference){}

        //Parameterized constructor ONLY for creating new administrators
        Administrator(const std::string& passedName, const std::string& passedEmail, const std::string& password, std::shared_ptr<UserManager> usersReference)
            : Administrator(nextID++, passedName, passedEmail, password, usersReference) {} 

        //Static function which sets static nextID member
        static void setNextID(int passedID) {nextID = passedID;}

        //Function which creates user based on criteria
        //User's role must be either: Passenger, BookingAgent or Administrator
        //If passed argument is neither of them it should print error message and abort creation
        //If all arguments are valid, print successfull message
        void createUser(const std::string& passedName, const std::string& passedRole, const std::string& passedEmail, const std::string& password);

        //Function which deletes user by id and role (Passenger, BookingAgent or Administrator)
        //If id not found print error message and abort process
        //If user found print successfull message
        //Note: an admin can not delete him self 
        void deleteUser(int id, const std::string& role);

        //Function which updates user data
        //It should not affect user's id, role, email or password
        //Searches user based on id and role
        //Name can only be altered
        void updateUserName(int id, const std::string& role, std::string newName);

        //Function which will print down the menu choices for user
        void showMenu() override;

        //Function which will print another menu of options related to flights management
        void manageFlights();

        //Function which will trigger creation of new flight
        //If there is a flight number on the same date this will throw an error and must be catched
        bool createNewFlight(std::string newFlightNumber, std::string newOrigin, std::string newDestination,
                std::string newDepartureDate, std::string newDepartureTime, int newDuration);

        //Function which updates flight status
        //Should be either "Scheduled" or "Delayed" or "Cancelleed" or "Departured"
        void updateFlightStatus(const std::string& targetFlightNumber,
                                const std::string& targetFlightDepartureDate,
                                std::string flightNewStatus);
        
        //Function which affects flight status and departure time, by passing delay in hours and in mins
        void delayFlight(int hours, int mins);

        //Function which creates new aircraft and add it to aircrafts list
        //Aircraft tail number should be unique
        void createNewAircraft();

        //Function which assigns aircraft to a flight
        //Aircraft should not have any flights on the same day of the targetted flight
        void assignAircraftToFlight(const std::string& tailNumber, const std::string& flightNumber, const std::string& departureDate);
        
        //Function which creates new crew member
        //Email must be unique, otherwise it will throw an error
        void createNewCrewMember();

        //Function which assigns crew member to existing flight
        //Crew member must be eligible by not exceeding the flight hours limit monthly
        void assignCrewMemberToFlight(int targetID, const std::string& flightNumber, const std::string& departureDate);

        //Function which removes crew member from flight list
        //This should alter flight hours of the crew member to decrease it back
        void removeCrewMemberFromFlight(int targetID, const std::string& flightNumber, const std::string& departureDate);
    };

#endif
