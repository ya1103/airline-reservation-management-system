#ifndef BOOKINGAGENT_HPP
#define BOOKINGAGENT_HPP

#include <memory>
#include "User.hpp"

//Forward declaration
class Passenger;
class Reservation;

class BookingAgent: public User{
    public: 
        //Parameterized constructor
        BookingAgent(const std::string& passedName, const std::string& passedRole, const std::string& passedEmail, const std::string& password)
            :  User(passedName, passedRole, passedEmail, password){}
        
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
