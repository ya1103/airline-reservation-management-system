#ifndef PASSENGER_HPP
#define PASSENGER_HPP

#include "User.hpp"

//forward declaration
class Reservation;

//inherits from User class
class Passenger: User{
    private:
        int loyaltyPoints;
        std::vector<std::shared_ptr<Reservation>> passengerReservations; //list of reservations made by a passenger

        //function creates a reservation only if passenger booked a flight
        //reservation status stays pending until payment is complete or cancelled
        //void makeReservation()
    public:
        void searchFlight(const std::string& departureDate, const std::string& origin, const std::string& destination);
        
        //function which searches all available seats on a flight
        void availableSeats(const std::string& flightNumber, const std::string& departureDate);

        //function which reserves a ticket for passenger
        //reservation status stays pending until passenger completes payment
        void bookFlight(const std::string& flightNumber, const std::string& seatNumber, const std::string& departureDate);
        
        //function which iterates over all reservations made by user to print them out
        void viewHistory();

    };      

#endif
