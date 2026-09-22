#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include <string>
#include <vector>
#include <memory>

//Forward declaration
class Flight;
class Seat;
class MaintenanceRecord;

class Aircraft{
    private:
        std::string tailNumber;
        std::string model;
        int capacity;
        bool isAvailable; 

        //array of maintenance record of this aircraft
        std::vector<std::shared_ptr<MaintenanceRecord>> maintenanceOfAircraft;

        //list of flights assigned to aircraft
        std::vector<std::weak_ptr<Flight>> assignedFlights;
    public:
        //Parameterized constructor
        Aircraft(std::string tailNumber, std::string model, int capacity, bool isAvailable = true)
            : tailNumber(std::move(tailNumber)), model(std::move(model)), capacity(capacity), isAvailable(isAvailable) {}
        // Getters inlined in header
        const std::string& getTailNumber() const { return tailNumber; }
        const std::string& getModel() const { return model; }
        int getCapacity() const { return capacity; }
        bool getIsAvailable() const { return isAvailable; }

        const std::vector<std::shared_ptr<MaintenanceRecord>>& getMaintenanceOfAircraft() const 
            { return maintenanceOfAircraft; }

        //function which creates a new maintenance record
        void addNewMaintenance(void);

        //function which updates a status of maintenance record
        void updateMaintenance(const std::string&);

        //function which assigns new flight to this aircraft
        void addFlight(const std::shared_ptr<Flight>& newFlight);

        // Aircraft.hpp
        bool hasFlightOnDate(const std::string& targetDate) const;
};

#endif
