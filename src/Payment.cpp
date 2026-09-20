#include "Payment.hpp"
#include <iostream>

// Print function to display payment details
void Payment::print() const {
    std::cout << "ID: " << id << "\n"
        << "Amount: $" << amount << "\n"
        << "Method: " << method << "\n"
        << "Status: " << status << "\n"
        << "Payment Date: " << paymentDate << "\n";
}