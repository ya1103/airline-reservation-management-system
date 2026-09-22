#include "Aircraft.hpp"
#include "Flight.hpp"

//Checks if there is a flight assigned on target date
//If yes return true indicating conflict
//Else return false
bool Aircraft::hasFlightOnDate(const std::string& targetDate) const {
    for (const auto& weakFlight : assignedFlights) {
        if (auto flight = weakFlight.lock()) {
            if (flight->getDepartureDate() == targetDate) {
                return true; // conflict found
            }
        }
    }
    return false;
}

void Aircraft::addFlight(const std::shared_ptr<Flight>& newFlight){
    assignedFlights.push_back(newFlight);
}