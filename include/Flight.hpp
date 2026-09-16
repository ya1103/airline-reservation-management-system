#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include <string>
#include <memory>
#include <vector>

//forward declaration
class Reservation;
class CrewMember;
class Aircraft;
class Seat;

class Flight{
    private:
        std::string flightNumber;
        std::string origin;
        std::string destination;
        std::string departure;
        std::string arrival;
        std::string status;

        //list of reservations assigned to this flight
        std::vector<std::shared_ptr<Reservation>> reservationsReference;

        //list of crew members assigned to this flight
        std::vector<std::shared_ptr<CrewMember>> crewMembersReference;

        //reference to assigned aircraft
        std::shared_ptr<Aircraft> aircraftReference;
    public:
        const auto& getFlightNumber() const { return flightNumber; }
        const auto& getOrigin() const { return origin; }
        const auto& getDestination() const { return destination; }
        const auto& getDeparture() const { return departure; }
        const auto& getArrival() const { return arrival; }
        const auto& getStatus() const { return status; }

        //function which adds a new crew member to this list of crew members assigned to this flight
        void addCrew(std::shared_ptr<CrewMember>);

        //function which assigns aircraft for this flight
        void assignAircraft(std::shared_ptr<Aircraft>);

        //function which updates flight status acts as a setter
        void updateStatus(const std::string& newStatus);

        //function which updates flight departure time
        //parameter is auto as departure data type might change through development process
        void updateDeparture(const auto& newDepartureTime);

        //function which updates flight arrival time
        //parameter is auto as arrival data type might change through development process
        void updateArrival(const auto& newArrivalTime);

        Seat& bookSeat(const std::string&);


};

#endif
