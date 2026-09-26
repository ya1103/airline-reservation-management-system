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

void Payment::refund(void)
{
    std::cout << "Processing refund...\n";
    //There should be an api process to process refund
    std::cout << "Refund issued!\n";
    status = "Refunded";
}

void Payment::process()
{
    std::cout << "Processing payment through " << method << "...\n";
    std::cout << amount << " deducted successfully!\n";
    status = "Completed";
    paymentDate = DateUtils::getCurrentDate();
}