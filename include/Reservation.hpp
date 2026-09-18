#ifndef RESERVATION_HPP
#define RESERVATION_HPP

#include <string>
#include <memory>

//forward declaration
class Passenger;
class Payment;
class Flight;
class Seat;

class Reservation: public std::enable_shared_from_this<Reservation>{
    private:
        std::string id;
        std::string bookingDate;
        std::string status;
        std::weak_ptr<Passenger> passengerReference;
        std::shared_ptr<Payment> paymentReference = nullptr; //default is null until payment is processed
        std::weak_ptr<Flight> flightReference; //default empty pointer until a flight is booked
        std::weak_ptr<Seat> seatReference; //default empty pointer until a seat is booked
        public:
        //Parameterized Constructor
        //Note: after constructing a new reservation, assignReservationToFlightAndSeat() must be called immediately after
        //      this, or otherwise the flight and seat will not be observing this new reservation
        Reservation(std::shared_ptr<Passenger> ptrToPassenger, std::shared_ptr<Flight> ptrToFlight,
            std::shared_ptr<Seat> ptrToSeat)
            : id("N/A"), bookingDate("Today"), status("Pending"),
            passengerReference(ptrToPassenger), flightReference(ptrToFlight), seatReference(ptrToSeat){}

        //This function must be called immediately after constructing a new reservation
        //It should not be called inside the constructor other wise it will throw bad weak pointer exception
        void assignReservationToFlightAndSeat();
        
        //function which cancels passenger flight and makes seat available for others to reserve
        //if reservation was confirmed before start refund process
        void cancelReservation();

        //function which helps passenger to reassign a new seat if available
        void modifyReservation(const std::string& newSeatNumber);

        //function which processes payment with payment class
        void processPayment();
};

#endif
