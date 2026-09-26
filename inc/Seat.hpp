#ifndef SEAT_HPP
#define SEAT_HPP

#include <memory>
#include <string>

//Forward declaration
class Flight;
class Reservation;

class Seat{
    private:
        std::string seatNumber;
        std::string seatClass;
        double price;
        bool isAvailable;

        //Weak pointer to flight reference
        std::weak_ptr<Flight> flightReference;

        //Weak pointer to reservation reference if there is a reservation to this seat
        //If no reservation acquires this seat, then it holds empty until reserved
        std::weak_ptr<Reservation> reservationReference;

    public:

        //Parameterized constructor
        Seat(std::shared_ptr<Flight> pointerToFlight, const std::string& newSeatNumber,
             const std::string& newSeatClass, double price, bool available = true)
             :seatNumber(newSeatNumber), seatClass(newSeatClass), price(price),
              isAvailable(available), flightReference(pointerToFlight) {}

        // Getters
        const std::string& getSeatNumber() const { return seatNumber; }
        const std::string& getSeatClass() const { return seatClass; }
        bool getIsAvailable() const { return isAvailable; }

        //Setter for availability
        void setIsAvailable(bool available) { isAvailable = available; }

        // ==========================================
        // FLIGHT REFERENCE
        // ==========================================

        // Getter: Promotes the weak_ptr to a shared_ptr to safely check/use it
        // Returns nullptr if the Flight has been destroyed
        // std::shared_ptr<Flight> getFlightReference() const {
        //     return flightReference.lock();
        // }

        // // Setter: Accepts a shared_ptr and implicitly converts it to a weak_ptr
        // void setFlightReference(std::shared_ptr<Flight> newFlight) {
        //     flightReference = std::move(newFlight);
        // }

        // ==========================================
        // RESERVATION REFERENCE
        // ==========================================

        // Getter: Promotes the weak_ptr to a shared_ptr
        // Returns nullptr if the seat is currently unreserved/empty
        std::shared_ptr<Reservation> getReservationReference() const {
            return reservationReference.lock();
        }

        // Setter: Links a reservation to this seat
        void setReservationReference(std::shared_ptr<Reservation> newReservation) {
            reservationReference = std::move(newReservation);
        }

};

#endif
