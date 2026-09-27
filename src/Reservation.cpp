#include "Reservation.hpp"
#include "Seat.hpp"
#include "Flight.hpp"
#include "Payment.hpp"

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
    if(status == "CheckedIn")
    {
        std::cout << "Passenger already checked-in on flight\n";
        return true;
    }

    if(status != "Confirmed")
    {
        std::cout << "Please complete payment before checking in.\n";
        return false;
    }

    //If all constraints passed then check in passenger
    setStatus("CheckedIn");
    std::cout << "Checked-in passenger on flight successfully";
    return true;
}

void Reservation::printReservInfo() const
{
    std::cout << "========================================\n";
    std::cout << "         RESERVATION INFORMATION        \n";
    std::cout << "========================================\n";
    std::cout << " Reservation ID : " << id << "\n";
    std::cout << " Booking Date   : " << bookingDate << "\n";
    std::cout << " Status         : " << status << "\n";

    if (auto seat = seatReference.lock()) {
        std::cout << " Seat Number    : " << seat->getSeatNumber() << "\n";
        std::cout << " Seat Class     : " << seat->getSeatClass() << "\n";
    } else {
        std::cout << " Seat           : Not available (reference expired)\n";
    }

    std::cout << "----------------------------------------\n";

    if (auto flight = flightReference.lock()) {
        flight->printFlightInfo();
    } else {
        std::cout << " Flight         : Not available (reference expired)\n";
    }

    std::cout << "========================================\n";
}

bool Reservation::cancelReservation(){
    //Check before double cancellation
    if(status == "Cancelled")
    {
        std::cout << "Reservation is already cancelled!\n";
        return false;
    }

    if(auto shared = seatReference.lock())
    {
        //Release seat to be available again
        shared->setIsAvailable(true);
    }

    //Update status
    status = "Cancelled";

    if(paymentReference)
    {
        //If payment was made previously start refund process
        paymentReference->refund();
    }

    //Return to caller indicating successfull process
    return true;

    
}

bool Reservation::modifyReservation(const std::string& newSeatNumber)
{
    if (status == "Cancelled" || status == "CheckedIn") {
        std::cout << "Cannot modify a reservation that is " << status << ".\n";
        return false;
    }

    auto flight = flightReference.lock();
    if (!flight) {
        std::cout << "Flight reference no longer available.\n";
        return false;
    }

    //Books new seat if available and marks it unavailable
    auto newSeat = flight->bookSeat(newSeatNumber); 
    if (!newSeat) {
        return false; // bookSeat already printed the error message
    }

    //Releases old seat to make it available again
    if (auto oldSeat = seatReference.lock()) {
        flight->releaseSeat(oldSeat);
        oldSeat->setReservationReference(nullptr);
    }

    //Assign new seat to seatReference
    newSeat->setReservationReference(shared_from_this());
    seatReference = newSeat;

    std::cout << "Seat changed successfully to " << newSeatNumber << ".\n";
    return true;
}


bool Reservation::processPayment(std::string paymentMethod)
{
    auto seat = seatReference.lock();
    
    //Check nullability before dereferencing
    if(!seat)
    {
        std::cout << "No seat reference!\n";
        return false;
    }

    std::string CreditCardNumber;
    if(paymentMethod == "CreditCard")
    {
        std::cout << "\nPlease Enter Credit Card Number (XXXX-XXXX-XXXX-XXXX): ";
        std::cin >> CreditCardNumber;
    }
    
    double seatPrice = seat->getPrice();
    paymentReference = std::make_shared<Payment>(shared_from_this(), seatPrice, std::move(paymentMethod));
    paymentReference->process();
    status = "Confirmed";
    return true;
}