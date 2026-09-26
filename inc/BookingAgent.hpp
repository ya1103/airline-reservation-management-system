#ifndef BOOKINGAGENT_HPP
#define BOOKINGAGENT_HPP

#include <memory>
#include "User.hpp"

//Forward declaration
class Passenger;
class Reservation;
class UserManager;

class BookingAgent: public User{
    private:
        inline static int nextID = 2000;
        
        //Reference to user manager which holds all type of users
        std::weak_ptr<UserManager> allUsersReference;

        // Looks up an active passenger by ID via UserManager. Returns nullptr (with a
        // printed reason) if the manager reference is gone or no matching passenger exists.
        // Private as it will be called by another functions in same class only
        std::shared_ptr<Passenger> getPassengerByID(int passengerID);
    public: 
        //Parameterized constructor ONLY for rebuilding existing passengers from memory on program startup
        //Should NOT be used for creation of new passengers
        BookingAgent(int passedID, const std::string& passedName, const std::string& passedEmail, const std::string& password, std::shared_ptr<UserManager> usersReference)
            : User(passedID, passedName, "BookingAgent", passedEmail, password) , allUsersReference(usersReference) {}
        
        //Parameterized constructor ONLY for creating new passengers
        BookingAgent(const std::string& passedName, const std::string& passedEmail, const std::string& password, std::shared_ptr<UserManager> usersReference)
            : BookingAgent(nextID++, passedName, passedEmail, password, usersReference) {}
        
        //Static function which sets static nextID member
        static void setNextID(int passedID) {nextID = passedID;}
        
        //Function which will print down the menu choices for admin
        void showMenu() override;
        
        //Searches for flights based on criteria departure, origin, and destination
        //Prints all available flights
        bool searchFlight(const std::string& departureDate, const std::string& origin, const std::string& destination);
        
        //function which searches all available seats on a flight
        //Prints all available seats
        void availableSeats(const std::string& flightNumber, const std::string& departureDate);

        //Calls book flight using passenger object shared pointer and passing arguments
        bool BookFlightForPassenger(int targetPassengerID, const std::string& flightNumber, const std::string& seatNumber, const std::string& departureDate);

        //Checks in passenger on flight updating reservation status on passenger's flight
        bool checkInPassenger(int targetPassengerID, int reservationID);
};

#endif
