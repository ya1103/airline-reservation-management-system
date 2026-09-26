#include "AirlineOperations.hpp"
#include "Flight.hpp"
#include "Aircraft.hpp"
#include "CrewMember.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>

//This function searches a flight number and departure date with the existing flights list
//Used before creating new flights
//If flight number and departure date is available already in flights list, then throw exception
void AirlineOperations::checkFlightContradiction(const std::string& targetFlightNumber, const std::string& targetDepartureDate){
    //Loop across all flights to check if there is a flight number with the same flight date or not
    for(auto eachFlight : allFlights)
    {            
        //check nullability before dereferencing
        if(eachFlight){
            //Perform logic check
            if((eachFlight->getFlightNumber() == targetFlightNumber) 
                && (eachFlight->getDepartureDate() == targetDepartureDate)){
                    //if condition true, then throw exception
                    throw std::invalid_argument("Flight number and departure date contradicts with already existing one");
                }
        }
    }
    //if reached this point then flight number and departure date doesn't contradict with existing one
    //return safely
    return;
}

//Function which handles aircrafts assigning to flights
//Returns bool indicating success or failure process
bool AirlineOperations::assignAircraftToFlight(const std::string& tailNumber, const std::string& flightNumber, const std::string& departureDate) {
    auto aircraftIt = std::find_if(allAircrafts.begin(), allAircrafts.end(),
        [&](const auto& a) { return a->getTailNumber() == tailNumber; });
    if (aircraftIt == allAircrafts.end()) {
        std::cout << "No aircraft with tail number entered was found, please try again!\n";
        return false;
    }

    auto flightIt = std::find_if(allFlights.begin(), allFlights.end(),
        [&](const auto& f) { return f->getFlightNumber() == flightNumber; });
    if (flightIt == allFlights.end()) {
        std::cout << "No flight with flight number entered was found, please try again!\n";
        return false;
    }

    if ((*aircraftIt)->hasFlightOnDate(departureDate)) {
        std::cout << "Aircraft already has a flight scheduled on this date.\n";
        return false;
    }

    (*flightIt)->setAircraftReference(*aircraftIt);
    (*aircraftIt)->addFlight(*flightIt); // you'll need this to keep assignedFlights in sync — the other direction
    return true;
}

//Function which will trigger creation of new flight
//If there is a flight number on the same date this will throw an error and must be catched
bool AirlineOperations::createFlight(std::string flightNumber, std::string origin, std::string destination,
                                      std::string departureDate, std::string departureTime, int duration)
{
    //check for contradiction, if found error will be thrown, process aborts
    checkFlightContradiction(flightNumber, departureDate);
    allFlights.push_back(std::make_shared<Flight>(std::move(flightNumber), std::move(origin),
                                                    std::move(destination), std::move(departureDate),
                                                    std::move(departureTime), duration));
    return true;
}

// AirlineOperations.cpp — the real logic moves here
bool AirlineOperations::updateFlightStatus(const std::string& targetFlightNumber, const std::string& targetFlightDeparture,
                                            std::string newStatus) {
    for (auto& eachFlight : allFlights) {
        if (eachFlight->getFlightNumber() == targetFlightNumber && eachFlight->getDepartureDate() == targetFlightDeparture) {
            if (eachFlight->getFlightStatus() == newStatus) {
                std::cout << "Flight status is already " << newStatus << std::endl;
            } else {
                eachFlight->setFlightStatus(std::move(newStatus));
                std::cout << "Flight updated successfully!\n";
            }
            eachFlight->printFlightInfo();
            return true;
        }
    }
    std::cout << "No flights found based on entered criteria, please try again!\n";
    return false;
}

//Function which affects flight status and departure time, by passing delay in hours and in mins
bool AirlineOperations::delayFlight(const std::string& targetFlightNumber, const std::string& targetFlightDepartureDate,
                                     int hours, int mins) {
    for (const auto& eachFlight : allFlights) {
        if (eachFlight->getFlightNumber() == targetFlightNumber &&
            eachFlight->getDepartureDate() == targetFlightDepartureDate) {
            eachFlight->setDelay(hours, mins);
            std::cout << "Delay for flight was set successfully!\n";
            eachFlight->printFlightInfo();
            return true;
        }
    }
    std::cout << "Flight not found, please double check criteria and try again!\n";
    return false;
}

//Function which creates new aircraft and add it to aircrafts list
//Aircraft tail number should be unique
bool AirlineOperations::createAircraft(std::string tailNumber, std::string model, int capacity, bool isAvailable) {
    for (const auto& eachAircraft : allAircrafts) {
        if (eachAircraft->getTailNumber() == tailNumber) {
            std::cout << "Tail number already exists, it cannot duplicate, please try again!\n";
            return false;
        }
    }
    allAircrafts.push_back(std::make_shared<Aircraft>(std::move(tailNumber), std::move(model), capacity, isAvailable));
    return true;
}

bool AirlineOperations::createCrewMember(std::string name, std::string role) {
    allCrewMembers.push_back(std::make_shared<CrewMember>(std::move(name), std::move(role)));
    std::cout << "Crew member created successfully!\n";
    return true;
}

