#ifndef MAINTENANCERECORD_HPP
#define MAINTENANCERECORD_HPP

#include <string>
#include <memory>

//Forward declaration
class Aircraft;

class MaintenanceRecord{
    private:
        std::string id;
        std::string dateScheduled;
        std::string description;
        std::string status;

        //Reference to aircraft
        std::weak_ptr<Aircraft> aircraftReference;
    public:
        // Getters
        const std::string& getId() const { return id; }
        const std::string& getDateScheduled() const { return dateScheduled; }
        const std::string& getDescription() const { return description; }
        const std::string& getStatus() const { return status; }

        //setter for status
        void updateStatus(const std::string&);

        // // Direct access to the raw weak_ptr
        // const std::weak_ptr<Aircraft>& getAircraftReference() const { return aircraftReference; }

        // // Safe helper getter: Returns a locked shared_ptr (nullptr if Aircraft was destroyed)
        // std::shared_ptr<Aircraft> getAircraft() const {
        //     return aircraftReference.lock();
        // }

};

#endif
