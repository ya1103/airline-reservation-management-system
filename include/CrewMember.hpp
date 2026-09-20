#ifndef CREWMEMBER_HPP
#define CREWMEMBER_HPP

#include <string>
#include <memory>
#include <vector>

//forward declaration
class Flight;



class CrewMember{
    private:
        int id;
        inline static int nextID = 1;
        std::string name;
        std::string role;
        int flightHours;

        //list of flights that crew member is assigned to later
        std::vector<std::weak_ptr<Flight>> flightsReference;
    public:
        //Parameterized constructor ONLY for creating new crew members
        CrewMember(std::string passedName, std::string passedRole)
            : CrewMember(nextID++, std::move(passedName), std::move(passedRole), 0){}

        //Parameterized constructor ONLY for rebuilding crew members from memory during program startup
        CrewMember(int passedID, std::string passedName, std::string passedRole, int passedFlightHours)
            : id(passedID), name(std::move(passedName)), role(std::move(passedRole)), flightHours(passedFlightHours) {}
        
        //Static function which sets static nextID member
        static void setNextID(int passedID) {nextID = passedID;}

        // Getters
        int getId() const { return id; }
        const std::string& getName() const { return name; }
        const std::string& getRole() const { return role; }
        int getFlightHours() const { return flightHours; }
        
        // Setters
        void setName(const std::string& newName) { name = newName; }
        void setFlightHours(int newFlightHours) { flightHours = newFlightHours; }

        // Raw reference to weak pointers
        const std::vector<std::weak_ptr<Flight>>& getFlightsReference() const { return flightsReference; }

        //Schedule new flight to crew member
        void addFlight(std::shared_ptr<Flight> newFlight);

        //Remove scheduled flight from crew member
        void removeFlight(std::shared_ptr<Flight> flight);

        //Helper getter: Returns only valid, active flights by locking weak_ptrs
        std::vector<std::shared_ptr<Flight>> getActiveFlights() const;

        // Print function to display crew member details
        void print() const;
};

#endif
