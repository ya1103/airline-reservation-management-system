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
        std::string latestStatus;

        // //Reference to aircraft
        // std::weak_ptr<Aircraft> aircraftReference;
    public:
        //Parameterized constructor
        MaintenanceRecord(const std::string& dateScheduled, const std::string& description, const std::string& status)
            : id("N/A"), dateScheduled(dateScheduled), description(description), latestStatus(status) {}
        
            // Getters
        const std::string& getId() const { return id; }
        const std::string& getDateScheduled() const { return dateScheduled; }
        const std::string& getDescription() const { return description; }
        const std::string& getStatus() const { return latestStatus; }

        //setter for status
        void updateStatus(const std::string&);

        // // Safe helper getter: Returns a locked shared_ptr (nullptr if Aircraft was destroyed)
        // std::shared_ptr<Aircraft> getAircraft() const {
        //     return aircraftReference.lock();
        // }

};

#endif
