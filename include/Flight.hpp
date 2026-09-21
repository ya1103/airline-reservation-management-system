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

class Flight: public std::enable_shared_from_this<Flight>{
    private:
        std::string flightNumber;
        std::string origin;
        std::string destination;
        std::string departure;
        std::string arrival;
        std::string flightStatus;
        int numberOfSeats = 210; //Assume all flights have the same number of seats for simplicity

        //list of reservations assigned to this flight
        std::vector<std::shared_ptr<Reservation>> reservationsReference;

        //list of crew members assigned to this flight
        std::vector<std::shared_ptr<CrewMember>> crewMembersReference;

        //reference to assigned aircraft
        std::shared_ptr<Aircraft> aircraftReference;

        //vector of references of each seat on flight
        std::vector<std::shared_ptr<Seat>> seatsReference;
    public:

        //Parameterized constructor
        //Note: initializeSeats() must be called after constructing each flight
        Flight(std::string newFlightNumber, std::string newOrigin, std::string newDestination,
                std::string newDeparture, std::string newArrival, std::string newStatus = "On Schedule")
                : flightNumber(std::move(newFlightNumber)), origin(std::move(newOrigin)), destination(std::move(newDestination)), departure(std::move(newDeparture)),
                    arrival(std::move(newArrival)), flightStatus(std::move(newStatus)) {}
        
        //Function which must be called after constructing each flight
        //Unless no seats are assigned to this flight
        void initializeSeats();

        const auto& getFlightNumber() const { return flightNumber; }
        const auto& getOrigin() const { return origin; }
        const auto& getDestination() const { return destination; }
        const auto& getDeparture() const { return departure; }
        const auto& getArrival() const { return arrival; }
        const auto& getFlightStatus() const { return flightStatus; }
        
        //function which updates flight status acts as a setter
        void updateStatus(const std::string& newStatus){
            flightStatus = newStatus;
        }

        //function which updates flight departure time
        //parameter is auto as departure data type might change through development process
        void updateDeparture(const auto& newDepartureTime);

        //function which updates flight arrival time
        //parameter is auto as arrival data type might change through development process
        void updateArrival(const auto& newArrivalTime);


        // ==========================================
        // AIRCRAFT REFERENCE
        // ==========================================
        
        // Getter: Returns a read-only const reference to the shared_ptr
        const std::shared_ptr<Aircraft>& getAircraftReference() const {
            return aircraftReference;
        }

        // Setter: Efficiently takes ownership of a new aircraft shared_ptr
        void setAircraftReference(std::shared_ptr<Aircraft> newAircraft) {
            aircraftReference = std::move(newAircraft);
        }

        // ==========================================
        // SEATS REFERENCE
        // ==========================================

        //Getter: Returns a read-only view of the entire seats vector
        const std::vector<std::shared_ptr<Seat>>& getSeats() const {
            return seatsReference;
        }

        // Adder: Appends a single seat to the flight's layout via moving
        void addSeat(std::shared_ptr<Seat> newSeat) {
            seatsReference.push_back(std::move(newSeat));
        }

        // ==========================================
        // RESERVATIONS REFERENCE
        // ==========================================

        // Getter: Returns a read-only view of all reservations on this flight
        const std::vector<std::shared_ptr<Reservation>>& getReservations() const {
            return reservationsReference;
        }

        // Adder: Adds a single reservation to the flight track
        void addReservation(std::shared_ptr<Reservation> newReservation) {
            reservationsReference.push_back(std::move(newReservation));
        }

        // ==========================================
        // CREW MEMBERS REFERENCE
        // ==========================================

        // Getter: Returns a read-only view of the assigned flight crew
        const std::vector<std::shared_ptr<CrewMember>>& getCrewMembers() const {
            return crewMembersReference;
        }

        // Adder: Assigns an individual crew member to this flight
        void addCrewMember(std::shared_ptr<CrewMember> newCrewMember) {
            crewMembersReference.push_back(std::move(newCrewMember));
        }

        //Remover: Removes crew member from this flight
        void removeCrewMember(std::shared_ptr<CrewMember> CrewMember);
        //==========================================


        std::shared_ptr<Seat> bookSeat(const std::string& seatNumber);


};

#endif
