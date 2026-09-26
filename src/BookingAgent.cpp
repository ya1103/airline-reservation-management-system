#include "BookingAgent.hpp"
#include "UserManager.hpp"
#include "Passenger.hpp"
#include <limits>
#include <iostream>

void BookingAgent::showMenu() {
    int choice = 0;
    bool exitMenu = false;

    while (!exitMenu) {
        std::cout << "\n====================================\n"
                  << "        BOOKING AGENT MENU          \n"
                  << "====================================\n"
                  << "1. Search Flight\n"
                  << "2. View Available Seats\n"
                  << "3. Book Flight for Passenger\n"
                  << "4. Check In Passenger\n"
                  << "5. Log Out\n"
                  << "Enter your choice: ";

        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {

            case 3: {
                bool processApproved = true;
                int passengerID;
                std::string flightNumber, seatNumber, departureDate;

                do{
                    if(!processApproved)
                    {
                        std::cout << "To return back to agent menu enter '0', to try again enter any number: ";
                        int userInput;
                        std::cin >> userInput;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if(userInput == 0) {break;}
                    }
                    std::cout << "Enter Passenger ID: ";
                    std::cin >> passengerID;

                    std::cout << "Enter Flight Number: ";
                    std::cin >> flightNumber;

                    std::cout << "Enter Seat Number: ";
                    std::cin >> seatNumber;

                    std::cout << "Enter Departure Date (YYYY-MM-DD): ";
                    std::cin >> departureDate;
                }
                while(!(processApproved = BookFlightForPassenger(passengerID, flightNumber, seatNumber, departureDate)));
                break;
            }

            case 5:
                logOut();
                std::cout << "Logged out successfully.\n";
                exitMenu = true;
                break;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }
}


std::shared_ptr<Passenger> BookingAgent::getPassengerByID(int passengerID)
{
    auto manager = allUsersReference.lock();

    //Check nullability before dereferencing
    if (!manager) {
        std::cout << "No user manager reference found!\n";
        return nullptr;
    }

    //Fetch passanger pointer
    auto passenger = manager->findPassengerByID(passengerID);
    //Retrun nevertheless what pointer holds
    //Caller should check the returned pointer
    return passenger;
}

bool BookingAgent::BookFlightForPassenger(int targetPassengerID, const std::string& flightNumber,
                                           const std::string& seatNumber, const std::string& departureDate) {
    
    //Fetch passenger pointer by his id
    auto targetPassengerPtr = getPassengerByID(targetPassengerID);
    
    //Check nullability before dereferencing
    if (!targetPassengerPtr) {
        std::cout << "No passenger found based on ID entered, please try again!\n";
        return false;
    }
    
    return targetPassengerPtr->bookFlight(flightNumber, seatNumber, departureDate);
}