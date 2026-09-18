#ifndef AIRLINEOPERATIONS_HPP
#define AIRLINEOPERATIONS_HPP

#include <memory>
#include <vector>

//Forward declaration
class Aircraft;
class CrewMember;
class Flight;
class Seat;


//This class acts as a container for all aircrafts, crew members and flights
class AirlineOperations{
        private:
        std::vector<std::shared_ptr<Flight>> allFlights;
        std::vector<std::shared_ptr<Aircraft>> allAircrafts;
        std::vector<std::shared_ptr<CrewMember>> allCrewMembers;

    public:
        //function which returns list of available flights based on criteria
        //vector contains tuples where each tuple holds
        //1) Flight Number
        //2) Origin
        //3) Destination
        //4) Departure date and time
        //5) Arrival date and time
        std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>> searchFlight(const std::string& departureDate, const std::string& origin, const std::string& destination);
        
        //function which searches all available seats on a flight
        //returns an array of seat numbers available on flight
        std::vector<std::string> searchAvailableSeats(const std::string& flightNumber, const std::string& departureDate);

        //function which reserves a ticket for passenger
        //reservation status stays pending until passenger completes payment
        //returns to caller a reference to flight and seat
        std::tuple<std::shared_ptr<Flight>, std::shared_ptr<Seat>> bookFlight(const std::string& flightNumber, const std::string& departureDate, const std::string& seatNumber);

};

#endif
