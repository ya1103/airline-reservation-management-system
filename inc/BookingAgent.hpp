#ifndef BOOKINGAGENT_HPP
#define BOOKINGAGENT_HPP

#include <memory>
#include "User.hpp"

//Forward declaration
class Passenger;
class Reservation;

class BookingAgent: public User{
    private:
        inline static int nextID = 2000;
    public: 
        //Parameterized constructor ONLY for rebuilding existing passengers from memory on program startup
        //Should NOT be used for creation of new passengers
        BookingAgent(int passedID, const std::string& passedName, const std::string& passedEmail, const std::string& password)
            : User(passedID, passedName, "BookingAgent", passedEmail, password) {}
        
        //Parameterized constructor ONLY for creating new passengers
        BookingAgent(const std::string& passedName, const std::string& passedEmail, const std::string& password)
            : BookingAgent(nextID++, passedName, passedEmail, password) {}
        
        //Static function which sets static nextID member
        static void setNextID(int passedID) {nextID = passedID;}
        //Searches for flights based on criteria departure, origin, and destination
        //Prints all available flights
        void searchFlight(const std::string& departureDate, const std::string& origin, const std::string& destination);
        
        //function which searches all available seats on a flight
        //Prints all available seats
        void availableSeats(const std::string& flightNumber, const std::string& departureDate);

        //Calls book flight using passenger object shared pointer and passing arguments
        void BookFlightForPassenger(std::shared_ptr<Passenger>, const std::string& flightNumber, const std::string& seatNumber, const std::string& departureDate);

        //Checks in passenger on flight updating reservation status on passenger's flight
        void checkInPassenger(std::shared_ptr<Passenger>, std::string reservationID);
};

#endif