bool AirlineOperations::assignCrewMemberToFlight(int targetID, const std::string& flightNumber, const std::string& departureDate) {
    auto crewIt = std::find_if(allCrewMembers.begin(), allCrewMembers.end(),
        [&](const auto& c) { return c->getId() == targetID; });
    if (crewIt == allCrewMembers.end()) {
        std::cout << "No crew member found with the entered ID, please try again!\n";
        return false;
    }

    auto flightIt = std::find_if(allFlights.begin(), allFlights.end(),
        [&](const auto& f) { return f->getFlightNumber() == flightNumber && f->getDepartureDate() == departureDate; });
    if (flightIt == allFlights.end()) {
        std::cout << "No flight found based on entered criteria, please try again!\n";
        return false;
    }

    int projectedHours = (*crewIt)->getFlightHours() + (*flightIt)->getDuration();
    if (projectedHours > CrewMember::MAX_FLIGHT_HOURS) {
        std::cout << "Crew member would exceed the maximum flight hours limit. Assignment rejected.\n";
        return false;
    }

    (*flightIt)->addCrewMember(*crewIt);
    (*crewIt)->addFlight(*flightIt);
    return true;
}

bool AirlineOperations::removeCrewMemberFromFlight(int targetID, const std::string& flightNumber, const std::string& departureDate) {
    auto crewIt = std::find_if(allCrewMembers.begin(), allCrewMembers.end(),
        [&](const auto& c) { return c->getId() == targetID; });
    if (crewIt == allCrewMembers.end()) {
        std::cout << "No crew member found with the entered ID, please try again!\n";
        return false;
    }

    auto flightIt = std::find_if(allFlights.begin(), allFlights.end(),
        [&](const auto& f) { return f->getFlightNumber() == flightNumber && f->getDepartureDate() == departureDate; });
    if (flightIt == allFlights.end()) {
        std::cout << "No flight found based on entered criteria, please try again!\n";
        return false;
    }

    // Check the crew member is actually assigned to this flight before touching anything
    bool isAssigned = std::any_of((*crewIt)->getFlightsReference().begin(), (*crewIt)->getFlightsReference().end(),
        [&](const std::weak_ptr<Flight>& wf) {
            auto locked = wf.lock();
            return locked && locked->getFlightNumber() == flightNumber;
        });
    if (!isAssigned) {
        std::cout << "Crew member is not assigned to this flight.\n";
        return false;
    }

    (*flightIt)->removeCrewMember(*crewIt);
    (*crewIt)->removeFlight(*flightIt);
    return true;
}

bool AirlineOperations::newAircraftMaintenance(const std::string& tailNumber, std::string dateScheduled, std::string caseDescription) {
    auto aircraftIt = std::find_if(allAircrafts.begin(), allAircrafts.end(),
        [&](const auto& a) { return a->getTailNumber() == tailNumber; });

    if (aircraftIt == allAircrafts.end()) {
        std::cout << "No aircraft with tail number entered was found, please try again!\n";
        return false;
    }

    return (*aircraftIt)->addNewMaintenance(std::move(dateScheduled), std::move(caseDescription));
}

bool AirlineOperations::searchFlight(const std::string& departureDate, const std::string& origin, const std::string& destination)
{
    int counterFlights = 0; //Initialized to zero, counts number of matching flights
    for(const auto& eachFlight: allFlights)
    {
        if(eachFlight && eachFlight->getDepartureDate() == departureDate && eachFlight->getOrigin() == origin && eachFlight->getDestination() == destination)
        {
            //If a flight found matching criteria, print its info
            eachFlight->printFlightInfo();
            counterFlights++; //increment flight counter
        }
    }

    if(counterFlights == 0)
    {
        //If no flights found inform user and return indicating failed process
        std::cout << "No flights found based on entered criteria, please try again!\n";
        return false;
    } else{
        //return safely indicating successful process
        return true;
    }
    
}

bool AirlineOperations::searchAvailableSeats(const std::string& flightNumber, const std::string& departureDate)
{
    //Perform search based on flight number and departure date only, as flight number can't duplicate on same departure date contradicting airline rules
    auto it = std::find_if(allFlights.begin(), allFlights.end(), 
                            [&](const auto& fl){
                                return fl && fl->getFlightNumber() == flightNumber && fl->getDepartureDate() == departureDate;
                            });

    //Check nullablility before dereferencing
    if(it == allFlights.end())
    {
        //If no flights found inform user and return indicating failed process
        std::cout << "Flight not found based on entered criteria, please try again!";
        return false;
    }

    //Access flight safely and print its seats and return indicating successfull process
    (*it)->printSeatMap();
    return true;

}

std::pair<std::shared_ptr<Flight>, std::shared_ptr<Seat>> 
AirlineOperations::bookFlight(const std::string& flightNumber, const std::string& departureDate, const std::string& seatNumber)
{
    //Search based on flight number and departure date
    auto flightIt = std::find_if(allFlights.begin(), allFlights.end(),
        [&](const auto& f) { return f && f->getFlightNumber() == flightNumber && f->getDepartureDate() == departureDate; });
    
    //Check flight nullability
    if(flightIt == allFlights.end())
    {
        std::cout << "Flight not found based on entered criteria, please try again!\n";
        //Return null to indicate failed process        
        return {nullptr, nullptr};
    }

    //Book seat number entered by user
    // prints its own error if seat missing/unavailable
    auto seat = (*flightIt)->bookSeat(seatNumber);

    //Check if seat shared pointer is valid or not
    if(!seat)
    {
        //Should have already printed error message inside previous called function
        //Return null to indicate failed process
        return {nullptr, nullptr};
    } else{
        //Return reserved seat and flight reference
        return {*flightIt, seat};
    }
}
