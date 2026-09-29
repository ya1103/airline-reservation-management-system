#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include <iostream>
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
        std::string departureDate;
        std::string departureTime;
        std::string gate = "TBA"; //(TBA) To be announced until set by airline operations' admin
        int duration;
        int hoursDelay = 0;
        int minsDelay = 0;
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

        //declaring friendship
        friend class AirlineOperations;

        // Setters
        void setFlightNumber(std::string newFlightNumber) { flightNumber = newFlightNumber; }
        void setOrigin(std::string newOrigin) { origin = newOrigin; }
        void setDestination(std::string newDestination) { destination = newDestination; }
        void setDepartureTime(std::string newDepartureTime) { departureTime = newDepartureTime; }
        void setDepartureDate(std::string newDepartureDate) { departureDate = newDepartureDate; }
        void setDuration(int newDuration) { duration = newDuration; }
        bool setFlightStatus(std::string newFlightStatus);
        void setGate(std::string newGate) { gate = std::move(newGate); }
        
        //Function which updates flight departure time
        //Takes two parameters delay in hours and mins
        //Updates flight status to "Delayed" and modify internal hoursDelay and minsDelay data members
        void delayDepartureTime(int hours, int mins)
        {
            if(hours < 0 || hours > 23)
            {
                std::cout << "Invalid hours, should be between 0 and 24 hours, please try again\n";
                return;
            }else if(mins < 0 || mins > 59)
            {
                std::cout <<"Invalid minutes, should be between 0 and 60 mins, please try again\n";
                return;
            }
            //If conditions passed, assign safely
            hoursDelay = hours;
            minsDelay = mins;
            //Update status to Delayed
            flightStatus = "Delayed";
        }

        //Function which prints extra details related to flight
        //Such as aircraft type, number of seats, number of crew members, number of reservations
        //Mainly important to administrators and airline operations
        void printFlightOperationsInfo() const;

        //Function which counts reserved seats by checking if it is unavailable
        //Returns count of reserved seats
        int countReservedSeats() const;
    public:

        //Parameterized constructor
        //Note: initializeSeats() must be called after constructing each flight
        Flight(std::string newFlightNumber, std::string newOrigin, std::string newDestination,
                std::string newDepartureDate, std::string newDepartureTime, int newDuration, std::string newStatus = "Scheduled")
                : flightNumber(std::move(newFlightNumber)), origin(std::move(newOrigin)), destination(std::move(newDestination)), departureDate(std::move(newDepartureDate)),
                    departureTime(std::move(newDepartureTime)), duration(newDuration) , flightStatus(std::move(newStatus)) {}
        
        //Function which must be called after constructing each flight
        //Unless no seats are assigned to this flight
        void initializeSeats();

        const auto& getFlightNumber() const { return flightNumber; }
        const auto& getOrigin() const { return origin; }
        const auto& getDestination() const { return destination; }
        const auto& getDepartureTime() const { return departureTime; }
        const auto& getDepartureDate() const { return departureDate; }
        int getDuration() const { return duration; }
        const auto& getFlightStatus() const { return flightStatus; }
        const std::string& getGate() const { return gate; }
        int getHoursDelay() const { return hoursDelay; }
        int getMinsDelay() const { return minsDelay; }
        // Boarding opens 60 minutes before the effective departure (scheduled time + any delay)
        std::string getBoardingTime() const;

        //Function which releases acquired seat back to available
        //This is used if reassigning a new seat is to be made
        void releaseSeat(std::shared_ptr<Seat> seat);

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

        //Helper function to print flight details
        void printFlightInfo(void) const;

        //Function which prints all seats on flight
        //If seat is not available seat number will not be printed, instead "-" will be printed indicating it is booked
        void printSeatMap() const;

        //Function which books a seat by setting to unavailable to avoid double booking
        //Returns a shared pointer of the booked seat
        std::shared_ptr<Seat> bookSeat(const std::string& seatNumber);


};

#endif
