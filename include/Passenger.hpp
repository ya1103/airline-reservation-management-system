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

        //Function creates a reservation only if passenger booked a flight
        //Reservation status stays pending until payment is complete or cancelled
        void makeReservation(std::shared_ptr<Reservation>&& res)
        {
            passengerReservations.push_back(std::move(res));
        }
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

        //Function which performs search on airline operations to fetch all flights available on given criteria
        //If any invalid data, it shall print out error for user and return false
        //Else print all available flights' details and return true
        bool searchFlight(const std::string& departureDate, const std::string& origin, const std::string& destination);
        
        //Function which searches all available seats on a flight by flight number and departure date
        //If any invalid data, it shall print out error for user and return false
        //Else print all available seats' details and return true
        bool availableSeats(const std::string& flightNumber, const std::string& departureDate);

        //function which reserves a ticket for passenger
        //reservation status stays pending until passenger completes payment
        //this should call another makeReservation() to create a reservation with related details
        //returns bool indicating successful booking or failed process
        bool bookFlight(const std::string& flightNumber, const std::string& seatNumber, const std::string& departureDate);

        //Checks in passenger on flight updating reservation status on passenger's flight to checkedIN
        //If any invalid data, it shall print out error for user and return false
        //Else print all available flights' details and return true
        bool checkIn(std::string reservationID);
        
        //Function which iterates over all reservations made by user to print them out
        //If any invalid data, it shall print out error for user and return to caller safely 
        //Else prints all reservations history for passenger
        void viewHistory();

        //Function which will print menu options for passenger
        virtual void showMenu() override;

    };      

#endif
