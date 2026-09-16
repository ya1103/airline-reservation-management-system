#ifndef RESERVATION_HPP
#define RESERVATION_HPP

#include <string>
#include <memory>

//forward declaration
class Passenger;
class Payment;
//class Flight;

class Reservation{
    private:
        std::string id;
        std::string bookingDate;
        std::string status;
        std::weak_ptr<Passenger> passengerReference;
        std::unique_ptr<Payment> paymentReference = nullptr; //default is null until payment is processed
        //std::weak_ptr<Flight> flightReference;
        //std::weak_ptr<Seat> seatReference;
        public:
        //function which cancels passenger flight and makes seat available for others to reserve
        //if reservation was confirmed before start refund process
        void cancelReservation();

        //function which helps passenger to reassign a new seat if available
        void modifyReservation(const std::string& newSeatNumber);

        //function which processes payment with payment class
        void processPayment();
};

#endif
