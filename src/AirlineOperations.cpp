#include "AirlineOperations.hpp"
#include "Flight.hpp"
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