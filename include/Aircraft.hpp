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

        //array of seats on this aircraft
        std::vector<std::shared_ptr<Seat>> seatsOnAircraft;

        //array of maintenance record of this aircraft
        std::vector<std::shared_ptr<MaintenanceRecord>> maintenanceOfAircraft;
    public:
        // Getters inlined in header
        const std::string& getTailNumber() const { return tailNumber; }
        const std::string& getModel() const { return model; }
        int getCapacity() const { return capacity; }
        bool getIsAvailable() const { return isAvailable; }

        const std::vector<std::shared_ptr<Seat>>& getSeatsOnAircraft() const
            { return seatsOnAircraft; }
        const std::vector<std::shared_ptr<MaintenanceRecord>>& getMaintenanceOfAircraft() const 
            { return maintenanceOfAircraft; }

        //function which creates a new maintenance record
        void addNewMaintenance(void);

        //function which updates a status of maintenance record
        void updateMaintenance(const std::string&);
};

#endif
