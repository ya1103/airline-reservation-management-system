#include "Administrator.hpp"
#include "Flight.hpp"
#include "AirlineOperations.hpp"
#include "Aircraft.hpp"
#include "UserManager.hpp"
#include <exception>
#include <iostream>
#include <limits>

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

                deactivateUser(targetId, targetRole);
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
                                     std::string newDepartureDate, std::string newDepartureTime, int newDuration) {
    try {
        auto ops = User::getAirlineOperations();
        if (!ops) {
            std::cout << "No airline operations reference found!\n";
            return false;
        }
        return ops->createFlight(std::move(newFlightNumber), std::move(newOrigin), std::move(newDestination),
                                  std::move(newDepartureDate), std::move(newDepartureTime), newDuration);
    } catch (std::exception& e) {
        std::cout << std::endl << e.what() << std::endl;
        return false;
    }
}


//Function which updates flight status
//Should be either "Scheduled" or "Delayed" or "Cancelleed" or "Departured"
bool Administrator::updateFlightStatus(const std::string& targetFlightNumber, const std::string& targetFlightDeparture,
                                        std::string flightNewStatus) {
    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return false;
    }
    return ops->updateFlightStatus(targetFlightNumber, targetFlightDeparture, std::move(flightNewStatus));
}

//Function which affects flight status and departure time, by passing delay in hours and in mins
bool Administrator::delayFlight(const std::string& targetFlightNumber, const std::string& targetFlightDepartureDate,
                                 int hours, int mins) {
    if (hours < 0 || hours > 23) {
        std::cout << "Invalid hours, should be between 0 and 23 hours, please try again\n";
        return false;
    }
    if (mins < 0 || mins > 59) {
        std::cout << "Invalid minutes, should be between 0 and 59 mins, please try again\n";
        return false;
    }

    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return false;
    }
    return ops->delayFlight(targetFlightNumber, targetFlightDepartureDate, hours, mins);
}

//Function which creates new aircraft and add it to aircrafts list
//Aircraft tail number should be unique
bool Administrator::createNewAircraft(std::string tailNumber, std::string model, int capacity, bool isAvailable) {
    if (capacity <= 0) {
        std::cout << "Capacity must be greater than zero, please try again!\n";
        return false;
    }

    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return false;
    }
    return ops->createAircraft(std::move(tailNumber), std::move(model), capacity, isAvailable);
}

//Function which assigns aircraft to a flight
//Aircraft should not have any flights on the same day of the targetted flight
bool Administrator::assignAircraftToFlight(const std::string& tailNumber, const std::string& flightNumber, const std::string& departureDate)
{
    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return false;
    }
    return ops->assignAircraftToFlight((tailNumber), flightNumber, departureDate);
}

bool Administrator::createNewCrewMember(std::string name, std::string role) {
    // Validate role is one of the accepted values — input sanity check, belongs here
    if (role != "Pilot" && role != "CoPilot" && role != "FlightAttendant") {
        std::cout << "Invalid role, must be Pilot, CoPilot, or FlightAttendant. Please try again!\n";
        return false;
    }

    if (name.empty()) {
        std::cout << "Name cannot be empty, please try again!\n";
        return false;
    }

    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return false;
    }

    return ops->createCrewMember(std::move(name), std::move(role));
}

bool Administrator::assignCrewMemberToFlight(int targetID, const std::string& flightNumber, const std::string& departureDate) {
    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return false;
    }
    return ops->assignCrewMemberToFlight(targetID, flightNumber, departureDate);
}

bool Administrator::removeCrewMemberFromFlight(int targetID, const std::string& flightNumber, const std::string& departureDate) {
    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return false;
    }
    return ops->removeCrewMemberFromFlight(targetID, flightNumber, departureDate);
}

bool Administrator::newAircraftMaintenance(const std::string& tailNumber, std::string dateScheduled, std::string caseDescription) {
    if (dateScheduled.empty()) {
        std::cout << "Scheduled date cannot be empty, please try again!\n";
        return false;
    }
    if (caseDescription.empty()) {
        std::cout << "Description cannot be empty, please try again!\n";
        return false;
    }

    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return false;
    }
    return ops->newAircraftMaintenance(tailNumber, std::move(dateScheduled), std::move(caseDescription));
}

//Function which creates user based on criteria
//User's role must be either: Passenger, BookingAgent or Administrator
//If passed argument is neither of them it should print error message and abort creation
//If all arguments are valid, print successfull message
bool Administrator::createUser(const std::string& passedName, const std::string& passedRole, const std::string& passedEmail, const std::string& password)
{
        auto manager = allUsersReference.lock();
    if (!manager) {
        std::cout << "No user manager reference found!\n";
        return false;
    }
    return manager->createUser(passedName, passedRole, passedEmail, password);
}

//Function which deletes user by id and role (Passenger, BookingAgent or Administrator)
//If id not found print error message and abort process
//If user found print successfull message
//Note: an admin can not delete him self 
bool Administrator::deactivateUser(int id, const std::string& role)
{
    //Self check
    if((id == this->id) && (role == this->role))
    {
        std::cout << "You cannot delete your own account.\n";
        return false;
    }

    //Check if user manager is available
    auto manager = allUsersReference.lock();
    if (!manager) {
        std::cout << "No user manager reference found!\n";
        return false;
    }

    manager->deactivateUser(id, role);
}