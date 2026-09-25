#ifndef AIRLINEOPERATIONS_HPP
#define AIRLINEOPERATIONS_HPP

#include <memory>
#include <vector>

#include <tuple>

//Forward declaration
class Aircraft;
class CrewMember;
class Flight;
class Seat;
class Administrator;


//This class acts as a container for all aircrafts, crew members and flights
class AirlineOperations{
        private:
        std::vector<std::shared_ptr<Flight>> allFlights;
        std::vector<std::shared_ptr<Aircraft>> allAircrafts;
        std::vector<std::shared_ptr<CrewMember>> allCrewMembers;

        //declaring friendship
        friend class Administrator;

        //This function searches a flight number and departure date with the existing flights list
        //Used before creating new flights
        //If flight number and departure date is available already in flights list, then throw exception
        void checkFlightContradiction(const std::string& targetFlightNumber, const std::string& targetDepartureDate);
        
        //Function which handles aircrafts assigning to flights
        //Returns bool indicating success or failure process
        bool assignAircraftToFlight(const std::string& tailNumber, const std::string& flightNumber, const std::string& departureDate);

        //Function which will trigger creation of new flight
        //If there is a flight number on the same date this will throw an error and must be catched 
        //Returns bool indicating success or failure process
        bool createFlight(std::string flightNumber, std::string origin, std::string destination,
                       std::string departureDate, std::string departureTime, int duration);

        //Function which updates flight status
        //Should be either "Scheduled" or "Delayed" or "Cancelleed" or "Departured"
        //Returns bool indicating success or failure process
        bool updateFlightStatus(const std::string& targetFlightNumber, const std::string& targetFlightDeparture,
                             std::string newStatus);
        
        //Function which affects flight status and departure time, by passing delay in hours and in mins
        //Returns bool indicating success or failure process
        bool delayFlight(const std::string& targetFlightNumber, const std::string& targetFlightDepartureDate,
                      int hours, int mins);
        
        //Function which creates new aircraft and add it to aircrafts list
        //Aircraft tail number should be unique
        //Returns bool indicating success or failure process
        bool createAircraft(std::string tailNumber, std::string model, int capacity, bool isAvailable);

        //Function which creates new crew member
        //Returns bool indicating success or failure process
        bool createCrewMember(std::string name, std::string role);

        //Function which assigns crew member to existing flight
        //Crew member must be eligible by not exceeding the flight hours limit monthly
        //This function should alter crew member flighing hours
        //Returns bool indicating success or failure process
        bool assignCrewMemberToFlight(int targetID, const std::string& flightNumber, const std::string& departureDate);
        
        //Removes a crew member from flight, and unbinding any relations between them
        //Returns bool indicating success or failure process
        bool removeCrewMemberFromFlight(int targetID, const std::string& flightNumber, const std::string& departureDate);
    
        //function which creates a new maintenance record
        bool newAircraftMaintenance(const std::string& tailNumber, std::string dateScheduled, std::string caseDescription);
    
public:
        //function which returns list of available flights based on criteria
        //vector contains tuples where each tuple holds
        //1) Flight Number
        //2) Origin
        //3) Destination
        //4) Departure date and time
        //5) Arrival date and time
        bool searchFlight(const std::string& departureDate, const std::string& origin, const std::string& destination);
        
        //function which searches all available seats on a flight
        //returns an array of seat numbers available on flight
        std::vector<std::string> searchAvailableSeats(const std::string& flightNumber, const std::string& departureDate);

        //function which reserves a ticket for passenger
        //reservation status stays pending until passenger completes payment
        //returns to caller a reference to flight and seat
        std::tuple<std::shared_ptr<Flight>, std::shared_ptr<Seat>> bookFlight(const std::string& flightNumber, const std::string& departureDate, const std::string& seatNumber);

};

#endif
