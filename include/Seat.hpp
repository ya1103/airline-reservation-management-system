#ifndef SEAT_HPP
#define SEAT_HPP

#include <memory>
#include <string>

//Forward declaration
class Aircraft;
class Reservation;

class Seat{
    private:
        std::string seatNumber;
        std::string seatClass;
        bool isAvailable;

        //Weak pointer to aircraft reference
        std::weak_ptr<Aircraft> aircraftReference;

        //Weak pointer to reservation reference if there is a reservation to this seat
        //If no reservation acquires this seat, then it holds nullptr
        std::weak_ptr<Reservation> reservationReference;

    public:
        // Getters
        const std::string& getSeatNumber() const { return seatNumber; }
        const std::string& getSeatClass() const { return seatClass; }
        bool getIsAvailable() const { return isAvailable; }

        // // Weak pointer reference getters
        // const std::weak_ptr<Aircraft>& getAircraftReference() const { return aircraftReference; }
        // const std::weak_ptr<Reservation>& getReservationReference() const { return reservationReference; }

        // // Safe helper getters (returns nullptr if expired or unassigned)
        // std::shared_ptr<Aircraft> getAircraft() const { return aircraftReference.lock(); }
        // std::shared_ptr<Reservation> getReservation() const { return reservationReference.lock(); }


};

#endif
