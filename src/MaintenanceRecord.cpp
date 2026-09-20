#include "MaintenanceRecord.hpp"
#include <iostream>

// Print function to display maintenance record details
void MaintenanceRecord::print() const {
    std::cout << "ID: " << id << "\n"
                << "Date: " << date << "\n"
                << "Description: " << description << "\n"
                << "Status: " << latestStatus << "\n";
}