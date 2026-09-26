#include "Reservation.hpp"
#include "Seat.hpp"
#include "Flight.hpp"

// This function must be called immediately after constructing a new reservation
// It should not be called inside the constructor other wise it will throw bad weak pointer exception
void Reservation::assignReservationToFlightAndSeat(){
    if(auto shared_ptr_to_flight = flightReference.lock())
    {
        shared_ptr_to_flight->addReservation(shared_from_this()); //Pass shared pointer from *this* object
    }

    if(auto shared_ptr_to_seat = seatReference.lock())
    {
        shared_ptr_to_seat->setReservationReference(shared_from_this()); //Pass shared pointer from *this* object
    }
}

bool Reservation::checkIn()
{
    if(status != "Confirmed")
    {
        std::cout << "Please complete payment before checking in.\n";
        return false;
    }

    if(status == "CheckedIn")
    {
        std::cout << "Passenger already checked-in on flight\n";
        return true;
    }

    //If all constraints passed then check in passenger
    setStatus("CheckedIn");
    std::cout << "Checked-in passenger on flight successfully";
    return true;
}