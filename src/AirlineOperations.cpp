#include "AirlineOperations.hpp"
#include "Flight.hpp"
#include "Aircraft.hpp"
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