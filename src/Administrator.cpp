#include "Administrator.hpp"
#include <iostream>
#include <limits>
#include "Flight.hpp"
#include "AirlineOperations.hpp"
#include <exception>

//Function which will print down the menu choices for user
void Administrator::showMenu() {
    while (loggedIn) {
        std::cout << "\n====================================\n"
                  << "        ADMINISTRATOR MENU          \n"
                  << "====================================\n"
                  << "1. Create User\n"
                  << "2. Update User\n"
                  << "3. Delete User\n"
                  << "4. Manage Flights\n"
                  << "5. Log Out\n"
                  << "Enter your choice: ";

        int choice;

        //Safety check to prevent bad user input
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                std::string name, role, email, password;

                std::cout << "Enter Name: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, name);

                std::cout << "Enter Role (Passenger / BookingAgent / Administrator): ";
                std::cin >> role;

                std::cout << "Enter Email: ";
                std::cin >> email;

                std::cout << "Enter Password: ";
                std::cin >> password;

                createUser(name, role, email, password);
                break;
            }
            case 2: {                
                int targetId;
                std::string targetRole;

                std::cout << "Enter User ID to update: ";
                std::cin >> targetId;

                std::cout << "Enter Role of the user: ";
                std::cin >> targetRole;

                std::string newName;
                std::cout << "Enter New Name: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, newName);

                updateUserName(targetId, targetRole, newName);
                break;
            }
            case 3: {
                int targetId;
                std::string targetRole;

                std::cout << "Enter User ID to delete: ";
                std::cin >> targetId;

                std::cout << "Enter Role of the user: ";
                std::cin >> targetRole;

                deleteUser(targetId, targetRole);
                break;
            }
            case 4:
                manageFlights();
                break;

            case 5:
                loggedIn = false;
                std::cout << "Logged out successfully.\n";
                break;

            default:
                std::cout << "Invalid option! Please try again.\n";
                break;
        }
    }
}


//Function which will trigger creation of new flight
//If there is a flight number on the same date this will throw an error and must be catched
bool Administrator::createNewFlight(std::string newFlightNumber, std::string newOrigin, std::string newDestination,
                std::string newDepartureDate, std::string newDepartureTime, int newDuration){
          try{
            auto airlineOperationsPtr = User::getAirlineOperations();
            
            //check nullability before dereferencing
            if(airlineOperationsPtr){
                airlineOperationsPtr->checkFlightContradiction(newFlightNumber, newDepartureDate);
                (airlineOperationsPtr->allFlights).push_back(std::make_shared<Flight>(Flight(newFlightNumber, newOrigin, 
                                                                                        newDestination, newDepartureDate,
                                                                                         newDepartureTime, newDuration)));
                //return indicating successfull operation
                return true;
            }
          } catch(std::exception& e){
            std::cout << std::endl << e.what() << std::endl;
            //indicating failed operation
            return false;
          } 
        }


//Function which updates flight status
//Should be either "Scheduled" or "Delayed" or "Cancelleed" or "Departured"
void updateFlightStatus(std::string targetFlightNumber, std::string targetFlightDeparture,
                        std::string flightNewStatus){

                        }