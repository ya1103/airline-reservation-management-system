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

