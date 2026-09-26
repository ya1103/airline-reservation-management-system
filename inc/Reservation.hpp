#ifndef RESERVATION_HPP
#define RESERVATION_HPP

#include <string>
#include <memory>
#include "DateUtils.hpp"

//forward declaration
class Passenger;
class Payment;
class Flight;
class Seat;

class Reservation: public std::enable_shared_from_this<Reservation>{
    private:
        int id;
        inline static int nextID = 1000;
        std::string bookingDate;
        std::string status;
        std::weak_ptr<Passenger> passengerReference;
        std::shared_ptr<Payment> paymentReference = nullptr; //default is null until payment is processed
        std::weak_ptr<Flight> flightReference; //default empty pointer until a flight is booked
        std::weak_ptr<Seat> seatReference; //default empty pointer until a seat is booked
        
        //Setter for reservation status
        void setStatus(std::string newStatus) { status = std::move(newStatus); }
        public:
        //Parameterized Constructor ONLY for creating new reservations
        //Note: after constructing a new reservation, assignReservationToFlightAndSeat() must be called immediately after
        //      this, or otherwise the flight and seat will not be observing this new reservation
        Reservation(std::shared_ptr<Passenger> ptrToPassenger, std::shared_ptr<Flight> ptrToFlight,
            std::shared_ptr<Seat> ptrToSeat)
             : Reservation(nextID++, ptrToPassenger, ptrToFlight, ptrToSeat, "Pending", DateUtils::getCurrentDate()) {}
        
        //Parameterized constructor ONLY for rebuilding existing reservations from memory during program startup
        Reservation(int passedID, std::shared_ptr<Passenger> ptrToPassenger,
            std::shared_ptr<Flight> ptrToFlight, std::shared_ptr<Seat> ptrToSeat,
            std::string passedStatus, std::string passedDate)
            : id(passedID), bookingDate(std::move(passedDate)), status(std::move(passedStatus)),
            passengerReference(ptrToPassenger), flightReference(ptrToFlight), seatReference(ptrToSeat) {}
        
        //Getter for reservation ID
        int getID() const { return id; }

        //Getter for reservation status
        const std::string& getStatus() { return status; }

        bool checkIn();

        //This function must be called immediately after constructing a new reservation
        //It should not be called inside the constructor other wise it will throw bad weak pointer exception
        void assignReservationToFlightAndSeat();
        
        //function which cancels passenger flight and makes seat available for others to reserve
        //if reservation was confirmed previously, then start refund process
        bool cancelReservation();

        //function which helps passenger to reassign a new seat if available
        void modifyReservation(const std::string& newSeatNumber);

        //function which processes payment with payment class
        void processPayment();

        //Function which prints all details related to reservation
        void printReservInfo() const;
};

#endif
