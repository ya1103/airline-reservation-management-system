#include "CrewMember.hpp"
#include "Flight.hpp"
#include "algorithm"
#include <iostream>

//Schedule new flight to crew member
void CrewMember::addFlight(std::shared_ptr<Flight> newFlight){
    flightsReference.push_back(std::move(newFlight));
    flightHours += newFlight->getDuration();
}

//Remove scheduled flight from crew member
void CrewMember::removeFlight(std::shared_ptr<Flight> targetFlight){
    auto iterator = std::find_if(flightsReference.begin(), flightsReference.end(),
        [&targetFlight](const std::weak_ptr<Flight>& fl){
            //each weak pointer to flight creates a lock and compares with target flight
            auto shared = fl.lock();
            return shared == targetFlight;
    });

    if(iterator != flightsReference.end()){
        //subtract this flight's duration before removing it, so flightHours
        //accurately reflects only the flights still assigned
        flightHours -= targetFlight->getDuration();
        if (flightHours < 0) flightHours = 0; //defensive clamp, shouldn't happen if accounting stays consistent

        flightsReference.erase(iterator);
        //return if flight was unassigned successfully
        return;
    }
    //otherwise inform that flight was not found
    std::cout << "Flight not found in crew member schedule!";
}

//Helper getter: Returns only valid, active flights by locking weak_ptrs
std::vector<std::shared_ptr<Flight>> CrewMember::getActiveFlights() const {
    std::vector<std::shared_ptr<Flight>> activeFlights;
    for (const auto& weakRef : flightsReference) {
        if (auto sharedRef = weakRef.lock()) {
            activeFlights.push_back(sharedRef);
        }
    }
    return activeFlights;
}

// Print function to display crew member details
void CrewMember::print() const {
    std::cout << "\tID: " << id << "\n"
            << "\tName: " << name << "\n"
            << "\tRole: " << role << "\n"
            << "\tFlight Hours: " << flightHours << "\n";
}