#include "Aircraft.hpp"
#include "MaintenanceRecord.hpp"
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

//function which creates a new maintenance record
bool Aircraft::addNewMaintenance(std::string dateScheduled, std::string caseDescription)
{
    maintenanceOfAircraft.push_back(
    std::make_shared<MaintenanceRecord>(std::move(dateScheduled), std::move(caseDescription), "Scheduled")
    );
    std::cout << "Maintenance record added successfully!\n";

    //Fetch new size of vector
    int newSize = maintenanceOfAircraft.size();
    //Access the latest added shared pointer of maintenance to print its info for user
    maintenanceOfAircraft[newSize-1]->print();
    
    return true;
}
