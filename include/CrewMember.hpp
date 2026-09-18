#ifndef CREWMEMBER_HPP
#define CREWMEMBER_HPP

#include <string>
#include <memory>
#include <vector>

//forward declaration
class Flight;



class CrewMember{
    private:
        std::string id;
        std::string name;
        std::string role;
        int flightHours;

        //list of flights that crew member is assigned to later
        std::vector<std::weak_ptr<Flight>> flightsReference;
    public:
        //Parameterized constructor
        CrewMember(const std::string& name, const std::string& role, int flightHours = 0)
            : name(name), role(role), flightHours(flightHours){}
        
        // Getters
        const std::string& getId() const { return id; }
        const std::string& getName() const { return name; }
        const std::string& getRole() const { return role; }
        int getFlightHours() const { return flightHours; }
        
        // Setters
        void setId(const std::string& newId) { id = newId; }
        void setName(const std::string& newName) { name = newName; }
        void setRole(const std::string& newRole) { role = newRole; }
        void setFlightHours(int newFlightHours) { flightHours = newFlightHours; }

        // Raw reference to weak pointers
        const std::vector<std::weak_ptr<Flight>>& getFlightsReference() const { return flightsReference; }

        //Schedule new flight to crew member
        void addFlight(std::shared_ptr<Flight> newFlight);

        //Remove scheduled flight from crew member
        void removeFlight(std::shared_ptr<Flight> flight);

        //Helper getter: Returns only valid, active flights by locking weak_ptrs
        std::vector<std::shared_ptr<Flight>> getActiveFlights() const;
};

#endif
