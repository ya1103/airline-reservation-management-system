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