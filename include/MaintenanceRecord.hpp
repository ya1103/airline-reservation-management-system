#ifndef MAINTENANCERECORD_HPP
#define MAINTENANCERECORD_HPP

#include <string>
#include <memory>

//Forward declaration
class Aircraft;

class MaintenanceRecord{
    private:
        int id;
        inline static int nextID = 1;
        std::string date;
        std::string description;
        std::string latestStatus;

        //Reference to aircraft
        std::weak_ptr<Aircraft> aircraftReference;
    public:
        //Parameterized constructor ONLY for creating new maintenance records
        MaintenanceRecord(std::string dateScheduled, std::string caseDescription)
            : MaintenanceRecord(nextID++, dateScheduled, caseDescription, "Scheduled") {}
        
        //Parameterized constructor ONLY for rebuilding existing records from memory during program startup
        MaintenanceRecord(int passedID, std::string dateScheduled, std::string caseDescription, std::string status)
            : id(passedID), date(std::move(dateScheduled)), description(std::move(caseDescription)), latestStatus(std::move(status)) {}
                
        //Static function which sets static nextID member
        static void setNextID(int passedID) {nextID = passedID;}
        
        // Getters
        int getId() const { return id; }
        const std::string& getDateScheduled() const { return date; }
        const std::string& getDescription() const { return description; }
        const std::string& getStatus() const { return latestStatus; }

        //setter for status
        void updateStatus(std::string newStatus){
            latestStatus = std::move(newStatus);
        }

        // Safe helper getter: Returns a locked shared_ptr (nullptr if Aircraft was destroyed)
        std::shared_ptr<Aircraft> getAircraft() const {
            return aircraftReference.lock();
        }

        // Print function to display maintenance record details
        void print() const;
    };

#endif
