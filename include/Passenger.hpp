#ifndef PASSENGER_HPP
#define PASSENGER_HPP

#include "User.hpp"

//forward declaration
class Reservation;

//inherits from User class and enable_shared_from_this which allow passing shared pointer of "this" object
class Passenger: public User, public std::enable_shared_from_this<Passenger>{
    private:        
        
        inline static int nextID = 3000;
        int loyaltyPoints;
        std::vector<std::shared_ptr<Reservation>> passengerReservations; //list of reservations made by a passenger

        //function creates a reservation only if passenger booked a flight
        //reservation status stays pending until payment is complete or cancelled
        void makeReservation();
    public:        
        //Parameterized constructor ONLY for rebuilding existing passengers from memory on program startup
        //Should NOT be used for creation of new passengers
        Passenger(int passedID, const std::string& passedName, const std::string& passedEmail, const std::string& password)
            : User(passedID, passedName, "Passenger", passedEmail, password) {}

        //Parameterized constructor ONLY for creating new passengers 
        Passenger(const std::string& passedName, const std::string& passedEmail, const std::string& password)
            : Passenger(nextID++, passedName, passedEmail, password) {}
        
        //Static function which sets static nextID member
        static void setNextID(int passedID) {nextID = passedID;}

        void searchFlight(const std::string& departureDate, const std::string& origin, const std::string& destination);
        
        //function which searches all available seats on a flight
        void availableSeats(const std::string& flightNumber, const std::string& departureDate);

        //function which reserves a ticket for passenger
        //reservation status stays pending until passenger completes payment
        //this should call another makeReservation() to create a reservation with related details
        //returns bool indicating successful booking or failed process
        bool bookFlight(const std::string& flightNumber, const std::string& seatNumber, const std::string& departureDate);

        //Checks in passenger on flight updating reservation status on passenger's flight to checkedIN
        void checkIn(std::string reservationID);
        
        //function which iterates over all reservations made by user to print them out
        void viewHistory();

    };      

#endif
