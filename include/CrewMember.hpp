#ifndef CREWMEMBER_HPP
#define CREWMEMBER_HPP

#include <string>
#include <memory>
#include <vector>

//forward declaration
class Flight;



class CrewMemeber{
    private:
        std::string id;
        std::string name;
        std::string role;
        int flightHours;

        //list of flights that crew member is assigned to later
        std::vector<std::weak_ptr<Flight>> flightsReference;
    public:
        // Getters
        const std::string& getId() const { return id; }
        const std::string& getName() const { return name; }
        const std::string& getRole() const { return role; }
        int getFlightHours() const { return flightHours; }
        
        // Raw reference to weak pointers
        const std::vector<std::weak_ptr<Flight>>& getFlightsReference() const { return flightsReference; }

        // Helper getter: Returns only valid, active flights by locking weak_ptrs
        // std::vector<std::shared_ptr<Flight>> getActiveFlights() const {
        //     std::vector<std::shared_ptr<Flight>> activeFlights;
        //     for (const auto& weakRef : flightsReference) {
        //         if (auto sharedRef = weakRef.lock()) {
        //             activeFlights.push_back(sharedRef);
        //         }
        //     }
        //     return activeFlights;
        // }
};

#endif
