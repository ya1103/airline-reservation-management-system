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
        Flight(const std::string& newFlightNumber, const std::string& newOrigin, const std::string& newDestination,
                const std::string& newDeparture, const std::string& newArrival, const std::string& newStatus = "On Schedule")
                : flightNumber(newFlightNumber), origin(newOrigin), destination(newDestination), departure(newDeparture),
                    arrival(newArrival), flightStatus(newStatus) {}
        
        //Function which must be called after constructing each flight
        //Unless no seats are assigned to this flight
        void initializeSeats() {
            const char columns[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
            seatsReference.reserve(210);

            for (int r = 1; r <= 30; ++r) {
                for (int c = 0; c < 7; ++c) {
                    std::string seatNumberStr = std::to_string(r) + columns[c];
                    
                    // ✅ This is now 100% safe because the shared_ptr exists!
                    seatsReference.push_back(std::make_shared<Seat>(shared_from_this(), seatNumberStr, "Economy", 50.00));
                }
            }
        }

        const auto& getFlightNumber() const { return flightNumber; }
        const auto& getOrigin() const { return origin; }
        const auto& getDestination() const { return destination; }
        const auto& getDeparture() const { return departure; }
        const auto& getArrival() const { return arrival; }
        const auto& getFlightStatus() const { return flightStatus; }

        // ==========================================
        // AIRCRAFT REFERENCE
        // ==========================================
        
        // // Getter: Returns a read-only const reference to the shared_ptr
        // const std::shared_ptr<Aircraft>& getAircraftReference() const {
        //     return aircraftReference;
        // }

        // // Setter: Efficiently takes ownership of a new aircraft shared_ptr
        // void setAircraftReference(std::shared_ptr<Aircraft> newAircraft) {
        //     aircraftReference = std::move(newAircraft);
        // }

        // ==========================================
        // SEATS REFERENCE
        // ==========================================

        // Getter: Returns a read-only view of the entire seats vector
        // const std::vector<std::shared_ptr<Seat>>& getSeatsReference() const {
        //     return seatsReference;
        // }

        // // Adder: Appends a single seat to the flight's layout via moving
        // void addSeatReference(std::shared_ptr<Seat> newSeat) {
        //     seatsReference.push_back(std::move(newSeat));
        // }

        // ==========================================
        // RESERVATIONS REFERENCE
        // ==========================================

        // Getter: Returns a read-only view of all reservations on this flight
        const std::vector<std::shared_ptr<Reservation>>& getReservationsReference() const {
            return reservationsReference;
        }

        // Adder: Adds a single reservation to the flight track
        void addReservationReference(std::shared_ptr<Reservation> newReservation) {
            reservationsReference.push_back(std::move(newReservation));
        }

        // ==========================================
        // CREW MEMBERS REFERENCE
        // ==========================================

        // Getter: Returns a read-only view of the assigned flight crew
        // const std::vector<std::shared_ptr<CrewMember>>& getCrewMembersReference() const {
        //     return crewMembersReference;
        // }

        // // Adder: Assigns an individual crew member to this flight
        // void addCrewMemberReference(std::shared_ptr<CrewMember> newCrewMember) {
        //     crewMembersReference.push_back(std::move(newCrewMember));
        // }
        // ==========================================

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

        std::shared_ptr<Seat> bookSeat(const std::string&);


};

#endif
